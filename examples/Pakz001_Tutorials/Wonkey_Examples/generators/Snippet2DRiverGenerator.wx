' 2d top down map generator RIVER(S)

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	' Our map (tile)array
	Field map:Int[,]
	' Our dimension variables
	Field mapwidth:Int,mapheight:Int
	' tilewidth and height variables
	Field tw:Float,th:Float
	
	Method New()
		' Randomize seed
		SeedRnd(Microsecs())
		' generate new map
		newmap()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Space to generate new map
		If Keyboard.KeyReleased(Key.Space) Then newmap()
		
		'Draw our map to the screen
		drawmap(canvas)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		
		' draw some screen info
		canvas.Color = Color.Black
		canvas.DrawText("Press SPACE to generate new RIVER map.",0,0)
	End Method	
	
	'This method generates a new map
	Method newmap()
		' Get a random map width/height'		
		Local dimension:Int=Rnd(20,64)
		' Create our map array
		map = New Int[dimension,dimension]
		' Store our width and height in the variables
		mapwidth = dimension
		mapheight = dimension
		' Store our tile width and height variables
		tw = Float(Width) / Float(mapwidth)
		th = Float(Height) / Float(mapheight)
		' Create our new river
		generateriver() 
		
	End Method
	
	' This method generates a new river on the map
	Method generateriver()
		' We start with a random point somewhere middish on the map.
		' We create 2 sets of 2 variables for this
		Local x1:Float,y1:Float
		Local x2:Float,y2:Float
		x1 = Rnd(4,mapwidth-4)
		y1 = Rnd(4,mapheight-4)
		x2 = x1
		y2 = y1
		' We want the river to go from this starting point into two different
		' directions. We create 2 angle float variables for this.
		Local angle1:Float=Rnd(TwoPi)
		Local angle2:Float=Rnd(TwoPi)
		' We have a river that has a variable width.
		Local riverwidth:Int=1
		'
		' Here we start drawing a randomish line into the FIRST direction. 
		Repeat
			' Move this end of the river
			x1+=Cos(angle1)
			y1+=Sin(angle1)
			' Slightly turn the direction of the river
			angle1+=Rnd(-.3,.3)
			' If the river ends its turn on the end of the map
			' then exit our loop(done)
			If x1<0 Or x1>=mapwidth Or y1<0 Or y1>=mapheight Then Exit
			' Draw our river to the map..
			' Every loop cycle change the river width
			If Rnd()<.2 Then riverwidth = Rnd(1,3)
			For Local y:Int=y1-riverwidth To y1+riverwidth
			For Local x:Int=x1-riverwidth To x1+riverwidth
				If x>=0 And x<mapwidth And y>=0 And y<mapheight Then map[x,y] = 1
			Next
			Next
		Forever
		' Here we start drawing a randomish line into the SECOND direction. 
		Repeat
			' Move this end of the river
			x2+=Cos(angle2)
			y2+=Sin(angle2)
			' Slightly turn the direction of the river
			angle2+=Rnd(-.3,.3)
			' If the river ends its turn on the end of the map
			' then exit our loop(done)
			If x2<0 Or x2>=mapwidth Or y2<0 Or y2>=mapheight Then Exit
			' Draw our river to the map..
			' Every loop cycle change the river width
			If Rnd()<.2 Then riverwidth = Rnd(1,3)
			For Local y:Int=y2-riverwidth To y2+riverwidth
			For Local x:Int=x2-riverwidth To x2+riverwidth
				If x>=0 And x<mapwidth And y>=0 And y<mapheight Then map[x,y] = 1
			Next
			Next
		Forever

	End Method
	
	' This method draws the map to the screen.
	Method drawmap(canvas:Canvas)		
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Select map[x,y]
				Case 0 ' grass
					canvas.Color = Color.Green
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
				Case 1 ' river
					canvas.Color = Color.Blue
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
			End Select
		Next
		Next
	End Method 
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
