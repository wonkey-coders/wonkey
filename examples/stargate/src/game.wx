
Namespace stargate

Const FirstAttackWave:=1

Const WindowWidth:=960
Const WindowHeight:=540

Const ScannerHeight:=80
Const ScannerWidth:=ScannerHeight*8

Const PlanetHeight:=WindowHeight-ScannerHeight
Const PlanetWidth:=PlanetHeight*8

Const ViewWidth:=WindowWidth
Const ViewHeight:=PlanetHeight
Const ViewX:=(PlanetWidth-ViewWidth)/2

Global ScrollX:Float
Global PlayerUp:Player

Global ActiveHumanoids:Int
Global ActiveLanders:Int
Global ActiveMutants:Int
Global ActiveBombers:Int
Global ActivePods:Int
Global ActiveSwarmers:Int
Global ActiveEnemies:Int
Global AttackWave:Int
Global InSpace:Bool
Global LandersToWarp:Int
Global LanderWarpTimer:Int

Global InitBaiterTimer:Int
Global BaiterTimer:Int

Global Difficulty:Float

'need to call 'RestartGame' after one of these goes true...
Global AttackWaveComplete:Bool
Global PlayerKilled:Bool

'random starting position
Function RndPosition:Vec2f()
	Return New Vec2f( Rnd( PlanetWidth ),Rnd( PlanetHeight/2 )+PlanetHeight/4 )
End

'return velocity
Function RndVelocity:Vec2f( magnitude:Float=1 )
	Local an:=Rnd( Pi*2 )
	Return New Vec2f( Cos( an ),Sin( an ) ) * magnitude'Rnd(-1,1),Rnd(-1,1) ).Normalize() * magnitude
End

'wrap coords to planet size
Function WrapX:Float( x:Float )

	If x>=PlanetWidth Return x-PlanetWidth
	
	If x<0 Return x+PlanetWidth
	
	Return x
End

'shortest digned distance from sx to dx
Function DeltaX:Float( sx:Float,dx:Float )

	Local t:=dx-sx
	
	If t>=PlanetWidth/2 Return t-PlanetWidth
	
	If t<-PlanetWidth/2 Return t+PlanetWidth
	
	Return t
End

'convert planet coords to scanner coords
Function ScannerX:Float( x:Float )

	Return WrapX( x-ScrollX )
End

'convert planet coords to render coords
Function RenderX:Float( x:Float )

	Return ScannerX( x )-ViewX
End

'convert render coords to planet coords
Function PlanetX:Float( x:Float )

	Return WrapX( ScrollX+ViewX+x )
End

Function StartNewGame()

	PlayerUp=New Player
	
	AttackWave=FirstAttackWave-1
	
	ActiveHumanoids=10
	
	AttackWaveComplete=True
	
	PlayerKilled=True
	
	RestartGame()
End

Function RestartGame()

	If PlayerKilled PlayerUp.lives-=1
	
	If AttackWaveComplete NextAttackWave()
	
	AttackWaveComplete=False
	
	PlayerKilled=False

	ClearActors()
	
	AddActor( PlayerUp,ACTOR_PLAYER )
	
	PlayerUp.Restart()
	
	For Local i:=0 Until ActiveHumanoids
		New Humanoid
	Next
	
	For Local i:=0 Until ActiveLanders
		New Lander
	Next
	
	For Local i:=0 Until ActiveMutants
		New Mutant
	Next
	
	For Local i:=0 Until ActiveBombers
		New Bomber
	Next
	
	For Local i:=0 Until ActivePods
		New Pod
	Next
	
	For Local i:=0 Until ActiveSwarmers
		New Swarmer
	Next
End

Function NextAttackWave()

	AttackWave+=1
	
	Difficulty=Sqrt( Min( (AttackWave-1)/20.0,1.0 ) )
	
	If AttackWave Mod 5=0
		ActiveHumanoids=10
	End
	
	ActiveLanders=0	
	LandersToWarp=25
	LanderWarpTimer=0
	LandersToWarp=Min( AttackWave*5+15,30 )
	
	ActiveMutants=0
	
	ActiveBombers=Clamp( (AttackWave-2)*3,0,9 )
	
	ActivePods=Clamp( AttackWave-1,0,5 )
	
	ActiveSwarmers=0
	
	InitBaiterTimer=2400-1200 * Difficulty
	BaiterTimer=InitBaiterTimer
End

Function WarpLanders()

	If Not LandersToWarp Return
	
	LanderWarpTimer-=1
	If ActiveLanders And LanderWarpTimer>0 Return

	LanderWarpTimer=600

	Local n:=Min( LandersToWarp,5 )
	LandersToWarp-=n
	
	For Local i:=0 Until n
		New Lander
	Next
	
End

Function WarpBaiter()

	BaiterTimer-=1
	If BaiterTimer>0 Return
	
	InitBaiterTimer=InitBaiterTimer/2+Rnd( 300 )
	
	BaiterTimer=InitBaiterTimer
	
	New Baiter
End
	
Function UpdateGame()

	WarpBaiter()

	WarpLanders()
	
	UpdateActors()
	
	If PlayerKilled Or AttackWaveComplete Return
	
	CollideActors()
	
	ActiveHumanoids=ActiveActors[ACTOR_HUMANOID]
	ActiveLanders=ActiveActors[ACTOR_LANDER]
	ActiveMutants=ActiveActors[ACTOR_MUTANT]
	ActiveBombers=ActiveActors[ACTOR_BOMBER]
	ActivePods=ActiveActors[ACTOR_POD]
	ActiveSwarmers=ActiveActors[ACTOR_SWARMER]
	
	ActiveEnemies=ActiveLanders+ActiveMutants+ActiveBombers+ActivePods+ActiveSwarmers
	
	If PlayerUp.state=0 PlayerKilled=True
	
	If PlayerUp.state>=0 And ActiveEnemies+LandersToWarp=0 AttackWaveComplete=True
		
End
