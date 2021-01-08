
#ifndef WX_VARIANT_H
#define WX_VARIANT_H

#include "wxtypeinfo.h"

struct wxVariant{
	
	template<class T> static wxObject *_getObject( T const& ){ wxRuntimeError( "Variant cast failed" );return 0; }
	template<class T,class R=typename T::wx_object_type> static wxObject *_getObject( T *p ){ return dynamic_cast<wxObject*>( p ); }
	
	template<class T> static int _getArrayLength( T const& ){ wxRuntimeError( "Variant is not an array" );return 0; }
	template<class T> static wxVariant _getArrayElement( T const&,int index ){ wxRuntimeError( "Variant is not an array" );return {}; }
	template<class T> static void _setArrayElement( T const&,int index,wxVariant value ){ wxRuntimeError( "Variant is not an array" ); }
	
	template<class T,int D> static int _getArrayLength( wxArray<T,D> v ){ return v.length(); }
	template<class T,int D> static wxVariant _getArrayElement( wxArray<T,D> v,int index );
	template<class T,int D> static void _setArrayElement( wxArray<T,D> v,int index,wxVariant value );
	template<class T,int D> static void _setArrayElement( wxArray<wxGCVar<T>,D> v,int index,wxVariant value );
 
	struct RepBase{
	
		int _refs=1;
	
		virtual ~RepBase(){
		}
		
		virtual void gcMark(){
		}
		
		virtual wxTypeInfo *getType(){
			return 0;
		}
		
		virtual wxObject *getObject(){
			return 0;
		}
		
		virtual int getArrayLength(){ 
			return 0; 
		}
		
		virtual wxVariant getArrayElement( int index ){
			return {}; 
		}
		
		virtual void setArrayElement( int index,wxVariant value ){
		}
		
		virtual wxVariant invoke( wxArray<wxVariant> params ){
			wxRuntimeError( "Variant is not invokable" );
			return {};
		}
		
	};
	
	template<class T> struct Rep : public RepBase{
	
		T value;
		
		Rep( const T &value ):value( value ){
		}
		
		virtual void gcMark(){
			wxGCMark( value );
		}
		
		virtual wxTypeInfo *getType(){
			return wxGetType<T>();
		}
		
		virtual wxObject *getObject(){
			return _getObject( value );
		}
		
		virtual int getArrayLength(){
			return _getArrayLength( value );
		}
		
		virtual wxVariant getArrayElement( int index ){
			return _getArrayElement( value,index );
		}
		
		virtual void setArrayElement( int index,wxVariant evalue ){
			_setArrayElement( value,index,evalue );
		}

	};
	
	static RepBase _null;
	
	RepBase *_rep;
	
	void retain()const{
		++_rep->_refs;
	}
	
	void release(){
		if( !--_rep->_refs && _rep!=&_null ) delete _rep;
	}
	
	// ***** public *****
	
	wxVariant():_rep( &_null ){
	}
	
	wxVariant( const wxVariant &v ):_rep( v._rep ){
		retain();
	}
	
	template<class T> explicit wxVariant( const T &t ):_rep( new Rep<T>( t ) ){
	}
	
	template<class T> explicit wxVariant( const wxGCVar<T> &t ):_rep( new Rep<T*>( t.get() ) ){
	}
	
	~wxVariant(){
		release();
	}
	
	wxVariant &operator=( const wxVariant &v ){
		v.retain();
		release();
		_rep=v._rep;
		return *this;
	}
	
	template<class T,class R=typename T::wx_object_type> T *_get( T* const& )const{
		wxObject *obj=_rep->getObject();
		return dynamic_cast<T*>( obj );
	}
	
	template<class T> T _get( T const& )const{
		wxRuntimeError( "Variant cast failed" );
		return {};
	}
	
	template<class T> T get()const{
		Rep<T> *r=dynamic_cast<Rep<T>*>( _rep );
		if( !r ) return _get( *(T*)0 );
		return r->value;
	}
	
	template<class T,class R=typename T::wx_object_type> T *_ref( T** )const{
		return get<T*>();
	}
	
	template<class T> T *_ref( T* )const{
		Rep<T> *r=dynamic_cast<Rep<T>*>( _rep );
		if( !r ) wxRuntimeError( "Variant cast failed" );
		return &r->value;
	}
	
	template<class T> T *ref()const{
		return _ref<T>( 0 );
	}

	wxTypeInfo *getType()const{
		return _rep->getType();
	}
	
	wxTypeInfo *getDynamicType()const{
		if( wxObject *obj=_rep->getObject() ) return obj->typeof();
		return _rep->getType();
	}
	
	operator bool()const{
		return _rep!=&_null;
	}
	
	int enumValue()const{
		return getType()->getEnum( *this );
	}

	int getArrayLength(){
		return _rep->getArrayLength();
	}
	
	wxVariant getArrayElement( int index ){
		return _rep->getArrayElement( index );
	}
	
	void setArrayElement( int index,wxVariant value ){
		_rep->setArrayElement( index,value );
	}
};

inline void wxGCMark( const wxVariant &v ){
	v._rep->gcMark();
}

inline int wxCompare( const wxVariant &x,const wxVariant &y ){
	return y._rep>x._rep ? -1 : x._rep>y._rep;
}

template<class T,int D> wxVariant wxVariant::_getArrayElement( wxArray<T,D> v,int index ){
	return wxVariant( v[index] );
}

template<class T,int D> void wxVariant::_setArrayElement( wxArray<T,D> v,int index,wxVariant value ){
	v[index]=value.get<T>();
}

template<class T,int D> void wxVariant::_setArrayElement( wxArray<wxGCVar<T>,D> v,int index,wxVariant value ){
	v[index]=value.get<T*>();
}

#endif
