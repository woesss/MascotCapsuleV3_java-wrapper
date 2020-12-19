/* -*- mode: C; tab-width: 4 -*- */
/* $Id: IAllocator.h,v 1.1.1.1 2001/01/12 12:10:12 tani Exp $ */

/*
 *  Micro3D interface class
 */

#if !defined(IALLOCATOR_H_INCLUDE)
#define IALLOCATOR_H_INCLUDE

#include "hi_types.h"


#if defined(__cplusplus)
extern "C" {
#endif


/* NOTES: Allocated memory must be aligned */


/**
 *  Allocator interface
 */
typedef struct tagIAllocator {
	const struct tagIAllocatorVtbl* vtbl;
} IAllocator;


/* Interface function table */
typedef struct tagIAllocatorVtbl {
	void*  (*alloc)( IAllocator* This, hi_uint32 size );
	void*  (*realloc)( IAllocator* This, void* address, hi_uint32 size );
	void   (*free)( IAllocator* This, void* address );
} IAllocatorVtbl;


/* Public method macro */
#define IAllocator_alloc(p,sz)         (p)->vtbl->alloc((p),(sz))
#define IAllocator_free(p,addr)        (p)->vtbl->free((p),(addr))

/* unused */
#define IAllocator_realloc(p,addr,sz)  (p)->vtbl->realloc((p),(addr),(sz))


#if defined(__cplusplus)
};
#endif


#endif /* IALLOCATOR_H_INCLUDE */
