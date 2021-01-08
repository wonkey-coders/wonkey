
Namespace stargate

Global swarmerAnim:Image[]

Class Swarmer Extends Actor

	Method New( pod:Pod=Null )
		Super.New( ACTOR_SWARMER )
		
		flags=ACTOR_WRAPY
		
		anim=swarmerAnim
		
		If pod
			position=pod.position
		Else
			position=RndPosition()
		Endif
		
		velocity=RndVelocity()
	End
	
End

Function InitSwarmer()

	swarmerAnim=GrabAnim( 0,26,10,8,1,0 )
	
	BlipColors[ACTOR_SWARMER]=New Vec4f( 1,.25,0,1 )

	ActorPoints[ACTOR_SWARMER]=100

End

