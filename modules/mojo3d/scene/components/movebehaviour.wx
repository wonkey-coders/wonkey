Namespace mojo3d

Class MoveBehaviour Extends Behaviour
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,move:MoveBehaviour )
		
		Super.New( entity )
		
		Speed=move.Speed
		
		AddInstance( move )
	End
	
	[jsonify=1]
	Property Speed:Vec3f()
		
		Return _speed
	
	Setter( speed:Vec3f )
		
		_speed=speed
	End
	
	[jsonify=1]
	Property LocalSpace:Bool()
		
		Return _localSpace
	
	Setter( localSpace:Bool )
		
		_localSpace=localSpace
	End
	
	Protected
	
	Method OnUpdate( elapsed:Float ) Override
		
		Entity.Move( _speed,_localSpace )
	End
	
	Private
	
	Field _speed:Vec3f
	
	Field _localSpace:Bool
	
End
