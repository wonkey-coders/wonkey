
#ifndef WX_TYPEINFO_H
#define WX_TYPEINFO_H

#include "wxassert.h"
#include "wxobject.h"
#include "wxarray.h"
#include "wxfunction.h"

//struct wxClassTypeInfo;

struct wxTypeInfo{

	wxString name;
	wxString kind;
	
	wxString getName(){
		return name;
	}
	
	wxString getKind(){
		return kind;
	}
	
	virtual wxString toString();

	virtual wxTypeInfo *pointeeType();
	
	virtual wxTypeInfo *elementType();
	
	virtual int arrayRank();
	
	virtual wxTypeInfo *returnType();
	
	virtual wxArray<wxTypeInfo*> paramTypes();
	
	virtual wxTypeInfo *superType();
	
	virtual wxArray<wxTypeInfo*> interfaceTypes();
	
	virtual wxBool extendsType( wxTypeInfo *type );
	
	virtual wxArray<wxDeclInfo*> getDecls();
	
	virtual wxVariant makeEnum( int value );
	
	virtual int getEnum( wxVariant );
	
	virtual wxVariant nullValue();

	virtual wxVariant newArray( int length );
	
	wxDeclInfo *getDecl( wxString name );
	
	wxDeclInfo *getDecl( wxString name,wxTypeInfo *type );
	
	wxArray<wxDeclInfo*> getDecls( wxString name );
	
	static wxTypeInfo *getType( wxString cname );
	
	static wxArray<wxTypeInfo*> getTypes();
};

#define WX_GETTYPE_DECL( TYPE ) wxTypeInfo *wxGetType( TYPE const& );

WX_GETTYPE_DECL( wxBool )
WX_GETTYPE_DECL( wxByte )
WX_GETTYPE_DECL( wxUByte )
WX_GETTYPE_DECL( wxShort )
WX_GETTYPE_DECL( wxUShort )
WX_GETTYPE_DECL( wxInt )
WX_GETTYPE_DECL( wxUInt )
WX_GETTYPE_DECL( wxLong )
WX_GETTYPE_DECL( wxULong )
WX_GETTYPE_DECL( wxFloat )
WX_GETTYPE_DECL( wxDouble )
WX_GETTYPE_DECL( wxString )
WX_GETTYPE_DECL( wxCString )
WX_GETTYPE_DECL( wxVariant )

template<class T> wxTypeInfo *wxGetType( T* const& );

template<class T> wxTypeInfo *wxGetType(){

	return wxGetType( *(T*)0 );
}

struct wxUnknownTypeInfo : public wxTypeInfo{
	
	wxUnknownTypeInfo( const char *name );
};

struct wxVoidTypeInfo : public wxTypeInfo{

	static wxVoidTypeInfo instance;

	wxVoidTypeInfo();
};

struct wxObjectTypeInfo : public wxTypeInfo{

	static wxObjectTypeInfo instance;

	wxObjectTypeInfo();
	
	wxTypeInfo *superType();
	
	wxBool extendsType( wxTypeInfo *type );
	
	wxArray<wxDeclInfo*> getDecls();
};

#endif
