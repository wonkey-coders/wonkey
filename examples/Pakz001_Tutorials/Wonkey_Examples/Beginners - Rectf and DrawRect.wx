#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Method New()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		Local x:=Mouse.X
		Local y:=Mouse.Y
		Local w:=100
		Local h:=100
		Local r := new Rectf(x,y,x+w,y+h)
		canvas.DrawRect(r)
		'
		canvas.DrawText("Left:"+r.Left,10,10)
		canvas.DrawText("Top:"+r.Top,10,30)
		canvas.DrawText("Right:"+r.Right,10,50)
		canvas.DrawText("Bottom:"+r.Bottom,10,70)
		canvas.DrawText("Width:"+r.Width,10,90)
		canvas.DrawText("Height:"+r.Height,10,110)
		Local s:=New Vec2f()
		s = r.Size
		canvas.DrawText("Size vec2f width:"+s.X,10,130)
		canvas.DrawText("Size vec2f Height:"+s.Y,10,150)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
