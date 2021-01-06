
#include <jni.h>

#include <wxwonkey.h>

namespace wxJNI{

	wxString JStringToString( JNIEnv *env,jstring jstr );
	
	jstring StringToJString( JNIEnv *env,wxString str );
	
	
	wxString GetStringField( JNIEnv *env,jobject obj,jfieldID fieldID );


	void CallVoidMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );
	
	wxBool CallBooleanMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );

	wxInt CallIntMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );
	
	wxFloat CallFloatMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );

	wxString CallStringMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );

	jobject CallObjectMethod( JNIEnv *env,jobject obj,jmethodID methodID,wxArray<wxVariant> args );


	void CallStaticVoidMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );
	
	wxBool CallStaticBooleanMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );

	wxInt CallStaticIntMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );
	
	wxFloat CallStaticFloatMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );

	wxString CallStaticStringMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );

	jobject CallStaticObjectMethod( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );
	

	jobject NewObject( JNIEnv *env,jclass clazz,jmethodID methodID,wxArray<wxVariant> args );
	

}
