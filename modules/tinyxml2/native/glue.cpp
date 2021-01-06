
#include "glue.h"

namespace tinyxml2{

	wxString wxAttributeName( XMLAttribute *attribute ){
		return wxString::fromCString( attribute->Name() );
	}
	
	wxString wxAttributeValue( XMLAttribute *attribute ){
		return wxString::fromCString( attribute->Value() );
	}
	
	XMLAttribute *wxAttributeNext( XMLAttribute *attribute ){
		return const_cast<XMLAttribute*>( attribute->Next() );
	}
	
	wxString wxNodeValue( XMLNode *node ){
		return wxString::fromCString( node->Value() );
	}
	
	wxString wxElementName( XMLElement *element ){
		return wxString::fromCString( element->Name() );
	}
	
	wxString wxElementAttribute( XMLElement *element,wxString name,wxString value ){
		wxCString cstr( value );
		const char *p=0;
		if( value.length() ) p=cstr;
		return wxString::fromCString( element->Attribute( wxCString( name ),p ) );
	}
	
	XMLAttribute *wxElementFirstAttribute( XMLElement *element ){
		return const_cast<XMLAttribute*>( element->FirstAttribute() );
	}
	
	wxString wxElementGetText( XMLElement *element ){
		return wxString::fromCString( element->GetText() );
	}

	void wxDocumentDestroy( XMLDocument *doc ){
		delete doc;
	}
}

