
'Base class used by Shapes like Tilemap and Background
Class TileGraphics Extends GameGraphics Abstract

	Field tileWidth:Double
	Field tileHeight:Double

	Protected
	Field drawScaleX:Double
	Field drawScaleY:Double
	Field viewLeft:Double
	Field viewTop:Double
	Field viewRight:Double
	Field viewBottom:Double
	
	Field tileStartX:Int
	Field tileStartY:Int
	Field tileEndX:Int
	Field tileEndY:Int

	Method GetVisibleTiles( x:Double, y:Double, scale:Double, camera:Rect<Double> )

		tileWidth = images[0].Width * scale
		tileHeight = images[0].Height * scale

		viewLeft = camera.Left - x
		viewRight = camera.Right - x
		viewTop = camera.Top - y
		viewBottom = camera.Bottom - y

'   		Local margin := 0
		
		tileStartX = Floor( viewLeft / tileWidth )' - margin
		tileStartY = Floor( viewTop / tileHeight )' - margin

		tileEndX = Ceil( viewRight / tileWidth )' + margin
		tileEndY = Ceil( viewBottom / tileHeight )' + margin
	End

End