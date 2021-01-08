/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "yuv_util.h"

static void _decodeGrey3(struct Theoraplayer_PixelTransform* t, int stride, int bytesCount)
{
	unsigned char* ySrc = t->y;
	unsigned char* yLineEnd;
	unsigned char* out = t->out;
	unsigned int y;
	for (y = 0; y < t->h; ++y, ySrc += t->yStride - t->w, out += stride - t->w * bytesCount)
	{
		for (yLineEnd = ySrc + t->w; ySrc != yLineEnd; ++ySrc, out += bytesCount)
		{
			out[0] = out[1] = out[2] = *ySrc;
		}
	}
}

void decodeGrey(struct Theoraplayer_PixelTransform* t)
{
	unsigned char* ySrc = t->y;
	unsigned char* yLineEnd;
	unsigned char* out = t->out;
	unsigned int y;
	for (y = 0; y < t->h; ++y, ySrc += t->yStride - t->w)
	{
		for (yLineEnd = ySrc + t->w; ySrc != yLineEnd; ++ySrc, ++out)
		{
			*out = *ySrc;
		}
	}
}

void decodeGrey3(struct Theoraplayer_PixelTransform* t)
{
	_decodeGrey3(t, t->w * 3, 3);
}

void decodeGreyA(struct Theoraplayer_PixelTransform* t)
{
	_decodeGrey3(t, t->w * 4, 4);
	_decodeAlpha(incOut(t, 3), t->w * 4);
}

void decodeGreyX(struct Theoraplayer_PixelTransform* t)
{
	_decodeGrey3(t, t->w * 4, 4);
}

void decodeAGrey(struct Theoraplayer_PixelTransform* t)
{
	_decodeGrey3(incOut(t, 1), t->w * 4, 4);
	_decodeAlpha(t, t->w * 4);
}

void decodeXGrey(struct Theoraplayer_PixelTransform* t)
{
	_decodeGrey3(incOut(t, 1), t->w * 4, 4);
}
