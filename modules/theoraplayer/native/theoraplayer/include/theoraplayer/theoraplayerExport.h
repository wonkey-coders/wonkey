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
/// Defines macros for DLL exports/imports.

#ifndef THEORAPLAYER_EXPORT_H
#define THEORAPLAYER_EXPORT_H

	//***** Mark was Here! *****
	#define _LIB 1
	#define _USE_THEORA 1
	#define _YUV_LIBYUV 1

	#ifdef _LIB
		#define theoraplayerExport
		#define theoraplayerFnExport
	#else
		#ifdef _WIN32
			#ifdef THEORAPLAYER_EXPORTS
				#define theoraplayerExport __declspec(dllexport)
				#define theoraplayerFnExport __declspec(dllexport)
			#else
				#define theoraplayerExport __declspec(dllimport)
				#define theoraplayerFnExport __declspec(dllimport)
			#endif
		#else
			#define theoraplayerExport __attribute__ ((visibility("default")))
			#define theoraplayerFnExport __attribute__ ((visibility("default")))
		#endif
	#endif
	#ifndef DEPRECATED_ATTRIBUTE
		#ifdef _MSC_VER
			#define DEPRECATED_ATTRIBUTE __declspec(deprecated("function is deprecated"))
		#else
			#define DEPRECATED_ATTRIBUTE __attribute__((deprecated))
		#endif
	#endif

#endif

