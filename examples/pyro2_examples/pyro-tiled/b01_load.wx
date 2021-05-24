#Import "assets/"																												' Import assets.

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"
#Import "<pyro-tiled>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..
Using pyro.tiled..

Global virtualResolution:=New Vec2i( 640,480 )																					' Backing global for virtual resolution.

Class PyroExample Extends Window

	Field camera:Camera
	Field scene:Scene																											' Backing global for scene.

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		scene=New Scene( Self )																									' Create a scene.

		camera=New Camera( scene )																								' Setup camera.

		' Create the Tiled loader:
		Local tiledLoader:=New TiledLoader
		tiledLoader.Load( "desert.tmx" )																						' Load the tilemap.
		tiledLoader.Build( scene )																								' Build the tilemap.
		
	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																											' Update must be called before Draw!

		If Keyboard.KeyDown( Key.Left ) camera.X-=8
		If Keyboard.KeyDown( Key.Right ) camera.X+=8
		If Keyboard.KeyDown( Key.Up ) camera.Y-=8
		If Keyboard.KeyDown( Key.Down ) camera.Y+=8

		scene.Draw( canvas )																									' Draw all scene objects to canvas

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
