/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Allocator.c,v 1.1.1.1 2001/01/22 09:09:57 tani Exp $ */

#include "../inc/Allocator.h"

Allocator* gAllocator;

/**
 *
 */
void Allocator_initialize( Allocator* This)
{
	IAllocatorVtbl* v = (IAllocatorVtbl*) malloc(sizeof(IAllocatorVtbl));
	v->alloc = _alloc;
	v->realloc = _realloc;
	v->free = _free;
	This->vtbl = v;

	return;
}


/**
 *
 */
void Allocator_finalize( Allocator* This )
{
	free(This->vtbl);
	free(This);
	gAllocator = NULL;
}

IAllocator* Allocator_getInstance()
{
	if (gAllocator == NULL)
	{
		gAllocator = (Allocator*) malloc(sizeof(Allocator));
		Allocator_initialize(gAllocator);
	}
	return ((IAllocator*)gAllocator);
}


/**
 *  IAllocator_alloc()
 */
void* _alloc( IAllocator* This, hi_uint32 size )
{
	return malloc(size);
}


/**
 *  IAllocator_realloc()
 */
void* _realloc( IAllocator* This, void* address, hi_uint32 size )
{
	return realloc( address, size );
}


/**
 *  IAllocator_free()
 */
void _free( IAllocator* This, void* address )
{
	free( address );
}




/* End of file */
