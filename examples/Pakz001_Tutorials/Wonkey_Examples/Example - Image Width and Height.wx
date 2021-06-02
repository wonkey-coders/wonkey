#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Field can:Canvas
	Field im:Image

	Method New()				
		im = New Image(640,480)
		can = New Canvas(im)
		can.Clear(Color.Black)
		can.Flush()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()				
		canvas.DrawText("Image Width:"+im.Width,0,0)
		canvas.DrawText("Image Height:"+im.Height,0,30)		
	End Method	
	
End	Class

Function Main()
	New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
