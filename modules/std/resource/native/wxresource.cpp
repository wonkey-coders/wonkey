
#include "wxresource.h"

wxResource::wxResource(){

	flags|=1;
}

void wxResource::gcFinalize(){

	if( !(flags&1) ) return;
	
	onFinalize();
}

void wxResource::discard(){

	if( !(flags&1) ) return;
	
	flags&=~1;
	
	onDiscard();
}

void wxResource::onDiscard(){
}

void wxResource::onFinalize(){
}
