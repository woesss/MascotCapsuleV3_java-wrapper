/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Render.h,v 1.19 2002/07/18 10:46:36 bugfire Exp $ */

#if !defined(Render_H_INCLUDE)
#define Render_H_INCLUDE

#include "hi_types.h"
#include "hi_float.h"
#include "Atrans3i.h"
#include "Polydraw.h"
#include "IAllocator.h"


#if defined(__cplusplus)
extern "C" {
#endif

struct tagPolyT;
struct tagPrimTag;
struct tagContextUnit;
struct tagVertWork;
struct tagFigure;
struct tagGeometry;


/**
 *	Int array container
 */
typedef struct tagIntArray {
	int        num;
	hi_sint32* array;
} IntArray;


/**
 *	Draw Primitive API state holder
 */
typedef struct tagDrawPrimitive {
	Atrans3iArray* viewtrans_array;
	hi_sint32	cur_tex;	/* Current texture index */

	hi_sint32	flat_cid;	/* Current flat colored context id */
	hi_sint32	tex_cid;	/* Current textured context id */
} DrawPrimitive;


/**
 *	Draw Primitive GL like wrapper state holder
 */
typedef struct tagPrimitiveGL {
	hi_sint32	prim_id;
	hi_sint32	prim_attr;
	hi_bool		is_texmode;
	hi_sint32	color;
	hi_sint32	pointspriteparam[8];
	hi_sint32	cur_idx;	/* Vertex queue index */

	/* Vertex queue */
	hi_sint32	coord[3*4];
	hi_sint32	normal[3*4];
	hi_sint32	texcoord[2*4];
} PrimitiveGL;


/**
 *  Micro3D Renderer
 */
typedef struct tagRender {
	// struct body replaced for compatibility
	unsigned char raw_stub[3032];
} Render;


/**
 *	Primitive List
 */
typedef struct tagPrimList {
	hi_uint32*	offset;		/* offset table */
	hi_uint32	length;		/* length */
	hi_byte*	buf;		/* primitive array */
	hi_uint32	unit;		/* primitive unit size ( total data size = unit*length ) */
} PrimList;


/*
 *	Attribute flag								0x000000ff
 */
#define	M3D_LIGHTING							0x00000001
#define	M3D_SPECULAR							0x00000002

#define	M3D_TOON_SHADING						0x00000004	/* used only setattribute */
#define	M3D_BLEND								0x00000008	/* used only setattribute */

#define	M3D_COLORKEY							0x00000010	/* used only primitives */
#define	M3D_BLEND_MASK							0x00000060	/* used only primitives */
#define	M3D_BLEND_NORM							0x00000000	/* used only primitives */
#define	M3D_BLEND_HALF	 						0x00000020	/* used only primitives */
#define	M3D_BLEND_ADD							0x00000040	/* used only primitives */
#define	M3D_BLEND_SUB							0x00000060	/* used only primitives */
/* Primitive Z-SORT */
#define M3D_ZSORT_FAR							0x00000004	/* used only primitives */
#define M3D_ZSORT_NEAR							0x00000008	/* used only primitives */

/*
 *	Micro3D Primitive							0x0f000000
 */
#define	M3DP_POINTS								0x01000000
#define	M3DP_LINES								0x02000000
#define	M3DP_TRIANGLES							0x03000000
#define	M3DP_QUADS								0x04000000
#define	M3DP_POINT_SPRITES						0x05000000


/*
 *	Micro3D Primitive Datatype					0x0000ff00
 */
/* Normal */
#define	M3DPD_NORMAL_MASK						0x00000300
#define	M3DPD_NORMAL_NONE						0x00000000
/*                                              0x00000100		NORMAL_PER_CMD would be useless */
#define	M3DPD_NORMAL_PER_FACE					0x00000200
#define	M3DPD_NORMAL_PER_VERTEX					0x00000300
/* Color */
#define	M3DPD_COLOR_MASK						0x00000c00
#define	M3DPD_COLOR_NONE						0x00000000
#define	M3DPD_COLOR_PER_CMD						0x00000400
#define	M3DPD_COLOR_PER_FACE					0x00000800
#define	M3DPD_COLOR_PER_VERTEX					0x00000c00		/* DONT USE, NOT IMPLEMENTED */
/* Texture coordinate */
#define	M3DPD_TEXCOORD_MASK						0x00003000
#define	M3DPD_TEXCOORD_NONE						0x00000000
#define	M3DPD_TEXCOORD_AND_PS_PARAMS_PER_CMD	0x00001000		/* TEXCOORD_PER_CMD must be useless */
#define	M3DPD_TEXCOORD_AND_PS_PARAMS_PER_FACE	0x00002000		/* TEXCOORD_PER_FACE must be useless */
#define	M3DPD_TEXCOORD_AND_PS_PARAMS_PER_VERTEX	0x00003000
#define	M3DPD_TEXCOORD							0x00003000

/* Example1: composite arg
	Gouraud lighting single textured quad
	M3DP_QUAD | M3DPD_NORMAL_PER_VERTEX | M3DPD_TEXCOORD | M3D_LIGHTING | ( 1 << 16 )
	Flat colored singe triangle
	M3DP_TRIANGLE | M3DPD_COLOR_PER_FACE | ( 1 << 16 )
 */

/* Example2: separate arg
	( M3DP_QUAD  | M3D_LIGHTING ) , ( M3DPD_NORMAL_PER_VERTEX | M3DPD_TEXCOORD | ( 1 << 16 ) )
	( M3DP_TRIANGLE ) , ( M3DPD_COLOR_PER_FACE | ( 1 << 16 ) )
 */


/*
 *	PointSprite Flag
 */
#define M3DPSF_LOCAL_SIZE						0x00000000
#define	M3DPSF_PIXEL_SIZE						0x00000001
#define M3DPSF_PERSPECTIVE						0x00000000
#define M3DPSF_NO_PERS							0x00000002


/*
 *	Micro3D Command								0xff000000 (0x80000000 is always on)
 */
#define	M3DCMD_END								0x80000000U
#define	M3DCMD_NOP								0x81000000U
#define	M3DCMD_FLUSH							0x82000000U	/* Render_flush() */
#define	M3DCMD_ATTRIBUTE						0x83000000U	/* Render_setAttribute() */
#define	M3DCMD_CLIP								0x84000000U	/* Render_setClipRect() */
#define	M3DCMD_CENTER							0x85000000U	/* Render_setCenter() */
#define	M3DCMD_TEXINDEX							0x86000000U	/* Render_setTextureIndex() */
#define	M3DCMD_VIEWINDEX						0x87000000U	/* Render_setViewTransIndex() */
#define	M3DCMD_ORTH_SCALE						0x90000000U	/* Render_setOrthographicScale() */
#define	M3DCMD_ORTH_WH							0x91000000U	/* Render_setOrthographicWH() */
#define	M3DCMD_PERS_FOV							0x92000000U	/* Render_setPerspectiveFov() */
#define	M3DCMD_PERS_WH							0x93000000U	/* Render_setPerspectiveWH() */
#define	M3DCMD_AMBIENT_LIGHT					0xa0000000U	/* Render_setAmbientLight() */
#define	M3DCMD_DIRECTION_LIGHT					0xa1000000U	/* Render_setDirectionalLight() */
#define	M3DCMD_TOON_PARAM						0xaf000000U	/* Render_setToonParam() */
#define M3DCMD_VERSION							0xfe000000U	/* Version Verify */
#define	M3DCMD_UNDEF							0xff000000U

#define M3D_V3_COMMAND_LIST_VERSION				0xfe000001U	/* V3 Version tag: Ver=1.0 */


/* Public method */
Micro3D_API	void    Render_initialize( Render* This, IAllocator* allocator );
Micro3D_API	void    Render_finalize( Render* This );

Micro3D_API hi_bool	Render_setTargetTexture( Render* This, Texture* texture );
Micro3D_API	void    Render_setVram( Render* This, hi_uint32 width, hi_uint32 height, hi_sint32 pitch, hi_byte* buffer );
Micro3D_API	void    Render_setClipRect( Render* This, hi_sint32 left, hi_sint32 top, hi_sint32 right, hi_sint32 bottom );

Micro3D_API	void    Render_setViewTrans( Render* This, const Atrans3i* trans );

Micro3D_API	void    Render_setScreenCenter( Render* This, hi_sint32 cx, hi_sint32 cy );
Micro3D_API void	Render_setPerspectiveFov( Render* This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 angle );
Micro3D_API void	Render_setPerspectiveWH( Render* This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 vw, hi_sint32 vh );
Micro3D_API void    Render_setOrthographicScale( Render* This, hi_sint32 sx, hi_sint32 sy );
Micro3D_API void    Render_setOrthographicWH( Render* This, hi_sint32 vw, hi_sint32 vh );

Micro3D_API void	  Render_setAttribute( Render* This, hi_sint32 attribute );
Micro3D_API hi_sint32 Render_getAttribute( Render* This );

Micro3D_API	void    Render_setAmbientLight( Render* This, hi_sint32 intensity );
Micro3D_API	void    Render_setDirectionLight( Render* This, const Vec3i* dir, hi_sint32 intensity );
Micro3D_API	hi_bool	Render_setSphereTexture( Render* This, Texture* texture );

Micro3D_API	void    Render_setToonParam( Render* This, hi_sint32 threshold, hi_sint32 high, hi_sint32 low );

Micro3D_API	hi_bool	Render_setTexture( Render* This, Texture* texture );
Micro3D_API hi_bool Render_setTextureArray( Render* This, TextureArray* array );
Micro3D_API hi_bool Render_flush( Render* This );

/* figure */
Micro3D_API	hi_bool Render_drawFigure( Render* This, struct tagFigure* fig );
Micro3D_API	hi_bool Render_drawFigure_v2( Render* This, struct tagFigure* fig );

/* draw primitive */
Micro3D_API void	Render_setTextureIndex( Render* This, hi_sint32 index );
Micro3D_API void	Render_setViewTransArray( Render* This, Atrans3iArray* array );
Micro3D_API void	Render_setViewTransIndex( Render* This, hi_sint32 index );
Micro3D_API	hi_bool	Render_drawPrimitive( Render* This, hi_sint32 primtype, IntArray* coord, IntArray* normal, IntArray* texcoord, IntArray* color );
Micro3D_API hi_sint32 Render_drawCommandList( Render* This, IntArray* array );

/* obsolute? or optional */
Micro3D_API void	Render_setPerspectiveW( Render* This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 vw );
Micro3D_API void    Render_setOrthographicW( Render* This, hi_sint32 vw );

Micro3D_API hi_bool	Render_transPoint( Render* This, Vec3i* dst, const Vec3i* src );
Micro3D_API	hi_bool	Render_drawPrimitive_( Render* This, hi_sint32 primtype, hi_sint32 datatype, IntArray* coord, IntArray* normal, IntArray* texcoord, IntArray* color );


#if defined(__cplusplus)
};
#endif


#endif /* Render_H_INCLUDE */
