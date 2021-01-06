
#ifndef WX_DECLINFO_R_H
#define WX_DECLINFO_R_H

#include "wxdeclinfo.h"

// ***** Global *****
//
template<class T> struct wxGlobalDeclInfo : public wxDeclInfo{

	T *ptr;
	
	wxGlobalDeclInfo( wxString name,T *ptr,wxString meta,bool isconst ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind=isconst ? "Const" : "Global";
		this->type=wxGetType<T>();
		this->flags=WX_DECL_GETTABLE|(isconst ? 0 : WX_DECL_SETTABLE);
	}
	
	wxVariant get( wxVariant instance ){
	
		return wxVariant( *ptr );
	}
	
	void set( wxVariant instance,wxVariant value ){
	
		*ptr=value.get<T>();
	}
};

template<class T> struct wxGlobalVarDeclInfo : public wxDeclInfo{

	wxGCVar<T> *ptr;
	
	wxGlobalVarDeclInfo( wxString name,wxGCVar<T> *ptr,wxString meta,bool isconst ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind=isconst ? "Const" : "Global";
		this->type=wxGetType<T>();
		this->flags=WX_DECL_GETTABLE|(isconst ? 0 : WX_DECL_SETTABLE);
	}
	
	wxVariant get( wxVariant instance ){
	
		return wxVariant( ptr->get() );
	}
	
	void set( wxVariant instance,wxVariant value ){
	
		*ptr=value.get<T*>();
	}
};


template<class T> wxDeclInfo *wxGlobalDecl( wxString name,T *ptr,wxString meta="" ){

	return new wxGlobalDeclInfo<T>( name,ptr,meta,false );
}

template<class T> wxDeclInfo *wxGlobalDecl( wxString name,wxGCVar<T> *ptr,wxString meta="" ){

	return new wxGlobalVarDeclInfo<T>( name,ptr,meta,false );
}

template<class T> wxDeclInfo *wxConstDecl( wxString name,T *ptr,wxString meta="" ){

	return new wxGlobalDeclInfo<T>( name,ptr,meta,true );
}

template<class T> wxDeclInfo *wxConstDecl( wxString name,wxGCVar<T> *ptr,wxString meta="" ){

	return new wxGlobalVarDeclInfo<T>( name,ptr,meta,true );
}

// ***** Field *****
//
template<class C,class T> struct wxFieldDeclInfo : public wxDeclInfo{

	T C::*ptr;
	
	wxFieldDeclInfo( wxString name,wxString meta,T C::*ptr ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Field";
		this->type=wxGetType<T>();
		this->flags=WX_DECL_GETTABLE|WX_DECL_SETTABLE;
	}
	
	wxVariant get( wxVariant instance ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		return wxVariant( p->*ptr );
	}
	
	void set( wxVariant instance,wxVariant value ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		p->*ptr=value.get<T>();
	}
};

template<class C,class T> struct wxFieldVarDeclInfo : public wxDeclInfo{

	wxGCVar<T> C::*ptr;
	
	wxFieldVarDeclInfo( wxString name,wxString meta,wxGCVar<T> C::*ptr ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Field";
		this->type=wxGetType<T*>();
		this->flags=WX_DECL_GETTABLE|WX_DECL_SETTABLE;
	}
	
	wxVariant get( wxVariant instance ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		return wxVariant( (p->*ptr).get() );
	}
	
	void set( wxVariant instance,wxVariant value ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		p->*ptr=value.get<T*>();
	}
};

template<class C,class T> wxDeclInfo *wxFieldDecl( wxString name,T C::*ptr,wxString meta="" ){

	return new wxFieldDeclInfo<C,T>( name,meta,ptr );
}

template<class C,class T> wxDeclInfo *wxFieldDecl( wxString name,wxGCVar<T> C::*ptr,wxString meta="" ){

	return new wxFieldVarDeclInfo<C,T>( name,meta,ptr );
}

// ***** Constructor *****
//
template<class C,class...A> struct wxCtorDeclInfo : public wxDeclInfo{

	wxCtorDeclInfo( wxString meta ){
		this->name="New";
		this->meta=meta;
		this->kind="Constructor";
		this->type=wxGetType<wxFunction<void(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> C *invoke( wxArray<wxVariant> params,detail::seq<I...> ){
	
		return wxGCNew<C>( params[I].get<A>()... );
	}
	
	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
		return wxVariant( invoke( params,detail::gen_seq<sizeof...(A)>{} ) );
	}
};

template<class C,class...A> wxDeclInfo *wxCtorDecl( wxString meta="" ){

	return new wxCtorDeclInfo<C,A...>( meta );
}

// ***** Method *****
//
template<class C,class R,class...A> struct wxMethodDeclInfo : public wxDeclInfo{

	R (C::*ptr)(A...);
	
	wxMethodDeclInfo( wxString name,wxString meta,R (C::*ptr)(A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Method";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( C *p,wxArray<wxVariant> params,detail::seq<I...> ){
	
		return (p->*ptr)( params[I].get<A>()... );
	}
	
	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		return wxVariant( invoke( p,params,detail::gen_seq<sizeof...(A)>{} ) );
	}
};

template<class C,class...A> struct wxMethodDeclInfo<C,void,A...> : public wxDeclInfo{

	typedef void R;

	R (C::*ptr)(A...);
	
	wxMethodDeclInfo( wxString name,wxString meta,R (C::*ptr)(A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Method";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( C *p,wxArray<wxVariant> params,detail::seq<I...> ){
	
		return (p->*ptr)( params[I].get<A>()... );
	}

	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		invoke( p,params,detail::gen_seq<sizeof...(A)>{} );
		
		return {};
	}
};

template<class C,class R,class...A> wxDeclInfo *wxMethodDecl( wxString name,R (C::*ptr)(A...),wxString meta="" ){

	return new wxMethodDeclInfo<C,R,A...>( name,meta,ptr );
}

// ***** Extension Method *****
//
template<class C,class R,class...A> struct wxExtMethodDeclInfo : public wxDeclInfo{

	R (*ptr)(C*,A...);
	
	wxExtMethodDeclInfo( wxString name,wxString meta,R (*ptr)(C*,A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Method";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( C *p,wxArray<wxVariant> params,detail::seq<I...> ){
	
		return ptr( p,params[I].get<A>()... );
	}
	
	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		return wxVariant( invoke( p,params,detail::gen_seq<sizeof...(A)>{} ) );
	}
};

template<class C,class...A> struct wxExtMethodDeclInfo<C,void,A...> : public wxDeclInfo{

	typedef void R;

	R (*ptr)(C*,A...);
	
	wxExtMethodDeclInfo( wxString name,wxString meta,R (*ptr)(C*,A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Method";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( C *p,wxArray<wxVariant> params,detail::seq<I...> ){
	
		return ptr( p,params[I].get<A>()... );
	}

	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		invoke( p,params,detail::gen_seq<sizeof...(A)>{} );
		
		return {};
	}
};

template<class C,class R,class...A> wxDeclInfo *wxExtMethodDecl( wxString name,R (*ptr)(C*,A...),wxString meta="" ){

	return new wxExtMethodDeclInfo<C,R,A...>( name,meta,ptr );
}

// ***** Property *****
//
template<class C,class T> struct wxPropertyDeclInfo : public wxDeclInfo{

	T (C::*getter)();
	
	void (C::*setter)(T);
	
	wxPropertyDeclInfo( wxString name,wxString meta,T(C::*getter)(),void(C::*setter)(T) ):getter( getter ),setter( setter ){
		this->name=name;
		this->meta=meta;
		this->kind="Property";
		this->type=wxGetType<T>();
		this->flags=(getter ? WX_DECL_GETTABLE : 0) | (setter ? WX_DECL_SETTABLE : 0);
	}
	
	wxVariant get( wxVariant instance ){
		if( !getter ) wxRuntimeError( "Property has not getter" );

//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		return wxVariant( (p->*getter)() );
	}
	
	void set( wxVariant instance,wxVariant value ){
		if( !setter ) wxRuntimeError( "Property has not setter" );
		
//		C *p=instance.get<C*>();
		C *p=instance.ref<C>();
		
		(p->*setter)( value.get<T>() );
	}
};

template<class C,class T> wxDeclInfo *wxPropertyDecl( wxString name,T(C::*getter)(),void(C::*setter)(T),wxString meta="" ){

	return new wxPropertyDeclInfo<C,T>( name,meta,getter,setter );
}

// ***** Extension Property *****
//
template<class C,class T> struct wxExtPropertyDeclInfo : public wxDeclInfo{

	T (*getter)(C*);
	
	void (*setter)(C*,T);
	
	wxExtPropertyDeclInfo( wxString name,wxString meta,T(*getter)(C*),void(*setter)(C*,T) ):getter( getter ),setter( setter ){
		this->name=name;
		this->meta=meta;
		this->kind="Property";
		this->type=wxGetType<T>();
		this->flags=(getter ? WX_DECL_GETTABLE : 0) | (setter ? WX_DECL_SETTABLE : 0);
	}
	
	wxVariant get( wxVariant instance ){
		if( !getter ) wxRuntimeError( "Property has no getter" );

		C *p=instance.ref<C>();
		
		return wxVariant( getter(p) );
	}
	
	void set( wxVariant instance,wxVariant value ){
		if( !setter ) wxRuntimeError( "Property has no setter" );
		
		C *p=instance.ref<C>();
		
		setter(p,value.get<T>() );
	}
};

template<class C,class T> wxDeclInfo *wxExtPropertyDecl( wxString name,T(*getter)(C*),void(*setter)(C*,T),wxString meta="" ){

	return new wxExtPropertyDeclInfo<C,T>( name,meta,getter,setter );
}

// ***** Function *****
//
template<class R,class...A> struct wxFunctionDeclInfo : public wxDeclInfo{

	R (*ptr)(A...);
	
	wxFunctionDeclInfo( wxString name,wxString meta,R (*ptr)(A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Function";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( wxArray<wxVariant> params,detail::seq<I...> ){
	
		return (*ptr)( params[I].get<A>()... );
	}
	
	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
		return wxVariant( invoke( params,detail::gen_seq<sizeof...(A)>{} ) );
	}
};

template<class...A> struct wxFunctionDeclInfo<void,A...> : public wxDeclInfo{

	typedef void R;

	R (*ptr)(A...);
	
	wxFunctionDeclInfo( wxString name,wxString meta,R (*ptr)(A...) ):ptr( ptr ){
		this->name=name;
		this->meta=meta;
		this->kind="Function";
		this->type=wxGetType<wxFunction<R(A...)>>();
		this->flags=WX_DECL_INVOKABLE;
	}
	
	template<int...I> R invoke( wxArray<wxVariant> params,detail::seq<I...> ){
	
		return (*ptr)( params[I].get<A>()... );
	}
	
	wxVariant invoke( wxVariant instance,wxArray<wxVariant> params ){
	
		invoke( params,detail::gen_seq<sizeof...(A)>{} );
		
		return {};
	}
};

template<class R,class...A> wxDeclInfo *wxFunctionDecl( wxString name,R (*ptr)(A...),wxString meta="" ){

	return new wxFunctionDeclInfo<R,A...>( name,meta,ptr );
}

// ***** Literal *****
//
template<class T> struct wxLiteralDeclInfo : public wxDeclInfo{

	T value;
	
	wxLiteralDeclInfo( wxString name,wxString meta,T value ):value( value ){
		this->name=name;
		this->meta=meta;
		this->kind="Const";
		this->type=wxGetType<T>();
		this->flags=WX_DECL_GETTABLE;
	}
	
	wxVariant get( wxVariant instance ){
	
		return wxVariant( value );
	}
};

template<class T> wxDeclInfo *wxLiteralDecl( wxString name,T value,wxString meta="" ){

	return new wxLiteralDeclInfo<T>( name,meta,value );
}

template<class...Ds> wxDeclInfo **wxMembers( Ds...ds ){

	int n=sizeof...(Ds);
	wxDeclInfo *ts[]={ ds...,0 };
	wxDeclInfo **ps=new wxDeclInfo*[n+1];
	for( int i=0;i<n;++i ) ps[i]=ts[i];
	ps[n]=0;
	
	return ps;
}

#endif
