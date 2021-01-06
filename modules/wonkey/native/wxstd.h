
#ifndef WX_STD_H
#define WX_STD_H

#if __OBJC__
#import <Foundation/Foundation.h>
#endif

#include <new>
#include <initializer_list>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>

#ifdef WX_THREADS
#include <atomic>
#endif

#ifndef _MSC_VER
#define __forceinline inline __attribute__((always_inline))
#endif

#endif
