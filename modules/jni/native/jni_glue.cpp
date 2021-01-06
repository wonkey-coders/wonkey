
#include "jni_glue.h"

namespace wxJNI{

	//64 params max
	const int MAX_LOCAL_REFS=64;

	jobject local_refs[MAX_LOCAL_REFS];
	
	int num_local_refs=0;
	
	void AddLocalRef( jobject jobj ){
	
		if( num_local_refs==MAX_LOCAL_REFS ) return;
	
		local_refs[num_local_refs++]=jobj;
	}
	
	void DeleteLocalRefs( JNIEnv *env ){
	
		while( num_local_refs ){
			
			jobject jobj=local_refs[--num_local_refs];
			
			env->DeleteLocalRef( jobj );
		}
	}
	
	// ***** Utility *****

	wxString JStringToString( JNIEnv *env,jstring jstr ){
	
		if( !jstr ) return "";
	
		const char *cstr=env->GetStringUTFChars( jstr,0 );
		
		wxString str=wxString::fromCString( cstr );
		
		env->ReleaseStringUTFChars( jstr,cstr );
		
		return str;
	}
	
	jstring StringToJString( JNIEnv *env,wxString str ){
	
		int n=str.utf8Length()+1;
		
		char *buf=new char[n];
		
		str.toCString( buf,n );
		
		jstring jstr=env->NewStringUTF( buf );
		
		return jstr;
	}
	
	jvalue *makeArgs( JNIEnv *env,wxArray<wxVariant> args ){
	
		jvalue *jargs=new jvalue[args.length()];
		
		memset( jargs,0,sizeof( jvalue ) * args.length() );
		
		jvalue *jarg=jargs;
		
		for( int i=0;i<args.length();++i ){
		
			wxVariant arg=args[i];
			
			wxTypeInfo *type=arg.getType();
			
			if( type==wxGetType<wxBool>() ){
			
				wxBool val=arg.get<wxBool>();
				
				jarg->z=val;
				
			}else if( type==wxGetType<wxInt>() ){
			
				wxInt val=arg.get<wxInt>();
				
				jarg->i=val;
			
			}else if( type==wxGetType<wxFloat>() ){
			
				wxFloat val=arg.get<wxFloat>();
				
				jarg->f=val;
			
			}else if( type==wxGetType<wxDouble>() ){
			
				wxDouble val=arg.get<wxDouble>();
				
				jarg->d=val;
			
			}else if( type==wxGetType<wxString>() ){
			
				wxString str=arg.get<wxString>();
				
				jstring jstr=StringToJString( env,str );
				
				AddLocalRef( (jobject)jstr );
				
				jarg->l=jstr;

			}else if( type==wxGetType<jobject>() ){
			
				jobject jobj=arg.get<jobject>();
			
				jarg->l=jobj;
/*				
			}else if( type==wxGetType<wxArray<wxBool>>() ){
			
				wxArray<wxBool> arr=arg.get<wxArray<wxBool>>();
				
				jbooleanArray jarr=env->NewBooleanArray( arr.length() );
				
				jboolean *jdata=env->GetBooleanArrayElements( jarr,0 );
				
				memcpy( jdata,arr.data(),arr.length()*sizeof(wxBool) );
				
				env->ReleaseBooleanArrayElements( jarr,jdata,0 );
				
				jarg->l=(jobject)jarr;
				
			}else if( type==wxGetType<wxArray<wxInt>>() ){

				wxArray<wxInt> arr=arg.get<wxArray<wxInt>>();
				
				jintArray jarr=env->NewIntArray( arr.length() );
				
				jint *jdata=env->GetIntArrayElements( jarr,0 );
				
				memcpy( jdata,arr.data(),arr.length()*sizeof(wxInt) );
				
				env->ReleaseIntArrayElements( jarr,jdata,0 );
				
				jarg->l=(jobject)jarr;
			
			}else if( type==wxGetType<wxArray<jobject>>() ){
			
			}else if( type==wxGetType<wxArray<wxString>>() ){
*/			
			}else{
			
				wxRuntimeError( "Can't evaluate JNI method param of typ:"+type->toString() );
			}
			
			++jarg;
		}
		
		return jargs;
	}
	
	// ***** Instance fields *****
	
	wxString GetStringField( JNIEnv *env,jobject obj,jfieldID fieldID ){
	
		jstring jstr=(jstring)env->GetObjectField( obj,fieldID );
		
		wxString r=JStringToString( env,jstr );
		
		env->DeleteLocalRef( jstr );
		
		return r;
	}
	
	// ***** Static fields *****

	wxString GetStaticStringField( JNIEnv *env,jclass clazz,jfieldID fieldID ){
	
		jstring jstr=(jstring)env->GetStaticObjectField( clazz,fieldID );
		
		wxString r=JStringToString( env,jstr );
		
		env->DeleteLocalRef( jstr );
		
		return r;
	}
	
	// ***** Instance methods *****

	void CallVoidMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		env->CallVoidMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
	}

	wxBool CallBooleanMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxBool r=env->CallBooleanMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	wxInt CallIntMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxInt r=env->CallIntMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	wxFloat CallFloatMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxFloat r=env->CallFloatMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	wxDouble CallDoubleMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxDouble r=env->CallDoubleMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	wxString CallStringMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		jstring jstr=(jstring)env->CallObjectMethodA( obj,methodID,jargs );
		
		wxString r=JStringToString( env,jstr );
		
		env->DeleteLocalRef( jstr );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	jobject CallObjectMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		jobject r=env->CallObjectMethodA( obj,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	// ***** Static methods *****

	void CallStaticVoidMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		env->CallStaticVoidMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
	}

	wxBool CallStaticBooleanMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxBool r=env->CallStaticBooleanMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	wxInt CallStaticIntMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxInt r=env->CallStaticIntMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}

	wxFloat CallStaticFloatMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxFloat r=env->CallStaticFloatMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	wxDouble CallStaticDoubleMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		wxDouble r=env->CallStaticDoubleMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	wxString CallStaticStringMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );

		jstring jstr=(jstring)env->CallStaticObjectMethodA( clazz,methodID,jargs );
		
		wxString r=JStringToString( env,jstr );
		
		env->DeleteLocalRef( jstr );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	jobject CallStaticObjectMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){
		
		jvalue *jargs=makeArgs( env,args );
		
		jobject r=env->CallStaticObjectMethodA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
	// ***** ctors *****
	
	jobject NewObject( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args ){

		jvalue *jargs=makeArgs( env,args );
		
		jobject r=env->NewObjectA( clazz,methodID,jargs );
		
		DeleteLocalRefs( env );
		
		delete[] jargs;
		
		return r;
	}
	
}
