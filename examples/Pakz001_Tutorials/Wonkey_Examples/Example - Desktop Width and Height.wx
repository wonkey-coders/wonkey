#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()		
		canvas.DrawText("Canvas Width : "+canvas.Viewport.Width,0,0)
		canvas.DrawText("Canvas Height : "+canvas.Viewport.Height,0,15)
		Local mysize:Vec2i
		mysize = App.DesktopSize
		canvas.DrawText("Desktop Width : "+mysize.X,0,30)
		canvas.DrawText("Desktop Height : "+mysize.Y,0,45)		
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
