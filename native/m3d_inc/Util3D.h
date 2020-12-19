/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Util3D.h,v 1.11 2002/04/08 10:41:21 bugfire Exp $ */

#if !defined(UTIL3D_H_INCLUDE)
#define UTIL3D_H_INCLUDE

#include "hi_types.h"
#include "Vec3i.h"
#include "Atrans3i.h"


#if defined(__cplusplus)
extern "C" {
#endif


/* Micro3D math utilties function */
Micro3D_API	hi_sint32 Util3D_iSqrt( hi_uint32 x );
Micro3D_API	hi_sint32 Util3D_sin12( hi_sint32 a );
Micro3D_API	hi_sint32 Util3D_cos12( hi_sint32 a );

Micro3D_API	hi_sint32 Util3D_getVersion( void );


#if defined(__cplusplus)
};
#endif


#endif /* UTIL3D_H_INCLUDE */
