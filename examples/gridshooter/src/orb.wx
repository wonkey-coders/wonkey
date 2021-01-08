
Class Orb Extends Actor

	Global cullDistance:Double
	
	Method New( sprite:Sprite )
		Super.New( sprite )
		name = "orb"
	End	
	
	Method OnUpdate() Override
		position.X -= 1.0
		If position.X < camera.Left - sprite.Width Then Reset()
	End
	
	Method OnReset() Override
		position.X = camera.Right + sprite.Width
		Local n := ( Rnd() * 240 ) - 120
		position.Y = n
	End
	
End