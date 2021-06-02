#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window 

	Field m:= New String[3]
	
	Method New()
		m[0] = "000"
		m[1] = "010"
		m[2] = "000"
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.Clear(Color.White)
		For Local y:=0 To 2
		For Local x:=0 To 2
			canvas.Color = Color.Black
			canvas.DrawRect(x*32+100,y*32+100,32,32)
		    If m[y][x] = 48 Then
			     canvas.Color = Color.Green
			     canvas.DrawText("X",x*32+100,y*32+100)
			End If 
			If m[y][x] = 49 Then 
				canvas.Color = Color.Blue
				canvas.DrawText("X",x*32+100,y*32+100)
			End If  
		Next
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
