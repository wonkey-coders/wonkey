' Tile set and get methods example:

' Pyro tiles are not the classic tiles as you might expect!
' They are just sprites ( or other layer objects ).
' They can be at any ( pixel ) position.

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
	
		' Plot a tile:
		Local tile1:=New LayerSprite( layer,Content.GetImage( "asset::gid_1.png" ) )
		' Pyro tiles can be at pixel position but for this example we use tile positions:
		ToTilePos( tile1,2,2 )
'		RoundTilePos( tile1,32,32 )

		' Plot another tile:
		Local tile2:=New LayerSprite( layer,Content.GetImage( "asset::gid_3.png" ) )
		ToTilePos( tile2,5,8 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																											' Update must be called before Draw!

		If tile tile.Selected=False																								' Selected mode off.

		' Grab tile from mouse pos:
		Local tiles:=layer.GetLayerObjects( Mouse.Location )																	' Get layer objects from mouse position.
		If tiles<>Null And tiles.Length>0																						' Tile?
			tile=tiles.Get(0)
			If tile<>Null tile.Selected=True																					' Selected mode on.
		Endif

		scene.Draw( canvas )																									' Draw all scene objects to canvas

		canvas.DrawText( "Move the mouse over a tile",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
