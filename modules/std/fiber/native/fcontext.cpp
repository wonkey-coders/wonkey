
#include "fcontext.h"

#if _WIN32

#include <windows.h>

unsigned char *alloc_fcontext_stack( size_t size,bool guard ){

	void *vp=::VirtualAlloc( 0,size,MEM_COMMIT,PAGE_READWRITE );
	if( !vp ) return 0;

	if( guard ){
		DWORD old_options;
		::VirtualProtect( vp,1,PAGE_READWRITE|PAGE_GUARD /*PAGE_NOACCESS*/,&old_options );
	}

	return (unsigned char*)vp;
}

void free_fcontext_stack( void *vp,size_t size ){

	::VirtualFree( vp,0,MEM_RELEASE );
}

#else

#include <sys/mman.h>

unsigned char *alloc_fcontext_stack( size_t size,bool guard ){

#if defined(MAP_ANON)
	void *vp=::mmap( 0,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANON,-1,0 );
#else
	void *vp=::mmap( 0,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0 );
#endif
	if( vp==MAP_FAILED ) return 0;

	if( guard ){
		::mprotect( vp,1,PROT_NONE );
	}
	
	return (unsigned char*)vp;
}

void free_fcontext_stack( void *vp,size_t size ){
   
	::munmap( vp,size );
}

#endif
