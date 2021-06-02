#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global screenwidth:Int,screenheight:Int


Class MyWindow Extends Window
	Field im:Image
	Field can:Canvas	
	Field time:Int=0
	Method New()
		SeedRnd(Microsecs())
		screenwidth = Width ; screenheight = Height
		newtree()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
	
		canvas.Color = Color.White
		canvas.Alpha=1
		canvas.DrawImage(im,0,0)		
		
		time+=1
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.Space) Or time>120 Then newtree() ; time=0
	End Method	
	Method newtree()
		im = New Image(Width,Height)
		can = New Canvas(im)
		can.Clear(New Color(0,0,0,1))
		can.Flush()
		'Local x:Int=320,y:Int=200
		
		For Local y:Int=0 Until Height Step 100
		For Local x:Int=0 Until Width Step 100
		Local maxsize:Int=Rnd(20,40)
		brush(can,x,y,maxsize,New Color(0,.2,0),1)		
		'brush(can,x,y,40,New Color(0,.5,0),1)
		For Local i:Int=0 Until 5
'			SeedRnd(1)
			brush(can,x+Rnd(-10,10),y+Rnd(-10,10),Rnd(20,maxsize),New Color(0,Rnd(.5,1),0),.5)		
			'brush(can,x+Rnd(-10,10),y+Rnd(-10,10),Rnd(20,40),New Color(0,.2,0),.5)					
		Next
		Next
		Next
	End Method	

	Method brush(canvas:Canvas,x:Int,y:Int,r:Int,col:Color,alp:Float)		
		Local ax:Int,ay:Int,bx:Int,by:Int 'connect last two points
		Local dx:Int=x,dy:Int=y
		Local map:Int[,]
		map = New Int[r*2,r*2]
		x = r
		y = r		
		
'		canvas.Color = Color.White
'RuntimeError(r/10)
		Local cnt:Float=0,maxcnt:Int=r/10,dir:Float=Float(maxcnt)/100.0		
		Local oldx:Int=-100,oldy:Int
		ax = x+Cos(0)*(r/2)
		ay = y+Sin(0)*(r/2)
		For Local a:Float = 0 Until TwoPi Step .005
			Local x1:Float=x+Cos(a)*(r/2)
			Local y1:Float=y+Sin(a)*(r/2)
			
			'canvas.DrawPoint(x1+Cos(a)*cnt,y1+Sin(a)*cnt)
			Local sx:Int=x1+Cos(a)*cnt
			Local sy:Int=y1+Sin(a)*cnt
			bx = sx ; by = sy
			If sx<0 Or sy<0 Or sx>=r*2 Or sy>=r*2 Then 
				Print "bow"
				Continue
			End If
			' connect previous to new
			If oldx<>-100
				While Not (oldx=sx And oldy=sy)
					If oldx<sx Then oldx+=1
					If oldx>sx Then oldx-=1
					If oldy<sy Then oldy+=1
					If oldy>sy Then oldy-=1
					map[oldx,oldy] = 1
				Wend
			End If
			map[sx,sy] = 1
			oldx = sx ; oldy = sy
			cnt+=dir
			If cnt>maxcnt
				dir=-dir
				maxcnt = Rnd(r/8,r/4)
			End If
			If cnt<0 
				dir=-dir
			End If
			
			
			'leaf
			If Rnd()<.2
			Local la:Float=Rnd(TwoPi)
			Local lx:Float=sx,ly:Float=sy
			Local s:Float=3.0'Float(r)/10.0
			Local di:Float=Rnd(-.3,.3)
			For Local i:Int=0 Until 10
				lx+=Cos(la)
				ly+=Sin(la)
				s-=3.0/10.0
				la+=di*(Float(i)/2)
				For Local cx:Int=lx-s Until lx+s
				For Local cy:Int=ly-s Until ly+s
					If cx<0 Or cy<0 Or cx>=r*2 Or cy>=r*2 Then Continue
					map[cx,cy] = 1
				Next
				Next
			Next
			End If
		Next
		
		' connect last two points
		While Not (ax=bx And ay=by)
			If ax<bx Then ax+=1
			If ax>bx Then ax-=1
			If ay<by Then ay+=1
			If ay>by Then ay-=1
			map[ax,ay] = 1
		Wend
'		' Floodfill the area
		Local ox:Stack<Int> = New Stack<Int>
		Local oy:Stack<Int> = New Stack<Int>
		Local mx:Int[]=New Int[](0,1,0,-1)
		Local my:Int[]=New Int[](-1,0,1,0)
		ox.Push(r)
		oy.Push(r)
		While ox.Length
			Local ix:Int=ox.Get(0)
			Local iy:Int=oy.Get(0)
			ox.Erase(0)
			oy.Erase(0)
			For Local i:Int=0 Until mx.Length
				Local jx:Int=ix+mx[i]
				Local jy:Int=iy+my[i]
				If jx<0 Or jy<0 Or jx>=r*2 Or jy>=r*2 Then Continue
				If map[jx,jy] = 0
					map[jx,jy] = 1
					ox.Push(jx)
					oy.Push(jy)
				End If
			Next
		Wend

		canvas.Alpha = alp
		canvas.Color = Color.White.Blend(col,.9)
		
		For Local zy:Int=0 Until r*2
		For Local zx:Int=0 Until r*2
			If map[zx,zy] Then 
				canvas.DrawPoint(zx+dx,zy+dy)
			End If
		Next
		Next
		canvas.Flush()
	End Method
End	Class

Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)  
	Return Abs(x2-x1)+Abs(y2-y1)   
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
