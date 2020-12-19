/* -*- mode: C; tab-width: 4 -*- */
/* $Id: hi_types.h,v 1.2 2001/06/28 09:03:08 tani Exp $ */

#if !defined(HI_TYPES_H_INCLUDE)
#define HI_TYPES_H_INCLUDE

#include <limits.h>


#if defined(__cplusplus)
extern "C" {
#endif


/* NOTES: Negative integer types are represented in two's complement notation. */


#if (CHAR_BIT == 8)
typedef unsigned char  hi_byte;			/* unsigned 8-bit integer */
typedef signed char    hi_sint8;		/* signed 8-bit integer */
typedef unsigned char  hi_uint8;		/* unsigned 8-bit integer */
#endif

#if (SHRT_MAX == 32767)
typedef short          hi_sint16;		/* signed 16-bit integer */
typedef unsigned short hi_uint16;		/* unsigned 16-bit integer */
#endif

#if (INT_MAX == 2147483647)
typedef int            hi_sint32;		/* signed 32-bit integer */
typedef unsigned int   hi_uint32;		/* unsigned 32-bit integer */
#endif

typedef unsigned char  hi_bool;			/* boolean */

#define HI_TRUE   ((hi_bool)1)			/* true */
#define HI_FALSE  ((hi_bool)0)			/* false */


#if defined(__cplusplus)
};
#endif


#endif /* HI_TYPES_H_INCLUDE */
