Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"
#Import "<mojo3d-loaders>"

#Import "assets/psionic/ninja.b3d"
#Import "assets/psionic/nskinbl.jpg"

Using std..
Using mojo..
Using mojo3d..

Class MyWindow Extends Window
	
	Field _scene:Scene
	
	Field _camera:Camera
	
	Field _light:Light
	
	Field _ground:Model
	
	Field _ninja:Model
	
	Field _animator:Animator
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		'create scene
		'		
		_scene=Scene.GetCurrent()
		_scene.SkyTexture=Texture.Load( "asset::miramar-skybox.jpg",TextureFlags.FilterMipmap|TextureFlags.Cubemap )
		
		'create camera
		'
		_camera=New Camera( Self )
		_camera.AddComponent<FlyBehaviour>()
		_camera.Near=.1
		_camera.Far=100
		_camera.Move( 0,5,-7 )
		
		'create light
		'
		_light=New Light
		_light.Rotate( 75,15,0 )	'aim directional light 'down' - Pi/2=90 degrees.
		_light.CastsShadow=True
		
		'create ground
		'
		_ground=Model.CreateBox( New Boxf( -50,-5,-50,50,0,50 ),1,1,1,New PbrMaterial( Color.Green ) )
		_ground.CastsShadow=False
		
		'create turtle
		'		
		_ninja=Model.LoadBoned( "asset::ninja.b3d" )
		
		_animator=_ninja.Animator
		
		_ninja.RotateY( 165 )
'		_ninja.Scale=New Vec3f( .125 )

		_animator.MasterSpeed=0.5

		Local anim1:=_animator.Animations[0].Slice( "Walk",1,14,AnimationMode.Looping )
		Local anim2:=_animator.Animations[0].Slice( "Idle",206,250,AnimationMode.Looping )
		Local anim3:=_animator.Animations[0].Slice( "Attack",134,145,AnimationMode.OneShot )
		_animator.Animations.Add( anim1 )
		_animator.Animations.Add( anim2 )
		_animator.Animations.Add( anim3 )
		
	End
		
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		
		If _animator.Animating?.Name<>"Attack"
			
			If Keyboard.KeyHit( Key.Space )				'attack!
				
				_animator.Animate( "Attack",.2 )
				
			Else If Keyboard.KeyDown( Key.Enter )		'walk
				
				_animator.Animate( "Walk",.2 )
			Else										'idle
				
				_animator.Animate( "Idle",.2 )
				
			Endif
		
		Endif
	
		_scene.Update()
		
		_camera.Render( canvas )
		
		canvas.Scale( Width/640.0,Height/480.0 )
		
		canvas.DrawText( "Hold [Enter] to strut, [Space] to attack! anim time="+_ninja.Animator.Time,0,0 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
