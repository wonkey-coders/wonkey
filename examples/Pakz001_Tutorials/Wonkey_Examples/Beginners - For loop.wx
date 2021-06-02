#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' for loop
		For Local i:=0 Until 10
			canvas.DrawText("For loop i:"+i,10,100+i*10)
		Next
		' grid
		For Local y:=0 To 10
		For Local x:=0 To 10			
			canvas.DrawLine(100+x*42,100+y*32,100+x*42+42,100+y*32)
			canvas.DrawLine(100+x*42,100+y*32,100+x*42,100+y*32+32)
			canvas.DrawText(""+x+","+y,100+x*42,100+y*32)
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
