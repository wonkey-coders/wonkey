
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef WX_FCONTEXT_H
#define WX_FCONTEXT_H

#include <stdlib.h>		// size_t

typedef void *fcontext_t;

struct transfer_t{
    fcontext_t fcontext;
    void *data;
};

extern "C"{

transfer_t jump_fcontext( fcontext_t fcontext,void *vp );
fcontext_t make_fcontext( void *sp,size_t size,void (*func)(transfer_t) );
transfer_t ontop_fcontext( fcontext_t fcontext,void *vp,transfer_t (*func)(transfer_t) );

}

unsigned char *alloc_fcontext_stack( size_t size,bool guard );
void free_fcontext_stack( void *vp,size_t size );

#endif

