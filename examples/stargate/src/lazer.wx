
Namespace stargate

Class Lazer Extends Actor

	Field player:Player
	Field renderx0:Float
	Field renderx1:Float
	Field rendervx:Float

	Method New( player:Player )
		Super.New( ACTOR_LAZER )
		
		Self.player=player

		position.x=player.position.x+player.direction*6
		position.y=player.position.y+2
				
		renderx0=RenderX( position.x )
		renderx1=renderx0
		rendervx=player.direction*16
	End
	
	Method OnUpdate() Override
	
		renderx0+=rendervx
		
		If renderx0<0 Or renderx0>=ViewWidth
			Destroy()
			Return
		End

		position.x=PlanetX( renderx0 )
		
		renderx1+=rendervx*.7
		
		Local x0:=Min( renderx0,renderx1 )
		Local x1:=Max( renderx0,renderx1 )
		
		collRect=New Rectf( PlanetX(x0),position.y,PlanetX(x1),position.y+2 )
	End
	
	Method OnCollide( actor:Actor ) Override
	
		actor.OnKilled()
	
		player.AddPoints( ActorPoints[actor.type] )
		
		Destroy()
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		Local x0:=Min( renderx0,renderx1 )
		Local x1:=Max( renderx0,renderx1 )

		canvas.Color=Color.Yellow
		canvas.DrawRect( x0,position.y,x1-x0,2 )
		
		canvas.Color=Color.White
	End
	
End

Function InitLazer()

	Collisions[ACTOR_LAZER]=New Int[]( ACTOR_HUMANOID,ACTOR_LANDER,ACTOR_MUTANT,ACTOR_BOMBER,ACTOR_POD,ACTOR_SWARMER,ACTOR_BAITER )
	
End