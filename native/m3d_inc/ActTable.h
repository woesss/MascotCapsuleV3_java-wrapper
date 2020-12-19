/* -*- mode: C; tab-width: 4 -*- */
/* $Id: ActTable.h,v 1.4 2001/12/07 06:35:04 bugfire Exp $ */

#if !defined(ACTTABLE_H_INCLUDE)
#define ACTTABLE_H_INCLUDE

#include "hi_types.h"
#include "Atrans3i.h"
#include "IIstream.h"
#include "IAllocator.h"


#if defined(__cplusplus)
extern "C" {
#endif


struct tagFigure;


/**
 *
 */
typedef struct tagActTable {
	// struct body replaced for compatibility
	unsigned char raw_stub[40];
} ActTable;


/* Public method */
Micro3D_API	void      ActTable_initialize( ActTable* This, IAllocator* allocator );
Micro3D_API	void      ActTable_finalize( ActTable* This );
Micro3D_API	hi_bool   ActTable_loadMtraData( ActTable* This, IIstream* iis );

Micro3D_API	hi_sint32 ActTable_getNumActions( const ActTable* This );
Micro3D_API	hi_sint32 ActTable_getNumFrames( const ActTable* This, hi_sint32 act_idx );

Micro3D_API hi_bool   ActTable_isLocked( const ActTable* This );


#if defined(__cplusplus)
};
#endif


#endif /* ACTTABLE_H_INCLUDE */
