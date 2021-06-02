#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global tilew:Int=24,tileh:Int=24
Global screenw:Int=640
Global screenh:Int=480


Class particle
	Field px:Float,py:Float,pangle:Float
	Field ps:Float=2.0+Rnd(2)
	Field pw:Int,ph:Int
	Field deleteme:Bool
	Field col:Color
	Field timeout:Int=200
	Field fadeout:Float=1
	Field fadeinc:Float
	Method New(x:Int,y:Int,angle:Float)
		Self.px = x
		Self.py = y
		col = Color.Red
		If Rnd()<.2 Then col = Color.Red.Blend(Color.Yellow,Rnd(0.1,0.5))
		If Rnd()<.2 Then col = Color.Grey.Blend(Color.Black,Rnd())
		pw = Rnd(1,5)
		ph = Rnd(1,5)
		fadeinc=1.0/ps
		'Self.pangle = angle
		pangle=Rnd(TwoPi)
	End Method
	Method update()
		
		fadeout+=fadeinc
		timeout-=1
		If timeout<=0 Then deleteme = True
		px+=Cos(pangle)*ps
		py+=Sin(pangle)*ps
		ps-=0.1
		If ps<0 Then deleteme = True ; Return
		If Rnd()<.05 Then pangle+=Rnd(-Pi,Pi)
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = col
		canvas.Alpha = fadeout
		canvas.DrawRect(px,py,pw,ph)
		canvas.Alpha = 1
	End Method
End Class
'
' Decals are graphics like spraypaints or bullet holes that get added ontop
' of the game graphics.
Class decal
	Field dx:Int,dy:Int
	Field ox:Int,oy:Int
	Field type:String="blood"
	Method New(x:Int,y:Int,type:String)
		Self.type = type
		Self.dx = x
		Self.dy = y
		ox=Rnd(tilew/8)
		oy=Rnd(tileh/8)
	End Method
	Method draw(canvas:Canvas)
		Local posx:Int=dx-(mytank.tx*tilew)+mytank.px-tilew/2
		Local posy:Int=dy-(mytank.ty*tileh)+mytank.py-tileh/2

		Select type
			Case "blood"				
				canvas.Color = Color.Red.Blend(Color.Black,.5)
				canvas.DrawOval(posx+tilew/4+ox,posy+tileh/4+oy,tilew/3,tileh/3)
		End Select
	End Method
End Class

Class soldier
	Field id:Int
	Field sx:Float,sy:Float,sw:Float,sh:Float
	Field tx:Int,ty:Int
	Field map:Int[,]
	Field targetx:Int,targety:Int
	Field targetfound:Bool=False
	Field deleteme:Bool
	Method New(id:Int,x:Int,y:Int)
		Self.id = id
		map = New Int[mymap.mw,mymap.mh]
		tx=x
		ty=y
		sx = x*tilew'(tx-mytank.tx)*tilew
		sy = y*tileh'(ty-mytank.ty)*tileh
		sw = tilew/3
		sh = tileh/3
		
		
	End Method
	Method update()
		'Return

		 'here we randomly shoot at the player 
		 ' if there is a chance of hitting. 
		If Rnd()<.01 
			If pathblocked() Then
				Local posx:Int=sx-(mytank.tx*tilew)+mytank.px-tilew/2
				Local posy:Int=sy-(mytank.ty*tileh)+mytank.py-tileh/2
				Local angle:Float=getangle(posx,posy,320,200)
				mybullet.Add(New bullet((posx+Cos(angle)*(tilew))+tilew/2,(posy+Sin(angle)*tileh)+(tileh/2),Cos(angle)*3,Sin(angle)*3,"soldier"))
			End If
		End if
	

		
		tx = (sx/tilew)
		ty = (sy/tileh)
		'
		If (Rnd()<.1 And map[tx,ty] = 0 ) Or Rnd()<0.09
			findsafespot()
		End If
		If targetfound = False And map[tx,ty] > 0
			Local lowest:Int=map[tx,ty]
			Local mx:Int,my:Int	
			Local sel:Bool
			If map[tx-1,ty]>0 And map[tx-1,ty] < lowest Then lowest = map[tx-1,ty] ; mx=-1;my=0; sel=True
			If map[tx+1,ty]>0 And map[tx+1,ty] < lowest Then lowest = map[tx+1,ty] ; mx=1;my=0; sel=True
			If map[tx,ty-1]>0 And map[tx,ty-1] < lowest Then lowest = map[tx,ty-1] ; my=-1;mx=0; sel=True
			If map[tx,ty+1]>0 And map[tx,ty+1] < lowest Then lowest = map[tx,ty+1] ; my=1;mx=0;sel=True
			If sel=True
				targetx = (tx+mx)*tilew
				targety = (ty+my)*tileh
				targetfound=True
			End If
			'tx+=mx
			'ty+=my
			'sx+=mx
			'sy+=my
			
			'sx+=Float(mx)*3
			'sy+=Float(my)*3
			
			
			
		End If
		
		' Move towards and If reaches the target position
		If targetfound = True
		If sx < targetx Then sx+=1
		If sx > targetx Then sx-=1
		If sy < targety Then sy+=1
		If sy > targety Then sy-=1
		'avoid()
		If distance(sx,sy,targetx,targety) < 6 Then 
			targetfound = False			
		End If
		End If


		collidewithplayer()

	End Method
	
	
	Method pathblocked:Bool()
		' First check if we are not goint to hit a wall or other turret
		Local posx:Int=sx-(mytank.tx*tilew)+mytank.px-tilew/2
		Local posy:Int=sy-(mytank.ty*tileh)+mytank.py-tileh/2
		Local angle:Float=getangle(posx,posy,320,200)
		Local ax:Float=posx+tilew/2,ay:Float=posy+tileh/2
		ax+=Cos(angle)*(tilew*1)
		ay+=Sin(angle)*(tileh*1)
		For Local i:Int=0 Until 300 Step 2
			If collidetile(ax,ay) Then 				
				
				Return False
			End If
			' Check if we have a chance of hitting the player
			If rectsoverlap(ax,ay,tilew,tileh,320-tilew*1.5,200-tileh*1.5,tilew*2,tileh*2) = True
				'Print "w"
				
				Return True
			End If
			'
			ax+=Cos(angle)*1
			ay+=Sin(angle)*1
			'Print ax+","+ay
		Next
		
		
		Return False
	End Method
	Method collidetile:Bool(posx:Int,posy:Int)
		Local zx:Int = (posx/tilew) + mytank.tx
		Local zy:Int = (posy/tileh) + mytank.ty
		For Local y1:Int=zy-2 To zy+2
		For Local x1:Int=zx-2 To zx+2
			If x1<0 Or y1<0 Or x1>=mymap.mw Or y1>=mymap.mh Then Continue			
			If mymap.map[x1,y1] = 1 Or mymap.map[x1,y1] = 2				
				Local x2:Int=((x1-mytank.tx)*tilew)+mytank.px-16
				Local y2:Int=((y1-mytank.ty)*tileh)+mytank.py-16
				If rectsoverlap(posx-2,posy-2,4,4,x2,y2,tilew,tileh)					
					Return True
				End If
			End If
		Next
		Next
		Return False
	End Method

	' The player is always at 320*200 so if the soldier
	' is there then he wil get squashed.
	'
	Method collidewithplayer()
		Local posx:Int=sx-(mytank.tx*tilew)+mytank.px-tilew/2
		Local posy:Int=sy-(mytank.ty*tileh)+mytank.py-tileh/2

		If rectsoverlap(posx,posy,sw,sh,320,200,mytank.w,mytank.h)
			deleteme = True

			mydecal.Add(New decal(sx,sy,"blood"))
		End If
	End Method
	
	
	
	Method align(x:Float,y:Float)
		'sx+=x
		'sy+=y
	End Method
	
	Method findsafespot()
		'Here the soldiier find sa safe spot behind a wall
		'from that spot a path is flooded so he can get there
		Local tankx:Float,tanky:Float
		tankx = (320/tilew)+mytank.tx
		tanky = (200/tileh)+mytank.ty
		Local a:Float= Rnd(TwoPi)
		For Local i:Int=0 To 20
			tankx+=Cos(a)
			tanky+=Sin(a)
			
			If tankx<0 Or tanky<0 Or tankx>=mymap.mw Or tanky>=mymap.mh Then Return
			
			If mymap.map[tankx,tanky] = 1
				For Local ii:Int=0 To 4
					tankx+=Cos(a)
					tanky+=Sin(a)
					If tankx<0 Or tanky<0 Or tankx>=mymap.mw Or tanky>=mymap.mh Then Return
					If mymap.map[tankx,tanky] = 4 Or mymap.map[tankx,tanky] = 5
						'mymap.map[tankx,tanky] = 2
						fillpos(tankx,tanky,10)
						Return
					End If
				Next
			End	if

		Next
		
	End Method
	Method fillpos(fx:Int,fy:Int,radius:Int)
		map = New Int[mymap.mw,mymap.mh]
		map[fx,fy] = 1
		Local current:Int=1
		
		For Local i:Int=0 Until radius
		For Local y:Int = fy-radius To fy+radius
		For Local x:Int = fx-radius To fx+radius
			If x<1 Or y<1 Or x>mymap.mw-1 Or y>=mymap.mh-1 Then Continue
			If map[x,y] = current Then 
				If validfilltile(x-1,y) And map[x-1,y] = 0 Then map[x-1,y] = current+1
				If validfilltile(x+1,y) And map[x+1,y] = 0 Then map[x+1,y] = current+1
				If validfilltile(x,y-1) And map[x,y-1] = 0 Then map[x,y-1] = current+1
				If validfilltile(x,y+1) And map[x,y+1] = 0 Then map[x,y+1] = current+1
			End if
		Next
		Next
			current+=1
		Next
	End Method
	Method validfilltile:Bool(x:Int,y:Int)
		Select mymap.map[x,y]
			Case 0
				Return True
			Case 1
				Return False
			Case 2
				Return False
			Default Return True
		End Select
		Return False
	End Method
	Method draw(canvas:Canvas)
		'Local posx:Int=((tx-mytank.tx)*tilew)+sx
		'Local posy:Int=((ty-mytank.ty)*tileh)+sy
		
		Local posx:Int=sx-(mytank.tx*tilew)+mytank.px-tilew/2+sw/2
		Local posy:Int=sy-(mytank.ty*tileh)+mytank.py-tileh/2+sh/2
		canvas.Color = Color.Blue
		canvas.DrawOval(posx-1,posy-1,sw+2,sh+2)
		canvas.Color = Color.Yellow
		canvas.DrawOval(posx,posy,sw,sh)
		canvas.Color = Color.Black
		canvas.DrawLine(posx,posy+sh/4,posx+sw,posy+sh/4)
		canvas.DrawLine(posx+sw/2,posy,posx+sw/2,posy+sh/1.5)
		canvas.DrawLine(posx+sw/2,posy+sh,posx+sw,posy-sh/2)
		canvas.DrawLine(posx+sw/2+1,posy+sh,posx+sw+1,posy-sh/2)
		' drawmap
		If Keyboard.KeyDown(Key.LeftShift)
			drawmap(canvas)
		End If
	End Method
	Method drawmap(canvas:Canvas)
		Local px:Int = mytank.px
		Local py:Int = mytank.py
		Local tx:Int = mytank.tx
		Local ty:Int = mytank.ty
		For Local y:Int=0 Until (screenh/tileh)+1
		For Local x:Int=0 Until (screenw/tilew)+1
			If x+tx<0 Or y+ty<0 Or x+tx>=mymap.mw Or y+ty>=mymap.mh Then Continue
			Local dx:Int=x*tilew+px-16
			Local dy:Int=y*tileh+py-16
			'Select map[x+tx,y+ty]
			canvas.Color = Color.White
			canvas.DrawText(map[x+tx,y+ty],dx+tilew/2,dy+tileh/2)
			'End Select
		Next
		Next		
	End Method
End Class

Class turret
	Field x:Float,y:Float,w:Float,h:Float
	Field mx:Int,my:Int 'on which tile in the map is it.
	Field angle:Float,destangle:Float
	Field deleteme:Bool
	Field clearshot:Bool
	Field maxdamage:Int=10
	Field damage:Int=10
	Method New(x:Int,y:Int,mx:Int,my:Int)
		Self.x = x
		Self.y = y
		Self.mx = mx
		Self.my = my
		Self.w = tilew
		Self.h = tileh
	End Method
	Method align(ax:Float,ay:Float)
		x+=ax
		y+=ay
	End Method
	Method update()
		turntoplayer()
		clearshot = pathblocked()
		If Rnd()<.01 And clearshot  Then 
			mybullet.Add(New bullet((x+Cos(angle)*(tilew))+tilew/2,(y+Sin(angle)*tileh)+(tileh/2),Cos(angle)*3,Sin(angle)*3,"turret"))
		End If
	End Method
	Method draw(canvas:Canvas)
		canvas.Alpha=.2
		canvas.Color = Color.Black
		canvas.DrawOval((x+w/2)-5,(y+h/2)-5,w,h)
		canvas.Alpha=.2
		canvas.Color = Color.Black.Blend(Color.Yellow,.2)
		canvas.DrawOval((x+w/2)-3,(y+h/2)-3,w,h)
		
		canvas.Alpha=.7
		canvas.Color = Color.Grey.Blend(Color.Yellow,.3)
		canvas.DrawOval((x+w/2)-2,(y+h/2)-2,w-4,h-4)
		canvas.Alpha=.5
		canvas.Color = Color.White
		canvas.DrawOval((x+tilew/2)+tilew/8-1,(y+tileh/2)+tileh/8-1,w/2,h/2)

		canvas.Color = Color.White
		canvas.Alpha=1
		Local x1:Float=x+w/4,y1:Float=y+h/4
		For Local i:Int=0 Until tilew/2
			x1+=Cos(angle)
			y1+=Sin(angle)			
			canvas.Color = Color.White.Blend(Color.Black,1.0-1.0/Float(tilew/2)*i)
			canvas.DrawRect(x1+tilew/2,y1+tileh/2,3,3)
		Next
		' Draw the damage bar
		Local pw:Int=tilew
		Local ph:Int=tileh/5
		Local p:Int=(pw/maxdamage+1)*damage
		canvas.Color = Color.Black
		canvas.DrawRect(x,y,pw,ph)
		If damage < 5 Then 
			canvas.Color = Color.Red
		Else
			canvas.Color = Color.Green
		End If
		canvas.DrawRect(x+1,y+1,p,ph-2)
		
		
	End Method
	
	Method pathblocked:Bool()
		' First check if we are not goint to hit a wall or other turret
		Local ax:Float=x+tilew/2-w/4,ay:Float=y+tileh/2-h/4
		ax+=Cos(angle)*(tilew*1.5)
		ay+=Sin(angle)*(tileh*1.5)
		For Local i:Int=0 Until 100 Step 2
			If collidetile(ax,ay) Then 
				Return False
			End If
			' Check if we have a chance of hitting the player
			If rectsoverlap(ax,ay,tilew,tileh,320-tilew*1.5,200-tileh*1.5,tilew*2,tileh*2) = True
				Return True
			End If
			'
			ax+=Cos(angle)*5
			ay+=Sin(angle)*5
		Next
		
		
		Return False
	End Method
	Method collidetile:Bool(posx:Int,posy:Int)
		Local zx:Int = (posx/tilew) + mytank.tx
		Local zy:Int = (posy/tileh) + mytank.ty
		For Local y1:Int=zy-2 To zy+2
		For Local x1:Int=zx-2 To zx+2
			If x1<0 Or y1<0 Or x1>=mymap.mw Or y1>=mymap.mh Then Continue			
			If mymap.map[x1,y1] = 1 Or mymap.map[x1,y1] = 2				
				Local x2:Int=((x1-mytank.tx)*tilew)+mytank.px-16
				Local y2:Int=((y1-mytank.ty)*tileh)+mytank.py-16
				If rectsoverlap(posx-2,posy-2,4,4,x2,y2,tilew,tileh)					
					Return True
				End If
			End If
		Next
		Next
		Return False
	End Method

	Method turntoplayer()
		destangle = getangle(x,y,320,200)
		' Make the angle and target angle suitable for comapisment		
		If (destangle >= (angle + Pi))
		    angle += TwoPi
		Elseif (destangle < (angle - Pi))
		        destangle += TwoPi
		End If		
		' .05 is the turn speed
		Local directiondiff:Float = destangle - angle
		
		If (directiondiff < -.007)
		    directiondiff = -.007
		End If
		If (directiondiff > .007)
		    directiondiff = .007
		End If
		angle+=directiondiff
	End Method

End Class

Class bullet
	Field x:Float,y:Float
	Field w:Float,h:Float
	Field timeout:Int
	Field owner:String="player"
	Field deleteme:Bool=False
	Field mx:Float,my:Float
	Field radius:Int
	Field angle:Float
	Field glow:Float
	Field glowtime:Float
	Field glowinc:Float=0.1
	Method New(x:Int,y:Int,mx:Float,my:Float,owner:String="player")
		Self.x = x
		Self.y = y
		Self.mx = mx
		Self.my = my
		If owner = "player" Or owner="turret" Then radius = 3
		If owner = "soldier" Then radius = 1
		Self.owner = owner
		timeout = 2000
	End Method
	Method update(canvas:Canvas)
		'glowtime+=.5
		'If glowtime>1 Then 
		'	glowtime=0
			glow+=glowinc
			If glow>1.0 Then glowinc=-glowinc ; glow=1.0
			If glow<0 Then glowinc=-glowinc ; glow=0
		'End If
		
		timeout-=1
		If timeout<0 Then deleteme=True
		x+=mx
		y+=my
		If owner = "player" Then collidetile(canvas,1,1)
		If owner = "turret" Then collideplayer()
		If owner = "soldier" Then collideplayer2()
	End Method
	Method align(mmx:Float,mmy:Float)
		x += mmx
		y += mmy
	End Method
	Method collideplayer2()
		If rectsoverlap(320-tilew/2,200-tileh/2,tilew,tileh,x-1,y-1,3,3)
			If Rnd()<.2 And mytank.damage>0 Then mytank.damage-=1
			deleteme = True
		End If
	End Method

	Method collideplayer()
		If rectsoverlap(320-tilew/2,200-tileh/2,tilew,tileh,x-1,y-1,3,3)
			If mytank.damage>0 Then mytank.damage-=1
			deleteme = True
		End If
	End Method
	Method collidetile(canvas:Canvas,posx:Int,posy:Int)
		Local zx:Int = (x/tilew) + mytank.tx
		Local zy:Int = (y/tileh) + mytank.ty
		For Local y1:Int=zy-2 To zy+2
		For Local x1:Int=zx-2 To zx+2
			If x1<0 Or y1<0 Or x1>=mymap.mw Or y1>=mymap.mh Then Continue
			
			If mymap.map[x1,y1] = 1 Or mymap.map[x1,y1] = 2
				
				Local x2:Int=((x1-mytank.tx)*tilew)+mytank.px-16
				Local y2:Int=((y1-mytank.ty)*tileh)+mytank.py-16
				If rectsoverlap(x-2,y-2,4,4,x2,y2,tilew,tileh)
					If mymap.map[x1,y1] = 1 And Rnd()<.2 Then mymap.map[x1,y1] = 0 ; mymap.tilemap[x1,y1] = 22
					canvas.Color = Color.Red.Blend(Color.Yellow,Rnd())
					canvas.DrawRect(x2,y2,tilew,tileh)			
					deleteme = True
					For Local z:Int=0 Until 20+Rnd(100)
						myparticle.Add(New particle(x2,y2+tileh/2,angle))
					Next
					For Local i:turret = Eachin myturret						
						If i.mx = x1 And i.my = y1 Then 
							i.damage-=1
							If i.damage<=0 Then 
								i.deleteme = True
								mymap.map[x1,y1] = 0
								mymap.tilemap[x1,y1] = 22
							End If
						End If
					Next
				End If
			End If
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Yellow.Blend(Color.Black,glow/3)
		canvas.Alpha = 1.0-glow/3
		canvas.DrawCircle(x,y,radius)
		canvas.Alpha = 1
	End Method
End Class

Class playertank
	Field x:Float,y:Float,w:Int,h:Int
	Field tx:Int,ty:Int 'tile x and y pos
	Field px:Float,py:Float 'tank pixel x and y
	Field angle:Float
	Field maxdamage:Int=10
	Field damage:Int=10
	Method New(tx:Int,ty:Int)
		' tile x and y position
		Self.tx = tx ; Self.ty = ty
		' tank pixel x and y position
		Self.x = tx*tilew ; Self.y = ty*tileh
		Self.w = tilew/2
		Self.h = tileh/2
	End Method
	Method controlmap()
		If Keyboard.KeyReleased(Key.Left) Then tx -=1		
		If Keyboard.KeyReleased(Key.Right) Then tx +=1
		If Keyboard.KeyReleased(Key.Up) Then ty -=1
		If Keyboard.KeyReleased(Key.Down) Then ty +=1		
	End Method
	Method controltank()
		
		If Keyboard.KeyReleased(Key.Space)
			mybullet.Add(New bullet((320+w/2)-(Cos(angle)*w),(200+h/2)-(Sin(angle)*h),-Cos(angle)*4,-Sin(angle)*4))
		End If
		If Keyboard.KeyDown(Key.Left)
			angle-=.1
		End If
		If Keyboard.KeyDown(Key.Right)
			angle+=.1
		End If

		If Keyboard.KeyDown(Key.Up) 
			Local xx:Float=Cos(angle)*1,yy:Float=Sin(angle)*1
			 ' First move ahead
			px += xx
			py += yy
			' If we touch a tile then move back and return
		 	If collidetile(xx,yy) = True Then
				px -= xx
				py -= yy
				Return
			End If
			
			' update the bullets with the new scroll posotion	
			For Local i:bullet = Eachin mybullet
				i.align(xx,yy)
			Next
			' udpat the turrets with the new scroll position
			For Local i:turret = Eachin myturret
				i.x+=xx
				i.y+=yy
			Next
			' udpat the soldiers with the new scroll position
			For Local i:soldier = Eachin mysoldier
				i.align(xx,yy)
				'i.sx+=xx
				'i.sy+=yy
			Next			
			' Scroll the actual tiles if we moved a tile dimension		
			Local ax:Int,ay:Int
			If px>=tilew-1 Then px-=tilew ; tx-=1 ; ax=-1
			If ax=0 And px<0 Then px+=tilew ; tx+=1 ; ax = 1
			If py>=tileh-1 Then py-=tileh ; ty-=1 ; ay=-1
			If ay=0 And py<0 Then py+=tileh ; ty+=1 ; ay=1
		End If
	End Method
	Method collidetile:Bool(posx:Int,posy:Int)
		Local zx:Int = ((320-tilew/2+posx)/tilew) + mytank.tx
		Local zy:Int = ((200-tileh/2+posy)/tileh) + mytank.ty
		For Local y1:Int=zy-2 To zy+2
		For Local x1:Int=zx-2 To zx+2
			If x1<0 Or y1<0 Or x1>=mymap.mw Or y1>=mymap.mh Then Continue
			
			If mymap.map[x1,y1] = 1 Or mymap.map[x1,y1] = 2
				
				Local x2:Int=((x1-mytank.tx)*tilew)+mytank.px-16
				Local y2:Int=((y1-mytank.ty)*tileh)+mytank.py-16
				If rectsoverlap(320,200,w,h,x2,y2,tilew,tileh)
					Return True
				End If
			End If
		Next
		Next
		Return False
	End Method
	
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawOval(320,200,w,h)
		canvas.PushMatrix()
		canvas.Translate(320+w/2,200+h/2)
		canvas.Rotate(-angle)
		
		canvas.DrawRect(-12,-4,7,4)
		'canvas.DrawRect(0,-8,10,16)
		
		canvas.PopMatrix()
		'draw the damage bar
		Local dw:Int=w
		Local dh:Int=h/4
		Local d:Int=(dw/maxdamage)*damage
		canvas.Color = Color.Black
		canvas.DrawRect(320,200-dh,dw,dh)
		If damage>maxdamage/3 Then 
			canvas.Color = Color.Green
		Elseif damage<maxdamage/3
			canvas.Color = Color.Yellow
		Else
			canvas.Color = Color.Red
		End If
		canvas.DrawRect(320+1,200-dh+1,d,dh-2)
	End Method
End Class

Class mainmap
	' screen width/height, map width/height, tile width/height
	Field sw:Int,sh:Int,mw:Int,mh:Int,tw:Float,th:Float
	Field brushmap:String[]
	Field map:Int[,] '
	Field tilemap:Int[,] 'the aactual tile graphics
	Field im:=New Image[80]
	Field can:=New Canvas[80]
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		Self.sw = sw ; Self.sh = sh
		Self.mw = mw ; Self.mh = mh
		Self.tw = tilew ; Self.th = tileh
		map = New Int[mw,mh]
		tilemap = New Int[mw,mh]
		'createmap(5,5)
		createrandommap()
		createtiles()
'		tilemap[20,20] = 41'left
'		tilemap[21,20] = 40'center
'		tilemap[22,20] = 42'right
'		tilemap[21,19] = 43'top
'		tilemap[21,21] = 44'bottom
'		tilemap[20,19] = 45 'left top
'		tilemap[22,19] = 46 'Right top
'		tilemap[20,21] = 47 'left bottom
'		tilemap[22,21] = 48 'right bottom
'	
	End Method
	Method createtiles()
		Local numtiles:Int=79
		For Local i:Int=0 To numtiles
			im[i] = New Image(tilew,tileh)
			can[i] = New Canvas(im[i])
			can[i].Color = Color.Black
			can[i].DrawRect(0,0,tilew,tileh)
			
			can[i].Flush()
		Next
		
		
		
		
		'create tile 4 (grass tile)
		Local ct:Int=4
		can[ct].Color = Color.Green.Blend(Color.Black,.8)
		can[ct].DrawRect(0,0,tilew,tileh)
		'noise
		For Local i:Int=0 Until 10
			Local x:Int=Rnd(-3,tilew+6)
			Local y:Int=Rnd(-3,tileh+6)
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(.75,.8))
			can[ct].DrawRect(x,y,3,3)
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(.75,.8))
			can[ct].DrawRect(x,y,1,1)
		Next
		'grass
		For Local i:Int=0 Until 8
			Local h:Int=Rnd(1,3)
			Local x:Int=Rnd(-2,tilew+4)
			Local y:Int=Rnd(-2,tileh+4)
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(0.75,0.8))
			Local y2:Int
			For y2=y To y+h
				can[4].DrawPoint(x,y2)
			Next
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(0.75,0.8))
			can[ct].DrawPoint(x,y2)
			can[ct].DrawPoint(x,y2+1)
		Next
		can[ct].Flush()
		
		' grass tile below wall (SHADE)
		ct=10		
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[4],0,0)
		can[ct].Alpha = 0.5
		can[ct].Color = Color.Black
		can[ct].DrawRect(0,0,tilew,tileh/6)
		can[ct].Alpha=1
		can[ct].Flush()
		' grass tile RIGHT of wall (SHADE)
		ct=11
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[4],0,0)
		can[ct].Alpha = 0.5
		can[ct].Color = Color.Black		
		can[ct].DrawRect(0,0,tilew/6,tileh)
		can[ct].Alpha=1
		can[ct].Flush()

		' Sand inside grass
		' sand 2
		ct=40
		can[ct].Alpha = 1
		can[ct].Color = Color.Brown.Blend(Color.Yellow,.05)
		can[ct].DrawRect(0,0,tilew,tileh)
		'noise
		For Local i:Int=0 Until 10
			Local x:Int=Rnd(-3,tilew+6)
			Local y:Int=Rnd(-3,tileh+6)
			can[ct].Alpha = Rnd()
			can[ct].Color = Color.Brown.Blend(Color.Black,Rnd(.75,.8))
			can[ct].DrawRect(x,y,2,2)
			can[ct].Color = Color.Brown.Blend(Color.Black,Rnd(.75,.8))
			can[ct].DrawRect(x,y,1,1)
		Next
		can[ct].Alpha=1
		For Local i:Int=0 Until 8
			Local h:Int=Rnd(1,3)
			Local x:Int=Rnd(-2,tilew+4)
			Local y:Int=Rnd(-2,tileh+4)
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(0.75,0.8))
			Local y2:Int
			For y2=y To y+h
				can[4].DrawPoint(x,y2)
			Next
			can[ct].Color = Color.Green.Blend(Color.Black,Rnd(0.75,0.8))
			can[ct].DrawPoint(x,y2)
			can[ct].DrawPoint(x,y2+1)
		Next

'		can[ct].Alpha = 1
'		can[ct].Color = Color.White
'		can[ct].Color = Color.Brown.Blend(Color.Black,.25)
'		can[ct].DrawRect(0,0,tilew,tileh)
'		For Local i:Int=0 Until 40
'			Local x:Int=Rnd(tilew)
'			Local y:Int=Rnd(tileh)
'			can[ct].Color = Color.Brown.Blend(Color.Black,Rnd(.2,.8))
'			can[ct].DrawRect(x,y,Rnd(1,3),Rnd(1,3))
'			can[ct].Color = Color.Brown.Blend(Color.Yellow,Rnd(.1,.3))
'			can[ct].DrawRect(x,y,1,1)
'		Next
		can[ct].Flush()
		' 
		' Left side edge is grass right side is sand
		ct = 41
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x+2,y)
		Next				
		can[ct].Flush()
		' Right side edge is grass right side is sand
		ct = 42
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=tw Until tw-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.3)
			can[ct].DrawPoint(x-2,y)
		Next				
		can[ct].Flush()
		' Top side edge is grass right side is sand
		ct = 43
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x,y+1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x,y+2)
		Next				
		can[ct].Flush()
		' Bottom side edge is grass right side is sand
		ct = 44
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=th Until th-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-2)
		Next				
		can[ct].Flush()


		' Left top grass base is sand
		ct = 45
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		
		Local l:Int=0
		For Local y:Int=th To 0 Step -1
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=0 Until l+m
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.7)
			can[ct].DrawPoint(x+2,y)			
			l+=1
		Next
		can[ct].Flush()

		' Right top grass base is sand
		ct = 46
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		
		l=0
		For Local y:Int=th To 0 Step -1
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=tw Until tw-(l+m) Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x-2,y)			
			l+=1
		Next
		can[ct].Flush()
		

		' Left bottom grass base is sand
		ct = 47
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		
		l=0
		For Local y:Int=0 To th 
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=0 Until l+m
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.7)
			can[ct].DrawPoint(x+2,y)			
			l+=1
		Next
		can[ct].Flush()
		

		' Right bottom grass base is sand
		ct = 48
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		
		l=0
		For Local y:Int=0 To th
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=tw Until tw-(l+m) Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x-2,y)			
			l+=1
		Next
		can[ct].Flush()

		' left and right grass center sand
		ct=49
		' Right side edge is grass right side is sand
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=tw Until tw-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.3)
			can[ct].DrawPoint(x-2,y)
		Next				
		' Left side edge is grass right side is sand
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x+2,y)
		Next				
		can[ct].Flush()
		
		
		' top and bottom grass center sand
		ct=50
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[40],0,0)
		'bottom
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=th Until th-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-2)
		Next				
		'top
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x,y+1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x,y+2)
		Next				
		can[ct].Flush()	
		
		' sand tile
		ct=5
		can[ct].Color = Color.Brown.Blend(Color.Black,.45)
		can[ct].DrawRect(0,0,tilew,tileh)
		For Local i:Int=0 Until 40
			Local x:Int=Rnd(tilew)
			Local y:Int=Rnd(tileh)
			can[ct].Color = Color.Brown.Blend(Color.Black,Rnd(.2,.8))
			can[ct].DrawRect(x,y,Rnd(1,3),Rnd(1,3))
			can[ct].Color = Color.Brown.Blend(Color.Yellow,Rnd(.1,.3))
			can[ct].DrawRect(x,y,1,1)
		Next
		can[ct].Flush()
	
		' Sand under wall or turret
		ct=14
		can[ct].Color = Color.White
		can[ct].DrawImage(im[5],0,0)
		can[ct].Alpha = 0.5
		can[ct].Color = Color.Black
		can[ct].DrawRect(0,0,tilew,tileh/6)
		can[ct].Alpha = 1
		can[ct].Flush()
		' Sand Right of wall or turret
		ct=15
		can[ct].Color = Color.White
		can[ct].DrawImage(im[5],0,0)
		can[ct].Alpha = 0.5
		can[ct].Color = Color.Black
		can[ct].DrawRect(0,0,tilew/6,tileh)
		can[ct].Alpha = 1
		can[ct].Flush()

	
		'turret tile (2)
		ct=2
		can[ct].Color = Color.Grey.Blend(Color.Black,.3)
		can[ct].DrawRect(0,0,tilew,tileh)
		'noise
		For Local i:Int=0 Until 130
			Local x:Int=Rnd(tilew)
			Local y:Int=Rnd(tileh)
			can[ct].Color = Color.Grey.Blend(Color.Black,Rnd())
			can[ct].DrawRect(x,y,2,2)
			can[ct].Color = Color.Grey.Blend(Color.White,Rnd(.6,.7))
			can[ct].DrawRect(x,y,1,1)
		Next
		can[ct].Flush()		
	
	
		'wall tile(1)
		ct=2
		can[ct].Color = Color.Grey
		can[ct].DrawRect(0,0,tilew,tileh)
		can[ct].Color = Color.Grey.Blend(Color.Black,.5)
		can[ct].DrawLine(0,tileh-1,tilew,tileh-1)
		can[ct].DrawLine(0,tileh-2,tilew,tileh-2)
		can[ct].DrawLine(0,tileh-3,tilew,tileh-3)
		can[ct].DrawLine(tilew-1,0,tilew-1,tileh-1)
		can[ct].DrawLine(tilew-2,0,tilew-2,tileh-1)
		can[ct].DrawLine(tilew-3,0,tilew-3,tileh-1)
		can[ct].Color = Color.Grey.Blend(Color.Black,.3)
		can[ct].DrawRect(3,3,tilew-6,tileh-6)
		'noise
		For Local i:Int=0 Until 30
			Local x:Int=Rnd(tilew)
			Local y:Int=Rnd(tileh)
			can[ct].Color = Color.Grey.Blend(Color.Black,Rnd())
			can[ct].DrawRect(x,y,2,2)
			can[ct].Color = Color.Grey.Blend(Color.White,Rnd(.6,.7))
			can[ct].DrawRect(x,y,1,1)
		Next

		can[ct].Flush()		

		'broken wall tile
		ct = 22
		can[ct].Color = Color.White
		can[ct].DrawImage(im[5],0,0)
		For Local i:Int=0 Until 180
			can[ct].Color = Color.Grey.Blend(Color.Black,Rnd())
			can[ct].Alpha = Rnd()
			If Rnd()<.3 Then can[ct].Alpha=1
			Local x1:Float,y1:Float,x2:Float,y2:Float,x3:Float,y3:Float
			x1 = Rnd(-3,tilew+3)
			y1 = Rnd(-3,tileh+3)
			If Rnd()<.5 And distance(x1,y1,tilew/2,tileh/2) > tilew/2 Then Continue
			x2 = x1 + Rnd(1,5)
			y2 = y1 + Rnd(-3,3)
			x3 = x1 + Rnd(1,6)
			y3 = y2 + Rnd(1,6)
			can[ct].DrawTriangle(x1,y1,x2,y2,x3,y3)
			If Rnd()<.3 Then 
				can[ct].Color=Color.Black
				can[ct].DrawTriangle(x1-1,y1-1,x2-1,y2-1,x3-1,y3-1)
			End If
		Next
		can[ct].Alpha=1
		can[ct].Flush()

		' Flag tile (3) sand+flag
		ct=3
		can[ct].Color = Color.Brown.Blend(Color.Black,.45)
		can[ct].DrawRect(0,0,tilew,tileh)
		For Local i:Int=0 Until 40
			Local x:Int=Rnd(tilew)
			Local y:Int=Rnd(tileh)
			If distance(tilew/2,tileh/2,x,y) < tilew/2 Then continue
			can[ct].Color = Color.Brown.Blend(Color.Black,Rnd(.2,.8))
			can[ct].DrawRect(x,y,Rnd(1,3),Rnd(1,3))
			can[ct].Color = Color.Brown.Blend(Color.Yellow,Rnd(.1,.3))
			can[ct].DrawRect(x,y,1,1)
		Next
		'flag
		
		
		can[ct].Color=Color.Brown.Blend(Color.White,.5)
		can[ct].DrawRect(tilew/4,0,tilew/10,tileh)
		can[ct].Color=Color.Brown
		can[ct].DrawRect((tilew/4)+1,0,tilew/10,tileh)
		can[ct].Color=Color.Black.Blend(Color.Brown,.3)
		can[ct].DrawRect(tilew/4+2,0,tilew/10,tileh)
		can[ct].Color=Color.Red
		can[ct].DrawRect(tilew/3,0,tilew/3,tileh/3)
		can[ct].Color=Color.Red.Blend(Color.White,.2)
		can[ct].DrawRect(tilew/3,tileh/8,tilew/3,tileh/8)

		can[ct].Flush()


		' Tree tile
		ct = 30
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[4],0,0)
		Local tmp:Image = New Image(32,32)
		tmp = createtree()
		can[ct].DrawImage(tmp,0,0,0,.5,.5)
		can[ct].Flush()
		
		'create water tile		
		ct=60
		can[ct].Alpha=1
		can[ct].Color = Color.White
		Local tmpim:Image
		tmpim = New Image(tw,th)
		tmpim = createwater()
		can[ct].DrawImage(tmpim,0,0)
		can[ct].Flush()

		' 
		' Left side edge is grass right side is water
		ct = 61
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x+2,y)
		Next				
		can[ct].Flush()
		' Right side edge is grass right side is water
		ct = 62
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=tw Until tw-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.3)
			can[ct].DrawPoint(x-2,y)
		Next				
		can[ct].Flush()
		' Top side edge is grass right side is water
		ct = 63
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x,y+1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x,y+2)
		Next				
		can[ct].Flush()
		' Bottom side edge is grass right side is water
		ct = 64
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=th Until th-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-2)
		Next				
		can[ct].Flush()


		' Left top grass base is water
		ct = 65
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		
		l=0
		For Local y:Int=th To 0 Step -1
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=0 Until l+m
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.7)
			can[ct].DrawPoint(x+2,y)			
			l+=1
		Next
		can[ct].Flush()

		' Right top grass base is sand
		ct = 66
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		
		l=0
		For Local y:Int=th To 0 Step -1
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=tw Until tw-(l+m) Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x-2,y)			
			l+=1
		Next
		can[ct].Flush()
		

		' Left bottom grass base is water
		ct = 67
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		
		l=0
		For Local y:Int=0 To th 
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=0 Until l+m
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.7)
			can[ct].DrawPoint(x+2,y)			
			l+=1
		Next
		can[ct].Flush()


		' Right bottom grass base is water
		ct = 68
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		
		l=0
		For Local y:Int=0 To th
			Local x:Int
			Local m:Int=Rnd(1,4)
			For x=tw Until tw-(l+m) Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x-2,y)			
			l+=1
		Next
		can[ct].Flush()

		' left and right grass center water
		ct=69
		' Right side edge is grass right side is sand
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=tw Until tw-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.1)
			can[ct].DrawPoint(x-1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.3)
			can[ct].DrawPoint(x-2,y)
		Next				
		' Left side edge is grass right side is sand
		For Local y:Int=0 Until th
			Local l:Int=Rnd(4,7)
			Local x:Int
			For x=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x+1,y)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x+2,y)
		Next				
		can[ct].Flush()
		
		
		' top and bottom grass center water
		ct=70
		can[ct].Alpha = 1
		can[ct].Color = Color.White
		can[ct].DrawImage(im[60],0,0)
		'bottom
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=th Until th-l Step -1
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.White,.2)
			can[ct].DrawPoint(x,y-2)
		Next				
		'top
		For Local x:Int=0 Until tw
			Local l:Int=Rnd(4,7)
			Local y:Int
			For y=0 Until l
				can[ct].Color = can[4].GetPixel(x,y)
				can[ct].DrawPoint(x,y)
			Next
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.5)
			can[ct].DrawPoint(x,y+1)
			can[ct].Color = can[4].GetPixel(x,y).Blend(Color.Black,.8)
			can[ct].DrawPoint(x,y+2)
		Next				
		can[ct].Flush()	


		
	End Method
	Method createtree:Image()
		Local im:Image
		Local can:Canvas
		im = New Image(32,32)
		can = New Canvas(im)
		can.Clear(Color.Green.Blend(Color.Black,.8))
		can.Flush()
		
		Local m:Int[,] = New Int[32,32]
		'create spot
		Local a:Float

		Local posx:Float
		Local posy:Float
		For Local ii:Int=0 Until 15
		Local x1:Float=Rnd(10,25)
		Local y1:Float=Rnd(1,16)
		a = 0
		For Local i:Int=0 Until 20
			x1+=Cos(a)
			y1+=Sin(a)
			a+=Rnd(0.1,0.2)
			If x1<1 Or y1<0 Or x1>=31 Or y1>=32 Then Continue
			m[x1,y1] = 1			
			If y1>29 Then Exit
			If (y1+2)<29 And Rnd()<.5 Then m[x1,y1+1] = 2	Else m[x1,y1+1] = 1
			If (y1+3)<29 And Rnd()<.5 Then m[x1,y1+2] = 3 Else m[x1,y1+2] = 2
			If (y1+4)<29 And Rnd()<.5 Then m[x1,y1+3] = 1 Else m[x1,y1+3] = 2
		Next
		Next
		For Local ii:Int=0 Until 15
		Local x1:Float=Rnd(7,24)
		Local y1:Float=Rnd(1,16)
		a = -Pi
		For Local i:Int=0 Until 20
			x1+=Cos(a)
			y1+=Sin(a)
			a-=Rnd(0.1,0.2)
			If x1<1 Or y1<0 Or x1>=31 Or y1>=31 Then Continue
			m[x1,y1] = 1			
			If y1>28 Then Exit
			If y1+1<=30 And Rnd()<.5 Then m[x1,y1+1] = 2	Else m[x1,y1+1] = 1
			If y1+2<=29 And Rnd()<.5 Then m[x1,y1+2] = 3 Else m[x1,y1+2] = 2
			If y1+3<=27 And Rnd()<.5 Then m[x1,y1+3] = 1 Else m[x1,y1+3] = 2
		Next
		Next

		'make dark edges
		Local tmpm:Int[,] = New Int[32,32]
		For Local y1:Int=0 Until 32
		For Local x1:Int=0 Until 32
			If m[x1,y1] <> 0 Then Continue
			
			For Local y2:Int=-1 To 1
			For Local x2:Int=-1 To 1
				Local x3:Int=x1+x2
				Local y3:Int=y1+y2
				If x3<0 Or y3<0 Or x3>=32 Or y3>=32 Then Continue
				If m[x3,y3] <> 0 Then tmpm[x1,y1] = 1			
				
			Next
			Next
		Next
		Next
		For Local y1:Int=0 Until 32
		For Local x1:Int=0 Until 32
			If tmpm[x1,y1] = 1 Then m[x1,y1] = 99
		Next
		Next

		'turn into image
		Local col:Color = New Color(Color.Green.Blend(New Color(Rnd(),Rnd(),Rnd()),Rnd(0.0,.4)))
		For Local y:Int=0 Until 32
		For Local x:Int=0 Until 32
			
			If m[x,y] = 0 Then Continue
			If m[x,y] = 1
				can.Color = col.Blend(Color.Black,.5)
				If distance(16,16,x,y) > 10 Then can.Color = col.Blend(Color.Black,.7)
				If distance(10,10,x,y) < 10 Then can.Color = col.Blend(Color.Black,.1)
				
				can.DrawPoint(x,y)
			End If
			If m[x,y] = 2
				can.Color = col.Blend(Color.White,.1)
				If distance(16,16,x,y) > 10 Then can.Color = col.Blend(Color.Black,.1)
				If distance(10,10,x,y) < 10 Then can.Color = col.Blend(Color.White,.3)
				
				can.DrawPoint(x,y)
			End If
			If m[x,y] = 3
				can.Color = col.Blend(Color.White,.4)
				If distance(16,16,x,y) > 10 Then can.Color = col.Blend(Color.Black,.4)
				If distance(10,10,x,y) < 10 Then can.Color = col.Blend(Color.White,.6)
				
				can.DrawPoint(x,y)
			End If
			If Rnd()<.3 Then  'white speckels
				If Rnd()<.2 
					can.Color = col.Blend(Color.White,Rnd())
					Else
					can.Color = col.Blend(Color.Black,Rnd(0.5,1))
				End If
				can.DrawPoint(x,y)
			End if

			If m[x,y] = 99
				can.Color = col.Blend(Color.Black,Rnd(.5,1))
				can.DrawPoint(x,y)
			End If
		Next
		Next
		can.Flush()
		Return im
	End Method

	'Here we create a random topdown water tile
	Method createwater:Image()
		Local tw:Int=32,th:Int=32
		Local im:Image
		Local can:Canvas
		im = New Image(tw,th)
		can = New Canvas(im)
		can.Clear(Color.Blue.Blend(Color.White,.3))
		can.Flush()

		' Store the water layer
		Local tm:Int[,] = New Int[tw,th]
		' create our water layer
		tm = makelayer(tw,th,Rnd(100,800))
		For Local y:Int=0 Until th
		For Local x:Int=0 Until tw
			If tm[x,y] = 1 Then
				can.Color = Color.Blue.Blend(Color.White,.45)
				can.DrawPoint(x,y)
				' make tilable
				If Rnd()<.7
				If x=tw-1 Then 
					If Rnd()<.5
					can.DrawPoint(0,y)
					Else
					can.DrawPoint(tw-2,y)
					End If					
				End If
				If x=0 Then 
					If Rnd()<.5
					can.DrawPoint(tw-1,y)
					Else
					can.DrawPoint(1,y)
					End If					
				End If
				If y=th-1 Then 
					If Rnd()<.5
					can.DrawPoint(x,0)
					Else
						can.DrawPoint(x,th-2)						
					End If
				End If
				If y=0 Then 
					If Rnd()<.5
					can.DrawPoint(x,th-1)
					Else
					End If
				End If
				End If

			End If
		Next
		Next
'		' Create our top layer (lighter)
		tm = New Int[tw,th]
		tm = makelayer(tw,th,Rnd(100,800))
		For Local y:Int=0 Until th
		For Local x:Int=0 Until tw
			If tm[x,y] = 1 Then
				can.Color = Color.Blue.Blend(Color.White,.5)
				If Rnd()<.2 Then can.Color = Color.White
				' make tilable
				If Rnd()<.7
				If x=tw-1 Then 
					If Rnd()<.5
					can.DrawPoint(0,y)
					Else
					can.DrawPoint(tw-2,y)					
					End If
				End If
				If x=0 Then 
					If Rnd()<.5
					can.DrawPoint(tw-1,y)
					Else
					can.DrawPoint(1,y)
					End If
				End If
				If y=th-1 Then 
					If Rnd()<.5
					can.DrawPoint(x,0)
					Else
					can.DrawPoint(x,th-2)
					End If
				End If
				If y=0 Then 
					If Rnd()<.2
					can.DrawPoint(x,th-1)
					Else
					can.DrawPoint(x,1)
					End If
				End If
				End If
				can.DrawPoint(x,y)
			End If
		Next
		Next
		
		'finsih up
		can.Flush()
		'
		Return im
	End Method
	'
	' This creates a pattern of water reflection
	' depth is the blurry thickness (defaulted at making to 400)
	Method makelayer:Int[,](tw:Int,th:Int,deep:Int=500)	
		' We want to create points and connect those
		Local px:Stack<Int> = New Stack<Int>
		Local py:Stack<Int> = New Stack<Int>

		'create points in some kind of pattern
		Local lx:Int=0
		Local st:Int=6
		For Local ly:Int=0 Until th Step st
		For Local i:Int=0 Until 2
			lx+=Rnd(tw/2)
			If lx>=tw Then lx=Rnd(0,5)
			px.Push(lx)
			py.Push(ly)
		Next
		Next

		For Local z:Int=0 Until 16
		'fix - make sure no double y
		For Local i:Int =0 Until px.Length
		For Local j:Int=0 Until px.Length
			If i=j Then Continue
			If distance(py.Get(i),0,py.Get(j),0)<2				
				py.Set(i,Rnd(th))	
			End if
		Next
		Next
		'no double x
		For Local i:Int =0 Until px.Length
		For Local j:Int=0 Until px.Length
			If i=j Then Continue
			If distance(px.Get(i),0,px.Get(j),0)<2				
				px.Set(i,Rnd(tw))
			End if
		Next
		Next
		Next
		'
		' Here we pick one point and connect it to the nearest next point
		Local tm:Int[,] = New Int[tw,th]
		Local x:Float=px.Get(0)
		Local y:Float=py.Get(0)
		Local sx:Int=x,sy:Int=y
		Local numt:Int=px.Length
		Local numc:Int=0
		tm[x,y] = 1
		While numc<numt
			'find closest next point
			Local x2:Int,y2:Int
			Local d:Int=999
			For Local i:Int=0 Until px.Length
				If tm[px.Get(i),py.Get(i)] = 1 Then Continue				
				If distance(px.Get(i),py.Get(i),x,y) < d										
					x2 = px.Get(i)
					y2 = py.Get(i)
					d = distance(x2,y2,x,y)
				End If
			Next
			tm[x2,y2] = 1
			numc+=1
			'connect line
			While distance(x,y,x2,y2) > 1
				If x<x2 Then x+=1
				If x>x2 Then x-=1
				If y<y2 Then y+=1
				If y>y2 Then y-=1
				If Rnd()<.5 
					Local ox:Int=x,oy:Int=y
					x+=Rnd(-2,2)
					y+=Rnd(-2,2)
					If x<0 Or x>=tw Then x=ox
					If y<0 Or y>=th Then y=oy
				End If
				tm[x,y] = 1
			Wend
			x=x2
			y=y2
		Wend
		'connect start with end
		While distance(x,y,sx,sy) > 1
			If x<sx Then x+=1
			If x>sx Then x-=1
			If y<sy Then y+=1
			If y>sy Then y-=1
			If Rnd()<.3 
				Local ox:Int=x,oy:Int=y
				x+=Rnd(-2,2)
				y+=Rnd(-2,2)
				If x<0 Or x>=tw Then x=ox
				If y<0 Or y>=th Then y=oy
			End If
			
			tm[x,y] = 1
		Wend

		' tm holds the starting point of the back layer of the water
		' we now are going to grow them a little bit(edge grow)
		
		Local zi:Int
		For zi=0 To deep
			Local x1:Int=Rnd(tw)
			Local y1:Int=Rnd(th)
			If Not tm[x1,y1]=1 Then Continue
			Local x2:Int=x1+Int(Rnd(-2,2))
			Local y2:Int=y1+Int(Rnd(-2,2))
			If x2<0 Then x2=tw-1
			If x2>=tw Then x2=0
			If y2<0 Then y2=th-1
			If y2>=th Then y2=0
			tm[x2,y2] = 1
		Next
		
		Return tm
	End Method

		
	Method createrandommap()
		'terrain = 5
		Local x:Int=10
		Local y:Int=10
		Local s:Int=1
		Local l:Int
		s = Rnd(1,2)
		l = Rnd(5,15)
		For Local x1:Int=0 To l
			For Local i:Int=-s To s
				map[x+x1,y+i]=5
			Next
		Next
		s = Rnd(1,2)
		l = Rnd(15)
		Local ox:Int=Rnd(0,5)
		Local oy:Int=Rnd(-3,3)
		For Local y1:Int=0 Until l
			For Local i:Int=-s To s
				map[x+i+ox,y+y1+oy]=5				
			Next
		Next
		s = Rnd(1,2)
		l = Rnd(15)
		ox=Rnd(0,5)
		oy=Rnd(-3,3)
		For Local y1:Int=0 Until l
			For Local i:Int=-s To s
				map[x+i+ox,y+y1+oy]=5				
			Next
		Next

		' add walls
		For Local y1:Int=1 Until 40
		For Local x1:Int=1 Until 40
			If map[x1,y1] = 5 And map[x1-1,y1] = 0 Then map[x1-1,y1] = 1
			If map[x1,y1] = 5 And map[x1,y1-1] = 0 Then map[x1,y1-1] = 1
			If map[x1,y1] = 5 And map[x1,y1+1] = 0 Then map[x1,y1+1] = 1
			If map[x1,y1] = 5 And map[x1+1,y1] = 0 Then map[x1+1,y1] = 1
			
		Next
		Next
		'add turrets in corners
		For Local y1:Int=1 Until 40
		For Local x1:Int=1 Until 40
			If map[x1,y1] = 0 And map[x1+1,y1] = 1 And map[x1,y1+1] = 1 Then map[x1,y1] = 2
			If map[x1,y1] = 0 And map[x1-1,y1] = 1 And map[x1,y1+1]=1 Then map[x1,y1] = 2
			If map[x1,y1] = 0 And map[x1,y1-1] = 1 And map[x1+1,y1]=1 Then map[x1,y1] = 2
			If map[x1,y1] = 0 And map[x1,y1-1] = 1 And map[x1-1,y1]=1 Then map[x1,y1] = 2
		Next
		Next
		' add turrets
		For Local y1:Int=1 Until 40
		For Local x1:Int=1 Until 40
			If Rnd()<.5
				If map[x1,y1]=1 And map[x1+1,y1]=1 And map[x1+2,y1]=1 And map[x1+3,y1]=1 Then map[x1+2,y1] = 2
			End If
		Next
		Next	
		' add gates
		For Local y1:Int=1 Until 40
		For Local x1:Int=1 Until 40
			If map[x1,y1]=1 And map[x1+1,y1]=1 And map[x1+2,y1]=1 Then map[x1+1,y1] = 5
		Next
		Next	
		
		'plant flag
		Local planted:Bool=False
		While planted=False
			Local x1:Int=Rnd(5,40)
			Local y1:Int=Rnd(5,40)
			Local allsand:Bool=True
			For Local y2:Int=-1 To 1
			For Local x2:Int=-1 To 1
				If map[x1+x2,y1+y2] <> 5 Then allsand=False
			Next
			Next
			If allsand=True Then 
				map[x1,y1] = 3
				planted=True
			End If
		Wend

		'random walls
		Local cnt:Int=0
		For Local i:Int=0 Until 150
			Local x1:Int=Rnd(5,35)
			Local y1:Int=Rnd(5,35)
			If cnt<5 And map[x1,y1] = 5 And map[x1-1,y1-1]=5 And map[x1+1,y1+1]=5 Then map[x1,y1] = 1 ; cnt+=1
		Next

		'lengthen Then roads
		For Local y1:Int=5 To 40
		For Local x1:Int=5 To 40
			If map[x1,y1] = 5 And map[x1,y1-1]=1 And map[x1+1,y1] = 0 Then 
				For Local x2:Int=0 To 2
					map[x1+x2,y1] = 5
				Next
			End If
			If map[x1,y1] = 5 And map[x1,y1-1]=1 And map[x1-1,y1] = 0 Then 
				For Local x2:Int=0 To 2
					map[x1-x2,y1] = 5
				Next
			End If
			If map[x1,y1] = 5 And map[x1+1,y1]=1 And map[x1,y1-1] = 0 Then 
				For Local y2:Int=0 To 2
					map[x1,y1-y2] = 5
				Next
			End If
			If map[x1,y1] = 5 And map[x1+1,y1]=1 And map[x1,y1+1] = 0 Then 
				For Local y2:Int=0 To 2
					map[x1,y1+y2] = 5
				Next
			End If
			
		Next
		Next

		'add shading
		For Local y1:Int=1 Until mh-1
		For Local x1:Int=1 Until mw-1
			If (map[x1,y1] = 1 Or map[x1,y1] = 2) And map[x1,y1+1] = 0 Then tilemap[x1,y1+1] = 10
			If (map[x1,y1] = 1 Or map[x1,y1] = 2) And map[x1+1,y1] = 0 Then tilemap[x1+1,y1] = 11
			If (map[x1,y1] = 1 Or map[x1,y1] = 2) And map[x1,y1+1] = 5 Then tilemap[x1,y1+1] = 14
			If (map[x1,y1] = 1 Or map[x1,y1] = 2) And map[x1+1,y1] = 5 Then tilemap[x1+1,y1] = 15
		Next
		Next

		' create the sand tiles that are in the grass
		If 1=1
			For Local i:Int=0 Until 10
				Local t:Int[,] = New Int[mw,mh]
				Local x:Float=Rnd(25,mw)
				Local y:Float=Rnd(25,mh)
				Local angle:Float=Rnd(TwoPi)
				Local m:Float=Rnd(-1,1)
				Local l:Int=Rnd(6,25)
				For Local j:Int=0 Until l
					x+=Cos(angle)
					y+=Sin(angle)
					If Rnd()<.2 Then angle+=m
					If x<0 Or y<0 Or x>=mw Or y>=mh Then Exit
					Local ex:Bool=False
					For Local x2:Int=x-5 To x+5
					For Local y2:Int=y-5 To y+5
						If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
						If tilemap[x2,y2] <> 0 Then ex=True
					Next
					Next
					If ex = True Then Continue
					Local rad:Int=Rnd(1,2)
					If Rnd()<.2 Then rad+=1
					For Local y3:Int=y-rad To y+rad
					For Local x3:Int=x-rad To x+rad
						If x3<0 Or y3<0 Or x3>=mw Or y3>=mh Then Continue
						t[x3,y3] = 40
					Next
					Next
					
					
				Next
				'grow
				For Local i:Int=0 Until 0'30000
					Local x:Int=Rnd(mw)
					Local y:Int=Rnd(mh)
					If t[x,y] = 40
						Local x2:Int=x+Rnd(-2,2)
						Local y2:Int=y+Rnd(-2,2)
						If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
						t[x2,y2] = 40
					Endif
				Next
				
				For Local y2:Int=0 Until mh
				For Local x2:Int=0 Until mw
					If t[x2,y2] = 40 Then 
						tilemap[x2,y2] = 40
											
					End If
				Next
				Next
			
			Next 
			
			Local tr:Int[,] = New Int[mw,mh]
			For Local y:Int=1 Until mh-1
			For Local x:Int=1 Until mw-1
				Local value:Int=0
				If tilemap[x,y] = 40 Then 
					If tilemap[x,y-1] = 0 Then value+=1
					If tilemap[x+1,y] = 0 Then value+=2
					If tilemap[x,y+1] = 0 Then value+=4
					If tilemap[x-1,y] = 0 Then value+=8
					'Print value
					tr[x,y] = value
				End If
			Next
			Next
			For Local y:Int=1 Until mh-1
			For Local x:Int=1 Until mw-1
				If tr[x,y] <>0 Then  tilemap[x,y] = tr[x,y]+200
			Next
			Next			
			
			' add edges
'		tilemap[20,20] = 41'left
'		tilemap[21,20] = 40'center
'		tilemap[22,20] = 42'right
'		tilemap[21,19] = 43'top
'		tilemap[21,21] = 44'bottom
'		tilemap[20,19] = 45 'left top
'		tilemap[22,19] = 46 'Right top
'		tilemap[20,21] = 47 'left bottom
'		tilemap[22,21] = 48 'right bottom
'			
'			For Local y:Int=1 Until mh-1
'			For Local x:Int=1 Until mw-1
'				If tilemap[x,y] = 40
'					If tilemap[x-1,y] = 0 Then tilemap[x-1,y] = 41
'					If tilemap[x+1,y] = 0 Then tilemap[x+1,y] = 42
'					If tilemap[x,y-1] = 0 Then tilemap[x,y-1] = 43
'					If tilemap[x,y+1] = 0 Then tilemap[x,y+1] = 44
'					'
'					' xxx
'					' xxx
'					' xxx
'					'If tilemap[x-1,y] = 41 And tilemap[x,y-1] = 43 Then tilemap[x-1,y-1]=45
'					'If tilemap[x+1,y] = 42 And tilemap[x,y-1] = 43 Then tilemap[x+1,y-1]=46
'					'If tilemap[x-1,y] = 41 And tilemap[x,y+1] = 44 Then tilemap[x-1,y+1]=47
'					'If tilemap[x+1,y] = 42 And tilemap[x,y+1] = 44 Then tilemap[x+1,y+1]=48
'				
'					
'					
'				End If
'			Next
'			Next
		End If

		' create the water tiles that are in the grass
		If 1=1
			For Local i:Int=0 Until 10
				Local t:Int[,] = New Int[mw,mh]
				Local x:Float=Rnd(25,mw)
				Local y:Float=Rnd(25,mh)
				Local angle:Float=Rnd(TwoPi)
				Local m:Float=Rnd(-1,1)
				Local l:Int=Rnd(6,25)
				For Local j:Int=0 Until l
					x+=Cos(angle)
					y+=Sin(angle)
					If Rnd()<.2 Then angle+=m
					If x<0 Or y<0 Or x>=mw Or y>=mh Then Exit
					Local ex:Bool=False
					For Local x2:Int=x-7 To x+7
					For Local y2:Int=y-7 To y+7
						If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
						If tilemap[x2,y2] <> 0 Then ex=True
					Next
					Next
					If ex = True Then Continue
					Local rad:Int=Rnd(1,2)
					If Rnd()<.2 Then rad+=Rnd(2,3)
					For Local y3:Int=y-rad To y+rad
					For Local x3:Int=x-rad To x+rad
						If x3<0 Or y3<0 Or x3>=mw Or y3>=mh Then Continue
						t[x3,y3] = 60
					Next
					Next
					
					
				Next
				'grow
				For Local i:Int=0 Until 0'30000
					Local x:Int=Rnd(mw)
					Local y:Int=Rnd(mh)
					If t[x,y] = 60
						Local x2:Int=x+Rnd(-2,2)
						Local y2:Int=y+Rnd(-2,2)
						If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
						t[x2,y2] = 60
					Endif
				Next
				
				For Local y2:Int=0 Until mh
				For Local x2:Int=0 Until mw
					If t[x2,y2] = 60 Then 
						tilemap[x2,y2] = 60
											
					End If
				Next
				Next
			
			Next 
			
			Local tr:Int[,] = New Int[mw,mh]
			For Local y:Int=1 Until mh-1
			For Local x:Int=1 Until mw-1
				Local value:Int=0
				If tilemap[x,y] = 60 Then 
					If tilemap[x,y-1] = 0 Then value+=1
					If tilemap[x+1,y] = 0 Then value+=2
					If tilemap[x,y+1] = 0 Then value+=4
					If tilemap[x-1,y] = 0 Then value+=8
					'Print value
					tr[x,y] = value
				End If
			Next
			Next
			For Local y:Int=1 Until mh-1
			For Local x:Int=1 Until mw-1
				If tr[x,y] <>0 Then  tilemap[x,y] = tr[x,y]+300
			Next
			Next			
			
			' add edges
'		tilemap[20,20] = 41'left
'		tilemap[21,20] = 40'center
'		tilemap[22,20] = 42'right
'		tilemap[21,19] = 43'top
'		tilemap[21,21] = 44'bottom
'		tilemap[20,19] = 45 'left top
'		tilemap[22,19] = 46 'Right top
'		tilemap[20,21] = 47 'left bottom
'		tilemap[22,21] = 48 'right bottom
'			
'			For Local y:Int=1 Until mh-1
'			For Local x:Int=1 Until mw-1
'				If tilemap[x,y] = 40
'					If tilemap[x-1,y] = 0 Then tilemap[x-1,y] = 41
'					If tilemap[x+1,y] = 0 Then tilemap[x+1,y] = 42
'					If tilemap[x,y-1] = 0 Then tilemap[x,y-1] = 43
'					If tilemap[x,y+1] = 0 Then tilemap[x,y+1] = 44
'					'
'					' xxx
'					' xxx
'					' xxx
'					'If tilemap[x-1,y] = 41 And tilemap[x,y-1] = 43 Then tilemap[x-1,y-1]=45
'					'If tilemap[x+1,y] = 42 And tilemap[x,y-1] = 43 Then tilemap[x+1,y-1]=46
'					'If tilemap[x-1,y] = 41 And tilemap[x,y+1] = 44 Then tilemap[x-1,y+1]=47
'					'If tilemap[x+1,y] = 42 And tilemap[x,y+1] = 44 Then tilemap[x+1,y+1]=48
'				
'					
'					
'				End If
'			Next
'			Next
		End If




		'add trees
		For Local i:Int=0 Until 200
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			If map[x,y] = 0 And tilemap[x,y] = 0 Then map[x,y]=30
		Next

	End Method
	
	Method createmap(lx:Int,ly:Int)
		brushmap = New String[10]
		brushmap[0] = "00000000200000000000"
		brushmap[1] = "00000tww2wwwt0000000"
		brushmap[2] = "00000w222222w0000000"
		brushmap[3] = "00000w22222222000000"
		brushmap[4] = "00wwwt22f222w0000000"
		brushmap[5] = "00w222222222twwwt000"
		brushmap[6] = "00w2222222222222w000"
		brushmap[7] = "00twwwwwwtwww2wwt000"
		brushmap[8] = "00000000000002000000"
		brushmap[9] = "00000000000002000000"
		For Local y:Int=0 Until brushmap.GetSize(0)
		For Local x:Int=0 Until brushmap[y].Length			
			If brushmap[y][x] = 119 'w-wall
				map[lx+x,ly+y] = 1
			End If
			If brushmap[y][x] = 116't-urret
				map[lx+x,ly+y] = 2				
			End If
			If brushmap[y][x] = 102 'f-flag
				map[lx+x,ly+y] = 3
			End If
			If brushmap[y][x] = 48 Then '0 - terrain (grass)
				map[lx+x,ly+y] = 4
				tilemap[lx+x,ly+y] = 4
			End If
			If brushmap[y][x] = 50 Then '1 - terrain (sand)
				map[lx+x,ly+y] = 5
				tilemap[lx+x,ly+y] = 5
			End If
		Next
		Next
		
		'add shading
		For Local y:Int=1 Until mh-1
		For Local x:Int=1 Until mw-1
			If (map[x,y] = 1 Or map[x,y] = 2) And map[x,y+1] = 4 Then tilemap[x,y+1] = 10
			If (map[x,y] = 1 Or map[x,y] = 2) And map[x+1,y] = 4 Then tilemap[x+1,y] = 11
			If (map[x,y] = 1 Or map[x,y] = 2) And map[x,y+1] = 5 Then tilemap[x,y+1] = 14
			If (map[x,y] = 1 Or map[x,y] = 2) And map[x+1,y] = 5 Then tilemap[x+1,y] = 15
		Next
		Next

	End Method
	Method drawmap(canvas:Canvas,px:Int,py:Int,tx:Int,ty:Int)
		For Local y:Int=0 Until (sh/th)+1
		For Local x:Int=0 Until (sw/tw)+1
			If x+tx<0 Or y+ty<0 Or x+tx>=mw Or y+ty>=mh Then Continue
			Local dx:Int=x*tw+px-16
			Local dy:Int=y*th+py-16
			Select map[x+tx,y+ty]
				Case 1'wall
'				canvas.Color = Color.Brown.Blend(Color.Grey,.5)
'				canvas.DrawRect(dx,dy,tw,th)				
				canvas.Color = Color.White
				canvas.DrawImage(im[2],dx,dy)

				Case 2'turret
				'canvas.Color = Color.Blue.Blend(Color.White,.8)
				'canvas.DrawRect(dx,dy,tw,th)				
				canvas.Color = Color.White
				canvas.DrawImage(im[2],dx,dy)

				Case 3'flag
'				canvas.Color = Color.Grey
'				canvas.DrawRect(dx,dy,tw,th)				
				canvas.Color = Color.White
				canvas.DrawImage(im[3],dx,dy)

				Case 4,0'terrain(1)
				'canvas.Color = Color.Green.Blend(Color.Black,.6)
				'canvas.DrawRect(dx,dy,tw,th)
				canvas.Color = Color.White
				canvas.DrawImage(im[4],dx,dy)
				Case 5'terrain(2)
				'canvas.Color = Color.Brown.Blend(Color.Black,.4)
				canvas.Color = Color.White
				'canvas.DrawRect(dx,dy,tw,th)
				canvas.DrawImage(im[5],dx,dy)
				Case 30'tree
				canvas.Color = Color.White
				'canvas.DrawRect(dx,dy,tw,th)
				canvas.DrawImage(im[30],dx,dy)

			End Select
			Select tilemap[x+tx,y+ty]
				Case 10
				canvas.Color = Color.White
				canvas.DrawImage(im[10],dx,dy)
				Case 11
				canvas.Color = Color.White
				canvas.DrawImage(im[11],dx,dy)
				Case 14
				canvas.Color = Color.White
				canvas.DrawImage(im[14],dx,dy)
				Case 15
				canvas.Color = Color.White
				canvas.DrawImage(im[15],dx,dy)
				Case 22
				canvas.Color = Color.White
				canvas.DrawImage(im[22],dx,dy)
				' grass/sand edges
	'		tilemap[20,20] = 41'left
	'		tilemap[21,20] = 40'center
	'		tilemap[22,20] = 42'right
	'		tilemap[21,19] = 43'top
	'		tilemap[21,21] = 44'bottom
	'		tilemap[20,19] = 45 'left top
	'		tilemap[22,19] = 46 'Right top
	'		tilemap[20,21] = 47 'left bottom
	'		tilemap[22,21] = 48 'right bottom
	'                        49'left right
							'50 'top bottom
				Case 40
				canvas.Color = Color.White
				canvas.DrawImage(im[40],dx,dy)
				Case 201''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[43],dx,dy)
				Case 202''''
				canvas.Color = Color.White
				canvas.DrawImage(im[42],dx,dy)
				Case 203''''
				canvas.Color = Color.White
				canvas.DrawImage(im[46],dx,dy)				
				Case 204''''
				canvas.Color = Color.White
				canvas.DrawImage(im[44],dx,dy)				
				Case 205''''
				canvas.Color = Color.White
				canvas.DrawImage(im[50],dx,dy)
				Case 206''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[48],dx,dy)
				Case 207'toprightbottom
				canvas.Color = Color.White
				canvas.DrawImage(im[50],dx,dy)				
				Case 208''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[41],dx,dy)				
				Case 209''''
				canvas.Color = Color.White	
				canvas.DrawImage(im[45],dx,dy)				
				Case 210''''
				canvas.Color = Color.White
				canvas.DrawImage(im[49],dx,dy)				
				Case 211'lefttopright
				canvas.Color = Color.White
				canvas.DrawImage(im[49],dx,dy)				
				Case 212''''
				canvas.Color = Color.White
				canvas.DrawImage(im[47],dx,dy)				
				Case 213'topleftbottom
				canvas.Color = Color.White
				canvas.DrawImage(im[50],dx,dy)				
				Case 214'test leftbottomright
				canvas.Color = Color.White
				canvas.DrawImage(im[49],dx,dy)				
				Case 215'solo sand
				canvas.Color = Color.White
				canvas.DrawImage(im[4],dx,dy)				

				Case 60
				canvas.Color = Color.White
				canvas.DrawImage(im[60],dx,dy)
				Case 301''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[63],dx,dy)
				Case 302''''
				canvas.Color = Color.White
				canvas.DrawImage(im[62],dx,dy)
				Case 303''''
				canvas.Color = Color.White
				canvas.DrawImage(im[66],dx,dy)				
				Case 304''''
				canvas.Color = Color.White
				canvas.DrawImage(im[64],dx,dy)				
				Case 305''''
				canvas.Color = Color.White
				canvas.DrawImage(im[60],dx,dy)
				Case 306''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[68],dx,dy)
				Case 307'toprightbottom
				canvas.Color = Color.White
				canvas.DrawImage(im[60],dx,dy)				
				Case 308''''''
				canvas.Color = Color.White
				canvas.DrawImage(im[61],dx,dy)				
				Case 309''''
				canvas.Color = Color.White	
				canvas.DrawImage(im[65],dx,dy)				
				Case 310''''
				canvas.Color = Color.White
				canvas.DrawImage(im[69],dx,dy)				
				Case 311'lefttopright
				canvas.Color = Color.White
				canvas.DrawImage(im[69],dx,dy)				
				Case 312''''
				canvas.Color = Color.White
				canvas.DrawImage(im[67],dx,dy)				
				Case 313'topleftbottom
				canvas.Color = Color.White
				canvas.DrawImage(im[60],dx,dy)				
				Case 314'test leftbottomright
				canvas.Color = Color.White
				canvas.DrawImage(im[69],dx,dy)				
				Case 315'solo water
				canvas.Color = Color.White
				canvas.DrawImage(im[4],dx,dy)				
					
			End Select
		Next
		Next
	End Method
End Class

	Global mymap:mainmap
	Global mytank:playertank
	Global mybullet:List<bullet>
	Global myturret:List<turret>
	Global mysoldier:List<soldier>
	Global mydecal:List<decal>
	Global myparticle:List<particle>
	
Class MyWindow Extends Window
	Method New()
		SeedRnd(Microsecs())
		mytank = New playertank(10,10)
		myturret = New List<turret>
		mymap = New mainmap(Width,Height,100,100)				
		mybullet = New List<bullet>
		mysoldier = New List<soldier>
		mydecal = New List<decal>
		myparticle = New List<particle>
		
		Local solcount:Int=8
		While solcount>0
			Local x:Int=Rnd(mymap.mw)
			Local y:Int=Rnd(mymap.mh)
			If mymap.map[x,y]=5 
				mysoldier.Add(New soldier(Microsecs(),x,y))
				solcount-=1
			End If
		Wend
		'mysoldier.Add(New soldier(1,18,13))
		'mysoldier.Add(New soldier(2,5,9))
		'mysoldier.Add(New soldier(3,18,6))
		'For Local i:Int=0 Until 4
		'mysoldier.Add(New soldier(4+i,10,13))
		'Next
		For Local i:Int=0 Until 14
			myparticle.Add(New particle(320,200,Rnd(TwoPi)))
		Next
		'inititate the turrets
		For Local y:Int=0 Until mymap.mh
		For Local x:Int=0 Until mymap.mw
			If mymap.map[x,y] = 2
				Local x2:Int,y2:Int
				x2 = (x-mytank.tx)*tilew-tilew
				y2 = (y-mytank.ty)*tileh-tileh
				myturret.Add(New turret(x2,y2,x,y))
			End If
		Next
		Next
	
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		For Local i:bullet = Eachin mybullet
			If i.deleteme = True Then mybullet.Remove(i)
		Next
		For Local i:turret = Eachin myturret
			If i.deleteme = True Then myturret.Remove(i)
		Next
		
		'mytank.controlmap()
		mytank.controltank()



		mymap.drawmap(canvas,mytank.px,mytank.py,mytank.tx,mytank.ty)
		For Local i:decal=Eachin mydecal
			i.draw(canvas)
		Next

		mytank.draw(canvas)


		For Local i:turret = Eachin myturret
			i.draw(canvas)
		Next
		For Local i:turret = Eachin myturret
			i.update()
		Next

		For Local i:bullet = Eachin mybullet
			i.draw(canvas)
		Next
		For Local i:bullet = Eachin mybullet
			i.update(canvas)
		Next
		
		
		For Local i:soldier = Eachin mysoldier
			i.update()
		Next
		For Local i:soldier = Eachin mysoldier
			If i.deleteme Then mysoldier.Remove(i)
		Next
		For Local i:soldier = Eachin mysoldier
			i.draw(canvas)
		Next

		For Local i:particle = Eachin myparticle
			i.update()
		Next
		For Local i:particle = Eachin myparticle
			If i.deleteme Then myparticle.Remove(i)
		Next
		
		For Local i:particle = Eachin myparticle
			i.draw(canvas)
		Next

		'mymap.drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function
    ' Manhattan Distance (less precise)
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function
    
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
