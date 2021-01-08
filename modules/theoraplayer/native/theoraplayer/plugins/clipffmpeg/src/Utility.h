/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause
/// 
/// @section DESCRIPTION
/// 
/// Defines internal utility functions.

#ifndef CLIPFFMPEG_UTILITY_H
#define CLIPFFMPEG_UTILITY_H

#include <string>

namespace clipffmpeg
{
	std::string str(int i);
	std::string strf(float i);
	int potCeil(int value);

}

#endif