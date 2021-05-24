' Import assets:
#Import "../assets/background.png"
#Import "../assets/playniax.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																						' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																	' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field camera:Camera
	Field logo:=New LayerSprite[2]
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		' To use sprites you need to setup the scene with a camera and atleast 1 layer:
		scene=New Scene( Self )																					' Create a scene.
		camera=New Camera( scene )																				' Setup camera.
		Local layer:=New Layer( scene )																			' Add layer.

		' Create the background sprite:
		' (  Note that the content manager is used to load the images but Image.Load can also be used instead )
		Local background:=New LayerSprite( layer,Content.GetImage( "asset::background.png" ) )
		background.Location=virtualResolution/2																	' Center of the screen.
		
		' Create a sprite:
		logo[0]=New LayerSprite( layer,Content.GetImage( "asset::playniax.png" ) )
		logo[0].Location=virtualResolution*.25
		
		' Create a second sprite:
		logo[1]=New LayerSprite( layer,Content.GetImage( "asset::playniax.png" ) )
		logo[1].Location=virtualResolution*.75
		logo[1].Tattooed=True

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		logo[0].Rotation+=.01
		logo[1].Rotation-=.01

		If Mouse.ButtonReleased( MouseButton.Left ) 
			For Local i:=0 Until logo.Length
				If logo[i].Layer And logo[i].PointInside( camera,MouseLocation )
					logo[i].Remove()																				' Remove the sprite.
					If logo[i].Tattooed=True Print "sprite can not be removed!"
				Endif
			Next
		Endif
		
		scene.Update()																								' Update must be called before Draw!

		scene.Draw( canvas )																						' Draw all scene objects to canvas.

		canvas.DrawText( "Click on the logo to remove it ( tattooed one can not be removed )",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
