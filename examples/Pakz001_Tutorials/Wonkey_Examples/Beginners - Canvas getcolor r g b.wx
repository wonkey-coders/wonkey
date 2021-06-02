#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
		Title="canvas getcolor r g b" 
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		canvas.Clear(Color.Black)
		canvas.Color = New Color(0.9,0.7,0.1)
		Local r:Float=canvas.Color.r
		Local g:Float=canvas.Color.g
		Local b:Float=canvas.Color.b
		canvas.DrawText("Current canvas.color.r:"+r,0,0)		
		canvas.DrawText("Current canvas.color.g:"+g,0,20)		
		canvas.DrawText("Current canvas.color.b:"+b,0,40)		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
