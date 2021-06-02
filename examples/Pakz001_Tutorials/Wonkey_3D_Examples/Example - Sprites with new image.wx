#Import "<std>"
#Import "<mojo>"
#Import "<mojo3d>"


Using std..
Using mojo..
Using mojo3d.. 'The new mojo 3d module.


Class MyWindow Extends Window
	' What are we going to use.
	Field myscene:Scene
	Field mycamera:Camera
	Field mylight:Light	
	Field mybox:Model
	Field sprites:=New Stack<Sprite>
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		' Get the current scene
		myscene=Scene.GetCurrent()
		
		'create camera
		'
		mycamera = New Camera
		mycamera.Near = 1 '??
		mycamera.Far = 256 'how far should we render
		mycamera.Move(0,0,0) 'move the camera to position x,y,z


		'create light
		'
		mylight = New Light
		mylight.RotateX(Pi/2)	'aim directional light 'down' - Pi/2=90 degrees.

		'
		' Create cube
		'
		' This is the mesh with which we create the model.
		Local mymesh := Mesh.CreateBox( New Boxf( -2,-2,-2,2,2,2 ),1,1,1 )
		' Here we create the material that we put on the box.
		Local material:=New PbrMaterial( New Color( 1,0,0) )
		mybox = New Model( mymesh,material )
		mybox.Move(0,0,20)				

	 	Local sm:= New SpriteMaterial()		
		Local ri:Image=New Image( 32, 32 )
		Local rc:Canvas=New Canvas(ri)
		rc.Clear(Color.Blue)
		rc.Flush()	 	
		sm.ColorTexture = ri.Texture

		For Local i:=0 Until 100
			
			Local sprite:=New Sprite(sm)			
			Local x:Int=Rnd(-50,50)
			Local y:Int=Rnd(-50,50)
			Local z:Int=Rnd(-50,50)
			sprite.Move(x,y,z)
			sprite.Scale=New Vec3f( Rnd(4,5),Rnd(5,6),1 )			
			sprite.Handle=New Vec2f( .5,0 )			
			sprite.Mode=SpriteMode.Billboard
			'sprite.Mode=SpriteMode.Upright
			sprites.Push( sprite )

		Next
	End Method
	
	' This method is the main loop.
	Method OnRender( canvas:Canvas ) Override
	
		RequestRender()
		
		' Primitive Mouse Movement
		If Mouse.X < 250 Then mycamera.RotateY(1.4)
		If Mouse.X > Width - 250 Then mycamera.RotateY(-1.4)
		If Mouse.Y > Height/2 Then mycamera.RotateX(1.4)
		If Mouse.Y < Height/2 Then mycamera.RotateX(-1.4)
		mybox.Rotate(.5,.5,.5) 'rotate the box (x,y,z)
		
		myscene.Update()
		myscene.Render( canvas) 'render the 3d scene
		
		canvas.Color = Color.Black
		canvas.DrawText("Move mouse to edges to turn.",0,0)
		
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		
	End Method

End Class

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End Function
