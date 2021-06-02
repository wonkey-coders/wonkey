#Import "<std>"
#Import "<mojo>"

' Bitwise
'

'         1
'     	+++++
'	  8 +++++ 2
'		+++++
'         4 
'
' blocks of + is our tile. The numbers around it you add up to get the tile 
' to draw on that + position.
'
' If a tile is above and right we get the number 1+2
' If a tile is left and below and right we get the number 8+4+2
'



Using std..
Using mojo..

Global mapwidth:Int=20
Global mapheight:Int=15

Class MyWindow Extends Window
	Field map:Int[,]
	Field tilemap:Int[,]
	Field tilewidth:Int,tileheight:Int
	Method New()
		map = New Int[mapwidth,mapheight]
		tilemap = New Int[mapwidth,mapheight]
		tilewidth = Width/mapwidth
		tileheight = Height/mapheight
		
		map[5,5] = 1 'all surrounded
		map[4,5] = 1
		map[5,6] = 1
		map[6,5] = 1
		map[5,4] = 1
		
		map[15,6] = 1 'right and below
		map[16,6] = 1
		map[15,7] = 1
		
		map[5,10] = 1 'left bottom and top
		map[4,10] = 1
		map[5,11] = 1
		map[5,9] = 1
		
		createtilemap()
		
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Grey)
		drawmap(canvas)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	

	Method createtilemap()
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] = 1
				'
				' Here we calculate which tile should be drawn at the current position.
				' This is done by reading above/right/bottom and left of the current position.
				' If above is a tile then we increate the value with 1 and right+2 bottom+4
				' and left +8. 
				Local bitwise:Int=0
				If map[x,y-1] = 1 Then bitwise+=1
				If map[x+1,y] = 1 Then bitwise+=2
				If map[x,y+1] = 1 Then bitwise+=4
				If map[x-1,y] = 1 Then bitwise+=8
				tilemap[x,y] = bitwise+1
			End If
		Next
		Next
	End Method
	
	Method drawmap(canvas:Canvas)
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If tilemap[x,y]>0 Then drawtile(canvas,tilemap[x,y],x*tilewidth,y*tileheight)
		Next
		Next
	End Method

	Method drawtile(canvas:Canvas,num:Int,x:Int,y:Int)
		num-=1
		canvas.Color = Color.Blue
		canvas.DrawRect(x,y,tilewidth,tileheight)
		canvas.Color = Color.White
		canvas.DrawRect(x+1,y+1,tilewidth-2,tileheight-2)
		canvas.Color = Color.White
		Select num
			Case 0 'naked block				
			Case 1 'block above present
				canvas.DrawLine(x,y,x+tilewidth,y)
			Case 2 'block right present
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)
			Case 3 'above and right present
				canvas.DrawLine(x,y,x+tilewidth,y)
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)
			Case 4 'block below present				
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)'below
			Case 5 'above and below present
				canvas.DrawLine(x,y,x+tilewidth,y)
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)
			Case 6 'right and below present
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)
			Case 7 'top and right and below present
				canvas.DrawLine(x,y,x+tilewidth,y)'top
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)'right
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)'below
			Case 8 'block left present
				canvas.DrawLine(x,y,x,y+tileheight)'left
			Case 9 'left and above present
				canvas.DrawLine(x,y,x,y+tileheight)''left
				canvas.DrawLine(x,y,x+tilewidth,y)'above
			Case 10 'left and right present
				canvas.DrawLine(x,y,x,y+tileheight)'left
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)'right
			Case 11 'left and right and above
				canvas.DrawLine(x,y,x,y+tileheight)'left
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)'right
				canvas.DrawLine(x,y,x+tilewidth,y)'above
			Case 12 'left and below present
				canvas.DrawLine(x,y,x,y+tileheight)'left
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)'below
			Case 13 'left and below and top
				canvas.DrawLine(x,y,x,y+tileheight)'left
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)'below
				canvas.DrawLine(x,y,x+tilewidth,y)'top
			Case 14'left and below and right
				canvas.DrawLine(x,y,x,y+tileheight)'left
				canvas.DrawLine(x,y+tileheight-1,x+tilewidth,y+tileheight-1)'below
				canvas.DrawLine(x+tilewidth-1,y,x+tilewidth-1,y+tileheight-1)'right
			Case 15'all surrounded
				canvas.DrawRect(x,y,tilewidth,tileheight)

		End Select
	End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
