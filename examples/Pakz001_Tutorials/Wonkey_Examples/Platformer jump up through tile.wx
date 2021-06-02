
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class map
    Field map:Int[][]
    Field mapwidth:Int
    Field mapheight:Int
	Field tilewidth:Int
	Field tileheight:Int
    Field screenwidth:Int
    Field screenheight:Int
	Method New(screenwidth:Int,screenheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		setlevel1()
	End Method
	Method setlevel1()
    	map = New Int[][] (
        New Int[]( 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 1, 1, 1, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 1, 1, 1, 1, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 1, 1, 1, 1, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 0, 0, 0, 0, 0, 0, 0, 0, 2 ),
        New Int[]( 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 ) )		
        mapwidth = map[0].Length
        mapheight = map.Length
	End Method
End Class

Class player
	' player x and y
	Field px:Float
	Field py:Float
	' player widht and heigth
	Field pw:Int
	Field ph:Int
	' How fast left move and right
	Field horspeed:Int=3
	' gravity variables
	Field incy:Float=0
	Field falling:Bool=False
	Field jumping:Bool=False
	Method New(x:Int,y:Int,w:Int,h:Int)
		px = x
		py = y
		pw = w
		ph = h
	End Method
	' Player controls
	Method controls()
		' Left and right movement (horspeed is the speed left and right)
		For Local i:Int=0 Until horspeed
			' If we are jumping or falling then we only want to be
			' stopped by tile number 2
			If jumping=True Or falling = True
				If Keyboard.KeyDown(Key.Right) And playertc(1,0,2) = False
					px += 1
				End If
				If Keyboard.KeyDown(Key.Left) And playertc(-1,0,2) = False
					px -= 1
				End If
			Else 'Here we are not jumping or falling so we want the 
				' collision with movement left and right to stop when
				' hitting any tile number.
				If Keyboard.KeyDown(Key.Right) And playertc(1,0,99) = False
					px += 1
				End If
				If Keyboard.KeyDown(Key.Left) And playertc(-1,0,99) = False
					px -= 1
				End If
			End if
		Next
		' Player jump when press space. We are not jumping or falling right now.
		If jumping=False And falling=False And Keyboard.KeyHit(Key.Space)
			jumping=True
			incy = 5			
		End If
	End Method
	' 
	' This method takes care of the falling and jumping for the player
	Method gravity()		
		' First check if we have something beneach us
		' and if not then fall down. Be sure we are
		' not falling or jumping right now.
		If falling = False And jumping=False 
			If playertc(0,1,99) = False 
				falling=True
				incy = 0								
			End If
		End If		
		' Code for when jumping state = true
		If jumping = True			
			incy-=.1
			For Local i:Int = 0 Until Ceil(incy)
				' If we are not jumping into a solid non jump through tile
				' then keep jumping
				If playertc(0,-1,2) = False
					py -= 1
				Else 'if we touched a tile we can not jump through then init
					 ' falling
					 incy=0
					 jumping = False
					 falling = True
					 Exit
				End If
			Next
			' If we run out of jump force(incy) then set to falling
			If incy<=0 Then 
				jumping=false
				falling=True
				incy=0
			End If
		End If
		' Code for when the falling state is true
		If falling=True Then
			incy+=.05
			For Local i:Int=0 Until Ceil(incy)
				' If we have nothing beneath us or are not inside anything
				' then keep falling
				If playertc(0,1,99) = False Or playertc(0,0,99) = True
					py+=1
				Else 'if we hit solid bottom
					falling = False
					Exit
				End If
			Next
		End If	
	End Method
	' Player versus tile collision (uses offsets x1 and y1)
	' Here we check if the player is inside any nearby tile around him.
	' x1 and y1 is the offset. This way we can check the player position
	' and a little bit around him.	
	Method playertc:Bool(x1:Int=0,y1:Int=0,tile:Int)
	    Local cx:Int = (px + x1) / mymap.tilewidth
	    Local cy:Int = (py + y1) / mymap.tileheight
	    For Local y2:Int=cy-1 Until cy+2
	    For Local x2:Int=cx-1 Until cx+2
	        If x2>=0 And x2<mymap.mapwidth And y2>=0 And y2<mymap.mapheight
		        ' If we check for tile = 99 then we check for any tile above value 0
		        If tile=99 Then
		            If mymap.map[y2][x2] > 0
		                If rectsoverlap(px+x1,py+y1,pw,ph,x2*mymap.tilewidth,y2*mymap.tileheight,mymap.tilewidth,mymap.tileheight) = True
		                    Return True
		                End If
		            End If
				Else 'Here we check the map we are inside of with the inputted tile number
		            If mymap.map[y2][x2] = tile
		                If rectsoverlap(px+x1,py+y1,pw,ph,x2*mymap.tilewidth,y2*mymap.tileheight,mymap.tilewidth,mymap.tileheight) = True
		                    Return True
		                End If
		            End If
				End If
	        End If
	    Next
	    Next
	    Return False
	End Method
	' Draw the player on the screen
	Method draw(canvas:Canvas)
		canvas.Color = Color.Blue
		canvas.DrawRect(px,py,pw,ph)
	End Method
	' Helper function
	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    	If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    	If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    	Return True
	End Function

End Class

Global myplayer:player
Global mymap:map

Class MyWindow Extends Window
	Method New()
		' Set The title of the window...
		Title="Tilemap example Array of Arrays....."
		mymap = New map(Width,Height)
		mymap.tilewidth = Width/mymap.map[0].Length
		mymap.tileheight = Height/mymap.map.Length
		myplayer = New player(4*mymap.tilewidth,4*mymap.tileheight,mymap.tilewidth/2,mymap.tileheight/2)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Clear with black color
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		'Draw the tilemap
		For Local y:Int=0 Until mymap.map.Length
		For Local x:Int=0 Until mymap.map[0].Length
			If mymap.map[y][x] > 0				
				canvas.DrawRect(x*mymap.tilewidth,y*mymap.tileheight,mymap.tilewidth,mymap.tileheight)
			End If
		Next
		Next		
		' Do the player controls and draw
		myplayer.controls()
		myplayer.gravity()
		myplayer.draw(canvas)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
