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
/// Defines macros for DLL exports/imports.

#ifndef CLIPWEBM_EXPORT_H
#define CLIPWEBM_EXPORT_H

	#ifdef _LIB
		#define clipwebmExport
		#define clipwebmFnExport
	#else
		#ifdef _WIN32
			#ifdef CLIPWEBM_EXPORTS
				#define clipwebmExport __declspec(dllexport)
				#define clipwebmFnExport __declspec(dllexport)
			#else
				#define clipwebmExport __declspec(dllimport)
				#define clipwebmFnExport __declspec(dllimport)
			#endif
		#else
			#define clipwebmExport __attribute__ ((visibility("default")))
			#define clipwebmFnExport __attribute__ ((visibility("default")))
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

