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

#ifndef CLIPFFMPEG_EXPORT_H
#define CLIPFFMPEG_EXPORT_H

	#ifdef _LIB
		#define clipffmegExport
		#define clipffmegFnExport
	#else
		#ifdef _WIN32
			#ifdef CLIPFFMPEG_EXPORTS
				#define clipffmegExport __declspec(dllexport)
				#define clipffmegFnExport __declspec(dllexport)
			#else
				#define clipffmegExport __declspec(dllimport)
				#define clipffmegFnExport __declspec(dllimport)
			#endif
		#else
			#define clipffmegExport __attribute__ ((visibility("default")))
			#define clipffmegFnExport __attribute__ ((visibility("default")))
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

