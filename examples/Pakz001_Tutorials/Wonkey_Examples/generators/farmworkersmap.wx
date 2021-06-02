#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global sw:Int=640,sh:Int=480

Class worker
	Field x:Int,y:Int
	Field w:Float,h:Float
	Field pathmap:Int[,]
	Method New(x:Int,y:Int)
		' get our tile position
		Self.x = x
		Self.y = y
		w = myfarm.tw/2
		h = myfarm.th/2 
	End Method
	Method findpathtotree()
		'find a closeby tree
		'flood the map towards it
		'set flag that worker can move
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawOval(x*myfarm.tw+myfarm.tw/5,y*myfarm.th+myfarm.th/5,w,h)
	End Method
End Class

Class farm
	Field mw:Int,mh:Int 'map width and height
	Field tw:Float,th:Float 'tile width and height
	Field housex:Int,housey:Int 'house x and y
	Field map:Int[,] ' our map
	Field tilemap:Int[,]
	Method New(w:Int,h:Int)
		'get pur map width and height
		mw = w
		mh = h
		' get our map width and height
		map = New Int[w,h]
		tilemap = New Int[w,h]
		' get our tile width and height
		tw = Float(sw) / Float(w)
		th = Float(sh) / Float(h)
		' plant our trees
		planttrees((mw*mh)/150)
		
		makeriver()
		
		placefarm()
		
		'maketilemap()	
		
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			If map[x,y] = 3
				'
				' Here we calculate which tile should be drawn at the current position.
				' This is done by reading above/right/bottom and left of the current position.
				' If above is a tile then we increate the value with 1 and right+2 bottom+4
				' and left +8. 
				Local bitwise:Int=0
				If y-1>=0 And map[x,y-1] <> 3 Then bitwise+=1
				If x+1<mw And map[x+1,y] <> 3 Then bitwise+=2
				If y+1<mh And map[x,y+1] <> 3 Then bitwise+=4
				If x-1>=0 And map[x-1,y] <> 3 Then bitwise+=8
				tilemap[x,y] = bitwise+1
			End If
			If map[x,y] = 0
				If Rnd()<.03 Then tilemap[x,y] = 100
			End If
			If map[x,y] = 3 
				If Rnd()<.12 And tilemap[x,y] = 1 Then tilemap[x,y] = 101
			End If
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:Int=0 Until mh
		For Local x:Int=0 Until mw
			Local tmp:Int=map[x,y]
			Select tmp
				Case 3 ' water
					canvas.Color = Color.Blue
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
					drawtile(canvas,tilemap[x,y],x*tw,y*th)
				Case 2 'our trees
					canvas.Color = Color.Green.Blend(Color.Brown,.5)
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
					canvas.Color = Color.Green.Blend(Color.White,.5)
					canvas.DrawTriangle(x*tw+tw/2,y*th,x*tw,y*th+th/1.4,x*tw+tw,y*th+th/1.4)										
					canvas.Color = Color.White.Blend(Color.Green,.2)
					canvas.DrawCircle(x*tw+tw/2.5,y*th+th/3,tw/8)
					canvas.Color = Color.Brown.Blend(Color.White,.2)
					canvas.DrawRect(x*tw+tw/2.6,y*th+th/1.4,tw/3,th/4)
					canvas.Color = Color.Brown.Blend(Color.Black,.8)
					canvas.DrawRect(x*tw+tw/2+tw/12,y*th+th/1.4,tw/8,th/4)
				Case 1 'our farm
					canvas.Color = Color.Brown
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
				Case 0 'our grass/sand
					canvas.Color = Color.Green.Blend(Color.Brown,.5)
					canvas.DrawRect(x*tw,y*th,tw+1,th+1)
					If tilemap[x,y] = 100 Then drawtile(canvas,100,x*tw,y*th)
			End Select			
'			If tilemap[x,y]>0
'				canvas.Color = Color.White
'				canvas.DrawText(tilemap[x,y],x*tw,y*th)
'			End If
		Next
		Next
	End Method
	
	Method drawtile(canvas:Canvas,tile:Int,x:Int,y:int)
		Select tile
			Case 2 ' above
				'above
				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+1,x+tw,y+1)		

				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+2,x+tw,y+2)				

				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y)
				Next

			Case 3 'right
				' right
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+tw-3,y,x+tw-3,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+tw-2,y,x+tw-2,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x+tw-1,tmp)
				Next
			Case 4 'above and right
				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+1,x+tw,y+1)		

				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+2,x+tw,y+2)				

				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y)
				Next

				' right
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+tw-3,y,x+tw-3,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+tw-2,y,x+tw-2,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x+tw-1,tmp)
				Next
					
			Case 5 'below is land
				'below
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+th-3,x+tw,y+th-3)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+th-2,x+tw,y+th-2)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y+th-1)
				Next
			Case 10 'above and left
				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+1,x+tw,y+1)		

				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+2,x+tw,y+2)				

				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y)
				Next
				' left
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+2,y,x+2,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+1,y,x+1,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x,tmp)
				Next
				
			Case 13 'below and left
				' below
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+th-3,x+tw,y+th-3)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+th-2,x+tw,y+th-2)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y+th-1)
				Next
				' left
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+2,y,x+2,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+1,y,x+1,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x,tmp)
				Next
			Case 7 'rigth and below
				' below
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x,y+th-3,x+tw,y+th-3)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x,y+th-2,x+tw,y+th-2)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=x Until x+tw Step 2
					canvas.DrawPoint(tmp,y+th-1)
				Next
				' Right
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+tw-3,y,x+tw-3,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+tw-2,y,x+tw-2,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x+tw-1,tmp)
				Next
								
			Case 9 'left
				' left
				canvas.Color = Color.White.Blend(Color.Grey,.5)
				canvas.DrawLine(x+2,y,x+2,y+th)				

				canvas.Color = Color.White.Blend(Color.Blue,.2)
				canvas.DrawLine(x+1,y,x+1,y+th)		
				canvas.Color = Color.Green.Blend(Color.White,.5)		
				For Local tmp:Int=y Until y+th Step 2
					canvas.DrawPoint(x,tmp)
				Next
			
			Case 100 'grass tile with a difference
				canvas.Color = Color.Green.Blend(Color.White,.15)
				For Local tmpy:Int=0 Until th Step th/1.5
				For Local tmpx:Int=0 Until tw Step tw/1.5
					canvas.DrawRect(x+tmpx,y+tmpy,3,3)
				Next
				Next
			Case 101 'water with a difference
				
				canvas.Color = Color.Blue.Blend(Color.White,.8)
				canvas.DrawPoint(x+tw/3,y)
				canvas.DrawPoint(x+tw/2,y+th/3)
				
		End Select
	End Method
	
	Method placefarm()
		Repeat
			' position the house
			housex = Rnd(4,mw-4)
			housey = Rnd(4,mh-4)
			Local failed:Bool=False
			' if the area below is trees or ground then go ahead
			For Local y:Int=housey-3 To housey+3
			For Local x:Int=housex-3 To housex+3
				If map[x,y] = 3 Then failed=True
			Next
			next
			If failed = False
				' put our farm there
				For Local y:Int=housey-3 To housey+3
				For Local x:Int=housex-3 To housex+3
					map[x,y] = 0
				Next
				Next		
				map[housex,housey] = 1
				Exit
			End If
		Forever
	End Method

	Method makeriver()
		'get a point on the map and draw 2 lines into a wavy direction until
		' they exit the map
		Local x1:Float=Rnd(5,mw-5) 'riverdirection 1
		Local y1:Float=Rnd(5,mh-5)
		Local x2:Float=x1 'riverdirection 2
		Local y2:Float=y1		
		Local angle1:Float=Rnd(TwoPi)
		Local angle2:Float=Rnd(TwoPi)
		Local riverwidth:Int=1
		'RIVER DIRECTION 1
		Repeat
			x1+=Cos(angle1)
			y1+=Sin(angle1)
			angle1+=Rnd(-.3,.3)
			If x1<0 Or y1<0 Or x1>=mw Or y1>= mh Then Exit
			' here we create the river in the map
			map[x1,y1] = 3
			' every now and then change the width of the river
			If Rnd()<.2 Then riverwidth=Rnd(1,3)
			For Local by:Int=y1-riverwidth To y1+riverwidth
			For Local bx:Int=x1-riverwidth To x1+riverwidth
				If bx>=0 And bx<mw And by>=0 And by<mh Then map[bx,by] = 3
			Next
			Next
		Forever
		'RIVER DIRECTION 2
		Repeat
			x2+=Cos(angle2)
			y2+=Sin(angle2)
			angle2+=Rnd(-.3,.3)
			If x2<0 Or y2<0 Or x2>=mw Or y2>= mh Then Exit
			' here we create the river in the map
			map[x2,y2] = 3
			' every now and then change the width of the river
			If Rnd()<.2 Then riverwidth=Rnd(1,3)
			For Local by:Int=y2-riverwidth To y2+riverwidth
			For Local bx:Int=x2-riverwidth To x2+riverwidth
				If bx>=0 And bx<mw And by>=0 And by<mh Then map[bx,by] = 3
			Next
			Next
		Forever
		
	End Method
	' this method create pathches of trees on the map. We do this
	' by creating a couple of tree lines and then growing around those.
	Method planttrees(num:Int)
		' draw some lines with trees
		For Local i:Int=0 Until num
			Local x:Float=Rnd(mw)
			Local y:Float=Rnd(mh)
			Local treegrowline:Int=Rnd(5,40)
			Local angle:Float = Rnd(TwoPi)
			For Local j:Int=0 Until treegrowline
				If x+Cos(angle)>=0 And x+Cos(angle)<mw-1 Then x+=Cos(angle)
				If y+Sin(angle)>=0 And y+Sin(angle)<mh-1 Then y+=Sin(angle)
				If Rnd()<.5 And map[x,y] = 0 Then map[x,y] = 2
			Next				
		Next
		'grow the trees 
		For Local i:Int=0 Until mw*mh
			Local x:Int=Rnd(mw)
			Local y:Int=Rnd(mh)
			If map[x,y] = 2
				If x-1>=0 And map[x-1,y] = 0 Then map[x-1,y] = 2
				If x+1<mw And map[x+1,y] = 0 Then map[x+1,y] = 2
				If y-1>=0 And map[x,y-1] = 0 Then map[x,y-1] = 2
				If y+1<mh And map[x,y+1] = 0 Then map[x,y+1] = 2
			End If
		Next
	End Method
End Class

Global myfarm:farm
Global myworker:List<worker> = New List<worker>

Class MyWindow Extends Window

	Method New()
		SeedRnd(Microsecs())
		newmap()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		myfarm.draw(canvas)
		For Local i:=Eachin myworker
			i.draw(canvas)
		Next
		
		' If press space then new map
		If Keyboard.KeyReleased(Key.Space) Then newmap()
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method newmap()
		Local s:Int=Rnd(20,60)
		myfarm = New farm(s,s)
		myworker.Clear()
		myworker.Add(New worker(myfarm.housex,myfarm.housey))
		
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
