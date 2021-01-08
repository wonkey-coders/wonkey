/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

//***** Mark was here *****
#include <string.h>

#include "Exception.h"
#include "theoraplayer.h"
#include "Utility.h"

namespace theoraplayer
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

	bool stringEndsWith(const std::string& string, const std::string& suffix)
	{
		int thisLength = (int)string.size();
		int stringLength = (int)suffix.size();
		if (stringLength > thisLength)
		{
			return false;
		}
		return (strcmp(string.c_str() + thisLength - stringLength, suffix.c_str()) == 0);
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

	FILE* openSupportedFormatFile(const std::string& filename, VideoClip::Format& outFormat, std::string& outFullFilename)
	{
		FILE* file = NULL;
		foreach (VideoClip::Format, it, videoClipFormats)
		{
			outFullFilename = filename;
			if (!stringEndsWith(filename, (*it).extension))
			{
				outFullFilename = filename + (*it).extension;
			}
			file = fopen(outFullFilename.c_str(), "rb");
			if (file != NULL)
			{
				outFormat = (*it);
				break;
			}
		}
		return file;
	}

}
