
#ifndef WX_TYPEINFO_T_H
#define WX_TYPEINFO_T_H

#include "wxtypeinfo.h"

template<class T> struct wxBaseTypeInfo : public wxTypeInfo{

	wxVariant nullValue(){
		return wxVariant( T{} );
	}

	wxVariant newArray( int length ){
		return wxVariant( wxArray<T>( length ) );
	}
};

template<class T> struct wxPrimTypeInfo : public wxBaseTypeInfo<T>{

	wxPrimTypeInfo( wxString name ){
		this->name=name;
		this->kind="Primitive";
	}
/*
	wxVariant nullValue(){
		return wxVariant( T{} );
	}

	wxVariant newArray( int length ){
		return wxVariant( wxArray<T>{ length } );
	}
*/
};

template<class T> struct wxPointerTypeInfo : public wxBaseTypeInfo<T*>{

	wxPointerTypeInfo(){
		this->name=wxGetType<T>()->name+" Ptr";
		this->kind="Pointer";
	}

	wxTypeInfo *pointeeType(){
		return wxGetType<T>();
	}
/*	
	wxVariant nullValue(){
		return wxVariant( (T*)0 );
	}
	
	wxVariant newArray( int length ){
		return wxVariant( wxArray<T*>{ length } );
	}
*/
};

template<class T,int D> struct wxArrayTypeInfo : public wxTypeInfo{	//wxBaseTypeInfo<wxArray<T,D>>{

	wxArrayTypeInfo(){
		this->name=wxGetType<T>()->name+"["+WX_T(",").dup(D-1)+"]";
		this->kind="Array";
	}
	
	wxTypeInfo *elementType(){
		return wxGetType<T>();
	}
	
	int arrayRank(){
		return D;
	}

	wxVariant nullValue(){
		return wxVariant( wxArray<T,D>{} );
	}
/*
	wxVariant newArray( int length )
		return wxVariant( wxArray<T>{ length } );
	}
*/
};

template<class R,class...A> struct wxFunctionTypeInfo : public wxTypeInfo{	//wxBaseTypeInfo<wxFunction<R(A...)>>{

	wxFunctionTypeInfo(){
		this->name=wxGetType<R>()->name+"("+WX_T(",").join( wxArray<wxString>( { wxGetType<A>()->name... },int(sizeof...(A)) ) )+")";
		this->kind="Function";
	}
	
	wxTypeInfo *returnType(){
		return wxGetType<R>();
	}
	
	wxArray<wxTypeInfo*> paramTypes(){
		return wxArray<wxTypeInfo*>( { wxGetType<A>()... },int(sizeof...(A)) );
	}

	wxVariant nullValue(){
		return wxVariant( wxFunction<R(A...)>{} );
	}
/*
	wxVariant newArray( int length ){
		return wxVariant( wxArray<wxFunction<R(A...)>>{ length } );
	}
*/
};

template<class...A> struct wxFunctionTypeInfo<void,A...> : public wxTypeInfo{	//wxBaseTypeInfo<wxFunction<void(A...)>>{

	wxFunctionTypeInfo(){
		this->name=WX_T("Void(")+WX_T(",").join( wxArray<wxString>( { wxGetType<A>()->name... },int(sizeof...(A)) ) )+")";
		this->kind="Function";
	}
	
	wxTypeInfo *returnType(){
		return &wxVoidTypeInfo::instance;
	}
	
	wxArray<wxTypeInfo*> paramTypes(){
		return wxArray<wxTypeInfo*>( { wxGetType<A>()... },int(sizeof...(A)) );
	}

	wxVariant nullValue(){
		return wxVariant( wxFunction<void(A...)>{} );
	}
/*
	wxVariant newArray( int length ){
		return wxVariant( wxArray<wxFunction<void(A...)>>{ length } );
	}	
*/
};

inline wxTypeInfo *wxGetType( wxObject* const& ){
	return &wxObjectTypeInfo::instance;
}

template<class T> wxTypeInfo *wxGetUnknownType( const char *name=0 ){
 	static wxUnknownTypeInfo info( name );
	
	return &info;
}

template<class T> wxTypeInfo *wxGetType( T const& ){
	return wxGetUnknownType<T>();
}

template<class T> wxTypeInfo *wxGetType( T* const& ){
	static wxPointerTypeInfo<T> info;
	
	return &info;
}

template<class T,int D> wxTypeInfo *wxGetType( wxArray<T,D> const& ){
	static wxArrayTypeInfo<T,D> info;
	
	return &info;
}

template<class R,class...A> wxTypeInfo *wxGetFuncType(){
	static wxFunctionTypeInfo<R,A...> info;
	
	return &info;
}

template<class R,class...A> wxTypeInfo *wxGetType( R(*)(A...) ){
	return wxGetFuncType<R,A...>();
}

template<class R,class...A> wxTypeInfo *wxGetType( wxFunction<R(A...)> const& ){
	return wxGetFuncType<R,A...>();
}

template<class T> wxTypeInfo *wxGetType( wxGCVar<T> const& ){
	return wxGetType<T*>();
}

template<> inline wxTypeInfo *wxGetType<void>(){
	return &wxVoidTypeInfo::instance;
}

#endif
