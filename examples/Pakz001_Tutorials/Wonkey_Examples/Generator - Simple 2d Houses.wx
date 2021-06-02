#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

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
	Method draw(canvas:Canvas)	
		canvas.Color = Color.White
		canvas.DrawImage(image,px,py)
	End Method
End Class



Class MyWindow Extends Window
	Field mybuilding:List<building>
	Field time:Int=Millisecs()
	Field hw:Int=48,hh:Int=64

	Method New()
		makehouses()

	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 

		If Keyboard.KeyReleased(Key.Space) Or Millisecs() > time
			time=Millisecs()+2000
			makehouses()
		End If



        canvas.Color = New Color((1.0/255.0)*50,(1.0/255.0)*155,(1.0/255.0)*255)
        canvas.DrawRect(0,0,Width,150+hh)
        canvas.Color = New Color( (1.0/255.0)*50,(1.0/255.0)*125,(1.0/255.0)*235)
        canvas.DrawRect(0,100,Width,(150+hh)-100)

        canvas.Color = New Color((1.0/255.0)*5,(1.0/255.0)*250,(1.0/255.0)*5)
        canvas.DrawRect(0,150+hh,Width,Height-(150+hh))
        canvas.Color = New Color((1.0/255.0)*125,(1.0/255.0)*250,(1.0/255.0)*125)
        canvas.DrawRect(0,150+hh,Width,2)
		
		For Local i:=Eachin mybuilding
        	i.draw(canvas)
        Next

		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
    Method makehouses()    	
    	mybuilding = New List<building>
    	hw = Rnd(20,50)
    	hh = hw
    	Local st:Int=hw*4
    	Local x:Int=0
    	While x<Width
    		
			Local z1:Bool
			If Rnd(5)<1 Then z1 = True
			Local w:Int = Rnd(1,4)
			st = hw*(w+2)
'	        mybuilding = New building(x,150,Rnd(1,4),z1)
	        mybuilding.AddLast(New building(x,150,w,hw,hh,z1))
	        x+=st
		Wend
    End Method
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
