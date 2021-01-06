
#ifndef BB_OPENGL_H
#define BB_OPENGL_H

#include <stddef.h>

//prevents confusion between 1001 GL headers - pinched from glew...
//
#if defined(__gl_h_) || defined(__GL_H__) || defined(_GL_H) || defined(__X_GL_H)
#error gl.h included before bbopengl.h
#endif
#if defined(__gl2_h_)
#error gl2.h included before bbopengl.h
#endif
#if defined(__gltypes_h_)
#error gltypes.h included before bbopengl.h
#endif
#if defined(__REGAL_H__)
#error Regal.h included before bbopengl.h
#endif
#if defined(__glext_h_) || defined(__GLEXT_H_)
#error glext.h included before bbopengl.h
#endif
#if defined(__gl_ATI_h_)
#error glATI.h included before bbopengl.h
#endif
#define __gl_h_
#define __gl2_h_
#define __GL_H__
#define _GL_H
#define __gltypes_h_
#define __REGAL_H__
#define __X_GL_H
#define __glext_h_
#define __GLEXT_H_
#define __gl_ATI_h_

#ifdef __cplusplus
extern "C"{
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

#if _WIN32
#define GLAPIENTRY __stdcall
#else
#define GLAPIENTRY
#endif

#if __EMSCRIPTEN__
#define GLFUN(X) X
#else
#define GLFUN(X) (GLAPIENTRY*bb##X)
#endif

void bbglInit();

GLAPI int BBGL_ES;

GLAPI int BBGL_draw_buffers;
GLAPI int BBGL_depth_texture;
GLAPI int BBGL_seamless_cube_map;
GLAPI int BBGL_texture_filter_anisotropic;
GLAPI int BBGL_standard_derivatives;

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef char GLchar;
typedef ptrdiff_t GLintptr;
typedef ptrdiff_t GLsizeiptr;
typedef struct __GLsync *GLsync;

${DEFS}

${DECLS}

#if !__EMSCRIPTEN__
${CDEFS}
#endif

#ifdef __cplusplus
}
#endif

#endif
