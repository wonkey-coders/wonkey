#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global developmode:Bool=False
Global theversion:String="Version 5-11-2017"
Global gamestate:String="select"
Global egghatchspeed:Float = 0.1 'how fast eggs hatch
Global egglayingfreq:Float = 0.1 ' lay lots of eggs 1 lay less eggs 0 '0 to 1
Global startingeggfreq:Float = 0.2 '0 to 1 0 is none 1 is full
Global maxflyingmonsters:Int=30
Global mapwidth:Int=320
Global mapheight:Int=240
Global screenwidth:Int=800
Global screenheight:Int=600
Global tilewidth:Int=20
Global tileheight:Int=20

'
' The tentacle for the growing slime monster
'
Class tentacle
	Field basex:Float,basey:Float
	Field targetx:Float,targety:Float
	Field topx:Float,topy:Float
	Field angle:Float
	Field mx:Float,my:Float
	Field speed:Float = 14
	Field deleteme:Bool=False
	Field state:String = "outgoing"
	Field grabbed:Bool=False
	Field grabbedx:Int
	Field grabbedy:Int
	Method New(basex:Float,basey:Float,targetx:Float,targety:Float)
		Self.basex = basex
		Self.basey = basey
		Self.topx = basex
		Self.topy = basey
		Self.targetx = targetx
		Self.targety = targety
		angle = getangle(basex,basey,targetx,targety)
		mx = Cos(angle)
		my = Sin(angle)
	End Method
	Method update()
		If speed > 1 Then speed -= .1
		For Local movement:Int=0 Until speed
			topx += mx
			topy += my
			If state = "outgoing"
				'check collision with flyingmonster
				For Local i:=Eachin myflyingmonster
					Local x:Int=i.px+(i.w/2)
					Local y:Int=i.py+(i.h/2)
					If distance(topx,topy,x,y) < 10
						topx = i.px
						topy = i.py
						angle = getangle(topx,topy,basex,basey)
						mx = Cos(angle)
						my = Sin(angle)
						grabbed = True
						state = "ingoing"
						i.deleteme = True
						Exit						
					End If
				Next
				'check collision with player
				Local x:Int=myplayer.px+(myplayer.pw/2)
				Local y:Int=myplayer.py+(myplayer.ph/2)
				If developmode = False And distance(x,y,topx,topy) < 20
					mx = -mx
					my = -my
					state = "ingoing"
					myplayer.hp -= 10
					If myplayer.hp < 0 Then 
						gamestate = "select"
						Return
					End if
				End If
			End if	
			If state="outgoing" And grabbed=False And distance(topx,topy,targetx,targety) < 10 Then 
					state = "ingoing"
					mx = -mx
					my = -my
					Return
			End If
			If state = "ingoing"
				If distance(topx,topy,basex,basey) < 10 Then
					deleteme = True
					Return
				End If
			End If
		Next
	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function    	
End Class

'
' Items that move towards the player and into his inventory
' by mining,
'
Class item
	Field px:Float,py:Float
	Field w:Int,h:Int
	Field deleteme:Bool
	Field angle:Float
	Field mx:Float,my:Float
	Field speed:Float
	Field kind:String 'coal,metal,gold,rock	
	Field removetime:Int=2000
	Field time:Int
	Method New(x:Int,y:Int,kind:String)
		Self.px = x
		Self.py = y
		Self.kind = kind
	End Method
	Method update()
		' if to long in game then remove
		time+=1
		If time>removetime Then deleteme=True
		' get player center position
		Local pcx:Int=myplayer.px + (myplayer.pw/2)
		Local pcy:Int=myplayer.py + (myplayer.ph/2)
		'if distance closest then add to player inventory		
		If distance(pcx,pcy,px,py) < 10 Then
			' code to add to player inventory here...
			deleteme = True
		End If

		' gravity
		If mymap.mapcollide(px,py+Ceil(my)+2,w,h) = False Then 			
			If my<3 Then my+=.1
			Else
				my=0
		End if

		' if in range then move to player
		If distance(pcx,pcy,px,py) < 150 Then 			
			angle = getangle(px,py,pcx,pcy)
			mx = Cos(angle)
			my = Sin(angle)			
			Else
			mx=0			
		End if

		' floor collision
		If mymap.mapcollide(px,py+1,w,h) = True Then 						
				my=-1
		End If

		' ceiling collision
		If mymap.mapcollide(px,py-1,w,h) = True Then 						
				my=1
		End If
		' left side collision
		If mymap.mapcollide(px-1,py,w,h) = True Then 						
				mx=1
		End if
		' right side collision
		If mymap.mapcollide(px+1,py,w,h) = True Then 						
				mx=-1
		End If
		' move the item
		px += mx
		py += my		
	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function    	
End Class

'fragmentation things
Class frag
	Field px:Float,py:Float 'pixel x and y
	Field owner:String
	Field angle:Float
	Field w:Int,h:Int
	Field deleteme:Bool
	Field countdown:Int
	Field mx:Float
	Field my:Float
	Field fragspeed:Int
	Method New(x:Int,y:Int,owner:String)
		Self.owner = owner
		Self.px = x
		Self.py = y
		Self.w = 3
		Self.h = 3
		fragspeed = Rnd(4,7)
		countdown = 100+Rnd(300)
		Self.angle = Rnd(TwoPi)
		mx = Cos(angle)
		my = Sin(angle)
	End Method
	Method update()		
		For Local ps:Int=0 Until fragspeed
		countdown-=1
		If countdown < 0 Then deleteme = True ; Return
		'bouncy vertical
		If mymap.mapcollide(px,py+2,1,h) Then 			
			my = -my+Rnd(-.1,.1)
			Local cnt:Int=0
			While mymap.mapcollide(px,py+2,1,h)
				py+=my
				cnt+=1
				If cnt>100 Then Exit
			Wend
			mx*=.8
			my*=.8
			If my<0 And my>-0.2 Then my=-0.2
			If my>0 And my<.2 Then my=.2
			If mx<0 And mx>-0.2 Then mx=-0.2
			If mx>0 And mx<.2 Then mx=.2
			
		End If
		'bounce horizontally
		If mymap.mapcollide(px-w,py,w*2,1) Then 			
			mx = -mx+Rnd(-.1,.1)
			Local cnt:Int=0
			While mymap.mapcollide(px-w,py,w*2,1)
				px+=mx	
				cnt+=1
				If cnt>100 Then Exit			
			Wend
			mx*=.8
			my*=.8
			If my<0 And my>-0.2 Then my=-0.2
			If my>0 And my<.2 Then my=.2
			If mx<0 And mx>-0.2 Then mx=-0.2
			If mx>0 And mx<.2 Then mx=.2
			
		End If

		px += mx
		py += my
		my+=.005
		
		' frag collision with flying monsters
		For Local i:=Eachin myflyingmonster
			If distance(i.x*tilewidth+tilewidth/2,i.y*tileheight+tileheight/2,px,py) < 10
				i.hp -= 5
				If i.hp<=0
					i.deleteme = True
					myitem.Add(New item(i.px,i.py,"gold"))
				End If
				deleteme = True
				Return
			End If
		Next
		
		' frag collision with the eggs
		If eggcollide(px-1,py-1,w+2,h+2)
			deleteme = True
			'myitem.Add(New item(px,py,"gold"))
			Return
		End if
		Next
	End Method	
	Method eggcollide:Bool(x:Int,y:Int,w:Int,h:Int)
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
		
		Local x2:Int=-1,y2:Int=-1
		If mymap.mapfinal[lefttopx,lefttopy] = mymap.tileegg Then x2=lefttopx;y2=lefttopy
		If mymap.mapfinal[righttopx,righttopy] = mymap.tileegg Then x2=righttopx;y2=righttopy
		If mymap.mapfinal[leftbottomx,leftbottomy] = mymap.tileegg Then x2=leftbottomx;y2=leftbottomy
		If mymap.mapfinal[rightbottomx,rightbottomy] = mymap.tileegg Then x2=rightbottomx;y2=rightbottomy
		If x2<>-1			
			If Rnd(7)<1 Then 
				mymap.mapfinal[x2,y2] = mymap.tileempty
				myitem.Add(New item(x2*tilewidth,y2*tileheight,"gold"))
				mymap.updateimage(mymap.mapcanvas)
			End If
			Return True
		End If
		Return False
	End Method	

    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function			

End Class

Class grenade
	Field px:Float,py:Float 'pixel x and y
	Field slimed:Bool=False
	Field angle:Float
	Field w:Int,h:Int
	Field deleteme:Bool
	Field countdown:Int
	Field mx:Float
	Field my:Float
	Method New(x:Int,y:Int,facing:String)
		Self.px = x
		Self.py = y
		Self.w = 6
		Self.h = 6
		countdown = 500
		Select facing
			Case "left"
				angle=Pi+.3
			Case "right"
				angle=0-.3
			Case "up"
				'Print Pi*1.5
				angle=Pi*1.55+Rnd(-.2,.2)
				
			Case "down"
				angle = Pi/2+Rnd(-.2,.2)
		End Select
		
		Self.angle = angle
		mx = Cos(angle)
		my = Sin(angle)

	End Method
	Method update()		
		For Local bulletspeed:Int=0 Until 4
		
		' Life of frags	
		countdown-=1
		If countdown < 0 Then 
			deleteme = True
			Local numfrags:Int=Rnd(6,20)
			For Local i:Int=0 Until numfrags
				myfrag.AddLast(New frag(px,py,"player"))
			next
			Return
		End If
						
		If slimed=False Then 
			If slimecollide(px-w,py-h,w*2.5,h*2.5) Then slimed = True ; Continue
			'bounc ceiling
			If mapcollide(px,py-2,1,h) Then 			
				'slimed=slimecollide(px,py+2,1,h)
				'If slimed = True Then Return
				my = -my+Rnd(-.1,.1)
				Local cnt:Int=0
				While mapcollide(px,py-2,1,h)
					py+=my
					cnt+=1
					If cnt>100 Then Exit
				Wend
			
				mx*=.8
				my*=.8
			
				If my<0 And my>-0.2 Then my=-0.2
				If my>0 And my<.2 Then my=.2
				If mx<0 And mx>-0.2 Then mx=-0.2
				If mx>0 And mx<.2 Then mx=.2
			
			End If
			'bouncy vertical
			If mapcollide(px,py+2,1,h) Then 			
				'slimed=slimecollide(px,py+2,1,h)
				'If slimed = True Then Return
				my = -my+Rnd(-.1,.1)
				Local cnt:Int=0
				While mapcollide(px,py+2,1,h)
					py+=my
					cnt+=1
					If cnt>100 Then Exit
				Wend
				
				mx*=.8
				my*=.8
				
				If my<0 And my>-0.2 Then my=-0.2
				If my>0 And my<.2 Then my=.2
				If mx<0 And mx>-0.2 Then mx=-0.2
				If mx>0 And mx<.2 Then mx=.2
				
			End If
			'bounce horizontally
			If mapcollide(px-w,py,w*2,1) Then 			
				'slimed=mapcollide(px-w,py,w*2,1)
				'If slimed Then Return
				mx = -mx+Rnd(-.1,.1)
				Local cnt:Int=0
				While mapcollide(px-w,py,w*2,1)
					px+=mx	
					cnt+=1
					If cnt>100 Then Exit			
				Wend
				mx*=.8
				my*=.8			
				If my<0 And my>-0.2 Then my=-0.2
				If my>0 And my<.2 Then my=.2
				If mx<0 And mx>-0.2 Then mx=-0.2
				If mx>0 And mx<.2 Then mx=.2
				
			End If
	
			' update the frag location
			px += mx
			py += my
			my+=.005
		End if		
		
		Next
	End Method
	Method mapcollide:Bool(x:Int,y:Int,w:Int,h:Int)
		Local mmw:Int=mymap.mmw
		Local mmh:Int=mymap.mmh
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
		If lefttopx < 0 Or lefttopx >= mmw Then Return True
		If lefttopy < 0 Or lefttopy >= mmh Then Return True
		If righttopx < 0 Or righttopx >= mmw Then Return True
		If righttopy < 0 Or righttopy >= mmh Then Return True
		If leftbottomx < 0 Or leftbottomx >= mmw Then Return True
		If leftbottomy < 0 Or leftbottomy >= mmh Then Return True
		If rightbottomx < 0 Or rightbottomx >= mmw Then Return True
		If rightbottomy < 0 Or rightbottomy >= mmh Then Return True
		
		If mymap.mapfinal[lefttopx,lefttopy] <> mymap.tileempty Then Return True
		If mymap.mapfinal[righttopx,righttopy] <> mymap.tileempty Then Return True
		If mymap.mapfinal[leftbottomx,leftbottomy] <> mymap.tileempty Then Return True
		If mymap.mapfinal[rightbottomx,rightbottomy] <> mymap.tileempty Then Return True						
		If mygrowslime.map[lefttopx*2,lefttopy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[righttopx*2,righttopy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[leftbottomx*2,leftbottomy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[rightbottomx*2,rightbottomy*2] = mymap.tileslime Then Return True						

		Return False
	End Method	
	Method slimecollide:Bool(x:Int,y:Int,w:Int,h:Int)
		Local mmw:Int=mymap.mmw
		Local mmh:Int=mymap.mmh
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
'		If lefttopx < 0 Or lefttopx >= mmw Then Return True
'		If lefttopy < 0 Or lefttopy >= mmh Then Return True
'		If righttopx < 0 Or righttopx >= mmw Then Return True
'		If righttopy < 0 Or righttopy >= mmh Then Return True
'		If leftbottomx < 0 Or leftbottomx >= mmw Then Return True
'		If leftbottomy < 0 Or leftbottomy >= mmh Then Return True
'		If rightbottomx < 0 Or rightbottomx >= mmw Then Return True
'		If rightbottomy < 0 Or rightbottomy >= mmh Then Return True
'	
		If mygrowslime.map[lefttopx*2,lefttopy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[righttopx*2,righttopy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[leftbottomx*2,leftbottomy*2] = mymap.tileslime Then Return True
		If mygrowslime.map[rightbottomx*2,rightbottomy*2] = mymap.tileslime Then Return True						
	
		Return False
	End Method	
	
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function			
End Class

Class bullet
	Field px:Float,py:Float
	Field mx:Float,my:Float
	Field angle:Float
	Field w:Int,h:Int
	Field deleteme:Bool
	Field countdown:Int
	Field owner:String	
	Method New(x:Int,y:Int,angle:Float,owner:String,kind:String)
		Self.owner = owner
		Self.px = x
		Self.py = y		
		Self.w = 2
		Self.h = 2
		mx = 1
		my = 1
		If kind="shotgun"
			w = 2
			h = 2
			mx = Rnd(.9,1)
			my = Rnd(.9,1)
		End If
		countdown = 500
		Self.angle = angle		
	End Method
	Method update()
		For Local bulletspeed:Int=0 Until 5
		countdown-=1
		If countdown < 0 Then deleteme = True ; Return
		If mymap.mapcollide(px,py,w,h) Then deleteme = True
		' Collision with bullet and flying monster
		For Local i:=Eachin myflyingmonster
			If distance(px,py,i.x*tilewidth,i.y*tileheight) < tilewidth Then 
				i.hp -= 1
				deleteme = True				
				If i.hp <= 0
					i.deleteme = True					
					myitem.Add(New item(px,py,"gold"))
					Return
				End if
				Return
			End If
		Next
		' Collision with bullet and egg
		If eggcollide(px,py,w,h) Then 						
			deleteme = True
			myitem.Add(New item(px,py,"gold"))
			Return
		End If
		px += Cos(angle)*mx
		py += Sin(angle)*my
		Next
	End Method
	Method eggcollide:Bool(x:Int,y:Int,w:Int,h:Int)
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
		
		Local x2:Int=-1,y2:Int=-1
		If mymap.mapfinal[lefttopx,lefttopy] = mymap.tileegg Then x2=lefttopx;y2=lefttopy
		If mymap.mapfinal[righttopx,righttopy] = mymap.tileegg Then x2=righttopx;y2=righttopy
		If mymap.mapfinal[leftbottomx,leftbottomy] = mymap.tileegg Then x2=leftbottomx;y2=leftbottomy
		If mymap.mapfinal[rightbottomx,rightbottomy] = mymap.tileegg Then x2=rightbottomx;y2=rightbottomy
		If x2<>-1			
			If Rnd(7)<1 Then 
				mymap.mapfinal[x2,y2] = mymap.tileempty
				mymap.updateimage(mymap.mapcanvas)
			End If
			Return True
		End If
		Return False
	End Method	
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function			
End Class

'uses myflyingmonster
Class turret
	Field deleteme:Bool
	Field mapx:Int,mapy:Int 
	Field tw:Int,th:Int 'tilewidht and height
	Field owner:String="town"
	Method New()
		findstartposition()
		tw = tilewidth
		th = tileheight
	End Method
	Method update()
		If Rnd(20)<10 Then Return
		For Local i:=Eachin myflyingmonster			
			If distance(mapx,mapy,i.x,i.y) > 15 Then Continue
			'if distance is close by
			If clearshot(mapx*tw,mapy*th,getangle(mapx*tw,mapy*th,i.x*tw,i.y*th)+Rnd(-.2,.2))
				mybullet.AddLast(New bullet(mapx*tw,mapy*th,getangle(mapx*tw,mapy*th,i.x*tw,i.y*th)+Rnd(-.2,.2),"town","turret"))
			Endif
		Next
	End Method
	' Check if we are not recklessly shooting into a solid tile
	Method clearshot:Bool(x:Float,y:Float,angle:Float)
		For Local i:Int=0 Until 100
			x+=Cos(angle)
			y+=Sin(angle)
			If mymap.mapcollide(x,y,3,3) Then Return False
		Next
		Return True
	End Method
	Method findstartposition()
		' position on the left side
		For Local y:Int=2 Until mymap.mmh-2
		For Local x:Int=2 Until mymap.mmw-2
			If mymap.mapfinal[x,y] = mymap.tileempty
			If mymap.mapfinal[x+1,y] = mymap.tileempty
			If mymap.mapfinal[x+1,y+1] = mymap.tileempty
			If mymap.mapfinal[x,y+1] = mymap.tilesolid				
				If mymap.mapfinal[x-1,y] = mymap.tileempty					
					mymap.mapfinal[x-1,y] = mymap.tileturret
					mapx = x - 1
					mapy = y
					Return
				Elseif mymap.mapfinal[x+5,y] = mymap.tileempty
					mymap.mapfinal[x+5,y] = mymap.tileturret
					mapx = x + 5
					mapy = y
					Return
				Else ' no place for turret
					deleteme = True					
					Return
				End if
			End If
			End If
			End If
			End If
		Next
		Next
	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function     
End Class

Class growslime
	Field map:Int[,]
	Field w:Float,h:Float
	Field tw:Float,th:Float
	Field openx:Stack<Int>
	Field openy:Stack<Int>
	Field slimetile:Int=10
	Field slimestartx:Int,slimestarty:Int
	Method New()
		w = mymap.mmw * 2
		h = mymap.mmh * 2
		tw = mymap.tw * 2
		th = mymap.th * 2+2
		map = New Int[w,h]
		'copy the map from the game into this map
		For Local y:Int=0 Until mymap.mmh
		For Local x:Int=0 Until mymap.mmw
		For Local y2:Int=0 Until 2
		For Local x2:Int=0 Until 2
			map[(x*2)+x2,(y*2)+y2] = mymap.mapfinal[x,y]			
		Next
		Next
		Next
		Next
		'create the active slime list
		openx = New Stack<Int>
		openy = New Stack<Int>
		findslimestartpos()
		openx.Push(slimestartx)
		openy.Push(slimestarty)
		map[slimestartx,slimestarty]=slimetile
	End Method
	Method findslimestartpos()
		For Local y:Int=h-1 To 0 Step -1
		For Local x:Int=0 Until w
			If map[x,y] = 1 Then 
				slimestartx = x
				slimestarty = y
				Return
			End If
		Next
		Next
	End Method
	Method update(speed:String)
		Local freq:Int
		If speed = "slow" Then freq = 120 Else freq = 20
		
		' Tentacle check
		' Every now and then check if active slime part is in range
		' of player/enemy and then check if path is clear and if so
		' then initiate tentacle.
		' Grab player
		For Local i:Int=0 Until openx.Length
			Local x1:Int = openx.Get(i) * (myplayer.tw/2)
			Local y1:Int = openy.Get(i) * (myplayer.th/2)
			Local pcx:Int=myplayer.px+(myplayer.pw/2)
			Local pcy:Int=myplayer.py+(myplayer.ph/2)
			' grab monster
			If Rnd(300) < 2
				For Local i2:=Eachin myflyingmonster
					Local mcx:Int=i2.px+(i2.w/2)
					Local mcy:Int=i2.py+(i2.h/2)
					If distance(mcx,mcy,x1,y1) < 200
						Local an:Float = getangle(x1,y1,mcx,mcy)
						Local mx:Float = Cos(an)
						Local my:Float = Sin(an)
						Local x2:Float = x1
						Local y2:Float = y1
						For Local i3:Int=0 Until 200
							x2 += mx
							y2 += my
							If mymap.mapcollide(x2,y2,i2.w,i2.h) = True Then 
								Exit
							End If
							If distance(x2,y2,mcx,mcy) < 50 Then 
								mytentacle.Add(New tentacle(x1,y1,mcx,mcy))					
								Exit
							End If
						Next
						Exit
					End If
				Next
			End if
			'grab player
			If Rnd(300)<2 And distance(pcx,pcy,x1,y1) < 200 
				Local an:Float = getangle(x1,y1,pcx,pcy)
				Local mx:Float = Cos(an)
				Local my:Float = Sin(an)
				Local x2:Float = x1
				Local y2:Float = y1
				For Local i2:Int=0 Until 200
					x2 += mx
					y2 += my
					If mymap.mapcollide(x2,y2,myplayer.pw,myplayer.ph) = True Then 
						Exit
					End If
					If distance(x2,y2,pcx,pcy) < 50 Then 
						mytentacle.Add(New tentacle(x1,y1,pcx,pcy))					
						Exit
					End If
				Next
				Exit
			End if			
		Next


		
		' Expand Slime		
		For Local i:Int=0 Until openx.Length
			If Rnd(freq) > 2 Then Continue
			Local x2:Int=openx.Get(i)
			Local y2:Int=openy.Get(i)
			'bottom bleft or bright first
			Local r:Int=Rnd(0,6)
			If r=0 And y2+1<h And map[x2,y2+1] = 1 Then addslime(x2,y2+1) ; Continue
			If r=1 And x2-1 >=0 And y2+1 <h And map[x2-1,y2+1] = 1 Then addslime(x2-1,y2+1) ; Continue
			If r=2 And y2+1<h And map[x2+1,y2+1] = 1 Then addslime(x2+1,y2+1) ; Continue
			' left Or right Then
			r = Rnd(0,2)
			If r=0 And x2-1>=0 And map[x2-1,y2] = 1 Then addslime(x2-1,y2) ; Continue
			If r=1 And x2+1<w And map[x2+1,y2] = 1 Then addslime(x2+1,y2) ; Continue
			' up lup and rup
			r = Rnd(0,23)
			If r=0 And y2-1>=0 And map[x2,y2-1] = 1 Then addslime(x2,y2-1);Continue
			If r=1 And x2-1>=0 And y2-1>=0 And map[x2-1,y2-1] = 1 Then addslime(x2-1,y2-1);Continue
			If r=2 And x2+1<w And y2-1>=0 And map[x2+1,y2-1] = 1 Then addslime(x2+1,y2-1);Continue
		Next
		
		Local tx:Stack<Int> = New Stack<Int>
		Local ty:Stack<Int> = New Stack<Int>
		' Remove Obsolete slime
		For Local i:Int=0 Until openx.Length
			Local cnt:Int=0
			For Local y:Int=-1 To 1
			For Local x:Int=-1 To 1
				Local x2:Int=openx.Get(i)+x
				Local y2:Int=openy.Get(i)+y
				If x2<0 Or y2<0 Or x2>=w Or y2>=h Then 
					cnt+=1
					Continue
				End If				
				If map[x2,y2] = 10 Then cnt+=1
				if map[x2,y2] = 0 Then cnt+=1
				'if map[x2,y2] = 1 Then cnt+=1
				'If map[x2,y2] <> 1 Then cnt+=1
			Next
			Next		
			If cnt=9 Then
				'openx.Remove(i)
				'openy.Remove(i)
				Else
				tx.Push(openx.Get(i))
				ty.Push(openy.Get(i))
			End If
		Next
		openx = New Stack<Int>
		openy = New Stack<Int>
		For Local i:Int=0 Until tx.Length
			openx.Push(tx.Get(i))
			openy.Push(ty.Get(i))
		Next
	End Method

	Method addslime(sx:Int,sy:Int)
		openx.Push(sx)
		openy.Push(sy)
		map[sx,sy] = slimetile
	End Method

	Method drawmap(canvas:Canvas)
		' Draw the solid slimes ()
        For Local y:Int=0 Until h
        For Local x:Int=0 Until w
            Local x1:Float=x*mymap.tw/2
            Local y1:Float=y*mymap.th/2
            If map[x,y] = slimetile
                canvas.Color = Color.Green
                canvas.DrawRect(x1,y1,mymap.tw/2,mymap.th/2)
            End If            
        Next
        Next

	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function    	
End Class


Class menuselect
	Field image:Image	
	Field icanvas:Canvas
	Field m:map
	Field index:Int=0
	Method New()
		image=New Image(800,600)
		image.Handle=New Vec2f( 0,0 )
		icanvas=New Canvas( image )
		icanvas.Clear(Color.Black)
		Local x:Int=50
		Local y:Int=100
		Local w:Int=150
		Local h:Int=150
		Local sw:Int=150
		Local sh:Int=150
		SeedRnd(1)
		m = New map(sw,sh,w,h)
		drawmap(icanvas,x,y,w,h)
		x = 200
		y = 100
		w = 250
		h = 250
		sw = 250
		sh = 250
		m = New map(sw,sh,w,h)
		drawmap(icanvas,x,y,w,h)
		x = 450
		y = 100
		w = 300
		h = 300
		sw = 300
		sh = 300
		m = New map(sw,sh,w,h)
		drawmap(icanvas,x,y,w,h)		
		icanvas.Flush()		
	End Method
	Method update()
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.Left) Then index-=1
		If Keyboard.KeyReleased(Key.Right) Then index+=1
		If index<0 Then index = 0
		If index>2 Then index = 2
		If Keyboard.KeyReleased(Key.Enter) Then
			Select index
				Case 0
					mapwidth = 150
					mapheight = 150
				Case 1
					mapwidth = 250
					mapheight = 250
				Case 2
					mapwidth = 300
					mapheight = 300
			End Select
			resetmap(screenwidth,screenheight)
			gamestate="play"			
		End If
	End Method
	Method draw(canvas:Canvas)
		canvas.DrawImage(image,0,0)
		canvas.DrawText("Use Cursor left and Right to select Enter to Play",0,0)
		canvas.PushMatrix()
		canvas.Scale(2,2)
		canvas.DrawText("Select Difficulty",400/2,50/2,.5,.5)
		canvas.PopMatrix()
		canvas.Color = Color.Yellow
		Local x:int=50
		Local y:Int=100
		Local w:Int=150
		Local h:int=150
		If index = 0 Then 
			mydrawrect(canvas,x,y,w,h)
			mydrawrect(canvas,x+1,y+1,w-2,h-2)
		End If
		x = 200
		y = 100
		w = 250
		h = 250
		If index = 1 Then 
			mydrawrect(canvas,x,y,w,h)
			mydrawrect(canvas,x+1,y+1,w-2,h-2)
		End If
		x = 450
		y = 100
		w = 300
		h = 300
		If index = 2 Then 
			mydrawrect(canvas,x,y,w,h)
			mydrawrect(canvas,x+1,y+1,w-2,h-2)
		End If
	End Method
	Method drawmap(canvas:Canvas,x:Int,y:Int,w:Int,h:Int)
		For Local y1:Int=0 Until h
		For Local x1:Int=0 Until w
			Select m.mapfinal[x1,y1]
				Case 1
					canvas.Color = New Color(1,1,1)
					canvas.DrawRect(x1+x,y1+y,1,1)
			End Select 
		Next
		Next
	End Method
	Method mydrawrect(canvas:Canvas,x:Int,y:Int,w:Int,h:Int)
		canvas.DrawLine(x,y,x+w,y)
		canvas.DrawLine(x+w,y,x+w,y+h)
		canvas.DrawLine(x,y,x,y+h)
		canvas.DrawLine(x,y+h,x+w,y+h)
	End Method
End Class

Class player
	Field hp:Int=100
	Field mineitem:String[] = New String[]("gold","coal","metal","rock")
	Field regularmode:Bool=True
	Field jump:Bool=False
	Field incy:Float=0
	Field movespeed:Float
	Field px:Float,py:Float
	Field pmx:Float,pmy:Float
	Field ptx:Float,pty:Float
	Field mox:Int,moy:Float
	Field pw:Int,ph:Int	
	Field mcx:Int,mcy:Int,mpx:Int,mpy:Int ' scroll coordinates
	Field maptileswidth:Int,maptilesheight:Int
	Field tw:Float=tilewidth
	Field th:float=tileheight
	Field facing:String="right"
	Field gtkd:Bool=False 'grenade thrown key down
	Field sfkd:Bool=False 'shogun fire key down
	Field minedelay:Int
	Method New()
		movespeed = 1
		px = tilewidth*20
		py = tileheight*14
		pw = tilewidth
		ph = tileheight
		maptileswidth = screenwidth / tw
		maptilesheight = screenheight / th
		mcx=0
		mcy=0
	End Method 
	Method updateplayercontrols()		
		'
		pmx = px-(mcx*tw)
		pmy = py-(mcy*th)
		ptx = px/tw
		pty = py/th
		If playerladdercollision(px,py)
			jump=False
			laddermode()
			movespeed = 1			
			Else
			For Local i:=0 Until 2
				playergravity()
			Next
		End If

		movespeed +=.1
		If movespeed > 4 Then movespeed = 4
		
		' If no movement left and right up and down then slow down
		' movement
		If Keyboard.KeyDown(Key.Right) = False
		If Keyboard.KeyDown(Key.Left) = False			
		If Keyboard.KeyDown(Key.Up) = False
		If Keyboard.KeyDown(Key.Down) = False			
			movespeed = 1
		End If
		End If
		End If
		End If
						
		For Local i:Int=0 Until Ceil(movespeed)
			If Keyboard.KeyDown(Key.Right)
			If playertilecollision(px+1,py) = False
				px+=1
				scrollmap(1,0)
			End If
			End If
			If Keyboard.KeyDown(Key.Left)
			If playertilecollision(px-1,py) = False
				px-=1
				scrollmap(-1,0)
			End If
		  	End If			
		Next
		If Keyboard.KeyDown(Key.Left) Then facing="left"
		If Keyboard.KeyDown(Key.Right) Then facing="right"
		If Keyboard.KeyDown(Key.Up) Then facing="up"
		If Keyboard.KeyDown(Key.Down) Then facing="down"

		' throw grenade
		If Keyboard.KeyDown(Key.G) = False Then gtkd = False
		If gtkd = False And Keyboard.KeyDown(Key.G)
			gtkd = True			
			Local pcx:Int=px+(pw/2)
			Local pcy:Int=py+(ph/2)						
			mygrenade.AddLast(New grenade(pcx,pcy,myplayer.facing))
		End if
		
		' Fire shotgun
		If Keyboard.KeyDown(Key.S) = False Then sfkd = False
		If sfkd = False And Keyboard.KeyDown(Key.S)
			sfkd = True	
			fireshotgun()					
		End if

		' Mine left or right
		If minedelay > 0 Then minedelay -= 1
		If Keyboard.KeyDown(Key.M) And minedelay <=0
		minedelay = 30
		mine()
		End If

	End Method
	Method mine()
		If facing = "left"
		For Local x:Int=px Until px-tilewidth Step -1
			Local x2:Int = x / tilewidth
			Local y2:Int = py / tileheight
			If mymap.mapfinal[x2,y2] = mymap.tilemineable
				mymap.mapfinal[x2,y2] = mymap.tileempty
				createmineitem(x2,y2)
				Return
			End If
		Next
		End If
		If facing = "right"
		For Local x:Int=px Until px+tilewidth*2
			Local x2:Int = x / tilewidth
			Local y2:Int = py / tileheight
			If mymap.mapfinal[x2,y2] = mymap.tilemineable
				mymap.mapfinal[x2,y2] = mymap.tileempty
				createmineitem(x2,y2)
				Return
			End If
		Next
		End If	
		If facing = "up"
		For Local y:Int=py Until py-tileheight*2 Step -1
			Local x2:Int = px / tilewidth
			Local y2:Int = y / tileheight
			If mymap.mapfinal[x2,y2] = mymap.tilemineable
				mymap.mapfinal[x2,y2] = mymap.tileempty
				createmineitem(x2,y2)
				Return
			End If
		Next
		End If	
		If facing = "down"
		For Local y:Int=py Until py+tileheight
			Local x2:Int = px / tilewidth
			Local y2:Int = y / tileheight
			If mymap.mapfinal[x2,y2] = mymap.tilemineable
				mymap.mapfinal[x2,y2] = mymap.tileempty
				createmineitem(x2,y2)
				Return
			End If
		Next
		End If	

	End Method
	Method createmineitem(x2:Int,y2:Int)		
		x2 *= tw
		y2 *= th
		x2 += tw/2
		y2 += th/2
		For Local i:Int=0 Until Rnd(3)				
		myitem.Add(New item(x2+Rnd(-tw/3,th/3),y2+Rnd(th/3,th/3),mineitem[Rnd(mineitem.Length)]))
		Next
	End Method
	Method fireshotgun()
		Local angle:Float
		Select facing
			Case "left"
				angle=Pi
			Case "right"
				angle=0
			Case "up"
				'Print Pi*1.5
				angle=Pi*1.55+Rnd(-.2,.2)
				
			Case "down"
				angle = Pi/2+Rnd(-.2,.2)
		End Select
		For Local i:Int=0 Until 7
			mybullet.AddLast(New bullet(px,py,angle+Rnd(-.1,.1),"player","shotgun"))
		Next
	End method
	Method scrollmap(x:Int,y:Int)
		If x=-1 Then mox+=1
		If x=1 Then mox-=1
		If y=-1 Then moy+=1
		If y=1 Then moy-=1
		If mox>tw-1 Then mcx-=1;mox=0
		If mox<-(tw-1) Then mcx+=1;mox=0
		If moy>th-1 Then mcy-=1;moy=0
		If moy<-(th-1) Then mcy+=1;moy=0
		
	End Method
    Method laddermode()
    	For Local i:=0 Until Ceil(movespeed)
			If Keyboard.KeyDown(Key.Right)
			If playertilecollision(px+1,py) = False
			If playerladdercollision(px+1,py) = True
				px+=1
				scrollmap(1,0)
			End If
			End If
			End If
			If Keyboard.KeyDown(Key.Left)			
			If playertilecollision(px-1,py) = False
			If playerladdercollision(px-1,py) = True
				px-=1
				scrollmap(-1,0)
			End If
			End If
		  	End If			
			If Keyboard.KeyDown(Key.Up)			
			If playertilecollision(px,py-1) = False
			If playerladdercollision(px,py-1) = True
				py-=1
				scrollmap(0,-1)
			End If
			End If
		  	End If			
			If Keyboard.KeyDown(Key.Down)			
			If playertilecollision(px,py+1) = False
			If playerladdercollision(px,py+1) = true			
				py+=1
				scrollmap(0,1)
			End If
			End If
		  	End If					  			  	
		Next
    End Method
    Method playergravity()
        If jump = False And playertilecollision(px,py+1) = False 
            jump = True
            incy = 0
        End If
        If jump = False And Keyboard.KeyDown(Key.Space) = True            
            incy = -5
            jump = True
        End
        'If the player is in the jump
        If jump = True
            incy += 0.1
            'if the player is going up
            If incy <=0
                For Local i:= 0 Until Abs(incy)                
                    py -= 1
                    scrollmap(0,-1)
                    If playertilecollision(px,py-1) = True
                        incy = 0
                        Exit
                    End If
                End
            End
            ' if the player if going down
            If incy > 0
                For Local i:= 0 Until incy
                    py += 1
                    scrollmap(0,1)
                    'if the player touches the ground
                    If playertilecollision(px,py+1) = True
                        jump = False                        
                        Exit
                    End
                End
                If incy>4 Then incy=4
            End
        End
    End Method	
	Method playertilecollision:Bool(x:Int,y:Int)
		Local cx:Int=x/tw
		Local cy:Int=y/th
        For Local y2:=cy-1 Until cy+2
        For Local x2:=cx-1 Until cx+2
            If x2>=0 And x2<mapwidth And y2>=0 And y2<mapheight	            		        
                If mymap.mapfinal[x2,y2] <> mymap.tileempty 'Or mymap.mapfinal[x2,y2] = mymap.tilemineable           
	                	                     
                    If rectsoverlap(x,y,pw,ph,x2*tw,
                                    y2*th,tw,th) = True                                    	                    
                        Return True
                    End If
                End If
            End If
        Next
        Next
    
    Return False
	End Method
	Method playerladdercollision:Bool(x:Int,y:Int)
		Local cx:Int=x/tw
		Local cy:Int=y/th
        For Local y2:=cy-1 Until cy+2
        For Local x2:=cx-1 Until cx+2
            If x2>=0 And x2<mapwidth And y2>=0 And y2<mapheight	            		        
                If mymap.mapladder[x2,y2] = 1	                	                     
                    If rectsoverlap(x,y,pw,ph,x2*tw,
                                    y2*th,tw,th) = True                                    	                    
                        Return True
                    End If
                End If
            End If
        Next
        Next
    
    Return False
	End Method

	Method userscrollmap()
		If Keyboard.KeyDown(Key.Right)
			mcx+=1
			If mcx+maptileswidth>mapwidth-1 Then 
			mcx-=1
			End If 
		End If 
		If Keyboard.KeyDown(Key.Left)
			mcx-=1
			If mcx<1 Then 
			mcx+=1
			End If 
		End If
		If Keyboard.KeyDown(Key.Down)
			mcy+=1
			If mcy+maptilesheight>mapheight-1 Then 
			mcy-=1
			End If
		End If
		If Keyboard.KeyDown(Key.Up)
			mcy-=1
			If mcy<1 Then 
			mcy+=1
			End If
		End If

	End Method
	Method draw(canvas:Canvas)
		canvas.Scissor = New Recti(32,32,screenwidth-32,screenheight-64)
		'draw the map
		For local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=(x*tw)+mox
			Local y3:Int=(y*th)+moy
			If x2>0 And x2<mapwidth And y2>0 And y2<mapheight
			Select mymap.mapfinal[x2,y2]
				Case 0
				canvas.Color = Color.Brown
				canvas.DrawRect(x3,y3,tw,th)
				Case mymap.tilesolid
				canvas.Color = Color.Black
				canvas.DrawRect(x3,y3,tw,th)
				Case mymap.tileegg
				canvas.Color = Color.Yellow
				canvas.DrawRect(x3,y3,tw,th)
				Case mymap.tileturret					
				canvas.Color = Color.Grey
				canvas.DrawRect(x3,y3,tw,th)	
				Case mymap.tilemineable
				canvas.Color = Color.Brown.Blend(Color.Yellow,.2)
				canvas.DrawRect(x3,y3,tw,th)
			End Select	
			'draw the slime			
			For Local y4:Float=0 Until 2 Step 1
			For Local x4:Float=0 Until 2 Step 1
				If mygrowslime.map[(x2*2)+x4,(y2*2)+y4] = 10
					canvas.Color = Color.Green
					canvas.DrawRect(x3+(x4*(mygrowslime.tw)),y3+(y4*(mygrowslime.th)),mygrowslime.tw,mygrowslime.th)
				End If
			Next
			Next
			End If
		Next
		Next
		'draw water
#rem
		canvas.Color = Color.Blue
		For Local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=(x*tw)+mox
			Local y3:Int=(y*th)+moy
			Select mywatermap.map[x2,y2]
				Case 0				
				'if water around
				Local cnt:Int=0
				For Local y4:Int=-1 To 1
				For Local x4:Int=-1 To 1
					If m(x2,y2,x4,y4) = 2
						cnt+=1
					End If
				Next
				Next
				If cnt>5
					canvas.Color = New Color(0,0.2,0.9)
					canvas.DrawRect(x3,y3,tw,th)
				End If
				
				Case 2
					Local cont:Bool=True
					' water no left no right solid bottom
					If m(x2,y2,0,-1) = 0
					If m(x2,y2,-1,0) = 0
					If m(x2,y2,1,0) = 0
					If m(x2,y2,0,1) = 1
						canvas.Color = Color.Blue
						canvas.DrawRect(x3,y3+th/2,tw,th/2)
						cont=False
					End If 
					End If 
					End If
					End If
					' if not surrounded by water
					Local cnt:Int=0
					For Local y4:=-1 To 1
					For Local x4:=-1 To 1
						If m(x2,y2,x4,y4) = 0
							cnt+=1
						End If
					Next
					Next
					If cnt=8
						canvas.Color = Color.Blue
						canvas.DrawRect(x3+tw/4,y3+th/4,tw/2,th/2)
						cont=False
					End If
					'if water below and no abow and no left and right
					If m(x2,y2,0,1) = 2
					If m(x2,y2,0,-1) = 0
					If m(x2,y2,-1,0) = 0
					If m(x2,y2,+1,0) = 0
						canvas.Color = Color.Blue
						canvas.DrawRect(x3,y3+th/2,tw,th/2)
						cont = False
					End If 
					End If
					End If 
					End If 
					'all else
					If cont=True
						canvas.Color = Color.Blue
						canvas.DrawRect(x3,y3,tw,th)
					End If
		End Select
		Next
		Next
#end

		'Draw the ladders		
		For Local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=(x*tw)+mox
			Local y3:Int=(y*th)+moy
			If x2>=0 And x2<mapwidth And y2>=0 And y2<mapheight
			If mymap.mapladder[x2,y2] = 1
				canvas.Color = Color.Brown
				canvas.DrawRect(x3,y3,tw,th)
				canvas.Color = Color.Red
				canvas.DrawRect(x3,y3,tw/4,th/3)
			End If
			End if
		Next
		Next		
		' Draw the player
		pmx = (px-(mcx*tw))+mox
		pmy = (py-(mcy*th))+moy
		canvas.Color = Color.White
		canvas.DrawRect(pmx,pmy,pw,ph)
		'draw monsters
		
		For Local i:=Eachin myflyingmonster
			Local x1:Int=i.px
			Local y1:Int=i.py
			Local x2:Int=(x1-(mcx*tw))+mox
			Local y2:Int=(y1-(mcy*th))+moy
			canvas.Color = Color.Red
			canvas.DrawRect(x2,y2,tw,th)
			
			'canvas.Color = Color.White
			'canvas.DrawText(i.state,x2,y2)
			'canvas.DrawText(i.substate,x2,y2+12)
			'canvas.DrawText(i.x*i.w+","+i.y*i.h,x2,y2+22)
			'canvas.DrawText(i.px+","+i.py,x2,y2+37)
			
			
			
		Next
		
		' Draw the bullets
		'
		canvas.OutlineMode=OutlineMode.Solid
		canvas.OutlineColor = Color.Grey
		canvas.OutlineWidth = 1					
		canvas.Color = Color.Yellow
		For Local i:=Eachin mybullet
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			canvas.DrawCircle(x2,y2,i.w)
		Next
		' Draw the grenades
		'
		canvas.Color = Color.Titanium
		For Local i:=Eachin mygrenade
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			canvas.DrawCircle(x2,y2,4)
		Next
		' Draw the fragmentation 
		'
		canvas.Color = Color.Gold
		For Local i:=Eachin myfrag
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			canvas.DrawCircle(x2,y2,3)
		Next		
		' Draw the items
		'
		canvas.Color = Color.Red
		For Local i:=Eachin myitem
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy			
			canvas.DrawCircle(x2,y2,3)
		Next
		'
		' Draw the tentacles 
		'
		
		For Local i:=Eachin mytentacle
			Local x1:Int=i.basex-mcx*tw+mox
			Local y1:Int=i.basey-mcy*th+moy			
			Local x2:Int=i.topx-mcx*tw+mox
			Local y2:Int=i.topy-mcy*th+moy			
			canvas.Color = Color.Green
			For Local y3:Int=-1 To 1
			For Local x3:Int=-1 To 1
				canvas.DrawLine(x1+x3,y1+y3,x2+x3,y2+y3)
			Next
			Next
			If i.grabbed = True
				canvas.Color = Color.Red
				canvas.DrawRect(x2-(tilewidth/2),y2-(tileheight/2),tilewidth,tileheight)
			End If
		Next
		canvas.OutlineMode=OutlineMode.None	
		'
	End Method
	Method m:Int(x:Int,y:Int,offx:int,offy:int)
		Return mywatermap.map[x+offx,y+offy]
	End Method
	Method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	 Method
End Class 

Class theflyingmonster
	Field px:float,py:Float 'pixel position (0-width)
	Field sx:Float,sy:Float 'movement speed
	Field x:Int,y:Int 'tile x and y position
	Field w:Float,h:Float
	Field hp:Int 'hitpoints
	Field deleteme:Bool
	Field dbx:Int,dby:Int
	Field dbtime:Int
	' movement between tiles
	' Field ox:Int,oy:Int
	' tx and ty are the next tile the flying monster
	' are on.
	'Field tx:Int,ty:Int
	Field state:String
	Field substate:String
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.w = tilewidth
		Self.h = tileheight
		px = x*w
		py = y*h
		hp = Rnd(10,30)
		'set the movement speed
		sx = Rnd(0.3,3)
		sy = sx
		state="hatched"
	End Method
	Method update()		
		
		If px < x*w Then px += sx
		If px > x*w Then px -= sx
		If py < y*h Then py += sy
		If py > y*h Then py -= sy
		If distance(px,py,x*w,y*h) > 8 Then Return
		Select state
			Case "hatched"
				state="takeoff"
'				ty=3 'move distance
			Case "takeoff"
				takeoff()
			Case "roam"								

				Select substate
					Case "left"
						x-=1						
						If mymap.mapfinal[x-1,y]  <> mymap.tileempty Then substate="right"
						If x<3 Then substate="right"
						' if flying on the ground level then move up 1 tile
						If mymap.mapfinal[x,y+1]  <> mymap.tileempty Then y-=1
						If mymap.mapfinal[x,y-1]  <> mymap.tileempty Then y+=1
					Case "right"
						x+=1
						If mymap.mapfinal[x+1,y]  <> mymap.tileempty Then substate="left"
						If x>mapwidth-3 Then substate="left"
						' if flying on the ground level then move up 1 tile						
						If mymap.mapfinal[x,y+1]  <> mymap.tileempty Then y-=1
						If mymap.mapfinal[x,y-1]  <> mymap.tileempty Then y+=1
					Case "up"
						y-=1						
						If mymap.mapfinal[x,y-2]  <> mymap.tileempty Then 
							If Rnd()<.5
								substate="left"
								Else
								substate="right"
							Endif							
						Endif
						If y<3 Then 
							If Rnd() < .5
								substate="right"
							Else
								substate="left"
							Endif
						End If
					Case "down"
						y+=1
						If mymap.mapfinal[x,y+2]  <> mymap.tileempty
							If Rnd() < .5
								substate="left"						
								Else
								substate="right"
							End If
						Endif
				End Select
				' Change direction to up or down if possible
				' sometimes
				gorandupordown()
				gorandleftorright()
				'change direction sometimes to left or right
				landandlayegg()
			Case "landlayegg"
				y+=1
				If mymap.mapfinal[x,y+1]  <> mymap.tileempty
					state="layegg"
				End If
			Case "layegg"
				If mymap.mapfinal[x,y] = 1 Then
				mymap.mapfinal[x,y] = 3
				mymap.updateimage(mymap.mapcanvas)				
				Else
				
				End If
				state="takeoff"
		End Select
	End Method
	Method landandlayegg()
		' Sometimes land and lay egg
		If Rnd() < (egglayingfreq/10)
			Local exitloop:Bool=False
			Local y1:Int=y
			Local egghere:Bool=False
			While exitloop = False
				If mymap.mapfinal[x,y1] = 3 Then 
					Return
				End If
				If mymap.mapfinal[x,y1]  <> mymap.tileempty Then exitloop = True
				y1+=1
			Wend
			Local cnt:Int=0
			For Local i:=Eachin myflyingmonster
				cnt+=1
			Next
			'if more then max monsters no lay egg
			If cnt<maxflyingmonsters Then		
				state="landlayegg"
			End If
		End If	
	End Method
	Method gorandleftorright()
		If substate="up" Or substate="down"
			If Rnd() < 0.1
				Local exitloop:Bool=False
				Local x1:Int=x
				Local cnt:Int=0
				While exitloop = False
					x1-=1
					cnt+=1
					If mymap.mapfinal[x1,y] <> mymap.tileempty Or x1<3
						exitloop = True
					End If
				Wend				
				If cnt>8 Then substate = "left"
			End If
			If Rnd() < 0.1
				Local exitloop:Bool=False
				Local x1:Int=x
				Local cnt:Int=0
				While exitloop = False
					x1+=1
					cnt+=1
					If mymap.mapfinal[x1,y] <> mymap.tileempty Or x1>mapwidth-3
						exitloop = True
					End If
				Wend				
				If cnt>8 Then substate = "right"					
			Endif
		Endif			
	End Method
	Method gorandupordown()
		If substate="left" Or substate="right"
			If Rnd() < .1
				Local exitloop:Bool=False
				Local y1:Int=y
				Local cnt:Int=0
				While exitloop=False
					y1-=1
					cnt+=1
					If mymap.mapfinal[x,y1] <> mymap.tileempty
						exitloop = True
					Endif
					If y1<3 Then exitloop = True
				Wend			
				If cnt>8 Then substate="up"					
			End If
			If Rnd() < .13 And substate<>"up"					
				Local exitloop:Bool=False
				Local y1:Int=y
				Local cnt:Int=0
				While exitloop=False
					y1+=1
					cnt+=1
					If mymap.mapfinal[x,y1]  <> mymap.tileempty
						exitloop = True
					Endif
				Wend
				If cnt>8 Then substate="down"
			End If
		End If	
	End Method
	Method takeoff()
		y-=1
		If mymap.mapfinal[x,y-1]  <> mymap.tileempty Then 
		state="roam"
		If Rnd(0,1) < 0.5 
			substate="left"
		Else
			substate="right"
		Endif
		Endif
	End Method
	Method draw(canvas:Canvas)
	    Local x1:Float=screenwidth/Float(mapwidth)*Float(x)
    	Local y1:Float=screenheight/Float(mapheight)*Float(y)
    	canvas.Color = Color.White
    	'SetColor 255,255,255
		canvas.DrawRect(x1,y1,3+2,3+2)
		canvas.Color = Color.Red
    	'SetColor 255,0,0		
		canvas.DrawRect(x1+1,y1+1,3,3)

	End Method
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function	
End Class

Class watermap
	Field freq:Int 'how many updates per cycle
	Field tw:Float,th:Float
	Field w:Int,h:Int
	Field map:= New Int[1,1] 
	Field px:Int,py:Int
	Field waterimage:Image
	Field watercanvas:Canvas
	Method New(sw:Float,sh:float,w:float,h:Float,freq:int)
		Self.freq = freq
		tw = sw/w
		th = sh/h
		map = New Int[w,h]
		Self.w = w
		Self.h = h
		waterimage=New Image(tw+1,th+1)
		watercanvas = New Canvas(waterimage)
		watercanvas.Color = Color.Blue
		watercanvas.DrawRect(0,0,tw+1,th+1)
		watercanvas.Flush()
	End Method 
	Method update()
		If Mouse.ButtonDown(MouseButton.Left)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 2
			End If
		End If
		If Mouse.ButtonDown(MouseButton.Right)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 1
			End If
		End If
		If Mouse.ButtonDown(MouseButton.Middle)
			Local x:Int= Mouse.X/tw
			Local y:Int = Mouse.Y/th
			If x>0 And x<w And y>0 And y<h 
				map[x,y] = 0
			End If
		End If

		For Local i := 0 Until freq
			updatewater(Rnd(2,w-2),Rnd(2,h-2))
		Next
	End Method 
	Method addwater()
		For Local y:=-1 To 1
		For Local x:=-1 To 1
			If Rnd()<.5 Then 
				map[px+x,py+y] = 2
			End If 
		Next
		Next
	End Method
	Method findpoorspot()
		For Local y:=0 Until h
		For Local x:=0 Until w
			If map[x,y] = 0
			px=x
			py=y
			Return
			End If 
		Next
		Next
	End Method 
	Method updatewater(x:Int,y:Int)
		Local s:Int=Rnd(0,6)
		If map[x,y] = 2 Then
			Select s
			Case 0
				If map[x-1,y] = 0
				If map[x+1,y] = 1
					map[x-1,y] = 2
					map[x,y] = 0				
				End If
				Endif
			Case 1
				If map[x-1,y] = 1
				If map[x+1,y] = 0
					map[x+1,y] = 2
					map[x,y] = 0				
				End If
				End If
			Case 2
				If map[x,y+1] = 0
					map[x,y+1] = 2
					map[x,y] = 0
				End If				
			Case 3
				If map[x-1,y] = 0
				If map[x-1,y+1] = 0
				If map[x,y+1] = 2
					map[x,y] = 0
					map[x-1,y+1] = 2
				End If	
				End If 
				End If
			Case 4 'swooop right
				If map[x+1,y] = 0
				If map[x-1,y] = 2
					Local exitloop:Bool=False
					Local mx:Int=x
					While exitloop = False										
						If map[mx,y] <> 2 Then exitloop = True					
						mx-=1
					Wend
					
					map[x+1,y] = 2
					Local el:Bool=False
					Local v:Int
					While el=False
					v=Rnd(mx+1,x)
					If map[v,y] = 2 Then el=True
					Wend
					map[v,y] = 0												
				End If
				End If 
			
			Case 5 'swooop left
				If map[x-1,y] = 0
				If map[x+1,y] = 2
					Local exitloop:Bool=False
					Local mx:Int=x
					While exitloop = False										
						If map[mx,y] <> 2 Then exitloop = True					
						mx+=1
					Wend
					map[x-1,y] = 2
					map[Rnd(x,mx-1),y] = 0												
				End If 
				End If
			End Select
		End If
	End Method 
	Method makewater(x:Int,y:Int,w:Int,h:Int)
		For Local y1:=y Until y+h
		For Local x1:=x Until x+w
			map[x1,y1] = 2
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		canvas.BlendMode = BlendMode.Alpha		
		For Local y:=0 Until h
		For Local x:=0 Until w
			'If map[x,y] = 0
			'	canvas.Color = Color.Black
			'	canvas.DrawRect(x*tw,y*th,tw,th)
			'End If 
			'If map[x,y] = 1
			'	canvas.Color = Color.Grey
			'	canvas.DrawRect(x*tw,y*th,tw,th)
			'End If 
			If map[x,y] = 2
				'canvas.Color = New Color(0,0,1,.5)'Color.Blue
				'canvas.DrawRect(x*tw,y*th,tw,th)
				canvas.Alpha = 0.5
				canvas.DrawImage(waterimage,x*tw,y*th)
			End If 
			'If map[x,y] = 3
			'	canvas.Color = New Color(.5,0,0)
			'	canvas.DrawRect(x*tw,y*th,tw,th)
			'End If 
		Next
		Next
	End Method 
End Class 

Class map
	Field tw:Float,th:Float
	Field mw:Float,mh:Float
	Field sw:Float,sh:Float,mmh:Float,mmw:Float'mmh is actual finalmap size
	Field map:=New Int[1,1]
	Field mapfinal:=New Int[1,1]
	Field mapladder:=New Int[1,1]
	Field mapimage:Image
	Field mapcanvas:Canvas
	Field mapladderimage:Image
	Field mapladdercanvas:Canvas
	Field mapdoor:=New Int[1,1]
	Field tilesolid:Int=0
	Field tileempty:Int=1
	Field tileegg:Int=3
	Field tileturret:Int=4
	Field tileslime:Int=10
	Field tilemineable:Int=50
	Method New(sw:float,sh:Float,mw:Float,mh:Float)
		Self.mmw = mw
		Self.mmh = mh
		Self.mw = mw/3
		Self.mh = mh/3		
		Self.sw = sw
		Self.sh = sh
		mapimage = New Image(sw,sh)
		mapcanvas = New Canvas(mapimage)
		mapladderimage = New Image(sw,sh)
		mapladdercanvas = New Canvas(mapladderimage)
		tw = sw/mmw
		th = sh/mmh
		map = New Int[mw,mh]
		mapfinal = New Int[mmw,mmh]
		mapladder = New Int[mmw,mmh]
		mapdoor = New Int[mmw,mmh]
		makemap()
		finalizemap()
		For Local i:=0 Until 1000
			Local x:Int=Rnd(2,mmw-4)
			Local y:Int=Rnd(17,mmh-4)
			If mapfinal[x,y] = 1
			If mapfinal[x,y+1] = 0
			mapfinal[x,y] = 3
			End If
			End If
		Next		
		createfinalmineable()
		updateladderimage(mapladdercanvas)
		updateimage(mapcanvas)
	End Method 
	' Here we create the parts on the mapfinal that can be mined
	' by the player (like in minecraft/digger) tilemineable
	Method createfinalmineable()
		' 3 high mineable mineshafts right to left
		For Local y1:Int=15 Until mmh-10
		For Local x1:Int=3 Until mmw-3
			' Find suitable spot
			If mapfinal[x1,y1] <> tilesolid Then Continue
			If mapfinal[x1+1,y1] <> tileempty Then Continue
			If mapfinal[x1,y1+1] <> tilesolid Then Continue
			If mapfinal[x1,y1+2] <> tilesolid Then Continue
			If mapfinal[x1,y1+3] <> tilesolid Then Continue
			If mapfinal[x1+1,y1+4] <> tilesolid Then Continue
			If mapfinal[x1+1,y1+1] <> tileempty Then Continue
			If mapfinal[x1+1,y1+2] <> tileempty Then Continue
			If mapfinal[x1+1,y1+3] <> tileempty Then Continue
			' See how far left we can go
			Local len:Int=0			
			For Local x2:Int=x1 Until 3 Step -1
				If mapfinal[x2,y1] <> tilesolid Then Exit
				If mapfinal[x2,y1+1] <> tilesolid Then Exit
				If mapfinal[x2,y1+2] <> tilesolid Then Exit
				If mapfinal[x2,y1+3] <> tilesolid Then Exit
				If mapfinal[x2,y1+4] <> tilesolid Then Exit
				len+=1
			Next
			' If we can go deep enough then prepare mineshaft
			If len<=10 Then Continue
			len = Rnd(7,len)
			For Local x2:Int=x1 Until x1-(len-3) Step -1
			For Local y2:Int=y1+1 Until y1+4 
				mapfinal[x2,y2] = tilemineable
			Next
			Next
		Next
		Next
		'
		'
		' 3 high mineable mineshafts left to right
		For Local y1:Int=15 Until mmh-10
		For Local x1:Int=3 Until mmw-3
			' Find suitable spot
			If mapfinal[x1,y1] <> tilesolid Then Continue
			If mapfinal[x1-1,y1] <> tileempty Then Continue
			If mapfinal[x1,y1+1] <> tilesolid Then Continue
			If mapfinal[x1,y1+2] <> tilesolid Then Continue
			If mapfinal[x1,y1+3] <> tilesolid Then Continue
			If mapfinal[x1-1,y1+4] <> tilesolid Then Continue
			If mapfinal[x1-1,y1+1] <> tileempty Then Continue
			If mapfinal[x1-1,y1+2] <> tileempty Then Continue
			If mapfinal[x1-1,y1+3] <> tileempty Then Continue
			' See how far left we can go
			Local len:Int=0			
			For Local x2:Int=x1 Until mmw-4
				If mapfinal[x2,y1] <> tilesolid Then Exit
				If mapfinal[x2,y1+1] <> tilesolid Then Exit
				If mapfinal[x2,y1+2] <> tilesolid Then Exit
				If mapfinal[x2,y1+3] <> tilesolid Then Exit
				If mapfinal[x2,y1+4] <> tilesolid Then Exit
				len+=1
			Next
			' If we can go deep enough then prepare mineshaft
			If len<=10 Then Continue
			len = Rnd(7,len)
			For Local x2:Int=x1 Until x1+(len-3)
			For Local y2:Int=y1+1 Until y1+4 
				mapfinal[x2,y2] = tilemineable
			Next
			Next
		Next
		Next


	End Method
	Method finalizemap()
	For Local y:=1 Until mh-1
	For Local x:=1 Until mw-1
		If map[x,y] = tileempty
			For Local y2:=-1 To 1
			For Local x2:=-1 To 1
				mapfinal[(x*3)+x2,(y*3)+y2] = tileempty
			Next
			Next			
		End If
	Next
	Next
	' make ladders/vines
	For Local y:=0 Until mh
	For Local x:=0 Until mw
		If map[x,y] = 1
		If map[x-1,y] = 0
		If map[x+1,y] = 0			
			Local y2:Int=y
			While map[x,y2] <> 0				
				mapladder[(x*3),y2*3] = 1
				mapladder[(x*3),y2*3-1] = 1
				mapladder[(x*3),y2*3+1] = 1				
				y2-=1
			Wend
			y2=y
			While map[x,y2] <> 0				
				mapladder[(x*3),y2*3] = 1
				mapladder[(x*3),y2*3-1] = 1
				mapladder[(x*3),y2*3+1] = 1
				y2+=1
			Wend			
		End If
		End If 
		End If
	Next
	Next
	' make doors
	For Local i:=0 Until mmw*mmh/2
		Local x:=Rnd(2,mmw-4)
		Local y:=Rnd(2,mmh-2)
		' door right side of tunnel
'		If Rnd()<0
		If mapfinal[x,y] = 0
		If mapfinal[x+1,y] = 0
		If mapfinal[x-1,y] = 0
		If mapfinal[x-2,y] = 0
		If mapfinal[x-3,y] = 1
		If mapfinal[x,y+1] = 1
		If mapfinal[x,y+2]= 1
		If mapfinal[x,y+3] = 1
		If mapfinal[x,y+4] = 0
			mapfinal[x,y+1] = 1
			mapfinal[x,y+2] = 1
			mapfinal[x,y+3] = 1
			mapdoor[x,y+1 ] = 1
			mapdoor[x,y+2 ] = 1
			mapdoor[x,y+3 ] = 1
		End If 
		End If
		End If 
		End If 
		End If
		End If 
		End If
		End If
		End If
'		End If
		' door left side of tunnel
		If mapfinal[x-1,y-1] = 0
		If mapfinal[x,y] = 0
		If mapfinal[x-1,y] = 0
		If mapfinal[x+1,y] = 0
		If mapfinal[x+2,y] = 0
		If mapfinal[x+3,y] = 1
		If mapfinal[x,y+1] = 1
		If mapfinal[x,y+2]= 1
		If mapfinal[x,y+3] = 1
		If mapfinal[x,y+4] = 0
			mapfinal[x,y+1] = 1
			mapfinal[x,y+2] = 1
			mapfinal[x,y+3] = 1
			mapdoor[x,y+1 ] = 1
			mapdoor[x,y+2 ] = 1
			mapdoor[x,y+3 ] = 1
		End If 
		End If
		End If 
		End If 
		End If 
		End If
		End If 
		End If
		End If
		End If

	Next
	End Method
	Method makemap()
		For Local y:=1 Until 6
		For Local x:=1 Until mw-1
			map[x,y] = 1
		Next
		Next
		Local minedownx:Int=5+Rnd(mw-15)
		For Local y:=5 Until mh/2+10
			map[mw/2,y] = 1
		Next
		For Local i:=0 Until (mw*mh)*6
			Local x:Int=Rnd(2,mw-4)
			Local y:Int=Rnd(2,mh-4)
			If map[x,y] = 1					
				Local v:Int=Rnd(0,2)
				Select v
					Case 0'go left or right										
					If map[x-1,y] = 0
					If map[x+1,y] = 0										
					makeside(x,y,Rnd(0,2))
					End If 
					End If
					Case 1'go down Or up
					If map[x,y-1]=0
					If map[x,y+1]=0
					makevert(x,y,Rnd(0,2))
					End If
					End If
				End Select
			End If
		Next
		widenhorizontal()
	End Method
	Method widenhorizontal()
		For Local i:=0 Until mw*mh/2
			Local x:Int=Rnd(2,mw-2)
			Local y:Int=Rnd(2,mh-2)
			If map[x,y] = 1 And map[x,y-1] = 0 And map[x,y+1] = 0				
				Local w:Int=0
				Local x2:Int=x
				Local exitloop:Bool=False
				While exitloop = False
					If map[x2,y] = 0 Then exitloop = true 
					If map[x2,y-1] = 1 Then exitloop = True
					If map[x2,y+1] = 1 Then exitloop = True				
					x2+=1
					w+=1
				Wend
				'
				
				If w-2>3					
					For Local x2:Int=x To x+w-2
						map[x2,y-1] = 1
						map[x2,y+1] = 1
						If x2>x+2 And w>6 And x2<(x+5)
							map[x2,y+2] = 1
						End If
					Next
				End If
			End If
		Next
	End Method
	Method makevert(x:Int,y:Int,side:Int)
		Local l:Int=Rnd(4,20)
		If y<22 Then Return
		If y>mw-22 Then Return
		If side =  0'down		
			If overlap(x-4,y+1,x+4,y+l+2) = False
				For Local y2:=y To y+l
					map[x,y2] = 1
				Next
			End If
		End If
		If side =  1'up
			If overlap(x-4,(y-l)-3,x+4,y-1) = False
				For Local y2:=y-l To y
					map[x,y2] = 1
				Next
			End If
		End If

	End Method
	Method makeside(x:Int,y:Int,side:Int)		
		Local l:Int=Rnd(4,20)		
		If x<22 Then Return
		If x>mw-22 Then Return				
		If side=0 Then 'left				
			If overlap((x-l)-2,y-5,x,y+5) = False				
				For Local x2:=x-l Until x
					map[x2,y] = 1
				Next
			End If
		End If
		If side=1 Then 'right		
			If overlap(x+1,y-5,x+l+2,y+5) = False								
				For Local x2:=x Until x+l
					map[x2,y] = 1
				Next
			End If			
		end If		
	End Method
	Method overlap:bool(x1:Int,y1:Int,x2:Int,y2:int)
		For Local y:=y1 Until y2
		For Local x:=x1 Until x2
			If x>0 And x<mw And y>0 And y<mh
				If map[x,y] = 1 Then Return True
			End If
		Next
		Next
		Return False
	End Method
	Method drawladder(canvas:Canvas)						
		For Local y:=0 Until mmh
		For Local x:=0 Until mmw
			Select mapladder[x,y]				
				Case 0
				'canvas.Color = Color.None
				'canvas.DrawRect(x*tw,y*th,tw,th)
				Case 1				
				canvas.Color = New Color(0.4,0,0)
				canvas.DrawRect(x*tw,y*th,tw,th)
				'canvas.DrawRect(0,0,100,100)
				canvas.Color = New Color(0.7,0.7,0)
				canvas.DrawLine(x*tw,y*th,x*tw,y*th+th-2)
			End Select			
		Next
		Next		
	End Method 	

	Method updateladderimage(canvas:Canvas)				
	
		canvas.BlendMode = BlendMode.Opaque
		'canvas.Clear(New Color(0,0,0,.5))
		For Local y:=0 Until mmh
		For Local x:=0 Until mmw
			Select mapladder[x,y]				
				Case 0
				canvas.Color = Color.None
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case 1								
				canvas.Color = Color.Red
				canvas.Alpha = 0.5
				canvas.DrawRect(x*tw,y*th,tw,th)
				canvas.Color = Color.Yellow
				canvas.DrawLine(x*tw,y*th,x*tw,y*th+th-2)
			End Select			
		Next
		Next
		canvas.Flush()
	End Method 	
	Method draw(canvas:Canvas)		
		For Local y:=0 Until mmh
		For Local x:=0 Until mmw
			Select mapfinal[x,y]
				Case 0
				canvas.Color = Color.Black
				Case 1
				canvas.Color = Color.White
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case 3				
				canvas.Color = Color.Yellow
				canvas.DrawRect(x*tw,y*th,tw,th)
			End Select	
		Next
		Next		
	End Method 
	Method updateimage(canvas:Canvas)			
		'canvas.BlendMode = BlendMode.Opaque	
		canvas.Clear(Color.Black)
		canvas.BlendMode = BlendMode.Opaque
		For Local y:=0 Until mmh
		For Local x:=0 Until mmw
			Select mapfinal[x,y]
				Case 0
				'canvas.Alpha = 1
				canvas.Color = Color.Brown
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case tilesolid
				'canvas.Alpha = 0.5
				'canvas.Color = Color.None'New Color(0,0,0,.8)
				'canvas.DrawRect(x*tw,y*th,tw,th)
				Case tileegg		
				canvas.Alpha = 0.8	
				canvas.Color = Color.Yellow
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case tileturret
				canvas.Alpha = 0.8	
				canvas.Color = Color.Grey
				canvas.DrawRect(x*tw,y*th,tw,th)				
				Case tilemineable
				canvas.Alpha = 0.8	
				canvas.Color = Color.Brown.Blend(Color.Yellow,.2)
				canvas.DrawRect(x*tw,y*th,tw,th)
			End Select						
		Next
		Next
		canvas.Flush()
	End Method 
	Method tilecollide:Bool(x:Int,y:Int,w:Int,h:Int,tile:Int)
		Local lefttopx:Int		=((x)/tilewidth)
		Local lefttopy:Int		=((y)/tileheight)
		Local righttopx:Int		=((x+w)/tilewidth)
		Local righttopy:Int		=((y)/tileheight)
		Local leftbottomx:Int	=((x)/tilewidth)
		Local leftbottomy:Int	=((y+h)/tileheight)
		Local rightbottomx:Int	=((x+w)/tilewidth)												
		Local rightbottomy:Int	=((y+h)/tileheight)
		If lefttopx < 0 Or lefttopx >= mmw Then Return False
		If lefttopy < 0 Or lefttopy >= mmh Then Return false
		If righttopx < 0 Or righttopx >= mmw Then Return false
		If righttopy < 0 Or righttopy >= mmh Then Return false
		If leftbottomx < 0 Or leftbottomx >= mmw Then Return false
		If leftbottomy < 0 Or leftbottomy >= mmh Then Return false
		If rightbottomx < 0 Or rightbottomx >= mmw Then Return false
		If rightbottomy < 0 Or rightbottomy >= mmh Then Return false
		
		If mapfinal[lefttopx,lefttopy] = tile Then Return True
		If mapfinal[righttopx,righttopy] = tile Then Return True
		If mapfinal[leftbottomx,leftbottomy] = tile Then Return True
		If mapfinal[rightbottomx,rightbottomy] = tile Then Return True						
		Return False
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
		If lefttopx < 0 Or lefttopx >= mmw Then Return True
		If lefttopy < 0 Or lefttopy >= mmh Then Return True
		If righttopx < 0 Or righttopx >= mmw Then Return True
		If righttopy < 0 Or righttopy >= mmh Then Return True
		If leftbottomx < 0 Or leftbottomx >= mmw Then Return True
		If leftbottomy < 0 Or leftbottomy >= mmh Then Return True
		If rightbottomx < 0 Or rightbottomx >= mmw Then Return True
		If rightbottomy < 0 Or rightbottomy >= mmh Then Return True
		
		If mapfinal[lefttopx,lefttopy] <> mymap.tileempty Then Return True
		If mapfinal[righttopx,righttopy] <> mymap.tileempty Then Return True
		If mapfinal[leftbottomx,leftbottomy] <> mymap.tileempty Then Return True
		If mapfinal[rightbottomx,rightbottomy] <> mymap.tileempty Then Return True						
		Return False
	End Method	
End Class

Global mymenuselect:menuselect
Global mymap:map
Global mygrowslime:growslime
Global mytentacle:List<tentacle> = New List<tentacle>
Global mywatermap:watermap
Global myflyingmonster:List<theflyingmonster> = New List<theflyingmonster>
Global myturret:List<turret> = New List<turret>
Global mybullet:List<bullet> = New List<bullet>
Global mygrenade:List<grenade> = New List<grenade>
Global myfrag:List<frag> = New List<frag>
Global myplayer:player
Global myitem:List<item> = New List<item>

Class MyWindow Extends Window
	Field time:Int
	Method New()
		Super.New("",800,600)
		Fullscreen = False
		mymenuselect = New menuselect()
		'resetmap(Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		
		If gamestate="select" Then 
			mymenuselect.update()
			mymenuselect.draw(canvas)
		End If
		If gamestate<>"play" Then Return
		If Keyboard.KeyReleased(Key.Key1) Then
			resetmap(screenwidth,screenheight)
		End If
		If Keyboard.KeyReleased(Key.Home) Then
			gamestate="select"
		End If  
		
		For Local i:=Eachin myflyingmonster
			i.update()
		Next
		For Local i:=Eachin myflyingmonster
			If i.deleteme = True Then myflyingmonster.Remove(i)
		Next

		mygrowslime.update("slow")

		' Update the tentacles
		For Local i:=Eachin mytentacle
			i.update()
		Next
		For Local i:=Eachin mytentacle
			If i.deleteme = True Then mytentacle.Remove(i)
		Next
		
		
		' Update the bullets
		For Local i:=Eachin mybullet
			i.update()
		Next
		For Local i:=Eachin mybullet
			If i.deleteme = True Then mybullet.Remove(i)
		Next

		
		For Local i:=Eachin myturret
			i.update()
		Next
		
		For Local i:=Eachin mygrenade
			i.update()
		Next
		For Local i:=Eachin mygrenade
			If i.deleteme = True Then mygrenade.Remove(i)
		Next

		For Local i:=Eachin myfrag
			i.update()
		Next
		For Local i:=Eachin myfrag
			If i.deleteme = True Then myfrag.Remove(i)
		Next

		For Local i:=Eachin myitem
			i.update()
		Next
		For Local i:=Eachin myitem
			If i.deleteme = True Then myitem.Remove(i)
		Next
						
		
		'debugbullettest
		'If Rnd(20)<2 Then mygrenade.AddLast(New grenade(myplayer.px,myplayer.py,myplayer.facing))
		
		'debugbullettest
		'If Rnd(10)<2 Then mybullet.AddLast(New bullet(myplayer.px,myplayer.py,Rnd(TwoPi)))
		
		time+=1
		If time>4000
		time=0
		'resetmap(Width,Height)
		End If
		'mywatermap.update()
		'mywatermap.addwater()		
		
		'player
		If Keyboard.KeyDown(Key.LeftShift) = False
			Local tp:Bool=False
			If Keyboard.KeyDown(Key.LeftControl) 
				myplayer.userscrollmap()
				tp=True
			End If
			If tp=False Then
				myplayer.updateplayercontrols()
			End If
			canvas.Clear(Color.Black)
			myplayer.draw(canvas)
		End If
		'minimap
		If Keyboard.KeyDown(Key.LeftShift)		
			canvas.Clear(Color.Black)
			canvas.DrawImage(mymap.mapimage,0,0)	
			mygrowslime.drawmap(canvas)
			
				
			mywatermap.draw(canvas)				
			canvas.Color = Color.White
			canvas.DrawImage(mymap.mapladderimage,0,0)		
			For Local i:=Eachin myflyingmonster
				i.draw(canvas)
			Next

			canvas.Color = New Color(255,255,255,0.5)
			Local x1:Int=myplayer.mcx*mymap.tw
			Local y1:Int=myplayer.mcy*mymap.th
			canvas.DrawRect(x1,y1,mymap.tw*myplayer.maptileswidth,mymap.th*myplayer.maptilesheight)
		End If
		addflyingmonster()
		'
		canvas.Scissor = New Recti(0,0,screenwidth,screenheight)
		canvas.Color = Color.White
		canvas.DrawText(App.FPS+"  Press 1(new level) or Home(selection). Left shift(total map view)",0,0)
		canvas.DrawText("Cursors(move), s(shotgun), g(grenade), m(mine) space(jump)..",0,20)
		canvas.DrawText(theversion,0,Height-20)	
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function addflyingmonster() 'hatch
	Local cnt:Int=0
	For Local i:=Eachin myflyingmonster
		cnt+=1
	Next
	If cnt<maxflyingmonsters
		'DebugLog (mapwidth+mapheight)/10
		For Local i:=0 Until (mapwidth+mapheight)/10
			If Rnd() < egghatchspeed
				Local x:Int=Rnd(mapwidth)
				Local y:Int=Rnd(mapheight)
				If mymap.mapfinal[x,y] = 3
					mymap.mapfinal[x,y] = 1
					myflyingmonster.AddLast(New theflyingmonster(x,y))
					mymap.updateimage(mymap.mapcanvas)
				End If
			End If
		Next
	End If
End Function

Function resetmap(Width:Int,Height:int)
		myflyingmonster.Clear()
		myturret.Clear()
		myitem.Clear()
		mybullet.Clear()
		myfrag.Clear()
		mygrenade.Clear()		
		SeedRnd(100+Microsecs())
		'Local s:Int=Rnd(140,150)
		'mapwidth = 
		'mapheight = s
		screenwidth = Width
		screenheight = Height
		mymap = New map(Width,Height,mapwidth,mapheight)
		myturret.AddFirst(New turret())		
		myturret.AddFirst(New turret())
		mymap.updateimage(mymap.mapcanvas)
		mygrowslime = New growslime()
		mywatermap = New watermap(Width,Height,mapwidth,mapheight,mapwidth*400)
		For Local y:=0 Until mapheight
		For Local x:=0 Until mapwidth
			mywatermap.map[x,y] = mymap.mapfinal[x,y]
			If mywatermap.map[x,y] = 1 
				mywatermap.map[x,y] = 0
			Elseif mywatermap.map[x,y] = 0
				mywatermap.map[x,y] = 1
			End If 	
			If mywatermap.map[x,y] = 3 Then 
				mywatermap.map[x,y] = 0
			End If
		Next
		Next
		mywatermap.findpoorspot()
		'
		myplayer = New player()
		
		myitem.Add(New item(100,100,"gold"))
		myitem.Add(New item(106,105,"gold"))
		myitem.Add(New item(110,115,"gold"))
		myitem.Add(New item(115,120,"gold"))

		'For Local i:Int=0 Until 20
		'myflyingmonster.Add(New theflyingmonster(5,5))
		'Next
End Function 

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
