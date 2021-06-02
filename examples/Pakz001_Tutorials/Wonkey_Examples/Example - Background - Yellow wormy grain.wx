#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class background
	Field sw:float,sh:Float
	Field mw:Float,mh:Float
	Field tw:Float,th:Float
	Field map:Color[,]
	method New(sw:int,sh:int,width:Int,height:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = width
		Self.mh = height
		tw = sw/mw
		th = sh/mh
		map = New Color[width,height]
		'drawclineto(50,50,70,30,.5,Color.White)
		For Local i:=0 Until mw*mh/10
			Local x1:Int=Rnd(mw)
			Local y1:Int=Rnd(mh)
			Local rgb:Float=Rnd()
			Local col:Color = New Color(rgb,rgb,0)
			Local x2:Int=x1+Rnd(-10,10)						
			Local y2:Int=y1+Rnd(-10,10)
			drawclineto(x1,y1,x2,y2,.5,col)
		Next
		For Local i:=0 Until mw*mh
			Local cnt:Int
			Local x1:Int=Rnd(mw)
			Local y1:Int=Rnd(mh)
			For Local y2:=-1 To 1
			For Local x2:=-1 To 1
				Local x3:Int=x1+x2
				Local y3:Int=y1+y2
				If x3>0 And x3<mw And y3>0 And y3<mh
					If map[x3,y3].r >.7 Then 					
					cnt+=1
					Elseif map[x3,y3].g>.7 
					cnt+=1
					Elseif map[x3,y3].b>.7 
					cnt+=1
					End If
				End If
			Next
			Next			
			If cnt>5 Then map[x1,y1] = Color.White
		Next
	End Method
	Method drawclinetofadeout(x1:Int,y1:Int,x2:Int,y2:Int,freq:Float,color:Color)
		Local dist:Int = distance(x1,y1,x2,y2)
		Local fout:Float=1.0/distance(x1,y1,x2,y2)
		Local exitloop:Bool=False
		Local ld:Float ' loop depth
		While exitloop=False
			If ld<dist Then ld+=1			
			If x1=x2 And y1=y2 Then exitloop=True			
			If Rnd()<.5
			If x1>x2 Then x1-=1
			If x1<x2 Then x1+=1
			If y1>y2 Then y1-=1
			If y1<y2 Then y1+=1
			End If
			If x1>0 And x1<mw And y1>0 And y1<mh				
				Local c:Float=1.0-(fout*ld)
				map[x1,y1] = tintcolor(New Color(c,c,c),color)
			End If
			If Rnd()<freq Then x1+=1
			If Rnd()<freq Then x1-=1
			If Rnd()<freq Then y1+=1
			If Rnd()<freq Then y1-=1
			If x1>0 And x1<mw And y1>0 And y1<mh
				Local c:Float=1.0-(fout*ld)
				map[x1,y1] = tintcolor(New Color(c,c,c),color)
			End If
		Wend
	End Method
	Method drawclineto(x1:Int,y1:Int,x2:Int,y2:Int,freq:Float,color:Color)
		Local lx:Stack<Int> = New Stack<Int>
		Local ly:Stack<Int> = New Stack<Int>
		Local exitloop:Bool=False
		While exitloop=False
			If x1=x2 And y1=y2 Then exitloop=True			
			If Rnd()<.5
			If x1>x2 Then x1-=1
			If x1<x2 Then x1+=1
			If y1>y2 Then y1-=1
			If y1<y2 Then y1+=1
			End If
			If x1>0 And x1<mw And y1>0 And y1<mh
				map[x1,y1] = color
				lx.Push(x1)
				ly.Push(y1)
			End If
			If Rnd()<freq Then x1+=1
			If Rnd()<freq Then x1-=1
			If Rnd()<freq Then y1+=1
			If Rnd()<freq Then y1-=1
			If x1>0 And x1<mw And y1>0 And y1<mh
				map[x1,y1] = color
				lx.Push(x1)
				ly.Push(y1)
			End If
		Wend
		For Local i:=0 Until lx.Length
			For Local x2:=-1 To 1
			For Local y2:=-1 To 1 
			Local x:Int=lx.Get(i)+x2
			Local y:Int=ly.Get(i)+y2
			If x>0 And x<mw And y>0 And y<mh
			If map[x,y] <> color
				map[x,y] = New Color(color.r/2,color.g/2,color.b/2)
			End If
			Endif
			Next
			Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			canvas.Color = map[x,y]
			canvas.DrawRect(x*tw,y*th,tw,th)
		Next
		Next
	End Method
	Method tintcolor:Color(col1:Color,col2:Color)
		Local r:Float,g:Float,b:Float
		r = col1.r/2+col2.r/2
		g = col1.g/2+col2.g/2
		b = col1.b/2+col2.b/2		
		Return New Color(r,g,b)
	End Method
    Method distance:int(x1:Int,y1:Int,x2:Int,y2:Int)
        Return Abs(x2-x1)+Abs(y2-y1)
    End Method	
End Class

Global mybg:background

Class MyWindow Extends Window
	Field time:Int
	Field n:Int=0
	Method New()
		mybg = New background(Width,Height,Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		canvas.Clear(Color.Black)
		mybg.draw(canvas)
		canvas.Scale(2,2)
		canvas.Color = Color.Black
		canvas.DrawRect(0,Height/4-20,Width/2,40)
		canvas.Color = Color.White
		canvas.DrawText("Background Image",Width/4,Height/4,.5,.5)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
