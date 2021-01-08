
Namespace test1

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"
#Import "<thread>"

Using std..
Using mojo..
Using mojo3d..

#If __THREADS__

Class C
End

Function Test()
	
	Const N:=10
	
	Local threads:=New Thread[N]
	
	For Local i:=0 Until N
		
		Local sema:=New Semaphore
	
		threads[i]=New Thread( Lambda()
		
			Print "Starting thread id="+Thread.Current().Id
			
			sema.Signal()
			
			For Local i:=0 Until 10
				
				Print "thread="+Thread.Current().Id+" i="+i
				
				For Local j:=0 Until 1000
					Local tmp:=New C
					Local tmp2:=tmp
				Next
			Next
			
		End )
		
		Print "Thread started id="+threads[i].Id
	
	Next
	
	For Local i:=0 Until N
		
		Print "Joining "+i
		
		threads[i].Join()

		Print "Joined "+i
	Next
End

#endif

Class MyWindow Extends Window
	
	Field _scene:Scene
	Field _camera:Camera
	Field _light:Light
	Field _ground:Model
	Field _donut:Model
	
	Method New( title:String="Simple mojo3d app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )
		
		Super.New( title,width,height,flags )
	End
	
	Method OnCreateWindow() Override
		
		'create (current) scene
		_scene=New Scene
		_scene.ClearColor = New Color( 0.2, 0.6, 1.0 )
		_scene.AmbientLight = _scene.ClearColor * 0.25
		_scene.FogColor = _scene.ClearColor
		_scene.FogFar = 1.0
		_scene.FogFar = 200.0
		
		'create camera
		_camera=New Camera( Self )
		_camera.AddComponent<FlyBehaviour>()
		_camera.Move( 0,2.5,-5 )
		
		'create light
		_light=New Light
		_light.CastsShadow=True
		_light.Rotate( 45, 45, 0 )
		
		'create ground
		Local groundBox:=New Boxf( -100,-1,-100,100,0,100 )
		Local groundMaterial:=New PbrMaterial( Color.Lime )
		_ground=Model.CreateBox( groundBox,1,1,1,groundMaterial )
		_ground.CastsShadow=False
		
		'create donut
		Local donutMaterial:=New PbrMaterial( Color.Red, 0.05, 0.2 )
		_donut=Model.CreateTorus( 2,.5,48,24,donutMaterial )
		_donut.Move( 0,2.5,0 )
	End
	
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		_donut.Rotate( .2,.4,.6 )
		_scene.Update()
		_camera.Render( canvas )
		
		canvas.DrawText( "FPS="+App.FPS,0,0 )
	End
	
End

Function Main()

#If __THREADS__

	Local N:=10
	
	GCSetTrigger( 65536 )
	
'	GCSuspend()
	
	For Local i:=0 Until N
	
		Test()
	Next
	
	Print "Threads test finished!"

#endif

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
