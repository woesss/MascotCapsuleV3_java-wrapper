/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Polydraw.h,v 1.16 2002/07/18 10:46:36 bugfire Exp $ */

/*
 *  Micro3D internal class
 */

#if !defined(POLYDRAW_H_INCLUDE)
#define POLYDRAW_H_INCLUDE

#include "hi_types.h"
#include "Texture.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  Polygon renderer
 */
typedef struct tagPolydraw {
	IAllocator* allocator;		/* Memory allocator */

	Surface*  target;			/* Target surface */
	hi_sint32 clip_left;		/* Left clip coordinate */
	hi_sint32 clip_top;			/* Top clip coordinate */
	hi_sint32 clip_right;		/* Right clip coordinate */
	hi_sint32 clip_bottom;		/* Bottom clip coordinate */

	Texture*  texture[2];		/* Texture */
	hi_uint32 color_pixel;		/* Current color pixel */
	hi_uint8  color_index;		/* Current color index */

	hi_uint8* diffuse_map;		/* Diffuse replacement map */
} Polydraw;


/* No public method */


#if defined(__cplusplus)
};
#endif


#endif /* POLYDRAW_H_INCLUDE */
