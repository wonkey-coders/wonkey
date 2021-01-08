
#Import "<std>"
#Import "<mojo3d-vr>"

Using std..
Using openvr..
Using mojo3d..

Function Main()
	
	Print "Hello from vr_init"
	
	Local _leftEyeMatrix:=New AffineMat4f
	Local _rightEyeMatrix:=New AffineMat4f
	
	Local _leftEyeFrustum:Rectf
	Local _rightEyeFrustum:Rectf
	
	local type:=VRApplication_Scene,error:HmdError
	
	Print "Calling VR_Init()..."
	
	VR_Init( Varptr error,type )
	
	If error<>VRInitError_None RuntimeError( "VR_Init error:"+VR_GetVRInitErrorAsSymbol( error ) )
		
	Print "VR_Init() Success!"

	_leftEyeMatrix=Cast<AffineMat4f>( VRSystem().GetEyeToHeadTransform( Eye_Left ) )

	_rightEyeMatrix=Cast<AffineMat4f>( VRSystem().GetEyeToHeadTransform( Eye_Right ) )
	
	VRSystem().GetProjectionRaw( Eye_Left,Varptr _leftEyeFrustum.min.x,Varptr _leftEyeFrustum.max.x,Varptr _leftEyeFrustum.min.y,Varptr _leftEyeFrustum.max.y )
	
	VRSystem().GetProjectionRaw( Eye_Right,Varptr _rightEyeFrustum.min.x,Varptr _rightEyeFrustum.max.x,Varptr _rightEyeFrustum.min.y,Varptr _rightEyeFrustum.max.y )
	
	Print "~nleftEyeMatrix:~n"+_leftEyeMatrix
	Print "~nrightEyeMatrix:~n"+_rightEyeMatrix
	Print "~nleftEyeFrustum:~n"+_leftEyeMatrix
	Print "~nleftEyeFrustum:~n"+_leftEyeMatrix
	
	Local frustum:=vr.Frustum( _leftEyeFrustum.min.x,_leftEyeFrustum.max.x,_leftEyeFrustum.min.y,_leftEyeFrustum.max.y,.1,100 )
	Local inv:=-frustum
	
	Print (inv * New Vec3f( 0,0,-1 )).z	'near?
	Print (inv * New Vec3f( 0,0,+1 )).z	'far?

	VR_Shutdown()
	
	Print "Later fiend"
End
