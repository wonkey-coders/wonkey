#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


'
' This is the tile class.
' Here a stone tile is created
' using the generate method
Class tile
	Field width:Int,height:Int
	Field map:Int[,]
	Method New(w:Int,h:Int)
		Self.width = w
		Self.height = h
		map = New Int[width,height]
	End Method
	Method generate(spacing:Int)
		' Put a number of stone points on the map
		' try to keep a distance between them
		Local numpoints:Int=Rnd(width/5,width/2)
		For Local i:Int=0 Until numpoints
			Local x:Int=Rnd(width)
			Local y:Int=Rnd(height)
			Local exitloop:Bool=False
			While exitloop=False
				exitloop = True
				If disttootherstone(x,y,i) < spacing
				x=Rnd(width)
				y=Rnd(height)
				exitloop=False
				End If
			Wend
			map[x,y] = i
		Next
		'
		' Grow the stone points
		For Local i:Int=0 Until (width*height)*10
			Local x:Int=Rnd(width)
			Local y:Int=Rnd(height)
			If map[x,y] > 0
				If disttootherstone(x,y,map[x,y]) < spacing Then Continue  
				For Local y2:Int=y-1 To y+1
				For Local x2:Int=x-1 To x+1
					If x2<0 Or y2<0 Or x2>=width Or y2>=height Then Continue
					If Rnd(5)<2 Then 
					If map[x2,y2] = 0
						If x2 = 0 Then map[width-1,y2] = map[x,y]
						If x2 = width-1 Then map[0,y2] = map[x,y]
						If y2 = 0 Then map[x2,height-1] = map[x,y]
						If y2 = height-1 Then map[x2,0] = map[x,y]
						map[x2,y2] = map[x,y]
					End If
					End If
				Next
				Next
			End If
		Next
		
		shadeedges()
		
	End Method
	' Add ligther and darker pixels ontop of the stones
	' value 1 to <100 is each seperate stone
	' value 200 is light color 100 is dark color
	Method shadeedges()
		For Local y:Int=0 Until height
		For Local x:Int=0 Until width
			If map[x,y] > 0 And map[x,y] <> 200			
			If x-1 >=0 And map[x-1,y] = 0		
				For Local x2:Int=x+2 To x+4
					If Rnd(2)<1 
					If x2>=0 And x2<width And map[x2,y] >0 Then map[x2,y] = 100
					End If
				Next

			End If
			If x-1 >=0 And y-1>=0 And map[x-1,y-1] = 0
			map[x,y] = 100
			End If
			If x+1 < width And map[x+1,y] = 0
				For Local x2:Int=x-4 To x+2
					If Rnd(2)<1 
					If x2>=0 And x2<width And map[x2,y] >0 Then map[x2,y] = 200
					End If
				Next

			End If
			End If
		Next
		Next
	End Method
	' Returns the shortest distance to any other stone part then
	' the currentstore
	Method disttootherstone:Int(sx:Int,sy:Int,currentstone:Int)
		Local shortest:Int=9999
		For Local y:Int=0 Until height
		For Local x:Int=0 Until width
			If map[x,y] <> 0 And map[x,y] <> currentstone
				Local d:Int=distance(sx,sy,x,y)
				If d<shortest Then shortest = d
			End If
		Next
		Next
		Return shortest
	End Method
	' Draw the tile at x and y position and tw=size
	Method draw(canvas:Canvas,sx:Int,sy:Int,tw:Int,th:Int)
		Local x:Int
		Local y:Int
		

		For y=0 Until height
		For x=0 Until width
			Local t:Int=map[x,y]
			Local x2:Int=x*tw
			Local y2:Int=y*th
			x2+=sx
			y2+=sy
			
			If t >= 1 Then 'grey base color
				canvas.Color = New Color(.6,.6,.6)
			End If
			If t=100 Then canvas.Color = New Color(.2,.2,.2) 'dark shade color
			If t=200 Then canvas.Color = New Color(.8,.8,.8) 'light shade color
			If t>0  ' draw a rect (part of the stone)
			canvas.DrawRect(x2,y2,tw,th)
			End If
		Next
		Next
	
	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function	
End Class



Class MyWindow Extends Window
	Field mytile:tile
	Field cnt:Int=0
	Field timer:Timer
	
	Method New()
    	timer = New Timer(1,OnUpdate)
        mytile = New tile(32,32)
        mytile.generate(6)	

	End Method

	Method OnUpdate()
		If Keyboard.KeyDown(Key.Escape) Then App.Terminate()

    	cnt+=1  
    	If Keyboard.KeyReleased(Key.Space) Or cnt>3
    		cnt = 0
	        mytile = New tile(32,32) 'reset/create new tile
	        Local spacing:Int=Rnd(4,10)  ' set random spacing
	        If Rnd(3)<1 Then spacing=4
    	    mytile.generate(spacing)	' generate the tile
    	End If

		App.RequestRender()
	End Method
		
	Method OnRender( canvas:Canvas ) Override
    	canvas.Clear(Color.Black)
        'draw the tiles in 4x the size
		For Local y:Int=0 Until Height Step 32*4
		For Local x:Int=0 Until Width Step 32*4
        mytile.draw(canvas,x,y,4,4)
        Next
        Next
        ' draw the tiles in 1x size
        canvas.Color = Color.Black
        canvas.DrawRect(320,240,320,240)
		For Local y:Int=240 Until Height Step 32
		For Local x:Int=320 Until Width Step 32
        mytile.draw(canvas,x,y,1,1)
        Next
        Next
	
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
