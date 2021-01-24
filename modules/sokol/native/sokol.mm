// same as sokol.c, but compiled as Objective-C++
#define SOKOL_IMPL
#define SOKOL_NO_ENTRY // define this if sokol_app.h shouldn't "hijack" the main() function

/* this is only needed for the debug-inspection headers */
#define SOKOL_TRACE_HOOKS
/* 
    sokol 3D-API defines are provided by build options 

    #define SOKOL_GLCORE33
    #define SOKOL_GLES2
    #define SOKOL_GLES3
    #define SOKOL_D3D11
    #define SOKOL_METAL
    #define SOKOL_WGPU

*/
#if __EMSCRIPTEN__
	#define SOKOL_GLES3 // or GLES2
#else
	#define SOKOL_METAL
#endif

#include "sokol_app.h"
#include "sokol_args.h"
#include "sokol_gfx.h"
#include "sokol_glue.h"
#include "sokol_time.h"
#include "sokol_audio.h"
#include "sokol_fetch.h"

#include "util/sokol_debugtext.h"
#include "util/sokol_gl.h"
#include "util/sokol_memtrack.h"
#include "util/sokol_shape.h"
//#include "util/sokol_fontstash.h"
//#include "util/sokol_gfx_imgui.h"
//#include "util/sokol_imgui.h"