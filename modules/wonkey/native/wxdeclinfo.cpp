
#include "wxdeclinfo_r.h"

// ***** wxDeclInfo ****

wxString wxDeclInfo::toString(){
	return kind+" "+name+":"+(type ? type->name : "?????");
}

wxVariant wxDeclInfo::get( wxVariant instance ){
	wxRuntimeError( "Decl is not gettable" );
	return {};
}
	
void wxDeclInfo::set( wxVariant instance,wxVariant value ){
	wxRuntimeError( "Decl is not settable" );
}
	
wxVariant wxDeclInfo::invoke( wxVariant instance,wxArray<wxVariant> params ){
	wxRuntimeError( "Decl is not invokable" );
	return {};
}

wxArray<wxString> wxDeclInfo::getMetaKeys(){

	if( !meta.length() ) return {};

	wxString eol="~\n";

	int n=1,i0=0;
	while( i0<meta.length() ){
		int i1=meta.find( eol,i0 );
		if( i1==-1 ) break;
		i0=i1+2;
		n+=1;
	}
	
	wxArray<wxString> keys( n );
	
	i0=0;
	for( int i=0;i<n;++i ){
		int i1=meta.find( "=",i0 );
		keys[i]=meta.slice( i0,i1 );
		i0=meta.find( eol,i1+1 )+2;
	}
	
	return keys;
}

wxString wxDeclInfo::getMetaValue( wxString key ){

	if( !meta.length() ) return {};
	
	wxString eol="~\n";

	key+="=";

	int i0=0;
	if( !meta.startsWith( key ) ){
		i0=meta.find( eol+key )+2;
		if( i0==1 ) return {};
	}
	
	i0+=key.length();

	int i1=meta.find( eol,i0 );
	if( i1==-1 ) return meta.slice( i0 );
	return meta.slice( i0,i1 );
}
