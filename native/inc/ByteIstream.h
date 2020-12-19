/* -*- mode: C; tab-width: 4 -*- */
/* $Id: FileIstream.h,v 1.1.1.1 2001/01/22 09:09:57 tani Exp $ */

#if !defined(BYTEISTREAM_H_INCLUDE)
#define BYTEISTREAM_H_INCLUDE

#include <hi_types.h>
#include <IIstream.h>
#include <stdio.h>
#include <stdlib.h>


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *
 */
typedef struct tagByteIstream {
	const IIstreamVtbl* vtbl;
	hi_byte* buf_ptr;
	const hi_byte* end;
	hi_bool fail;
} ByteIstream;

hi_bool  ByteIstream_initialize( ByteIstream* This, hi_byte* data, hi_sint32 cnt );
void     ByteIstream_finalize( ByteIstream* This );
#define  ByteIstream_getIIstream( This ) ((IIstream*)This)

hi_sint8  _readSint8( IIstream* This );
hi_sint16 _readSint16( IIstream* This );
hi_sint32 _readSint32( IIstream* This );
void      _readBytes( IIstream* This, hi_byte* buffer, hi_uint32 n );
void      _skipBytes( IIstream* This, hi_uint32 n );
hi_bool   _fail( IIstream* This );

#if defined(__cplusplus)
};
#endif


#endif /* FILEISTREAM_H_INCLUDE */
