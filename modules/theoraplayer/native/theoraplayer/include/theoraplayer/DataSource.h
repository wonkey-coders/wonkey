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
/// Provides an interface for a generic video data source.

#ifndef THEORAPLAYER_DATA_SOURCE_H
#define THEORAPLAYER_DATA_SOURCE_H

#include <stdint.h>
#include <string>

#include "theoraplayerExport.h"

namespace theoraplayer
{
	/// @brief This is a simple class that provides abstracted data feeding. You can use FileDataSource for regular file playback or
	/// you can implement your own internal streaming solution or a class that uses encrypted datafiles etc. The sky is the limit.
	class theoraplayerExport DataSource
	{
	public:
		DataSource();
		virtual ~DataSource();

		/// @return The name of the format used for creating a VideoClip.
		virtual std::string getFormatName() const = 0;
		/// @return The size of the stream in bytes.
		virtual int64_t getSize() = 0;
		/// @return The current position of the source pointer.
		virtual int64_t getPosition() = 0;

		/// @brief Reads bytesCount bytes from data source and returns number of read bytes
		/// @note If function returns less bytes then nBytes, the system assumes EOF is reached.
		virtual int read(void* output, int bytesCount) = 0;
		/// @brief Positions the source pointer to byteIndex from the start of the source.
		virtual void seek(int64_t byteIndex) = 0;
		/// @return A string representation of the DataSource, eg 'File: source.ogg'
		virtual std::string toString() const = 0;

	};

}
#endif
