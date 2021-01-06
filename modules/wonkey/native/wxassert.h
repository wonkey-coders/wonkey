
#ifndef WX_ASSERT_H
#define WX_ASSERT_H

#include "wxtypes.h"

void wxRuntimeError( const wxString &str );

#define wxAssert( COND,MSG ) (void)((COND) || (wxRuntimeError(MSG),0))

#ifdef NDEBUG
#define wxDebugAssert( COND,MSG )
#else
#define wxDebugAssert( COND,MSG ) (void)((COND) || (wxRuntimeError(MSG),0))
#endif

#endif
