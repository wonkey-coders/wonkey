
Class Area<T>

	Private
	
	Field _vec:Vec2<T>
	Field _width:T
	Field _height:T	
	Field _handle := New Vec2f( 0.5, 0.5 )	'Values are from 0,0 (Left, Top ) to 1,1 (Right, Bottom )

	Field _x0:T, _y0:T, _x1:T, _y1:T		'corners
	Field _pivotX:T							'width * handle.X
	Field _pivotY:T							'height * handle.Y
	
	Field _rect:Rect<T>

	Public

	'*************************  Properties  ****************************
	
	Property X:T()
		Return _vec.X
	Setter( x:T )
		_vec.X = x
		Self._x0 = x - _pivotX
		Self._x1 = _x0 + _width
	End
	
	Property Y:T()
		Return _vec.Y
	Setter( y:T )
		_vec.Y = y
		Self._y0 = y - _pivotY
		Self._y1 = _y0 + _height
	End

	Property Width:T()
		Return _width
	Setter( w:T )
		Self._width = w
		_pivotX = ( _width * _handle.x )
		Self._x0 = _vec.X - _pivotX
		Self._x1 = _x0 + _width
	End
	
	Property Height:T()
		Return _height
	Setter( h:T )
		Self._height = h
		_pivotY = ( _height * _handle.y )
		Self._y0 = _vec.Y - _pivotY
		Self._y1 = _y0 + _height
	End

	Property Left:T()
		Return _x0
	End
	
	Property Right:T()
		Return _x1
	End
	
	Property Top:T()
		Return _y0
	End
	
	Property Bottom:T()
		Return _y1
	End
	
	Property Handle:Vec2f()
		Return _handle
	End
	
	Property Rect:Rect<T>()
		_rect.Left = _x0
		_rect.Top = _y0
		_rect.Right = _x1
		_rect.Bottom = _y1		
		Return _rect
	End

	'**************************  Public Methods  ****************************

	Method New( x:T, y:T, _width:T, _height:T )
		X = x
		Y = y
		Size( _width, _height )
		_rect = New Rect<T>
	End
	
	Method Position( x:T, y:T )
		X = x
		Y = y
	End

	Method Size(_width:T, _height:T )
		Self._width = _width
		Self._height = _height
		_pivotX = ( _width * _handle.x )
		_pivotY = ( _height * _handle.y )
		Self._x0 = _vec.X - _pivotX
		Self._y0 = _vec.Y - _pivotY
		Self._x1 = _x0 + _width
		Self._y1 = _y0 + _height
	End
	
	Method SetHandle( pX:Float, pY:Float )
		_handle.X = pX
		_handle.Y = pY
		_pivotX = pX * _width
		_pivotY = pY * _height
		Self._x0 = _vec.X - _pivotX
		Self._y0 = _vec.Y - _pivotY
		Self._x1 = _x0 + _width
		Self._y1 = _y0 + _height
	End
	 
	Method PositionByCorner( _x0:Float, _y0:Float )
		X = _x0 + _pivotX
		Y = _y0 + _pivotY
	End

	Method Move( deltaX:Float, deltaY:Float )
		Position( _vec.X + deltaX, _vec.Y +deltaY )
	End
'   
	Method Contains:Bool(_x:Float, _y:Float)
		If _x > _x0
			If _x < _x1
				If _y > _y0
					If _y < _y1
						Return True
					End
				End
			End
		End
		Return False
	End

	Method Overlaps:Bool( rect:Area )
		If rect._x1 > _x0
			If rect._x0 < _x1
				If rect._y1 > _y0
					If rect._y0 < _y1
						Return True
					End
				End
			End
		End
		Return False
	End
	
	Method ToString:String()
		Return "Area("+_vec.X+","+_vec.Y+"; "+_width+"x"+_height+")"
	End
	

'	Old code, unconverted to M2

'   	Method Copy( other:Vec2<f> )
'   		Self.X = other.X
'   		Self.Y = other.Y
'   		local otherRect := Rec2<T>( other )
'   		If otherRect
'   			Self._pivotX = otherRect._pivotX
'   			Self._pivotY = otherRect._pivotY
'   			Self._width = otherRect.Width
'   			Self._height = otherRect.Height
'   			Self._x0 = x - _pivotX
'   			Self._y0 = y - _pivotY
'   			Self._x1 = _x0 + _width
'   			Self._y1 = _y0 + _height
'   			Self._handle.Copy( otherRect._handle )
'   		End
'   	End

'   	Method SnapToPixel:Void()
'   		x = Round( x )
'   		y = Round( y )
'   		_width = Round( _width )
'   		_height = Round( _height )
'   		_pivotX = Round( _width * _handle.x )
'   		_pivotY = Round( _height * _handle.y )
'   		_x0 = Round( x - _pivotX )
'   		_y0 = Round( y - _pivotY )
'   		_x1 = Round( _x0 + _width )
'   		_y1 = Round( _y0 + _height )
'   	End
'   
'   	Function Round:Float(number:Float)
'   		If number - Int(number) > 0.5 Then Return Ceil(number)
'   		Return Floor(number)
'   	End

End
