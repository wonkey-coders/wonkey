' Tile properties and global properties example:

' Import assets
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

	Global layer:Layer
	Global scene:Scene																											' Backing global for scene.
	Global tile:LayerObject
	Global tiles:=New Image[5]

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		' Load/create tileset:
		For Local i:=0 Until tiles.Length
			tiles[i]=Content.GetImage( "asset::gid_"+i+".png" )
		Next

		Layout="letterbox"

		scene=New Scene( Self )																									' Create a scene.

		Local camera:=New Camera( scene )																						' Setup camera.
		layer=New Layer( scene )																								' Add layer.
		layer.TileSize=New Vec2i( 32,32 )																						' Set the tile width and height.

		' Create global properties:
		Local globalProperties:=New Config()
		globalProperties.WriteString( "type","tile" )																			' Set a value.
	
		' Plot a tile:
		Local tile1:=New LayerSprite( layer,Content.GetImage( "asset::gid_1.png" ) )
		' Pyro tiles can be at pixel position but for this example we use tile positions:
		ToTilePos( tile1,2,2 )
		' Give the tile some properties:
		tile1.Properties=New Config()
		tile1.Properties.WriteString( "grass","green" )
		tile1.GlobalProperties=globalProperties
		
		' Plot another tile:
		Local tile2:=New LayerSprite( layer,Content.GetImage( "asset::gid_10.png" ) )
		ToTilePos( tile2,5,8 )
		' Give the tile some properties:
		tile2.Properties=New Config()
		tile2.Properties.WriteString( "poison","orange" )
		tile2.Properties.WriteBool( "kill",True )
		tile2.GlobalProperties=globalProperties

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																											' Update must be called before Draw!

		' Read keys:
		Local key_P:=Keyboard.KeyHit( Key.P )
		Local key_G:=Keyboard.KeyHit( Key.G )

		If tile tile.Selected=False																								' Selected mode off.

		' Grab tile from mouse pos:
		Local tiles:=layer.GetLayerObjects( Mouse.Location )																	' Get layer objects from mouse position.
		If tiles<>Null And tiles.Length>0																						' Check if any are there!
			tile=tiles.Get(0)
			If tile<>Null tile.Selected=True																					' Selected mode on.
			If tile<>Null And tile.Properties<>Null																				' Tile and has properties?
				If key_P Print tile.Properties.ToString() ; Print ""															' Show properties.
				If key_G Print tile.GlobalProperties.ToString() ; Print ""														' Show global properties.
			Endif
		Endif

		scene.Draw( canvas )																									' Draw all scene objects to canvas

		canvas.DrawText( "Move mouse over a tile and press key P for properties or key G for global properties",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
