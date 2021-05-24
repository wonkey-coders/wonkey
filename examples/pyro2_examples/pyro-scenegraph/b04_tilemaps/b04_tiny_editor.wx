' Import assets
#Import "../assets/testtiles/"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																											' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																						' Backing global for virtual resolution.

Class PyroExample Extends Window

	Const TILE_SIZE:=32

	Field camera:Camera
	Field id:=0
	Field layer:Layer
	Field scene:Scene																												' Backing global for scene.
	Field tiles:=New Image[170]

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		' Load/create tileset:
		For Local i:=0 To tiles.Length
			tiles[i]=Content.GetImage( "asset::gid_"+( i+1 ) +".png" )
		Next

		Layout="letterbox"

		scene=New Scene( Self )																										' Create a scene.

		camera=New Camera( scene )																									' Setup camera.
		layer=New Layer( scene )																									' Add layer.
		layer.TileSize=New Vec2i( TILE_SIZE,TILE_SIZE )																				' Set the tile width and height.

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																												' Update must be called before Draw!

		' Get the mouse position:
		' ( GetMouseLocation makes sure rotating, scaling etc. is taken into account )
		Local x:Int=layer.GetMouseLocation( camera ).X
		Local y:Int=layer.GetMouseLocation( camera ).Y

		' Set a tile with left mouse:
		If Mouse.ButtonDown ( MouseButton.Left )
			Local tile:=layer.GetLayerObject( camera,x,y )																			' GetLayerObject always returns the one on top!
			If tile tile.Remove()																									' Remove a tile if there is already one ( because Pyro can have multiple tiles in a cell ).
			RoundTilePos( New LayerSprite( layer,tiles[id] ),x,y )																	' Create a new tile and set it at a cell location ( you can use pixel positions but we stick to tile positions )
		End

		' Remove a tile with right mouse:
		If Mouse.ButtonDown ( MouseButton.Right )
			Local tile:=layer.GetLayerObject( camera,x,y )
			If tile tile.Remove()																									' Remove tile.
		End

		' The tile browser:
		If Keyboard.KeyReleased( Key.PageUp ) id+=1
		If Keyboard.KeyReleased( Key.PageDown ) id-=1

		' Make sure array stays within its bounds:
		If id<0 id=0
		If id>tiles.Length-1 id=tiles.Length-1

		scene.Draw( canvas )																										' Draw all scene objects to canvas.

		If Mouse.ButtonDown ( MouseButton.Right )
			canvas.DrawRect( x/TILE_SIZE*TILE_SIZE,y/TILE_SIZE*TILE_SIZE,TILE_SIZE,TILE_SIZE )										' Draw remove 'cursor'.
		Else
			canvas.DrawImage( tiles[id],x/TILE_SIZE*TILE_SIZE,y/TILE_SIZE*TILE_SIZE )												' Draw selected tile.
		Endif

		canvas.DrawText( "Use left / right mouse to plot / delete a tile. Page up / down to select a tile", 8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
