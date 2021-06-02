#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	
	Field image:Image
 	Field icanvas:Canvas
 
	Method New()
		image=New Image(640,480,TextureFlags.Dynamic)
		icanvas=New Canvas(image)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		icanvas.Clear(Color.Black)
		icanvas.Scissor = New Recti(50,50,50+640-100,50+480-100)
		icanvas.Color = Color.White
		For Local i:=0.0 Until TwoPi Step TwoPi/10
			Local poly:=New Float[6]
			poly[0] = 320
			poly[1] = 240
			poly[2] = 320+Cos(i)*640
			poly[3] = 240+Sin(i)*480
			poly[4] = 320+Cos(i+TwoPi/20)*640
			poly[5] = 240+Sin(i+TwoPi/20)*480
			icanvas.DrawPoly(poly)
		Next	
		
		icanvas.Flush()		
		
		canvas.DrawImage(image,0,0)
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
