#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' Based somewhat on http://www.squidi.net/three/entry.php?id=164

Class mapgen
	Field sw:Int,sh:Int
	Field tw:Float,th:Float
	Field mw:Int,mh:Int
	Field map:Int[,]
	Field grassmap:Int[,]
	Field bridgemap:Int[,]
	Field tileroad:Int=999
	Field numzones:Int
	Method New(sw:Int,sh:Int,mw:Int,mh:Int,numzones:Int)
		Self.numzones = numzones
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		Self.tw = Float(sw) / Float(mw)
		Self.th = Float(sh) / Float(mh)		
		map = New Int[mw,mh]
		grassmap = New Int[mw,mh]		
		bridgemap = New Int[mw,mh]
'		For Local i:Int=0 Until mw
'			map[i] = New Int[mh]
'			grassmap[i] = New Int[mh]
'			bridgemap[i] = New Int[mh]			
'		Next
		createmap()
	End Method
	Method createmap()
		'Create a number of zones (area's)
		For Local zone:Int=0 Until numzones
			map[Rnd(mw),Rnd(mh)] = zone+1
		Next
		'Grow the zones
		Local cangrow:Bool=True
		Local mx:Int[]= New Int[](0,1,0,-1)
		Local my:Int[]=New Int[](-1,0,1,0)
		While cangrow=True
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			If map[x,y] > 0
				Local tile:Int=map[x,y]
				For Local i:Int=0 Until mx.Length
					Local x2:Int=mx[i]+x
					Local y2:Int=my[i]+y
					If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
					If Rnd(10)<2 And map[x2,y2] = 0
						map[x2,y2] = tile
					End If
				Next
			End If
			' Every now and then check if every spot is taken
			If Rnd(mw)<mw/10
				cangrow = False
				For Local y2:Int=0 Until mh
				For Local x2:Int=0 Until mw
					If map[x2,y2] = 0 Then cangrow = True;Exit
				Next
				Next
			End If			
		Wend
		' Create the roads
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			Local t:Int=map[x,y]
			If x+1 < mw And map[x+1,y] <> t And grassmap[x+1,y] = 0 Then grassmap[x,y] = 1
			If y+1 < mh And map[x,y+1] <> t And grassmap[x,y+1] = 0 Then grassmap[x,y] = 1
			If x+1 < mw And y+1 < mh And map[x+1,y+1] <> t And grassmap[x+1,y+1] = 0 Then grassmap[x,y] = 1
		Next
		Next
		'create the bridges
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If grassmap[x,y] <> 1 Then Continue
			Local cnt:Int=0
			For Local y2:Int=y-1 To y+1
			For Local x2:Int=x-1 To x+1
				If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
				If map[x2,y2] >= numzones/3 Then cnt+=1
			Next
			Next
			If cnt=0 Then bridgemap[x,y] = 1
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		' map pass 1		
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If map[x,y] = 0 Then Continue			
			Local x2:Int = x*tw
			Local y2:Int = y*th
			If map[x,y] < numzones/3 Or map[x,y] = 1 Then
			' water
			canvas.Color = New Color (1.0/255.0*44,1.0/255.0*140,1.0/255.0*200)
			canvas.DrawRect(x2,y2,tw+1,th+1)
			canvas.Color = New Color(1.0/255.0*46,1.0/255.0*165,1.0/255.0*225)
			canvas.DrawOval(x2+tw/3,y2+th/5,tw/4,th/2)
			canvas.Color = New Color(1.0/255.0*56,1.0/255.0*195,1.0/255.0*255)
			canvas.DrawOval(x2+tw/3,y2+th/4,tw/5,th/7)

			Else
			'grass
			canvas.Color = New Color(1.0/255.0*160,1.0/255.0*200,1.0/255.0*105)
			canvas.DrawRect(x2,y2,tw+1,th+1)
			'treebase dark
			canvas.Color = New Color(1.0/255.0*10,1.0/255.0*45,1.0/255.0*0)
			canvas.DrawOval(x2+tw/3,y2+th/2,tw/2,th/1.5)

			'treebase light
			canvas.Color = New Color(1.0/255.0*200,1.0/255.0*55,1.0/255.0*0)
			canvas.DrawOval(x2+tw/2.2,y2+th/2,tw/4,th/1.5)
			' tree top dark			
			canvas.Color = New Color(1.0/255.0*0,1.0/255.0*55,1.0/255.0*0 )
			canvas.DrawOval(x2+tw/8,y2+th/10,tw/1.1,th/1.3)
			' tree top 
			canvas.Color = New Color(1.0/255.0*0,1.0/255.0*190,1.0/255.0*0)
			canvas.DrawOval(x2+tw/8+1,y2+th/10,tw/1.2-2,th/1.3)
			

			' highlight top 
			canvas.Color = New Color(1.0/255.0*200,1.0/255.0*255,1.0/255.0*200)
			canvas.DrawOval(x2+tw/4+1,y2+th/5,tw/3,th/3)
			
			End If

		Next
		Next
		'grass
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If grassmap[x,y] = 0 Then Continue			
			Local x2:Int = x*tw
			Local y2:Int = y*th
			canvas.Color = New Color(1.0/255.0*80,1.0/255.0*230,1.0/255.0*20)
			canvas.DrawRect(x2,y2,tw+1,th+1)
		Next
		Next

		'bridges
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If bridgemap[x,y] = 0 Then Continue			
			Local x2:Int = x*tw
			Local y2:Int = y*th
			canvas.Color = New Color(1.0/255.0*150,1.0/255.0*120,1.0/255.0*15)
			canvas.DrawRect(x2,y2,tw+1,th+1)
			'plank
			canvas.Color = New Color(1.0/255.0*200,1.0/255.0*170,1.0/255.0*20)
			canvas.DrawRect(x2+tw/10,y2,tw/3,th+1)
			canvas.DrawRect(x2+tw/1.8,y2,tw/3,th+1)
			'plank shadow and light
			canvas.Color = New Color( 1.0/255.0*240,1.0/255.0*200,1.0/255.0*200)
			canvas.DrawRect(x2+tw/10,y2,1,th+1)
			canvas.DrawRect(x2+tw/1.8,y2,1,th+1)
			canvas.Color = New Color(1.0/255.0*0,1.0/255.0*0,1.0/255.0*0)
			canvas.DrawRect(x2+tw/10+tw/3,y2,1,th+1)
			canvas.DrawRect(x2+tw/1.8+tw/3,y2,1,th+1)
		Next
		Next


		' map pass 2 (shadow under trees/grass and highlight up water)		
		For Local y:Int=1 Until mh
		For Local x:Int=0 Until mw
			If map[x,y] = 0 Then Continue			
			Local x2:Int = x*tw
			Local y2:Int = y*th
			'shadow under trees
			If grassmap[x,y] = 1 And grassmap[x,y-1] = 0 And map[x,y] > numzones/3
			canvas.Color = New Color( 1.0/255.0*40,1.0/255.0*160,1.0/255.0*30)
			canvas.DrawRect(x2+tw/4,y2,tw-th/2,th/3)
			End If
			'shadow under water
			If grassmap[x,y] = 0 And grassmap[x,y-1] = 1 And map[x,y] < numzones/3
			canvas.Color = New Color(0,0,0)
			canvas.DrawRect(x2,y2,tw+1,th/8)
			End If
		Next
		Next


	End Method
End Class

Class MyWindow Extends Window
	Field plumps:Int
	Field mymapgen:mapgen 
	Method New()
		Local s:Int=Rnd(30,100)
		If s<40 Then plumps = s/1.5 Else plumps = s*2
		mymapgen = New mapgen(Width,Height,50,50,plumps)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		If Keyboard.KeyReleased(Key.Space) Then 
			Local s:Float=Rnd(30,100)
			If Rnd(10)<8 Then s = Rnd(20,40)
			If s<40 Then plumps = s/1.5 Else plumps = s*2
			mymapgen = New mapgen(Width,Height,s,s,plumps)
		End If
		mymapgen.draw(canvas)
		
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
