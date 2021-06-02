#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class hud
	Field screenwidth:Int,screenheight:Int
	Field weapons:String[]=New String[]("gun","RPG")
	Method New(screenwidth:Int,screenheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
	End Method
	Method update()
		If Keyboard.KeyReleased(Key.Key1)
			myplayer.weapon = 1
		End If
		If Keyboard.KeyReleased(Key.Key2)
			myplayer.weapon = 2
		End If
	End Method
	Method draw(canvas:Canvas)
		Local x:Int=50
		For Local i:Int=0 Until weapons.Length
			If myplayer.weapon = i+1
				canvas.Color = New Color(.3,.3,.3)
				canvas.DrawRect(x,screenheight-42,canvas.Font.TextWidth(weapons[i])+48,20)
			End If
			canvas.Color = Color.White
			canvas.DrawText(i+1+" - "+weapons[i],x,screenheight-40)
			'SetColor 0,0,0
			x+=canvas.Font.TextWidth(weapons[i])+48
		Next
	End Method
End Class

Class smoke
	Field x:Float,y:Float
	Field poly:Float[]
	Field w:Int,h:Int
	Field dx:Float,dy:Float
	Field alpha:Float=Rnd(0.1,0.7)
	Field deleteme:Bool
	Field timeoutcnt:Int
	Method New(x:Int,y:Int)
		Self.x = x + Rnd(-15,15)
		Self.y = y + Rnd(-15,15)
		w = Rnd(10,32)
		h = Rnd(10,32)
		setpos(Self.x,Self.y)
		timeoutcnt = Rnd(40,150)
	End Method

	Method setpos(x1:Float,y1:Float)
		Local angle:Int=Rnd(360)
		Local distance:Int=Rnd(0,60)
		For Local i:Int=0 Until distance
			x1+=Cos(angle)*1
			y1+=Sin(angle)*1
			If mymap.mapcollide(x1,y1,w,h) Then 
				w = 0
				h = 0
				deleteme = True
				Return
			End If
		Next
		dx = Cos(angle)*Rnd(.1,.7)
		dy = Sin(angle)*Rnd(.1,.7)
		Self.x = x1
		Self.y = y1

		'make the poly
		Local numpoly:Int=Rnd(4,10)*2
		poly = New Float[numpoly+2]
		Local angstep:Int=340/(numpoly/2)
		Local d:Int=w
		Local s:Int=0
		angle=0
		While angle<360
			Local d2:Int=Rnd(5,d)
			poly[s] = Self.x+Cos(angle)*d2
			poly[s+1] = Self.y+Sin(angle)*d2
			s+=2
			angle+=angstep
		Wend

	End Method
	Method update()
		timeoutcnt-=1
		If timeoutcnt<0 Then deleteme = True
		
		If mymap.mapcollide(x,y,w,w) = False Then 
			x+=dx ; y+=dy
			For Local i:Int=0 Until poly.Length-1 Step 2
				poly[i] += dx
				poly[i+1] += dy
			Next
		End If
		
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = New Color(.6,.6,.6,alpha)
		canvas.DrawPoly(poly)
		'DrawOval x,y,w,h
	End Method
End Class


Class particle
	Field x:Float,y:Float
	Field w:Float,h:Float
	Field size:Float
	Field poly:Float[]
	Field mx:Float,my:Float
	Field speed:Int
	Field deleteme:Bool
	Field timeout:Int
	Field bouncecountdown:Int
	Field time:Int
	Field hpdamage:Int
	Field hp:Int 'how strong is the particle
	Field shooter:String
	Method New(x:Int,y:Int,shooter:String)
		Self.shooter = shooter
		Self.x = x+Rnd(-5,5)
		Self.y = y+Rnd(-5,5)
		speed = Rnd(1,4)
		mx = Rnd(0.1,1)
		my = Rnd(0.1,1)
		If Rnd(1)<.5 Then mx=-mx
		If Rnd(1)<.5 Then my=-my
		size = Rnd(3,mymap.tilewidth/3)
		w = Rnd(3,mymap.tilewidth)
		h = Rnd(3,mymap.tileheight)
		timeout = Rnd(20,100)
		bouncecountdown = Rnd(1,3)		
		hpdamage = 3
		
		hp = Rnd(1,5)
		
		'make the poly
		Local angle:Int=0
		Local numpoly:Int=Rnd(4,10)*2
		poly = New Float[numpoly+2]
		Local angstep:Int=340/(numpoly/2)
		Local d:Int=size
		Local st:Int=0
		angle=0
		While angle<360
			Local d2:Int=Rnd(5,d)
			poly[st] = Self.x+Cos(angle)*d2
			poly[st+1] = Self.y+Sin(angle)*d2
			st+=2
			angle+=angstep
		Wend
		
	End Method
	Method update()
		For Local i:Int=0 Until speed
			x+=mx
			y+=my
			'update the poly
			For Local ii:Int=0 Until poly.Length-1 Step 2
				poly[ii] += mx
				poly[ii+1] += my
			Next
			If mymap.mapcollide(x,y,size,size) = True Then
				mx = -mx
				my = -my
				'w/=3
				'h/=3
				bouncecountdown-=1
				If bouncecountdown<1 Then 
					deleteme = True				
				End If
			End If
		Next

		' if particle collide with enemy
		If shooter = "player"
			For Local ii:=Eachin myenemy
				If distance(x,y,ii.x,ii.y)<size Then
					ii.deleteme = True
					Return
				End If
			Next				
		End If
		If shooter = "enemy"
			If distance(myplayer.x,myplayer.y,x,y)<size
				myplayer.died = True				
				Return
			End If
		End If
		
		time+=1
		If time>timeout Then deleteme = True
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Red
		'DrawOval x,y,w,h
		canvas.DrawPoly(poly)
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
    	Return Abs(x2-x1)+Abs(y2-y1)
	End Function	
End Class


Class rpg
	Field x:Float,y:Float
	Field w:Float,h:Float
	Field mx:Float
	Field my:Float
	Field speed:Int 'how many updates per call
	Field hpdamage:Int=3
	Field deleteme:Bool=False 'when remove from game
	Field shooter:String
	Method New(x:Int,y:Int,direction:String,shooter:String)
		Self.shooter = shooter
		speed = 3  'set movement speed
		w = myplayer.w / 2
		h = myplayer.h / 2
		If w<3 Then w = 3
		If h<3 Then h = 3
		Self.x = x
		Self.y = y 
		Select direction 
			Case "left"
			mx=-1
			my+=Rnd(-.04,.04)
			Case "right"
			mx=1
			my+=Rnd(-.04,.04)
			Case "up"
			my=-1
			mx+=Rnd(-.04,.04)
			Case "down"
			my=1
			mx+=Rnd(-.04,.04)
			Case "leftup"
			mx=-1+Rnd(-0.2,0.2)
			my=-1+Rnd(-0.2,0.2)
			Case "rightup"
			mx=1+Rnd(-0.2,0.2)
			my=-1+Rnd(-0.2,0.2)
			Case "leftdown"
			mx=-1+Rnd(-0.2,0.2)
			my=1+Rnd(-0.2,0.2)
			Case "rightdown"
			mx=1+Rnd(-0.2,0.2)
			my=1+Rnd(-0.2,0.2)
		End Select
	End Method
	' rpg logic
	Method update()
		For Local i:Int=0 Until speed
			x+=mx
			y+=my
			' if collide with map
			If mymap.mapcollide(x,y,w,h) Then 
				deleteme = True
				' explode the rpg
				For Local ii:Int=0 Until 20
					myparticle.AddLast(New particle(x,y,shooter))
					
				Next
				For Local ii:Int=0 Until 60
					mysmoke.AddLast(New smoke(x,y))
				Next
				Return
			End If
			'if collide with enemy
			If shooter = "player"
				For Local ii:=Eachin myenemy
					If distance(x,y,ii.x+(ii.w/2),ii.y+(ii.h/2))<8 Then 
						deleteme = True
						' Explode the rpg
						For Local iii:Int=0 Until 10
							myparticle.AddLast(New particle(x,y,"player"))
							mysmoke.AddLast(New smoke(x,y))
						Next
					End If
				Next
			End If	
			'if collide with player
			If shooter = "enemy"
				If distance(x,y,myplayer.x+(myplayer.w/2),myplayer.y+(myplayer.h/2))<8 Then 
					' Explode the rpg
					For Local iii:Int=0 Until 10
						myparticle.AddLast(New particle(x,y,"enemy"))
						mysmoke.AddLast(New smoke(x,y))
					Next
				End If
			End If	

		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Yellow
		canvas.DrawOval(x,y,w,h)
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
    	Return Abs(x2-x1)+Abs(y2-y1)
	End Function	
End Class


Class enemy
	Field x:Int,y:Int
	Field w:Int,h:Int
	Field state:String
	Field deleteme:Bool
	Field cooldown:Int
	Field waittime:Int
	Field path:List<pathnode> = New List<pathnode>	
	Method New()
		w = mymap.tilewidth-4
		h = mymap.tileheight-4
		findstartpos()

	End Method
	Method update()
		' enemy shoot diagnal
		If Rnd(100)<2 Then
			Local px:Int=myplayer.x
			Local py:Int=myplayer.y
			If distance(px,py,x,y) < 200
				If px<x And py<y And mymap.mapcollide(x-5,y-5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"leftup","enemy"))
					If checkrpg(x,y,"leftup") Then myrpg.AddLast(New rpg(x,y,"leftup","enemy"))
				End If
				If px>x And py<y And mymap.mapcollide(x+5,y-5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"rightup","enemy"))
					If checkrpg(x,y,"rightup") Then myrpg.AddLast(New rpg(x,y,"rightup","enemy"))
				End If
				If px<x And py>y And mymap.mapcollide(x-5,y+5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"leftdown","enemy"))
					If checkrpg(x,y,"leftdown") Then myrpg.AddLast(New rpg(x,y,"leftdown","enemy"))
				End If
				If px>x And py>y And mymap.mapcollide(x+5,y+5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"rightdown","enemy"))
					If checkrpg(x,y,"rightdown") Then myrpg.AddLast(New rpg(x,y,"rightdown","enemy"))
				End If

			End If
		End If
		'enemy shoot horizontal vertical
		If Rnd(100)<2 Then
			Local px:Int=myplayer.x
			Local py:Int=myplayer.y
			If distance(px,py,x,y) < 200
				If px<x And mymap.mapcollide(x-5,y,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"left","enemy"))
					If checkrpg(x,y,"left") Then myrpg.AddLast(New rpg(x,y,"left","enemy")) 
				End If
				If px>x And mymap.mapcollide(x+5,y-5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"right","enemy"))
					If checkrpg(x,y,"right") Then myrpg.AddLast(New rpg(x,y,"right","enemy"))
				End If
				If py>y And mymap.mapcollide(x,y+5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"down","enemy"))
					If checkrpg(x,y,"down") Then myrpg.AddLast(New rpg(x,y,"down","enemy"))
				End If
				If py<y And mymap.mapcollide(x,y-5,w/3,h/3) = False 
					mybullet.AddLast(New bullet(x,y,"up","enemy"))
					If checkrpg(x,y,"down") Then myrpg.AddLast(New rpg(x,y,"down","enemy"))
				End If

			End If
		End If


		' move around the enemy
		If path.Empty = False
		' add 2 to the destination coords or gets stuck
		Local dx:Int=path.First.x*mymap.tilewidth+2
		Local dy:Int=path.First.y*mymap.tileheight+2
		If x<dx And mymap.mapcollide(x+1,y,w,h) = False Then x+=1
		If x>dx And mymap.mapcollide(x-1,y,w,h) = False Then x-=1
		If y<dy And mymap.mapcollide(x,y+1,w,h) = False Then y+=1
		If y>dy And mymap.mapcollide(x,y-1,w,h) = False Then y-=1

		'if near destination 
		If distance(x,y,dx,dy) < 2 Then 
			path.RemoveFirst()
			x = dx
			y = dy
		End If
		End If
		
		'if no more moves left find new cover spot
		If path.Empty
			If waittime>0 Then waittime-=1
			If waittime<=0
			For Local i:Int=0 Until 100
				Local dx:Int=Rnd(2,mymap.mapwidth-2)
				Local dy:Int=Rnd(2,mymap.mapheight-2)
				If mymap.covermap[dx,dy] = 1 Then 
					createpath(dx,dy)
					waittime=200
					Exit	
				End If
			Next
			End If
		End If
		
		'if player is nearby then move to closest cover spot
		If distance(myplayer.x,myplayer.y,x,y) < 160
			If cooldown>0 Then cooldown-=1
			If cooldown=0
			cooldown=100
			Local d:Int=10000
			Local destx:Int,desty:Int
			Local fnd:Bool=False
			' random spots until coverspot, log closest
			For Local i:Int=0 Until 250
				Local dx:Int=Rnd(2,mymap.mapwidth-2)
				Local dy:Int=Rnd(2,mymap.mapheight-2)
				If mymap.covermap[dx,dy] = 1 Then 
					Local d2:Int = distance(dx,dy,x/mymap.tilewidth,y/mymap.tileheight)
					If d2 < d Then
						d = d2
						destx = dx
						desty = dy
						fnd=True
					End If
				End If
			Next
			' if we have a new dest then plan it
			If fnd=True Then createpath(destx,desty)
			End If
		End If

	End Method
	Method createpath(ex:Int,ey:Int)
		path = New List<pathnode>
		Local dx:Int=x/mymap.tilewidth
		Local dy:Int=y/mymap.tileheight
'		x = dx*mymap.tilewidth
'		y = dy*mymap.tileheight
		myastar.findpath(dx,dy,ex,ey)
		For Local i:=Eachin myastar.path
			path.AddLast(New pathnode(i.x,i.y))
		Next
	End Method
	Method drawpath(canvas:Canvas)
		canvas.Color = Color.Red
		For Local i:=Eachin path
			canvas.DrawOval(i.x*mymap.tilewidth,i.y*mymap.tileheight,w/2,h/2)
		Next
	End Method
	Method findstartpos()
		Local cnt:Int=400
		Local cnt2:Int=0
		Repeat
			Local nx:Int=Rnd(0,mymap.screenwidth-20)
			Local ny:Int=Rnd(0,mymap.screenheight-20)
			Local found:Bool=True
			' if the map position a tile
			If mymap.mapcollide(nx,ny,w,h) Then found = False
			' if the position is to close other enemy
			For Local i:=Eachin myenemy
				If i=Self Then Continue
				If distance(i.x,i.y,nx,ny) < 30 Then found = False ;Exit
			Next
			' if the position to close to player
			If distance(myplayer.x,myplayer.y,nx,ny) < cnt Then found = False 
			If found = True Then 
				x = nx
				y = ny
				Exit
			Else
				If cnt>32 Then cnt -=1
			End If
		Forever
	End Method

	
	'
	' This method fires a fake rpg to see if it hits the player. 
	' 
	Method checkrpg:Bool(x:Int,y:Int,direction:String)
		' set how many times the ai uses the rpg
		'If Rnd(50)>3 Then Return False
		Local mx:Float,my:Float
		Select direction
			Case "left"
				mx=-1;my=0
			Case "right"
				mx=1;my=0
			Case "up"
				mx=0;my=-1
			Case "down"
				mx=0;my=1
			Case "leftup"
				mx=-1;my=-1
			Case "leftdown"
				mx=-1;my=1
			Case "rightup"
				mx=1;my=-1
			Case "rightdown"
				mx=1;my=1
		End Select
		Local px:Float=x,py:Float=y
		Local dist:Int=256
		For Local i:Int=0 Until dist
			px += mx
			py += my
			' if hit wall then check particle hit against player
			If mymap.mapcollide(px-5,py-5,10,10) Then 
				For Local ii:Int=0 Until 50 
					Local px2:Float=px-Rnd(-10,10)
					Local py2:Float=py-Rnd(-10,10)
					Local mx2:Float=Rnd(-1,1)
					Local my2:Float=Rnd(-1,1)
					For Local iii:Int=0 Until 100
						px2+=mx2
						py2+=my2
						If mymap.mapcollide(px2-5,py2-5,10,10) Then Exit
						If distance(myplayer.x,myplayer.y,px2,py2) < 10 Then Return True
					Next	
				Next
				Return False
			End If
			If distance(px,py,myplayer.x,myplayer.y) < 50 Then Return True
		Next
		
		Return False
	End Method

	Method draw(canvas:Canvas)
		canvas.Color = Color.Brown
		canvas.DrawOval(x,y,w,h)
	End Method

	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function

End Class

Class bullet
	Field x:Float,y:Float
	Field w:Int,h:Int
	Field mx:Int,my:Int
	Field direction:String
	Field deleteme:Bool=False
	Field speed:Int=2
	Field shooter:String
	Method New(x:Int,y:Int,direction:String,shooter:String)
		Self.x = x
		Self.y = y
		Self.w = myplayer.w/3
		Self.h = myplayer.h/3
		Self.shooter = shooter
		Self.direction = direction
		If direction = "left" Then mx = -1
		If direction = "right" Then mx = 1
		If direction = "up" Then my = -1
		If direction = "down" Then my = 1
		If direction = "leftup" Then mx = -1 ; my = -1
		If direction = "rightup" Then mx = 1 ; my = -1
		If direction = "leftdown" Then mx = -1 ; my = 1
		If direction = "rightdown" Then mx = 1 ; my = 1
	End Method
	Method update()
		'move the bullet and see collision with walls
		For Local i:Int=0 Until speed
			x += mx
			y += my
			If x < 0 Or x > mymap.screenwidth Then deleteme = True
			If y < 0 Or y > mymap.screenheight Then deleteme = True
			If mymap.mapcollide(x,y,w,h) Then deleteme = True
		Next
		' collision with bullet vs enemy
		' delete bullet and delete enemy
		If shooter = "player"
			For Local i:=Eachin myenemy
				If distance(i.x+(i.w/2),i.y+(i.h/2),x,y)<myplayer.w/1.5 Then 
					deleteme = True
					i.deleteme = True
				End If
			Next
		End If

		' collision with bullet vs player
		' delete bullet and kill player
		If shooter = "enemy"
			If distance(myplayer.x+(myplayer.w/2),myplayer.y+(myplayer.h/2),x,y)<myplayer.w/1.5 Then 
				deleteme = True
				myplayer.died = True
			End If
		End If

	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Yellow
		canvas.DrawOval(x,y,w,h)
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function

End Class

Class player
	Field x:Float,y:Float
	Field w:Int,h:Int
	Field direction:String="up"
	Field died:Bool=False
	Field weapon:Int
	Method New()
		w = mymap.tilewidth-4
		h = mymap.tileheight-4
		findstartingpos()
	End Method
	Method update()
		playercontrols()
		makecovermap()
	End Method
    Method playercontrols()
    	' movement	
    	If Keyboard.KeyDown(Key.Up) And Not mymap.mapcollide(x,y-1,w,h)
    		y-=1
			direction = "up"
    	End If
    	If Keyboard.KeyDown(Key.Left) And Not mymap.mapcollide(x-1,y,w,h)
    		x-=1
    		direction = "left"
    	End If
    	If Keyboard.KeyDown(Key.Right) And Not mymap.mapcollide(x+1,y,w,h)
    		x+=1
    		direction = "right"
    	End If
    	If Keyboard.KeyDown(Key.Down) And Not mymap.mapcollide(x,y+1,w,h)
    		y+=1
    		direction = "down"
    	End If
		If Keyboard.KeyDown(Key.Left) And Keyboard.KeyDown(Key.Up) Then direction = "leftup"
		If Keyboard.KeyDown(Key.Right) And Keyboard.KeyDown(Key.Up) Then direction = "rightup"
		If Keyboard.KeyDown(Key.Left) And Keyboard.KeyDown(Key.Down) Then direction = "leftdown"
		If Keyboard.KeyDown(Key.Right) And Keyboard.KeyDown(Key.Down) Then direction = "rightdown"	
		' shooting
		If Keyboard.KeyHit(Key.F)
			If weapon = 1 Then mybullet.AddLast(New bullet(x,y,direction,"player"))
			If weapon = 2 Then myrpg.AddLast(New rpg(x,y,direction,"player"))
		End If
    End Method
	Method makecovermap()
		If Rnd(60)>2 Then Return
		For Local y:Int=0 Until mymap.mapheight
		For Local x:Int=0 Until mymap.mapwidth
			mymap.covermap[x,y] = 1
			If mymap.map[x,y] <> 0 Then mymap.covermap[x,y] = 2
		Next
		Next
		' shoot bullets into random directions around
		' the player and see if any position is a cover position
		For Local i:Int=0 Until 600
			Local x2:Float=x
			Local y2:Float=y
			Local xa:Float=Rnd(-1,1)
			Local ya:Float=Rnd(-1,1)
			For Local d:Int=0 Until 40
				x2+=xa*Float(mymap.tilewidth/2)
				y2+=ya*Float(mymap.tileheight/2)
				Local mx:Int=x2/mymap.tilewidth
				Local my:Int=y2/mymap.tileheight
				If mx>=0 And my>=0 And mx<mymap.mapwidth And my<mymap.mapheight
				mymap.covermap[mx,my] = 0
				Else
				Exit
				End If
				If mymap.mapcollide(x2,y2,w/3,h/3) Then Exit
				
			Next
		Next
		'
		' Remove every coverpoint except if they
		' are near a wall. 
		For Local y2:Int=0 Until mymap.mapheight
		For Local x2:Int=0 Until mymap.mapwidth
			Local remove:Bool=True
			For Local y3:Int=y2-1 To y2+1
			For Local x3:Int=x2-1 To x2+1
				If x3<0 Or y3<0 Or x3>=mymap.mapwidth Or y3>=mymap.mapheight Then Continue
				If mymap.map[x3,y3] <> 0 Then remove = False ; Exit
			Next
			Next
			If remove = True Then
				mymap.covermap[x2,y2] = 0
			End If
		Next
		Next
		'if closer to the player then higher movement cost per tile
		For Local y2:Int=0 Until mymap.mapheight
		For Local x2:Int=0 Until mymap.mapwidth
			If myastar.map[x2,y2] <> 1000 Then myastar.map[x2,y2] = 100-distance(myplayer.x/mymap.tilewidth,myplayer.y/mymap.tileheight,x2,y2)
			If myastar.map[x2,y2] < 85 Then myastar.map[x2,y2] = 0
			If mymap.covermap[x2,y2] = 1 Then myastar.map[x2,y2] = 0
		Next
		Next


	End Method
	Method findstartingpos()
		Repeat
			Local x1:Int = Rnd(0,mymap.mapwidth)
			Local y1:Int = Rnd(0,mymap.mapheight)
			Local istaken:Bool=False
			For Local x2:Int=x1-4 To x1+4
			For Local y2:Int=y1-4 To y1+4
				If x2<0 Or y2<0 Or x2>=mymap.mapwidth Or y2>=mymap.mapheight Then Continue
				If mymap.map[x2,y2] <> 0 Then istaken = True ; Exit				
			Next
			Next
			If istaken=False Then 
				x = x1*mymap.tilewidth
				y = y1*mymap.tileheight
				Exit
			End If			
		Forever
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawOval(x,y,w,h)
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function
End Class

Class astar
	Field mapwidth:Int,mapheight:Int
	Field sx:Int,sy:Int
	Field ex:Int,ey:Int
	Field olmap:Int[,]
	Field clmap:Int[,]
	Field map:Int[,]
	Field ol:List<openlist> = New List<openlist>
	Field cl:List<closedlist> = New List<closedlist>
	Field path:List<pathnode> = New List<pathnode>
	Field xstep:Int[] = New int[](0,-1,1,0)
	Field ystep:Int[] = New Int[](-1,0,0,1)
	Method New()
		mapwidth = mymap.mapwidth
		mapheight = mymap.mapheight
		olmap = New Int[mapwidth,mapheight]
		clmap = New Int[mapwidth,mapheight]
		map = New Int[mapwidth,mapheight]
		' Copy the map into the astar class map
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			map[x,y] = mymap.map[x,y]
		Next
		Next
	End Method
	' This creates the map and copies the 
	' path in the path list
	Method findpath:Bool(sx:Int,sy:Int,ex:Int,ey:Int)
	    If sx = ex And sy = ey Then Return False
	    Self.sx = sx
	    Self.sy = sy
	    Self.ex = ex
	    Self.ey = ey
	    For Local y:Int=0 Until mapheight
	    For Local x:Int=0 Until mapwidth
	        olmap[x,y] = 0
	        clmap[x,y] = 0
	    Next
	    Next
	    ol.Clear()
	    cl.Clear()
	    path.Clear()
	    ol.AddFirst(New openlist(sx,sy))
	    Local tx:Int
	    Local ty:Int
	    Local tf:Int
	    Local tg:Int
	    Local th:Int
	    Local tpx:Int
	    Local tpy:Int
	    Local newx:Int
	    Local newy:Int
	    Local lowestf:Int
	    olmap[sx,sy] = 1
	    While ol.Empty = False
	        lowestf = 100000
	        For Local i:=Eachin ol
	            If i.f < lowestf
	                lowestf = i.f
	                tx = i.x
	                ty = i.y
	                tf = i.f
	                tg = i.g
	                th = i.h
	                tpx = i.px
	                tpy = i.py
	            End If
	        Next
	        If tx = ex And ty = ey
	            cl.AddLast(New closedlist(tx,ty,tpx,tpy))
	            findpathback()
	            Return True
	        Else
	            removefromopenlist(tx,ty)
	            olmap[tx,ty] = 0
	            clmap[tx,ty] = 1
	            cl.AddLast(New closedlist(tx,ty,tpx,tpy))
	            For Local i:Int=0 Until xstep.Length
					Local x:Int=xstep[i]
					Local y:Int=ystep[i]
	                newx = tx+x
	                newy = ty+y
	                If newx>=0 And newy>=0 And newx<mapwidth And newy<mapheight
	                If olmap[newx,newy] = 0
	                If clmap[newx,newy] = 0
	                    olmap[newx,newy] = 1
	                    Local gg:Int = map[newx,newy]+1
	                    Local hh:Int = distance(newx,newy,ex,ey)
	                    Local ff:Int = gg+hh
	                    ol.AddLast(New openlist(newx,newy,ff,gg,hh,tx,ty))
	                End If
	                End If
	                End If
	            Next
	        End If
	    Wend
	    Return False
	End Method

	Method drawpath:Void(canvas:Canvas)
	    Local cnt:Int=1
	    For Local i:=Eachin path
	        canvas.Color = Color.Yellow
	        canvas.DrawOval(i.x*mymap.tilewidth,i.y*mymap.tileheight,4,4)
	        canvas.Color = Color.White
	        canvas.DrawText(cnt,i.x*mymap.tilewidth,i.y*mymap.tileheight)
	        cnt+=1
	    Next
	End Method
	' Here we calculate back from the end back to the
	' start and create the path list.
	Method findpathback:Bool()
	    Local x:Int=ex
	    Local y:int=ey
	    path.AddFirst(New pathnode(x,y))
	    Repeat
	        For Local i:=Eachin cl
	            If i.x = x And i.y = y
	                x = i.px
	                y = i.py
	                path.AddFirst(New pathnode(x,y))
	            End If
	        Next
	        If x = sx And y = sy Then Return True
	    Forever    
		Return false
	End Method


	Method removefromopenlist:Void(x1:Int,y1:Int)
    	For Local i:=Eachin ol
        	If i.x = x1 And i.y = y1
            	ol.Remove(i)
            	Exit	
        	End If
    	Next
	End Method
	
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function


End Class

Class map
	Field mapwidth:Int
	Field mapheight:Int
	Field screenwidth:Int
	Field screenheight:Int
	Field tilewidth:Float
	Field tileheight:Float
	Field map:Int[,]
	Field covermap:Int[,]
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		Self.screenheight = screenheight
		Self.screenwidth = screenwidth
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		tilewidth = Float(screenwidth) / Float(mapwidth)
		tileheight = Float(screenheight) / Float(mapheight)
		map = New Int[mapwidth,mapheight]
		covermap = New Int[mapwidth,mapheight]
		makemap(10)
	End Method

	Method makemap:Void(numobstacles:Int)
	    For Local y:Int=0 Until mapheight
	    For Local x:int=0 Until mapwidth
	        map[x,y] = 0
	    Next
	    Next
		' Here we create short lines on the map
		' and sometimes draw some random blocks near them.
		For Local i:Int=0 Until numobstacles
			Local x1:Int=Rnd(4,mapwidth-4)
			Local y1:Int=Rnd(4,mapheight-4)
			Local dist:Int=Rnd(3,5)
			Local angle:Int=Rnd(0,360)
			Local x2:Float=x1
			Local y2:Float=y1
			While dist >= 0
				x2 += Cos(angle) * 1
				y2 += Sin(angle) * 1
				dist -= 1
				If x2<0 Or y2<0 Or x2>=mapwidth Or y2>=mapheight Then continue
				map[x2,y2] = 1000
'				If Rnd(10) < 2 Then
'					If x2>2 And x2<mymap.mapwidth-2 And y2>2 And y2<mymap.mapheight-2 Then
'						map[x2+Rnd(-1,1)][y2+Rnd(-1,1)] = 10
'					end if
'				End If
			Wend			
		Next
	End Method

	Method mapcollide:Bool(x:Int,y:Int,w:Int,h:Int)
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
		If lefttopx < 0 Or lefttopx >= mapwidth Then Return True
		If lefttopy < 0 Or lefttopy >= mapheight Then Return True
		If righttopx < 0 Or righttopx >= mapwidth Then Return True
		If righttopy < 0 Or righttopy >= mapheight Then Return True
		If leftbottomx < 0 Or leftbottomx >= mapwidth Then Return True
		If leftbottomy < 0 Or leftbottomy >= mapheight Then Return True
		If rightbottomx < 0 Or rightbottomx >= mapwidth Then Return True
		If rightbottomy < 0 Or rightbottomy >= mapheight Then Return True
		
		If map[lefttopx,lefttopy] <> 0 Then Return True
		If map[righttopx,righttopy] <> 0 Then Return True
		If map[leftbottomx,leftbottomy] <> 0 Then Return True
		If map[rightbottomx,rightbottomy] <> 0 Then Return True						
		Return False
	End Method

	Method drawmap:Void(canvas:Canvas)
	    For Local y:Int=0 Until mapheight
	    For Local x:Int=0 Until mapwidth
	        If map[x,y] = 1000
	       	canvas.Color = Color.White
	        canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
	        End If
	    Next
	    Next
	End Method

	Method drawcovermap:Void(canvas:Canvas)
	    For Local y:Int=0 Until mapheight
	    For Local x:Int=0 Until mapwidth
			If covermap[x,y] = 1
				canvas.Color = New Color(0,0.1,0)
				canvas.DrawOval(x*mymap.tilewidth,y*mymap.tileheight,tilewidth,tileheight)
			End If
	    Next
	    Next		
	End Method

	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	    Return Abs(x2-x1)+Abs(y2-y1)
	End Function

	
End Class

' The open list used by the astar
Class openlist
    Field x:Int
    Field y:Int
    Field f:Int
    Field g:Int
    Field h:Int
    Field px:Int
    Field py:Int
    Method New(    x:Int=0,y:Int=0,f:Int=0,
                g:Int=0,h:Int=0,px:Int=0,py:Int=0)
        Self.x=x
        Self.y=y
        Self.f=f
        Self.g=g
        Self.h=h
        Self.px=px
        Self.py=py
    End Method
End Class

' The closed list used by the astar
Class closedlist
    Field x:Int
    Field y:Int
    Field px:Int
    Field py:Int 
    Method New(x:Int,y:Int,px:Int,py:Int)
        Self.x = x
        Self.y = y
        Self.px = px
        Self.py = py
    End Method
End Class
' the pathnodes (x and y variables)
' used by the astar
Class pathnode
    Field x:Int
    Field y:Int
    Method New(x:Int,y:Int)
        Self.x = x
        Self.y = y
    End Method
End Class

Global mymap:map
Global myastar:astar
Global myplayer:player
Global mybullet:List<bullet> = New List<bullet>
Global myenemy:List<enemy> = New List<enemy>
Global myrpg:List<rpg> = New List<rpg>
Global myparticle:List<particle> = New List<particle>
Global myhud:hud
Global mysmoke:List<smoke> = New List<smoke>


Class MyWindow Extends Window
	Field playerwins:Int
	Field enemywins:Int

	Method New()
		mymap = New map(Width,Height,30,30)
    	myastar = New astar()
		myplayer = New player()
		myhud = New hud(Width,Height)
		For Local i:Int=0 Until 10
			myenemy.AddLast(New enemy())
		Next
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Clear(Color.Black)
		update()
		
        mymap.drawmap(canvas)        
        mymap.drawcovermap(canvas)
        For Local i:=Eachin myenemy
        	i.draw(canvas)
        Next

        For Local i:=Eachin mybullet
        	i.draw(canvas)
        Next

        For Local i:=Eachin myrpg
        	i.draw(canvas)
        Next
        
        For Local i:=Eachin myparticle
        	i.draw(canvas)
        Next

        
        For Local i:=Eachin mysmoke
        	i.draw(canvas)
        Next


        myplayer.draw(canvas)
	    myhud.draw(canvas)

        'drawdebug(canvas)
        canvas.Color = Color.White
        canvas.DrawText("AI - 'Taking Cover' Locations - Example. (' = new level)",0,Height-15)
        canvas.DrawText("Controls - cursor u/d/l/r and F - fire",0,15)
        canvas.DrawText("Matches Player Wins : " + playerwins + " vs Enemy Wins : " + enemywins,Width/2,0,.5,0)
		
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	Method update:Void()
    	myplayer.update()
    	
    	For Local i:=Eachin myenemy
    		i.update()
    	Next
    	For Local i:=Eachin myenemy
    		If i.deleteme = True Then myenemy.Remove(i)
    	Next

    	
    	For Local i:=Eachin mybullet
    		i.update()
    	Next
    	For Local i:=Eachin mybullet
    		If i.deleteme = True Then mybullet.Remove(i)
    	Next

 	  	For Local i:=Eachin myrpg
    		i.update()
    	Next
    	For Local i:=Eachin myrpg
    		If i.deleteme = True Then myrpg.Remove(i)
    	Next


 	  	For Local i:=Eachin myparticle
    		i.update()
    	Next
    	For Local i:=Eachin myparticle
    		If i.deleteme = True Then myparticle.Remove(i)
    	Next


 	  	For Local i:=Eachin mysmoke
    		i.update()
    	Next
    	For Local i:=Eachin mysmoke
    		If i.deleteme = True Then mysmoke.Remove(i)
    	Next

		myhud.update()

		' if no more enemies then reset level
		If myenemy.Empty Or myplayer.died Or Keyboard.KeyHit(Key.Apostrophe)
			If myplayer.died Then enemywins+=1 
			If myenemy.Empty Then playerwins+=1
			mymap = New map(Width,Height,30,30)
    		myastar = New astar()
			myenemy = New List<enemy>
			mybullet = New List<bullet>
			myrpg = New List<rpg>
			myparticle = New List<particle>
			mysmoke = New List<smoke>

			myplayer = New player()

			For Local i:Int=0 Until 10
				myenemy.AddLast(New enemy())
			Next
			
		End If

		
	End Method
End	Class

Function drawdebug(canvas:Canvas)
       canvas.Color = Color.White
       For Local i:=Eachin myenemy
        	i.drawpath(canvas)
        Next
		Return
        canvas.Scale(.7,.7)
        For Local y:Int=0 Until mymap.mapwidth
        For Local x:Int=0 Until mymap.mapheight
        	canvas.DrawText(myastar.map[x,y],(x*mymap.tilewidth)*1.4,(y*mymap.tileheight)*1.4)
        Next
        Next
End Function


Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
