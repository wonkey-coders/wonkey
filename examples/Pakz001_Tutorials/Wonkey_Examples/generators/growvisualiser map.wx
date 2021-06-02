#Import "<std>"
#Import "<mojo>"


'
'
'
'



Using std..
Using mojo..

Global w:Int=40
Global h:Int=40

Class MyWindow Extends Window
	Field ex1:Int[,]
	Field ex2:Int[,]
	Field ex1pos:Vec2i
	Field ex2pos:Vec2i
	Field tw:Int,th:Int
	Method New()
		tw = 5
		th = 5
		ex1pos.X = 50
		ex1pos.Y = 50		
		ex2pos.X = 370
		ex2pos.Y = 50
		reset()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		If Keyboard.KeyDown(Key.Key1) 
			For Local i:Int=0 Until 50
				ex1 = grow(ex1)
				ex2 = grow(ex2)
			Next
		End If
		
		editgrow()
		'
		draw(canvas,ex1,ex1pos.X,ex1pos.Y)
		draw(canvas,ex2,ex2pos.X,ex2pos.Y)
		
		canvas.Color = Color.White
		canvas.DrawText("Press and hold '1' - to grow arrays.",0,0)
		canvas.DrawText("Press 'c' - to clear arrays.",0,10)
		canvas.DrawText("Use Mouse and Left/Right Button to draw in area.",0,300)
		canvas.DrawText("Grow is done by taking a random point on the array and then",0,330)
		canvas.DrawText("increasing the value on or besides it. Colors are assigned based",0,350)
		canvas.DrawText("on low(0)..[sea].[grass].[hill].[mountain]..high(max)",0,370)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		If Keyboard.KeyReleased(Key.C) Then reset()
	End Method	
	Method editgrow()
		Local c:Int = -1
		If Mouse.ButtonDown(MouseButton.Left) Then c=1
		If Mouse.ButtonDown(MouseButton.Right) Then c=0
		If c=-1 Then Return
		
		If Mouse.X > ex1pos.X And Mouse.Y > ex1pos.Y
			Local x:Int=(Mouse.X - ex1pos.X) / tw
			Local y:Int=(Mouse.Y - ex1pos.Y) / th
			If x<w And y<h
				If c=0 Then 
					ex1[x,y] = 0
				Else
					Local hv:Int = highestval(ex1)
					If hv = 0 Then hv = 1
					ex1[x,y] = hv
				End If
			End If
		End If
		If Mouse.X > ex2pos.X And Mouse.Y > ex2pos.Y
			Local x:Int=(Mouse.X - ex2pos.X) / tw
			Local y:Int=(Mouse.Y - ex2pos.Y) / th
			If x<w And y<h
				If c=0 Then 
					ex2[x,y] = 0
				Else
					Local hv:Int=highestval(ex2)
					If hv = 0 Then hv = 1
					ex2[x,y] = hv
				End If
			End If
		End If
	End Method
	Method grow:Int[,](ar:Int[,])
		
		Local ret:Int[,] = New Int[ar.GetSize(0),ar.GetSize(1)]
		For Local y2:Int=0 Until ar.GetSize(1)
		For Local x2:Int=0 Until ar.GetSize(0)
			ret[x2,y2] = ar[x2,y2]
		Next
		Next
		Local y:Int
		Local x:Int
		While (x<1 Or y<1 Or x>=w-1 Or y>=h-1)
			x = Rnd(w)
			y = Rnd(h)
			If x<1 Or y<1 Or x>=w-1 Or y>=h-1 Then Continue
			If ar[x,y] > 0				
				ret[x+Rnd(-1,2),y+Rnd(-1,2)] += 1								
			End If
		Wend
		Return ret
	End Method
	Method draw(canvas:Canvas,ar:Int[,],x:Int,y:Int)
		canvas.Color = Color.White
		canvas.DrawRect(x-1,y-1,ar.GetSize(0)*tw+2,ar.GetSize(1)*th+2)
		Local highest:Int=highestval(ar)
		Local tv:Float=1.0/Float(highest)
		For Local y2:Int = 0 Until ar.GetSize(1)
		For Local x2:Int = 0 Until ar.GetSize(0)
			Local v:Float=ar[x2,y2]
			canvas.Color = New Color(tv*v,tv*v,tv*v)
			If v<highest/5 And v>0 Then 				
				canvas.Color = canvas.Color.Blend(Color.Green,.5)
			Elseif v<highest/4 And v>highest/5
				canvas.Color = canvas.Color.Blend(Color.Green,.9)
			Elseif v<highest/3 And v>highest/4
				canvas.Color = canvas.Color.Blend(Color.Brown,.8)
			Elseif v>highest/2
				canvas.Color = canvas.Color.Blend(Color.White,.8)
			End If
			If v=0 Then canvas.Color = Color.Blue
			canvas.DrawRect(x+x2*tw,y+y2*th,tw,th)
		Next
		Next		
	End Method
	Method reset()
		ex1 = New Int[w,h]
		ex2 = New Int[w,h]
	End Method	
	Method highestval:Int(ar:Int[,])
		Local highest:Int=0
		For Local y:Int = 0 Until ar.GetSize(1)
		For Local x:Int = 0 Until ar.GetSize(0)
			Local v:Int=ar[x,y]
			If v>highest Then highest=v
		Next
		Next
		Return highest
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
