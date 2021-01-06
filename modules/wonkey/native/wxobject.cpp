
#include "wxobject.h"
#include "wxdebug.h"
#include "wxarray.h"

wxNullCtor_t wxNullCtor;

// ***** wxObject *****

wxObject::~wxObject(){
}

const char *wxObject::typeName()const{
	return "wonkey.Object";
}

// ***** wxInterface *****

wxInterface::~wxInterface(){
}