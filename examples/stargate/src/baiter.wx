
Namespace stargate

Global baiterAnim:Image[]

Class Baiter Extends Actor

	field timer:int

	Method New()
		Super.New( ACTOR_BAITER )
		
		anim=baiterAnim
		animSpeed=.5
		
		flags=ACTOR_WRAPY
		
		position=New Vec2f( Rnd( PlanetWidth ),Rnd( PlanetHeight ) )
		
		SetFireTimer( 150,15 )
		
		Implode()
	End
	
	Method OnUpdate() Override
	
		timer-=1
		If timer<=0
		
			If inview
				Local player:=PlayerUp
			
				Local speed:=2.0
				Local dx:=DeltaX( position.x,player.position.x )
				Local dy:=player.position.y-position.y
				velocity=New Vec2f(dx,dy).Normalize() * speed
				velocity.x+=player.velocity.x
			Endif
					
			timer=Rnd( 60,120 )
		
		Endif
		
		Super.OnUpdate()
	
	End
	
	
End

Function InitBaiter()

	baiterAnim=GrabAnim( 338,144,22,8,4,68 )
	
	BlipColors[ACTOR_BAITER]=New Vec4f( 0,1,1,1 )
	
	ActorPoints[ACTOR_BAITER]=200
End


