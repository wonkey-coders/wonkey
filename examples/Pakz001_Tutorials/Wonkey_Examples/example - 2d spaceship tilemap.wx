
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


' Our gfx
Global shipim:Image
Global shipcan:Canvas
Global rockim:Image
Global rockcan:Canvas
Global rockltim:Image
Global rockltcan:Canvas
Global rockrtim:Image
Global rockrtcan:Canvas
Global rocklbim:Image
Global rocklbcan:Canvas
Global rockrbim:Image
Global rockrbcan:Canvas
Global rockbackim:Image
Global rockbackcan:Canvas
Global rockore1im:Image
Global rockore1can:Canvas


Class laser
	Field x:Float,y:Float,s:Float=3
	Field incx:Float,incy:Float
	Field time:Int,timeout:Int=320
	Field deleteme:Bool=False
	Method New(x:Float,y:Float,incx:Float,incy:Float)
		Self.x = x
		Self.y = y
		Self.incx = incx
		Self.incy = incy
	End Method
	Method update()
		' increase life
		time+=1
		' if to old then mark for delete
		If time>timeout Then deleteme=True
		x += incx
		y += incy
		'
		' get map position
		Local rx:Int=x+myship.x
		Local ry:Int=y+myship.y
		Local tx:Int=rx/myship.tilew
		Local ty:Int=ry/myship.tileh
		For Local y2:Int=-1 To 1
		For Local x2:Int=-1 To 1
			Local ax:Int=tx+x2*myship.tilew
			Local ay:Int=ty+y2*myship.tileh
			
		If myship.map[ax,ay] = 7 Or myship.map[ax,ay] = 1
			If rectsoverlap(ax*myship.tilew,ay*myship.tileh,myship.tilew,myship.tileh,rx,ry,3,3)
				myship.map[ax,ay] = 6
				deleteme = True
				' remove any edges
				For Local bx:Int=-1 To 1
				For Local by:Int=-1 To 1
					If myship.map[ax+bx,ay+by] >1 And myship.map[ax+bx,ay+by]<6 Then myship.map[ax+bx,ay+by] = 6
				Next
				Next
				'recreate any edges
				For Local by:Int=ay-2 Until ay+2
				For Local bx:Int=ax-2 Until ax+2
					If myship.map[bx,by] = 1 And myship.map[bx-1,by+1] = 1 And myship.map[bx-1,by]=6 Then myship.map[bx-1,by] = 2 'left top rock
					If myship.map[bx,by] = 1 And myship.map[bx+1,by+1] = 1 And myship.map[bx+1,by]=6 Then myship.map[bx+1,by] = 3 'right top rock
					If myship.map[bx,by] = 1 And myship.map[bx-1,by-1] = 1 And myship.map[bx-1,by]=6 Then myship.map[bx-1,by] = 4 'left bottom rock
					If myship.map[bx,by] = 1 And myship.map[bx+1,by-1] = 1 And myship.map[bx+1,by]=6 Then myship.map[bx+1,by] = 5 'right bottom rock
				Next
				Next


				Exit
			End If
		End If
		Next
		Next
		'
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Red
		canvas.DrawCircle(x,y,s)
	End Method
End Class

Class ship
	' tilemap
	Field map:Int[,]
	Field tilew:Int=48
	Field tileh:Int=48
	'ship
    Field x:Float,y:Float
	Field incx:Float,incy:Float
	Field thrust:Float,thrustmax:Float=2
	Field angle:Float
	Field maxspeed:Float=2
   	Method New(x:Float,y:Float,angle:Float)
	   	map = New Int[512,512]
	   	generatemap()
		Self.x = x
		Self.y = y
		Self.angle = angle
	End Method
	
	Method update()		
		
		If thrust>0 Then thrust-=.01

	End Method
	Method controls()
		'mine
		If Keyboard.KeyReleased(Key.Space) Then
			mylaser.Add(New laser(320+24-16,200+24+16,Cos(angle)*4,-Sin(angle)*4))
		End If

		' turn
		If Keyboard.KeyDown(Key.Right) Then angle-=.1
		If Keyboard.KeyDown(Key.Left) Then angle+=.1
		If angle<0 Then angle+=TwoPi
		If angle>TwoPi Then angle-=TwoPi
		' thrust (inc)
		If Keyboard.KeyDown(Key.Up) Then 
			thrust+=.015
			If thrust>thrustmax Then thrust=thrustmax
			Local nvx:Float = incx+Cos(angle)*thrust
			Local nvy:Float = incy+Sin(angle)*thrust
			'get the angle of the new nvx and nvy
			Local nangle:Float = ATan2(nvy,nvx) 'get the angle from the movement variables
			'get the distance traveled from location of ship and the location with the movement added
			Local dist:Float = edistance(x,y,x+nvx,y+nvy)
			' If the movement is larger than max then limit
			If Abs(dist) > maxspeed	Then
				incx = Cos(nangle)*maxspeed
				incy = Sin(nangle)*maxspeed
				Else
				'if the movement is within bounds then update the inc variables
				incx = nvx
				incy = nvy
			End If			
		End If
        x+=incx
        y-=incy
	End Method
	Method generatemap()	
		' center of map set to 256,256
		
		'create asteroid by growing pixels
		map[256,256] = 1
		For Local i:Int=0 Until 1000*1000
			Local x:Int=256+Rnd(-100,100)
			Local y:Int=256+Rnd(-100,100)
			If map[x,y] = 1 Then 
				For Local y2:Int=-1 To 1
				For Local x2:Int=-1 To 1
					map[x+x2,y+y2] = 1
				Next
				Next
			End If
		Next
		
		Local point:Stack<Vec2i> = New Stack<Vec2i>
		Local numpoints:Int=32
		For Local i:Int=0 Until numpoints
			point.Push(New Vec2i(256-Rnd(-100,100),256+Rnd(-100,100)))
		Next
		For Local i:Int=1 Until point.Length
			'carve
			Local x1:Int=point.Get(i-1).x
			Local y1:Int=point.Get(i-1).y
			Local x2:Int=point.Get(i).x
			Local y2:Int=point.Get(i).y
			While x1<>x2 And y1<>y2
				If x1<x2 Then x1+=1
				If x1>x2 Then x1-=1
				If y1<y2 Then y1+=1
				If y1>y2 Then y1-=1
				Local s:Int=1
				If Rnd()<.1 Then s=Rnd(2,3)
				For Local y:Int=-s To s
				For Local x:Int=-s To s
				map[x1+x,y1+y] = 6
				Next
				Next
			Wend
			
		Next

		'find edges and create those tile values
		For Local y:Int=1 Until 511
		For Local x:Int=1 Until 511
			If map[x,y] = 1 And map[x-1,y+1] = 1 And map[x-1,y]=6 Then map[x-1,y] = 2 'left top rock
			If map[x,y] = 1 And map[x+1,y+1] = 1 And map[x+1,y]=6 Then map[x+1,y] = 3 'right top rock
			If map[x,y] = 1 And map[x-1,y-1] = 1 And map[x-1,y]=6 Then map[x-1,y] = 4 'left bottom rock
			If map[x,y] = 1 And map[x+1,y-1] = 1 And map[x+1,y]=6 Then map[x+1,y] = 5 'right bottom rock
		Next
		Next
		
		'add ore 1
		For Local i:Int=0 Until 900
			Local x:Int=256+Rnd(-100,100)
			Local y:Int=256+Rnd(-100,100)
			If map[x,y] = 1 Then map[x,y] = 7
			'grow
			If Rnd()<.8
				Local s:Int=Rnd(2,80)
				For Local i2:Int=0 Until s
					Local x2:Int=x+Rnd(-25,25)
					Local y2:Int=y+Rnd(-25,25)
					If map[x2,y2] = 7 Then
						
						For Local x3:Int=-1 To 1
						For Local y3:Int=-1 To 1
							If map[x2+x3,y2+y3] = 1 And Rnd()<.3
								map[x2+x3,y2+y3] = 7
							End If 
						Next
						Next
					End if
				Next
			End If
		Next
		
	End Method
	Method drawmap(canvas:Canvas)
		Local offx:Int=x/tilew
		Local offy:Int=y/tileh
		Local poffx:Int = (offx*tilew)-x
		Local poffy:Int = (offy*tileh)-y
		For Local my:Int=0 Until 16
		For Local mx:Int=0 Until 24
			If map[offx+mx,offy+my] = 1
				canvas.Color=Color.White
				'canvas.DrawRect(0+mx*tilew+poffx,0+my*tileh+poffy,tilew,tileh)
				canvas.DrawImage(rockim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End If
			If map[offx+mx,offy+my] = 2 'left top rock
				canvas.Color=Color.White
				canvas.DrawImage(rockltim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 3 'right top rock
				canvas.Color=Color.White
				canvas.DrawImage(rockrtim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 4 'left bottom rock
				canvas.Color=Color.White
				canvas.DrawImage(rocklbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 5 'right bottom rock
				canvas.Color=Color.White
				canvas.DrawImage(rockrbim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 6 'background rock
				canvas.Color=Color.White '.Blend(Color.Black,.8)
				canvas.DrawImage(rockbackim,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if
			If map[offx+mx,offy+my] = 7 'background rock
				canvas.Color=Color.White '.Blend(Color.Black,.8)
				canvas.DrawImage(rockore1im,0+mx*tilew+poffx,0+my*tileh+poffy)
			End if

		Next
		Next
	End Method
End Class

Global mylaser:List<laser> = New List<laser>
	' Our classes
Global myship:ship

Class MyWindow Extends Window
	' The c64 palette (16 colors)
	Field c64color:Color[]
	Method New()
		'Setup our images so they can be drawn
		setupim()
		myship = New ship(256*48,256*48,0)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		myship.update()
		myship.controls()
		' update the lasers
		For Local i:=Eachin mylaser
			i.update()
		Next
		' remove any dead ones
		For Local i:=Eachin mylaser
			If i.deleteme Then mylaser.Remove(i)
		Next
		
		
		'
		myship.drawmap(canvas)
		canvas.Color = Color.White
		canvas.DrawImage(shipim,320,240,myship.angle)

		' draw the lasers
		For Local i:=Eachin mylaser
			i.draw(canvas)
		Next



		canvas.DrawText("angle : "+myship.angle,0,0)
		canvas.DrawText("thrust : "+myship.thrust,0,15)
		canvas.DrawText("incx and incy : "+myship.incx+","+myship.incy,0,25)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	
	
	'
	' Holds and set up the gfx data.
	Method setupim()
		inic64colors()
		shipim = New Image(32,32)
		shipcan = New Canvas(shipim)
		shipim.Handle = New Vec2f(0.5,0.5)
		rockim = New Image(48,48)
		rockcan = New Canvas(rockim)
		rockltim = New Image(48,48)
		rockltcan = New Canvas(rockltim)
		rockrtim = New Image(48,48)
		rockrtcan = New Canvas(rockrtim)
		rocklbim = New Image(48,48)
		rocklbcan = New Canvas(rocklbim)
		rockrbim = New Image(48,48)
		rockrbcan = New Canvas(rockrbim)
		rockbackim = New Image(48,48)
		rockbackcan = New Canvas(rockbackim)
		rockore1im = New Image(48,48)
		rockore1can = New Canvas(rockore1im)
Local map := New Int[][] (
New Int[](1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,1,12,1,1,1,0,0,0,0,0,0,0,0,0,0),
New Int[](0,1,12,1,1,1,1,1,1,0,0,0,0,0,0,0),
New Int[](0,1,12,11,1,1,1,1,1,1,1,0,0,0,0,0),
New Int[](0,1,1,1,1,12,1,1,1,1,1,1,1,0,0,0),
New Int[](0,11,1,1,1,11,1,1,1,1,1,1,1,1,1,0),
New Int[](0,11,1,1,1,1,1,11,1,1,1,1,11,12,1,1),
New Int[](0,11,1,1,1,1,1,11,1,1,1,1,11,12,1,1),
New Int[](0,11,1,1,1,11,1,1,1,1,1,1,1,1,1,0),
New Int[](0,1,1,1,1,12,1,1,1,1,1,1,1,0,0,0),
New Int[](0,1,12,11,1,1,1,1,1,1,1,0,0,0,0,0),
New Int[](0,1,12,1,1,1,1,1,1,0,0,0,0,0,0,0),
New Int[](0,1,12,1,1,1,0,0,0,0,0,0,0,0,0,0),
New Int[](0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0))		
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			shipcan.Color = c64color[map[y][x]]
			shipcan.DrawRect(x*2,y*2,2,2)
		Next
		Next
		shipcan.Flush()

map = New Int[][] (
New Int[](12,11,12,12,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,15,15,1,12,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,15,15,15,15,15,15,12,12,15,15,15),
New Int[](15,15,15,12,1,15,15,15,15,1,12,11,15,15,15,15),
New Int[](15,15,15,15,12,1,15,15,15,15,12,15,15,15,15,15),
New Int[](15,15,15,15,15,12,15,15,15,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,11,12,15,15,15,15,15,15,15,15,12),
New Int[](12,15,15,15,15,15,15,12,15,15,15,15,15,12,15,15),
New Int[](15,15,15,15,15,15,15,11,12,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,1,15,15,15,15,15,15,15,1,15,15),
New Int[](15,15,15,11,12,12,15,15,15,15,15,15,12,12,1,15),
New Int[](15,15,15,12,15,15,15,15,15,15,15,15,15,12,12,15),
New Int[](15,15,11,12,1,15,15,15,15,15,15,15,12,11,12,15),
New Int[](12,11,15,15,1,15,15,15,15,15,15,15,12,11,12,15),
New Int[](12,15,15,12,15,15,15,15,15,15,15,15,15,15,12,12))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockcan.Color = c64color[map[y][x]]
			rockcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockcan.Flush()

'lefttop rock
map = New Int[][] (
New Int[](11,12,15,0,0,0,0,0,0,0,0,0,11,11,0,15),
New Int[](0,11,15,0,0,11,11,0,11,0,0,0,0,0,11,15),
New Int[](11,0,0,0,11,0,0,0,0,11,0,11,0,15,11,15),
New Int[](0,0,0,0,11,12,15,12,11,0,11,0,15,15,15,15),
New Int[](0,11,11,0,11,11,11,0,0,0,0,11,15,15,15,15),
New Int[](0,11,12,11,0,11,0,0,0,11,11,11,15,11,12,15),
New Int[](11,0,12,0,0,11,0,11,0,15,11,11,15,11,12,15),
New Int[](0,12,15,11,0,0,11,0,0,15,15,15,15,12,1,15),
New Int[](11,11,11,0,0,11,11,15,15,1,15,15,15,12,12,1),
New Int[](11,0,0,11,0,11,15,15,15,15,12,12,15,15,15,15),
New Int[](11,0,11,0,0,15,15,15,15,15,12,15,15,15,15,15),
New Int[](12,15,0,0,15,11,15,15,15,15,15,15,15,15,15,15),
New Int[](11,0,11,0,0,0,15,15,15,15,15,15,15,15,15,15),
New Int[](0,11,15,11,15,15,15,12,11,15,15,15,15,15,15,15),
New Int[](11,15,1,15,15,15,12,1,15,15,15,15,1,15,15,15),
New Int[](15,15,12,15,15,11,15,15,15,15,15,15,12,12,11,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockltcan.Color = c64color[map[y][x]]
			rockltcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockltcan.Flush()

'right top rock
map = New Int[][] (
New Int[](15,11,0,11,0,0,0,12,11,0,0,0,11,0,0,0),
New Int[](15,15,11,0,0,11,15,11,11,11,0,0,11,0,0,11),
New Int[](15,15,11,11,11,0,0,11,0,0,0,0,11,0,0,12),
New Int[](11,15,11,15,0,0,0,11,0,0,0,11,0,11,15,12),
New Int[](15,15,11,15,15,11,0,0,0,0,0,0,11,11,12,11),
New Int[](15,15,15,15,15,15,11,11,0,11,11,11,0,11,0,11),
New Int[](15,15,1,12,12,15,15,11,11,11,12,11,0,0,11,0),
New Int[](15,15,15,12,11,15,0,11,0,12,12,15,11,0,0,0),
New Int[](15,15,12,15,15,15,0,0,11,11,11,15,11,0,11,0),
New Int[](15,15,15,15,15,15,15,15,15,15,11,0,0,0,0,12),
New Int[](15,15,15,15,15,15,15,12,12,15,15,11,0,11,15,12),
New Int[](15,15,15,15,15,15,1,1,11,15,15,15,0,0,0,11),
New Int[](15,15,15,15,15,12,12,12,15,11,15,15,15,11,0,0),
New Int[](15,12,1,15,15,12,15,15,15,15,15,11,11,0,11,0),
New Int[](15,11,12,12,15,15,15,15,12,12,1,15,11,11,15,11),
New Int[](15,15,15,15,15,15,15,15,11,12,15,15,15,15,15,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockrtcan.Color = c64color[map[y][x]]
			rockrtcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockrtcan.Flush()


'left bottom rock
map = New Int[][] (
New Int[](15,15,15,15,15,15,1,15,12,11,15,15,15,15,15,15),
New Int[](11,15,15,12,12,12,12,15,15,15,15,15,15,15,15,15),
New Int[](11,11,15,15,15,15,12,11,15,15,15,15,12,1,12,15),
New Int[](0,0,11,15,11,11,15,15,15,15,15,15,15,15,11,15),
New Int[](11,0,11,0,0,11,15,15,15,15,15,15,15,15,15,15),
New Int[](12,12,0,11,0,11,15,15,15,12,1,15,15,12,15,15),
New Int[](11,0,15,11,0,0,15,15,11,12,12,15,15,15,15,15),
New Int[](0,11,11,0,11,0,0,15,15,11,12,15,15,15,15,15),
New Int[](0,0,0,11,0,12,0,0,15,12,15,15,15,12,1,15),
New Int[](0,0,0,0,15,12,11,11,11,15,15,15,15,12,12,15),
New Int[](0,0,0,0,11,11,0,0,11,11,11,11,15,15,12,15),
New Int[](11,11,11,0,0,11,11,0,0,0,11,0,11,15,12,11),
New Int[](15,12,11,0,11,0,11,0,0,0,0,11,15,15,15,11),
New Int[](11,0,0,0,0,11,0,0,11,11,0,11,0,11,15,15),
New Int[](0,0,0,0,0,0,0,15,12,11,0,0,11,0,15,15),
New Int[](11,0,0,11,11,0,0,11,12,0,0,0,0,11,11,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rocklbcan.Color = c64color[map[y][x]]
			rocklbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rocklbcan.Flush()


'right bottom rock
map = New Int[][] (
New Int[](1,12,12,15,15,15,15,12,1,11,12,15,15,15,15,15),
New Int[](15,12,11,15,15,15,15,15,1,15,15,15,15,11,15,11),
New Int[](15,12,15,15,15,15,15,15,12,15,15,11,0,15,11,11),
New Int[](15,15,15,15,15,15,1,12,11,15,15,15,0,11,0,0),
New Int[](15,15,15,15,12,12,12,11,15,15,15,0,11,11,0,11),
New Int[](15,15,15,15,15,15,15,15,15,15,15,0,0,11,15,0),
New Int[](15,15,15,15,15,1,12,15,11,15,11,11,11,12,12,0),
New Int[](15,15,15,15,15,12,15,15,11,11,0,0,11,11,0,11),
New Int[](15,15,15,15,12,15,15,15,11,0,0,11,0,0,11,0),
New Int[](15,1,15,15,15,11,15,0,11,11,12,11,0,0,0,0),
New Int[](15,1,12,15,11,15,11,11,0,11,11,11,0,0,0,11),
New Int[](15,12,11,11,11,11,11,0,0,11,0,0,0,0,0,0),
New Int[](15,15,15,15,11,11,0,11,11,0,0,0,0,0,0,0),
New Int[](15,15,15,12,12,15,11,0,0,0,0,0,0,11,0,0),
New Int[](15,15,11,0,11,12,12,12,11,0,11,15,12,11,0,11),
New Int[](15,11,0,11,0,0,0,0,11,0,0,11,12,11,0,11))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockrbcan.Color = c64color[map[y][x]]
			rockrbcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockrbcan.Flush()

' background dark
map = New Int[][] (

New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,11,0,0,0),
New Int[](0,0,11,0,0,0,0,0,0,0,12,15,0,0,0,0),
New Int[](11,11,0,0,0,0,0,0,0,11,0,11,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,11,12,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,11,0,0,0,0,0,0),
New Int[](0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](11,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0),
New Int[](15,12,0,0,0,0,0,0,0,0,0,11,0,0,0,0),
New Int[](11,0,0,0,0,0,0,0,0,0,11,0,0,0,0,0))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockbackcan.Color = c64color[map[y][x]]
			rockbackcan.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockbackcan.Flush()

map = New Int[][] (

New Int[](12,15,12,11,12,15,12,12,15,15,15,15,12,15,15,12),
New Int[](15,15,15,1,15,15,11,12,11,15,15,15,15,15,15,15),
New Int[](15,15,15,15,15,12,12,1,14,14,11,15,15,15,15,15),
New Int[](15,15,15,15,15,11,3,14,6,0,11,15,12,12,15,15),
New Int[](15,11,15,15,12,11,3,14,0,11,15,15,15,15,15,15),
New Int[](15,12,1,15,15,15,14,6,11,11,15,15,15,15,15,15),
New Int[](15,12,15,11,12,12,15,0,15,12,12,15,15,15,15,15),
New Int[](15,15,12,12,1,3,14,11,15,15,12,15,12,15,15,15),
New Int[](15,15,12,11,3,14,14,6,11,12,11,11,14,0,15,15),
New Int[](15,15,15,15,14,14,6,0,12,1,3,14,14,11,15,15),
New Int[](15,15,15,15,0,0,0,12,11,14,6,14,6,0,15,15),
New Int[](15,15,15,15,15,11,12,15,11,14,15,0,0,11,15,15),
New Int[](15,15,15,15,15,15,1,12,15,0,11,11,15,15,15,15),
New Int[](15,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15),
New Int[](12,12,15,15,15,15,15,15,15,15,15,15,12,1,15,15),
New Int[](11,12,15,15,15,15,15,15,15,15,15,15,11,12,12,15))
		For Local y:Int=0 Until 16
		For Local x:Int=0 Until 16
			rockore1can.Color = c64color[map[y][x]]
			rockore1can.DrawRect(x*3,y*3,3,3)
		Next
		Next
		rockore1can.Flush()


End Method
	'
	' This is the palette used for the graphics... 
	Method inic64colors()
		c64color = New Color[16]
		c64color[0 ] = New Color(intof(0)  ,intof(0)  ,intof(0)  )'Black
		c64color[1 ] = New Color(intof(255),intof(255),intof(255))'White
		c64color[2 ] = New Color(intof(136),intof(0)  ,intof(0)  )'Red
		c64color[3 ] = New Color(intof(170),intof(255),intof(238))'Cyan
		c64color[4 ] = New Color(intof(204),intof(68) ,intof(204))'Violet / Purple
		c64color[5 ] = New Color(intof(0)  ,intof(204),intof(85) )'Green
		c64color[6 ] = New Color(intof(0)  ,intof(0)  ,intof(170))'Blue
		c64color[7 ] = New Color(intof(238),intof(238),intof(119))'Yellow
		c64color[8 ] = New Color(intof(221),intof(136),intof(85) )'Orange
		c64color[9 ] = New Color(intof(102),intof(68) ,intof(0)  )'Brown
		c64color[10] = New Color(intof(255),intof(119),intof(119))'Light red
		c64color[11] = New Color(intof(51) ,intof(51) ,intof(51) )'Dark grey / Grey 1
		c64color[12] = New Color(intof(119),intof(119),intof(119))'Grey 2
		c64color[13] = New Color(intof(170),intof(255),intof(102))'Light green
		c64color[14] = New Color(intof(0)  ,intof(136),intof(255))'Light blue
		c64color[15] = New Color(intof(187),intof(187),intof(187))'Light grey / grey 3
	End Method
	' convert int(0.255) to float(0.1)
	Function intof:Float(a:Int)
		Return 1.0/255.0*a
	End Function
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function


Function edistance:Float(x1:Float,y1:Float,x2:Float,y2:Float) 
	Return Sqrt( (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) )
End Function
Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    Return True
End
