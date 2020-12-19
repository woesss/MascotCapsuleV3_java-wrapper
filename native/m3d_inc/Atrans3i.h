/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Atrans3i.h,v 1.8 2002/07/18 10:46:35 bugfire Exp $ */

#if !defined(ATRANS3I_H_INCLUDE)
#define ATRANS3I_H_INCLUDE

#include "hi_types.h"
#include "Vec3i.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  3-Dimention affine transform
 */
typedef struct tagAtrans3i {
	/** 1行1列の要素 */
	hi_sint32  m00;

	/** 1行2列の要素 */
	hi_sint32  m01;  
					  
	/** 1行3列の要素 */
	hi_sint32  m02;  
					  
	/** 1行4列の要素 */
	hi_sint32  m03;  
					  
	/** 2行1列の要素 */
	hi_sint32  m10;  
					  
	/** 2行2列の要素 */
	hi_sint32  m11;  
					  
	/** 2行3列の要素 */
	hi_sint32  m12;  
					  
	/** 2行4列の要素 */
	hi_sint32  m13;  
					  
	/** 3行1列の要素 */
	hi_sint32  m20;  
					  
	/** 3行2列の要素 */
	hi_sint32  m21;  
					  
	/** 3行3列の要素 */
	hi_sint32  m22;  
					  
	/** 3行4列の要素 */
	hi_sint32  m23;
} Atrans3i;


/* Public method */
Micro3D_API	void Atrans3i_set( Atrans3i* This,
							   hi_sint32 a00, hi_sint32 a01, hi_sint32 a02, hi_sint32 a03,
							   hi_sint32 a10, hi_sint32 a11, hi_sint32 a12, hi_sint32 a13,
							   hi_sint32 a20, hi_sint32 a21, hi_sint32 a22, hi_sint32 a23 );

Micro3D_API	void Atrans3i_setIdentity( Atrans3i* This );

Micro3D_API	void Atrans3i_transPoint( const Atrans3i* This, const Vec3i* src, Vec3i* dst );

Micro3D_API	void Atrans3i_multiply( Atrans3i* This, const Atrans3i* t );
Micro3D_API	void Atrans3i_multiply2( Atrans3i* This, const Atrans3i* t1, const Atrans3i* t2 );

Micro3D_API void Atrans3i_setRotateX( Atrans3i* This, hi_sint32 angle );
Micro3D_API void Atrans3i_setRotateY( Atrans3i* This, hi_sint32 angle );
Micro3D_API void Atrans3i_setRotateZ( Atrans3i* This, hi_sint32 angle );
Micro3D_API void Atrans3i_setRotateV( Atrans3i* This, const Vec3i* axis, hi_sint32 angle );

Micro3D_API	void Atrans3i_setViewTrans( Atrans3i* This, const Vec3i* position, const Vec3i* look, const Vec3i* up );
Micro3D_API	void Atrans3i_normalize( Atrans3i* This, const Atrans3i* src );


/**
 *	Atrans3i array container
 */
typedef struct tagAtrans3iArray {
	hi_sint32 ref_cnt;
	hi_sint32 num;
	Atrans3i* trans;
} Atrans3iArray;


Micro3D_API	void    Atrans3iArray_initialize( Atrans3iArray* This );
Micro3D_API	void    Atrans3iArray_finalize( Atrans3iArray* This );

Micro3D_API hi_bool Atrans3iArray_set( Atrans3iArray* This, Atrans3i* trans, hi_sint32 num );
Micro3D_API hi_bool Atrans3iArray_isLocked( Atrans3iArray* This );


#if defined(__cplusplus)
};
#endif


#endif /* ATRANS3I_H_INCLUDE */
