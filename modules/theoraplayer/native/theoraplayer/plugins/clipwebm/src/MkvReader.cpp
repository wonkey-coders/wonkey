/// @file
/// @version 1.0
/// 
/// @section LICENSE
/// 
/// This program is free software; you can redistribute it and/or modify it under
/// the terms of the BSD license: http://opensource.org/licenses/BSD-3-Clause

#include <theoraplayer/DataSource.h>

#include "MkvReader.h"

namespace clipwebm
{
	MkvReader::MkvReader(theoraplayer::DataSource* dataSource)
	{
		this->dataSource = dataSource;
		this->length = (int)dataSource->getSize();
	}

	MkvReader::~MkvReader()
	{
	}

	int MkvReader::Length(long long* total, long long* available)
	{
		if (this->dataSource == NULL)
		{
			return 1; // failed
		}
		if (total != NULL)
		{
			*total = this->length;
		}
		if (available != NULL)
		{
			*available = this->length;
		}
		return 0; // success
	}

	int MkvReader::Read(long long offset, long len, unsigned char* buffer)
	{
		if (this->dataSource == NULL || offset < 0 || offset >= this->length || len < 0)
		{
			return -1; // failed
		}
		if (len > 0)
		{
			this->dataSource->seek(offset);
			this->dataSource->read(buffer, len);
		}
		return 0; // success
	}

}
