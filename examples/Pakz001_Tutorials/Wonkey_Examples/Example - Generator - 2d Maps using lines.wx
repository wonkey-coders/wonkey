#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' This is the map class. It contains the generating code
' and the code to draw the map to the screen.
''
Class map
	Field screenwidth:Int
	Field screenheight:Int
	Field mapwidth:Int
	Field mapheight:Int
	Field tilewidth:Float
	Field tileheight:Float
	Field map:Int[,]
	Field spacing:Int 'how much space should be inbetween the lines/walls
	Method New(sw:Int,sh:Int,mw:Int,mh:Int,spacing:Int)
		Self.screenwidth = sw
		Self.screenheight = sh
		Self.mapwidth = mw
		Self.mapheight = mh
		Self.tilewidth = Float(sw) / Float(mw)
		Self.tileheight = Float(sh) / Float(mh)
		map = New Int[mapwidth,mapheight]
		Self.spacing = spacing
		' Here we call the createmap method
		createmap()
	End Method
	'
	' Here we create a simple random map. 
	' We daw a line into a angled direction for a certain
	' distance and a couple of times we change the angle to create
	' non straight lines. We check to see if there are any previously
	' drawn lines near the current point of the line. The Spacing variable
	' is used to see how much space there needs to be between our lines.
	'
	Method createmap()		
		' Loop a number of times based on the size 
		' of the map
		For Local i:Int=0 Until (mapwidth+mapheight)
			' Get a random x and y spot on the map
			Local x:Float=Rnd(mapwidth)
			Local y:Float=Rnd(mapheight)
			' Chose an angle
			Local angle:Int=Rnd(TwoPi)
			' We will draw d into angle it's direction
			Local d:Int=Rnd(3,mapwidth/3)
			Local xitloop:Bool=False
			' We change the angle and distance 3 times
			For Local iii:Int=0 Until 3
			' Loop the distance
			For Local ii:Int=0 Until d				
				' If the current map location area has (a) previously drawn line point(s)
				' then stop drawing the current line
				If maptaken(x-spacing,y-spacing,spacing*2,spacing*2) Then xitloop=True ; Exit
				' Put value 2 into the map
				map[x,y] = 2
				' Next x and y position
				x+=Cos(angle)*1
				y+=Sin(angle)*1				
			Next
			' Exit the loop(spot taken)
			If xitloop=True Then Exit
			' Change angle and distance
			angle+=Rnd(-Pi/2,Pi/2)
			d=Rnd(3,mapwidth/3)
			Next
			' Turn all new drawn 2 value's into
			' value of 1 so they can be detected
			For Local y:Int=0 Until mapheight
			For Local x:Int=0 Until mapwidth
				If map[x,y] = 2 Then map[x,y] = 1
			Next
			Next
		Next
	End Method
	' See if the area selected is outside the
	' screen or if the map value is 1
	Method maptaken:Bool(x:Int,y:Int,w:Int,h:Int)
		For Local y2:Int=y Until y+h
		For Local x2:Int=x Until x+w
			If x2<0 Or x2>=mapwidth Or y2<0 Or y2>=mapheight Then Return True
			If map[x2,y2] = 1 Then Return True
		Next
		Next
		Return False
	End Method
	' Draw the map
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] = 0 Then Continue
			canvas.Color = Color.White
			Local x2:Int=x*tilewidth
			Local y2:Int=y*tileheight
			canvas.DrawRect(x2,y2,tilewidth+1,tileheight+1)
		Next
		Next
	End Method
End Class

Class MyWindow Extends Window
	
	Field mymap:map
	Field cnt:Int=0 'cnt is used to auto create new maps
	
	Method New()
		' Try to get a unique map every time
		SeedRnd(Microsecs())
		' Create a random map
		createrandommap()
	End Method
	
	' Our update method.
	' Here we create the new maps
	Method update:Void()
    	cnt+=1
    	If Keyboard.KeyReleased(Key.Space) Or cnt > 60*3
    		cnt=0
    		createrandommap()
    	End If 
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Call update method
		update()
		
        ' Draw the map
        canvas.Clear(Color.Black)
        mymap.draw(canvas)
        ' Drawn some info to the canvas
        canvas.Color = Color.Red
		Local mw:Int=mymap.mapwidth
		Local mh:Int=mymap.mapheight
		Local sp:Int=mymap.spacing
		canvas.DrawText("Width : "+mw+" Height : "+mh+" Spacing : "+sp,0,0)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	

	' This method create a new random map
	Method createrandommap:Void()
		Local size:Int=Rnd(20,200)
		mymap = New map(Width,Height,size,size,Rnd(2,6))
	End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
