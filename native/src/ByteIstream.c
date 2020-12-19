/* -*- mode: C; tab-width: 4 -*- */
/* $Id: FileIstream.c,v 1.1.1.1 2001/01/22 09:09:57 tani Exp $ */

#include "../inc/ByteIstream.h"

hi_bool ByteIstream_initialize(ByteIstream* This, hi_byte* data, hi_sint32 cnt)
{
	IIstreamVtbl* v = malloc(sizeof(IIstreamVtbl));
	if (v == NULL)
	{
		return HI_FALSE;
	}
	v->readSint8 = _readSint8;
	v->readSint16 = _readSint16;
	v->readSint32 = _readSint32;
	v->readBytes = _readBytes;
	v->skipBytes = _skipBytes;
	v->fail = _fail;
	This->vtbl = v;

	This->buf_ptr = data;
	This->end = &data[cnt];
	This->fail = HI_FALSE;

	return HI_TRUE;
}

void ByteIstream_finalize(ByteIstream* This)
{
	free(This->vtbl);
	This->vtbl = NULL;
}


/**
 *  IIstream_readSint8()
 */
hi_sint8 _readSint8(IIstream* This)
{
	ByteIstream* _This = (ByteIstream*)This;

	if (_This->fail)
	{
		return 0;
	}

	if (_This->buf_ptr >= _This->end)
	{
		_This->fail = HI_TRUE;
		return 0;
	}
	return *_This->buf_ptr++;
}


/**
 *  IIstream_readSint16()
 */
hi_sint16 _readSint16(IIstream* This)
{
	ByteIstream* _This = (ByteIstream*)This;

	if (_This->fail)
	{
		return 0;
	}

	if (_This->buf_ptr + 2 > _This->end)
	{
		_This->fail = HI_TRUE;
		return 0;
	}
	hi_uint8 lo = *_This->buf_ptr++;
	hi_uint8 hi = *_This->buf_ptr++;
	return lo | (hi << 8);
}


/**
 *  IIstream_readSint32()
 */
hi_sint32 _readSint32(IIstream* This)
{
	ByteIstream* _This = (ByteIstream*)This;

	if (_This->fail)
	{
		return 0;
	}

	if (_This->buf_ptr + 4 > _This->end)
	{
		_This->fail = HI_TRUE;
		return 0;
	}
	hi_uint8 b0 = *_This->buf_ptr++;
	hi_uint8 b1 = *_This->buf_ptr++;
	hi_uint8 b2 = *_This->buf_ptr++;
	hi_uint8 b3 = *_This->buf_ptr++;
	return b0 | ((b1 | ((b2 | (b3 << 8)) << 8)) << 8);
}


/**
 *  IIstream_readBytes()
 */
void _readBytes(IIstream* This, hi_byte* buffer, hi_uint32 n)
{
	ByteIstream* _This = (ByteIstream*)This;

	if (_This->fail)
	{
		return;
	}
	if (_This->buf_ptr + n > _This->end)
	{
		_This->fail = HI_TRUE;
		return;
	}

	while (n)
	{
		*buffer++ = *_This->buf_ptr++;
		--n;
	}
}


/**
 *  IIstream_skipBytes()
 */
void _skipBytes(IIstream* This, hi_uint32 n)
{
	ByteIstream* _This = (ByteIstream*)This;

	if (_This->fail)
	{
		return;
	}

	if (_This->buf_ptr + n > _This->end)
	{
		_This->fail = HI_TRUE;
		return;
	}

	_This->buf_ptr += n;
}


/**
 *  IIstream_fail()
 */
hi_bool _fail(IIstream* This)
{
	ByteIstream* _This = (ByteIstream*)This;
	return _This->fail;
}


/* End of file */
