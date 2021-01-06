
#define GLAPI

#include "wxopengl.h"

#include <stdio.h>

#if __EMSCRIPTEN__

void GLAPIENTRY glClearDepthf( GLclampf depth );

void GLAPIENTRY wxglClearDepth( GLclampd depth ){

	glClearDepthf( (GLclampf)depth );
}

#else

#define SDL_GL_CONTEXT_PROFILE_MASK		21
#define SDL_GL_CONTEXT_PROFILE_ES		0x0004 

void *SDL_GL_GetProcAddress( const char *proc );
int SDL_GL_ExtensionSupported( const char *ext );
int SDL_GL_GetAttribute( int attr,int *value );

void (GLAPIENTRY*wxglClearDepthf)( GLclampf depth );

void GLAPIENTRY wxglClearDepthd( GLclampd depth ){

	wxglClearDepthf( (GLclampf)depth );
}

#endif

void wxglInit(){

#if __EMSCRIPTEN__

	WXGL_ES=1;

	WXGL_draw_buffers=SDL_GL_ExtensionSupported( "GL_WEBGL_draw_buffers" );
		
#else

${INITS}

	int profile=0;
	SDL_GL_GetAttribute( SDL_GL_CONTEXT_PROFILE_MASK,&profile );
	WXGL_ES=( profile==SDL_GL_CONTEXT_PROFILE_ES );

	if( WXGL_ES ){
		
		wxglClearDepthf=SDL_GL_GetProcAddress( "glClearDepthf" );
		wxglClearDepth=wxglClearDepthd;
		
		if( WXGL_draw_buffers=SDL_GL_ExtensionSupported( "GL_EXT_draw_buffers" ) ){			//For MRTSs
			
			wxglDrawBuffers=SDL_GL_GetProcAddress( "glDrawBuffersEXT" );
			
		}else if( WXGL_draw_buffers=SDL_GL_ExtensionSupported( "GL_NV_draw_buffers" ) ){	//For MRTs on nvidia shield!
		
			wxglDrawBuffers=SDL_GL_GetProcAddress( "glDrawBuffersNV" );
		}
		
	}else if( wxglDrawBuffers ){
	
		WXGL_draw_buffers=1;
	}

#endif
	
	WXGL_depth_texture=SDL_GL_ExtensionSupported( "GL_EXT_depth_texture" ) || 
		SDL_GL_ExtensionSupported( "GL_ANGLE_depth_texture" ) ||
		SDL_GL_ExtensionSupported( "GL_WEBGL_depth_texture" ) ||
		SDL_GL_ExtensionSupported( "GL_OES_depth_texture" );
	
	WXGL_seamless_cube_map=SDL_GL_ExtensionSupported( "GL_ARB_seamless_cube_map" );
		
	WXGL_texture_filter_anisotropic=SDL_GL_ExtensionSupported( "GL_ARB_texture_filter_anisotropic" ) ||
		SDL_GL_ExtensionSupported( "GL_EXT_texture_filter_anisotropic" );
		
	WXGL_standard_derivatives=!WXGL_ES  || SDL_GL_ExtensionSupported( "GL_OES_standard_derivatives" );
}
