
#ifndef WX_TYPEINFO_R_H
#define WX_TYPEINFO_R_H

#include "wxtypeinfo_t.h"

struct wxClassTypeInfo;

struct wxClassDecls{

	wxClassDecls *_succ;
	wxDeclInfo **_decls=0;
	int _numDecls=0;

	wxClassDecls( wxClassTypeInfo *classType );
	
	wxDeclInfo **decls();
	
	int numDecls();
	
	virtual wxDeclInfo **initDecls(){
		return 0;
	}
};

struct wxClassTypeInfo : public wxTypeInfo{

	wxClassTypeInfo *_succ=0;
	wxClassDecls *_decls=0;
	
	wxClassTypeInfo( wxString name,wxString kind );
	
	wxTypeInfo *superType();
	
	wxArray<wxTypeInfo*> interfaceTypes();
	
	wxBool extendsType( wxTypeInfo *type );
	
	wxArray<wxDeclInfo*> getDecls();
	
	wxString toString(){
		return kind+" "+name;
	}
	
	static wxClassTypeInfo *getNamespace( wxString name );
};

struct wxEnumTypeInfo : public wxClassTypeInfo{
	
	wxEnumTypeInfo( wxString name ):wxClassTypeInfo( name,"Enum" ){
	}
};

#endif

