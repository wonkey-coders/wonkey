
Namespace mojo3d

Class FlyBehaviour Extends Behaviour
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,fly:FlyBehaviour )
		
		Super.New( entity )
		
		Speed=fly.Speed
		RotSpeed=fly.RotSpeed
		
		AddInstance( fly )
	End
	
	[jsonify=1]
	Property Speed:Float()
		
		Return _speed
	
	Setter( speed:Float )
		
		_speed=speed
	End
	
	[jsonify=1]
	Property RotSpeed:Float()
		
		Return _rspeed
		
	Setter( rspeed:Float )
		
		_rspeed=rspeed
	End
	
	Method OnUpdate( elapsed:Float ) Override
		
		Local rspeed:=_rspeed * 60.0 * elapsed
		
		Local entity:=Entity
		
		Local view:=App.ActiveWindow
	
		If Keyboard.KeyDown( Key.Up )
			entity.RotateX( rspeed )
		Else If Keyboard.KeyDown( Key.Down )
			entity.RotateX( -rspeed )
		Endif
		
		If Keyboard.KeyDown( Key.Left )
			entity.RotateY( rspeed,True )
		Else If Keyboard.KeyDown( Key.Right )
			entity.RotateY( -rspeed,True )
		Endif
	
		If Keyboard.KeyDown( Key.A )
			entity.MoveZ( _speed * 60 * elapsed )
		Else If Keyboard.KeyDown( Key.Z )
			entity.MoveZ( -_speed * 60 * elapsed )
		Endif
		
#If __MOBILE_TARGET__
		If Mouse.ButtonDown( MouseButton.Left )
			If Mouse.X<view.Width/3
				entity.RotateY( rspeed,True )
			Else If Mouse.X>view.Width/3*2
				entity.RotateY( -rspeed,True )
			Else
				entity.Move( New Vec3f( 0,0,_speed * 60 * elapsed ) )
			Endif
		Endif
#endif
		
	End
	
	Private
	
	Field _speed:Float=.1
	Field _rspeed:Float=3.0
	
End
