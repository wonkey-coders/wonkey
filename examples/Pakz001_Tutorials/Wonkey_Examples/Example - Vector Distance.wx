#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	

	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' These lines below get the distance between 2 vectors!
		Local dist:Int=New Vec2i(10,10).Distance(New Vec2i(Mouse.X,Mouse.Y))
		Local distf:Float=New Vec2f(10,10).Distance(New Vec2f(Mouse.X,Mouse.Y))
		
		canvas.DrawText(dist,0,0)
		canvas.DrawText(distf,0,20)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
