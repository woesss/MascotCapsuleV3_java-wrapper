/* -*- mode: C; tab-width: 4 -*- */
/* $Id: IIstream.h,v 1.1.1.1 2001/01/12 12:10:12 tani Exp $ */

/*
 *  Micro3D interface class
 */

#if !defined(IISTREAM_H_INCLUDE)
#define IISTREAM_H_INCLUDE

#include "hi_types.h"


#if defined(__cplusplus)
extern "C" {
#endif


/**
 *  Input stream interface
 */
typedef struct tagIIstream {
	const struct tagIIstreamVtbl* vtbl;
} IIstream;


/* Interface function table */
typedef struct tagIIstreamVtbl {
	hi_sint8  (*readSint8)( IIstream* This );
	hi_sint16 (*readSint16)( IIstream* This );
	hi_sint32 (*readSint32)( IIstream* This );
	void      (*readBytes)( IIstream* This, hi_byte* buffer, hi_uint32 n );
	void      (*skipBytes)( IIstream* This, hi_uint32 n );
	hi_bool   (*fail)( IIstream* This );
} IIstreamVtbl;


/* Public method macro */
#define IIstream_readSint8(p)        (p)->vtbl->readSint8((p))
#define IIstream_readSint16(p)       (p)->vtbl->readSint16((p))
#define IIstream_readSint32(p)       (p)->vtbl->readSint32((p))
#define IIstream_readUint8(p)        ((hi_uint8)(p)->vtbl->readSint8((p)))
#define IIstream_readUint16(p)       ((hi_uint16)(p)->vtbl->readSint16((p)))
#define IIstream_readUint32(p)       ((hi_uint32)(p)->vtbl->readSint32((p)))
#define IIstream_readBytes(p,buf,n)  (p)->vtbl->readBytes((p),(buf),(n))
#define IIstream_skipBytes(p,n)      (p)->vtbl->skipBytes((p),(n))
#define IIstream_fail(p)             (p)->vtbl->fail((p))


#if defined(__cplusplus)
};
#endif


#endif /* IISTREAM_H_INCLUDE */
