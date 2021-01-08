
Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"
#Import "<mojo3d-loaders>"

#Import "assets/psionic/turtle1.b3d"
#Import "assets/psionic/turtle1.png"

#Import "util"

Using std..
Using mojo..
Using mojo3d..

Class MyWindow Extends Window
	
	Field _scene:Scene
	
	Field _camera:Camera
	
	Field _light:Light
	
	Field _ground:Model
	
	Field _turtle:Model
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		'create scene
		'		
		_scene=Scene.GetCurrent()
		
		'create camera
		'
		_camera=New Camera( Self )
		_camera.Near=.1
		_camera.Far=100
		_camera.Move( 0,10,-20 )
		
		New FlyBehaviour( _camera )
		
		'create light
		'
		_light=New Light
		_light.Rotate( 75,15,0 )	'aim directional light 'down' - Pi/2=90 degrees.
		_light.CastsShadow=True
		
		'create ground
		'
		_ground=Model.CreateBox( New Boxf( -50,-5,-50,50,0,50 ),1,1,1,New PbrMaterial( Color.Green ) )
		_ground.CastsShadow=False
		
		'create ground
		'
'		_ground=Model.CreateBox( New Boxf( -50,-1,-50,50,0,50 ),1,1,1,New PbrMaterial( Color.Green,0,.5 ) )
		
		'create turtle
		'		
		_turtle=Model.LoadBoned( "asset::turtle1.b3d" )
		_turtle.Scale=New Vec3f( .125 )

		Local walk:=_turtle.Animator.Animations[0].Slice( "Walk",1,11,AnimationMode.Looping )
		_turtle.Animator.Animations.Add( walk )
		
		For Local i:=0 Until 360 Step 6
			
			Local copy:=_turtle.Copy()
			
			copy.RotateY( i )
			copy.MoveZ( 30 )
			
			copy.Animator.Animate( copy.Animator.Animations[0],Rnd(.5,1.0) )
			
		Next
		
		_turtle.Animator.Animate( "Walk" )
	End
		
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()

		_scene.Update()
		
		_camera.Render( canvas )
		
		canvas.Scale( Width/640.0,Height/480.0 )
		
		canvas.DrawText( "Width="+Width+", Height="+Height+", anim time="+_turtle.Animator.Time+", FPS="+App.FPS,0,0 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
