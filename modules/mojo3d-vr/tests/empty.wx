
Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"
#Import "<mojo3d-vr>"

#Import "assets/vivecontroller.gltf"

Using std..
Using mojo..
Using mojo3d..

Class MyWindow Extends Window
	
	Field _renderer:VRRenderer
	
	Field _scene:Scene
	
	Field _camera:Camera

	Field _light:Light
	
	Field _ground:Model
	
	Field _baseStations:=New Model[2]

	Field _controllers:=New Model[2]
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		SwapInterval=0
		
		Print "GL_VERSION="+opengl.glGetString( opengl.GL_VERSION )
		
		'Enables VR: must happen before Scene.GetCurrent()
		'
		_renderer=New VRRenderer
		
		'Use more detailed CSM shadow split distances to compensate for the much nearer near clip plane.
		'
		_renderer.CSMSplits=New Float[]( 2,4,16,256 )
		
		_renderer.TrackingSpace=VRTrackingSpace.Standing
		
		'Get current scene
		'
		_scene=Scene.GetCurrent()

		'create camera
		'
		_camera=New Camera
		_camera.Viewport=Rect	'Inital viewport same as view.
		_camera.Near=.01		'Note: near clip plane 1 centimeter from camera so we can look at things nice and close up.
		_camera.Far=256			'only 10m visiblity.
		
		'create light
		'
		_light=New Light
		_light.Rotate( 75,15,0 )
		_light.CastsShadow=True
		
		'create ground
		'
		Local groundBox:=New Boxf( -50,-.1,-50,50,0,50 )
		Local groundMaterial:=New PbrMaterial( Color.Green,0,1 )
		_ground=Model.CreateBox( groundBox,1,1,1,groundMaterial )
		Local groundCollider:=New BoxCollider( _ground )
		Local groundBody:=New RigidBody( _ground )
		groundCollider.Box=groundBox
		groundBody.Mass=0
		
		_ground.CastsShadow=False
		
		'create base stations
		'
		Local baseStationBox:=New Boxf( -.042,-.042,-.042,.042,.042,.042 )
		Local baseStationMaterial:=New PbrMaterial( Color.Aluminum,1.0,1.0 )
		Local baseStation:=Model.CreateBox( baseStationBox,1,1,1,baseStationMaterial )
		
		_baseStations[0]=baseStation
		_baseStations[1]=baseStation.Copy()
		
		'create controllers
		Local controller:=Model.Load( "asset::vivecontroller.gltf" )
		controller.Mesh.TransformVertices( AffineMat4f.Rotation( -Pi/2,0,0 ) )

		_controllers[0]=controller
		_controllers[1]=controller.Copy()
	End
	
	Method OnRender( canvas:Canvas ) Override

		RequestRender()
		
		'Update camera viewport, ie: handle window/view resizing
		'
		_camera.Viewport=Rect
		
		'Update VR - update all VR matrices, controller states etc.
		'
		_renderer.Update()
		
		'Update camera
		'
		_camera.Matrix=_renderer.HeadMatrix
		
		'Update controllers
		'		
		Local cmatrix:=_renderer.ControllerMatrices[0]
		
		Local adj:=AffineMat4f.Rotation( 0,0,-cmatrix.m.GetRoll() )
		
		cmatrix=cmatrix * adj
		
		'Local yaw:=_controllers[0].Basis.GetYaw()
		'Local pitch:=_controllers[0].Basis.GetPitch()
		'Local adj:=AffineMat4f.Rotation( pitch,yaw,0 )
		
		_controllers[0].Matrix=cmatrix
		_controllers[1].Matrix=_renderer.ControllerMatrices[1]
		
		'Hide controllers when vr 'paused' (eg: when system menu up)
		'
		_controllers[0].Visible=_renderer.Active
		_controllers[1].Visible=_renderer.Active

		'Update base stations
		'
		_baseStations[0].Matrix=_renderer.BaseStationMatrices[0]
		_baseStations[1].Matrix=_renderer.BaseStationMatrices[1]

		'Update scene unless VR paused
		'
		If _renderer.Active _scene.Update()
			
		'Render scene!
		'		
		_scene.Render( canvas )

		'Render left eye view to canvas
		'
		canvas.DrawRect( 0,Height,Width,-Height,_renderer.LeftEyeImage )

		canvas.DrawText( "Camera.Position="+_camera.Position+", FPS="+App.FPS,0,0 )
	End
	
End

Function Main()
	
	New AppInstance
	
	New MyWindow
	
	App.Run()
End
