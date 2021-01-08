
Namespace stargate

Global bombAnim:Image[]

Class Bomb Extends Actor

	Method New( actor:Actor )
		Super.New( ACTOR_BOMB )
		
		anim=bombAnim
		animSpeed=.05
		
		position=actor.position
		
		Destroy( 300 )
	End
	
End

Function InitBomb()
	
	bombAnim=GrabAnim( 542,1,6,6,2,36 )
End

