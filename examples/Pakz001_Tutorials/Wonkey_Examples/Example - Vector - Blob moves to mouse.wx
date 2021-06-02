#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field blob:= New Vec2f(50,50)
	Method New()
		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Create a vector that holds the desired velocity
		Local desired:= New Vec2f()
		' Get the angle between blob and mouse and multiply it by 0.1
		desired = (blob-Mouse.Location)*0.1				
		
		' Substract the desired from blob to move blob
		' towards the mouse
		blob-=desired
		
		'draw the blob
		canvas.DrawCircle(blob.x,blob.y,10)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
