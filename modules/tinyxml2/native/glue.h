
#ifndef WX_TINYXML2_GLUE_H
#define WX_TINYXML2_GLUE_H

#include "tinyxml2.h"

#include <wxwonkey.h>

namespace tinyxml2{

	wxString wxAttributeName( XMLAttribute *attribute );
	
	wxString wxAttributeValue( XMLAttribute *attribute );
	
	XMLAttribute *wxAttributeNext( XMLAttribute *attribute );
	
	wxString wxNodeValue( XMLNode *node );
	
	wxString wxElementName( XMLElement *element );
	
	wxString wxElementAttribute( XMLElement *element,wxString name,wxString value );
	
	XMLAttribute *wxElementFirstAttribute( XMLElement *element );
	
	wxString wxElementGetText( XMLElement *element );

	void wxDocumentDestroy( XMLDocument *doc );
}

#endif
