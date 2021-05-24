#Import "../assets/light.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-scenegraph>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Class PyroExample Extends Window

	Field camera:Camera
	Field layer:Layer
	Field particleImage:Image
	Field scene:Scene

	Method New()

		particleImage=Image.Load( "asset::light.png" )

		scene=New Scene( Self )
		camera=New Camera( scene )
		camera.ClearColor=New Color( .25,0,0,1 )
		layer=New Layer( scene )

	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		If Mouse.ButtonDown( MouseButton.Left )

			' Create particles:
			Local particle:=New Particle( layer,particleImage )
			particle.TaskManager=scene.TaskManager
			particle.BlendMode=BlendMode.Additive

			particle.Location=MouseLocation

			particle.TimeToLive=Rnd( 500,1750 )
			particle.Acceleration=New Vec2f( 1,0 )

			particle.Drag=New Vec2f( .99,.99 )

			particle.Velocity=New Vec2f( Rnd( -8,8 ),Rnd( -8,8 ) )

			Local scale:=Rnd( .25,.75 )

			particle.Scale=New Vec2f( scale,scale )
		
			Local targetScale:=Rnd( 1,3 )

			Local r:=Rnd( .75,1 )
			Local g:=Rnd( .5,.75 )
			Local b:=Rnd( 0,.5 )

			particle.TargetScale=New Vec2f( targetScale,targetScale )

			particle.Color=New Color( r,g,b )

		End

		scene.Update()

		scene.Draw( canvas )

		canvas.DrawText( "Press left mouse for particle effect",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
