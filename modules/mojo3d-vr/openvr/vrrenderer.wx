
Namespace mojo3d.vr

Enum VRTrackingSpace
	Seated
	Standing
End

Enum VRAxis
	Trackpad=			0
	Trigger=			1
End

Enum VRButton
	
	System=				0
	Menu=				1
	Grip=				2
	DPadLeft=			3
	DPadUp=				4
	DPadRight=			5
	DPadDown=			6
	A=					7

	ProximitySensor=	15	'31 in openvr, but lets stick to an int for now...
	Axis0=				16
	Axis1=				17
	Axis2=				18
	Axis3=				19
	Axis4=				20
	Trackpad=			Axis0
	Trigger=			Axis1
	DashboardBack=		Grip
End

Class VRControllerState
	
	Field Changed:Void()
	
	Property Seq:Int()
		
		Return _seq
	End
	
	Property Matrix:AffineMat4f()
		
		Return Cast<AffineMat4f>( _pose.mDeviceToAbsoluteTracking )		
	End
	
	Property ButtonPressedMask:Int()
		
		Return _pressed
	End
	
	Property ButtonTouchedMask:Int()
		
		Return _touched
	End
	
	Property Trackpad:Vec2f()
		
		Return New Vec2f( _state.rAxis[0].x,_state.rAxis[0].y )
	End
	
	Property Trigger:Float()
		
		Return _state.rAxis[1].x
	End
	
	Method GetButtonPressed:Bool( button:VRButton )
		
		Return _pressed & (1 Shl button)
	End
	
	Method GetButtonTouched:Bool( button:VRButton )
		
		Return _touched & (1 Shl button)
	End
	
	Method GetAxis:Vec2f( axis:VRAxis )
		
		Return New Vec2f( _state.rAxis[axis].x,_state.rAxis[axis].y )
	End
	
	Internal
	
	Method Update( index:Int,origin:ETrackingUniverseOrigin )

		If Not VRSystem().GetControllerStateWithPose( origin,index,Varptr _state,libc.sizeof( _state ),Varptr _pose )
'			Print "OpenVR GetControllerState Failed!"
			Return
		Endif
		
		If _state.unPacketNum=_seq Return
		
		_pressed=(_state.ulButtonPressed Shr 16 & ~$7fff) | (_state.ulButtonPressed & $7fff)
		
		_touched=(_state.ulButtonTouched Shr 16 & ~$7fff) | (_state.ulButtonTouched & $7fff)
			
		_seq=_state.unPacketNum
				
		Changed()
	End
	
	Private
	
	Field _state:VRControllerState_t
	
	Field _pose:TrackedDevicePose_t
	
	Field _pressed:Int
	
	Field _touched:Int
	
	Field _seq:Int
End

Class VRRenderer Extends Renderer
	
	Field OpenvrEventFilter:Void( vrevent:VREvent_t Ptr )
	
	Method New()
		
		InitVR()
		
		InitRender()
	End
	
	Property Active:Bool()
		
		Return Not VROverlay().IsDashboardVisible()
	End
	
	Property NumControllers:Int()
		
		Return _numControllers
	End
	
	Property NumBaseStations:Int()
		
		Return _numBaseStations
	End
	
	Property HeadMatrix:AffineMat4f()
		
		Return _headMatrix
	End
	
	Property ControllerMatrices:AffineMat4f[]()
		
		Return _controllerMatrices
	End
	
	Property BaseStationMatrices:AffineMat4f[]()
		
		Return _baseStationMatrices
	End

	Property LeftEyeImage:Image()
		
		Return _leftEyeImage
	End
	
	Property RightEyeImage:Image()
		
		Return _rightEyeImage
	End
	
	Property TrackingSpace:VRTrackingSpace()
		
		Return _trackingSpace
	
	Setter( space:VRTrackingSpace )
		
		If space=_trackingSpace Return
		
		_trackingSpace=space
		
		Select _trackingSpace
		Case VRTrackingSpace.Seated
	 		VRCompositor().SetTrackingSpace( TrackingUniverseSeated )
		Case VRTrackingSpace.Standing
	 		VRCompositor().SetTrackingSpace( TrackingUniverseStanding )
		End
	 
	End
	
	Method GetControllerState:VRControllerState( index:Int )
		
		Return _controllerStates[index]
	End
	
	Method Update()

		Local vrevent:VREvent_t
		
		While VRSystem().PollNextEvent( Varptr vrevent,libc.sizeof( vrevent ) )
			
			OpenvrEventFilter( Varptr vrevent )
		Wend
		
		Local poses:=New TrackedDevicePose_t[k_unMaxTrackedDeviceCount]

		If VRCompositor().WaitGetPoses( poses.Data,k_unMaxTrackedDeviceCount,Null,0 )<>VRCompositorError_None

			RuntimeError( "Compositor error for WaitGetPoses!" )
		Endif
		
		Local origin:=_trackingSpace=VRTrackingSpace.Seated ? TrackingUniverseSeated Else TrackingUniverseStanding
		
		_numControllers=0
		_numBaseStations=0

		_headId=-1
		_headMatrix=New AffineMat4f
		
		For Local i:=0 Until k_unMaxTrackedDeviceCount
			
			Local p:=poses.Data+i
			
			If Not p->bDeviceIsConnected Continue
			
			Local c:=VRSystem().GetTrackedDeviceClass( i )
			
			Select c
			Case TrackedDeviceClass_HMD
				
				_headId=i
				_headMatrix=Cast<AffineMat4f>( p->mDeviceToAbsoluteTracking )
				
			Case TrackedDeviceClass_Controller
				
				If _numControllers<2
					_controllerIds[_numControllers]=i
					_controllerStates[_numControllers].Update( i,origin )
					_controllerMatrices[_numControllers]=Cast<AffineMat4f>( p->mDeviceToAbsoluteTracking )
					_numControllers+=1
				Endif

			Case TrackedDeviceClass_TrackingReference
				
				If _numBaseStations<2
					_baseStationIds[_numBaseStations]=i
					_baseStationMatrices[_numBaseStations]=Cast<AffineMat4f>( p->mDeviceToAbsoluteTracking )
					_numBaseStations+=1
				Endif
				
			End
		Next
		
		For Local i:=_numControllers Until 2
			_controllerIds[i]=-1
			_controllerMatrices[i]=New AffineMat4f
		Next
		
		For Local i:=_numBaseStations Until 2
			_baseStationIds[i]=-1
			_baseStationMatrices[i]=New AffineMat4f
		Next
	End
	
	Method ResetSeatedPose()

		VRSystem().ResetSeatedZeroPose()
	End
	
	Method Openvr_GetHMDTrackedDeviceIndex:TrackedDeviceIndex_t()
		
		Return _headId
	End
	
	Method Openvr_GetControllerTrackedDeviceIndex:TrackedDeviceIndex_t( index:Int )
		
		Return _controllerIds[index]
	End
	
	Method Openvr_GetTrackingReferenceTrackedDeviceIndex:TrackedDeviceIndex_t( index:Int )
		
		Return _baseStationIds[index]
	End
	
	Protected
	
	Method Render( target:RenderTarget,targetSize:Vec2i,viewport:Recti,scene:Scene,viewMatrix:AffineMat4f,projMatrix:Mat4f,near:Float,far:Float ) Override
		
		Local ptexture:Texture_t
		
		ptexture.eType=TextureType_OpenGL
		ptexture.eColorSpace=ColorSpace_Auto
		
		Local tviewMatrix:AffineMat4f
		Local tprojMatrix:Mat4f
		
		'***** Render left eye *****
		'	
		tviewMatrix=_leftEyeMatrix * viewMatrix

		tprojMatrix=vr.Frustum( _leftEyeFrustum.min.x,_leftEyeFrustum.max.x,_leftEyeFrustum.min.y,_leftEyeFrustum.max.y,near,far )
		
		Super.Render( _leftEyeRTarget,_eyeRect.Size,_eyeRect,scene,tviewMatrix,tprojMatrix,near,far )
		
		ptexture.handle=Cast<Void Ptr>( _leftEyeTex.ValidateGLTexture() )

		If VRCompositor().Submit( Eye_Left,Varptr ptexture )<>VRCompositorError_None
			
			RuntimeError( "OpenVR Compositor error for Submit left eye!" )
		Endif

		
		'***** Render righteye *****
		'
		tviewMatrix=_rightEyeMatrix * viewMatrix

		tprojMatrix=vr.Frustum( _rightEyeFrustum.min.x,_rightEyeFrustum.max.x,_rightEyeFrustum.min.y,_rightEyeFrustum.max.y,near,far )
		
		Super.Render( _rightEyeRTarget,_eyeRect.Size,_eyeRect,scene,tviewMatrix,tprojMatrix,near,far )
		
		ptexture.handle=Cast<Void Ptr>( _rightEyeTex.ValidateGLTexture() )

		If VRCompositor().Submit( Eye_Right,Varptr ptexture )<>VRCompositorError_None
			
			RuntimeError( "OpenVR Compositor error for Submit right eye!" )
		Endif
		
		'***** Finished VR *****
		
		VRCompositor().PostPresentHandoff()
	End
	
	Protected
	
	Method RenderCopyQuad() Override
		
		Super.RenderQuad()
	end
	
	Private
	
	'VR
	Field _headMatrix:AffineMat4f
	Field _numControllers:Int
	Field _numBaseStations:Int
	Field _controllerMatrices:=New AffineMat4f[2]
	Field _baseStationMatrices:=New AffineMat4f[2]
	
	Field _controllerStates:=New VRControllerState[2]
	
	Field _headId:Int
	Field _controllerIds:=New Int[2]
	Field _baseStationIds:=New Int[2]
	
	Field _eyeRect:Recti
	
	Field _leftEyeMatrix:=New AffineMat4f
	Field _rightEyeMatrix:=New AffineMat4f
	
	Field _leftEyeFrustum:Rectf
	Field _rightEyeFrustum:Rectf
	
	Field _trackingSpace:VRTrackingSpace
	
	'Render
	Field _leftEyeTex:Texture
	Field _leftEyeRTarget:RenderTarget
	
	Field _rightEyeTex:Texture
	Field _rightEyeRTarget:RenderTarget
	
	Field _leftEyeImage:Image
	Field _rightEyeImage:Image
	
	Method InitVR()

		local type:=VRApplication_Scene,error:HmdError
		
		VR_Init( Varptr error,type )
		
		If error<>VRInitError_None RuntimeError( "VR_Init error:"+VR_GetVRInitErrorAsSymbol( error ) )

		Local w:UInt,h:UInt
		VRSystem().GetRecommendedRenderTargetSize( Varptr w,Varptr h )
		_eyeRect=New Recti( 0,0,w,h )

		_leftEyeMatrix=-Cast<AffineMat4f>( VRSystem().GetEyeToHeadTransform( Eye_Left ) )
		_rightEyeMatrix=-Cast<AffineMat4f>( VRSystem().GetEyeToHeadTransform( Eye_Right ) )
		
		VRSystem().GetProjectionRaw( Eye_Left,Varptr _leftEyeFrustum.min.x,Varptr _leftEyeFrustum.max.x,Varptr _leftEyeFrustum.min.y,Varptr _leftEyeFrustum.max.y )
		
		VRSystem().GetProjectionRaw( Eye_Right,Varptr _rightEyeFrustum.min.x,Varptr _rightEyeFrustum.max.x,Varptr _rightEyeFrustum.min.y,Varptr _rightEyeFrustum.max.y )
		
		_headId=-1;_controllerIds[0]=-1;_controllerIds[1]=-1;_baseStationIds[0]=-1;_baseStationIds[1]=-1
		
		_controllerStates[0]=New VRControllerState
		_controllerStates[1]=New VRControllerState

 		VRCompositor().SetTrackingSpace( TrackingUniverseSeated )
		_trackingSpace=VRTrackingSpace.Seated
	End
	
	Method InitRender()
		
		Local w:UInt,h:UInt
		VRSystem().GetRecommendedRenderTargetSize( Varptr w,Varptr h )
		
		_leftEyeTex=New Texture( _eyeRect.Width,_eyeRect.Height,PixelFormat.RGBA8,TextureFlags.Dynamic|TextureFlags.Filter )
		_leftEyeRTarget=New RenderTarget( New Texture[]( _leftEyeTex ),Null )
		
		_rightEyeTex=New Texture( _eyeRect.Width,_eyeRect.Height,PixelFormat.RGBA8,TextureFlags.Dynamic|TextureFlags.Filter )
		_rightEyeRTarget=New RenderTarget( New Texture[]( _rightEyeTex ),Null )
		
		_leftEyeImage=New Image( _leftEyeTex )
		_rightEyeImage=New Image( _rightEyeTex )
	End
			
End
