#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field zoom:Float=1
	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		canvas.Translate(Width/2-(Width/2*zoom),Height/2-(Height/2*zoom))
		canvas.Scale(New Vec2f(zoom))
		canvas.DrawText("Top Left....",0,0)
		canvas.DrawText("Center....",Width/2,Height/2)
		If Keyboard.KeyReleased(Key.Left) Then zoom-=.1
		If Keyboard.KeyReleased(Key.Right) Then zoom+=.1
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
