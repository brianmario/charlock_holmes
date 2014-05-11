#ifndef __UTF16_H__
#define __UTF16_H__
#ifndef __UTF_H__
#   include "unicode/utf.h"
#endif
#define U16_IS_SINGLE(c) !U_IS_SURROGATE(c)
#define U16_IS_LEAD(c) (((c)&0xfffffc00)==0xd800)
#define U16_IS_TRAIL(c) (((c)&0xfffffc00)==0xdc00)
#define U16_IS_SURROGATE(c) U_IS_SURROGATE(c)
#define U16_IS_SURROGATE_LEAD(c) (((c)&0x400)==0)
#define U16_IS_SURROGATE_TRAIL(c) (((c)&0x400)!=0)
#define U16_SURROGATE_OFFSET ((0xd800<<10UL)+0xdc00-0x10000)
#define U16_GET_SUPPLEMENTARY(lead, trail) \
    (((UChar32)(lead)<<10UL)+(UChar32)(trail)-U16_SURROGATE_OFFSET)
#define U16_LEAD(supplementary) (UChar)(((supplementary)>>10)+0xd7c0)
#define U16_TRAIL(supplementary) (UChar)(((supplementary)&0x3ff)|0xdc00)
#define U16_LENGTH(c) ((uint32_t)(c)<=0xffff ? 1 : 2)
#define U16_MAX_LENGTH 2
#define U16_GET_UNSAFE(s, i, c) { \
    (c)=(s)[i]; \
    if(U16_IS_SURROGATE(c)) { \
        if(U16_IS_SURROGATE_LEAD(c)) { \
            (c)=U16_GET_SUPPLEMENTARY((c), (s)[(i)+1]); \
        } else { \
            (c)=U16_GET_SUPPLEMENTARY((s)[(i)-1], (c)); \
        } \
    } \
}
#define U16_GET(s, start, i, length, c) { \
    (c)=(s)[i]; \
    if(U16_IS_SURROGATE(c)) { \
        uint16_t __c2; \
        if(U16_IS_SURROGATE_LEAD(c)) { \
            if((i)+1<(length) && U16_IS_TRAIL(__c2=(s)[(i)+1])) { \
                (c)=U16_GET_SUPPLEMENTARY((c), __c2); \
            } \
        } else { \
            if((i)>(start) && U16_IS_LEAD(__c2=(s)[(i)-1])) { \
                (c)=U16_GET_SUPPLEMENTARY(__c2, (c)); \
            } \
        } \
    } \
}
#define U16_NEXT_UNSAFE(s, i, c) { \
    (c)=(s)[(i)++]; \
    if(U16_IS_LEAD(c)) { \
        (c)=U16_GET_SUPPLEMENTARY((c), (s)[(i)++]); \
    } \
}
#define U16_NEXT(s, i, length, c) { \
    (c)=(s)[(i)++]; \
    if(U16_IS_LEAD(c)) { \
        uint16_t __c2; \
        if((i)<(length) && U16_IS_TRAIL(__c2=(s)[(i)])) { \
            ++(i); \
            (c)=U16_GET_SUPPLEMENTARY((c), __c2); \
        } \
    } \
}
#define U16_APPEND_UNSAFE(s, i, c) { \
    if((uint32_t)(c)<=0xffff) { \
        (s)[(i)++]=(uint16_t)(c); \
    } else { \
        (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
        (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
    } \
}
#define U16_APPEND(s, i, capacity, c, isError) { \
    if((uint32_t)(c)<=0xffff) { \
        (s)[(i)++]=(uint16_t)(c); \
    } else if((uint32_t)(c)<=0x10ffff && (i)+1<(capacity)) { \
        (s)[(i)++]=(uint16_t)(((c)>>10)+0xd7c0); \
        (s)[(i)++]=(uint16_t)(((c)&0x3ff)|0xdc00); \
    } else  { \
        (isError)=TRUE; \
    } \
}
#define U16_FWD_1_UNSAFE(s, i) { \
    if(U16_IS_LEAD((s)[(i)++])) { \
        ++(i); \
    } \
}
#define U16_FWD_1(s, i, length) { \
    if(U16_IS_LEAD((s)[(i)++]) && (i)<(length) && U16_IS_TRAIL((s)[i])) { \
        ++(i); \
    } \
}
#define U16_FWD_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        U16_FWD_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define U16_FWD_N(s, i, length, n) { \
    int32_t __N=(n); \
    while(__N>0 && (i)<(length)) { \
        U16_FWD_1(s, i, length); \
        --__N; \
    } \
}
#define U16_SET_CP_START_UNSAFE(s, i) { \
    if(U16_IS_TRAIL((s)[i])) { \
        --(i); \
    } \
}
#define U16_SET_CP_START(s, start, i) { \
    if(U16_IS_TRAIL((s)[i]) && (i)>(start) && U16_IS_LEAD((s)[(i)-1])) { \
        --(i); \
    } \
}
#define U16_PREV_UNSAFE(s, i, c) { \
    (c)=(s)[--(i)]; \
    if(U16_IS_TRAIL(c)) { \
        (c)=U16_GET_SUPPLEMENTARY((s)[--(i)], (c)); \
    } \
}
#define U16_PREV(s, start, i, c) { \
    (c)=(s)[--(i)]; \
    if(U16_IS_TRAIL(c)) { \
        uint16_t __c2; \
        if((i)>(start) && U16_IS_LEAD(__c2=(s)[(i)-1])) { \
            --(i); \
            (c)=U16_GET_SUPPLEMENTARY(__c2, (c)); \
        } \
    } \
}
#define U16_BACK_1_UNSAFE(s, i) { \
    if(U16_IS_TRAIL((s)[--(i)])) { \
        --(i); \
    } \
}
#define U16_BACK_1(s, start, i) { \
    if(U16_IS_TRAIL((s)[--(i)]) && (i)>(start) && U16_IS_LEAD((s)[(i)-1])) { \
        --(i); \
    } \
}
#define U16_BACK_N_UNSAFE(s, i, n) { \
    int32_t __N=(n); \
    while(__N>0) { \
        U16_BACK_1_UNSAFE(s, i); \
        --__N; \
    } \
}
#define U16_BACK_N(s, start, i, n) { \
    int32_t __N=(n); \
    while(__N>0 && (i)>(start)) { \
        U16_BACK_1(s, start, i); \
        --__N; \
    } \
}
#define U16_SET_CP_LIMIT_UNSAFE(s, i) { \
    if(U16_IS_LEAD((s)[(i)-1])) { \
        ++(i); \
    } \
}
#define U16_SET_CP_LIMIT(s, start, i, length) { \
    if((start)<(i) && (i)<(length) && U16_IS_LEAD((s)[(i)-1]) && U16_IS_TRAIL((s)[i])) { \
        ++(i); \
    } \
}
#endif
