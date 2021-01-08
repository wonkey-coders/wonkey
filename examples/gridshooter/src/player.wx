Class Player Extends Actor

	Field  oldY:Double
	Field limitY:Double = 180
	
	Method New( sprite:Sprite )
		Super.New( sprite )
		name = "player"
	End	
	
	Method OnUpdate() Override		
		If Keyboard.KeyDown( Key.Left )
			position.X -= speed
		Else If Keyboard.KeyDown( Key.Right )
			position.X += speed
		End
		If Keyboard.KeyDown( Key.Up )
			position.Y -= speed
		Else If Keyboard.KeyDown( Key.Down )
			position.Y += speed
		End
		
		If Keyboard.KeyHit( Key.Space )
			Local bullet := bulletPool.Get( currentBullet )
			bullet.Reset()
			bullet.visible = True
			bullet.position.X = position.X
			bullet.position.Y = position.Y + 4
			currentBullet += 1
			If currentBullet > 9 Then currentBullet = 0
		End
		
		position.X = Clamp( position.X, camera.Left, camera.Right )
		position.Y = Clamp( position.Y, camera.Top, camera.Bottom)
		
		If position.Y > oldY
			anim = "down"
		Elseif position.Y < oldY
			anim = "up"
		Else
			anim = "idle"
		End
		oldY = position.Y
	End
End