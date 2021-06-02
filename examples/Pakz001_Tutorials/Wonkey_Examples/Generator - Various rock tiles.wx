#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Global tilewidth:Int=20
Global tileheight:Int=20

'
' This is the tile class.
' Here a stone tile is created
' using the generate method
Class tile
	Field image:Image[,] = New Image[10,5]
	
	Field icanvas:Canvas[,] = New Canvas[10,5]

	Field width:Int,height:Int
	Field map:Int[][]
	Field a:Int[][]
	Field tile:Int[][][]
	Method New(w:Int,h:Int)
		Self.width = w
		Self.height = h
		map = New Int[width][]
		For Local i:Int=0 Until width
			map[i] = New Int[height]
		Next	
		tile = New Int[width][][]
        For Local i:Int = 0 Until width
            tile[i] = New Int[height][]
            For Local z:Int=0 Until height
                tile[i][z] = New Int[10]
            Next
        Next
        
        For Local ii:Int=0 Until 3
        For Local i:Int=0 Until 10
	        
		image[i,ii]=New Image( tilewidth,tileheight,TextureFlags.Mipmap|TextureFlags.Dynamic )
		image[i,ii].Handle=New Vec2f( 0,0 )
		icanvas[i,ii]=New Canvas( image[i,ii] )        	
		Next
		Next
	End Method
	Method create()
		Local col:Color[]=New Color[10]
		col[0] = New Color(0,0,0)
		col[1] = Color.Grey
		col[2] = Color.Brown
		col[3] = Color.Blue
		col[4] = Color.Gold
		col[5] = Color.SeaGreen
		For Local ii:Int=0 Until 3
		For Local i:=0 Until 10
			draw(icanvas[i,ii],i,0,0,1,1,col[ii])
			icanvas[i,ii].Flush()
		Next
		Next
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
			map[x][y] = i
		Next
		'
		growstone(spacing)
		copyintotile(0)
		shadeedges(0)
		'
		For Local i:Int=1 Until 5
		preparecenter(spacing)
		growstone(spacing)		
		copyintotile(i)
		shadeedges(i)
		Next
		
	End Method
	
	Method copyintotile(num:Int)
		For Local y:Int=0 Until height
		For Local x:Int=0 Until width
			tile[x][y][num] = map[x][y]
		Next
		Next
	End Method


	Method preparecenter(spacing:Int)
		'
		' Erase the center and create a new center
		'
		For Local y:Int=2 Until height-2
		For Local x:Int=2 Until width-2
			map[x][y] = 0
		Next
		Next
		' Create a few new points
		Local numpoints:Int=Rnd(1,4)
		For Local i:Int=40 Until 40+numpoints
			'map[Rnd(9,width-9)][Rnd(9,height-9)] = i
			Local x:Float=Rnd(9,width-9)
			Local y:Float=Rnd(9,height-9)
			Local angle:Int=Rnd(360)
			Local d:Int=Rnd(3,(width+height)/5)
			For Local ii:Int=0 Until d
				x+=Cos(angle)*1
				y+=Sin(angle)*1
				map[x][y] = i
				For Local iii:Int=0 Until 2
					map[x+Rnd(-2,2)][y+Rnd(-2,2)] = i
				Next
				If disttootherstone(x,y,i) < spacing Then Exit
			Next
		Next
		'

	End Method

	Method growstone(spacing:Int)	
		' Grow the stone points
		For Local i:Int=0 Until (width*height)*10
			Local x:Int=Rnd(width)
			Local y:Int=Rnd(height)
			If map[x][y] > 0
				If disttootherstone(x,y,map[x][y]) < spacing Then Continue  
				For Local y2:Int=y-1 To y+1
				For Local x2:Int=x-1 To x+1
					If x2<0 Or y2<0 Or x2>=width Or y2>=height Then Continue
					If Rnd(5)<2 Then 
					If map[x2][y2] = 0
						If x2 = 0 Then map[width-1][y2] = map[x][y]
						If x2 = width-1 Then map[0][y2] = map[x][y]
						If y2 = 0 Then map[x2][height-1] = map[x][y]
						If y2 = height-1 Then map[x2][0] = map[x][y]
						map[x2][y2] = map[x][y]
					End If
					End If
				Next
				Next
			End If
		Next
	End Method		
	
	' Add ligther and darker pixels ontop of the stones
	' value 1 to <100 is each seperate stone
	' value 200 is light color 100 is dark color
	Method shadeedges(mytile:Int)
		For Local y:Int=0 Until height
		For Local x:Int=0 Until width
			If tile[x][y][mytile] > 0 And tile[x][y][mytile] <> 200			
			If x-1 >=0 And tile[x-1][y][mytile] = 0		
				For Local x2:Int=x+2 To x+4
					If Rnd(2)<1 
					If x2>=0 And x2<width And tile[x2][y][mytile] >0 Then tile[x2][y][mytile] = 100
					End If
				Next

			End If
			If x-1 >=0 And y-1>=0 And tile[x-1][y-1][mytile] = 0
			tile[x][y][mytile] = 100
			End If
			If x+1 < width And tile[x+1][y][mytile] = 0
				For Local x2:Int=x-4 To x+2
					If Rnd(2)<1 
					If x2>=0 And x2<width And tile[x2][y][mytile] >0 Then tile[x2][y][mytile] = 200
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
			If map[x][y] <> 0 And map[x][y] <> currentstone
				Local d:Int=distance(sx,sy,x,y)
				If d<shortest Then shortest = d
			End If
		Next
		Next
		Return shortest
	End Method
	' Draw the tile at x and y position and tw=size
	Method draw(canvas:Canvas,thetile:Int,sx:Int,sy:Int,tw:Int,th:Int,col:Color)
		Local x:Int
		Local y:Int
		
		canvas.Clear(Color.Black)
		For y=0 Until height
		For x=0 Until width		
			Local t:Int
			t = tile[x][y][thetile]
			Local x2:Int=x*tw
			Local y2:Int=y*th
			x2+=sx
			y2+=sy
			
			If t >= 1 Then 'grey base color
				canvas.Color = New Color(.4,.4,.4).Blend(col,.5)
			End If
			If t=100 Then canvas.Color = New Color(.1,.1,.1).Blend(col,.5) 'dark shade color
			If t=200 Then canvas.Color = New Color(.7,.7,.7).Blend(col,.5)'light shade color
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


Global mytile:tile

Class MyWindow Extends Window

'	Field image:Image
'	
'	Field icanvas:Canvas	
	field map:Int[,] = New int[100,100]
	Method New()
'		image=New Image( 256,256,TextureFlags.Mipmap|TextureFlags.Dynamic )
'		image.Handle=New Vec2f( 0,0 )
'		icanvas=New Canvas( image )
'
'
'		icanvas.Color=Color.White
'		icanvas.DrawText( "This way up!",icanvas.Viewport.Width/2,0,.5,0 )
'		icanvas.Flush()
'
		For Local y:Int=0 Until 100
		For Local x:Int=0 Until 100
			map[x,y] = Rnd(4)
		Next
		Next
		mytile = New tile(tilewidth,tileheight)
		mytile.generate(3)
		mytile.create()

	End Method
	
	Method OnRender( canvas:Canvas ) Override

		App.RequestRender()

'		canvas.DrawImage( image,App.MouseLocation.x,App.MouseLocation.y,0,.5,.5 )
'		
'		canvas.DrawText( "Here!",0,0 )
'	
		Local t:Float=0
		For Local y:Int=0 Until Height Step tileheight
		For Local x:Int=0 Until Width Step tilewidth
		'Print map[x,y]
		t = (3.0/Height)*Float(y)
		canvas.DrawImage(mytile.image[map[x/tilewidth,y/tileheight],t],x,y)		
		Next
		Next
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
	End Method	
	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End function
