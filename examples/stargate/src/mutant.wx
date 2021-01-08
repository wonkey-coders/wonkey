
Namespace stargate

Global mutantAnim:Image[]

Class Mutant Extends Actor

	Field ivelocity:Vec2f

	Method New( lander:Lander=Null )
		Super.New( ACTOR_MUTANT )
		
		flags=ACTOR_CLAMPY

		anim=mutantAnim
		animSpeed=.5
		
		If lander
			position=lander.position
		Else
			position=RndPosition()
		Endif
		
		Local v1:=New Vec2f( Rnd( 2,4 ),Rnd( 1,2 ) )
		Local v2:=New Vec2f( Rnd( 3,5 ),Rnd( 2,3 ) )
		
		ivelocity=v1.Blend( v2,Difficulty )
		
		SetFireTimer( 50,10 )
	End

	Method OnUpdate() Override
	
		Local dx:=DeltaX( position.x,PlayerUp.position.x )
		Local dy:=PlayerUp.position.y-position.y
		
		If dx>0
			velocity.x=ivelocity.x
		Else
			velocity.x=-ivelocity.x
		Endif
		
		If dy>0
			velocity.y=ivelocity.y
		Else
			velocity.y=-ivelocity.y
		Endif
		
		Local facing:=(PlayerUp.direction>0)<>(dx>0)
		
		If facing And Abs( dx )>Abs( dy ) velocity.y=-velocity.y
		
		Super.OnUpdate()
	End
	
End

Function InitMutant()

	mutantAnim=GrabAnim( 0,1,18,16,1,0 )
	
	BlipColors[ACTOR_MUTANT]=New Vec4f( 0,.3,0,1 )
	
	ActorPoints[ACTOR_MUTANT]=200
End

