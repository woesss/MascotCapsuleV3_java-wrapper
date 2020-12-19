/* -*- mode: C; tab-width: 4 -*- */
/* $Id: Texture.h,v 1.15 2002/07/18 10:46:37 bugfire Exp $ */

#if !defined(TEXTURE_H_INCLUDE)
#define TEXTURE_H_INCLUDE

#include "hi_types.h"
#include "IIstream.h"
#include "IAllocator.h"
#include "Surface.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  Texture
 */
typedef struct tagTexture {
	// struct body replaced for compatibility
	unsigned char raw_stub[512];
} Texture;


#define MAX_TEXTURE		16


/**
 *	Texture array container
 */
typedef struct tagTextureArray {
	hi_sint32 num;
	Texture*  texture[MAX_TEXTURE];
} TextureArray;


/*
 * Texture type ( Texture_loadBmpData() )
 */
typedef enum {
	TEXTURE_TYPE_NORMAL = 0,		/* Model texture */
	TEXTURE_TYPE_SPHEREMAP = 1		/* Envirnmental-spheremap texture */
} hi_texture_type;


/* Public method */
Micro3D_API	void    Texture_initialize( Texture* This, IAllocator* allocator );
Micro3D_API	void    Texture_finalize( Texture* This );
Micro3D_API	hi_bool	Texture_loadBmpData( Texture* This, IIstream* iis, hi_texture_type type );

Micro3D_API hi_bool Texture_isSphereTexture( const Texture* This );

Micro3D_API hi_bool Texture_isLocked( const Texture* This );

#if defined(__cplusplus)
};
#endif


#endif /* TEXTURE_H_INCLUDE */
