/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <string>

#include "Utility.h"

namespace clipffmpeg
{
	std::string str(int i)
	{
		char s[64] = { 0 };
		sprintf(s, "%d", i);
		return std::string(s);
	}

	std::string strf(float i)
	{
		char s[64] = { 0 };
		sprintf(s, "%.3f", i);
		return std::string(s);
	}

	int potCeil(int value)
	{
		--value;
		value |= value >> 1;
		value |= value >> 2;
		value |= value >> 4;
		value |= value >> 8;
		value |= value >> 16;
		++value;
		return value;
	}

}
