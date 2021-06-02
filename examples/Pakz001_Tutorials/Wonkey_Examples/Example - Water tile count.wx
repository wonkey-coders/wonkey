#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field map:Int[,]
	Field tw:Float,th:Float
	Field mw:Int=32,mh:Int=32
	Method New()
		tw = Float(Width)/Float(mw)
		th = Float(Height)/Float(mh)
		map = New Int[mw,mh]
		makemap()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		drawmap(canvas) 
		' If we press the mouse on the map then execute 
		' the method. (print the returnvale to the console)
		If Mouse.ButtonReleased(MouseButton.Left)
			Print waterarea(Mouse.X/tw,Mouse.Y/th)
		End If
		' 
		canvas.Color = Color.Black
		canvas.DrawText("Press the Left Mouse button on water for it's surface.",0,0)
		'
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	' This method returns the size of the water. How much 
	' connected tiles it has. (Water in this example is
	' tile <=5)
	'
	Method waterarea:Int(x:Int,y:Int)
		' If the input tile is not water then exit this method
		If map[x,y] > 5 Then return -1
		' This value returns the amount of tiles
		' that are connected to water.
		Local retval:Int=1
		' These are the variables for the
		' floodfill.
		Local floodx:Stack<Int> = New Stack<Int>
		Local floody:Stack<Int> = New Stack<Int>
		Local floodmap:Bool[,] = New Bool[mw,mh]
		floodx.Push(x)
		floody.Push(y)
		floodmap[x,y] = True
		Local currentx:Int=x,currenty:Int=y
		Repeat
			'If the stack is empty then exit the loop
			If floodx.Length = 0 Then Exit
			' Get the first value from the stack
			currentx = floodx.Top
			currenty = floody.Top
			' Remove the first value from the stack
			floodx.Pop()
			floody.Pop()
			'Loop 8 way direction
			For Local y2:=-1 To 1
			For Local x2:=-1 To 1
				Local x3:Int=currentx+x2
				Local y3:Int=currenty+y2
				If x3>=0 And y3>=0 And x3<mw And y3<mh 'if within the array
				If floodmap[x3,y3] = False' if it has not been flooded before
				If map[x3,y3] <= 5 ' if it is a water tile.
					floodx.Push(x3) 'push new value to the stack
					floody.Push(y3)
					floodmap[x3,y3] = True 'set the floodmap to true 
					retval+=1 'mass+1
				End If
				End If
				End If
			Next
			Next
		Forever
		Return retval 'return the size of the area
	End Method
	
	' Create a random map (hill algorithm)
	Method makemap()
		Local exitloop:Bool=False
		While exitloop=False
			Local x1:Int=Rnd(-10,mw)
			Local y1:Int=Rnd(-10,mh)
			Local w:Int=Rnd(1,12)
			Local h:Int=Rnd(1,10)
			For Local y2:=y1 To y1+h
			For Local x2:=x1 To x1+w
				If x2>=0 And x2<mw And y2>=0 And y2<mh
					map[x2,y2] = map[x2,y2] + 1
					If map[x2,y2] > 46 Then exitloop = True
				End If
			Next
			Next		
		Wend
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			map[x,y] = (10.0/46)*map[x,y]
		Next
		Next
	End Method
	' Draw the map on the canvas
	Method drawmap(canvas:Canvas)
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local col:Float=0
			col = Float(map[x,y])/20
			If map[x,y]>5
				canvas.Color = New Color(col,1,col)
				Else
				canvas.Color = New Color(col,col,1)
			End If
			canvas.DrawRect(x*tw,y*th,tw,th)
		Next
		Next
	End Method
End	Class
	
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
