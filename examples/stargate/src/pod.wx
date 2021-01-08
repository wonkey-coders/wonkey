
Namespace stargate

Global podAnim:Image[]

Class Pod Extends Actor

	Method New()
		Super.New( ACTOR_POD )
	
		anim=podAnim
		
		flags=ACTOR_WRAPY
		
		position.x=Rnd( PlanetWidth )
		position.y=Rnd( PlanetHeight/2+PlanetHeight/4 )

		velocity.x=Rnd( -.002,.002 )		
		velocity.x=Rnd( -.002,.002 )
	
	End
	
	Method OnKilled() Override
	
		For Local i:=0 Until 8
			New Swarmer( Self )
		End
		
		Super.OnKilled()
		
	End
	
End

Function InitPod()

	podAnim=GrabAnim( 112,0,14,14,1,0 )
	
	BlipColors[ACTOR_POD]=New Vec4f( 1,.5,1,1 )

	ActorPoints[ACTOR_POD]=1000

End

