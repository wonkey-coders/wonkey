/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines a utility struct for pixel transformation.

#ifndef THEORAPLAYER_PIXEL_TRANSFORM_H
#define THEORAPLAYER_PIXEL_TRANSFORM_H

// no theoraplayer namespace, because this is included in C files

struct Theoraplayer_PixelTransform
{
	unsigned char* raw;
	unsigned char* y;
	unsigned char* u;
	unsigned char* v;
	unsigned char* out;
	unsigned int w;
	unsigned int h;
	unsigned int rawStride;
	unsigned int yStride;
	unsigned int uStride;
	unsigned int vStride;

};
#endif
