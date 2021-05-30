
#ifndef WX_DEBUG_H
#define WX_DEBUG_H

#include "wxstring.h"

struct wxDBFiber;
struct wxDBFrame;
struct wxDBVarType;
struct wxDBVar;

inline wxString wxDBType( const void *p ){ return "Void"; }
inline wxString wxDBType( wxBool *p ){ return "Bool"; }
inline wxString wxDBType( wxByte *p ){ return "Byte"; }
inline wxString wxDBType( wxUByte *p ){ return "UByte"; }
inline wxString wxDBType( wxShort *p ){ return "Short"; }
inline wxString wxDBType( wxUShort *p ){ return "UShort"; }
inline wxString wxDBType( wxInt *p ){ return "Int"; }
inline wxString wxDBType( wxUInt *p ){ return "UInt"; }
inline wxString wxDBType( wxLong *p ){ return "Long"; }
inline wxString wxDBType( wxULong *p ){ return "ULong"; }
inline wxString wxDBType( wxFloat *p ){ return "Float"; }
inline wxString wxDBType( wxDouble *p ){ return "Double"; }
inline wxString wxDBType( wxString *p ){ return "String"; }

inline wxString wxDBValue( void *p ){ return wxString( wxULong(p) ); } // return "?????"
inline wxString wxDBValue( wxBool *p ){ return *p ? "True" : "False"; }
inline wxString wxDBValue( wxByte *p ){ return wxString(*p); }
inline wxString wxDBValue( wxUByte *p ){ return wxString(*p); }
inline wxString wxDBValue( wxShort *p ){ return wxString(*p); }
inline wxString wxDBValue( wxUShort *p ){ return wxString(*p); }
inline wxString wxDBValue( wxInt *p ){ return wxString(*p); }
inline wxString wxDBValue( wxUInt *p ){ return wxString(*p); }
inline wxString wxDBValue( wxLong *p ){ return wxString(*p); }
inline wxString wxDBValue( wxULong *p ){ return wxString(*p); }
inline wxString wxDBValue( wxFloat *p ){ return wxString(*p); }
inline wxString wxDBValue( wxDouble *p ){ return wxString(*p); }
extern wxString wxDBValue( wxString *p );

template<class R,class...A> wxString wxDBType( R(*)(A...) ){ return "Extern?(?)"; }
template<class R,class...A> wxString wxDBValue( R(*)(A...) ){ return "?"; }

template<class T> wxString wxDBType(){
	return wxDBType( (T*)0 );
}

template<class T> wxString wxDBType( wxGCVar<T> *p ){ return wxDBType<T*>(); }
template<class T> wxString wxDBValue( wxGCVar<T> *p ){ T *t=p->get();return t ? wxDBValue( &t ) : "Null"; }

template<class T> wxString wxDBType( T **p ){ return wxDBType<T>()+" Ptr"; }
template<class T> wxString wxDBValue( T **p ){ char buf[64];sprintf( buf,"$%p",*p );return buf; }

struct wxDBVarType{
	virtual wxString type()=0;
	virtual wxString value( void *p )=0;
};

template<class T> struct wxDBVarType_t : public wxDBVarType{

	wxString type(){
		return wxDBType( (T*)0 );
	}
	
	wxString value( void *p ){
		return wxDBValue( (T*)p );
	}
	
	static wxDBVarType_t info;
};

template<class T> wxDBVarType_t<T> wxDBVarType_t<T>::info;

struct wxDBVar{

	const char *name;
	wxDBVarType *type;
	void *var;
};

struct wxDBContext{

	wxDBFrame *frames=nullptr;
	wxDBVar *localsBuf=nullptr;
	wxDBVar *locals=nullptr;
	int stepMode=0;
	int stopped=0;

	~wxDBContext();
	
	void init();
};

namespace wxDB{

#ifdef WX_THREADS	
	extern std::atomic_int nextSeq;
	extern thread_local wxDBContext *currentContext;
#else
	extern int nextSeq;
	extern wxDBContext *currentContext;
#endif
	extern wxDBContext mainContext;
	
	void init();
	void stop();
	void stopped();
	void error( wxString err );
	wxArray<wxString> stack();
	void emitStack();
}

struct wxDBBlock{
	wxDBVar *locals;
    wxDBBlock(){
        if(!wxDB::currentContext) return;
	    locals = wxDB::currentContext->locals;
		if( wxDB::currentContext->stepMode=='l' ) --wxDB::currentContext->stopped;
	}
	~wxDBBlock(){
        if(!wxDB::currentContext) return;
		if( wxDB::currentContext->stepMode=='l' ) ++wxDB::currentContext->stopped;
		wxDB::currentContext->locals=locals;
	}
};

struct wxDBFrame : public wxDBBlock{
	wxDBFrame *succ;
	const char *decl;
	const char *srcFile;
	int srcPos;
	int seq;

	wxDBFrame( const char *decl,const char *srcFile ):decl( decl ),srcFile( srcFile ),seq( ++wxDB::nextSeq ){
        if(!wxDB::currentContext) return;
        succ = wxDB::currentContext->frames;
		wxDB::currentContext->frames=this;
		if( wxDB::currentContext->stepMode=='s' ) --wxDB::currentContext->stopped;
	}
	
	~wxDBFrame(){
        if(!wxDB::currentContext) return;
		if( wxDB::currentContext->stepMode=='s' ) ++wxDB::currentContext->stopped;
		wxDB::currentContext->frames=succ;
        if(wxDB::currentContext != &wxDB::mainContext) wxDB::currentContext=nullptr;
	}
};

struct wxDBLoop : public wxDBBlock{
	wxDBLoop(){
	}
	~wxDBLoop(){
	}
};

inline void wxDBStmt( int srcPos ){
    if(!wxDB::currentContext) return;
    if(wxDB::currentContext->frames) {
        wxDB::currentContext->frames->srcPos=srcPos;
    }
	if( wxDB::currentContext->stopped>0 ) wxDB::stopped();
}

template<class T> void wxDBEmit( const char *name,T *var ){
	wxDBVarType *type=&wxDBVarType_t<T>::info;
	puts( (WX_T( name )+":"+type->type()+"="+type->value( var )).c_str() );
}

template<class T> void wxDBEmit( const char *name,wxGCVar<T> *p ){
	T *var=p->get();return wxDBEmit( name,&var );
}

template<class T> void wxDBLocal( const char *name,T *var ){
    if(!wxDB::currentContext) return;
    if(wxDB::currentContext->locals) {
        wxDB::currentContext->locals->name=name;
        wxDB::currentContext->locals->type=&wxDBVarType_t<T>::info;
        wxDB::currentContext->locals->var=var;
        ++wxDB::currentContext->locals;
    }
}

#endif
