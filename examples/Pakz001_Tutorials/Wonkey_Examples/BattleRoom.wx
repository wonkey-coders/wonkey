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
' In the stoners class I actually was able to create a movement
' system that makes a group of units move as a group. They do 
' not get in each other.
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class stoners
	Field px:Float,py:Float
	Field pw:Int=8,ph:Int=8
	Field deleteme:Bool=False
	Method New(x:Int,y:Int)
		Self.px = x
		Self.py = y
	End Method	
	Method update()
		Local tx:Int=px/myworld.tilewidth
		Local ty:Int=py/myworld.tileheight
		If tx<0 Or tx>=myworld.mapwidth Or ty>=myworld.mapheight Or ty<0 Then 
			deleteme = True
			return
		End if
		Local v:Int=myplayer.pathto[tx,ty]
		If v=1 Then v=99
		If v>6 Then Return
		For Local y:Int=-1 To 1
		For Local x:Int=-1 To 1
			If tx+x<0 Or ty+y<0 Or tx+x>=myworld.mapwidth Or ty+y>=myworld.mapheight Then Continue
			If myplayer.pathto[tx+x,ty+y] <= v Then
				If myplayer.pathto[tx+x,ty+y] > 1
					Local dont:Bool=False
					For Local i:Int=0 Until mystoners.Length
						If mystoners.Get(i).px <> px And mystoners.Get(i).py <> py							
							If distance(mystoners.Get(i).px,mystoners.Get(i).py,px,py) < 16 
								dont=True
							End If							
						End If						
					Next
					If dont=True Then Return
					px += Float(x)/5
					py += Float(y)/5

				End If
			End If
		Next
		Next
		' Push them appart if to close to each other
		For Local i:Int=0 Until mystoners.Length
		For Local j:Int=0 Until mystoners.Length
			If i<>j				
				Local x1:Int=mystoners.Get(i).px
				Local y1:Int=mystoners.Get(i).py				
				Local x2:Int=mystoners.Get(j).px
				Local y2:Int=mystoners.Get(j).py
				If distance(x1,y1,x2,y2) < 20 Then
					Local a:Float=getangle(x2,y2,x1,y1) 
					mystoners.Get(i).px += Cos(a)/10
					mystoners.Get(i).py += Sin(a)/10
				End if
			End If
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Pink
		canvas.DrawOval(px,py,pw,ph)
	End Method
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 	
End Class

Class player
	Class point
		Field x:Int,y:Int,val:Int
		Method New(x:Int,y:Int,val:Int)
			Self.x = x
			Self.y = y
			Self.val = val
		End Method
	End Class
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
	Field pathto:Int[,]
	Method New(x:Int,y:Int,w:Int,h:Int)
		Self.px = x
		Self.py = y
		Self.pw = w
		Self.ph = h
		createpathtoplayer()
		myrpg = New Stack<rpg>
	End Method
	Method update()
		If Rnd() < .05 Then createpathtoplayer()
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
	Method createpathtoplayer()
		pathto = New Int[myworld.mapwidth,myworld.mapheight]
		For Local y:Int=0 Until myworld.mapheight
		For Local x:Int=0 Until myworld.mapwidth
			pathto[x,y] = myworld.map[x,y]
		next
		Next
		' Flood the path
		Local mypoint:Stack<point> = New Stack<point>
		mypoint.Push(New point(px/myworld.tilewidth,py/myworld.tileheight,1))
		pathto[px/myworld.tilewidth,py/myworld.tileheight] = 1
		While mypoint.Length > 0
			Local x:Int=mypoint.Get(0).x
			Local y:Int=mypoint.Get(0).y
			Local v:Int=mypoint.Get(0).val
			mypoint.Erase(0)
			For Local y2:Int=y-1 To y+1
			For Local x2:Int=x-1 To x+1
				If x2<0 Or x2>=myworld.mapwidth Or y2<0 Or y2>=myworld.mapheight Then Continue
				If pathto[x2,y2] = 0
					pathto[x2,y2] = v+1
					mypoint.Push(New point(x2,y2,v+1))
				End if
			Next
			Next
		Wend
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Pine
		canvas.DrawOval(px,py,pw,ph)
		For Local i:Int=0 Until myrpg.Length
			myrpg.Get(i).draw(canvas)
		Next
'		For Local y:Int=0 Until myworld.mapheight
'		For Local x:Int=0 Until myworld.mapwidth
'			canvas.Color = Color.Blue
'			canvas.DrawText(pathto[x,y],x*myworld.tilewidth,y*myworld.tileheight)
'		Next
'		Next
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
Global mystoners:Stack<stoners>

Class MyWindow Extends Window
	
	Method New()
		SeedRnd(Microsecs())
		mycloud = New Stack<cloud>
		myworld = New world(Width,Height,30,30)
		myplayer = New player(320,240,16,16)
		mystoners = New Stack<stoners>
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' New map
		If Keyboard.KeyReleased(Key.Space)
			mycloud = New Stack<cloud>
			myworld = New world(Width,Height,30,30)
			myplayer = New player(320,240,16,16)
			mystoners = New Stack<stoners>
		End If		
		'
		' Update the stoners
		'
		If Rnd()<.3 And mystoners.Length<25
			Local x:Int=Rnd(2,myworld.mapwidth-2)
			Local y:Int=Rnd(2,myworld.mapheight-2)
			If myworld.map[x,y] = 0 And myplayer.pathto[x,y] > 1
				Local e:Bool=False
				For Local y2:Int=y-1 To y+1
				For Local x2:Int=x-1 To x+1
					If x2<0 Or y2<0 Or x2>=myworld.mapwidth Or y2>=myworld.mapheight Then Continue
					If e=False
						If myworld.map[x2,y2] = 1
							e=True
							Local dont:Bool=False
							For Local i:Int= 0 Until mystoners.Length
								If distance(x*myworld.tilewidth,y*myworld.tileheight,mystoners.Get(i).px,mystoners.Get(i).py)<20
									dont=True									
								End If
							Next
							If dont=False
								mystoners.Push(New stoners(x*myworld.tilewidth+myworld.tilewidth/2,y*myworld.tileheight+myworld.tileheight/2))
							End If
						End If
					End if
				Next
				Next
			End if
		End If
		For Local i:Int=0 Until mystoners.Length
			mystoners.Get(i).update()
		Next
		For Local i:Int=0 Until mystoners.Length
			mystoners.Get(i).draw(canvas)
		Next
		For Local i:Int=0 Until mystoners.Length
			If mystoners.Get(i).deleteme = True
				mystoners.Erase(i)
			End If
		Next

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
		canvas.DrawText(mystoners.Length,0,20)
		
	End Method	
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
