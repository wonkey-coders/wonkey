
#include "wxweakref.h"

wxGCWeakRef *wxGC::weakRefs;

wxGCWeakRef::wxGCWeakRef( wxObject *target ):target( target ){

	if( !target) return;
	
	succ=wxGC::weakRefs;
	wxGC::weakRefs=this;
	target->flags|=2;
}

wxGCWeakRef::~wxGCWeakRef(){

	if( !target ) return;
	
	wxAssert( target->flags & 2,"internal wxGCWeakRef error 1" );
	
	wxGCWeakRef **pred=&wxGC::weakRefs,*curr;
	
	target->flags&=~2;

	while( curr=*pred ){
		
		if( curr==this ){
			
			*pred=succ;
			
			if( target->flags & 2 ) return;
			
			while( curr=*pred ){
				if( curr->target==target ){
					target->flags|=2;
					return;
				}
				pred=&curr->succ;
			}
			return;
		}
		
		if( curr->target==target ) target->flags|=2;
			
		pred=&curr->succ;
	}
		
}

wxObject *wxGCWeakRef::getTarget(){

	return target;
}

