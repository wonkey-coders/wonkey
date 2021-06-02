#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance


Class MyWindow Extends Window

	Field timer:Timer

	Method New()
		timer = New Timer(10,OnUpdate)
	End Method
	
	Method OnUpdate()
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		canvas.DrawText("FPS:"+App.FPS,0,0)				
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
