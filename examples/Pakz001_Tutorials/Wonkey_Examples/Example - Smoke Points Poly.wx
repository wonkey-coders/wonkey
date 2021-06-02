'
' CLouds from explosions test

'
' What I am trying to do here is to create smoke that expands
' and gets shaped by the game level. If on side of the smoke hits
' a wall then the points that make up the smoke there will not move
' into the level so the smoke stays inside the level.
' The smoke is a series of points that gets drawn as a poly.
'
'
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class player
	Field myrpg:Stack<rpg>
	Class rpg
		Field px:Int,py:Int
		Field lastpx:Int,lastpy:Int
		Field mx:Float,my:Float
		Field deleteme:Bool		
		Method New(x:Int,y:Int,mx:Float,my:Float)
			Self.px = x
			Self.py = y
			Self.mx = mx
			Self.my = my
		End Method
		Method update()
			For Local i:Int=0 Until 3
				lastpx = px
				lastpy = py
				px += mx
				py += my
				If myworld.map[(px)/myworld.tilewidth,(py)/myworld.tileheight] = 1
					deleteme = True
					mycloud.Push(New cloud(lastpx,lastpy))
				End if
			Next
		End Method
		Method draw(canvas:Canvas)
			canvas.Color = Color.Blue
			canvas.DrawCircle(px,py,3)
		End Method
	End Class
	' x y width height
	Field px:Int,py:Int
	Field pw:Int,ph:Int
	Field shootdelay:Int
	Method New(x:Int,y:Int,w:Int,h:Int)
		Self.px = x
		Self.py = y
		Self.pw = w
		Self.ph = h
		myrpg = New Stack<rpg>
	End Method
	Method update()
		shootdelay+=1
		Local oldx:Int=px
		Local oldy:Int=py
		Local l:Bool=False,u:Bool=False,d:Bool=False,r:Bool=False
		If Keyboard.KeyDown(Key.Right) Then r=True
		If Keyboard.KeyDown(Key.Left) Then l=True
		If Keyboard.KeyDown(Key.Up)Then u=True
		If Keyboard.KeyDown(Key.Down) Then d=True
		
		If Keyboard.KeyDown(Key.Right) Then px+=1
		If Keyboard.KeyDown(Key.Left) Then px-=1
		If Keyboard.KeyDown(Key.Up)Then py-=1
		If Keyboard.KeyDown(Key.Down) Then py+=1
		If myworld.map[(px+pw/2)/myworld.tilewidth,(py+ph/2)/myworld.tileheight] = 1
			px = oldx
			py = oldy
		End If
		If shootdelay>10
			If r=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,1,0));shootdelay=0
			If l=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,-1,0));shootdelay=0
			If u=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,0,-1));shootdelay=0
			If d=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,0,1));shootdelay=0
			If r=True And u=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,1,-1));shootdelay=0
			If r=True And d=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,1,1));shootdelay=0
			If l=True And u=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,-1,-1));shootdelay=0
			If l=True And d=True And Keyboard.KeyDown(Key.F) Then myrpg.Push(New rpg(px,py,-1,1));shootdelay=0
		End if
		For Local i:Int=0 Until myrpg.Length
			myrpg.Get(i).update()
		Next
		For Local i:Int=0 Until myrpg.Length
			If myrpg.Get(i).deleteme = True Then
				myrpg.Erase(i)
			End If
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Pine
		canvas.DrawOval(px,py,pw,ph)
		For Local i:Int=0 Until myrpg.Length
			myrpg.Get(i).draw(canvas)
		Next
	End Method
End Class

Class world
	Field map:Int[,]
	Field mapwidth:Int,mapheight:Int
	Field screenwidth:Int,screenheight:Int
	Field tilewidth:Float,tileheight:Float
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		Self.tilewidth = Float(screenwidth) / Float(mapwidth)
		Self.tileheight = Float(screenheight) / Float(mapheight)
		generatemap()
	End Method
	Method generatemap()
		map = New int[mapwidth,mapheight]
		'edges
		For Local y:Int=0 Until mapheight
			map[0,y] = 1
			map[mapwidth-1,y] = 1
		Next
		For Local x:Int=0 Until mapwidth
			map[x,0] = 1
			map[x,mapheight-1] = 1
		Next
		' stick/grow things from walls
		For Local i:Int=0 Until mapwidth*mapheight/6
			Local x:Int=Rnd(mapwidth)
			Local y:Int=Rnd(mapheight)
			If map[x,y] = 0 Then Continue
			Local mx:Int,my:Int
			If Rnd()<.5 Then
				If Rnd()<.5 Then mx=-1 Else mx=1
			Else
				If Rnd()<.5 Then my=-1 Else my=1
			End If
			Local d:Int=Rnd(2,mapwidth/4)
			For Local j:Int = 0 Until d
				x+=mx
				y+=my
				If x<0 Or y<0 Or x>=mapwidth Or y>=mapheight Then Exit
				map[x,y] = 1
				If Rnd()<.1
					Local x2:Int=x,y2:Int=y
					For Local k:Int=0 Until d
						x2+=-my
						y2+=-mx
						If x2<0 Or y2<0 Or x2>=mapwidth Or y2>=mapheight Then Exit
						map[x2,y2] = 1
					Next
				End If
			Next
		Next
		'grow a little
		For Local i:Int=0 Until mapwidth*mapheight*1.5
			Local x:Int=Rnd(mapwidth)
			Local y:Int=Rnd(mapheight)
			If map[x,y] = 0 Then Continue
			Local nx:Int=x+Rnd(-1,2)
			Local ny:Int=y+Rnd(-1,2)
			If nx<0 Or ny<0 Or nx>=mapwidth Or ny>=mapheight Then Continue
			map[nx,ny] = 1
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local t:Int=map[x,y]
			If t = 0 Then Continue
			If t = 1 Then canvas.Color = Color.Grey
			canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth+1,tileheight+1)
		Next
		Next
	End Method
End Class

Class cloud
	Field px:Float,py:Float
	Field mypoint:Stack<point>
	Field timeout:Int=50
	Field time:Float=50
	Field deleteme:Bool=False
	Class point
		Field px:Float,py:Float
		Field mx:Float,my:Float		
		Method New(x:Int,y:Int,mx:Float,my:Float)
			Self.px = x			
			Self.py = y			
			Self.mx = mx
			Self.my = my									
		End Method		
	End Class
	Method New(x:Int,y:Int)
		Self.px = x
		Self.py = y
		mypoint = New Stack<point>
		createcloud()
	End Method
	Method createcloud()
		For Local i:Float=-Pi Until Pi Step .35
			Local a:Float=Cos(i)/Rnd(5,9)
			Local b:Float=Sin(i)/Rnd(5,9)
			mypoint.Push(New point(px,py,a,b))
		Next		
	End Method
	Method update()		
		timeout-=1
		If timeout<0 Then deleteme = True
		For Local j:Int=0 Until 10
		For Local i:Int=0 Until mypoint.Length
			Local x:Float = mypoint.Get(i).px
			Local y:Float = mypoint.Get(i).py
			x += mypoint.Get(i).mx
			y += mypoint.Get(i).my
			If mapcollide(x,y)
				mypoint.Get(i).mx = 0
				mypoint.Get(i).my = 0
			End If
			mypoint.Get(i).px = x
			mypoint.Get(i).py = y
		Next		
		Next
	End Method
	Method draw(canvas:Canvas)
		If timeout<0 Then Return
		For Local i:Int=0 Until mypoint.Length
			canvas.Color = Color.Red
			Local x:Int=mypoint.Get(i).px
			Local y:Int=mypoint.Get(i).py
			canvas.DrawCircle(x,y,4)
		Next
		' draw the poly
		Local pol:Float[]
		pol = New Float[mypoint.Length*2]
		For Local i:Int=0 Until mypoint.Length
			pol[i*2] = mypoint.Get(i).px
			pol[i*2+1] = mypoint.Get(i).py
			
		Next
		Local s:Float=(1.0/time)*Float(timeout)
		canvas.Color = New Color(1,1,0,s)
		canvas.DrawPoly(pol)
	End Method
	Method mapcollide:Bool(x:Int,y:Int)
		Local x2:Int = x / myworld.tilewidth
		Local y2:Int = y / myworld.tileheight
		If myworld.map[x2,y2] = 1 Then Return True
		Return False
	End Method
End Class

Global mycloud:Stack<cloud>
Global myworld:world
Global myplayer:player

Class MyWindow Extends Window
	
	Method New()
		SeedRnd(Microsecs())
		mycloud = New Stack<cloud>
		myworld = New world(Width,Height,30,30)
		myplayer = New player(320,240,16,16)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' New map
		If Keyboard.KeyReleased(Key.Space)
			mycloud = New Stack<cloud>
			myworld = New world(Width,Height,30,30)
			myplayer = New player(320,240,16,16)
		End If		
		'
		myworld.draw(canvas)
		' Draw the player
		myplayer.draw(canvas)
		myplayer.update()
		' Update the clouds
		
		' Sometimes create a random one
		If Rnd()<0.02 Then
			Local x:Int=Rnd(Width)
			Local y:Int=Rnd(Height)
			If myworld.map[x/myworld.tilewidth,y/myworld.tileheight] = 0
				mycloud.Push(New cloud(x,y))
			End If
		End If
		'
		For Local i:Int=0 Until mycloud.Length
			mycloud.Get(i).update()
		Next
		For Local i:Int=0 Until mycloud.Length
			mycloud.Get(i).draw(canvas)		
		Next
		For Local i:Int=0 Until mycloud.Length
			If mycloud.Get(i).deleteme = True Then
				mycloud.Erase(i)
			End If
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		canvas.Color = Color.White
		canvas.DrawText("Press space/F/Left,Right,Up,Down.",0,0)
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
