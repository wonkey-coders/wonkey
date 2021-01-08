/// @file
/// @version 2.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <memory.h>
#include <stdio.h>
#include <sys/stat.h>

#include "FileDataSource.h"
#include "Exception.h"
#include "Manager.h"
#include "theoraplayer.h"
#include "Utility.h"

namespace theoraplayer
{	
	FileDataSource::FileDataSource(const std::string& filename)
	{
		this->filename = filename;
		this->filePtr = NULL;
		VideoClip::Format format;
		// used for determining the file format, does not throw an exception inside the ctor
		FILE* file = openSupportedFormatFile(this->filename, format, this->fullFilename);
		if (file != NULL)
		{
			fclose(file);
		}
		this->formatName = format.name;
	}

	FileDataSource::~FileDataSource()
	{
		if (this->filePtr != NULL)
		{
			fclose(this->filePtr);
			this->filePtr = NULL;
		}
	}

	void FileDataSource::_openFile()
	{
		if (this->filePtr == NULL)
		{
			VideoClip::Format format;
			this->filePtr = openSupportedFormatFile(this->filename, format, this->fullFilename);
			if (this->filePtr == NULL)
			{
				std::string message = "Can't open or find video file: " + filename;
				log(message);
				throw TheoraplayerException(message);
			}
			this->formatName = format.name;
			
//***** Mark was here! *****
#ifdef _MSC_VER	//_WIN32

			struct _stat64 s;
			_fstati64(_fileno(this->filePtr), &s);
#else
			struct stat s;
			fstat(fileno(this->filePtr), &s);
#endif
			this->length = (int64_t)s.st_size;
		}
	}

	int FileDataSource::read(void* output, int nBytes)
	{
		if (this->filePtr == NULL)
		{
			this->_openFile();
		}
		int64_t n = (int64_t)fread(output, 1, nBytes, this->filePtr);
		return (int)n;
	}

	void FileDataSource::seek(int64_t byte_index)
	{

		if (this->filePtr == NULL) 
		{
			this->_openFile();
		}
		
		fseek( this->filePtr,byte_index,SEEK_SET );
		
		/*
		if (this->filePtr == NULL) 
		{
			this->_openFile();
		}
		// fpos_t is not a scalar in Linux, for more info refer here: https://code.google.com/p/libtheoraplayer/issues/detail?id=6
#ifdef __linux
//_LINUX
		fpos_t fpos = { 0 };
		fpos.__pos = byte_index;
#else
		fpos_t fpos = byte_index;
#endif
		fsetpos(this->filePtr, &fpos);
		*/
	}

	int64_t FileDataSource::getSize()
	{
		if (this->filePtr == NULL)
		{
			this->_openFile();
		}
		return this->length;
	}

	int64_t FileDataSource::getPosition()
	{
		if (this->filePtr == NULL)
		{
			return 0LL;
		}
		return ftell( this->filePtr );
		
		/*
		if (this->filePtr == NULL)
		{
			return 0LL;
		}
#ifdef __linux
//_LINUX
		fpos_t pos;
		fgetpos(this->filePtr, &pos);
		return (int64_t)pos.__pos;
#else
		fpos_t pos;
		fgetpos(this->filePtr, &pos);
		return (int64_t)pos;
#endif
		*/
	}
}
