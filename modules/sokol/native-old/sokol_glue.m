#define SOKOL_IMPL
#define SOKOL_NO_ENTRY // define this if sokol_app.h shouldn't "hijack" the main() function

/* 

	TODO: Specifies rendering backend for platform

		#define SOKOL_GLCORE33
        #define SOKOL_GLES2
        #define SOKOL_GLES3
        #define SOKOL_D3D11
        #define SOKOL_METAL
        #define SOKOL_DUMMY_BACKEND

*/
#define SOKOL_METAL

#include "sokol_app.h"
#include "sokol_gfx.h"