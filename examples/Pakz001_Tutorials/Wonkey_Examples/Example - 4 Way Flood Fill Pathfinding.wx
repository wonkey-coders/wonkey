#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' This is a class that holds x and y variables.
Class pathnode
	Field x:Int,y:Int
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
	End Method
End Class

'Our map. it holds the walls(-1) and the distance
'from the start to end position.
Global cmap:Int[,]
' map width and height
Global mw:Int=20,mh:Int=20
' tile width and height
Global tw:Float=22,th:Float=18
' our start and end position
Global sx:Int,sy:Int,ex:Int,ey:Int
' this holds our path
Global path:List<pathnode>


Class MyWindow Extends Window
	Field timer:Timer
	Method New()
		timer = New Timer(1,OnUpdate)
		' create a new map array
		cmap = New Int[mw,mh]
        ' set the tile width and height.
        tw = Width / Float(mw)
        th = Height / Float(mh)
		ClearColor = Color.Black
	End Method
	
	Method OnUpdate()
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		App.RequestRender()
	End Method	
	
	Method OnRender( canvas:Canvas ) Override
		newmapandpath()
		draw(canvas)
	End Method	
	
End	Class

Function newmapandpath()
	' new map
	cmap = New int[mw,mh]
  	'draw some contents on the map
   	For Local x:=0 Until mw Step 5
   	For Local y:=2 Until mh-2
   		cmap[x,y] = -1
   	Next
   	Next
   	For Local i:=0 Until 5
   		Local x1:Int=Rnd(0,mw-4)
   		Local y1:Int=Rnd(0,mh-4)
   		For Local x2:=0 Until 4
   		For Local y2:=0 Until 4
   			cmap[x1+x2,y1+y2] = -1
   		Next
   		Next
   	Next
   	For Local y:=0 Until mh Step 5
 	For Local x:=0 Until mw
 		cmap[x,y] = 0
 	Next
   	Next

	'find start and end position
	Repeat
		sx = Rnd(0,mw)
		sy = Rnd(0,mh)
		ex = Rnd(0,mw)
		ey = Rnd(0,mh)
		If cmap[sx,sy] = 0 And cmap[ex,ey] = 0 
			If sx<>ex And sy<>ey
				Exit
			End If
		End If	
	Forever
	 	
	'flood the map with distance from
	'sx and sy
	' Create a list with a class inside it (the class has
	' the x and y variables)
	Local ol:List<pathnode> = New List<pathnode>
 	' Add the start position on the list
 	ol.AddLast(New pathnode(sx,sy))
 	' set the cloes map at the start position to distance 1
 	cmap[sx,sy] = 1
 	' some helper arrays. We can determine the top,right,and bottom
 	' and left position cells with these numbers.
 	Local dx:Int[] = New Int[](0,1,0,-1)
 	Local dy:Int[] = New Int[](-1,0,1,0)
 	' While there is contents in the list
 	While ol.Count() <> 0
 		' Get the current location
 		Local x1:Int=ol.First.x
 		Local y1:Int=ol.First.y
 		' Remove the current location from the list
 		ol.RemoveFirst()
 		' Get 4 new positions around the current positions
		For Local i:=0 Until 4
			' Set new x and y
			Local nx:Int=x1+dx[i]
			Local ny:Int=y1+dy[i]
			' If the coordinates are inside the map
			If nx>=0 And ny>=0 And nx<mw And ny<mh
			' If the closedmap is not written to yet
 			If cmap[nx,ny] = 0 
 				' Set the new distance based on the current distance
 				cmap[nx,ny] = cmap[x1,y1] + 1
 				' Add new position to the list
 				ol.AddLast(New pathnode(nx,ny))
 			End If
 			End If
		Next
 	Wend
 	 
	' Make the path. Here we start at the end position
	' and find the lowest value around our current position
	' and so on until we are at the start position.
	' Get the current position
	Local x1:Int=ex,y1:Int=ey
	' Reset our path list
	path = New List<pathnode>
	' Set the first path contents(end x and y)
	path.AddLast(New pathnode(x1,y1))
	' Little counter for if we enter an infinite loop
 	Local cnt:Int=0
 	' While we are not near the map distance of 1
	While cmap[x1,y1] > 1		
		' Get tge current poditions distance	
		Local lowest:Int=cmap[x1,y1]
		' Create 2 new variables that hold the new location
		Local nx:Int,ny:Int
		' If the position left of our current position is on the map
		' and is not a wall and has a distance smaller that of our
		' current position.
		If x1-1>=0 And cmap[x1-1,y1]>-1 And cmap[x1-1,y1] < lowest Then 
			' set new position
			nx=x1-1
			ny=y1
			' set new lowest variable
			lowest = cmap[nx,ny]
		End If
		' If the position right of our current position is on the map
		' and is not a wall and has a distance smaller that of our
		' current position.
		If x1+1<mw And cmap[x1+1,y1]>-1 And cmap[x1+1,y1] < lowest
			nx=x1+1
			ny=y1
			lowest = cmap[nx,ny]
		End If
		' If the position top of our current position is on the map
		' and is not a wall and has a distance smaller that of our
		' current position.
		If y1-1>=0 And cmap[x1,y1-1]>-1 And cmap[x1,y1-1] < lowest
			nx=x1
			ny=y1-1
			lowest = cmap[nx,ny]
		End If
		' If the position at the bottom of our current position is on the map
		' and is not a wall and has a distance smaller that of our
		' current position.
		If y1+1 < mh And cmap[x1,y1+1]>-1 And cmap[x1,y1+1] < lowest
			nx=x1
			ny=y1+1
			lowest = cmap[nx,ny]
		End If
		' Here we should have a new position so we put it into 
		' our current position
		x1 = nx
		y1 = ny
		' Add the next position to the bottom of our path list
		path.AddLast(New pathnode(x1,y1))
		' If we can not go anywhere then exit this loop if we have done
		' a thousand loops.
		cnt+=1
		If cnt>1000 Then Exit
	Wend
   	 
 	 
End Function

Function draw(canvas:Canvas)
	'draw the map
    For Local y:=0 Until mh
    For Local x:=0 Until mw
    	If cmap[x,y] = -1 Then
    		canvas.DrawRect(x*tw,y*th,tw,th)
    	End If
    Next
    Next
    'draw the path
    If path
    For Local i:=Eachin path
    	canvas.Color = Color.Yellow
    	canvas.DrawRect(i.x*tw,i.y*th,tw,th)
    	canvas.Color = Color.Black
    	canvas.DrawText(cmap[i.x,i.y],i.x*tw,i.y*th)
    Next
    End If
    'Draw the end and start position
    canvas.Color = Color.Red
    canvas.DrawRect(sx*tw,sy*th,tw,th)
    canvas.DrawRect(ex*tw,ey*th,tw,th)
    
    canvas.Color = Color.White
    canvas.DrawText("FloodFill pathfinding",0,0	)
	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
