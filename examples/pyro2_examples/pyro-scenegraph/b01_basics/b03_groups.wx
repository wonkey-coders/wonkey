' Import assets:
#Import "../assets/shield.png"
#Import "../assets/space_monkey.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																			' Import pyro engine.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 800,600 )																' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field group:LayerGroup
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		scene=New Scene( Self )																		' Create a scene.
		Local camera:=New Camera( scene )															' Setup camera.
		Local layer:=New Layer( scene )																' Add layer.

		' The Group class is a simple container to 'merge' different sprites in to one object:
		group=New LayerGroup( layer )																' Create group sprite and set layer.

		' Add a sprite to the group:
		Local spaceMonkey:=New LayerSprite
		spaceMonkey.Image=Content.GetImage( "asset::space_monkey.png" )
		spaceMonkey.Group=group																		' Set group instead of a layer!
		
		' Add a sprite to the group:
		Local shield:=New LayerSprite
		shield.Image=Content.GetImage( "asset::shield.png" )
		shield.Group=group																			' Set group instead of a layer!
		shield.Scale=New Vec2f( 3.25,3.25 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		group.Location=MouseLocation																' Follow the mouse.

		scene.Update()																				' Update must be called before Draw!

		scene.Draw( canvas )																		' Draw all scene objects to canvas.

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
