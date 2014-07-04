#lang racket/base

(require (for-syntax syntax/parse racket/syntax racket)
         ffi/unsafe racket/function racket/string
         "start.rkt" "c.rkt")

(struct jtype (signature tag predicate ctype racket->java java->racket))
(struct jtype/object jtype (class))
(struct jtype/vector jtype/object (element))
(struct jvector (cpointer type length))
(struct jprocedure (args return proc))

(define ((single-compose f1 f2) e) (f1 (f2 e)))

(define (make-jtype obj racket->java java->racket)
  (let ([composed-racket->java (single-compose (jtype-racket->java obj) racket->java)]
        [composed-java->racket (single-compose java->racket (jtype-java->racket obj))])
    ; due to limitation in racket's struct-copy
    (cond
      [(jtype/vector? obj)
       (struct-copy jtype/vector obj
         [racket->java #:parent jtype composed-racket->java]
         [java->racket #:parent jtype composed-java->racket])]
      [(jtype/object? obj)
       (struct-copy jtype/object obj
         [racket->java #:parent jtype composed-racket->java]
         [java->racket #:parent jtype composed-java->racket])]
      [else
       (struct-copy jtype obj
         [racket->java                composed-racket->java]
         [java->racket                composed-java->racket])])))

(define (jtype->ctype obj)
  (make-ctype (jtype-ctype obj) (jtype-racket->java obj) (jtype-java->racket obj)))

; --- signature makers ---
(define (make-class-signature c)  (string-append "L" c ";"))
(define (make-vector-signature s) (string-append "[" s))
(define (make-signature args return)
  (let ([args-signature (string-append* (map jtype-signature args))]
        [return-signature (jtype-signature return)])
    (string-append "(" args-signature ")" return-signature)))

; --- predicates for java types on racket ---
(require (only-in web-server/dispatch/extend make-coerce-safe?) srfi/26/cut)

(define jboolean?   boolean?)
(define jbyte?      byte?)
(define jchar?      char?)
(define jshort?     (make-coerce-safe? (cut < -32768 <> 32767)))
(define jint?       (make-coerce-safe? (cut < -2147483648 <> 2147483647)))
(define jlong?      (make-coerce-safe? (cut < -9223372036854775808 <> 9223372036854775807)))
(define jfloat?     single-flonum?)
(define jdouble?    flonum?)
(define jstring?    string?)
(define ((make-jobject-predicate clss) o) (instance-of? o clss))
(define ((make-jlist-predicate element?) o) (andmap element? o))

; --- java types ---
(define _jboolean (jtype "Z" 'boolean jboolean? __jboolean #f            #f))
(define _jbyte    (jtype "B" 'byte    jbyte?    __jbyte    #f            #f))
(define _jchar    (jtype "C" 'char    jchar?    __jchar    char->integer integer->char))
(define _jshort   (jtype "S" 'short   jshort?   __jshort   #f            #f))
(define _jint     (jtype "I" 'int     jint?     __jint     #f            #f))
(define _jlong    (jtype "J" 'long    jlong?    __jlong    #f            #f))
(define _jfloat   (jtype "F" 'float   jfloat?   __jfloat   #f            #f))
(define _jdouble  (jtype "D" 'double  jdouble?  __jdouble  #f            #f))
(define _jvoid    (jtype "V" 'void    #f        __jvoid    #f            #f))
; hack for _jobject and _jlist so that they dual as a jtype and function
(define _jobject
  ((λ ()
     (struct _jobject jtype/object ()
       #:property prop:procedure 
       (λ (self class-name [racket->java #f] [java->racket #f] [predicate #f])
         (let ([class-id (find-class class-name)])
           (struct-copy jtype/object self
             [signature    #:parent jtype (make-class-signature class-name)]
             [predicate    #:parent jtype (or predicate (make-jobject-predicate class-id))]
             [racket->java #:parent jtype racket->java]
             [java->racket #:parent jtype java->racket]
             [class                 class-id]))))
     (let ([class-id (find-class "Ljava/lang/Object;")])
       (_jobject "Ljava/lang/Object;" 'object (make-jobject-predicate class-id)
                 __jobject #f #f class-id)))))
(define _jstring  (_jobject "java/lang/String" new-string get-string jstring?))
(define _jlist    
  ((λ ()
     (struct _jlist jtype/vector ()
       #:property prop:procedure
       (λ (self element)
         (define-values (make-array array-ref array-set!) (tag->array-info (jtype-tag element)))
         (when (jtype/object? element)
           (let ([clss (jtype/object-class element)])
             (set! make-array (λ (n) (new-object-array n clss #f)))))
         (let* ([signature (make-vector-signature (jtype-signature element))]
                [element-racket->java (or (jtype-racket->java element) identity)]
                [element-java->racket (or (jtype-java->racket element) identity)]
                [element? (or (jtype-predicate element) (λ (_) #t))])
           (struct-copy jtype/vector self
             [signature    #:parent jtype signature]
             [predicate    #:parent jtype (make-jlist-predicate element?)]
             [ctype        #:parent jtype __jobject]
             [racket->java #:parent jtype
              (λ (c)
                (let ([array (make-array (length c))])
                  (for ([e (in-list c)] [i (in-naturals)])
                    (array-set! array i (element-racket->java e)))
                  array))]
             [java->racket #:parent jtype
              (λ (c)
                (for/list ([i (in-range (get-array-length c))])
                  (element-java->racket (array-ref c i))))]
             [class        #:parent jtype/object (find-class signature)]
             [element               element]))))
     (let ([class-id (find-class "[Ljava/lang/Object;")]
           [element-class-id (jtype/object-class _jobject)])
       (_jlist "[Ljava/lang/Object;" 'object (make-jobject-predicate element-class-id) __jobject
               (λ (c)
                 (let ([array (new-object-array (length c) element-class-id #f)])
                   (for ([e (in-list c)]
                         [i (in-naturals)])
                     (set-object-array-element array i e))
                   array))
               (λ (c)
                 (for/list ([i (in-range (get-array-length c))])
                   (get-object-array-element c i)))
               class-id
               _jobject)))))
(define-syntax (_jmethod stx)
  (define-syntax-class type #:literals (->)
    (pattern (~and x (~not (~or (~literal ...) ->)))))
  (syntax-parse stx #:literals (->)
    [(_ arg:type ... (~optional (~seq farg:type (~literal ...))) (~optional (~seq -> return*)))
     (with-syntax* ([(arg* ...) (generate-temporaries #'(arg ...))]
                    [(larg ... . marg) #`(arg* ... #,@(if (attribute farg) #'arg-rest #`()))]
                    [(aarg ...) #`(arg* ... #,@(if (attribute farg) #'(arg-rest) #`()))]
                    [return (if (attribute return*) #'return* #'_jvoid)])
       #`(let* ([args  (list arg ... #,@(if (attribute farg) #`((_jlist farg)) #`()))])
           (jprocedure args return
            (λ (type jnienv clss method func)
              (case type
                [(constructor) (λ (larg ... . marg) (func jnienv clss method aarg ...))]
                [(static-method) (λ (larg ... . marg) (func jnienv clss method aarg ...))]
                [(method) (λ (o larg ... . marg) (func jnienv o method aarg ...))]
                [else (error '_jmethod "invalid type provided")])))))]))
; dynamic and slower version of _jmethod
(define (_jprocedure args return #:repeat-last-arg? [repeat-last-arg? #f])
  (define (nest-at lst i)
    (if (null? lst) (list null)
        (let loop ([lst lst] [i i])
          (cond [(null? lst) null]
                [(zero? i) (list lst)]
                [else (cons (car lst) (loop (cdr lst) (sub1 i)))]))))
 (jprocedure args return
    (if repeat-last-arg?
        (let ([repeat-position (sub1 (length args))])
          (λ (type jnienv clss method func)
            (case type
              [(constructor) (λ larg  (apply func jnienv clss method (nest-at larg repeat-position)))]
              [(static-method) (λ larg (apply func jnienv clss method (nest-at larg repeat-position)))]
              [(method) (λ (o . larg) (apply func jnienv o method (nest-at larg repeat-position)))])))
        (λ (type jnienv clss method func)
          (case type
            [(constructor) (λ larg (apply func jnienv clss method larg))]
            [(static-method) (λ larg (apply func jnienv clss method larg))]
            [(method) (λ (o . larg) (apply func jnienv o method larg))]
            [else (error '_jprocedure "invalid type provided")])))))
; get-jmethod/get-jconstructor pass the following arguments (type jnienv class method func) 
; to a function created by _jmethod or _jprocedure 
; according to the type the function returns one of the following functions
; | constructor   (λ (args ...) ; doesn't need to take in an object and the class is static
; | static-method (λ (args ...) ; same reasoning as above
; | method        (λ (object args ...)


; --- interfacing with java methods ---
(define (get-jconstructor class-id type)
  (let* ([args      (jprocedure-args type)]
         [return    (jprocedure-return type)]
         [proc      (jprocedure-proc type)]
         [signature (make-signature args return)]
         [method-id (get-method-id class-id "<init>" signature)]
         [ffi-func  (get-jrffi-obj "new-object"
                      (_cprocedure (list* __jnienv __jclass __jmethodID (map jtype->ctype args))
                                   __jobject))])
    (proc 'constructor current-jnienv class-id method-id ffi-func)))

(define (get-jmethod class-id method-name type #:static? [static? #f])
  (let* ([args      (jprocedure-args type)]
         [return    (jprocedure-return type)]
         [proc      (jprocedure-proc type)]
         [signature (make-signature args return)]
         [method-id (get-method-id class-id method-name signature #:static? static?)]
         [type      (if static? 'static-method 'method)]
         [ffi-func  (get-jrffi-obj 
                     (format "call-~a~a-method" (if static? "static-" "") (jtype-tag return))       
                     (_cprocedure (append (list __jnienv (if static? __jclass __jobject)
                                                __jmethodID) (map jtype->ctype args))
                                  (jtype->ctype return)))])
    (proc type current-jnienv class-id method-id ffi-func)))


; --- interfacing with java fields ---
(define (get-jaccessor class-id field-name type #:static? [static? #f])
  (let* ([signature (jtype-signature class-id field-name (jtype-signature type))]
         [field-id  (get-field-id class-id field-name signature #:static? static?)]
         [ffi-func  (get-jrffi-obj
                     (format "get-~a~a-field" (if static? "static-" "") (jtype-tag type))
                     (_cprocedure (list __jnienv (if static? __jclass __jobject) __jfieldID) type))])
    (if static? (λ () (ffi-func current-jnienv class-id field-id))
        (λ (obj) (ffi-func current-jnienv obj field-id)))))

(define (get-jmutator class-id field-name type #:static? [static? #f])
  (let* ([signature (jtype-signature class-id field-name (jtype-signature type))]
         [field-id  (get-field-id class-id field-name signature #:static? static?)]
         [ffi-func (get-jrffi-obj 
                    (format "set-~a~a-field" (if static? "static-" "") (jtype-tag type))
                    (_cprocedure (list __jnienv (if static? __jclass __jobject) __jfieldID type) type))])
    (if static? (λ (new-value) (ffi-func current-jnienv class-id field-id new-value))
        (λ (obj new-value) (ffi-func current-jnienv obj field-id new-value)))))

(define (get-jparameter class-id field-name type #:static? [static? #f])
  (let* ([accessor (get-jaccessor class-id field-name type #:static? static?)]
         [mutator  (get-jmutator class-id field-name type #:static? static?)])
    (if static?
        (case-lambda
          [() (accessor)]
          [(new-value) (mutator new-value)])
        (case-lambda
          [(obj) (accessor obj)]
          [(obj new-value) (mutator obj new-value)]))))



(provide _jboolean _jbyte _jchar _jshort _jint _jlong _jfloat _jdouble _jvoid
         _jobject _jstring _jlist)

(provide get-jconstructor get-jmethod get-jparameter get-jmutator get-jaccessor)

;(provide instance-of? (rename-out [find-class find-class]) get-method-id get-field-id)


(provide (all-defined-out)  : -> current-jnienv)











