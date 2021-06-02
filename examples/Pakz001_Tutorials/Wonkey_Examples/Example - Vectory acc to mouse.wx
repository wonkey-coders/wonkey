#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window

	Field point1:Vec2f
	Field point2:Vec2f
	Field dir:Vec2f,acc:Vec2f,velocity:Vec2f
	Method New()
		point1 = New Vec2f(100,100)
		point2 = New Vec2f(320,240)
		dir = New Vec2f()
		acc = New Vec2f()
		velocity = New Vec2f()
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		' Get the mouse position in poitn 2
		point2.x = Mouse.X
		point2.Y = Mouse.Y

		' get point2 into dir
		dir = point2
		'substract position of the point1 from the dir
		dir-= point1
		' normalize the dir
		dir.Normalize()
		' multi ply the dir
		dir*=.05
		' copy the dir into the acceleration vector
		acc=dir
		
		
		' Set our velocity
		velocity+=acc
		' Limit our velocity
		velocity.x = Clamp(velocity.x,-4.0,4.0)
		velocity.y = Clamp(velocity.y,-4.0,4.0)
		' Move our point1
		point1+=velocity
		
		
		canvas.DrawText("yeh",point1.x,point1.y)
		canvas.DrawText("Here",point2.x,point2.y)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
