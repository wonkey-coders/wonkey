#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance


Class MyWindow Extends Window
	
	' Here we create the vectors for the ship
	' and the velocity
	Field ship:Vec2f
	Field velocity:Vec2f

	Method New()
		ship.X = 100
		ship.Y = 100
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then instance.Terminate()
		App.RequestRender() ' Loop with sync
		
		' Input
		If Keyboard.KeyDown(Key.Right)
			velocity.X += 0.1
		End If
		If Keyboard.KeyDown(Key.Left)
			velocity.X -= 0.1
		End If
		If Keyboard.KeyDown(Key.Up)
			velocity.Y -= 0.1
		End If
		If Keyboard.KeyDown(Key.Down)
			velocity.Y += 0.1
		End If

		'Limit speed
		If velocity.X < -5 Then velocity.X = -5
		If velocity.X > 5 Then velocity.X = 5
		If velocity.Y < -5 Then velocity.Y = -5
		If velocity.Y > 5 Then velocity.Y = 5
		
		' keep the ship inside the viewport
		If ship.X > canvas.Viewport.Width Then ship.X = 0
		If ship.X < 0 Then ship.X = canvas.Viewport.Width
		If ship.Y > canvas.Viewport.Height Then ship.Y = 0
		If ship.Y < 0 Then ship.Y = canvas.Viewport.Height
		
		' Update the ship position
		ship+=velocity
		
		
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Use cursor keys to move rectangle around the screen.",0,0)
		' Draw the ship
		canvas.DrawRect(ship.X,ship.Y,20,20)
	End Method	
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
