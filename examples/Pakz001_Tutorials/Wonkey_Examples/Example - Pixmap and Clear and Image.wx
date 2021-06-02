#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field pixmap:=New Pixmap( 640,480 )
	Field image:=New Image( 640,480,TextureFlags.Dynamic )
 
	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		pixmap.Clear(New Color(Rnd(),Rnd(),Rnd(),1))
		
		image.Texture.PastePixmap( pixmap,0,0 )
		canvas.DrawImage( image,0,0 )
		
		canvas.Color = Color.White
		canvas.DrawText("FPS:"+App.FPS,0,0)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
