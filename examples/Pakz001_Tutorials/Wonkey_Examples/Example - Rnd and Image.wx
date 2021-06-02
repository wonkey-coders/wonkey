#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance


Class MyWindow Extends Window

	Field can:Canvas
	Field im:Image

	Method New()				
		im = New Image(640,480)
		can = New Canvas(im)
		can.Clear(Color.Black)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()				

'		canvas.Clear(Color.Black)
		can.Color = Color.White
		can.DrawText(Int(Rnd(0,10)),Rnd(0,640),Rnd(20,480))
		can.Flush()
		canvas.DrawImage(im,0,0)
		canvas.Color = Color.Yellow
		canvas.DrawText("Int(Rnd(0,10))",0,0)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
