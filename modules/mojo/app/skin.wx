
Namespace mojo.app

Using std.resource

Class Skin Extends Resource

	Property Image:Image()
		Return _image
	End
	
	Property Bounds:Recti()
		Return _bounds
	End

	Method Draw( canvas:Canvas,rect:Recti )
	
		Local x0:=rect.Left
		Local x1:=rect.Left+_x1
		Local x2:=rect.Right-(_x3-_x2)
		Local x3:=rect.Right
		
		Local y0:=rect.Top
		Local y1:=rect.Top+_y1
		Local y2:=rect.Bottom-(_y3-_y2)
		Local y3:=rect.Bottom
		
		canvas.DrawRect( x0,y0,x1-x0,y1-y0,_image,_x0,_y0,_x1-_x0,_y1-_y0 )
		canvas.DrawRect( x1,y0,x2-x1,y1-y0,_image,_x1,_y0,_x2-_x1,_y1-_y0 )
		canvas.DrawRect( x2,y0,x3-x2,y1-y0,_image,_x2,_y0,_x3-_x2,_y1-_y0 )
		
		canvas.DrawRect( x0,y1,x1-x0,y2-y1,_image,_x0,_y1,_x1-_x0,_y2-_y1 )
		canvas.DrawRect( x1,y1,x2-x1,y2-y1,_image,_x1,_y1,_x2-_x1,_y2-_y1 )
		canvas.DrawRect( x2,y1,x3-x2,y2-y1,_image,_x2,_y1,_x3-_x2,_y2-_y1 )
		
		canvas.DrawRect( x0,y2,x1-x0,y3-y2,_image,_x0,_y2,_x1-_x0,_y3-_y2 )
		canvas.DrawRect( x1,y2,x2-x1,y3-y2,_image,_x1,_y2,_x2-_x1,_y3-_y2 )
		canvas.DrawRect( x2,y2,x3-x2,y3-y2,_image,_x2,_y2,_x3-_x2,_y3-_y2 )
	
	End

	Function Load:Skin( path:String )
	
		Local pixmap:=Pixmap.Load( path,,True )
		If Not pixmap Return Null
		
		Return New Skin( pixmap )
	End
	
	Protected
	
	Method OnDiscard() Override
		_image=Null
	End
	
	Private
	
	Field _image:Image
	
	Field _bounds:Recti
	
	Field _x0:Int,_x1:Int,_x2:Int,_x3:Int
	Field _y0:Int,_y1:Int,_y2:Int,_y3:Int
	
	Method New( pixmap:Pixmap )
	
		Local stretch:Recti
		Local padding:Recti
	
		For Local x:=1 Until pixmap.Width-1
			Local p:=pixmap.GetPixelARGB( x,0 )
			If p=UInt( $ff000000 )
				If Not stretch.min.x stretch.min.x=x
				stretch.max.x=x+1
			Endif
			p=pixmap.GetPixelARGB( x,pixmap.Height-1 )
			If p=UInt( $ff000000 )
				If Not padding.min.x padding.min.x=x
				padding.max.x=x+1
			Endif
		Next
		
		For Local y:=1 Until pixmap.Height-1
			Local p:=pixmap.GetPixelARGB( 0,y )
			If p=UInt( $ff000000 )
				If Not stretch.min.y stretch.min.y=y
				stretch.max.y=y+1
			Endif
			p=pixmap.GetPixelARGB( pixmap.Width-1,y )
			If p=UInt( $ff000000 )
				If Not padding.min.y padding.min.y=y
				padding.max.y=y+1
			Endif
		Next
		
		If stretch.min.x And stretch.min.y
			pixmap=pixmap.Window( 1,1,pixmap.Width-2,pixmap.Height-2 ).Copy()
			If Not padding.min.x Or Not padding.min.y padding=stretch
			stretch-=New Vec2i( 1,1 )
			padding-=New Vec2i( 1,1 )
		Else
			stretch=New Recti( pixmap.Width/2,pixmap.Height/2,pixmap.Width*2+1,pixmap.Height*2+1 )
			padding=stretch
		Endif
		
		_x0=0
		_x1=stretch.min.x
		_x2=stretch.max.x
		_x3=pixmap.Width
		
		_y0=0
		_y1=stretch.min.y
		_y2=stretch.max.y
		_y3=pixmap.Height

		_bounds=New Recti( -padding.min.x,-padding.min.y,_x3-padding.max.x,_y3-padding.max.y )
		
		_image=New Image( pixmap )
	End
End

Class ResourceManager Extension

	Method OpenSkin:Skin( path:String )
	
		Local slug:="Skin:name="+StripDir( StripExt( path ) )
		
		Local skin:=Cast<Skin>( OpenResource( slug ) )
		If skin Return skin
		
		Local pixmap:=OpenPixmap( path,,True )
		If pixmap skin=New Skin( pixmap )

		AddResource( slug,skin )
		Return skin
	End

End
