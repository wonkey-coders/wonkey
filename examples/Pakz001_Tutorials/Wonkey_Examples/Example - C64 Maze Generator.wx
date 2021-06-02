'
' From the coding train - based on a commodore 64 line of code.
' 10 print chr
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field x:Int,y:Int
	Field spacing:Int=10
	Field iimage:Image
	Field icanvas:Canvas
	Method New()
		iimage = New Image(Width,Height,TextureFlags.Dynamic)
		icanvas = New Canvas(iimage)
		icanvas.Clear(Color.Black)
		icanvas.Color = Color.White
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		draw(icanvas)
		canvas.DrawImage(iimage,0,0)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method draw(canvas:Canvas)
		
		If Rnd(1)<.5 Then
			canvas.DrawLine(x,y,x+spacing,y+spacing)			
			Else
			canvas.DrawLine(x+spacing,y,x,y+spacing)
		End If
		
		x+=spacing
		If x>Width Then x=0 ; y+=spacing
		If y>Height Then 
			canvas.Clear(Color.Black)
			y=0
		End If
		canvas.Flush()
	End Method
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
