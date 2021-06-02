 

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class explosion
	Field l:Stack<particle>
	Class particle
		Field x:Float,y:Float
		Field incx:Float,incy:Float
		Field timeout:Int=500
		Field deleteme:Bool=False
		Method New(x:Int,y:Int,incx:Float,incy:Float)
			Self.x = x
			Self.y = y
			Self.incx = incx
			Self.incy = incy
		End Method
		Method update()
			timeout-=1
			If timeout < 0 Then deleteme = True
			x += incx
			y += incy
		End Method		
	End Class
	Method New(x:Int,y:Int)
		l.Push(New particle(x,y,Rnd(-3,3),Rnd(-3,3)))
		l.Push(New particle(x,y,Rnd(-3,3),Rnd(-3,3)))
		l.Push(New particle(x,y,Rnd(-3,3),Rnd(-3,3)))
		l.Push(New particle(x,y,Rnd(-3,3),Rnd(-3,3)))
	End Method
	Method update()
		For Local i:Int=0 Until l.Length
			l.Get(i).update()			
		Next
	End Method
	Method draw(canvas:Canvas,xpos:Int,ypos:Int)
	End Method
End Class

Class world
	Field map:Int[,]
	Field screenwidth:Int,screenheight:Int
	Field mapwidth:Int,mapheight:Int
	Field tilewidth:Int = 48
	Field tileheight:Int = 48
	Field tileshor:Int,tilesver:Int
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		tileshor = (screenwidth / tilewidth) + 2
		tilesver = (screenheight / tileheight) + 2
		getdungeon()
		adddungeonwalls()
				
	End Method	

	Method update()
	End Method

	Method adddungeonwalls()		
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] > 0
			For Local y2:Int=-1 To 1
			For Local x2:Int=-1 To 1
				Local x3:Int=x+x2
				Local y3:Int=y+y2
				If x3<0 Or x3>=mapwidth Or y3<0 Or y3>=mapheight Then Continue
				If map[x3,y3] = 0 Then map[x,y] = 2
			Next
			Next
			End if
		Next
		Next
	End Method
	Method getdungeon()
		Local dw:Int = mapwidth / 3
		Local dh:Int = mapheight / 3
		Local mydungeon:dungeon = New dungeon(screenwidth,screenheight,dw,dh)
		map = New Int[mapwidth,mapheight]
		For Local y:Int=0 Until dh
		For Local x:Int=0 Until dw
			If mydungeon.map[x,y] <> 0
				For Local y2:Int=0 To 2
				For Local x2:Int=0 To 2
					map[x*3+x2,y*3+y2] = 1
				Next
				Next
			End If
		Next
		Next
	End Method	
	Method drawworld(canvas:Canvas)		
		Local tw:Float=Float(screenwidth) / Float(mapwidth)
		Local th:Float=Float(screenheight) / Float(mapheight)	
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local t:Int = map[x,y]
			If t = 0 Then Continue
			If t=1 Then canvas.Color = Color.White
			If t=2 Then canvas.Color = Color.Brown
			canvas.DrawRect(x*tw,y*th,tw+1,th+1)
		Next
		Next
	End Method

	Method draw(canvas:Canvas,xpos:Int,ypos:Int)
		Local tx:Int=xpos/tilewidth
		Local ty:Int=ypos/tileheight
		Local px:Int=tx*tilewidth-xpos
		Local py:Int=ty*tileheight-ypos		
		For Local y:Int=0 Until tilesver
		For Local x:Int=0 Until tileshor			
			If x+tx < 0 Or x+tx >= mapwidth Or y+ty<0 Or y+ty >= mapheight Then Continue
			Local t:Int = map[x+tx,y+ty]
			If t = 0 Then Continue
			If t = 1 Then canvas.Color = Color.Grey.Blend(Color.Black,.5)
			If t = 2 Then canvas.Color = Color.Grey
			canvas.DrawRect((x*tilewidth)+px,(y*tileheight)+py,tilewidth,tileheight)			
		Next
		Next
	End Method
End Class

Class dungeon	
	Field map:Int[,]
	Field screenwidth:Int,screenheight:Int
	Field mapwidth:Int,mapheight:Int
	Field tilewidth:Int,tileheight:Int
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		If mapwidth < 10 Or mapheight < 10 Then RuntimeError("Map size to small. in dungeon class.")
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		tilewidth = Float(screenwidth) / Float(mapwidth)
		tileheight = Float(screenheight) / Float(mapheight)
		generatedungeon()
	End Method
	Method generatedungeon()
		map = New Int[mapwidth,mapheight]
		Local maxroomwidth:Int=mapwidth/4
		Local maxroomheight:Int=mapheight/4
		Local minroomwidth:Int=4
		Local minroomheight:Int=4
		' center of the room coordinates
		Local currentroomx:Int
		Local currentroomy:Int
		Local prevroomx:Int=-1
		Local prevroomy:Int
		' We create a number of rooms based on the width and 
		' height of the map.
		
		For Local i:Int=0 Until (mapwidth+mapheight)/10
			Local newroomwidth:Int = Rnd(minroomwidth,maxroomwidth)
			Local newroomheight:Int = Rnd(minroomheight,maxroomheight)
			Local count:Int=0
			currentroomx = Rnd(minroomwidth/2,mapwidth)
			currentroomy = Rnd(minroomheight/2,mapheight)			
			' Here we keep looping until we have a valid room position
			While overlap(currentroomx,currentroomy,newroomwidth,newroomheight) = True
				' We exit the method if it takes to long.
				count += 1
				If count>99 Then Return
				' Try to get new valid room
				currentroomx = Rnd(minroomwidth,mapwidth)
				currentroomy = Rnd(minroomheight,mapheight)
				newroomwidth = Rnd(minroomwidth,maxroomwidth)
				newroomheight = Rnd(minroomheight,maxroomheight)				
			Wend			
			' Place the room
			For Local y1:Int=currentroomy-newroomheight/2 Until currentroomy+newroomheight/2
			For Local x1:Int=currentroomx-newroomwidth/2 Until currentroomx+newroomwidth/2
				map[x1,y1] = 1
			Next
			Next
			' Can we connect two room yet?
			If prevroomx > -1 
				' Here we start to tunnel between the current room
				' center to the previous rooms center.
				Local x1:Int=currentroomx,x2:Int=prevroomx
				Local y1:Int=currentroomy,y2:Int=prevroomy
				' Randomly decide if x or y goes first
				If Rnd() < .5
					' Make a tunnel
					While x1<>x2
						If x1<x2 Then x1+=1 Else x1-=1					
						map[x1,y1] = 1
					Wend
					While y1<>y2
						If y1<y2 Then y1+=1 Else y1-=1
						map[x1,y1] = 1
					Wend
				Else
					' Make a tunnel
					While y1<>y2
						If y1<y2 Then y1+=1 Else y1-=1
						map[x1,y1] = 1
					Wend
					While x1<>x2
						If x1<x2 Then x1+=1 Else x1-=1					
						map[x1,y1] = 1
					Wend				
				End If
	
			End If
			prevroomx = currentroomx
			prevroomy = currentroomy
			
		Next
	End Method
	' Does the inputted area touch a value in the map
	' or does it go outside of the screen.
	' returns true if so.
	Method overlap:Bool(x:Int,y:Int,w:Int,h:Int)
		x-=1
		y-=1
		w+=1
		h+=1
		If x-w/2<0 Or y-h/2<0 Or x+w/2>=mapwidth Or y+h/2>=mapheight Then Return True
		For Local y1:Int=y-h/2 Until y+h/2
		For Local x1:Int=x-w/2 Until x+w/2
			If map[x1,y1] = 1 Then Return True
		Next
		Next			
		Return False
	End Method
	Method drawmap(canvas:Canvas)
		canvas.Color = Color.White
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If map[x,y] > 0
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth+1,tileheight+1)
			End If
		Next
		Next
	End Method
End Class

Global myworld:world
Global myexplosion:Stack<explosion>

Class MyWindow Extends Window
	Field xpos:Int=1550
	Field ypos:Int=1550
	'Field mydun:dungeon
		
	Method New()
		'mydun = New dungeon(Width,Height,50,50)
		myworld = New world(Width,Height,100,100)
		myexplosion = New Stack<explosion>
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		myworld.update()
		myworld.draw(canvas,xpos,ypos)
		updateexplosion()
		drawexplosion(canvas,xpos,ypos)
		If Keyboard.KeyDown(Key.Right) Then xpos+=4
		If Keyboard.KeyDown(Key.Down) Then ypos+=4
		If Keyboard.KeyDown(Key.Left) Then xpos-=4
		If Keyboard.KeyDown(Key.Up) Then ypos-=4

		If Keyboard.KeyDown(Key.Space) Then
			myworld.drawworld(canvas)
		End if
'		

'		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		canvas.Color = Color.White
		canvas.DrawText(xpos+","+ypos,0,0)
	End Method	
	
	Method updateexplosion()
		For Local i:Int=0 Until myexplosion.Length
			myexplosion.Get(i).update()
		Next
	End Method
	
	Method drawexplosion(canvas:Canvas,xpos:Int,ypos:Int)
		For Local i:Int=0 Until myexplosion.Length
			myexplosion.Get(i).draw(canvas,xpos,ypos)
		Next		
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
