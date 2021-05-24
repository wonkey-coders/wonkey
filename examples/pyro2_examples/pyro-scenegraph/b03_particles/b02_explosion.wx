#Import "../assets/light.png"
#Import "../assets/black_smoke.png"
#Import "../assets/blastwave.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-scenegraph>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global camera:Camera
Global layer:Layer
Global scene:Scene

Class FX

	Function BlackSmoke( layer:Layer,location:Vec2f,delay:Int=0 )

		Local image:=Content.GetImage( "asset::black_smoke.png" )

		For Local c:=0 Until 10
	
			Local particle:=New Particle( layer,image )
			particle.TaskManager=scene.TaskManager
			particle.Location=location
			particle.Drag=New Vec2f( .9,.9 )
			particle.TimeToLive=Rnd( 1000,1600 )
			particle.Delay=delay+Rnd( 500 )
	
			Local angle:=Rnd( 359 )/360.0*TwoPi
			Local scale:=Rnd( .1,.5 )
			Local targetScale:=Rnd( .5,1.5 )
			Local velocity:=Rnd( 1,7 )
	
			particle.Scale=New Vec2f( scale,scale )
			particle.TargetScale=New Vec2f( targetScale,targetScale )
			particle.Velocity=New Vec2f( Cos( angle )*velocity,Sin( angle )*velocity )
	
		Next

	End

	Function BlastWave:Particle( layer:Layer,location:Vec2f,delay:Int=0,scale:Float=1,timeToLive:Int=1000 )

		Local particle:=New Particle( layer,Content.GetImage( "asset::blastwave.png" ) )
		particle.TaskManager=scene.TaskManager
		particle.Location=location
		particle.Scale=New Vec2f( 0,0 )
		particle.TargetScale=New Vec2f( scale,scale )
		particle.TimeToLive=timeToLive
		particle.Delay=delay+Rnd( 300 )

		Return particle

	End

	Function Explosion( layer:Layer,location:Vec2f,delay:Int=0 )

		Local image:=Content.GetImage( "asset::light.png" )

		For Local c:=0 Until 5
	
			Local particle:=New Particle( layer,image )
			particle.TaskManager=scene.TaskManager
			particle.BlendMode=BlendMode.Additive
			particle.Location=location

			Local r:=Rnd( .75,1 )
			Local g:=Rnd( .5,.75 )
			Local b:=Rnd( .1,.25 )
			
			particle.Color=New Color( r,g,b )

			particle.Drag=New Vec2f( .9,.9 )
			particle.TimeToLive=Rnd( 250,1000 )
			particle.Delay=delay+Rnd( 500 )

			Local angle:=Rnd( 0,359 )/360.0*TwoPi
			Local scale:=Rnd( .05,.25 )
			Local velocity:=Rnd( 1,4 )
	
			particle.Scale=New Vec2f( scale,scale )

			particle.Velocity=New Vec2f( Cos( angle )*velocity,Sin( angle )*velocity )

		Next

	End

End

Class PyroExample Extends Window

	Method New()

		scene=New Scene( Self )
		camera=New Camera( scene )
		camera.ClearColor=New Color( .25,0,0,1 )
		layer=New Layer( scene )

	End

	Method OnRender( canvas:Canvas ) Override

		App.RequestRender()

		scene.Update()

		If Mouse.ButtonHit( MouseButton.Left )
	
			FX.BlastWave( layer,MouseLocation )
			FX.BlackSmoke( layer,MouseLocation )
			FX.Explosion( layer,MouseLocation )
	
		Endif

		scene.Draw( canvas )

		canvas.DrawText( "Press left mouse for particle effect",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
