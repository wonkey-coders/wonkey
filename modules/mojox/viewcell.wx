
Namespace mojox

Class ViewCell

	Method New()
	End

	Method New( text:String,icon:Image=null )
		_text=text
		_icon=icon
	End
	
	Property Text:String()
		
		Return _text
		
	Setter( text:String )
		
		_text=text
		
		OnModified()
	End
		
	Property Icon:Image()
		
		Return _icon
		
	Setter( icon:Image )
		
		_icon=icon
		
		OnModified()
	End
	
	Method Measure:Vec2i( style:Style ) Virtual
	
		Local size:=style.MeasureText( _text )
		
		If _icon
			size.x+=_icon.Width+style.Font.TextWidth( " " )
			size.y=Max( size.y,Int( _icon.Height ) )
		Endif
		
		size+=style.Bounds.Size
		
		Return size
	End
	
	Method Render( canvas:Canvas,rect:Recti,style:Style,textGravity:Vec2f ) Virtual
	
		style.Render( canvas,rect )
		
		rect-=style.Bounds
	
		If _icon
			Local y:=(rect.Height-_icon.Height)/2
			style.DrawIcon( canvas,_icon,rect.min.x,rect.min.y+y )
			rect.min.x+=_icon.Width+style.Font.TextWidth( " " )
		Endif

		style.DrawText( canvas,_text,rect,textGravity )
	End
	
	Protected
	
	Method OnModified() Virtual
	End
		
	Private
	
	Field _text:String
	
	Field _icon:Image
	
End
