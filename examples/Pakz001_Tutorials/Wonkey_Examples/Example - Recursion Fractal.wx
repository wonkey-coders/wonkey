#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Field r:Float=0
	Method New()

	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		r+=.1
		If r>=TwoPi Then r=0
		canvas.Translate(Width/2,Height/2)
		canvas.Rotate(r)		
		canvas.OutlineMode = OutlineMode.Solid
		canvas.OutlineWidth = 2
		canvas.OutlineColor = Color.Black
		drawcirc(canvas,0,0,300)
		canvas.Translate(-Width/2,-Height/2)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	Method drawcirc(canvas:Canvas,x:Int,y:Int,r:Int)
		If r<2 Then Return
		canvas.DrawCircle(x,y,r)
		drawcirc(canvas,x+r*0.5,y,r*0.5)
		drawcirc(canvas,x-r*0.5,y,r*0.5)
		drawcirc(canvas,x,y+r*0.5,r*0.5)
		drawcirc(canvas,x,y-r*0.5,r*0.5)
	End Method
		
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
