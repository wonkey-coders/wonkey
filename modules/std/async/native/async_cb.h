
#ifndef WX_STD_ASYNC_CB_H
#define WX_STD_ASYNC_CB_H

#include <wxwonkey.h>

#include "async.h"

namespace wxAsync{

	int createAsyncCallback( wxFunction<void()> func,bool oneshot );
	
	void destroyAsyncCallback( int callback );
	
	void invokeAsyncCallback( int callback );
}

#endif
