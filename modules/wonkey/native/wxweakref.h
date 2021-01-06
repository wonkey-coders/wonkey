

#ifndef WX_WEAKREF_H
#define WX_WEAKREF_H

#include "wxobject.h"

struct wxGCWeakRef;

namespace wxGC{

	extern wxGCWeakRef *weakRefs;
}

struct wxGCWeakRef : public wxObject{

	wxGCWeakRef *succ;	
	wxObject *target;
	
	wxGCWeakRef( wxObject *target );
	~wxGCWeakRef();
	
	wxObject *getTarget();
};

#endif
