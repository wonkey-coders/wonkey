#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field numdots:Int=150
	Field dots:Int[]
	Method New()
		dots = New Int[numdots]
		fillrandom(0,100)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Black)
		drawdots(canvas)
		If Keyboard.KeyReleased(Key.Space) Then smootdots()
		If Keyboard.KeyReleased(Key.Enter) Then fillrandom(0,100)
		canvas.Color = Color.White
		canvas.DrawText("Press Space to smooth press Enter to randomize",100,320)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
	Method fillrandom(low:Int,high:Int)
		For Local i:Int=0 Until dots.Length
			dots[i] = Rnd(low,high)
		Next
	End Method
	
	Method smootdots()
		For Local i:Int=1 Until dots.Length
			Local a:Int=dots[i-1]
			Local b:Int=dots[i]
			If a<b Then
				dots[i-1] = a+(Abs(b-a)/2)
			Else			
				dots[i-1] = b+(Abs(a-b)/2)
			End If
		Next
	End Method	

	
	Method drawdots(canvas:Canvas)
		canvas.Color = Color.White
		Local sx:Int=Width/dots.Length
		Local x:Int=0
		For Local i:Int=0 Until dots.Length-1 
			canvas.DrawLine(x,dots[i]+100,x+sx,dots[i+1]+100)
			x+=sx
		Next
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
