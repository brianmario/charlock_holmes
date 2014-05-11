#ifndef __UTF_OLD_H__
#define __UTF_OLD_H__
#ifndef U_HIDE_DEPRECATED_API
#ifndef __UTF_H__
#   include "unicode/utf.h"
#endif
#ifdef U_USE_UTF_DEPRECATES
typedef int32_t UTextOffset;
#endif
#define UTF_SIZE 16
#define UTF_SAFE
#undef UTF_UNSAFE
#undef UTF_STRICT
#define UTF8_ERROR_VALUE_1 0x15
#define UTF8_ERROR_VALUE_2 0x9f
#define UTF_ERROR_VALUE 0xffff
#define UTF_IS_ERROR(c) \
    (((c)&0xfffe)==0xfffe || (c)==UTF8_ERROR_VALUE_1 || (c)==UTF8_ERROR_VALUE_2)
#define UTF_IS_VALID(c) \
    (UTF_IS_UNICODE_CHAR(c) && \
     (c)!=UTF8_ERROR_VALUE_1 && (c)!=UTF8_ERROR_VALUE_2)
#define UTF_IS_SURROGATE(uchar) (((uchar)&0xfffff800)==0xd800)
#define UTF_IS_UNICODE_NONCHAR(c) \
    ((c)>=0xfdd0 && \
     ((uint32_t)(c)<=0xfdef || ((c)&0xfffe)==0xfffe) && \
     (uint32_t)(c)<=0x10ffff)
#define UTF_IS_UNICODE_CHAR(c) \
    ((uint32_t)(c)<0xd800 || \
        ((uint32_t)(c)>0xdfff && \
         (uint32_t)(c)<=0x10ffff && \
         !UTF_IS_UNICODE_NONCHAR(c)))
#define UTF8_COUNT_TRAIL_BYTES(leadByte) (utf8_countTrailBytes[(uint8_t)leadByte])
#define UTF8_MASK_LEAD_BYTE(leadByte, countTrailBytes) ((leadByte)&=(1<<(6-(countTrailBytes)))-1)
#define UTF8_IS_SINGLE(uchar) (((uchar)&0x80)==0)
#define UTF8_IS_LEAD(uchar) ((uint8_t)((uchar)-0xc0)<0x3e)
#define UTF8_IS_TRAIL(uchar) (((uchar)&0xc0)==0x80)
#define UTF8_NEED_MULTIPLE_UCHAR(c) ((uint32_t)(c)>0x7f)
#if 1
#   define UTF8_CHAR_LENGTH(c) \
        ((uint32_t)(c)<=0x7f ? 1 : \
            ((uint32_t)(c)<=0x7ff ? 2 : \
                ((uint32_t)((c)-0x10000)>0xfffff ? 3 : 4) \
            ) \
        )
#else
#   define UTF8_CHAR_LENGTH(c) \
        ((uint32_t)(c)<=0x7f ? 1 : \
            ((uint32_t)(c)<=0x7ff ? 2 : \
                ((uint32_t)(c)<=0xffff ? 3 : \
                    ((uint32_t)(c)<=0x10ffff ? 4 : \
                        ((uint32_t)(c)<=0x3ffffff ? 5 : \
                            ((uint32_t)(c)<=0x7fffffff ? 6 : 3) \
                        ) \
                    ) \
                ) \
            ) \
        )
#endif
#define UTF8_MAX_CHAR_LENGTH 4
#define UTF8_ARRAY_SIZE(size) ((5*(size))/2)
#define UTF8_GET_CHAR_UNSAFE(s, i, c) { \
    int32_t _utf8_get_char_unsafe_index=(int32_t)(i); \
    UTF8_SET_CHAR_START_UNSAFE(s, _utf8_get_char_unsafe_index); \
    UTF8_NEXT_CHAR_UNSAFE(s, _utf8_get_char_unsafe_index, c); \
}
#define UTF8_GET_CHAR_SAFE(s, start, i, length, c, strict) { \
    int32_t _utf8_get_char_safe_index=(int32_t)(i); \
    UTF8_SET_CHAR_START_SAFE(s, start, _utf8_get_char_safe_index); \
    UTF8_NEXT_CHAR_SAFE(s, _utf8_get_char_safe_index, length, c, strict); \
}
#define UTF8_NEXT_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[(i)++]; \
    if((uint8_t)((c)-0xc0)<0x35) { \
        uint8_t __count=UTF8_COUNT_TRAIL_BYTES(c); \
        UTF8_MASK_LEAD_BYTE(c, __count); \
        switch(__count) { \
         \
        case 3: \
            (c)=((c)<<6)|((s)[(i)++]&0x3f); \
        case 2: \
            (c)=((c)<<6)|((s)[(i)++]&0x3f); \
        case 1: \
            (c)=((c)<<6)|((s)[(i)++]&0x3f); \
         \
            break; \
        } \
    } \
}
#define UTF8_APPEND_CHAR_UNSAFE(s, i, c) { \
    if((uint32_t)(c)<=0x7f) { \
        (s)[(i)++]=(uint8_t)(c); \
    } else { \
        if((uint32_t)(c)<=0x7ff) { \
            (s)[(i)++]=(uint8_t)(((c)>>6)|0xc0); \
        } else { \
            if((uint32_t)(c)<=0xffff) { \
                (s)[(i)++]=(uint8_t)(((c)>>12)|0xe0); \
            } else { \
                (s)[(i)++]=(uint8_t)(((c)>>18)|0xf0); \
                (s)[(i)++]=(uint8_t)((((c)>>12)&0x3f)|0x80); \
            } \
            (s)[(i)++]=(uint8_t)((((c)>>6)&0x3f)|0x80); \
        } \
        (s)[(i)++]=(uint8_t)(((c)&0x3f)|0x80); \
    } \
}
#define UTF8_FWD_1_UNSAFE(s, i) { \
    (i)+=1+UTF8_COUNT_TRAIL_BYTES((s)[i]); \
}
#define UTF8_FWD_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        UTF8_FWD_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define UTF8_SET_CHAR_START_UNSAFE(s, i) { \
    while(UTF8_IS_TRAIL((s)[i])) { --(i); } \
}
#define UTF8_NEXT_CHAR_SAFE(s, i, length, c, strict) { \
    (c)=(s)[(i)++]; \
    if((c)>=0x80) { \
        if(UTF8_IS_LEAD(c)) { \
            (c)=utf8_nextCharSafeBody(s, &(i), (int32_t)(length), c, strict); \
        } else { \
            (c)=UTF8_ERROR_VALUE_1; \
        } \
    } \
}
#define UTF8_APPEND_CHAR_SAFE(s, i, length, c)  { \
    if((uint32_t)(c)<=0x7f) { \
        (s)[(i)++]=(uint8_t)(c); \
    } else { \
        (i)=utf8_appendCharSafeBody(s, (int32_t)(i), (int32_t)(length), c, NULL); \
    } \
}
#define UTF8_FWD_1_SAFE(s, i, length) U8_FWD_1(s, i, length)
#define UTF8_FWD_N_SAFE(s, i, length, n) U8_FWD_N(s, i, length, n)
#define UTF8_SET_CHAR_START_SAFE(s, start, i) U8_SET_CP_START(s, start, i)
#define UTF8_PREV_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[--(i)]; \
    if(UTF8_IS_TRAIL(c)) { \
        uint8_t __b, __count=1, __shift=6; \
\
         \
        (c)&=0x3f; \
        for(;;) { \
            __b=(s)[--(i)]; \
            if(__b>=0xc0) { \
                UTF8_MASK_LEAD_BYTE(__b, __count); \
                (c)|=(UChar32)__b<<__shift; \
                break; \
            } else { \
                (c)|=(UChar32)(__b&0x3f)<<__shift; \
                ++__count; \
                __shift+=6; \
            } \
        } \
    } \
}
#define UTF8_BACK_1_UNSAFE(s, i) { \
    while(UTF8_IS_TRAIL((s)[--(i)])) {} \
}
#define UTF8_BACK_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        UTF8_BACK_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define UTF8_SET_CHAR_LIMIT_UNSAFE(s, i) { \
    UTF8_BACK_1_UNSAFE(s, i); \
    UTF8_FWD_1_UNSAFE(s, i); \
}
#define UTF8_PREV_CHAR_SAFE(s, start, i, c, strict) { \
    (c)=(s)[--(i)]; \
    if((c)>=0x80) { \
        if((c)<=0xbf) { \
            (c)=utf8_prevCharSafeBody(s, start, &(i), c, strict); \
        } else { \
            (c)=UTF8_ERROR_VALUE_1; \
        } \
    } \
}
#define UTF8_BACK_1_SAFE(s, start, i) U8_BACK_1(s, start, i)
#define UTF8_BACK_N_SAFE(s, start, i, n) U8_BACK_N(s, start, i, n)
#define UTF8_SET_CHAR_LIMIT_SAFE(s, start, i, length) U8_SET_CP_LIMIT(s, start, i, length)
#define UTF_IS_FIRST_SURROGATE(uchar) (((uchar)&0xfffffc00)==0xd800)
#define UTF_IS_SECOND_SURROGATE(uchar) (((uchar)&0xfffffc00)==0xdc00)
#define UTF_IS_SURROGATE_FIRST(c) (((c)&0x400)==0)
#define UTF_SURROGATE_OFFSET ((0xd800<<10UL)+0xdc00-0x10000)
#define UTF16_GET_PAIR_VALUE(first, second) \
    (((first)<<10UL)+(second)-UTF_SURROGATE_OFFSET)
#define UTF_FIRST_SURROGATE(supplementary) (UChar)(((supplementary)>>10)+0xd7c0)
#define UTF_SECOND_SURROGATE(supplementary) (UChar)(((supplementary)&0x3ff)|0xdc00)
#define UTF16_LEAD(supplementary) UTF_FIRST_SURROGATE(supplementary)
#define UTF16_TRAIL(supplementary) UTF_SECOND_SURROGATE(supplementary)
#define UTF16_IS_SINGLE(uchar) !UTF_IS_SURROGATE(uchar)
#define UTF16_IS_LEAD(uchar) UTF_IS_FIRST_SURROGATE(uchar)
#define UTF16_IS_TRAIL(uchar) UTF_IS_SECOND_SURROGATE(uchar)
#define UTF16_NEED_MULTIPLE_UCHAR(c) ((uint32_t)(c)>0xffff)
#define UTF16_CHAR_LENGTH(c) ((uint32_t)(c)<=0xffff ? 1 : 2)
#define UTF16_MAX_CHAR_LENGTH 2
#define UTF16_ARRAY_SIZE(size) (size)
#define UTF16_GET_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[i]; \
    if(UTF_IS_SURROGATE(c)) { \
        if(UTF_IS_SURROGATE_FIRST(c)) { \
            (c)=UTF16_GET_PAIR_VALUE((c), (s)[(i)+1]); \
        } else { \
            (c)=UTF16_GET_PAIR_VALUE((s)[(i)-1], (c)); \
        } \
    } \
}
#define UTF16_GET_CHAR_SAFE(s, start, i, length, c, strict) { \
    (c)=(s)[i]; \
    if(UTF_IS_SURROGATE(c)) { \
        uint16_t __c2; \
        if(UTF_IS_SURROGATE_FIRST(c)) { \
            if((i)+1<(length) && UTF_IS_SECOND_SURROGATE(__c2=(s)[(i)+1])) { \
                (c)=UTF16_GET_PAIR_VALUE((c), __c2); \
                 \
            } else if(strict) {\
                 \
                (c)=UTF_ERROR_VALUE; \
            } \
        } else { \
            if((i)-1>=(start) && UTF_IS_FIRST_SURROGATE(__c2=(s)[(i)-1])) { \
                (c)=UTF16_GET_PAIR_VALUE(__c2, (c)); \
                 \
            } else if(strict) {\
                 \
                (c)=UTF_ERROR_VALUE; \
            } \
        } \
    } else if((strict) && !UTF_IS_UNICODE_CHAR(c)) { \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF16_NEXT_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[(i)++]; \
    if(UTF_IS_FIRST_SURROGATE(c)) { \
        (c)=UTF16_GET_PAIR_VALUE((c), (s)[(i)++]); \
    } \
}
#define UTF16_APPEND_CHAR_UNSAFE(s, i, c) { \
    if((uint32_t)(c)<=0xffff) { \
        (s)[(i)++]=(uint16_t)(c); \
    } else { \
        (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
        (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
    } \
}
#define UTF16_FWD_1_UNSAFE(s, i) { \
    if(UTF_IS_FIRST_SURROGATE((s)[(i)++])) { \
        ++(i); \
    } \
}
#define UTF16_FWD_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        UTF16_FWD_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define UTF16_SET_CHAR_START_UNSAFE(s, i) { \
    if(UTF_IS_SECOND_SURROGATE((s)[i])) { \
        --(i); \
    } \
}
#define UTF16_NEXT_CHAR_SAFE(s, i, length, c, strict) { \
    (c)=(s)[(i)++]; \
    if(UTF_IS_FIRST_SURROGATE(c)) { \
        uint16_t __c2; \
        if((i)<(length) && UTF_IS_SECOND_SURROGATE(__c2=(s)[(i)])) { \
            ++(i); \
            (c)=UTF16_GET_PAIR_VALUE((c), __c2); \
             \
        } else if(strict) {\
             \
            (c)=UTF_ERROR_VALUE; \
        } \
    } else if((strict) && !UTF_IS_UNICODE_CHAR(c)) { \
         \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF16_APPEND_CHAR_SAFE(s, i, length, c) { \
    if((uint32_t)(c)<=0xffff) { \
        (s)[(i)++]=(uint16_t)(c); \
    } else if((uint32_t)(c)<=0x10ffff) { \
        if((i)+1<(length)) { \
            (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
            (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
        } else  { \
            (s)[(i)++]=UTF_ERROR_VALUE; \
        } \
    } else  { \
        (s)[(i)++]=UTF_ERROR_VALUE; \
    } \
}
#define UTF16_FWD_1_SAFE(s, i, length) U16_FWD_1(s, i, length)
#define UTF16_FWD_N_SAFE(s, i, length, n) U16_FWD_N(s, i, length, n)
#define UTF16_SET_CHAR_START_SAFE(s, start, i) U16_SET_CP_START(s, start, i)
#define UTF16_PREV_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[--(i)]; \
    if(UTF_IS_SECOND_SURROGATE(c)) { \
        (c)=UTF16_GET_PAIR_VALUE((s)[--(i)], (c)); \
    } \
}
#define UTF16_BACK_1_UNSAFE(s, i) { \
    if(UTF_IS_SECOND_SURROGATE((s)[--(i)])) { \
        --(i); \
    } \
}
#define UTF16_BACK_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        UTF16_BACK_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define UTF16_SET_CHAR_LIMIT_UNSAFE(s, i) { \
    if(UTF_IS_FIRST_SURROGATE((s)[(i)-1])) { \
        ++(i); \
    } \
}
#define UTF16_PREV_CHAR_SAFE(s, start, i, c, strict) { \
    (c)=(s)[--(i)]; \
    if(UTF_IS_SECOND_SURROGATE(c)) { \
        uint16_t __c2; \
        if((i)>(start) && UTF_IS_FIRST_SURROGATE(__c2=(s)[(i)-1])) { \
            --(i); \
            (c)=UTF16_GET_PAIR_VALUE(__c2, (c)); \
             \
        } else if(strict) {\
             \
            (c)=UTF_ERROR_VALUE; \
        } \
    } else if((strict) && !UTF_IS_UNICODE_CHAR(c)) { \
         \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF16_BACK_1_SAFE(s, start, i) U16_BACK_1(s, start, i)
#define UTF16_BACK_N_SAFE(s, start, i, n) U16_BACK_N(s, start, i, n)
#define UTF16_SET_CHAR_LIMIT_SAFE(s, start, i, length) U16_SET_CP_LIMIT(s, start, i, length)
#define UTF32_IS_SAFE(c, strict) \
    (!(strict) ? \
        (uint32_t)(c)<=0x10ffff : \
        UTF_IS_UNICODE_CHAR(c))
#define UTF32_IS_SINGLE(uchar) 1
#define UTF32_IS_LEAD(uchar) 0
#define UTF32_IS_TRAIL(uchar) 0
#define UTF32_NEED_MULTIPLE_UCHAR(c) 0
#define UTF32_CHAR_LENGTH(c) 1
#define UTF32_MAX_CHAR_LENGTH 1
#define UTF32_ARRAY_SIZE(size) (size)
#define UTF32_GET_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[i]; \
}
#define UTF32_GET_CHAR_SAFE(s, start, i, length, c, strict) { \
    (c)=(s)[i]; \
    if(!UTF32_IS_SAFE(c, strict)) { \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF32_NEXT_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[(i)++]; \
}
#define UTF32_APPEND_CHAR_UNSAFE(s, i, c) { \
    (s)[(i)++]=(c); \
}
#define UTF32_FWD_1_UNSAFE(s, i) { \
    ++(i); \
}
#define UTF32_FWD_N_UNSAFE(s, i, n) { \
    (i)+=(n); \
}
#define UTF32_SET_CHAR_START_UNSAFE(s, i) { \
}
#define UTF32_NEXT_CHAR_SAFE(s, i, length, c, strict) { \
    (c)=(s)[(i)++]; \
    if(!UTF32_IS_SAFE(c, strict)) { \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF32_APPEND_CHAR_SAFE(s, i, length, c) { \
    if((uint32_t)(c)<=0x10ffff) { \
        (s)[(i)++]=(c); \
    } else  { \
        (s)[(i)++]=0xfffd; \
    } \
}
#define UTF32_FWD_1_SAFE(s, i, length) { \
    ++(i); \
}
#define UTF32_FWD_N_SAFE(s, i, length, n) { \
    if(((i)+=(n))>(length)) { \
        (i)=(length); \
    } \
}
#define UTF32_SET_CHAR_START_SAFE(s, start, i) { \
}
#define UTF32_PREV_CHAR_UNSAFE(s, i, c) { \
    (c)=(s)[--(i)]; \
}
#define UTF32_BACK_1_UNSAFE(s, i) { \
    --(i); \
}
#define UTF32_BACK_N_UNSAFE(s, i, n) { \
    (i)-=(n); \
}
#define UTF32_SET_CHAR_LIMIT_UNSAFE(s, i) { \
}
#define UTF32_PREV_CHAR_SAFE(s, start, i, c, strict) { \
    (c)=(s)[--(i)]; \
    if(!UTF32_IS_SAFE(c, strict)) { \
        (c)=UTF_ERROR_VALUE; \
    } \
}
#define UTF32_BACK_1_SAFE(s, start, i) { \
    --(i); \
}
#define UTF32_BACK_N_SAFE(s, start, i, n) { \
    (i)-=(n); \
    if((i)<(start)) { \
        (i)=(start); \
    } \
}
#define UTF32_SET_CHAR_LIMIT_SAFE(s, i, length) { \
}
#define UTF_ARRAY_SIZE(size) UTF16_ARRAY_SIZE(size)
#define UTF_GET_CHAR_UNSAFE(s, i, c)                 UTF16_GET_CHAR_UNSAFE(s, i, c)
#define UTF_GET_CHAR_SAFE(s, start, i, length, c, strict) UTF16_GET_CHAR_SAFE(s, start, i, length, c, strict)
#define UTF_NEXT_CHAR_UNSAFE(s, i, c)                UTF16_NEXT_CHAR_UNSAFE(s, i, c)
#define UTF_NEXT_CHAR_SAFE(s, i, length, c, strict)  UTF16_NEXT_CHAR_SAFE(s, i, length, c, strict)
#define UTF_APPEND_CHAR_UNSAFE(s, i, c)              UTF16_APPEND_CHAR_UNSAFE(s, i, c)
#define UTF_APPEND_CHAR_SAFE(s, i, length, c)        UTF16_APPEND_CHAR_SAFE(s, i, length, c)
#define UTF_FWD_1_UNSAFE(s, i)                       UTF16_FWD_1_UNSAFE(s, i)
#define UTF_FWD_1_SAFE(s, i, length)                 UTF16_FWD_1_SAFE(s, i, length)
#define UTF_FWD_N_UNSAFE(s, i, n)                    UTF16_FWD_N_UNSAFE(s, i, n)
#define UTF_FWD_N_SAFE(s, i, length, n)              UTF16_FWD_N_SAFE(s, i, length, n)
#define UTF_SET_CHAR_START_UNSAFE(s, i)              UTF16_SET_CHAR_START_UNSAFE(s, i)
#define UTF_SET_CHAR_START_SAFE(s, start, i)         UTF16_SET_CHAR_START_SAFE(s, start, i)
#define UTF_PREV_CHAR_UNSAFE(s, i, c)                UTF16_PREV_CHAR_UNSAFE(s, i, c)
#define UTF_PREV_CHAR_SAFE(s, start, i, c, strict)   UTF16_PREV_CHAR_SAFE(s, start, i, c, strict)
#define UTF_BACK_1_UNSAFE(s, i)                      UTF16_BACK_1_UNSAFE(s, i)
#define UTF_BACK_1_SAFE(s, start, i)                 UTF16_BACK_1_SAFE(s, start, i)
#define UTF_BACK_N_UNSAFE(s, i, n)                   UTF16_BACK_N_UNSAFE(s, i, n)
#define UTF_BACK_N_SAFE(s, start, i, n)              UTF16_BACK_N_SAFE(s, start, i, n)
#define UTF_SET_CHAR_LIMIT_UNSAFE(s, i)              UTF16_SET_CHAR_LIMIT_UNSAFE(s, i)
#define UTF_SET_CHAR_LIMIT_SAFE(s, start, i, length) UTF16_SET_CHAR_LIMIT_SAFE(s, start, i, length)
#define UTF_IS_SINGLE(uchar) U16_IS_SINGLE(uchar)
#define UTF_IS_LEAD(uchar) U16_IS_LEAD(uchar)
#define UTF_IS_TRAIL(uchar) U16_IS_TRAIL(uchar)
#define UTF_NEED_MULTIPLE_UCHAR(c) UTF16_NEED_MULTIPLE_UCHAR(c)
#define UTF_CHAR_LENGTH(c) U16_LENGTH(c)
#define UTF_MAX_CHAR_LENGTH U16_MAX_LENGTH
#define UTF_GET_CHAR(s, start, i, length, c) U16_GET(s, start, i, length, c)
#define UTF_NEXT_CHAR(s, i, length, c) U16_NEXT(s, i, length, c)
#define UTF_APPEND_CHAR(s, i, length, c) UTF16_APPEND_CHAR_SAFE(s, i, length, c)
#define UTF_FWD_1(s, i, length) U16_FWD_1(s, i, length)
#define UTF_FWD_N(s, i, length, n) U16_FWD_N(s, i, length, n)
#define UTF_SET_CHAR_START(s, start, i) U16_SET_CP_START(s, start, i)
#define UTF_PREV_CHAR(s, start, i, c) U16_PREV(s, start, i, c)
#define UTF_BACK_1(s, start, i) U16_BACK_1(s, start, i)
#define UTF_BACK_N(s, start, i, n) U16_BACK_N(s, start, i, n)
#define UTF_SET_CHAR_LIMIT(s, start, i, length) U16_SET_CP_LIMIT(s, start, i, length)
#endif
#endif
