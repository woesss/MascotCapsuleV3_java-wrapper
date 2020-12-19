/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Atrans3i.h,v 1.8 2002/07/18 10:46:35 bugfire Exp $ */

#if !defined(COMPATV2_H_INCLUDE)
#define COMPATV2_H_INCLUDE

#include "hi_types.h"

/* API compatibility utilities */

#if defined(__cplusplus)
extern "C" {
#endif


/* Renamed to ActTable_getNumActinos() */
Micro3D_API	hi_uint32 ActTable_getNumAction( const ActTable* This );
Micro3D_API	hi_sint32 ActTable_getMaxFrame( const ActTable* This, hi_sint32 act_idx );
Micro3D_API	void      ActTable_setFigure( ActTable* This, Figure* fig );
Micro3D_API	void      ActTable_figPosture( ActTable* This, hi_sint32 act_idx, hi_sint32 frame );

/* Renamed to Vec3i_normalize(), dst<>src */
Micro3D_API void Util3D_getUnitVector12( const Vec3i* src, Vec3i* dst );

/* Renamed to Atrans3i_setRotate*() t<>a */
Micro3D_API void Util3D_getRotateX( hi_sint32 a, Atrans3i* t );
Micro3D_API void Util3D_getRotateY( hi_sint32 a, Atrans3i* t );
Micro3D_API void Util3D_getRotateZ( hi_sint32 a, Atrans3i* t );
Micro3D_API void Util3D_getRotateV( const Vec3i* axis, hi_sint32 angle, Atrans3i* This );

/* Renamed to Atrans3i_setViewTrans() */
Micro3D_API void Util3D_getViewTrans( const Vec3i* position, const Vec3i* look, const Vec3i* up, Atrans3i* This );

/* Renamed to Atrans3i_normalize() */
Micro3D_API void Util3D_getUnitTrans( const Atrans3i* src, Atrans3i* dst );

/* Moved to Render_setAttribute() */
Micro3D_API	void	Render_enableLight( Render* This, hi_bool flag );
Micro3D_API	void	Render_enableSphereMap( Render* This, hi_bool flag );
Micro3D_API	void	Render_enableSemiTransparent( Render* This, hi_bool flag );

/* Moved to Render_setAttribute() and Render_setToonParam() */
Micro3D_API	void    Texture_setToonShader( Texture* This, hi_sint32 threshold, hi_sint32 high, hi_sint32 low );
Micro3D_API	void    Texture_setNormalShader( Texture* This );

/* undocumented */
Micro3D_API void    Render_fillRect( Render* This, hi_uint32 rgb, hi_sint32 x, hi_sint32 y, hi_sint32 w, hi_sint32 h );
Micro3D_API void    Render_fillRectRaw( Render* This, hi_uint32 pixel, hi_sint32 x, hi_sint32 y, hi_sint32 w, hi_sint32 h );
Micro3D_API hi_bool Render_drawRect( Render* This, hi_sint32 dx, hi_sint32 dy, hi_sint32 tx, hi_sint32 ty, hi_sint32 w, hi_sint32 h );

/* deleted - undocumented */
#if 0
Micro3D_API	void	Render_forceSemiTransparent( Render* This, hi_semitransparent_type mode );
#endif


#if defined(__cplusplus)
}
#endif


#endif /* COMPATV2_H_INCLUDE */
