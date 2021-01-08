Namespace mojo3d

#Import "Useful"
Using useful..

Class PlaneControl Extends Behaviour
	
	Field speed:= 1.0
	Field turnRate := 0.5
	Field ascentionRate := 0.1
	
	Field lag := 100.0
	
	Field maxPitch := 30.0
	Field maxRoll := 60.0
	Field maxYaw := 15.0
	
	Field plane:Entity			'The plane model to which we'll apply roll
	Field target:Entity			'The camera target, positioned ahead of the plane
	Field camera:Entity	
	
	Private
	Field _azimuth:Float
	Field _azimuthGoal:Float
	
	Field _pitch:Float
	Field _yaw:Float
	Field _roll:Float
	
	Field _throttle:Float = 1.0
	Field _zSpeed:Float
	Field _ySpeed:Float
	Field _ySpeedGoal:Float
	
	Public	
	Method New( entity:Entity )	
		Super.New( entity )
	End
	
	Method OnUpdate( elapsed:Float ) Override
		
		Local delta := elapsed * 60.0
		Local entity:=Entity
		
		If Keyboard.KeyDown( Key.Left )
			_azimuthGoal += turnRate
			_yaw = maxYaw
			_roll = -maxRoll
		Else If Keyboard.KeyDown( Key.Right )
			_azimuthGoal -= turnRate
			_yaw = -maxYaw
			_roll = maxRoll
		Else
			_yaw = 0
			_roll = 0
		Endif
		
		If Keyboard.KeyDown( Key.Up )
			_pitch = -maxPitch
			_ySpeedGoal = -ascentionRate * 2.0
		Else If Keyboard.KeyDown( Key.Down )
			_pitch = maxPitch
			_ySpeedGoal = ascentionRate
		Else
			_ySpeedGoal = 0
			_pitch = 0
		Endif

		_zSpeed = -speed * _throttle * delta
		_ySpeed = Smooth( _ySpeed, _ySpeedGoal, lag, delta )
		
		entity.Move( 0, _ySpeed, _zSpeed )
		
		_azimuth = Smooth( _azimuth, _azimuthGoal, lag, delta )
		entity.Ry = _azimuth

		plane.LocalRx = Smooth( plane.Rx, _pitch, lag, delta )
		plane.LocalRy = Smooth( plane.LocalRy, _yaw, lag, delta )
		plane.LocalRz = Smooth( plane.Rz, _roll, lag, delta )
		
		camera.LocalRz = plane.LocalRz/2.0
		
		target.LocalX = Smooth( target.LocalX, _yaw/4.0, lag, delta )
		
	End
	
	
End
