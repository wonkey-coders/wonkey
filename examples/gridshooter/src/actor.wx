Class Actor

	'******************************* Static Globals *******************************

	Global catalog := New Stack<Actor>
	Global bulletPool := New Stack<Bullet>
	
	Global camera:Area<Double>
	Global player:Actor
	
	Global scrollSpeed := 5.0
	Global currentBullet := 0
	Global cullDistance:Double
	
	'******************************* Public fields *******************************
	
	Field name := ""
	Field visible := True
	Field speed:Double = 3.0
	Field anim:= "idle"
	Field detectCollision := True
	
	Field sprite:Sprite
	Field position := New Vec2<Double>
	
	Field collider :Area<Double>
	
	'******************************* Protected fields *******************************
	
	Field _hide := False
	Field _hideTimer := 0
	Field _hideTimerStart := 0
	Field _hideWait := 0
	
	'******************************* Public methods *******************************
		
	Method New( sprite:Sprite )
		Self.sprite = sprite
		catalog.Push( Self )
		collider= New Area<Double>( 0, 0, sprite.Width, sprite.Height )
		Reset()
	End
	
	Method Hide( time:Int )
		_hide = True
		_hideTimerStart = Millisecs()
		_hideWait = time
	End
	
	Method Reset()
		sprite.Reset()
		_hide = False
		detectCollision = True
		OnReset()
	End
	
	
	
	'******************************* Static functions *******************************

	Function UpdateAll()
		For Local a := Eachin catalog
			If a.visible
				If a._hide
					a._hideTimer = Millisecs() - a._hideTimerStart
					If a._hideTimer > a._hideWait
						a.visible = False
						a._hide = False
					End				
				End
				a.position.X += scrollSpeed
				a.OnUpdate()
				a.collider.Position( a.position.X, a.position.Y )
			End
		Next
	End

	Function DrawAll( canvas:Canvas )
		For Local a := Eachin catalog
			If a.visible
				a.sprite.Draw( canvas, a.anim, a.position.X, a.position.Y )
'   				GameGraphics.DrawRectOutline( canvas, a.collider.Left, a.collider.Top, a.collider.Width, a.collider.Height )
				a.OnDraw( canvas )
			End
		Next
	End
	
	'******************************* Virtual methods *******************************
	
	Method OnUpdate() Virtual
	End
	
	Method OnDraw( canvas:Canvas ) Virtual
	End
	
	Method OnReset() Virtual
	End
	
End
