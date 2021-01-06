
#include "wxtypes.h"

#include "wxstring.h"

namespace{

	wxString typeName( const char *&p );
	
	wxString funcName( const char *&p ){
	
		wxString retType=typeName( p ),argTypes;
		while( *p && *p!='E' ){
			if( argTypes.length() ) argTypes+=",";
			argTypes+=typeName( p );
		}
		if( *p ) ++p;
		
		return retType+"("+argTypes+")";
	}

	wxString arrayName( const char *&p ){
	
		int rank=1;
		if( *p>'0' && *p<='9' ) rank=(*p++)-'0';
		
		wxString e=typeName( p );
		
		return e+wxString( "[,,,,,,,,,",rank )+"]";
	}
	
	wxString className( const char *&p ){
		wxString name;
		
		const char *p0=p;

		for( ;; ){
		
			if( !*p ) return name+wxString( p0,p-p0 );
			
			if( *p++!='_' ) continue;
			
			name+=wxString( p0,p-p0-1 );
			
			char c=*p++;
			
			if( c=='0' ){
			
				name+="_";
				
			}else if( c=='1' ){

				wxString types;
				while( *p && *p!='E' ){
					if( types.length() ) types+=",";
					types+=typeName( p );
				}
				name+="<"+types+">";
				if( !*p ) return name;
				++p;
				
			}else if( c=='2' ){
			
				return name;
				
			}else{
			
				name+=".";
				p0=p-1;
				continue;
			}
			
			p0=p;
		}
	}
	
	wxString typeName( const char *&p ){
		switch( *p++ ){
		case 'v':return "Void";
		case 'z':return "Bool";
		case 'i':return "Int";
		case 'f':return "Float";
		case 's':return "String";
		case 'F':return funcName( p );
		case 'A':return arrayName( p );
		case 'T':return className( p );
		case 'P':return typeName( p )+" Ptr";
		}
		return "?!?!?";
	}
}

wxString wxTypeName( const char *type ){
	return typeName( type );
}
