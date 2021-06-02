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
				ex1[x,y] = c
			End If
		End If
		If Mouse.X > ex2pos.X And Mouse.Y > ex2pos.Y
			Local x:Int=(Mouse.X - ex2pos.X) / tw
			Local y:Int=(Mouse.Y - ex2pos.Y) / th
			If x<w And y<h
				ex2[x,y] = c
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
			If ar[x,y] = 1				
				ret[x+Rnd(-1,2),y+Rnd(-1,2)] = 1								
			End If
		Wend
		Return ret
	End Method
	Method draw(canvas:Canvas,ar:Int[,],x:Int,y:Int)
		canvas.Color = Color.White
		canvas.DrawRect(x-1,y-1,ar.GetSize(0)*tw+2,ar.GetSize(1)*th+2)
		For Local y2:Int = 0 Until ar.GetSize(1)
		For Local x2:Int = 0 Until ar.GetSize(0)
			Select ar[x2,y2] 
				Case 0 
					canvas.Color = Color.Black
				Case 1 
					canvas.Color = Color.White				
			End select
			canvas.DrawRect(x+x2*tw,y+y2*th,tw,th)
		Next
		Next		
	End Method
	Method reset()
		ex1 = New Int[w,h]
		ex2 = New Int[w,h]
	End Method	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
