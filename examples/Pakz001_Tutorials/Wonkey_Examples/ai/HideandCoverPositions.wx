#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global sw:Int,sh:Int 'screenwidth and height

'
' This is our map class
' 
'
Class map
	' our map width and height and tile width and height
	Field w:Int,h:Int,tw:Float,th:Float
	Field map:Int[,]
	'
	'
	Field px:Float,py:Float ' tile position not pixel position
	Method New(w:Int,h:Int)
		Self.w = w
		Self.h = h
		Self.tw = Float(sw) / Float(w)
		Self.th = Float(sh) / Float(h)
		map = New Int[w,h]
		createmap()
	End Method
	' Here we use the mouse coordinates as the dummy player position
	Method update()
		px = Int(Mouse.X/tw)
		py = Int(Mouse.Y/th)
	End Method
	Method createmap()
		For Local i:Int=0 Until w+h
			Local x:Int = Rnd(4,w-4)
			Local y:Int = Rnd(4,h-4)
			If Rnd() < .5
				If Rnd()<.5
					For Local i:Int=0 Until 3
						map[x,y] = 1
						x+=1
					Next
				Else
					For Local i:Int=0 Until 3
						map[x,y] = 1
						y+=1
					Next
				End If
			Else
				map[x,y] = 1
			End If
		Next
	End Method
	Method drawmap(canvas:Canvas)
		' Draw the map
		For Local y:Int=0 Until h
		For Local x:Int=0 Until w
			Local dx:Int=x*tw
			Local dy:Int=y*th
			Select map[x,y]
				Case 1
					canvas.Color = Color.Grey
					canvas.DrawRect(dx,dy,tw+1,th+1)
			End Select
		Next
		Next
		' Draw the player
		
		canvas.Color = Color.Yellow
		canvas.DrawRect(Int(px)*tw,Int(py)*th,tw,th)
	End Method
End Class

Class agent
	' our agent x and y position
	Field x:Float,y:Float 'tile
	Field w:Float,h:Float
	' each agent has a array with a floodfill of numbers towards a safe spot
	Field floodmap:Int[,]
	' this method gets called every time a new agent is created.
	Method New()
		x = 15
		y = 15
		Self.w = mymap.tw
		Self.h = mymap.th
		' Create our floodmap
		floodmap = New Int[mymap.w,mymap.h]
		
	End Method
	' update
	Method update()
		floodthemap()
	End Method
	' Create a new floodmap
	Method floodthemap()
		' first we shoot invisible bullets from the player position around
		' the player finding tiles and then spaces behind the tiles.
		' Get the player position(tile)
		floodmap = New Int[mymap.w,mymap.h]
		For Local a:Float=0 Until TwoPi Step .1
			Local x1:Float = mymap.px*mymap.tw
			Local y1:Float = mymap.py*mymap.th									
			' distance of 100
			Local collided:Bool=False
			For Local i:Int=0 Until 200
				x1+=Cos(a)*1
				y1+=Sin(a)*1
				'If x1<0 Or y1<0 Or x1>=sw Or y1>=sh Then Exit
				If x1/mymap.tw>=mymap.w Or y1/mymap.th>=mymap.h Then Exit
				If x1/mymap.tw<0 Or y1/mymap.th<0 Then Exit
				' if we collide with a wall the first time
				If mymap.map[x1/mymap.tw,y1/mymap.th]=1 And collided = False Then					
					collided = True
				End If
				' here we find the first tile behind the obstacle
				If collided = True And mymap.map[x1/mymap.tw,y1/mymap.th]=0
					floodmap[x1/mymap.tw,y1/mymap.th] = 1
					
					Exit
				End If
			Next			
		Next		
	End Method
	' draw our agent
	Method draw(canvas:Canvas)
		canvas.Color = Color.Red
		canvas.DrawOval(x*mymap.tw,y*mymap.th,w,h)
		For Local y:Int=0 Until mymap.h
		For Local x:Int=0 Until mymap.w
			If floodmap[x,y] = 1
				canvas.Color = Color.Puce
				canvas.DrawRect(x*mymap.tw,y*mymap.th,mymap.tw,mymap.th)
			End If
		Next
		Next
	End Method
End Class


Global mymap:map
Global myagent:List<agent> = New List<agent>
Class MyWindow Extends Window
	
	Method New()
		sw = Width ; sh = Height
		mymap = New map(50,50)
		myagent.Add(New agent())
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		'update the agents
		For Local i:=Eachin myagent
			i.update()
		Next
		'draw the agents
		For Local i:=Eachin myagent
			i.draw(canvas)
		Next
		
		'update the map
		mymap.update()
		mymap.drawmap(canvas)
		
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
	Return ATan2(y2-y1, x2-x1)
End Function 

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
