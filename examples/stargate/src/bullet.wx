
Namespace stargate

Global bulletAnim:Image[]

Class Bullet Extends Actor

	Field timeout:Int
	
	Method New( actor:Actor )
		Super.New( ACTOR_BULLET )
		
		flags|=ACTOR_AUTODESTROY
		
		anim=bulletAnim
		
		position=actor.position
		
		Local player:=PlayerUp
		
		Local speed:=4.0
		
		velocity=(player.position-position).Normalize() * speed
		velocity.x+=player.velocity.x
		
		timeout=300
	End
	
	Method OnUpdate() Override
	
		timeout-=1
		If timeout<=0
			Destroy()
			Return
		End
		
		Super.OnUpdate()
	End

End

Function InitBullet()

	bulletAnim=GrabAnim( 578,0,6,6,1,0 )
	
	ActorPoints[ACTOR_BULLET]=75

End

