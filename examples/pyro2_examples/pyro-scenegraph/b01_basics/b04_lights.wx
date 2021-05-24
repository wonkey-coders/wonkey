' Import assets:
#Import "../assets/playniax.png"
#Import "../assets/playniax_N.png"
#Import "../assets/playniax_S.png"
#Import "../assets/background.png"
#Import "../assets/background_N.png"
#Import "../assets/background_S.png"
#Import "../assets/light.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																														' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																											' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field light:LayerSprite
	Field logo:LayerSprite
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		scene=New Scene( Self )																													' Create a scene.
		Local camera:=New Camera( scene )																										' Setup camera.
		Local layer:=New Layer( scene )																											' Add layer.
		layer.AmbientLight=New Color( .1,.1,.1,1 )																								' Set ambient light.

		' Create background sprites
		Local background:=New LayerSprite( layer,Content.GetBump( "asset::background.png","asset::background_N.png","asset::background_S.png" ) )
		background.Location=virtualResolution/2																										' Center of the screen.
		
		logo=New LayerSprite( layer,Content.GetBump( "asset::playniax.png","asset::playniax_N.png","asset::playniax_S.png" ) )						' Create a sprite using the Playniax logo.
		logo.Location=virtualResolution/2

		' A light is just a sprite but you need to set lighting on by changing the Type property to 2.
		light=New LayerSprite( layer,Content.GetLight( "asset::light.png" ) )
		light.Type=2																															' LayerSprite now functions as a light! ( 1=normal image by default )
		light.Scale=New Vec2f( 3,3 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		light.Location=MouseLocation																											' Logo at mouse position.

		scene.Update()																															' Update must be called before Draw!

		scene.Draw( canvas )																													' Draw all scene objects to canvas.

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
