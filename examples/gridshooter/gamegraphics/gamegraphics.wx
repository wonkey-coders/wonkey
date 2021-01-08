
#Import "<mojo>"
#Import "src/sprite"
#Import "src/background"

Using mojo..
Using std..

Class GameGraphics Abstract

	Field images		:Image[]	'The array containing all frames
	Field debug := False
		
	Protected
	Field _handle:= New Vec2f
	
	'************************************* Public Properties *************************************
	
	Public
	
	'Sets the handles in all sub-images
	Property Handle:Vec2f()
		Return _handle
	Setter( handle:Vec2f )
		_handle = handle
		For Local i := Eachin images
			i.Handle = _handle
		Next
	End

	Property Width:Double()
		Return images[0].Width
	End

	Property Height:Double()
		Return images[0].Height
	End
	
	'************************************* Public Methods *************************************
	
	'Loads an array of Images from a sprite sheet
	Method LoadFrames:Image[] ( path:String, numFrames:Int, cellWidth:Int, cellHeight:Int, filter:Bool = True, padded:Bool = False )
	
		Local atlasTextture := Texture.Load( path, Null )
		Assert( atlasTextture, " ~n ~nGameGraphics: Image " + path + " not found.~n ~n" )
		
		Local atlasImg := New Image( atlasTextture )
		Local imgs := New Image[ numFrames ]

		If cellHeight = atlasImg.Height
			Local x := 0
			Local width := cellWidth
			If padded
				x += 1
				width -= 2
			End
			For Local i := 0 Until numFrames
				Local x0 := i * cellWidth + x
				Local y0 := 0
				imgs[i] = New Image( atlasImg, New Recti( x0, y0, x0 + cellWidth, cellHeight ) )
			Next
		Else
			Local x:= 0
			Local width:= cellWidth
			Local y:= 0
			Local height:= cellHeight
			Local columns:= atlasImg.Width / width
			If padded
				x += 1
				y += 1
				width -= 2
				height -= 2
			End If
			For Local i:= 0 Until numFrames
				Local fx := i Mod columns * cellWidth
				Local fy := i / columns * cellHeight
				imgs[i] = New Image( atlasImg, New Recti( fx + x, fy + y, fx + cellWidth, fy + cellHeight ) )
			Next
		Endif
		atlasImg = Null
		Return imgs
	End
	
	
	Method DrawOutline( canvas:Canvas, x:Float, y:Float, width:Float, height:Float, rz:Float = 0, sx:Float = 1.0, sy:Float = 1.0 )
		Local matrix:= canvas.Matrix
		canvas.Translate( x, y )
		canvas.Rotate( rz )
		canvas.Scale( sx,sy )
		DrawRectOutline( canvas, -( width * Handle.X ), -( height * Handle.Y ), width, height )
		canvas.Matrix=matrix
	End
	
	
	
	'************************************* Class Functions *************************************

	Function DrawRectOutline:Void(canvas:Canvas, left:Int, top:Int, width:Int, height:Int )
		canvas.DrawLine( left, top, left+width, top )
		canvas.DrawLine( left, top, left ,top+height )
		canvas.DrawLine( left, top+height, left+width, top+height )
		canvas.DrawLine( left+width, top, left+width, top+height )
	End

End