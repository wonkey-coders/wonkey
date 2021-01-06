
#ifndef WX_FIBER_H
#define WX_FIBER_H

#include <wxwonkey.h>

namespace wxFiber{

	typedef wxFunction<void()> Entry;

	int startFiber( Entry entry );
	
	int createFiber( Entry entry );
	
	void resumeFiber( int fiber );
	
	void terminateFiber( int fiber );
	
	void suspendCurrentFiber();
	
	void currentFiberSleep( double seconds );
	
	int getCurrentFiber();
}

#endif
