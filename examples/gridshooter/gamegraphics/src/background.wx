
#Import "tilegraphics"

Class Background Extends TileGraphics

	Field total:Int

	Method New( path:String)
		
		Local atlasTextture := Texture.Load( path,Null )
		Assert( atlasTextture, " ~n ~nGameGraphics: Image " + path + " not found.~n ~n" )
		images = New Image[]( New Image( atlasTextture ) )
	End
	
	Method Draw( canvas:Canvas, x:Double, y:Double, scale:Double, camera:Rect<Double> )

		total = 0

		GetVisibleTiles( x, y, scale, camera )
		
		For Local tY := tileStartY Until tileEndY
			For Local tX := tileStartX Until tileEndX
				local absX := ( tX * tileWidth ) + x
				local absY := ( tY * tileHeight ) + y
				If images[0]
					total += 1
					canvas.DrawImage( images[0], absX, absY, 0, scale, scale )
					If debug
						DrawRectOutline( canvas, absX, absY, tileWidth, tileHeight )
						canvas.DrawText( tX + "," + tY, absX + 4, absY + 4 )
					End
				End
			Next
		Next
	End
	
	Method ToString:String()
		Local t := ""
		t += ( "Background: " + tileStartX + "," + tileStartY + "; " + tileEndX + "," + tileEndY + "; " )
		t += ( "Total tiles: " + total )
		Return t
	End
	
End