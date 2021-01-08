
Namespace util

Function Fly( entity:Entity,view:View )
	
	Const rspeed:=2.0

	If Keyboard.KeyDown( Key.Up )
		entity.RotateX( rspeed )
	Else If Keyboard.KeyDown( Key.Down )
		entity.RotateX( -rspeed )
	Endif
	
	If Keyboard.KeyDown( Key.Q )
		entity.RotateZ( rspeed )
	Else If Keyboard.KeyDown( Key.W )
		entity.RotateZ( -rspeed )
	Endif
	
	If Keyboard.KeyDown( Key.Left )
		entity.RotateY( rspeed,True )
	Else If Keyboard.KeyDown( Key.Right )
		entity.RotateY( -rspeed,True )
	Endif

	If Mouse.ButtonDown( MouseButton.Left )
		If Mouse.X<view.Width/3
			entity.RotateY( rspeed,True )
		Else If Mouse.X>view.Width/3*2
			entity.RotateY( -rspeed,True )
		Else
			entity.Move( New Vec3f( 0,0,.1 ) )
		Endif
	Endif
	
	If Keyboard.KeyDown( Key.A )
		entity.MoveZ( .1 )	'( New Vec3f( 0,0,.1 ) )
	Else If Keyboard.KeyDown( Key.Z )
		entity.MoveZ( -.1 )	'( New Vec3f( 0,0,-.1 ) )
	Endif
		
End
