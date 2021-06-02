#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global sw:Int,sh:Int

Class tiles
	Field tw:Float,th:Float
	Method New(tw:Float,th:Float)
		Self.tw = tw
		Self.th = th
	End Method
	Method drawtile(canvas:Canvas,tile:Int,x:Int,y:Int)
		Select tile
			Case 0 'ground
				canvas.Color = Color.Green.Blend(Color.Brown,.6)
				canvas.DrawRect(x,y,tw,th)
			Case 10 'wallleftop
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y,x+tw,y)
				canvas.DrawLine(x,y,x,y+th)
			Case 11 'wallrighttop
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y,x+tw,y)
				canvas.DrawLine(x+tw-2,y,x+tw-2,y+th)
			Case 12 'walllefbottom
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y+th-1,x+tw-1,y+th-1)
				canvas.DrawLine(x,y,x,y+th-1)
			Case 13 'wallrightbottom
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y+th-2,x+tw-1,y+th-2)
				canvas.DrawLine(x+tw-1,y,x+tw-1,y+th-1)
			Case 14 'wall horizona
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y,x+tw,y)
				canvas.DrawLine(x,y+th-2,x+tw-2,y+th-2)
			Case 15 ' wall vertical
				canvas.Color = Color.Grey
				canvas.DrawRect(x,y,tw,th)
				canvas.Color = Color.White
				canvas.DrawLine(x,y,x,y+th)
				canvas.DrawLine(x+tw-2,y,x+tw-2,y+th)
		End Select
	End Method	
End Class

Class basegenerator
	Field w:Int,h:Int
	Field tw:Float,th:Float
	Field map:Int[,]
	Method New(w:Int,h:Int)
		Self.w = w
		Self.h = h
		Self.tw = Float(sw)/Float(w)
		Self.th = Float(sh)/Float(h)
		map = New Int[w,h]
		phase1(1,0)
		phase1(0,1)
		phase1(-1,0)
		phase1(0,-1)		
		phase2()
		phase3()
		tilecreate()
	End Method
	Method tilecreate()
		' set left top walls
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			If map[x,y] = 2 'left top wall
				If map[x-1,y] = 0
				If map[x,y-1] = 0
				If map[x-1,y-1] = 0
					map[x,y] = 10
				End If
				End if
				End If
			End If
			If map[x,y] = 2 'right top wall
				If map[x+1,y] = 0
				If map[x,y-1] = 0
				If map[x+1,y-1] = 0
					map[x,y] = 11
				End If
				End if
				End If
			End If
			If map[x,y] = 2 'left bottom wall								
				If map[x-1,y] = 0
				If map[x,y+1] = 0
				If map[x-1,y+1] = 0
					map[x,y] = 12
				End If
				End if
				End If				
			End If
			If map[x,y] = 2 'right bottom wall
				If map[x+1,y] = 0
				If map[x,y+1] = 0
				If map[x+1,y+1] = 0
					map[x,y] = 13
				End If
				End If
				End If
			End If
			If map[x,y]	= 2 'wall horizonat
				If map[x,y-1] = 0
				If map[x,y+1] = 0
					map[x,y] = 14
				End If
				End If
			End If
			If map[x,y]	= 2 'wall vertical
				If map[x-1,y] = 0
				If map[x+1,y] = 0
					map[x,y] = 15
				End If
				End If
			End If
			
		Next
		Next
	End Method
	Method counttilesaround:Int(x:Int,y:Int,tile:Int)
		Local out:Int=0
		For Local y1:Int=y-1 To y+1
		For Local x1:Int=x-1 To x+1
			If map[x1,y1] = tile Then out+=1
		Next
		Next
		Return out
	End Method
	' Find road points that must be extended to go through walls
	Method phase3()
		For Local y:Int=2 Until h-2
		For Local x:Int=2 Until w-2
			If map[x,y] = 1
				Local cnt:Int=0
				For Local y2:Int=y-1 To y+1
				For Local x2:Int=x-1 To x+1
					If map[x2,y2] = 1 Then cnt+=1
				Next
				Next				
				'if the count is 2 that means we have a end point road
				'we will extend it for a few steps so it goes through the wall
				' creating a gate
				If cnt=2
					If map[x+1,y]=1 
						If map[x-2,y] = 2 And map[x-3,y] = 0
							map[x-1,y]=1
							map[x-2,y]=1
							map[x-3,y]=1
						End if
						Exit
					End If
					If map[x-1,y]=1 
						If map[x+2,y] = 2 And map[x+3,y] = 0
							map[x+1,y]=1
							map[x+2,y]=1
							map[x+3,y]=1
						End If
						Exit					
					End If
					If map[x,y+1]=1
						If map[x,y-2] = 2 And map[x,y-3] = 0
							map[x,y-1] = 1
							map[x,y-2] = 1
							map[x,y-3] = 1
						End If
					End if
					If map[x,y-1]=1
						If map[x,y+2] = 2 And map[x,y+3] = 0
							map[x,y+1] = 1
							map[x,y+2] = 1
							map[x,y+3] = 1
						End If
					End if

				End If
			End If				
		Next
		Next
	End Method
	'walls
	Method phase2()
		' Here we thicken the map so the walls are a little
		' bit away from the roads
		
		' First keep a copy of the map
		Local tmpmap:Int[,] = New Int[w,h]
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			tmpmap[x,y] = map[x,y]
		Next
		Next
		'
		' here we find the edges for spacing the walls		
		Local tmpmap2:Int[,] = New Int[w,h]
		For Local x:Int=0 Until w
		For Local y:Int=0 Until h
			If map[x,y] = 1 Then
			For Local x2:Int=x-1 To x+1
			For Local y2:Int=y-1 To y+1
				tmpmap2[x2,y2] = 1
			Next
			Next
			End If
		Next
		Next
		For Local x:Int=0 Until w
		For Local y:Int=0 Until h
			map[x,y] = tmpmap2[x,y]
		Next
		Next
		
		
		'flood fill to find edges and turn these into walls(2)
		Local ox:Stack<Int> = New Stack<Int>
		Local oy:Stack<Int> = New Stack<Int>
		Local cmap:Int[,] = New Int[w,h]
		ox.Push(0)
		oy.Push(0)
		cmap[0,0] = 1
		While ox.Length
			Local tx:Int=ox.Get(0)
			Local ty:Int=oy.Get(0)		
			ox.Erase(0)
			oy.Erase(0)
			For Local y:Int=-1 To 1
			For Local x:Int=-1 To 1
				Local nx:Int=tx+x
				Local ny:Int=ty+y
				If nx<0 Or nx>w-1 Or ny<0 Or ny>h-1 Then Continue
				If cmap[nx,ny] = 0 And map[nx,ny] = 0 
					ox.Push(nx)
					oy.Push(ny)
					cmap[nx,ny] = 1		
				End If
			Next
			Next
		Wend
		' He we actually place the walls
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			If map[x,y]=1 
				For Local x1:Int=-1 To 1
				For Local y1:Int=-1 To 1
					If cmap[x+x1,y+y1] = 1 Then 
						map[x+x1,y+y1] = 2						
					End If
				Next
				Next
			End If
		Next
		Next
		
		'erase roads
		For Local x:Int=0 Until w
		For Local y:Int=0 Until h
			If map[x,y] = 1 Then map[x,y] = 0
		Next
		Next
		'pu told roads back
		For Local x:Int=0 Until w
		For Local y:Int=0 Until h
			If tmpmap[x,y] = 1 Then map[x,y] = 1
		Next
		Next
		
	End Method
	' roads
	' randomly draw lines into 1 of four directions and keep
	' doing this for a certain number of times
	Method phase1(xa:Int,ya:Int)
		' get center of map
		' (remember that maps can be temps and be later pasted
		' inside other maps)
		Local x:Int=w/2
		Local y:Int=h/2
		map[x,y] = 1
		Local depth:Int=Rnd(6,20)
		For Local i:Int=0 Until depth
			Local d:Int=Rnd(5,10)
			Local dx:Int=Rnd(-2,2)			
			Local dy:Int=0
			If dx=0 And dy=0 Then dy=1
			If dy=1 And Rnd()<.5 Then dy=-dy

  			If xa<>0 Then dx = xa ; xa=0 ; ya=0 ; dy=0
			If ya<>0 Then dy = ya ; ya=0 ; xa=0 ; dx=0
			
			For Local i2:Int=0 Until d
				x+=dx
				y+=dy
				map[x,y] =1
				If x+8>w Then dx=-1;dy=0
				If x-8<0 Then dx=1;dy=0
				If y+8>h Then dy=-1;dx=0
				If y-8<0 Then dy=1;dx=0
			Next
		Next
	End Method
	Method drawmap(canvas:Canvas)
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			'If map[x,y] = 0 Then Continue
			Local dx:Int=x*tw
			Local dy:Int=y*th

			Select map[x,y]
				Case 0 'ground
				
				'canvas.Color = Color.Brown.Blend(Color.Green,.5)
				'canvas.DrawRect(dx,dy,tw+1,th+1)				
				canvas.Color = Color.White
				mytile.drawtile(canvas,0,dx,dy)
				Case 1 'roads
				canvas.Color = Color.Grey.Blend(Color.Black,.5)
				canvas.DrawRect(dx,dy,tw+1,th+1)
				Case 2 'walls or water
				canvas.Color = Color.Blue
				canvas.DrawRect(dx,dy,tw+1,th+1)
				Case 10 'wallcornerlefttop
				canvas.Color = Color.White
				mytile.drawtile(canvas,10,dx,dy)
				Case 11 'wallcornerrighttop
				canvas.Color = Color.White
				mytile.drawtile(canvas,11,dx,dy)
				Case 12 'wallcornerleftbottom
				canvas.Color = Color.White
				mytile.drawtile(canvas,12,dx,dy)
				Case 13 'wallcornerrightbottom
				canvas.Color = Color.White
				mytile.drawtile(canvas,13,dx,dy)
				Case 14 'wallhor
				canvas.Color = Color.White
				mytile.drawtile(canvas,14,dx,dy)
				Case 15 'wallver
				canvas.Color = Color.White
				mytile.drawtile(canvas,15,dx,dy)

			End Select
		Next
		Next
	End Method
End Class


Global mytile:tiles

Class MyWindow Extends Window
	Field mymap:basegenerator	
	Method New()
		SeedRnd(Microsecs())
		sw = Width
		sh = Height		
		mymap = New basegenerator(50,50)
		mytile = New tiles(mymap.tw,mymap.th)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		mymap.drawmap(canvas)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.Space) Then mymap = New basegenerator(50,50)
	End Method	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
