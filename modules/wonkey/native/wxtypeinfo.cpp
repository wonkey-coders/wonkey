
#include "wxvariant.h"
#include "wxtypeinfo_r.h"
#include "wxdeclinfo.h"

namespace{

	wxClassTypeInfo *_classes;
}

#define WX_PRIM_GETTYPE( TYPE,ID ) wxTypeInfo *wxGetType( TYPE const& ){ \
	static wxPrimTypeInfo<TYPE> info( ID ); \
	return &info; \
}

WX_PRIM_GETTYPE( wxBool,"Bool" )
WX_PRIM_GETTYPE( wxByte,"Byte" )
WX_PRIM_GETTYPE( wxUByte,"UByte" )
WX_PRIM_GETTYPE( wxShort,"Short" )
WX_PRIM_GETTYPE( wxUShort,"UShort" )
WX_PRIM_GETTYPE( wxInt,"Int" )
WX_PRIM_GETTYPE( wxUInt,"UInt" )
WX_PRIM_GETTYPE( wxLong,"Long" )
WX_PRIM_GETTYPE( wxULong,"ULong" )
WX_PRIM_GETTYPE( wxFloat,"Float" )
WX_PRIM_GETTYPE( wxDouble,"Double" )
WX_PRIM_GETTYPE( wxString,"String" )
WX_PRIM_GETTYPE( wxCString,"CString" )
WX_PRIM_GETTYPE( wxVariant,"Variant" )

// ***** wxTypeInfo *****

wxString wxTypeInfo::toString(){
	return name;
}

wxTypeInfo *wxTypeInfo::pointeeType(){
	wxRuntimeError( "Type '"+name+"' is not a pointer type" );
	return 0; 
}
	
wxTypeInfo *wxTypeInfo::elementType(){
	wxRuntimeError( "Type '"+name+"' is not an array type" );
	return 0;
}
	
int wxTypeInfo::arrayRank(){
	wxRuntimeError( "Type '"+name+"' is not an array type" );
	return 0;
}
	
wxTypeInfo *wxTypeInfo::returnType(){
	wxRuntimeError( "Type '"+name+"' is not a function type" );
	return 0; 
}
	
wxArray<wxTypeInfo*> wxTypeInfo::paramTypes(){
	wxRuntimeError( "Type '"+name+"' is not a function type" );
	return {};
}
	
wxTypeInfo *wxTypeInfo::superType(){
	wxRuntimeError( "Type '"+name+"' is not a class type" );
	return 0;
}
	
wxArray<wxTypeInfo*> wxTypeInfo::interfaceTypes(){
	wxRuntimeError( "Type '"+name+"' is not a class or interface type" );
	return {};
}
	
wxBool wxTypeInfo::extendsType( wxTypeInfo *type ){
	return this==type;
}
	
wxArray<wxDeclInfo*> wxTypeInfo::getDecls(){
	wxRuntimeError( "Type '"+name+"' is not a class or interface type" );
	return {};
}

wxVariant wxTypeInfo::makeEnum( int ){
	wxRuntimeError( "Type '"+name+"' is not an enum type" );
	return {};
}

int wxTypeInfo::getEnum( wxVariant ){
	wxRuntimeError( "Type '"+name+"' is not an enum type" );
	return {};
}

wxVariant wxTypeInfo::nullValue(){
	return {};
}

wxVariant wxTypeInfo::newArray( int length ){
	return {};
}

wxDeclInfo *wxTypeInfo::getDecl( wxString name ){

	wxArray<wxDeclInfo*> decls=getDecls();
	wxDeclInfo *found=0;

	for( int i=0;i<decls.length();++i ){
		wxDeclInfo *decl=decls[i];
		if( decl->name!=name ) continue;
		if( found ) return 0;
		found=decl;
	}

	return found;
}

wxArray<wxDeclInfo*> wxTypeInfo::getDecls( wxString name ){

	wxArray<wxDeclInfo*> decls=getDecls();

	int n=0;
	for( int i=0;i<decls.length();++i ){
		if( decls[i]->name==name ) ++n;
	}
	if( !n ) return {};
	
	wxArray<wxDeclInfo*> rdecls( n );
	
	int j=0;
	for( int i=0;i<decls.length();++i ){
		if( decls[i]->name==name ) rdecls[j++]=decls[i];
	}
	return rdecls;
}

wxDeclInfo *wxTypeInfo::getDecl( wxString name,wxTypeInfo *type ){

	wxArray<wxDeclInfo*> decls=getDecls();

	for( int i=0;i<decls.length();++i ){
		wxDeclInfo *decl=decls[i];
		if( decl->name==name && decl->type==type ) return decl;
	}
	
	return 0;
}

wxTypeInfo *wxTypeInfo::getType( wxString cname ){

	for( wxClassTypeInfo *c=_classes;c;c=c->_succ ){
		if( c->name==cname ) return c;
	}
	
	return 0;
}

wxArray<wxTypeInfo*> wxTypeInfo::getTypes(){

	int n=0;
	for( wxClassTypeInfo *c=_classes;c;c=c->_succ ) ++n;
	
	wxArray<wxTypeInfo*> types( n );
	
	int i=0;
	for( wxClassTypeInfo *c=_classes;c;c=c->_succ ) types[i++]=c;
	
	return types;
}


// ***** wxUnknownTypeInfo *****

wxUnknownTypeInfo::wxUnknownTypeInfo( const char *name ){
	this->name=name ? wxString( name ) : WX_T("Unknown@")+wxString( wxLong( this ) );
	this->kind="Unknown";
}

// ***** wxVoidTypeInfo *****

wxVoidTypeInfo wxVoidTypeInfo::instance;

wxVoidTypeInfo::wxVoidTypeInfo(){
	this->name="Void";
	this->kind="Void";
}


// ***** wxObjectTypeInfo *****

wxObjectTypeInfo wxObjectTypeInfo::instance;

wxObjectTypeInfo::wxObjectTypeInfo(){
	this->name="Object";
	this->kind="Class";
}
	
wxTypeInfo *wxObjectTypeInfo::superType(){
	return 0;
}
	
wxBool wxObjectTypeInfo::extendsType( wxTypeInfo *type ){
	return type==&instance;
}
	
wxArray<wxDeclInfo*> wxObjectTypeInfo::getDecls(){
	return {};
}

wxTypeInfo *wxObject::typeof()const{

	return &wxObjectTypeInfo::instance;
}


// ***** wxClassDecls *****

wxClassDecls::wxClassDecls( wxClassTypeInfo *classType ){
	_succ=classType->_decls;
	classType->_decls=this;
}

wxDeclInfo **wxClassDecls::decls(){

	if( !_decls ){
		_decls=initDecls();
		wxDeclInfo **p=_decls;
		while( *p ) ++p;
		_numDecls=p-_decls;
	}
	
	return _decls;
}

int wxClassDecls::numDecls(){
	if( !_decls ) decls();
	return _numDecls;
}

// ***** wxClassTypeInfo *****

wxClassTypeInfo::wxClassTypeInfo( wxString name,wxString kind ){
//	printf( "ClassTypeInfo:%s\n",name.c_str() );
	this->name=name;
	this->kind=kind;
	_succ=_classes;
	_classes=this;
}

wxTypeInfo *wxClassTypeInfo::superType(){
	return 0;
}

wxArray<wxTypeInfo*> wxClassTypeInfo::interfaceTypes(){
	return {};
}

wxBool wxClassTypeInfo::extendsType( wxTypeInfo *type ){

	if( type==this ) return true;
	
	wxArray<wxTypeInfo*> ifaces=interfaceTypes();
	
	for( int i=0;i<ifaces.length();++i ){

		if( ifaces[i]->extendsType( type ) ) return true;
	}
	
	if( wxTypeInfo *super=superType() ) return super->extendsType( type );
	
	return false;
}

wxArray<wxDeclInfo*> wxClassTypeInfo::getDecls(){

	int n=0;
	for( wxClassDecls *m=_decls;m;m=m->_succ ) n+=m->numDecls();
	
	wxArray<wxDeclInfo*> rdecls( n );
	
	int i=0;
	for( wxClassDecls *m=_decls;m;m=m->_succ ){
		wxDeclInfo **decls=m->decls();
		int n=m->numDecls();
		for( int j=0;j<n;++j ) rdecls[i++]=decls[j];
	}
	
	return rdecls;
}

wxClassTypeInfo *wxClassTypeInfo::getNamespace( wxString name ){

	for( wxClassTypeInfo *nmspace=_classes;nmspace;nmspace=nmspace->_succ ){
		if( nmspace->name==name ) return nmspace;
	}
	
	wxClassTypeInfo *nmspace=new wxClassTypeInfo( name,"Namespace" );
	return nmspace;
}

// ***** EnumTypeInfo *****

