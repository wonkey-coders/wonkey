#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance


Class MyWindow Extends Window

	' Create 2 rectangles	
	Field rec1:Rect<Int>
	Field rec2:Rect<Int>
	'Size of the rectangles
	Field rec1s:= new Vec2i(150,50)
	Field rec2s:= new Vec2i(100,100)
	
	Method New()
		' put one rect here
		rec1.X = 150
		rec1.Y = 150
		'Set the sizes of the rects
		rec1.Size = rec1s
		rec2.Size = rec2s
	End Method	
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender() ' Loop with sync
		
		' move rectangle with mouse
		rec2.X = Mouse.X
		rec2.Y = Mouse.Y
		'update the width and height
		rec2.Size = rec2s
		
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
	
		' Draw the rects
		canvas.DrawRect(rec1.X,rec1.Y,rec1.Width,rec1.Height)
		canvas.Color = Color.Blue
		canvas.DrawRect(rec2.X,rec2.Y,rec2.Width,rec2.Height)
		
		' Collision/Intersect with the two rects
		If rec1.Intersects(rec2) = true
			canvas.DrawText("Collision",320,0)
		End If
		
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
