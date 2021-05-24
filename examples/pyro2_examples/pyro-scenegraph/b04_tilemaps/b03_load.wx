' Tile load map example:

' Import the Tile map created with Tiled and converted to Pyro with the Pyro 2 Tiled Converter:
#Import "../assets/testtiles/"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																										' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																					' Backing global for virtual resolution.

Class PyroExample Extends Window

	Global scene:Scene																											' Backing global for scene.
	Global tile:LayerObject

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		scene=New Scene( Self )																									' Create a scene.
		Local camera:=New Camera( scene )																						' Setup camera.

		' Load scene ( 'scene.txt' was created with the help of Tiled and the Pyro 2 Tiled Converter ) :
		Local sceneBuilder:=New SceneLoader
		sceneBuilder.Load( "asset::scene.txt" )
		sceneBuilder.Build( scene )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																											' Update must be called before Draw!

		If tile tile.Selected=False																								' Selected mode off.

		' Grab tile from mouse pos:
		Local tiles:=scene.GetLayer(0).GetLayerObjects( Mouse.Location )														' Get layer objects from mouse position.
		If tiles<>Null And tiles.Length>0																						' Check if any are there!
			tile=tiles.Get(0)
			If tile<>Null tile.Selected=True																					' Selected mode on.
			If tile<>Null And tile.GlobalProperties<>Null																		' Tile and has global properties?
				Print "global id="+tile.GlobalProperties.ReadInt( "gid" )														' Get gid property.
			Endif
		Endif

		' Toggle the collision layer:
		If Keyboard.KeyHit( Key.Space )
			scene.GetLayer( 1 ).Enabled=Not scene.GetLayer( 1 ).Enabled
		Endif

		scene.Draw( canvas )																									' Draw all scene objects to canvas

		canvas.DrawText( "Move the mouse over a tile | Space to toggle collision layer",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
