
#ifndef WX_WONKEY_H
#define WX_WONKEY_H

#include "wxstd.h"
#include "wxtypes.h"
#include "wxassert.h"
#include "wxstring.h"
#include "wxdebug.h"
#include "wxarray.h"
#include "wxfunction.h"
#include "wxobject.h"
#include "wxweakref.h"
#include "wxvariant.h"
#include "wxtypeinfo_t.h"
#include "wxdeclinfo.h"

#ifdef WX_THREADS
#include "wxgc_mx.h"
#else
#include "wxgc.h"
#endif

extern int wx_argc;

extern char **wx_argv;

extern void wx_print( wxString str );

extern void wx_printf( const char *fmt,...);

#endif
