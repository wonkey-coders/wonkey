
Namespace stargate

Global playerAnim:Image[]

Class Player Extends Actor

	Field direction:Float	'1=facing right,-1=facing left
	Field reverse:Bool
	Field fire:Bool
	
	Field lives:Int=3
	Field score:Int=0
	
	Method New()
		Super.New( 0 )
		
		flags|=ACTOR_CLAMPY
		
		anim=playerAnim
	End
	
	Method Restart()

		animTime=0
		image=anim[0]
		
		position.x=PlanetWidth/2
		position.y=ViewHeight/2
		velocity=New Vec2f( 0,0 )
		
		renderx=144
		direction=1
		flags&=~ACTOR_XFLIPIMAGE
		reverse=True
		fire=True
	End
	
	Method AddPoints( points:Int )
		Local n:=score/10000
		score+=points
		If score/10000<>n lives+=1
	End
	
	Method OnUpdate() Override
	
		'handle up/down
		'
		If Keyboard.KeyDown( Key.A )
			velocity.y+=(-4-velocity.y)*.2
		Else If Keyboard.KeyDown( Key.Z )
			velocity.y+=( 4-velocity.y)*.2
		Else
			velocity.y*=.3'+=velocity.y*-.3
		Endif
		
		'handle reverse
		If Keyboard.KeyDown( Key.LeftAlt )
			If Not reverse
				reverse=True
				direction=-direction
				If direction<0 flags|=ACTOR_XFLIPIMAGE Else flags&=~ACTOR_XFLIPIMAGE
			Endif
		Else
			reverse=False
		Endif
		
		'handle thrust
		If Keyboard.KeyDown( Key.Period )'( Key.Apostrophe )
			velocity.x+=(direction*10-velocity.x)*.025
		Else
			velocity.x*=.99
		Endif
		
		'update renderx
		Local rx:Float
		If direction>0
			rx=144+Max( (velocity.x-0.0)*16,0.0 )
		Else
			rx=ViewWidth-144+Min( (velocity.x+0.0)*16,0.0 )
		Endif
		Local dx:=Clamp( rx-renderx,-4.0,4.0 )
		renderx+=dx
		
		Super.OnUpdate()

		'handle fire
		If Keyboard.KeyDown( Key.Slash )'( Key.Enter )
			If Not fire
				fire=True
				New Lazer( Self )
'				PlaySound( "asset::Laser_Shoot5.wav",.5 )
			Endif
		Else
			fire=False
		Endif
	End
	
	Method OnCollide( actor:Actor ) Override
	
		actor.OnKilled()
		
		AddPoints( ActorPoints[actor.type] )
		
		Explode()
	End

End

Function InitPlayer()

	playerAnim=GrabAnim( 44,27,30,12,1,0 )
	
	BlipColors[ACTOR_PLAYER]=New Vec4f( 1,1,1,1 )
	
	Collisions[ACTOR_PLAYER]=New Int[]( ACTOR_LANDER,ACTOR_BULLET,ACTOR_MUTANT,ACTOR_BOMBER,ACTOR_BOMB,ACTOR_BAITER )
	
End
