
Namespace stargate

Global bomberAnim:Image[]

Class Bomber Extends Actor

	Field bombing:Int
	Field bombTimer:Int

	Method New()
		Super.New( ACTOR_BOMBER )
		
		flags=ACTOR_WRAPY
		
		anim=bomberAnim
		animSpeed=.1
		
		position=New Vec2f( Rnd( PlanetWidth ),Rnd( PlanetHeight/2 )+PlanetHeight/4 )
		
		velocity=New Vec2f( Rnd( 1,2 ),0 )	'easy
'		velocity=New Vec2f( Rnd( 2,3 ),0 )	'hard
		
		If Rnd()>=.5 velocity.x=-velocity.x
	End
	
	Method OnUpdate() Override

		Local dy:=PlayerUp.position.y-position.y
		
		If dy>0
			velocity.y=Min( velocity.y+.01,1.0 )	'easy
'			velocity.y=Min( velocity.y+.03,2.0 )
		Else
			velocity.y=Max( velocity.y-.01,-1.0 )	'easy
'			velocity.y=Max( velocity.y-.03,-2.0 )
		Endif
		
		Super.OnUpdate()
		
		If bombing
			bombTimer-=1
			If bombTimer<=0
				New Bomb( Self )
				bombTimer=Rnd( 10,30 ) 'easy
'				bombTimer=Rnd( 10,30 )
				bombing-=1
			Endif
		Else If inview And Abs( dy )<32
			bombing=Rnd( 1,4 )   'easy
'			bombing=Rnd( 4,8 )
		Endif
		
	End

End

Function InitBomber()

	bomberAnim=GrabAnim( 308,0,12,16,4,52 )

	BlipColors[ACTOR_BOMBER]=New Vec4f( 1,0,.5,1 )

	ActorPoints[ACTOR_BOMBER]=250	
End
