/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Figure.h,v 1.11 2002/07/18 10:46:36 bugfire Exp $ */

#if !defined(FIGURE_H_INCLUDE)
#define FIGURE_H_INCLUDE

#include "hi_types.h"
#include "Atrans3i.h"
#include "Surface.h"
#include "Render.h"
#include "IIstream.h"
#include "IAllocator.h"


#if defined(__cplusplus)
extern "C" {
#endif

struct tagSegment;
struct tagActTable;


/**
 *
 */
typedef struct tagFigure {
	// struct body replaced for compatibility
	unsigned char raw_stub[368];
} Figure;


/* Public method */
Micro3D_API	void      Figure_initialize( Figure* This, IAllocator* allocator );
Micro3D_API	void      Figure_finalize( Figure* This );
Micro3D_API	hi_bool   Figure_loadMbacData( Figure* This, IIstream* iis );

Micro3D_API void      Figure_setPosture( Figure* This, struct tagActTable* act, hi_sint32 act_idx, hi_sint32 frame );
Micro3D_API void	  Figure_setPattern( Figure* This, hi_sint32 pattern );
Micro3D_API hi_sint32 Figure_getPattern( Figure* This );
Micro3D_API	hi_sint32 Figure_getNumPatterns( Figure* This );

Micro3D_API hi_bool   Figure_isLocked( const Figure* This );


#if defined(__cplusplus)
};
#endif


#endif /* FIGURE_H_INCLUDE */
