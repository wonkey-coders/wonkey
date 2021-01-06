
#ifndef WX_OBJECT_H
#define WX_OBJECT_H

#ifdef WX_THREADS
#include "wxgc_mx.h"
#else
#include "wxgc.h"
#endif

//#include "wxstring.h"
#include "wxdebug.h"

struct wxObject : public wxGCNode{

	typedef wxObject *wx_object_type;

	wxObject(){
	
		wxGC::beginCtor( this );
	}
	
	virtual ~wxObject();

	//implemented in wxtypeinfo.h
	//	
	virtual wxTypeInfo *typeof()const;
	
	virtual const char *typeName()const;
	
	void *operator new( size_t size ){
	
		return wxGC::malloc( size );
	}
	
	//NOTE! We need this in case ctor throws an exception. delete never otherwise called...
	//
	void operator delete( void *p ){
	
		wxGC::endCtor( (wxObject*)(p) );
	}
};

struct wxThrowable : public wxObject{
};

struct wxInterface{

	typedef wxInterface *wx_object_type;

	virtual ~wxInterface();
};

struct wxNullCtor_t{
};

extern wxNullCtor_t wxNullCtor;

template<class T,class...A> T *wxGCNew( A...a ){
	T *p=new T( a... );
	wxGC::endCtor( p );
	return p;
}

template<class T,class R=typename T::wx_object_type> void wxGCMark( T *p ){
	wxGC::enqueue( dynamic_cast<wxObject*>( p ) );
}

template<class T,class C> T wx_object_cast( C *p ){
	return dynamic_cast<T>( p );
}

inline void wxDBAssertSelf( void *p ){
	wxDebugAssert( p,"Attempt to invoke method on null instance" );
}

inline wxString wxDBObjectValue( wxObject *p ){
	char buf[64];
	sprintf( buf,"@%p",p );
	return buf;
}

inline wxString wxDBInterfaceValue( wxInterface *p ){
	return wxDBObjectValue( dynamic_cast<wxObject*>( p ) );
}

template<class T> wxString wxDBStructValue( T *p ){
	char buf[64];
	sprintf( buf,"@%p:%p",p,&T::dbEmit );
	return buf;
}

inline wxString wxDBType( wxObject **p ){
	return "Object";
}

inline wxString wxDBValue( wxObject **p ){
	return wxDBObjectValue( *p );
}

template<class T> struct wxGCVar{

	public:
	
	T *_ptr;
	
	void enqueue(){
		wxGC::enqueue( dynamic_cast<wxGCNode*>( _ptr ) );
	}
	
	wxGCVar():_ptr( nullptr ){
	}
	
	wxGCVar( T *p ):_ptr( p ){
		enqueue();
	}
	
	wxGCVar( const wxGCVar &p ):_ptr( p._ptr ){
		enqueue();
	}
	
	wxGCVar &operator=( T *p ){
		_ptr=p;
		enqueue();
		return *this;
	}
	
	wxGCVar &operator=( const wxGCVar &p ){
		_ptr=p._ptr;
		enqueue();
		return *this;
	}
	void discard(){
		_ptr=nullptr;
	}
	
	T *get()const{
		return _ptr;
	}
	
	T *operator->()const{
		return _ptr;
	}
	
	operator T*()const{
		return _ptr;
	}
	
	T **operator&(){
		return &_ptr;
	}
};

template<class T,class C> T wx_object_cast( const wxGCVar<C> &v ){
	return dynamic_cast<T>( v._ptr );
}

template<class T> void wxGCMark( const wxGCVar<T> &v ){
	wxGCMark( v._ptr );
}

#endif
