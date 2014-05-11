#ifndef __UTF_H__
#define __UTF_H__
#include "unicode/utypes.h"
#define U_SENTINEL (-1)
#define U_IS_UNICODE_NONCHAR(c) \
    ((c)>=0xfdd0 && \
     ((uint32_t)(c)<=0xfdef || ((c)&0xfffe)==0xfffe) && \
     (uint32_t)(c)<=0x10ffff)
#define U_IS_UNICODE_CHAR(c) \
    ((uint32_t)(c)<0xd800 || \
        ((uint32_t)(c)>0xdfff && \
         (uint32_t)(c)<=0x10ffff && \
         !U_IS_UNICODE_NONCHAR(c)))
#define U_IS_BMP(c) ((uint32_t)(c)<=0xffff)
#define U_IS_SUPPLEMENTARY(c) ((uint32_t)((c)-0x10000)<=0xfffff)
#define U_IS_LEAD(c) (((c)&0xfffffc00)==0xd800)
#define U_IS_TRAIL(c) (((c)&0xfffffc00)==0xdc00)
#define U_IS_SURROGATE(c) (((c)&0xfffff800)==0xd800)
#define U_IS_SURROGATE_LEAD(c) (((c)&0x400)==0)
#define U_IS_SURROGATE_TRAIL(c) (((c)&0x400)!=0)
#include "unicode/utf8.h"
#include "unicode/utf16.h"
#include "unicode/utf_old.h"
#endif
