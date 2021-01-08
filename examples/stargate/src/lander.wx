
Namespace stargate

Global landerAnim:Image[]

Const LANDER_IDLE:=1
Const LANDER_HOMING:=2
Const LANDER_ATTACKING:=3
Const LANDER_PICKINGUP:=4

Class Lander Extends Actor

	Field ivelocity:Vec2f
	Field hoverh:Float
	Field humanoid:Humanoid
	
	Field firemin:Int
	Field firemax:Int
	Field firetimer:Int

	Method New()
		Super.New( ACTOR_LANDER )
		
		anim=landerAnim
		animSpeed=.5
		
		image=anim[0]
		
		position.x=Rnd( PlanetWidth )
		position.y=Rnd( PlanetHeight/3 )+PlanetHeight/9
		
		Local v1:=New Vec2f( Rnd( .5,1 ),Rnd( .5,1 ) )	'EASY
		Local v2:=New Vec2f( Rnd(  2,3 ),Rnd(  2,3 ) )	'HARD!
		
		ivelocity=v1.Blend( v2,Difficulty )
		
		If Rnd()>=.5 ivelocity.x=-ivelocity.x
		
		velocity=ivelocity
		
		hoverh=Rnd( 48,96 )
		
		SetFireTimer( 150,50 )

		Implode()
	End
	
	Method OnUpdate() Override
	
		'Update velocity
		'
		Select state
		Case LANDER_IDLE,LANDER_HOMING
			velocity.x=ivelocity.x
			Local dy:=Mountains[position.x]-hoverh-position.y
			If dy>16
				velocity.y=ivelocity.y
			Else If dy<-16
				velocity.y=-ivelocity.y
			Else
				velocity.y=0
			Endif
		Case LANDER_ATTACKING
			velocity.x=0
			velocity.y=ivelocity.y
		Case LANDER_PICKINGUP
			velocity.x=0
			If position.y+image.Bounds.Top<=0
				position.y=-image.Bounds.Top
				velocity.y=0
			Else
				velocity.y=-ivelocity.y
			Endif
		End

		Super.OnUpdate()

		'Update state
		'
		Select state
		Case LANDER_IDLE
		
			humanoid=Cast<Humanoid>( FindRandomActor( ACTOR_HUMANOID,HUMANOID_IDLE ) )
			
			If humanoid state=LANDER_HOMING
			
		Case LANDER_HOMING
		
			If humanoid.state=HUMANOID_IDLE
		
				If Abs( DeltaX( position.x,humanoid.position.x ) )<Abs( ivelocity.x )

					humanoid.lander=Self
					
					humanoid.state=HUMANOID_UNDERATTACK
					state=LANDER_ATTACKING

				Endif
			Else
				humanoid=Null
				state=LANDER_IDLE
			Endif
		
		Case LANDER_ATTACKING
		
			If humanoid.state=HUMANOID_UNDERATTACK
			
				If position.y+image.Bounds.Bottom>=humanoid.position.y+humanoid.image.Bounds.Top-4
				
					humanoid.state=HUMANOID_PICKEDUP
					state=LANDER_PICKINGUP
					
'					PlaySound( "asset::Powerup8.wav",.75 )
					
				Endif
			
			Else
				humanoid.lander=Null
				humanoid=Null
				state=LANDER_IDLE
			Endif
		
		Case LANDER_PICKINGUP
		
			If humanoid.state=HUMANOID_PICKEDUP
			
				If humanoid.position.y+humanoid.image.Bounds.Top<=0
				
					humanoid.Explode()
					humanoid=Null
					
					New Mutant( Self )

					state=LANDER_IDLE
					Explode()
					Return
				Endif
			
			Else
				humanoid.lander=Null
				humanoid=Null
				state=LANDER_IDLE
			Endif
		
		End
	
	End
	
	Method OnKilled() Override
	
		Select state
		Case LANDER_ATTACKING
			If humanoid.state=HUMANOID_UNDERATTACK 
				humanoid.state=HUMANOID_IDLE
				humanoid.lander=Null
			Endif
		Case LANDER_PICKINGUP
			If humanoid.state=HUMANOID_PICKEDUP
				humanoid.state=HUMANOID_FALLING
				humanoid.lander=Null
			Endif
		End
		
		Explode()
	End
	
End

Function InitLander()

	landerAnim=GrabAnim( 204,169,18,16,4,60 )
	
	BlipColors[ACTOR_LANDER]=New Vec4f( 0,1,0,1 )

	ActorPoints[ACTOR_LANDER]=150

End

