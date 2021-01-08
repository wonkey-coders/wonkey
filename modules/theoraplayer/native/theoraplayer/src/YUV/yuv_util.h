/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#ifndef THEORAPLAYER_YUV_UTIL_H
#define THEORAPLAYER_YUV_UTIL_H

#include "PixelTransform.h"

struct Theoraplayer_PixelTransform* incOut(struct Theoraplayer_PixelTransform* t, int n);
void _decodeAlpha(struct Theoraplayer_PixelTransform* t, int stride);

#endif
