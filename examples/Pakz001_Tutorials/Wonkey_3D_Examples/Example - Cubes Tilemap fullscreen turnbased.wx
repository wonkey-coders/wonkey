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

	Field map:Int[,] = New Int[100,100]

	Field mapmodel:Model[,,] = New Model[2,15,15]

	Field posx:Int=50,posy:Int=50

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )
		
		createmap()
		' Get the current scene
		myscene=Scene.GetCurrent()
		
		'create camera
		'
		mycamera = New Camera
		mycamera.Near = 1 '??
		mycamera.Far = 256 'how far should we render
		mycamera.Move(30,25,5) 'move the camera to position x,y,z
		


		'create light
		'
		mylight = New Light
		mylight.CastsShadow = True
		mylight.Move(0,0,0)
		'mylight.RotateX(Pi/2)	'aim directional light 'down' - Pi/2=90 degrees.
		
		'
		' Here we create some sort of tile system. We create a bunch
		' of cubes that wil form the map. The floor is black and the walls
		' are reddish. Each of the upper cubes wil be visible or invisible
		' based on data on the map array. (Player location)
		'
		Local mymesh := Mesh.CreateBox( New Boxf( -2,-2,-2,2,2,2 ),1,1,1 )
		Local material:=New PbrMaterial( New Color( .7,.3,.3) )
		Local material2:=New PbrMaterial( New Color( .2,.2,.2) )
		For Local y:Int=0 Until 15
		For Local x:Int=0 Until 15			
			For Local i:Int=0 To 1
				If i=0 Then 
					mapmodel[i,x,y] = New Model( mymesh,material2 )
				Else
					mapmodel[i,x,y] = New Model( mymesh,material )
				End If
				mapmodel[i,x,y].Move(x*4,y*4,30-i*4)
			Next
		Next
		Next
		mylight.PointAt(mapmodel[0,4,4])
		'mycamera.PointAt(mapmodel[0,4,4])
		' Here we turn cubes invisible or visible based on the xpos and ypos for the
		' player.
		updatemap()
		'


	End Method
	
	' This method is the main loop.
	Method OnRender( canvas:Canvas ) Override
	
		RequestRender()
		
		
		myscene.Render( canvas) 'render the 3d scene
		
		' Player input
		If Keyboard.KeyReleased(Key.Up) Then 
			If posy<90 Then posy+=1
			updatemap()
		End If
		If Keyboard.KeyReleased(Key.Down) Then 
			If posy>10 Then posy-=1
			updatemap()
		End If
		If Keyboard.KeyReleased(Key.Left) Then 
			If posx>10 Then posx-=1
			updatemap()
		End If
		If Keyboard.KeyReleased(Key.Right) Then 
			If posx<90 Then posx+=1
			updatemap()
		End If
		
		
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		
		' Draw the minimap to the screen (map array)
		For Local y:Int=0 Until 100
		For Local x:Int=0 Until 100
			If map[x,y] = 1 Then 
				canvas.Color = Color.Red
				canvas.DrawRect(x*2,y*2,2,2)
			End If
		Next
		Next
		
		
	End Method

	
	'  
	' Here we set the models that are on the screen to visible or
	' unvisible based on the value on the map array. 
	'
	Method updatemap()		
		For Local y:Int=posy-7 To posy+6
		For Local x:Int=posx-7 To posx+6
			If map[x,y] = 0 Then 
				mapmodel[1,x-posx+7,y-posy+7].Visible = True
				Else
				mapmodel[1,x-posx+7,y-posy+7].Visible = False
			End if
		Next
		Next
	End Method
	
	' This creates a random map by drawing halways.
	Method createmap()
		SeedRnd(Microsecs())
		Local sx:Int=50
		Local sy:Int=50
		makehall(sx,sy,"left")
		makehall(sx,sy,"right")
		makehall(sx,sy,"up")
		makehall(sx,sy,"down")

	End Method
	' the map is 0 = wall - 1 = open
	' x = start x , y = start y
	' dir = direction to carve into (will stop if hits another open area
	' or random length =>z)
	Method makehall(x:Int,y:Int,dir:String)
		Local len:Int=Rnd(3,10)
		Local dirs:String[] = New String[]("up","down","right","left")
		For Local i:Int=0 Until len
			If Rnd(40) < 10 Then makehall(x,y,dirs[Rnd(0,4)])
			Select dir
				Case "up"
					y-=1
					If y<3 Then Return
					If map[x,y-1] = 1 Then Return
					map[x,y] = 1
				Case "down"
					y+=1
					If y>100-3 Then Return
					If map[x,y+1] = 1 Then Return
					map[x,y] = 1
				Case "right"
					x+=1
					If x>100-3 Then Return
					If map[x+1,y] = 1 Then Return
					map[x,y] = 1
				Case "left"
					x-=1
					If x<3 Then Return
					If map[x-1,y] = 1 Then Return
					map[x,y] = 1
			End Select
		Next
		makehall(x,y,dirs[Rnd(0,4)])
	End Method
	
End Class

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End Function
