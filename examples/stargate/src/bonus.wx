
Namespace stargate

Global bonus500Anim:Image[]

Class Bonus Extends Actor

	Field timeout:Int
	
	Method New( player:Player )
		Super.New( ACTOR_BONUS )
		
		flags|=ACTOR_AUTODESTROY
		
		anim=bonus500Anim
	
		position=player.position
		velocity.x=player.velocity.x+Rnd( -.5,.5 )
		velocity.y=Rnd( -.2,.2 )
		
		timeout=200
		
		player.AddPoints( 500 )
	End
	
	Method OnUpdate() Override
	
		timeout-=1
		If timeout<=0
			Destroy()
			Return
		Endif
		
		Super.OnUpdate()
	End
	
End

Function InitBonus()

	bonus500Anim=GrabAnim( 68,101,22,10,1,0 )

End
