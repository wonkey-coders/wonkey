#Import "../assets/p10000.png"
#Import "../assets/p10001.png"
#Import "../assets/p20000.png"
#Import "../assets/p20001.png"
#Import "../assets/bullet.png"
#Import "../assets/black_smoke.png"
#Import "../assets/light.png"
#Import "../assets/blastwave.png"
#Import "../assets/explosion.txt"
#Import "../assets/smoke.txt"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-scenegraph>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global attacker:Attacker
Global camera:Camera
Global explosion:Emitter
Global layer:Layer
Global scene:Scene
Global smoke:Emitter
Global player:Player

Class Attacker Extends LayerSprite

	Field fireDelayCounter:=0
	Field speed:=2

	Method OnUpdate() Override

		Y+=speed
		If Y>480-32 speed=-speed
		If Y<32 speed=-speed

		If fireDelayCounter=0
	
			fireDelayCounter=40
	
			Local bullet:=New Bullet()
			bullet.Layer=layer
			bullet.TaskManager=scene.TaskManager
			bullet.Image=Content.GetImage( "asset::bullet.png" )
			bullet.Name="bullet"
			bullet.FlippedX=-1
			bullet.speed=-8
			bullet.X=X-40-bullet.speed
			bullet.Y=Y

			bullet.ScoreSystem=New ScoreSystem()
			bullet.CollisionRead=True
			bullet.ScoreCollector=Self

		Else
	
			fireDelayCounter=fireDelayCounter-1
	
		Endif

		Frame+=.25
		Frame=Frame Mod Frames

	End

End

Class Bullet Extends LayerSprite

	Field speed:Float

	' Called when a collision occurs:
	Method OnCollision( layerObject:LayerObject ) Override
		Print layerObject.Name+" "+Rnd( 1 )
	End

	Method OnUpdate() Override

		X+=speed
		If X<0 Or X>640
			Remove()
		Endif

	End

End

Class Player Extends LayerSprite

	Field fireDelayCounter:Int

	Method OnCollision( layerObject:LayerObject ) Override
		Print layerObject.Name+" "+Rnd( 1 )
	End

	Method OnUpdate() Override

		If Keyboard.KeyDown( Key.Up ) Y-=4
		If Keyboard.KeyDown( Key.Down ) Y+=4
		If Keyboard.KeyDown( Key.Left ) X-=4
		If Keyboard.KeyDown( Key.Right ) X+=4

		If fireDelayCounter=0
	
			fireDelayCounter=16
	
			If Keyboard.KeyDown( Key.M )
	
				Local bullet:=New Bullet()
				bullet.Layer=layer
				bullet.TaskManager=scene.TaskManager
				bullet.Image=Content.GetImage( "asset::bullet.png" )
				bullet.speed=8
				bullet.X=X+40-bullet.speed
				bullet.Y=Y
	
				bullet.ScoreSystem=New ScoreSystem()
				bullet.CollisionRead=True
				bullet.ScoreCollector=Self
	
			Endif

		Else

			fireDelayCounter-=1

		Endif

		Frame+=.25
		Frame=Frame Mod Frames

	End

End

Class PyroDemo Extends Window

	Method New()

		explosion=New Emitter( "asset::explosion.txt" )
		smoke=New Emitter( "asset::smoke.txt" )

		scene=New Scene( Self )
'		scene.AmbientLight=Color.White

		scene.CollisionMonitor=New CollisionMonitor()

		camera=New Camera( scene )
		camera.ClearColor=New Color( .25,0,0,1 )
'		camera.Visible=False

		layer=New Layer()
		layer.Scene=scene

		player=New Player()
		player.Layer=layer
		player.TaskManager=layer.TaskManager
		player.Images=New Image[]( Image.Load( "asset::p10000.png" ),Image.Load( "asset::p10001.png" ) )
		player.Name="player"
		player.X=96
		player.Y=240

		' Player score system settings:
		player.ScoreSystem=New ScoreSystem()	' Create score system.
		player.CollisionRead=True				' Enable the detection of collisions ( collision reader ).
		player.CollisionWrite=True				' Makes player detectable for collision readers.

		attacker=New Attacker()
		attacker.Layer=layer
		attacker.TaskManager=scene.TaskManager
		attacker.Images=New Image[]( Image.Load( "asset::p20000.png" ),Image.Load( "asset::p20001.png" ) )
		attacker.Name="attacker"
		attacker.X=640-96
		attacker.Y=240
		attacker.FlippedX=-1

		' Attacker score system settings:
		attacker.ScoreSystem=New ScoreSystem()	' Create score system.
		attacker.CollisionWrite=True			' Makes player detectable for collision readers ( player has a collision reader ).

	End

	Method OnRender( canvas:Canvas ) Override

		scene.Update()

		App.RequestRender()

		scene.Draw( canvas )

	End

End

Function Main()

	New AppInstance
	
	New PyroDemo
	
	App.Run()

End
