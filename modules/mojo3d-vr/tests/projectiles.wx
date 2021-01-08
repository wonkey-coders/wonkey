
Namespace myapp

#Import "<mojo3d-vr>"

#Import "assets/scuffed-plastic-pbr/@/scuffed-plastic-pbr"

#Import "assets/plastic-pattern-pbr/@/plastic-pattern-pbr"

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
	
	Field _ctrlModel:Model
	
	Field _bases:=New Model[2]

	Field _ctrls:=New Model[2]
	
	Field _bullets:=New Model[2]
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
	End
	
	Method OnCreateWindow() Override
		
		SwapInterval=0
		
		'Enables VR
		'
		_renderer=New VRRenderer
		
		_renderer.TrackingSpace=VRTrackingSpace.Standing
		
		_scene=New Scene
		
		_scene.UpdateRate=90
		
		_scene.MaxSubSteps=2
		
		'Use more detailed CSM shadow split distances to compensate for the much nearer near clip plane.
		'
		_scene.CSMSplits=New Float[]( 2,4,16,256 )
		
		'_scene.UpdateRate=90

		'create camera
		'
		_camera=New Camera
		_camera.Near=.01		'Note: near clip plane 1 centimeter from camera so we can look at things nice and close up.
		_camera.Far=100			'camera far/near ratio is probably a bit much
		
		'create light
		'
		_light=New Light
		_light.Rotate( 75,15,0 )
		_light.CastsShadow=True
		
		'ground material
		'
		Local groundMaterial:=New PbrMaterial( Color.Green,0,1 )
		
		'create ground
		'
		Local groundBox:=New Boxf( -10,-.1,-10,10,.1,10 )
		
		_ground=Model.CreateBox( groundBox,1,1,1,groundMaterial )
		_ground.CastsShadow=False
'		_ground.Move( 0,-1,0 )
		
'		Local groundCollider:=New BoxCollider( _ground )
'		groundCollider.Box=groundBox

		Local groundCollider:=New ConvexHullCollider( _ground )
		groundCollider.Mesh=_ground.Mesh

		'***** bullet mesh collisions suck badly, big problem? *****
'		Local groundCollider:=New MeshCollider( _ground )
'		groundCollider.UseInternalEdgeInfo=True
'		groundCollider.Mesh=_ground.Mesh

		Local groundBody:=New RigidBody( _ground )
'		groundBody.Kinematic=True
		groundBody.Mass=0
		
		'create basestations
		'		
		Local baseBox:=New Boxf( -.042,.042 )
		
		Local baseMaterial:=New PbrMaterial( Color.Aluminum,1.0,1.0 )
		
		_bases[0]=Model.CreateBox( baseBox,1,1,1,baseMaterial )
		
		Local baseCollider:=New BoxCollider( _bases[0] )
		baseCollider.Box=baseBox
		
		Local baseBody:=New RigidBody( _bases[0] )
		baseBody.Mass=0
	
		_bases[1]=_bases[0].Copy()
		
		'create controllers
		'
		Local ctrlModel:=Model.Load( "asset::vivecontroller.gltf" )
		ctrlModel.Mesh.TransformVertices( AffineMat4f.Rotation( -Pi/2,0,0 ) )
		
		_ctrls[0]=ctrlModel
		_ctrls[1]=ctrlModel.Copy()
		
		'create bullets
		'
		For Local i:=0 Until 2
			
			Local mat:=New PbrMaterial( i ? Color.Red Else Color.Blue,0,.5 )
			
			_bullets[i]=Model.CreateSphere( .05,24,12,mat,_ctrls[i] )
			_bullets[i].LocalPosition=New Vec3f( 0,0,.06 )
			
			Local collider:=New SphereCollider( _bullets[i] )
			collider.Radius=.05
			
			Local body:=New RigidBody( _bullets[i] )
			body.Kinematic=True				'while under user control
			body.Restitution=.7				'bouncy
			body.Mass=.170					'170g, about a pool ball?

			'Some fudge...launched dynamic bodies seem to be interfering with kinematic bodies,
			'even when kinematic bodies are hidden? investigate...
			body.CollisionGroup=0
			body.CollisionMask=0
			
		Next
		
#If __CONFIG__="debug"
		For Local an:=0 Until 360 Step 12
#else
		For Local an:=0 Until 360 Step 6
#endif
			Local sz:=.2,sz2:=1.50,sz3:=.1
			
			Local box:=New Boxf( -sz,-sz2,-sz3,+sz,+sz2,+sz3 )
			
			Local mat:=New PbrMaterial( New Color( Rnd(),Rnd(),Rnd() ),1,0 )
			
			Local model:=Model.CreateBox( box,1,1,1,mat )
			model.Rotate( 0,an,0 )
			model.Move( 0,sz2,Rnd( 2,8 ) )
			
			Local collider:=New BoxCollider( model )
			collider.Box=box
			
			Local body:=New RigidBody( model )
			body.Mass=1		'Default mass, 1kg
		Next
		
	End
	
	Method OnRender( canvas:Canvas ) Override

		RequestRender()
		
		'need to call this for VRRenderer before renderer or you'll get an error.
		'
		_renderer.Update()
		
		'***** shoot *****
		Local i:=0
		Local cstate:=_renderer.GetControllerState( i )
		
		If cstate.GetButtonPressed( VRButton.Trigger )
			
			If _bullets[i].Visible
				
				Local bullet:=_bullets[i].Copy( Null )
				
				bullet.RigidBody.Kinematic=False
				
				bullet.RigidBody.CollisionGroup=1
				bullet.RigidBody.CollisionMask=1
				
'				bullet.Position=cstate.Matrix.t
'				bullet.RigidBody.LinearVelocity=cstate.Matrix.m.k.Normalize() * 6

				bullet.Position=_bullets[i].Position
				bullet.RigidBody.LinearVelocity=_bullets[i].Basis.k * 6

'				bullet.RigidBody.ApplyImpulse( _bullets[i].Basis.k/90.0 * 6 )
			
				_bullets[i].Visible=False
				
			Endif
			
		Else
			
			_bullets[i].Visible=True
			
		Endif
		
		'***** throw *****
		i=1
		cstate=_renderer.GetControllerState( i )
		
		If cstate.GetButtonPressed( VRButton.Trigger )
			
			_bullets[i].Visible=True
		
		Else
			
			If _bullets[i].Visible
				
				Local bullet:=_bullets[i].Copy( Null )

				bullet.RigidBody.Kinematic=False
				
				bullet.RigidBody.CollisionGroup=1
				bullet.RigidBody.CollisionMask=1
				
				bullet.Position=_bullets[i].Position
				
				Local vel:=_renderer.ControllerMatrices[i].t-_ctrls[i].Position
					
				bullet.RigidBody.LinearVelocity=vel * _scene.UpdateRate * 2
					
				_bullets[i].Visible=False
			
			Endif
			
		Endif
		
		_camera.Matrix=_renderer.HeadMatrix
		
		_ctrls[0].Visible=_renderer.Active
		_ctrls[1].Visible=_renderer.Active
		
		_ctrls[0].Matrix=_renderer.ControllerMatrices[0]
		_ctrls[1].Matrix=_renderer.ControllerMatrices[1]
		
		_bases[0].Matrix=_renderer.BaseStationMatrices[0]
		_bases[1].Matrix=_renderer.BaseStationMatrices[1]
		
		If _renderer.Active _scene.Update()
		
		_scene.Render( canvas )

		'Done!
'		_renderer.LeftEyeImage.Scale=New Vec2f( -1,-1 )
		canvas.DrawRect( 0,Height,Width,-Height,_renderer.LeftEyeImage )

		canvas.Scale( Width/640.0,Height/480.0 )
		
		canvas.DrawText( "Camera.Position="+_camera.Position+", FPS="+App.FPS,0,0 )
	End
	
End

Function Main()
	
	New AppInstance
	
	New MyWindow
	
	App.Run()
End
