/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Vec3i.h,v 1.4 2001/12/07 06:35:05 bugfire Exp $ */

#if !defined(VEC3I_H_INCLUDE)
#define VEC3I_H_INCLUDE

#include "hi_types.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  3-Dimension integer vector
 *
 *	Reference counter is not exist. All object will be copied.
 */
typedef struct tagVec3i {
	hi_sint32  x;	/* 1st element */
	hi_sint32  y;	/* 2nd element */
	hi_sint32  z;	/* 3rd element */
} Vec3i;


/* Public method */
Micro3D_API	hi_sint32 Vec3i_dot( const Vec3i* This, const Vec3i* v );
Micro3D_API	void      Vec3i_cross( Vec3i* This, const Vec3i* v );
Micro3D_API	void      Vec3i_cross2( Vec3i* This, const Vec3i* u, const Vec3i* v );
Micro3D_API	void      Vec3i_normalize12( Vec3i* This, const Vec3i* src );


#if defined(__cplusplus)
};
#endif


#endif /* VEC3I_H_INCLUDE */
