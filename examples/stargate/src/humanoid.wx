
Namespace stargate

Global humanoidAnim:Image[]

Const HUMANOID_IDLE:=1
Const HUMANOID_UNDERATTACK:=2
Const HUMANOID_PICKEDUP:=3
Const HUMANOID_FALLING:=4
Const HUMANOID_RESCUED:=5

Class Humanoid Extends Actor

	Field ivelocity:Vec2f
	
	Field lander:Lander
	Field player:Player

	Method New()
		Super.New( ACTOR_HUMANOID )
		
		anim=humanoidAnim
		animSpeed=.05
		
		image=anim[0]
		
		position.x=Rnd( PlanetWidth )
		
		ivelocity.x=Rnd( -.1,.1 )
	End
	
	Method OnUpdate() Override
	
		Select state
		Case HUMANOID_IDLE
		
			position.y=Mountains[ position.x ]'+image.Y0
			velocity=ivelocity
			
		Case HUMANOID_UNDERATTACK
		
			velocity.x=0
			velocity.y=0
			
		Case HUMANOID_PICKEDUP
		
			velocity.x=0
			velocity.y=-lander.ivelocity.y
			
		Case HUMANOID_FALLING
		
			If position.y>=Mountains[ position.x ]'+image.Y0
				position.y=Mountains[ position.x ]'+image.Y0
				velocity=ivelocity
				state=HUMANOID_IDLE
			Else
				If velocity.y<0 velocity.y=0
				velocity.y+=.01
			Endif
			
		Case HUMANOID_RESCUED

			position.x=player.position.x		
			position.y=player.position.y+player.image.Bounds.Bottom+4-image.Bounds.Top
			
			If position.y>=Mountains[ position.x ]'+image.Y0
				position.y=Mountains[ position.x ]'+image.Y0
				velocity=ivelocity
				state=HUMANOID_IDLE
				New Bonus( player )
			Else
				velocity.x=0
				velocity.y=0
			Endif
			
		End
		
		Super.OnUpdate()
	End
	
	Method OnCollide( actor:Actor ) Override
	
		If state=HUMANOID_FALLING
			player=Cast<Player>( actor )
			If player
				state=HUMANOID_RESCUED
				New Bonus( player )
			Endif
		Endif
	End
	
End

Function InitHumanoid()

	humanoidAnim=GrabAnim( 164,1,6,16,2,36 )
	
	Collisions[ACTOR_HUMANOID]=New Int[]( ACTOR_PLAYER )
	
	BlipColors[ACTOR_HUMANOID]=New Vec4f( 1,0,1,1 )
	
End

