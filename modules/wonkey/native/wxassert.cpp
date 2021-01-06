
#include "wxassert.h"
#include "wxdebug.h"

void wxRuntimeError( const wxString &msg ){
	wxDB::error( msg );
}