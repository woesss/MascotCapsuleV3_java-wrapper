/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Surface.h,v 1.2 2002/04/08 10:41:20 bugfire Exp $ */

/*
 *  Micro3D internal class
 */

#if !defined(SURFACE_H_INCLUDE)
#define SURFACE_H_INCLUDE

#include "IAllocator.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *	Pixel format
 */
typedef enum tagPixelFormat {
	PixelFormat_undef = 0,
	PixelFormat_idx8,		/* 8bit index for palette surface */
	PixelFormat_n16,		/* 16bit device native pixel format */
	PixelFormat_n32,		/* 32bit device native pixel format */
	PixelFormat_default
} PixelFormat;


/**
 *  Memory image holder
 */
typedef struct tagSurface {
	IAllocator* allocator;				/* Memory allocator */
	void*       buffer;					/* Allocated or set by API memory */
	hi_uint32   width, height, pitch;	/* Property */
	PixelFormat format;					/* Pixel format */
	hi_bool     owner;					/* Buffer owner flag */
} Surface;


/* No public method */


#if defined(__cplusplus)
};
#endif


#endif /* SURFACE_H_INCLUDE */
