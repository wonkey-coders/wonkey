#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field gi:Image
	Field gic:Canvas
	Field tmpim:=New Image[20]
	Field treemap:Int[,] = New Int[20,20]
	Method New()
				
		SeedRnd(Microsecs())
		For Local y:Int=0 Until 20
			tmpim[y] = New Image(32,32)
			tmpim[y] = createtree()
		Next
		' make the treemap
		For Local i:Int=0 To 10
			treemap[Rnd(20),Rnd(20)] = 1
		Next
		'grow
		For Local i:Int=0 Until 900
			Local x:Int=Rnd(1,19)
			Local y:Int=Rnd(1,19)
			If treemap[x,y] > 0 Then treemap[x+Rnd(-1,2),y+Rnd(-1,2)] = Rnd(20)
		Next
		
		'make the ground image
		gi = New Image(32,32)
		gic = New Canvas(gi)
		gic.Clear(Color.Green.Blend(Color.Black,.8))
		gic.Flush()
		For Local i:Int=0 Until 25
			Local x1:Float=Rnd(32)
			Local y1:Float=Rnd(32)
			Local a:Float=Rnd(TwoPi)
			For Local z:Int=0 Until 3
				x1+=Cos(a)
				y1+=Sin(a)
				If x1<0 Or y1<0 Or x1>=32 Or y1>=32 Then Continue
				gic.Color = Color.Green.Blend(Color.Black,Rnd(.5,1))
				gic.DrawPoint(x1,y1)
			Next
		Next
		gic.Flush()
	End method
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
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Green.Blend(Color.Black,.5))
		canvas.Color = Color.White
		'canvas.DrawImage(tmpim[0],100,100,0,4,4)
		For Local y:Int=0 Until 20
		For Local x:Int=0 Until 20
			canvas.DrawImage(gi,x*32,y*32)
			If treemap[x,y]>0 Then canvas.DrawImage(tmpim[treemap[x,y]],x*32,y*32,0,.9,.9)
			
		Next
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class
    ' Manhattan Distance (less precise)
    Function distance:Float(x1:Float,y1:Float,x2:Float,y2:Float)   
	    Return Abs(x2-x1)+Abs(y2-y1)   
    End Function
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function    
Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
