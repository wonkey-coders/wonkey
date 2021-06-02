#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class background
	Field sw:float,sh:Float
	Field mw:Float,mh:Float
	Field tw:Float,th:Float
	Field map:Color[,]
	method New(sw:int,sh:int,width:Int,height:Int,screen:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = width
		Self.mh = height
		tw = sw/mw
		th = sh/mh
		map = New Color[width,height]
		'drawclineto(50,50,70,30,.5,Color.White)
		Select screen
			Case 0
			script1()
			Case 1
			script2()
			Case 2
			script3()
		End Select
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
			End If
			If Rnd()<freq Then x1+=1
			If Rnd()<freq Then x1-=1
			If Rnd()<freq Then y1+=1
			If Rnd()<freq Then y1-=1
			If x1>0 And x1<mw And y1>0 And y1<mh
				map[x1,y1] = color
			End If
		Wend
	End Method
	Method script1()
		For Local y:=0 Until sh Step 8
		For Local x:=0 Until sw Step 8 
			Local df:Float=Rnd(0.1,0.7)
			drawclineto(x,y,x+64,y,df,Color.White)
		Next
		Next
	End Method
	Method script2()
		For Local y:=0 Until sh Step 16
		For Local x:=0 Until sw Step 16
			Local df:Float=Rnd(0.1,0.7)
			drawclineto(x,y,x+16,y,df,Color.White)
			drawclineto(x,y,x,y+16,df,Color.White)
		Next
		Next
	End Method
	Method script3()
		For Local y:=0 Until mh Step 8	
			Local nc:Color = New Color(1,1,0)			
			If y Mod 3 = 0 Then 
			drawclinetofadeout(0,y,mw,y,.4,nc)
			Else
			drawclinetofadeout(mw,y,0,y,.4,nc)
			End If
			nc = New Color(.5,.5,0)			
			If y Mod 3 = 0 Then 
			drawclinetofadeout(0,y+2,mw,y+2,.4,nc)
			Else
			drawclinetofadeout(mw,y+2,0,y+2,.4,nc)
			End If
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
		mybg = New background(Width,Height,100,100,0)
		n+=1
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		time+=1
		If time>100 Then 
			time=0
			mybg = New background(Width,Height,100,100,n)
			n+=1
			If n>2 Then n=0
		End If
		
		canvas.Clear(Color.Black)
		mybg.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
