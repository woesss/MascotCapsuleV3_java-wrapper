/* -*- mode: C; tab-width: 4 -*- */
/* $Id: hi_float.h,v 1.1 2002/04/08 10:41:24 bugfire Exp $ */

/*
 *  Micro3D internal class
 */

#if !defined(HI_FLOAT_H_INCLUDE)
#define HI_FLOAT_H_INCLUDE

#include "hi_types.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  Poor floating point.
 */
#if 1
typedef struct _hi_float {
	hi_sint16 fraction;	/* fraction ( with sign ) [-2^15, +2^15) */
	hi_sint16 exponent;	/* exponent */
} hi_float;
#else
typedef hi_sint32 hi_float;
#endif


/* No public method */


#if defined(__cplusplus)
};
#endif


#endif /* HI_FLOAT_H_INCLUDE */
