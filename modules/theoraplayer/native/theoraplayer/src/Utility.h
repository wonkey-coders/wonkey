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
/// Defines internal utility functions.

#ifndef THEORAPLAYER_UTILITY_H
#define THEORAPLAYER_UTILITY_H

#include <string>
#include <vector>

#include "VideoClip.h"

//***** Mark was here *****
#define _USE_THEORA 1

#define LOG_TAG "theoraplayer"

#define foreach(type, name, container) for (std::vector< type >::iterator name = (container).begin(); name != (container).end(); ++name)
#define foreachc(type, name, container) for (std::vector< type >::const_iterator name = (container).begin(); name != (container).end(); ++name)
#define foreach_r(type, name, container) for (std::vector< type >::riterator name = (container).rbegin(); name != (container).rend(); ++name)
#define foreachc_r(type, name, container) for (std::vector< type >::const_riterator name = (container).rbegin(); name != (container).rend(); ++name)

#define foreach_l(type, name, container) for (std::list< type >::iterator name = (container).begin(); name != (container).end(); ++name)
#define foreachc_l(type, name, container) for (std::list< type >::const_iterator name = (container).begin(); name != (container).end(); ++name)
#define foreach_lr(type, name, container) for (std::list< type >::reverse_iterator name = (container).rbegin(); name != (container).rend(); ++name)
#define foreachc_lr(type, name, container) for (std::list< type >::const_reverse_iterator name = (container).rbegin(); name != (container).rend(); ++name)

#define foreach_map(typeKey, typeValue, name, container) for (std::map< typeKey, typeValue >::iterator name = (container).begin(); name != (container).end(); ++name)
#define foreachc_map(typeKey, typeValue, name, container) for (std::map< typeKey, typeValue >::const_iterator name = (container).begin(); name != (container).end(); ++name)
#define foreach_m(type, name, container) for (std::map< std::string, type >::iterator name = (container).begin(); name != (container).end(); ++name)
#define foreachc_m(type, name, container) for (std::map< std::string, type >::const_iterator name = (container).begin(); name != (container).end(); ++name)

#ifdef _USE_THEORA
#define THEORA_DECODER_NAME "Theora"
#endif

namespace theoraplayer
{
	extern std::vector<VideoClip::Format> videoClipFormats;

	std::string str(int i);
	std::string strf(float i);
	bool stringEndsWith(const std::string& string, const std::string& suffix);
	int potCeil(int value);
	FILE* openSupportedFormatFile(const std::string& filename, VideoClip::Format& outFormat, std::string& outFullFilename);

}

//typedef std::string hstr;
//typedef const std::string& chstr;

#endif