
Namespace android

#If __TARGET__="android"

#Import "<libc>"
#Import "<sdl2>"
#Import "<jni>"

#Import "<sdl2/SDL/src/core/android/SDL_android.h>"
'#Import "<asset_manager.h>"
'#Import "<SDL.h>"

Extern Private

'this is actually in SDL...
Function Android_JNI_GetAssetManager:Void Ptr()

Extern

Const AASSET_MODE_UNKNOWN:Int	'0
Const AASSET_MODE_RANDOM:Int	'1
Const AASSET_MODE_STREAMING:Int	'2
Const AASSET_MODE_BUFFER:Int	'3
 
Class AAssetManager Extends Void
End

Class AAssetDir Extends Void
End

Class AAsset Extends Void
End

Function AAssetManager_open:AAsset( mgr:AAssetManager,filename:CString,mode:Int )
Function AAssetManager_openDir:AAssetDir( mgr:AAssetManager,dirName:CString )
	
Function AAssetDir_getNextFileName:CString( assetDir:AAssetDir )
Function AAssetDir_rewind( assetDir:AAssetDir )
Function AAssetDir_close( assetDir:AAssetDir )
	
Function AAsset_getLength:Int( asset:AAsset )
Function AAsset_getRemainingLength:Int( asset:AAsset )
Function AAsset_read:Int( asset:AAsset,buf:Void Ptr,count:Int )
Function AAsset_seek:Int( asset:AAsset,offset:Int,whence:Int )
Function AAsset_close( asset:AAsset )
	
Public

Function GetAssetManager:AAssetManager()
	
	Return Cast<AAssetManager>( Android_JNI_GetAssetManager() )
End

#endif


