' short list
' add - town shop
' add - player inventory (first draft - collected items get added)
' add - towns people(initiated)

' Bug - flying/walking monster attacking player can go through laser wall (first fix - more testing)
' Bug walking monster standing still
' check laser wall ontop of eggs situation


#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global developmode:Bool=False
Global theversion:String="Version 10-11-2017"
Global gamestate:String="select"
Global egghatchspeed:Float = 0.1 'how fast eggs hatch
Global egglayingfreq:Float = 0.1 ' lay lots of eggs 1 lay less eggs 0 '0 to 1
Global startingeggfreq:Float = 0.2 '0 to 1 0 is none 1 is full
Global maxflyingmonsters:Int=30
Global maxwalkingmonsters:Int=30
Global mapwidth:Int=320
Global mapheight:Int=240
Global screenwidth:Int=800
Global screenheight:Int=600
Global tilewidth:Int=20
Global tileheight:Int=20
Global maxplayeritems:Int=10

'
' This is the code for the people in the town.
'
Class townperson
	Field px:float,py:Float 'pixel position (0-width)
	Field sx:Float,sy:Float 'movement speed
	Field x:Int,y:Int 'tile x and y position
	Field w:Float,h:Float
	Field hp:Int 'hitpoints
	Field hpmax:Int
	Field deleteme:Bool
	Field state:String
	Field substate:String
	Field jx:Float
	Field jy:Float
	Field oldpy:Float 'old py coordinate
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.w = tilewidth
		Self.h = tileheight
		px = x*w
		py = y*h
		hp = Rnd(10,30)
		hpmax = hp
		'set the movement speed
		sx = Rnd(0.3,1)
'		sy = sx
		state="roam"
		If Rnd(10)<2 Then substate="left" Else substate="stand"
	End Method
	Method update()		
'		If laserwait>0 Then laserwait-=1
		
		If px < x*w Then px += sx
		If px > x*w Then px -= sx
		If distance(px,py,x*w,y*h) > 8 Then Return
				
		Select state
			Case "roam"												
				Select substate
					Case "left"
						If x<3 Then substate="right" ; Return
						x-=1
						'If Rnd(50) < 1 And mymap.mapfinal[x-1,y] = mymap.tileempty And mymap.mapfinal[x-1,y+1] <> mymap.tileempty Then substate="right"						
						'If Rnd(50) < 1 And cannotgohere(x+1,y) = False And cannotgohere(x+1,y+1)=True Then substate="right" 
						If cannotgohere(x-1,y) = True Then substate = "right"
						If cannotgohere(x-1,y+1) = False Then substate = "right"
						'If mymap.mapfinal[x-1,y]  <> mymap.tileempty Then substate="right"
						'If mymap.mapfinal[x-1,y+1] = mymap.tileempty Then substate="right"
						
						
					Case "right"						
						If x>mapwidth-3 Then substate="left" ; Return
						x+=1
						'If Rnd(50) < 1 And cannotgohere(x-1,y) =  False And cannotgohere(x-1,y+1)=True Then substate="left"
						If cannotgohere(x+1,y) = True Then substate="left"
						If cannotgohere(x+1,y+1) = False Then substate="left"
						'If Rnd(50) < 1 And mymap.mapfinal[x+1,y] = mymap.tileempty And mymap.mapfinal[x+1,y+1] <> mymap.tileempty Then substate="left"						
						'If mymap.mapfinal[x+1,y]  <> mymap.tileempty Then substate="left"
						'If mymap.mapfinal[x+1,y+1] = mymap.tileempty Then substate="left"
						
				End Select
				randaction()
		End Select
	End Method
	Method randaction()
		If substate = "left" And Rnd(600)<2 Then changedirection() ; Return
		If substate = "right" And Rnd(600)<2 Then changedirection(); Return
		If substate = "stand" And Rnd(600)<2 Then 
			If Rnd(2) < 1 Then substate = "left" Else substate="right"
			Return
		End If
		If Rnd(100) < 2 Then substate = "stand"; Return
	End Method
	' Check if tile on map is blocked
	Method cannotgohere:Bool(x:Int,y:Int)
		If mymap.mapfinal[x,y] = mymap.tilesolid Then Return True
		If mymap.mapfinal[x,y] = mymap.tilemineable Then Return True
		If mymap.mapfinal[x,y] = mymap.tileturret Then Return True
		Return False
	End Method
	Method changedirection()
		state = "roam"
		If substate = "left" Then 
			substate="right" 
			x += 2		
		Else 
			substate="left"
			x -= 2
		End If
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
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function  	     
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function	
	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	 Function
End Class

' 
' Tree sprite generator
'
Class tree
	Field image:Image
	Field icanvas:Canvas
	Field px:Int,py:Int
	Field pw:Float,ph:Float
	Field mapone:Color[][]
	Field nocolor:Color = New Color(0,0,0,0)
	Field outlcolor:Color = New Color(.01,0.1,0.1)
	Field treecolor1:Color = New Color(Rnd(.5,.8),Rnd(.8,1),0)
	Field treecolor2:Color = New Color(Rnd(.3,.7),Rnd(.7,.78),0)
	Field treecolor3:Color = New Color(Rnd(.25,.5),Rnd(.5,.68),0)
	Field treecolor4:Color = New Color(Rnd(.1,.20),Rnd(.2,.45),0)
	Field treecolor1r:Color = New Color(Rnd(.1,.5),0,0)
	Field basecolor1:Color = New Color(.5,.24,0)
	Field basecolor2:Color = New Color(.8,.4,0)
	Field basecolor3:Color = New Color(.9,.45,.0)
	Method New(x:Int,y:Int,w:Int,h:Int)
		If Rnd(3)<2 Then 
			treecolor1 = treecolor1.Blend(treecolor1r,.1)
			treecolor2 = treecolor1.Blend(treecolor1r,.2)
			treecolor3 = treecolor1.Blend(treecolor1r,.3)
			treecolor4 = treecolor1.Blend(treecolor1r,.4)
		End If
		px = x
		py = y
		pw = w
		ph = h
		mapone = New Color[w][]
		For Local i:Int=0 Until w
			mapone[i] = New Color[h]
		Next
		maketree()
		image = New Image(pw,ph)',TextureFlags.Dynamic)
		icanvas = New Canvas(image)
		icanvas.Clear(New Color(0,0,0,0))
		icanvas.Flush()
		Local opx:Int=x
		Local opy:Int=y
		Self.px = 0
		Self.py = 0
		draw(icanvas)
		icanvas.Flush()
		Self.px = opx
		Self.py = opy
	End Method
	Method maketree()
		Local mx:Float=0.05
		Local my:Float=.1
		Local y:Float=1
		Local x:Float=pw/2+1
		Local base:Float=0
		Local bounce:Float=.1
		Local col:Color
		Local num:Float=2
		Local stap:Float=Rnd(0.001,0.005)
		Local stap2:Float=Rnd(0.01,0.2)
		Local stap3:Float=Rnd(0.5,1.5)
		' Place two black pixels at the top of the tree
		mapone[x-1][0] = outlcolor
		mapone[x-2][0] = outlcolor
		' create the tree
		While (y+5)<=(ph-(ph/20)) 
			y+=my
			x+=mx
			' stay inside the image
			If x>=pw Then x=pw-2
			If x<=0 Then x=0
			' change color of the tree depending
			' on the current y location
			If y<ph/1.4 Then col = treecolor4										
			If y<ph/1.6 Then col = treecolor3
			If y<ph/1.9 Then col = treecolor2
			If y<ph/4 Then col = treecolor1
			' fill the current line
			filltoleft(x,y,pw-x,col)
			' black pixel to the left and right
			mapone[x][y] = outlcolor
			mapone[pw-x][y] = outlcolor		
			' next step in the tree shape
			mx-=stap
			If y<ph/1.45 Then 
				If mx<0 
					If x < ((pw/2)+num) Then mx=bounce ; bounce+=stap2 ; num+=stap3
				End If				
			Else	
				If mx<0	
				If x<((pw/2)+num) Then bounce=.1 ; mx=bounce ; num-=stap3
				Endif
			End If
		Wend
		' Make sure the bottom of the tree is also drawn
		filltoleft(x,y,pw-x,outlcolor)
		' Make the tree trunk
		maketreebase()
	End Method
	'
	' Fill from x to tox on y line using col(or)
	' We go from right to left and fill the line with 
	' a number. (tree inside color)
	'
	Method filltoleft(x:Int,y:Int,tox:Int,col:Color)		
		Local ls:Int=(pw/2)
		Local len1:Int=(x-ls)/2
		Local len2:Int=(x-ls)/1.7		
		For Local x2:Int=x To tox Step -1
			mapone[x2][y] = col
			If col = treecolor2 Then
			If Rnd(4) < 1 And distance(x2,0,tox,0) < len1 And y<ph/2 Then mapone[x2][y] = treecolor1
			If Rnd(4) < 1 And distance(x2,0,x,0)< len1 And y<ph/2 Then mapone[x2][y] = treecolor1
			If Rnd(2)<1.3 And distance(x2,0,ls-len1,0) < 2 And y<ph/2 Then mapone[x2][y] = treecolor1
			If Rnd(2)<1.3 And distance(x2,0,ls+len1,0) < 2 And y<ph/2 Then mapone[x2][y] = treecolor1
			End If
			If col=treecolor1
			If Rnd(2) < 1 And y>5 And distance(x2,0,ls,0) < 3 Then mapone[x2][y] = treecolor2
			End If
			If col=treecolor3
			If Rnd(2)<1.3 And distance(x2,0,ls,0) < len2 And y<ph/1.8 Then mapone[x2][y] = treecolor2
			End If
			If col=treecolor4
			If Rnd(2)<1.3 And distance(x2,0,ls,0) < len2 And y<ph/1.45 Then mapone[x2][y] = treecolor3
			End If

		Next
	End Method
	Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)  
    	Return Abs(x2-x1)+Abs(y2-y1)  
  	End Function 
	Method maketreebase()
		' treebase
		For Local y:Int=ph-(ph/5) Until ph
		For Local x:Int=(pw/2)-(pw/8) Until (pw/2)+(pw/8)
			If x<0 Or y<0 Or x>=pw Or y>= ph Then Continue
			mapone[x][y] = basecolor1
			If x=(pw/2)-(pw/8) Then mapone[x][y] = outlcolor
			If x=(pw/2)+(pw/8)-1 Then mapone[x][y]= outlcolor
			If y=ph-1 Then mapone[x][y]=outlcolor
		Next
		Next
		For Local y:Int=ph-(ph/5) Until ph-(ph/5)
		For Local x:Int=(pw/2)-(pw/8) Until (pw/2)+(pw/8)
			If x<0 Or y<0 Or x>=pw Or y>= ph Then Continue
			mapone[x][y] =outlcolor
		Next
		Next

		' tree base center lighting
		For Local y:Int=ph-(ph/7) Until ph-1
		For Local x:Int=(pw/2)-(pw/30) Until (pw/2)+(pw/30)
			If x<0 Or y<0 Or x>=pw Or y>= ph Then Continue
			mapone[x][y] = basecolor3
		Next
		Next
		For Local y:Int=ph-(ph/7) Until ph-1
		For Local x:Int=(pw/2) Until (pw/2)+(pw/30)
			If x<0 Or y<0 Or x>=pw Or y>= ph Then Continue
			mapone[x][y] = basecolor2
		Next
		Next
		'Remove two black pixels from the bottom of the treebase
		mapone[(pw/2)-(pw/8)][ph-1] = nocolor
		mapone[(pw/2)+(pw/8)-1][ph-1] = nocolor


	End Method

	Method draw(canvas:Canvas)
		'canvas.Clear(New Color(0,0,0,0))
		For Local y:Int=0 Until ph
		For Local x:Int=0 Until pw
			If mapone[x][y] = nocolor Then Continue
			canvas.Color = mapone[x][y]
			canvas.DrawRect(px+(x*1),py+(y*1),1,1)
		Next
		Next
	End Method
End Class
'
' The town buildings
'
Class building
	Field image:Image
	Field icanvas:Canvas
	Field px:Int,py:Int
	Field totalwidth:Int
	Field blockhouse:Int=1
	Field blockdoor:Int=2
	' For collision (enter/flee in home/shop)
	Field doorx:Int,doory:Int
	Field doorwidth:Int,doorheight:Int
	Field blocksmallwindow:Int=3
	Field blockwidewindow:Int=4
	Field blockcrateleft:Int=5
	Field blockcrateright:Int=6
	Field blockiceboxleft:Int=7
	Field blockiceboxright:Int=7
	Field blocktoiletleft:Int=8
	Field blocktoiletright:Int=9
	Field blockfrontcrate:Int=10
	Field blockrooftop:Int=11
	Field blockchimney:Int=12
	Field blockshopsign:Int=13
	Field houselayer:Int[]=New Int[3] 'base blocks
	Field rooftoplayer:Int[]=New Int[3]
	Field chimneylayer:Int[]=New Int[3]
	Field doorlayer:Int[] = New Int[3]
	Field windowlayer:Int[] = New Int[3] '011010'
	Field housesidelayer:Int[] = New Int[2]
	Field shopsignlayer:Int[] = New Int[3]
	Field frontlayer:Int[] = New Int[6]
	Field bw:Float,bh:Float
	Method New(x:Int,y:Int,w:Int,bw:Int,bh:Int,isshop:Bool)
		Self.bw = bw
		Self.bh = bh
		image = New Image(bw*(w+2),bh*2)
		image.Handle=New Vec2f( 0,0 )
		icanvas = New Canvas(image)	
		px = x
		py = y
		totalwidth = w
		makehouse(w,isshop)
		Local opx:Int=px
		Local opy:Int=py
		px=bw
		py=bh
		bufferdraw(icanvas)
		px = opx
		py = opy-bh
		icanvas.Flush()
	End Method
	Method makehouse(w:Int,isshop:Bool)



		' Make the base house blocks
		For Local i:Int=0 Until w
			houselayer[i] = blockhouse
		Next
		' Create the items at the side of the houses
		If Rnd(10)<5
			' add to which side(s)
			Local sides:String="left"			
			If Rnd(10)<3 Then sides="right" 
			If Rnd(10)<3 Then sides="both"
			' Add items to side(s)
			If sides="left" Or sides="both" Then 
				housesidelayer[0] = blocktoiletleft
				If Rnd(10)<3 Then 
					housesidelayer[0] = blockcrateleft
				End If
				If Rnd(10)<3 Then
					housesidelayer[0] = blockiceboxleft
				End If	
			Endif				
			If sides="right" Or sides="both" Then 
				housesidelayer[1] = blocktoiletright
				If Rnd(10)<3 Then 
					housesidelayer[1] = blockcrateright
				End If
				If Rnd(10)<3 Then
					housesidelayer[1] = blockiceboxright
				End If	
			Endif				
		End If
		'Create the crates at the front of the house
		For Local i:Int= 0 Until (w*2)-2
			If Rnd(10)<2 Then
				frontlayer[i] = blockfrontcrate
			End If

		Next
		'Create windows
		Select w
			Case 2
				windowlayer[0] = blocksmallwindow
			Case 3
				windowlayer[0] = blockwidewindow
		End Select
		' create door
		Select w
			Case 1
				doorlayer[0] = blockdoor
				If isshop Then shopsignlayer[0] = blockshopsign
			Case 2
				doorlayer[1] = blockdoor
				If isshop Then shopsignlayer[1] = blockshopsign				
			Case 3
				doorlayer[2] = blockdoor
				If isshop Then shopsignlayer[2] = blockshopsign
		End Select
		' rooftop
		Select w
			Case 1
				rooftoplayer[0] = blockrooftop
			Case 2
				rooftoplayer[0] = blockrooftop
				rooftoplayer[1] = blockrooftop
			Case 3
				rooftoplayer[0] = blockrooftop
				rooftoplayer[1] = blockrooftop
				rooftoplayer[2] = blockrooftop
		End Select
		' chimney
		Select w
			Case 1
				chimneylayer[0] = blockchimney
			Case 2
				chimneylayer[Rnd(0,2)] = blockchimney
			Case 3
				chimneylayer[Rnd(0,3)] = blockchimney
		End Select
	
	End Method
	Method bufferdraw(canvas:Canvas)
		canvas.Clear(New Color(0,0,0,0))
		' Draw the house blocks
		For Local i:Int=0 Until 3	
			If houselayer[i] = blockhouse Then
				canvas.Color = New Color((1.0/255.0)*150,(1.0/255.0)*140,(1.0/255.0)*150)
				canvas.DrawRect(px+(i*bw),py,bw+1,bh)

				canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*200,(1.0/255.0)*200)
				canvas.DrawRect( px+(i*bw),py,bw,bh)
				'SetColor 230,230,230
				'shadow top
				canvas.Color = New Color((1.0/255.0)*60,(1.0/255.0)*60,(1.0/255.0)*60)
				canvas.DrawRect( px+(i*bw),py,bw,bh/15)
				'shadow bottom
				canvas.Color = New Color((1.0/255.0)*150,(1.0/255.0)*150,(1.0/255.0)*150)
				canvas.DrawRect( px+(i*bw),py+bh/1.1,bw,bh/8)
				'highlight left
				If i=0 
					canvas.Color = New Color((1.0/255.0)*220,(1.0/255.0)*220,(1.0/255.0)*220)
					canvas.DrawRect( px+(i*bw),py,1,bh/3)
				Endif
			End If
		Next
		' Draw the rooftop
		For Local i:Int=0 Until 3	
			If rooftoplayer[i] = blockrooftop Then
				'SetColor 200,100,100
				canvas.Color = New Color((1.0/255.0)*170,(1.0/255.0)*70,(1.0/255.0)*60)
				canvas.DrawRect( px+(i*bw),py-(bh/1.5),bw,bh-(bh/3))
				' Bottom shade
				canvas.Color = New Color((1.0/255.0)*130,(1.0/255.0)*50,(1.0/255.0)*30)
				'SetColor 200,100,100
				canvas.DrawRect( px+(i*bw),py-(bh/8),bw,bh/8)
				' top shade
				canvas.Color = New Color((1.0/255.0)*190,(1.0/255.0)*90,(1.0/255.0)*80)
				canvas.DrawRect( px+(i*bw),py-(bh/1.5),bw,1)
				' top shade
				If i=0
				'horizontal
				canvas.Color = New Color((1.0/255.0)*220,(1.0/255.0)*120,(1.0/255.0)*110)
				canvas.DrawRect( px+(i*bw),py-(bh/1.5),bw/2,1)
				'vertical
				canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*100,(1.0/255.0)*100)
				canvas.DrawRect( px+(i*bw),py-(bh/1.5),1,bh/3)
				End If
			End If
		Next

		' Draw the chimney
		For Local i:Int=0 Until 3	
			If chimneylayer[i] = blockchimney Then
				canvas.Color = New Color((1.0/255.0)*100,(1.0/255.0)*100,(1.0/255.0)*100)
				canvas.DrawRect( px+(i*bw)+(bw/4),py-(bh/1.2),bw/2.5,bh/4)
				'chimney highlight
				canvas.Color = New Color((1.0/255.0)*140,(1.0/255.0)*130,(1.0/255.0)*120)
				canvas.DrawRect( px+(i*bw)+(bw/4),py-(bh/1.2),bw/6,1)

			End If
		Next		
		'Draw the windows
		For Local i:Int=0 Until 3
			If windowlayer[i] = blocksmallwindow
				canvas.Color = New Color((1.0/255.0)*0,(1.0/255.0)*100,(1.0/255.0)*200)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh/5),bw-(bw/3),bh-(bh/2.5))
				' light bottom
				canvas.Color = New Color((1.0/255.0)*0,(1.0/255.0)*115,(1.0/255.0)*210)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh/2),bw-(bw/3),(bh/3.3))
				' dark bottom
				canvas.Color = New Color((1.0/255.0)*180,(1.0/255.0)*125,(1.0/255.0)*20)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh*.7),bw-(bw/3),(bh/8.3))

			End If
			If windowlayer[i] = blockwidewindow
				canvas.Color = New Color((1.0/255.0)*0,(1.0/255.0)*100,(1.0/255.0)*200)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh/5),(bw*2)-(bw/3),bh-(bh/2.5))
				'light bottom
				canvas.Color = New Color((1.0/255.0)*0,(1.0/255.0)*115,(1.0/255.0)*210)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh/2),(bw*2)-(bw/3),(bh/3.3))
				'dark  bottom
				canvas.Color = New Color((1.0/255.0)*180,(1.0/255.0)*125,(1.0/255.0)*20)
				canvas.DrawRect( px+(i*bw)+(bw/3),py+(bh*.7),(bw*2)-(bw/3),(bh/8.3))

			End If
		Next
		' Draw the door
		For Local i:Int=0 Until 3
			If doorlayer[i] = blockdoor
				canvas.Color = New Color((1.0/255.0)*100,(1.0/255.0)*50,(1.0/255.0)*50)
				If shopsignlayer[i] = blockshopsign
					canvas.Color = New Color((1.0/255.0)*250,(1.0/255.0)*200,(1.0/255.0)*50)
				End If
				canvas.DrawRect( px+(i*bw)+(bw/5),py+(bh/5),bw-(bw/2),bh-(bh/4))
				' doorknob
				canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*210,(1.0/255.0)*210)
				canvas.DrawRect( px+(i*bw)+(bw/2),py+(bh/1.7),(bw/9),(bh/9))
				'numberplate
				canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*250,(1.0/255.0)*250)
				canvas.DrawRect( px+(i*bw)+(bw/1.3),py+(bh/3),(bw/9),(bh/9))
				canvas.Color = New Color((1.0/255.0)*10,(1.0/255.0)*50,(1.0/255.0)*50)
				canvas.DrawRect( px+(i*bw)+(bw/1.25),py+(bh/2.8),(bw/18),(bh/14))

			End If
		Next
		' Draw the sides
		If housesidelayer[0] = blocktoiletleft Then drawtoilet(canvas,px,py,bw,bh,"left")
		If housesidelayer[1] = blocktoiletright Then drawtoilet(canvas,px,py,bw,bh,"right")
		If housesidelayer[0] = blockcrateleft Then drawsidecrate(canvas,px,py,bw,bh,"left")
		If housesidelayer[1] = blockcrateright Then drawsidecrate(canvas,px,py,bw,bh,"right")
		If housesidelayer[0] = blockiceboxleft Then drawsideicebox(canvas,px,py,bw,bh,"left")
		If housesidelayer[1] = blockiceboxright Then drawsideicebox(canvas,px,py,bw,bh,"right")
		
		'Draw the crates  at the front of the house
		For Local i:Int=0 Until (totalwidth*2)-2
			If frontlayer[i] = blockfrontcrate
				canvas.Color = New Color((1.0/255.0)*100,(1.0/255.0)*50,(1.0/255.0)*50)
				canvas.DrawRect( px+((bw/2)*i),py+bh/1.2,bw/4,bh/6.4)
			End If
		Next
		
		'Draw the shop sign
		For Local i:Int=0 Until totalwidth
			If shopsignlayer[i] = blockshopsign
				canvas.Color = New Color((1.0/255.0)*255,(1.0/255.0)*40,(1.0/255.0)*30)
				Local x:Int=px+(bw*i)-bw/8
				Local y:Int=py-bh/5
				canvas.DrawRect( x,y,bw*1.2,bh/3)
				canvas.Color = New Color((1.0/255.0)*255,(1.0/255.0)*255,(1.0/255.0)*255)
				'DrawText "Shop X",x+5,y+5
				canvas.DrawRect( x+bh/10,y+bh/12,4,4)
			End If
		Next
	End Method
	Method drawtoilet(canvas:Canvas,x:Int,y:Int,w:Int,h:Int,side:String)
		If side = "left"
		Local ltx:Float=x-w/2
		Local lty:Float=y+(h/4)
		Local rtx:Float=ltx+(w/2)
		Local rty:Float=lty
		Local lbx:Float=ltx
		Local lby:Float=lty+(h-h/4)
		Local rbx:Float=ltx+(w/2)
		Local rby:Float=lby

		Local toil:Float[] = New Float[8]
		toil[0] = ltx
		toil[1] = lty-(h/6)
		toil[2] = rtx
		toil[3] = rty
		toil[4] = rbx
		toil[5] = rby
		toil[6] = lbx
		toil[7] = lby
		
		canvas.Color = New Color( (1.0/255.0)*150,(1.0/255.0)*50,(1.0/255.0)*50 )
		canvas.DrawPoly(toil)
		
		'canvas.DrawRect( x-w/2,y+10,w/2,h-10
		Elseif side="right"
		Local ltx:Float=(x)+(totalwidth*w)
		Local lty:Float=y+(h/4)
		Local rtx:Float=ltx+(w/2)
		Local rty:Float=lty
		Local rbx:Float=ltx+(w/2)
		Local rby:Float=rty+(h-h/4)
		Local lbx:Float=ltx
		Local lby:Float=rby
		canvas.Color = New Color((1.0/255.0)*150,(1.0/255.0)*50,(1.0/255.0)*50)
		Local box:Float[] = New Float[8]
		box[0] = ltx
		box[1] = lty
		box[2] = rtx
		box[3] = rty-(h/6)
		box[4] = rbx
		box[5] = rby
		box[6] = lbx
		box[7] = lby
		canvas.DrawPoly(box)

'		SetColor 100,50,50
'		canvas.DrawRect( (x)+totalwidth*w,y+10,w/2,h-10
		End If
	End Method
	Method drawsidecrate(canvas:Canvas,x:Int,y:Int,w:Int,h:Int,side:String)
		If side = "left"
		' pipe
		canvas.Color = New Color((1.0/255.0)*120,(1.0/255.0)*120,(1.0/255.0)*120)
		canvas.DrawRect( x-w/8,y,w/8,h)
		'barrel
		canvas.Color = New Color((1.0/255.0)*100,(1.0/255.0)*50,(1.0/255.0)*50)
		canvas.DrawRect( x-w/3,y+(h/1.5),w/3,h-(h/1.5))
		Elseif side="right"
		'pipe
		canvas.Color = New Color((1.0/255.0)*120,(1.0/255.0)*120,(1.0/255.0)*120)
		canvas.DrawRect( (x)+totalwidth*w,y,w/8,h)
		'barrel
		canvas.Color = New Color((1.0/255.0)*100,(1.0/255.0)*50,(1.0/255.0)*50)
		canvas.DrawRect( (x)+totalwidth*w,y+(h/1.5),w/3,h-(h/1.5))
		End If
	End Method
	Method drawsideicebox(canvas:Canvas,x:Int,y:Int,w:Int,h:Int,side:String)
		If side = "left"
		Local ltx:Float=x-w/2
		Local lty:Float=y+(h/1.5)
		Local rtx:Float=ltx+(w/2)
		Local rty:Float=lty
		Local lbx:Float=ltx
		Local lby:Float=lty+(h-h/1.5)
		Local rbx:Float=ltx+(w/2)
		Local rby:Float=lby
		canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*200,(1.0/255.0)*200)
		Local box:Float[] = New Float[8]
		box[0] = ltx
		box[1] = lty+(h/6)
		box[2] = rtx
		box[3] = rty
		box[4] = rbx
		box[5] = rby
		box[6] = lbx
		box[7] = lby
		'canvas.DrawRect( ltx,lty,w/2,h-(h/1.5)
		canvas.DrawPoly(box)
		Elseif side="right"
		Local ltx:Float=(x)+(totalwidth*w)
		Local lty:Float=y+(h/1.5)
		Local rtx:Float=ltx+(w/2)
		Local rty:Float=lty
		Local rbx:Float=ltx+(w/2)
		Local rby:Float=rty+(h-h/1.5)
		Local lbx:Float=ltx
		Local lby:Float=rby
		canvas.Color = New Color((1.0/255.0)*200,(1.0/255.0)*200,(1.0/255.0)*200)
		Local box:Float[] = New Float[8]
		box[0] = ltx
		box[1] = lty
		box[2] = rtx
		box[3] = rty+h/6
		box[4] = rbx
		box[5] = rby
		box[6] = lbx
		box[7] = lby
		canvas.DrawPoly(box)
		'canvas.DrawRect( (x)+totalwidth*w,y+(h/1.5),w/2,h-(h/1.5)
		End If
	End Method
	Method draw(canvas:Canvas,x:Int,y:Int)	
		canvas.Color = Color.White
		canvas.DrawImage(image,x,y)
	End Method
End Class

'
' The player inventory
''
Class inventory
	Field px:Int,py:Int
	Field pw:Int,ph:Int
	
	Method New()
		pw = 450
		ph = 240
		px = (screenwidth/2)-(pw/2)
		py = (screenheight/2)-(ph/2)		
	End Method
	Method update()
		If Keyboard.KeyReleased(Key.I) Or Keyboard.KeyReleased(Key.Escape)
			gamestate = "play"
			Return
		End If
		
	End Method
	Method draw(canvas:Canvas)
		canvas.Clear(Color.Black)
		canvas.OutlineMode=OutlineMode.Solid
		canvas.OutlineColor = Color.White
		canvas.OutlineWidth = 1	
		'Draw the main window
		canvas.Color = Color.Grey
		canvas.DrawRect(px,py,pw,ph)
		canvas.OutlineMode=OutlineMode.None
		'Draw the items and their count
		Local cnt:Int=0
		For Local y:Int=0 Until 15
		For Local x:Int=0 Until 2
			If cnt>=myplayer.playeritemnames.Length Then Continue
			Local x2:Int=(x*(pw/2))+px
			Local y2:Int=y*20+py
			canvas.Color = Color.White
			canvas.DrawText(myplayer.playeritem[cnt,1],x2,y2)
			canvas.DrawText(myplayer.playeritemnames[myplayer.playeritem[cnt,0]],x2+48,y2)
			cnt+=1
		Next
		Next
		canvas.DrawText("Press I or escape to return to game",px+(pw/2),py+ph-20,.5,.5)
	End method
End Class
'
' Drop a number from a x,y position
' 
Class numberfall
	Field px:Float,py:Float
	Field number:Int
	Field col:Color
	Field mx:Float
	Field my:Float
	Field time:Int ' if 0 then remove
	Field deleteme:Bool
	Method New(x:Int,y:Int,number:Int,col:Color)
		Self.px = x
		Self.py = y
		Self.number = number
		Self.col = col
		Self.time = 80
		mx = Rnd(-1,1)
		my = -2
	End Method
	Method update()
		my += .17
		px += mx
		py += my
		time-=1
		If time<=0 Then deleteme = True
	End Method
End Class
'
' These are the walking monsters that
' hatch from the eggs. They do not lay eggs
' themselfs but guard the other nearby eggs.
'
Class walkingmonster
	Field px:float,py:Float 'pixel position (0-width)
	Field sx:Float,sy:Float 'movement speed
	Field x:Int,y:Int 'tile x and y position
	Field w:Float,h:Float
	Field hp:Int 'hitpoints
	Field hpmax:Int
	Field deleteme:Bool
	Field state:String
	Field substate:String
	Field jx:Float
	Field jy:Float
	Field oldpy:Float 'old py coordinate
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.w = tilewidth
		Self.h = tileheight
		px = x*w
		py = y*h
		hp = Rnd(10,30)
		hpmax = hp
		'set the movement speed
		sx = Rnd(0.3,3)
'		sy = sx
		state="hatched"
	End Method
	Method update()		
'		If laserwait>0 Then laserwait-=1
	
		' Damage to player
		If developmode = False
		If distance(myplayer.px+(myplayer.pw/2),myplayer.py+(myplayer.ph/2),px+(w/2),py+(h/2)) < tilewidth
			myplayer.hp -= 2
			mynumberfall.Add(New numberfall(myplayer.px+(myplayer.pw/2),myplayer.py,2,Color.Red))
			If myplayer.hp < 0 Then gamestate = "select"
		End If
		End If
		
		If state<>"attack"
			'If Rnd(10)<1 Print Millisecs() + "sx : " + sx
			If px < x*w Then px += sx
			If px > x*w Then px -= sx
	'		If py < y*h Then py += sy
	'		If py > y*h Then py -= sy
			If laserwall() Then changedirection()
			If distance(px,py,x*w,y*h) > 8 Then Return
		Else
			If substate = "jump"
			If mymap.mapcollide(px+jx,py,w,h) = False
				px += jx
				Else
				'substate = "finishjump"				
			End If
			If mymap.mapcollide(px,py+jy,w,h-1) = False
				py += jy
				Else
				x = myplayer.px / tilewidth
				y = myplayer.py / tileheight
				substate = "finishjump"
				Return
			End If
			jy += .1
			x = px / tilewidth
			y = py / tileheight
			End If
		End If
		Select state
			Case "hatched"
				state="roam"
				substate="left"
			Case "attack"
				Select substate
					Case "setjump"
						If myplayer.py < py Then substate="finishjump"
						If myplayer.py > py+3 Then substate="finishjump"
						Local d:Int=distance(myplayer.px,myplayer.py,px,py)
						If px < myplayer.px Then jx = d/35 Else jx = -d/35
						
						If distance(px,py,myplayer.px,myplayer.py) > 50 Then jy = -2
						substate = "jump"
						Return
					Case "jump"
'						
						Local cnt:Int=0
						For Local ppy:Int=0 Until 40
							If mymap.mapcollide(px+(jx*10),py+ppy,w,h) = False Then cnt+=1
						Next
						If cnt>30 Then jx=-jx
					Case "finishjump"
						state = "roam"
						x = px / tilewidth
						y = py / tileheight
						If Rnd(2)< 1 Then substate = "left" Else substate="right"						
				End Select					
			Case "roam"								
				If canattackplayer() Then state="attack" ; substate="setjump"
				Select substate
					Case "left"
						x-=1
						'If Rnd(50) < 1 And mymap.mapfinal[x-1,y] = mymap.tileempty And mymap.mapfinal[x-1,y+1] <> mymap.tileempty Then substate="right"						
						'If Rnd(50) < 1 And cannotgohere(x+1,y) = False And cannotgohere(x+1,y+1)=True Then substate="right" 
						If cannotgohere(x-1,y) = True Then substate = "right"
						If cannotgohere(x-1,y+1) = False Then substate = "right"
						'If mymap.mapfinal[x-1,y]  <> mymap.tileempty Then substate="right"
						'If mymap.mapfinal[x-1,y+1] = mymap.tileempty Then substate="right"
						If x<3 Then substate="right"
						
					Case "right"						
						x+=1
						'If Rnd(50) < 1 And cannotgohere(x-1,y) =  False And cannotgohere(x-1,y+1)=True Then substate="left"
						If cannotgohere(x+1,y) = True Then substate="left"
						If cannotgohere(x+1,y+1) = False Then substate="left"
						'If Rnd(50) < 1 And mymap.mapfinal[x+1,y] = mymap.tileempty And mymap.mapfinal[x+1,y+1] <> mymap.tileempty Then substate="left"						
						'If mymap.mapfinal[x+1,y]  <> mymap.tileempty Then substate="left"
						'If mymap.mapfinal[x+1,y+1] = mymap.tileempty Then substate="left"
						If x>mapwidth-3 Then substate="left"
				End Select
				'gorandleftorright()
		End Select
	End Method
	Method canattackplayer:Bool()
		If distance(px,py,myplayer.px,myplayer.py) > 150 Then Return False
		If myplayer.px < px
			For Local xx:Int=px/tilewidth Until px/tilewidth-3 Step -1
				If mymap.mapfinal[xx,y+1] <> mymap.tilesolid Then Return False
			Next
		Else
			For Local xx:Int=px/tilewidth Until px/tilewidth+3
				If mymap.mapfinal[xx,y+1] <> mymap.tilesolid Then Return False
			Next			
		End if
		Local angle:Float = getangle(px,py,myplayer.px,myplayer.py)
		Local clearpath:Bool=False
		Local mx:Float = Cos(angle)
		Local my:Float = Sin(angle)
		Local monx:Float = px
		Local mony:Float = py
		For Local i:Int=0 Until 200
			monx += mx
			mony += my
			If distance(monx,mony,myplayer.px,myplayer.py) < 20 Then Return True
			If mymap.mapcollide(monx,mony,w/2,h/2) = True Then Return False	
			If collidelaserwall(monx,mony,w,h) Then Return False
		Next					
		Return True
	End Method	
	' for the walking monster Check if tile on map is blocked
	Method cannotgohere:Bool(x:Int,y:Int)
		If mymap.mapfinal[x,y] = mymap.tilesolid Then Return True
		If mymap.mapfinal[x,y] = mymap.tilemineable Then Return True
		If mymap.mapfinal[x,y] = mymap.tileturret Then Return True
		Return False
	End Method
	Method laserwall:Bool()
		For Local i:=Eachin mylaserwall
			If rectsoverlap((px-w)+(Rnd(-w,w)),py-h,w*2,h*2,i.tx-5,i.ty,10,i.by-i.ty)
				Return True
			End If 
		Next
		Return False
	End Method
	Method collidelaserwall:Bool(x:Int,y:Int,w1:Int,h1:Int)
		For Local i:=Eachin mylaserwall
			If rectsoverlap((x-w1)+(Rnd(-w1,w1)),y-h1,w1*2,h1*2,i.tx-5,i.ty,10,i.by-i.ty)
				Return True
			End If 
		Next
		Return False
	End Method	
	Method changedirection()
		state = "roam"
		If substate = "left" Then 
			substate="right" 
			x += 2		
		Else 
			substate="left"
			x -= 2
		End If
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
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function  	     
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function	
	Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	 Function
End Class

Class gradienttile
	Field image:Image[] = New Image[17]
	
	Field icanvas:Canvas[] = New Canvas[17]
	Field width:Int,height:Int
	Field tile:Color[][][]
	Method New(w:Int,h:Int)
		Self.width = w
		Self.height = h
		tile = New Color[width][][]
        For Local i:Int = 0 Until width
            tile[i] = New Color[height][]
            For Local z:Int=0 Until height
                tile[i][z] = New Color[17]
            Next
        Next
        For Local i:Int=0 Until 17
	        
		image[i]=New Image( tilewidth,tileheight)',TextureFlags.FilterMipmap)'|TextureFlags.Dynamic )
		image[i].Handle=New Vec2f( 0,0 )
		icanvas[i]=New Canvas( image[i] )        	
		Next

	End Method	
	Method generate()
		Local mc:Color
		Local r:Float=1,g:Float=1,b:Float=1
		For Local n:Int=0 Until 17
			For Local y:Int=0 Until height
				mc = New Color(r,g,b)
				tile[0][y][n] = mc
				r-=1/(17*Float(height))
				g-=1/(17*Float(height))
				b-=.3/(17*Float(height))
			Next
		Next
	End Method
	Method create()
		For Local i:=0 Until 17
			draw(icanvas[i],i,0,0,1,1)
			icanvas[i].Flush()
		Next
	End Method
	' Draw the tile at x and y position and tw=size
	Method draw(canvas:Canvas,thetile:Int,sx:Int,sy:Int,tw:Int,th:Int)
		Local x:Int
		Local y:Int
		
		canvas.Clear(Color.Black)
		For y=0 Until height
		'For x=0 Until width		
			Local t:Color
			t = tile[x][y][thetile]
			Local x2:Int=0
			Local y2:Int=y*th			
			y2+=sy
			canvas.Color = t			
			canvas.DrawRect(x2,y2,width,th)			
		'Next
		Next
	
	End Method
End Class

'
' This is the tile class.
' Here a stone tile is created
' using the generate method
Class tile
	Field image:Image[,] = New Image[5,5]
	
	Field icanvas:Canvas[,] = New Canvas[5,5]

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

		' Set up the buildings and trees
        For Local ii:Int=0 Until 3
        For Local i:Int=0 Until 4
	        
			image[i,ii]=New Image( tilewidth,tileheight)',TextureFlags.FilterMipmap)'|TextureFlags.Dynamic )
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
		For Local i:=0 Until 4
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
			If t=100 Then canvas.Color = New Color(.2,.2,.2).Blend(col,.5) 'dark shade color
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



Class laserwall
	' bottom x and y and top x and y
	Field bx:Float,by:Float
	Field tx:Float,ty:Float
	Field deleteme:Bool
	Method New(x:Int,y:Int)
		If toclosetoother(x,y) Then Return
		bx = x
		by = getbottomtile(x,y)
		tx = x
		ty = gettoptile(x,y-10)		
	End Method
	
	Method update()
		Return
		' Make flying enemies turn into other direction
		' if close by
		For Local i:=Eachin myflyingmonster
			'If i.laserwait<>0 Then Continue
			Local mx:Int
			If i.substate="right" Then mx=5 Else mx = -5
			If rectsoverlap(i.px-i.w+mx,i.py-i.h,i.w*3,i.h*3,tx-20,ty,40,(by-ty))
			'i.laserwait=160
			If i.substate="right" 
				i.substate="left" 
				i.x-=1
				i.px -= 6
			Else 
				i.substate="right"
				i.x+=1
				i.px += 6
				
			End If
			
			Endif
		Next
	End Method
	Method draw(canvas:Canvas)
		Local dx:Float=Float(screenwidth)/Float(mapwidth)
		Local dy:Float=Float(screenheight)/Float(mapheight)
	    Local x1:Float=Float(tx/tilewidth)*dx
    	Local y1:Float=Float(ty/tileheight)*dy
	    Local x2:Float=Float(bx/tilewidth)*dx
	    Local y2:Float=Float(by/tileheight)*dy
    	Local h:Float=y2-y1
    	
		canvas.Color = Color.Yellow
    	'SetColor 255,0,0		
		canvas.DrawRect(x1+1,y1+1,3,h)

	End Method	
	' Return true if new laserwall is to close to
	' existing laser wall
	Method toclosetoother:Bool(x:Int,y:Int)
		For Local i:=Eachin mylaserwall
			If distance(x,y,i.tx,i.ty) < tilewidth*4 Then Return True
			If distance(x,y,i.bx,i.by) < tilewidth*4 Then Return True
		Next
		Return False
	End Method
	
	' Get the y position of bottom of the first tile above
	Method getbottomtile:Int(x:Int,y:Int)
		Local y2:Int=y				
		Repeat
			If mymap.mapcollide(x,y2,2,2) Then Return y2
			y2+=1
		Forever
		Return y
	End Method
	
	'Get the y position of the top of the first tile below
	Method gettoptile:Int(x:Int,y:Int)
		Local y2:Int=y				
		Repeat
			If mymap.mapcollide(x,y2,2,2) Then Return y2
			y2-=1
		Forever
		Return y
	End Method
	Method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	 Method	
    Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Function	
End Class
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
				'check collision with walkingmonster
				For Local i:=Eachin mywalkingmonster
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
					mynumberfall.Add(New numberfall(myplayer.px+(myplayer.pw/2),myplayer.py,10,Color.Red))
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
		Self.mx = Rnd(-2,2)
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
			addtoplayerinventory()	
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
			If mx > 0 Then mx-=.01
			If mx < 0 Then mx+=.01
			If mx<0.1 And mx>0 Then mx=0
			If mx>-0.1 And mx<0 Then mx=0
						
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
	Method addtoplayerinventory()
		For Local i:Int=0 Until myplayer.playeritemnames.Length
			If kind = myplayer.playeritemnames[i]
				myplayer.playeritem[i,1] += 1
				Return
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
		
		'Collision with mineable tiles
		If mymap.mapmineablecollide(px-4,py-4,w+8,h+8,True,"frag")
			deleteme = True
		End	if
		
		'Collision with the slime
		If mygrowslime.slimecollide(px-2,py-2,w+4,h+4,True)
			deleteme = True
			'Print Millisecs()
		End If
		
		
		'bouncy vertical
		If mymap.mapcollide(px,py+2,1,h) Then 			
			my = -my*.8'+Rnd(-.1,.1)
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
		'bounc ceiling
		If mymap.mapcollide(px,py-2,1,h) Then 			
			'slimed=slimecollide(px,py+2,1,h)
			'If slimed = True Then Return
			my = -my*.8
			Local cnt:Int=0
			While mymap.mapcollide(px,py-2,1,h)
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
			mx = -mx*.8'+Rnd(-.1,.1)
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


		' frag collision with walking monsters
		For Local i:=Eachin mywalkingmonster
			If distance(i.px,i.py,px,py) < 10
				i.hp -= 5
				mynumberfall.Add(New numberfall(i.px+(i.w/2),i.py,5,Color.Red))
				If i.hp<=0
					i.deleteme = True
					myitem.Add(New item(i.px,i.py,"Monster Tail"))
				End If
				deleteme = True
				Return
			End If
		Next
		
		' frag collision with flying monsters
		For Local i:=Eachin myflyingmonster
			If distance(i.px,i.py,px,py) < 10
				i.hp -= 5
				mynumberfall.Add(New numberfall(i.px+(i.w/2),i.py,5,Color.Red))
				If i.hp<=0
					i.deleteme = True
					myitem.Add(New item(i.px,i.py,"Monster Tooth"))
				End If
				deleteme = True
				Return
			End If
		Next		
		' frag collision with the eggs
		If eggcollide(px-1,py-1,w+2,h+2)
			deleteme = True
			myitem.Add(New item(px,py,"Egg Shell"))
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
			' destroy egg
			If Rnd(3)<1 Then 
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
				my = -my*.8
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
				my = -my*.8'-.1,.1)
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
				mx = -mx*.8'+Rnd(-.1,.1)
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
		If mymap.mapcollide2(px,py,w,h) Then deleteme = True
	
		' Collision with a mineable tile
		If mymap.mapmineablecollide(px-2,py-2,w+4,h+4,True,"gun")
			deleteme = True
			Return
		End If		
		' Collision with the slime
		If mygrowslime.slimecollide(px-2,py-2,w+4,h+4,True)
			deleteme = True
			Return
			'Print Millisecs()
		End If		
		
		' Collision with bullet and walking monster
		For Local i:=Eachin mywalkingmonster
			If distance(px,py,i.px,i.py) < tilewidth Then 
				i.hp -= 1
				'mynumberfall.Add(New numberfall(i.px+(i.w/2),i.py,1,Color.Red))
				deleteme = True				
				If i.hp <= 0
					i.deleteme = True					
					myitem.Add(New item(px,py,"Monster Tail"))
					Return
				End if
				Return
			End If
		Next
		
		' Collision with bullet and flying monster
		For Local i:=Eachin myflyingmonster
			If distance(px,py,i.px,i.py) < tilewidth Then 
				i.hp -= 1
				mynumberfall.Add(New numberfall(i.px+(i.w/2),i.py,1,Color.Red))
				deleteme = True				
				If i.hp <= 0
					i.deleteme = True					
					myitem.Add(New item(px,py,"Monster Tooth"))
					Return
				End if
				Return
			End If
		Next
		
		' Collision with bullet and egg
		If eggcollide(px,py,w,h) Then 						
			deleteme = True
			myitem.Add(New item(px,py,"Egg Shell"))
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
		For Local i:=Eachin mywalkingmonster			
			If distance(mapx,mapy,i.x,i.y) > 15 Then Continue
			'if distance is close by
			If clearshot(mapx*tw,mapy*th,getangle(mapx*tw,mapy*th,i.x*tw,i.y*th)+Rnd(-.2,.2))
				mybullet.AddLast(New bullet(mapx*tw,mapy*th,getangle(mapx*tw,mapy*th,i.x*tw,i.y*th)+Rnd(-.2,.2),"town","turret"))
			Endif
		Next

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
			If mymap.mapcollide2(x,y,3,3) Then Return False
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
		tw = tilewidth/2'mymap.tw * 2
		th = tileheight/2'mymap.th * 2+2
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
	Method remove(x:Int,y:Int)		
		map[x,y] = mymap.tileempty
		Local rem:Bool=False
		Local tmpx:Stack<Int> = New Stack<Int>
		Local tmpy:Stack<Int> = New Stack<Int>
		For Local i:Int=0 Until openx.Length
			If openx.Get(i) = x And openy.Get(i) = y
				'map[x,y] = mymap.tileempty
				rem = True
			Else
				tmpx.Push(x)
				tmpy.Push(y)
			End If
		Next
		If rem = False Then Return
		openx.Clear()
		openy.Clear()
		For Local i:Int=0 Until tmpx.Length
			openx.Push(tmpx.Get(i))
			openy.Push(tmpy.Get(i))
		Next
	End Method
	Method update(speed:String)
		Local freq:Int
		If speed = "slow" Then freq = 120 Else freq = 20
		
		'every now And then check if we can restore growth
		If Rnd(1500) < 2 Then
			For Local y:Int=0 Until mymap.mmw*2
			For Local x:Int=0 Until mymap.mmh*2
				If mygrowslime.map[x,y] = mymap.tileslime					
					For Local i:Int=0 Until openx.Length
						If openx.Get(i) = x And openy.Get(i) = y Then Continue
					Next					
					Local cnt:Int=0
					For Local y2:Int=y-1 To y+1
					For Local x2:Int=x-1 To x+1
						If mygrowslime.map[x2,y2] = mymap.tileempty
							cnt+=1
						End If
					Next
					Next
					If cnt<9 Then 
						addslime(x,y)
					End If					
				End if
			Next
			Next
		End If
		
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
			' grab walking monster
			If Rnd(300) < 2
				For Local i2:=Eachin mywalkingmonster
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
		
		' Remove open slime where no slimetiles are underneath
		tx = New Stack<Int>
		ty = New Stack<Int>
		For Local i:Int=0 Until openx.Length
			If map[openx.Get(i),openy.Get(i)] = slimetile Then
				tx.Push(openx.Get(i))
				ty.Push(openy.Get(i))
				Else
			End if
		Next
		openx = New Stack<Int>
		openy = New Stack<Int>
		For Local i:Int=0 Until tx.Length
			openx.Push(tx.Get(i))
			openy.Push(ty.Get(i))
		Next

	End Method
	Method slimecollide:Bool(x:Int,y:Int,w:Int,h:Int,remove:Bool)
		If remove = True And Rnd(20) > 2 Then remove=False
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
'
'		If lefttopx < 0 Or lefttopx >= mmw Then Return True
'		If lefttopy < 0 Or lefttopy >= mmh Then Return True
'		If righttopx < 0 Or righttopx >= mmw Then Return True
'		If righttopy < 0 Or righttopy >= mmh Then Return True
'		If leftbottomx < 0 Or leftbottomx >= mmw Then Return True
'		If leftbottomy < 0 Or leftbottomy >= mmh Then Return True
'		If rightbottomx < 0 Or rightbottomx >= mmw Then Return True
'		If rightbottomy < 0 Or rightbottomy >= mmh Then Return True
'	
For Local y2:Int=0 To 1
For Local x2:Int=0 To 1
		If mygrowslime.map[lefttopx*2+x2,lefttopy*2+y2] = mymap.tileslime Then 			
			If remove = True Then 				
				removeslime(lefttopx*2+x2,lefttopy*2+y2)
			End If
			Return True
		End if
		If mygrowslime.map[righttopx*2+x2,righttopy*2+y2] = mymap.tileslime Then 			
			If remove = True Then 
				removeslime(righttopx*2+x2,righttopy*2+y2)
			End If
			Return True
		End if
		If mygrowslime.map[leftbottomx*2+x2,leftbottomy*2+y2] = mymap.tileslime Then 			
			If remove = True Then 
				removeslime(leftbottomx*2+x2,leftbottomy*2+y2)
			End If
			Return True
		End if
		If mygrowslime.map[rightbottomx*2+x2,rightbottomy*2+y2] = mymap.tileslime Then 			
			If remove = True Then 
				removeslime(rightbottomx*2+x2,rightbottomy*2+y2)
			End If
			Return True						
		End If
	Next
	Next
		Return False
	End Method	
	Method removeslime(x:Int,y:Int)
		For Local y2:Int=y-1 To y+1
		For Local x2:Int=x-1 To x+1
			mygrowslime.remove(x2,y2)
		Next
		Next
	End Method

	Method addslime(sx:Int,sy:Int)
		If mymap.mapcollide((sx/2)*tilewidth,(sy/2)*tileheight,tilewidth/2,tileheight/2) Then Return
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
	Field hpmax:Int=100
	Field playeritemnames:String[] = New String[]("Gold","Coal","Metal","Rock","Shotgun Round","Grenade","Sticky Grenade","Monster Tail","Monster Tooth","Egg Shell")
	Field playeritem:Int[,]
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
		playeritem = New Int[playeritemnames.Length,2]
		createrandominventory()
	End Method 
	Method createrandominventory()
		For Local i:Int=0 Until playeritemnames.Length
			playeritem[i,0] = i
			playeritem[i,1] = Rnd(65)
		Next
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

		If Keyboard.KeyReleased(Key.L)
			mylaserwall.Add(New laserwall(px,py+ph))
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
		Local item:String
		Local num:Int=Rnd(10)
		If num>=8 Then item="Gold" 
		If num<8 Then item="Coal" Else item="Rock"		
		myitem.Add(New item(x2+Rnd(-tw/3,th/3),y2+Rnd(th/3,th/3),item))
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
		'canvas.BlendMode = BlendMode.Opaque
		For local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=(x*tw)+mox
			Local y3:Int=(y*th)+moy
			If x2<0 Or x2>=mapwidth Or y2<0 Or y2>=mapheight Then Continue				
			
			If y2<17 Then
				canvas.Color = Color.White
				canvas.DrawImage(mygradienttile.image[y2],x3,y3)
			End If
			
			Select mymap.mapfinal[x2,y2]
				Case mymap.tileempty
				If y2>16
					canvas.Color = Color.White
					canvas.DrawImage(mytile.image[mymap.maptilevariation[x2,y2],0],x3,y3)
				End if
				'canvas.Color = Color.Brown
				'canvas.DrawRect(x3,y3,tw,th)
				Case mymap.tilesolid
					If y2>16
					canvas.Color = Color.White
					canvas.DrawImage(mytile.image[mymap.maptilevariation[x2,y2],1],x3,y3)
					End If
'				canvas.Color = Color.Black
'				canvas.DrawRect(x3,y3,tw,th)
				Case mymap.tileegg
				canvas.OutlineMode=OutlineMode.Solid
				canvas.OutlineColor = Color.White
				canvas.OutlineWidth = 1						
				canvas.Color = Color.Yellow
				canvas.DrawRect(x3,y3,tw,th)
				canvas.OutlineMode=OutlineMode.None
				Case mymap.tileturret
				canvas.OutlineMode=OutlineMode.Solid
				canvas.OutlineColor = Color.Black
				canvas.OutlineWidth = 1						
				canvas.Color = Color.Grey
				canvas.DrawRect(x3,y3,tw,th)	
				canvas.OutlineMode=OutlineMode.None
				Case mymap.tilemineable
					canvas.Color = Color.White
					canvas.DrawImage(mytile.image[mymap.maptilevariation[x2,y2],2],x3,y3)
'				canvas.Color = Color.Brown.Blend(Color.Yellow,.2)
'				canvas.DrawRect(x3,y3,tw,th)
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


		'
		''Draw the trees
		'
		canvas.Color = Color.White		
		For Local i:=Eachin mytree
			'If Rnd(100)<10 Then Print Millisecs()
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			'i.draw(canvas,x2,y2)
			canvas.DrawImage(i.image,x2,y2)
			'canvas.Color = i.col
			'canvas.DrawText(i.number,x2,y2)
		Next
				
		'
		''Draw the buildings
		'
		canvas.Color = Color.White
		For Local i:=Eachin mybuilding
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			i.draw(canvas,x2,y2)
			'canvas.Color = i.col
			'canvas.DrawText(i.number,x2,y2)
		Next

		'draw towns people
		For Local i:=Eachin mytownperson
			Local x1:Int=i.px
			Local y1:Int=i.py
			Local x2:Int=(x1-(mcx*tw))+mox
			Local y2:Int=(y1-(mcy*th))+moy
			canvas.OutlineMode=OutlineMode.Solid
			canvas.OutlineColor = Color.Black
			canvas.OutlineWidth = 1				
			canvas.Color = Color.Green
			canvas.DrawRect(x2,y2,tw,th)
			canvas.OutlineMode = OutlineMode.None
			drawpowerbar(canvas,x2,y2,i.hp,i.hpmax)
			'canvas.Color = Color.White
			'canvas.DrawText(i.state,x2,y2)
			'canvas.DrawText(i.substate,x2,y2+12)
			'canvas.DrawText(i.x*i.w+","+i.y*i.h,x2,y2+22)
			'canvas.DrawText(i.px+","+i.py,x2,y2+37)
			
			
			
		Next

		' Draw the player
		pmx = (px-(mcx*tw))+mox
		pmy = (py-(mcy*th))+moy
		canvas.Color = Color.White
		canvas.DrawRect(pmx,pmy,pw,ph)
		drawpowerbar(canvas,pmx,pmy,hp,hpmax)

		'draw flying monsters		
		For Local i:=Eachin myflyingmonster
			Local x1:Int=i.px
			Local y1:Int=i.py
			Local x2:Int=(x1-(mcx*tw))+mox
			Local y2:Int=(y1-(mcy*th))+moy
			canvas.Color = Color.Red
			canvas.DrawRect(x2,y2,tw,th)
			drawpowerbar(canvas,x2,y2,i.hp,i.hpmax)
			'canvas.Color = Color.White
			'canvas.DrawText(i.state,x2,y2)
			'canvas.DrawText(i.substate,x2,y2+12)
			'canvas.DrawText(i.x*i.w+","+i.y*i.h,x2,y2+22)
			'canvas.DrawText(i.px+","+i.py,x2,y2+37)
			
			
			
		Next

		'draw walking monsters		
		For Local i:=Eachin mywalkingmonster
			Local x1:Int=i.px
			Local y1:Int=i.py
			Local x2:Int=(x1-(mcx*tw))+mox
			Local y2:Int=(y1-(mcy*th))+moy
			canvas.Color = Color.Red
			canvas.DrawRect(x2,y2,tw,th)
			drawpowerbar(canvas,x2,y2,i.hp,i.hpmax)			
			canvas.Color = Color.White
			canvas.DrawText(i.state,x2,y2)
			canvas.DrawText(i.substate,x2,y2+12)
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
		
		'
		' Draw the laser walls
		
		For Local i:=Eachin mylaserwall
			Local x2:Int=i.tx-mcx*tw+mox
			Local y2:Int=i.ty-mcy*th+moy
			Local h:Int=i.by-i.ty
			canvas.Color = Color.Yellow
			canvas.DrawRect(x2-2,y2,4,h)
			canvas.Color = Color.Red
			canvas.DrawRect(x2-4,y2,8,4)
			canvas.DrawRect(x2-4,y2+h-4,8,4)
		Next

		'
		' Draw the falling numbers
		'
		For Local i:=Eachin mynumberfall
			Local x2:Int=i.px-mcx*tw+mox
			Local y2:Int=i.py-mcy*th+moy
			canvas.Color = i.col
			canvas.DrawText(i.number,x2,y2)
		Next
		
		

		
	End Method
	' Powerbar method)
	Method drawpowerbar(canvas:Canvas,x:Int,y:Int,hp:Float,hpmax:Float)
		Local powerbarlen:Float=20
		Local cpos:Float=(powerbarlen/hpmax)*hp
		canvas.Color = Color.Black
		canvas.DrawRect(x,y,powerbarlen,5)
		If hp >= hpmax/2
			canvas.Color = Color.Green
		Elseif hp<hpmax/2 And hp>hpmax/4
			canvas.Color = Color.Yellow
		Else
			canvas.Color = Color.Red
		Endif
		canvas.DrawRect(x+1,y+1,cpos,3)
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
	Field hpmax:Int
	Field deleteme:Bool
'	Field dbx:Int,dby:Int
'	Field dbtime:Int
'	Field laserwait:Int
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
		hpmax = hp
		'set the movement speed
		sx = Rnd(0.3,3)
		sy = sx
		state="hatched"
	End Method
	Method update()		
'		If laserwait>0 Then laserwait-=1
		' Damage to player
		If developmode = False
		If distance(myplayer.px+(myplayer.pw/2),myplayer.py+(myplayer.ph/2),px+(w/2),py+(h/2)) < tilewidth
			myplayer.hp -= 2
			mynumberfall.Add(New numberfall(myplayer.px+(myplayer.pw/2),myplayer.py,2,Color.Red))
			If myplayer.hp < 0 Then gamestate = "select"
		End If
		End If

		
		If px < x*w Then px += sx
		If px > x*w Then px -= sx
		If py < y*h Then py += sy
		If py > y*h Then py -= sy
		If laserwall() Then changedirection()
		If distance(px,py,x*w,y*h) > 8 Then Return
		Select state
			Case "hatched"
				state="takeoff"
'				ty=3 'move distance
			Case "takeoff"
				takeoff()
			Case "attack"
				If canattackplayer() = False Then state = "roam" ; substate="up"; Return
				'Local angle:Float = getangle(px,py,myplayer.px,myplayer.py)
				
				x = myplayer.px / tilewidth
				y = myplayer.py / tileheight
			Case "roam"								
				
				If canattackplayer() Then state = "attack"
				
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
				If mymap.mapfinal[x,y] = mymap.tileempty And mymap.mapfinal[x,y+1] <> mymap.tileegg Then				
				If distance(myplayer.px,myplayer.py,px,py) < 100 Then 
				Else
					mymap.mapfinal[x,y] = 3
					mymap.updateimage(mymap.mapcanvas)				
				End If
				Else
				
				End If
				state="takeoff"
		End Select
	End Method
	Method canattackplayer:Bool()
		If distance(px,py,myplayer.px,myplayer.py) > 200 Then Return False
		Local angle:Float = getangle(px,py,myplayer.px,myplayer.py)
		Local clearpath:Bool=False
		Local mx:Float = Cos(angle)
		Local my:Float = Sin(angle)
		Local monx:Float = px
		Local mony:Float = py
		For Local i:Int=0 Until 200
			monx += mx
			mony += my
			If distance(monx,mony,myplayer.px,myplayer.py) < 20 Then Return True
			If mymap.mapcollide(monx,mony,w,h) = True Then Return False	
			If collidelaserwall(monx,mony,w,h) Then Return False
		Next					
		Return True
	End Method
	Method collidelaserwall:Bool(x:Int,y:Int,w1:Int,h1:Int)
		For Local i:=Eachin mylaserwall
			If rectsoverlap((x-w1)+(Rnd(-w1,w1)),y-h1,w1*2,h1*2,i.tx-5,i.ty,10,i.by-i.ty)
				Return True
			End If 
		Next
		Return False
	End Method
	Method laserwall:Bool()
		For Local i:=Eachin mylaserwall
			If rectsoverlap((px-w)+(Rnd(-w,w)),py-h,w*2,h*2,i.tx-5,i.ty,10,i.by-i.ty)
				Return True
			End If 
		Next
		Return False
	End Method
	Method changedirection()
		state = "roam"
		If substate = "left" Then 
			substate="right" 
			x += 2		
		Else 
			substate="left"
			x -= 2
		End If
	End Method
	Method landandlayegg()
		' Sometimes land and lay egg
		If Rnd() < (egglayingfreq/10)
			' Debug - So monster will not lay egg in player
			
			Local exitloop:Bool=False
			Local y1:Int=y
			Local egghere:Bool=False
			While exitloop = False
				If mymap.mapfinal[x,y1] = 3 Then 
					Return
				End If
				If mymap.mapladder[x,y1] = 1
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
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function     	
	Method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	 Method	    
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
	Field maptilevariation:= New Int[1,1]
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
		maptilevariation = New Int[mapwidth,mapheight]
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			maptilevariation[x,y] = Rnd(4)
		Next
		Next
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
				Case tilesolid
				canvas.Color = Color.Black
				Case tileempty
				canvas.Color = Color.White
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case tileegg			
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
				Case tilesolid
				'canvas.Alpha = 1
				canvas.Color = Color.Brown
				canvas.DrawRect(x*tw,y*th,tw,th)
				'Case tilesolid
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
	Method mapmineablecollide:Bool(x:Int,y:Int,w:Int,h:Int,remove:Bool,kind:String)
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
		
		If mymap.mapfinal[lefttopx,lefttopy] = mymap.tilemineable Then 
			If remove=True
				removemineable(lefttopx,lefttopy,kind)
			End If
			Return True
		End If
		If mymap.mapfinal[righttopx,righttopy] = mymap.tilemineable Then 
			If remove=True
				removemineable(righttopx,righttopy,kind)
			End If
			Return True
		End if
		If mymap.mapfinal[leftbottomx,leftbottomy] = mymap.tilemineable Then 
			If remove=True
				removemineable(leftbottomx,leftbottomy,kind)
			End If
			Return True
		End If
		If mymap.mapfinal[rightbottomx,rightbottomy] = mymap.tilemineable Then 
			If remove=True
				removemineable(rightbottomx,rightbottomy,kind)
			End If
			Return True						
		End If
		Return False
	End Method	

	' Every now and then remove mineable tile
	' and add item
	'
	Method removemineable(x:Int,y:Int,kind:String)
		Local chance:Int=10
		If kind="gun" Then chance=50 
		If kind="frag" Then chance = 10
		If Rnd(chance) < 2 Then
			mymap.mapfinal[x,y] = mymap.tileempty
			myitem.Add(New item((x*tilewidth)+tilewidth/2,(y*tileheight)+tileheight/2,"gold"))
		End If
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
	' Collide with solid and mineable
	Method mapcollide2:Bool(x:Int,y:Int,w:Int,h:Int)
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
		
		If mapfinal[lefttopx,lefttopy] = mymap.tilesolid Then Return True
		If mapfinal[righttopx,righttopy] = mymap.tilesolid Then Return True
		If mapfinal[leftbottomx,leftbottomy] = mymap.tilesolid Then Return True
		If mapfinal[rightbottomx,rightbottomy] = mymap.tilesolid Then Return True						

		If mapfinal[lefttopx,lefttopy] = mymap.tilemineable Then Return True
		If mapfinal[righttopx,righttopy] = mymap.tilemineable Then Return True
		If mapfinal[leftbottomx,leftbottomy] = mymap.tilemineable Then Return True
		If mapfinal[rightbottomx,rightbottomy] = mymap.tilemineable Then Return True						

		Return False
	End Method	

End Class


Global mymenuselect:menuselect
Global mymap:map
Global mygrowslime:growslime
Global mytentacle:List<tentacle> = New List<tentacle>
Global mywatermap:watermap
Global myflyingmonster:List<theflyingmonster> = New List<theflyingmonster>
Global mywalkingmonster:List<walkingmonster> = New List<walkingmonster>
Global myturret:List<turret> = New List<turret>
Global mybullet:List<bullet> = New List<bullet>
Global mygrenade:List<grenade> = New List<grenade>
Global myfrag:List<frag> = New List<frag>
Global myplayer:player
Global myinventory:inventory
Global myitem:List<item> = New List<item>
Global mylaserwall:List<laserwall> = New List<laserwall>
Global mynumberfall:List<numberfall> = New List<numberfall>
Global mytile:tile
Global mygradienttile:gradienttile
Global mybuilding:List<building> = New List<building>
Global mytree:List<tree> = New List<tree>
Global mytownperson:List<townperson> = New List<townperson>

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
		If gamestate="inventory"
			myinventory.update()			
			myinventory.draw(canvas)
		End If
		If gamestate<>"play" Then Return
		If Keyboard.KeyReleased(Key.Key1) Then
			resetmap(screenwidth,screenheight)
		End If
		If Keyboard.KeyReleased(Key.Home) Then
			gamestate="select"
		End If  
		
		' update the flying monsters
		For Local i:=Eachin myflyingmonster
			i.update()
		Next
		For Local i:=Eachin myflyingmonster
			If i.deleteme = True Then myflyingmonster.Remove(i)
		Next

		' update the walking monsters
		For Local i:=Eachin mywalkingmonster
			i.update()
		Next
		For Local i:=Eachin mywalkingmonster
			If i.deleteme = True Then mywalkingmonster.Remove(i)
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
		
		' Update the grenades
		For Local i:=Eachin mygrenade
			i.update()
		Next
		For Local i:=Eachin mygrenade
			If i.deleteme = True Then mygrenade.Remove(i)
		Next

		' Update the fragments (from grenades)
		For Local i:=Eachin myfrag
			i.update()
		Next
		For Local i:=Eachin myfrag
			If i.deleteme = True Then myfrag.Remove(i)
		Next

		' Update the items (drops)
		For Local i:=Eachin myitem
			i.update()
		Next
		For Local i:=Eachin myitem
			If i.deleteme = True Then myitem.Remove(i)
		Next
						
		' Update the laser walls
		For Local i:=Eachin mylaserwall
			i.update()
		Next
		For Local i:=Eachin mylaserwall
			If i.deleteme = True Then mylaserwall.Remove(i)
		Next
		
		' update the numbers (falling damage)
		For Local i:=Eachin mynumberfall
			i.update()
		Next
		For Local i:=Eachin mynumberfall
			If i.deleteme = True Then mynumberfall.Remove(i)
		Next

		' update the towns people
		For Local i:=Eachin mytownperson
			i.update()
		Next
		For Local i:=Eachin mytownperson
			If i.deleteme = True Then mytownperson.Remove(i)
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
		If Keyboard.KeyReleased(Key.I)
			gamestate = "inventory"
		End If
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
			For Local i:=Eachin mywalkingmonster
				i.draw(canvas)
			Next

			For Local i:=Eachin mylaserwall
				i.draw(canvas)
			Next

			canvas.Color = New Color(255,255,255,0.5)
			Local x1:Int=myplayer.mcx*mymap.tw
			Local y1:Int=myplayer.mcy*mymap.th
			canvas.DrawRect(x1,y1,mymap.tw*myplayer.maptileswidth,mymap.th*myplayer.maptilesheight)
		End If
		addflyingmonster()
		addwalkingmonster()
		'
		canvas.Scissor = New Recti(0,0,screenwidth,screenheight)
		canvas.Color = Color.White
		Local fps:String=App.FPS
		canvas.DrawText(fps.Left(2)+"  Press 1(new level) or Home(selection). Left shift(map view) I(Inventory)",0,0)
		canvas.DrawText("Cursors(move), s(shotgun), g(grenade), m(mine) space(jump) l(laserwall)..",0,15)
		canvas.DrawText(theversion,0,Height-20)	
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

'
' This function adds a walking monster to the game
'
Function addwalkingmonster() 'hatch
	Local cnt:Int=0
	For Local i:=Eachin mywalkingmonster
		cnt+=1
	Next
	Local cnt2:Int=0
	For Local i:=Eachin myflyingmonster
		cnt2+=1
	Next
	
	' If there are not to many walking monsters
	' and still some egg laying monsters left
	If cnt<maxwalkingmonsters And cnt2>0
		'DebugLog (mapwidth+mapheight)/10
		For Local i:=0 Until (mapwidth+mapheight)/10
			If Rnd() < egghatchspeed
				Local x:Int=Rnd(mapwidth)
				Local y:Int=Rnd(mapheight)
				If mymap.mapfinal[x,y] = mymap.tileegg
					' If there are no walking monsters nearby
					Local makemonster:Bool=True
					For Local ii:= Eachin mywalkingmonster
						If distance(x,y,ii.x,ii.y) < 6 Then makemonster = False
					Next					
					If makemonster = True
						mymap.mapfinal[x,y] = mymap.tileempty
						mywalkingmonster.AddLast(New walkingmonster(x,y))
						mymap.updateimage(mymap.mapcanvas)
					End if
				End If
			End If
		Next
	End If
End Function


'
' This function adds a flying monster to the game
'
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
				If mymap.mapfinal[x,y] = mymap.tileegg
					mymap.mapfinal[x,y] = mymap.tileempty
					myflyingmonster.AddLast(New theflyingmonster(x,y))
					mymap.updateimage(mymap.mapcanvas)
				End If
			End If
		Next
	End If
End Function

Function resetmap(Width:Int,Height:int)
		myflyingmonster.Clear()
		mywalkingmonster.Clear()
		myturret.Clear()
		myitem.Clear()
		mybullet.Clear()
		myfrag.Clear()
		mygrenade.Clear()		
		mybuilding.Clear()
		mytree.Clear()
		mytownperson.Clear()
		SeedRnd(100+Microsecs())
		'Local s:Int=Rnd(140,150)
		'mapwidth = 
		'mapheight = s
		screenwidth = Width
		screenheight = Height
		mymap = New map(Width,Height,mapwidth,mapheight)
		
		mytile = New tile(tilewidth,tileheight)
		mytile.generate(3)
		mytile.create()
		mygradienttile = New gradienttile(tilewidth,tileheight)
		mygradienttile.generate()
		mygradienttile.create()

				
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
		myinventory = New inventory()
		
		'
		' Create the buildings and the trees
		'
		If developmode = False Then
			'
			' Create the buildings
			'
			Local shopmade:Bool=False
			Local x:Int=2 
			While x<(mapwidth/2)-12
				Local makeshop:Bool
				If Rnd(10) < 2 And shopmade = False Then makeshop = True ; shopmade=True
				Local st:Int=Rnd(12,24)
				mybuilding.Add(New building(x*tilewidth,tileheight*15,Rnd(1,4),tilewidth*3,tileheight*2,makeshop))
				mytree.Add(New tree(x*tilewidth-(tilewidth),tileheight*14,48,60))
				x+=st
			Wend		
			x=(mapwidth/2)+5
			While x<(mapwidth-12)
				Local makeshop:Bool
				If Rnd(10) < 5 And shopmade = False Then makeshop = True ; shopmade=True
				If shopmade = False And x>(mapwidth/2)+(mapwidth/4) Then makeshop=True;shopmade=True
				Local st:Int=Rnd(12,24)
				mybuilding.Add(New building(x*tilewidth,tileheight*15,Rnd(1,4),tilewidth*3,tileheight*2,makeshop))
				mytree.Add(New tree(x*tilewidth-(tilewidth),tileheight*14,48,60))
				x+=st
			Wend				
		End If		
		
		'
		' Create the towns people
		'
		For Local i:Int=0 Until mapwidth/40
			mytownperson.Add(New townperson(Rnd(3,mapwidth/2-5),16))
			mytownperson.Add(New townperson(Rnd(mapwidth/2+5,mapwidth-5),16))
		Next
		
		
		myitem.Add(New item(100,100,"Gold"))
		myitem.Add(New item(106,105,"Gold"))
		myitem.Add(New item(110,115,"Gold"))
		myitem.Add(New item(115,120,"Gold"))


		'mygrowslime.addslime(10,30)
		'For Local i:Int=0 Until 10
		'	myflyingmonster.Add(New theflyingmonster(5,5))
	 	'Next
	 	'mywalkingmonster.Add(New walkingmonster(5,16))
	 	'mywalkingmonster.Add(New walkingmonster(15,16))
	 	'mywalkingmonster.Add(New walkingmonster(16,16))
	 	'mynumberfall.Add(New numberfall(myplayer.px,myplayer.py,10,Color.Red))
End Function 

Function distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
	Return Abs(x2-x1)+Abs(y2-y1)
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
