Namespace myapp3d

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"
#Import "<mojo3d-vr>"

#Import "assets/plane/"
#Import "assets/water.jpg"
#Import "assets/miramar-skybox.jpg"

Using std..
Using mojo..
Using mojo3d..

Using openvr..

Class MyWindow Extends Window
	
	Field _renderer:VRRenderer
	
	Field _scene:Scene
	
	Field _camera:Camera
	
	Field _light:Light
	
	Field _water:Model
	
	Field _plane:Model
	
	Field _headpos:=AffineMat4f.Translation( 0,1.26,-.26 )
	
	Method New( title:String="Simple mojo3d app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		_renderer=New VRRenderer
		
		_renderer.OpenvrEventFilter+=OnOpenvrEvent

		Local state:=_renderer.GetControllerState( 0 )
		
		state.Changed+=Lambda()
		
			Print "ControllerState Changed"+
				", ButtonPressedMask="+Hex(state.ButtonPressedMask)+
				", ButtonTouchedMask="+Hex(state.ButtonTouchedMask)+
				", Trackpad="+state.Trackpad+
				", Trigger="+state.Trigger
		
		End
		
		
		_scene=New Scene

		'Use more detailed CSM shadow split distances to compensate for the much nearer near clip plane.
		'
		_scene.CSMSplits=New Float[]( 2,4,16,256 )
		
		_scene.SkyTexture=Texture.Load( "asset::miramar-skybox.jpg",TextureFlags.FilterMipmap|TextureFlags.Cubemap )
		
		'create light
		'
		_light=New Light
		_light.Rotate( 45,15,0 )
'		_light.CastsShadow=true
		
		Local material:=New PbrMaterial( Color.Black )
		material.EmissiveFactor=New Color( 0,2,0 )
		
		'create water material
		'
		Local waterMaterial:=New PbrMaterial
		
		waterMaterial.ScaleTextureMatrix( 100,100 )
		waterMaterial.ColorTexture=Texture.Load( "asset::water.jpg",TextureFlags.WrapST|TextureFlags.FilterMipmap )
		waterMaterial.ColorFactor=New Color( 0.05, 0.25, 0.3 )
		
		'create water
		'
		_water=Model.CreateBox( New Boxf( -1000,-1,-1000,1000,0,1000 ),1,1,1,waterMaterial )

		'create plane
		'		
		_plane=Model.Load( "asset::plane.gltf" )
		_plane.Mesh.FitVertices( New Boxf( -10,-1.0,-10,10,1.85,9 ) )
		_plane.Move( 0,10,0 )
		
		New FlyBehaviour( _plane )
		
		'create camera
		'
		_camera=New Camera( Self,_plane )
		
		_camera.Near=.1
		
		_camera.Far=100
		
		_camera.Move( 0,.5,.5 )
		
		SwapInterval=0
		
	End
	
	'for hooking into low level openvr events
	'
	Method OnOpenvrEvent( event:VREvent_t Ptr )
		
		#rem
		
		'Print "OpenvrEvent! type="+VRSystem().GetEventTypeNameFromEnum( Cast<EVREventType>( event->eventType ) )
		
		Select event->eventType
		Case VREvent_ButtonPress
			Print "Press:"+VRSystem().GetButtonIdNameFromEnum( Cast<EVRButtonId>( event->data.controller.button ) )
		Case VREvent_ButtonUnpress
			Print "Unpress:"+VRSystem().GetButtonIdNameFromEnum( Cast<EVRButtonId>( event->data.controller.button ) )
		Case VREvent_ButtonTouch
			Print "Touch:"+VRSystem().GetButtonIdNameFromEnum( Cast<EVRButtonId>( event->data.controller.button ) )
		Case VREvent_ButtonUntouch
			Print "Untouch:"+VRSystem().GetButtonIdNameFromEnum( Cast<EVRButtonId>( event->data.controller.button ) )
		End
		
		#end
		
	End
	
	Method OnRender( canvas:Canvas ) Override
		
		'Esc to quit
		'
		If Keyboard.KeyHit( Key.Escape ) App.Terminate()
			
		RequestRender()
		
		'need to call this for VRRenderer before renderer or you'll get an error.
		'
		_renderer.Update()
		
		If Keyboard.KeyHit( Key.Space ) _renderer.ResetSeatedPose()
		
		_camera.LocalMatrix=_headpos * _renderer.HeadMatrix
		
		_scene.Update()
		
		_water.Position=New Vec3f( Round(_camera.Position.x/1000)*1000,0,Round(_camera.Position.z/1000)*1000 )
		
		_scene.Render( canvas )

		'upside down? I thought we were over that...		
		canvas.DrawRect( 0,Height,Width,-Height,_renderer.LeftEyeImage )
		
		canvas.DrawText( "Width="+Width+", Height="+Height+", FPS="+App.FPS,0,0 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
