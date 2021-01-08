
#if _MSC_VER

#include <openvr.h>

#else
//
// This address an issue with differences between the msvc/mingw abis when returning structs.
//
// See:
//
// https://github.com/ValveSoftware/openvr/issues/133
//
// Looks like the GCC guys don't quite get it yet, still think it's caller/callee popping issue:
//
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=64384

#include <openvr_mingw.h>

#endif

using namespace vr;