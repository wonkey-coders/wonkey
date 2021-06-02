' slow computers - do not run in debug mode::
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global egghatchspeed:Float = 0.1 'how fast eggs hatch
Global egglayingfreq:Float = 0.1 ' lay lots of eggs 1 lay less eggs 0 '0 to 1
Global startingeggfreq:Float = 0.2 '0 to 1 0 is none 1 is full
Global maxflyingmonsters:Int=30
Global mapwidth:Int=320
Global mapheight:Int=240
Global screenwidth:Int=640
Global screenheight:Int=480


Class player
	Field mcx:Int,mcy:Int,mpx:Int,mpy:Int ' scroll coordinates
	Field maptileswidth:Int,maptilesheight:Int
	Field tw:Int=32
	Field th:Int=32
	Method New()
		maptileswidth = screenwidth / tw
		maptilesheight = screenheight / th
		mcx=5
		mcy=5
	End Method 
	Method update()
		If Keyboard.KeyDown(Key.Right)
			mcx+=1
			If mcx+maptileswidth>mapwidth-1 Then mcx-=1
		End If 
		If Keyboard.KeyDown(Key.Left)
			mcx-=1
			If mcx<1 Then mcx+=1
		End If
		If Keyboard.KeyDown(Key.Down)
			mcy+=1
			If mcy+maptilesheight>mapheight-1 Then mcy-=1
		End If
		If Keyboard.KeyDown(Key.Up)
			mcy-=1
			If mcy<1 Then mcy+=1
		End If

	End Method
	Method draw(canvas:Canvas)
		'draw the map
		For local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=x*tw
			Local y3:Int=y*th
			If x2>0 And x2<mapwidth And y2>0 And y2<mapheight
			Select mymap.mapfinal[x2,y2]
				Case 0
				canvas.Color = Color.Brown
				canvas.DrawRect(x3,y3,tw,th)
				Case 1
				canvas.Color = Color.Black
				canvas.DrawRect(x3,y3,tw,th)
				Case 3
				canvas.Color = Color.Yellow
				canvas.DrawRect(x3,y3,tw,th)
			End Select			
			End If
		Next
		Next
		'draw water
		canvas.Color = Color.Blue
		For Local y:=0 Until maptilesheight
		For Local x:=0 Until maptileswidth
			Local x2:Int=mcx+x
			Local y2:Int=mcy+y
			Local x3:Int=x*tw
			Local y3:Int=y*th
			Select mywatermap.map[x2,y2]
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
						canvas.DrawRect(x3+tw/4,y3+th/4,tw/2,th/2)
						cont=False
					End If
					'if water below and no abow and no left and right
					If m(x2,y2,0,1) = 2
					If m(x2,y2,0,-1) = 0
					If m(x2,y2,-1,0) = 0
					If m(x2,y2,+1,0) = 0
						canvas.DrawRect(x3,y3+th/2,tw,th/2)
						cont = False
					End If 
					End If
					End If 
					End If 
					'all else
					If cont=True
						canvas.DrawRect(x3,y3,tw,th)
					End If
		End Select
		Next
		Next
		'draw monsters
		canvas.Color = Color.Red
		For Local i:=Eachin myflyingmonster
			Local x1:Int=i.x*tw
			Local y1:Int=i.y*th
			Local x2:Int=x1-(mcx*tw)
			Local y2:Int=y1-(mcy*th)
			canvas.DrawRect(x2,y2,tw,th)
			
		Next
		
	End Method
	Method m:int(x:Int,y:Int,offx:int,offy:int)
		Return mywatermap.map[x+offx,y+offy]
	End method
End Class 

Class theflyingmonster
	Field x:Int,y:Int
	Field w:Float,h:Float
	Field state:String
	Field tx:Float
	Field ty:Float
	Field substate:String
	Method New(x:Int,y:Int)
		Self.x = x
		Self.y = y
		Self.w = 3
		Self.h = 3
		state="hatched"
	End Method
	Method update()
		Select state
			Case "hatched"
				state="takeoff"
				ty=3 'move distance
			Case "takeoff"
				takeoff()
			Case "roam"				
				Select substate
					Case "left"
						x-=1
						If mymap.mapfinal[x-1,y] = 0 Then substate="right"
						If x<3 Then substate="right"
						' if flying on the ground level then move up 1 tile
						If mymap.mapfinal[x,y+1] = 0 Then y-=1
						If mymap.mapfinal[x,y-1] = 0 Then y+=1
					Case "right"
						x+=1
						If mymap.mapfinal[x+1,y] = 0 Then substate="left"
						If x>mapwidth-3 Then substate="left"
						' if flying on the ground level then move up 1 tile						
						If mymap.mapfinal[x,y+1] = 0 Then y-=1
						If mymap.mapfinal[x,y-1] = 0 Then y+=1
					Case "up"
						y-=1						
						If mymap.mapfinal[x,y-2] = 0 Then 
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
						If mymap.mapfinal[x,y+2] = 0 
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
				If mymap.mapfinal[x,y+1] = 0
					state="layegg"
				End If
			Case "layegg"
				If mymap.mapfinal[x,y] = 1 Then
				mymap.mapfinal[x,y] = 3
				mymap.updateimage(mymap.mapcanvas)				
				Else
				
				End If
				state="takeoff"
				ty=3
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
				If mymap.mapfinal[x,y1] = 0 Then exitloop = True
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
					If mymap.mapfinal[x1,y] = 0 Or x1<3
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
					If mymap.mapfinal[x1,y] = 0 Or x1>mapwidth-3
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
					If mymap.mapfinal[x,y1] = 0
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
					If mymap.mapfinal[x,y1] = 0
						exitloop = True
					Endif
				Wend
				If cnt>8 Then substate="down"
			End If
		End If	
	End Method
	Method takeoff()
		y-=1
		ty-=1
		If ty<0 Or mymap.mapfinal[x,y-1] = 0 Then 
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
		canvas.DrawRect(x1,y1,w+2,h+2)
		canvas.Color = Color.Red
    	'SetColor 255,0,0		
		canvas.DrawRect(x1+1,y1+1,w,h)

	End Method
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
	Field sw:Float,sh:Float,mmh:Float,mmw:Float
	Field map:=New Int[1,1]
	Field mapfinal:=New Int[1,1]
	Field mapladder:=New Int[1,1]
	Field mapimage:Image
	Field mapcanvas:Canvas
	Field mapladderimage:Image
	Field mapladdercanvas:Canvas
	Field mapdoor:=New Int[1,1]
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
			Local y:Int=Rnd(2,mmh-4)
			If mapfinal[x,y] = 1
			If mapfinal[x,y+1] = 0
			mapfinal[x,y] = 3
			End If
			End If
		Next		

		updateladderimage(mapladdercanvas)
		updateimage(mapcanvas)
	End Method 
	Method finalizemap()
	For Local y:=1 Until mh-1
	For Local x:=1 Until mw-1
		If map[x,y] = 1
			For Local y2:=-1 To 1
			For Local x2:=-1 To 1
				mapfinal[(x*3)+x2,(y*3)+y2] = 1				
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
			mapfinal[x,y+1] = 0
			mapfinal[x,y+2] = 0
			mapfinal[x,y+3] = 0
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
			mapfinal[x,y+1] = 0
			mapfinal[x,y+2] = 0
			mapfinal[x,y+3] = 0
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
				Case 1
				'canvas.Alpha = 0.5
				'canvas.Color = Color.None'New Color(0,0,0,.8)
				'canvas.DrawRect(x*tw,y*th,tw,th)
				Case 3			
				canvas.Alpha = 0.8	
				canvas.Color = Color.Yellow
				canvas.DrawRect(x*tw,y*th,tw,th)
			End Select						
		Next
		Next
		canvas.Flush()
	End Method 
End Class

Global mymap:map
Global mywatermap:watermap
Global myflyingmonster:List<theflyingmonster> = New List<theflyingmonster>
Global myplayer:player

Class MyWindow Extends Window
	Field time:Int
	Method New()
		Super.New("",640,480)
		Fullscreen = False
		resetmap(Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method
		If Keyboard.KeyReleased(Key.Space) Then
			resetmap(Width,Height)
		End If  
		
		For Local i:=Eachin myflyingmonster
			i.update()
		Next
		
		
		time+=1
		If time>4000
		time=0
		resetmap(Width,Height)
		End If
		mywatermap.update()
		mywatermap.addwater()		
		
		'player
		If Keyboard.KeyDown(Key.LeftShift) = False
			myplayer.update()
			canvas.Clear(Color.Black)
			myplayer.draw(canvas)
		End If
		'minimap
		If Keyboard.KeyDown(Key.LeftShift)		
			canvas.Clear(Color.Black)
			canvas.DrawImage(mymap.mapimage,0,0)		
			mywatermap.draw(canvas)				
			canvas.DrawImage(mymap.mapladderimage,0,0)		
			For Local i:=Eachin myflyingmonster
				i.draw(canvas)
			Next
		End If
		addflyingmonster()
		'
		canvas.Color = Color.White
		canvas.DrawText(App.FPS+"  Press space for new level. Left shift for map overview",0,0)
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
				End If
			End If
		Next
	End If
End Function

Function resetmap(Width:Int,Height:int)
		myflyingmonster.Clear()
		SeedRnd(100+Microsecs())
		Local s:Int=Rnd(140,241)
		mapwidth = s
		mapheight = s
		screenwidth = Width
		screenheight = Height
		mymap = New map(Width,Height,s,s)
		mywatermap = New watermap(Width,Height,s,s,s*400)
		For Local y:=0 Until s
		For Local x:=0 Until s
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
End Function 

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
