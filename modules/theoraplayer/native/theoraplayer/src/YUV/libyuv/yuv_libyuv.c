/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

//***** Mark was here *****
#define _YUV_LIBYUV 1

#ifdef _YUV_LIBYUV

#include <libyuv.h>

#include "yuv_util.h"
#include "yuv_libyuv.h"

void decodeRGB(struct Theoraplayer_PixelTransform* t)
{
	I420ToRAW(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 3, t->w, t->h);
}

void decodeRGBA(struct Theoraplayer_PixelTransform* t)
{
	I420ToABGR(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
	_decodeAlpha(incOut(t, 3), t->w * 4);
}

void decodeRGBX(struct Theoraplayer_PixelTransform* t)
{
    I420ToABGR(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
}

void decodeARGB(struct Theoraplayer_PixelTransform* t)
{
    I420ToBGRA(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
	_decodeAlpha(t, t->w * 4);
}

void decodeXRGB(struct Theoraplayer_PixelTransform* t)
{
    I420ToBGRA(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
}

void decodeBGR(struct Theoraplayer_PixelTransform* t)
{
	I420ToRGB24(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 3, t->w, t->h);
}

void decodeBGRA(struct Theoraplayer_PixelTransform* t)
{
	I420ToARGB(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
	_decodeAlpha(incOut(t, 3), t->w * 4);
}

void decodeBGRX(struct Theoraplayer_PixelTransform* t)
{
	I420ToARGB(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
}

void decodeABGR(struct Theoraplayer_PixelTransform* t)
{
    I420ToRGBA(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
	_decodeAlpha(t, t->w * 4);
}

void decodeXBGR(struct Theoraplayer_PixelTransform* t)
{
	I420ToRGBA(t->y, t->yStride, t->u, t->uStride, t->v, t->vStride, t->out, t->w * 4, t->w, t->h);
}

void initYUVConversionModule()
{

}
#endif
