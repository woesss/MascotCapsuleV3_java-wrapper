/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Allocator.h,v 1.1.1.1 2001/01/22 09:09:57 tani Exp $ */

#if !defined(ALLOCATOR_H_INCLUDE)
#define ALLOCATOR_H_INCLUDE

#include <hi_types.h>
#include <IAllocator.h>
#include <malloc.h>


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *
 */
typedef struct tagAllocator {
	const IAllocatorVtbl* vtbl;
} Allocator;

void         Allocator_initialize( Allocator* This);
void         Allocator_finalize( Allocator* This );
IAllocator*  Allocator_getInstance() ;

void* _alloc( IAllocator* This, hi_uint32 size );
void* _realloc( IAllocator* This, void* address, hi_uint32 size );
void  _free( IAllocator* This, void* address );


#if defined(__cplusplus)
};
#endif


#endif /* ALLOCATOR_H_INCLUDE */
