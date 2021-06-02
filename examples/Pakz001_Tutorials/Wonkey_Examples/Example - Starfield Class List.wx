#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class star
	Field s:Vec2f
	Field m:Vec2f
	Method New()
		s.X = Rnd(0,640)
		s.Y = Rnd(0,480)
		m.X = Rnd(-1,-0.1)
	End Method
	Method update()
		s+=m
		If s.X < 0 Then s.X = 640
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawPoint(s.X,s.Y)
	End Method
End Class

Global mylist:List<star> = New List<star>

Class MyWindow Extends Window

	Method New()
		For Local i:=0 To 100
			mylist.AddLast(New star())
		Next
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()				
		'
		canvas.Clear(Color.Black)
		For Local i:=Eachin mylist
			i.update()
			i.draw(canvas)
		Next
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow()
	App.Run()
End Function
