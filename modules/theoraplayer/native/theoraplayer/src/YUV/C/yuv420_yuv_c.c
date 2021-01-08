/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include "yuv_util.h"

static void _decodeYUV(struct Theoraplayer_PixelTransform* t, int stride, int bytesCount, int maxWidth)
{
	int cv;
	int cu;
	int y1;
	int y2;
	int y3;
	int y4;
	int width = (maxWidth == 0 ? t->w : maxWidth);
	unsigned char* ySrcEven;
	unsigned char* ySrcOdd;
	unsigned char* yLineEnd;
	unsigned char* uSrc;
	unsigned char* vSrc;
	unsigned char* out1;
	unsigned char* out2;
	unsigned int y;
	for (y = 0; y < t->h; y += 2)
	{
		ySrcEven = t->y + y * t->yStride;
		ySrcOdd  = t->y + (y + 1) * t->yStride;
		uSrc = t->u + y * t->uStride / 2;
		vSrc = t->v + y * t->vStride / 2;
		out1 = t->out + y * stride;
		out2 = t->out + (y + 1) * stride;
		for (yLineEnd = ySrcEven + width; ySrcEven != yLineEnd;)
		{
			// EVEN columns
			cu = *uSrc;	++uSrc;
			cv = *vSrc;	++vSrc;
			y1 = *ySrcEven;	++ySrcEven;
			y2 = *ySrcOdd;	++ySrcOdd;
			y3 = *ySrcEven;	++ySrcEven;
			y4 = *ySrcOdd;	++ySrcOdd;
			// EVEN columns
			out1[0] = y1;
			out1[1] = cu;
			out1[2] = cv;
			out2[0] = y2;
			out2[1] = cu;
			out2[2] = cv;
			out1 += bytesCount;
			out2 += bytesCount;
			// ODD columns
			out1[0] = y3;
			out1[1] = cu;
			out1[2] = cv;
			out2[0] = y4;
			out2[1] = cu;
			out2[2] = cv;
			out1 += bytesCount;
			out2 += bytesCount;
		}
	}
}

void decodeYUV(struct Theoraplayer_PixelTransform* t)
{
	_decodeYUV(t, t->w * 3, 3, 0);
}

void decodeYUVA(struct Theoraplayer_PixelTransform* t)
{
	_decodeYUV(t, t->w * 4, 4, 0);
	_decodeAlpha(incOut(t, 3), t->w * 4);
}

void decodeYUVX(struct Theoraplayer_PixelTransform* t)
{
	_decodeYUV(t, t->w * 4, 4, 0);
}

void decodeAYUV(struct Theoraplayer_PixelTransform* t)
{
	_decodeYUV(incOut(t, 1), t->w * 4, 4, 0);
	_decodeAlpha(t, t->w * 4);
}

void decodeXYUV(struct Theoraplayer_PixelTransform* t)
{
	_decodeYUV(incOut(t, 1), t->w * 4, 4, 0);
}
