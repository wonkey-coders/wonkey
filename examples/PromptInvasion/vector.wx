#Import "<mojo>"
#Import "<std>"

Using mojo..
Using std..

Class PVector2D
	Field x:Float
	Field y:Float
	
	Method New()
	End method
	
	Method New(x:Float,y:Float)
		Set(x,y)
	End Method
	
	Method New(v:PVector2D)
		Set(v)
	End Method
	
	Method Set:PVector2D(v:PVector2D)
		x = v.x
		y = v.y
		Return Self
	End Method

	Method Set:PVector2D(x:Float,y:Float)
		Self.x = x
		Self.y = y
		Return Self
	End Method
		
	Method Add:PVector2D(x:Float,y:Float)
		Self.x += x
		Self.y += y
		Return Self
	End Method
	
	Method Add:PVector2D(v:PVector2D)
		Self.x += v.x
		Self.y += v.y
		Return Self
	End Method
	
	Method Add:PVector2D(value:Float)
		Self.x += value
		Self.y += value
		Return Self
	End Method
	
	Method Subtract:PVector2D(x:Float,y:Float)
		Self.x -= x
		Self.y -= y
		Return Self
	End Method
	
	Method Subtract:PVector2D(v:PVector2D)
		Self.x -= v.x
		Self.y -= v.y
		Return Self
	End Method
	
	Method Subtract:PVector2D(value:Float)
		Self.x -= value
		Self.y -= value
		Return Self
	End Method
	
	Method Multiply:PVector2D(x:Float,y:Float)
		Self.x *= x
		Self.y *= y
		Return Self
	End Method
	
	Method Multiply:PVector2D(v:PVector2D)
		Self.x *= v.x
		Self.y *= v.y
		Return Self
	End Method
	
	Method Multiply:PVector2D(value:Float)
		Self.x *= value
		Self.y *= value
		Return Self
	End Method
	
	Method Divide:PVector2D(x:Float,y:Float)
		Self.x /= x
		Self.y /= y
		Return Self
	End Method
	
	Method Divide:PVector2D(v:PVector2D)
		Self.x /= v.x
		Self.y /= v.y
		Return Self
	End Method
	
	Method Divide:PVector2D(value:Float)
		Self.x /= value
		Self.y /= value
		Return Self
	End Method
	
	Method DotProduct:Float(x:Float,y:Float)
		Return Self.x * x + Self.y * y
	End Method
	
	Method DotProduct:Float(v:PVector2D)
		Return Self.x * v.x + Self.y * v.y
	End Method
	
	Method PerpDotProduct:Float(x:Float,y:Float)
		Return Self.x * y - Self.y * x
	End Method
	
	Method PerpDotProduct:Float(v:PVector2D)
		Return Self.x * v.y - Self.y * v.x
	End Method
	
	Method MagnitudeSquare:Float()
		Return Self.x * Self.x + Self.y * Self.y
	End Method
	
	Method Magnitude:Float()
		Return Sqrt(MagnitudeSquare())
	End Method
	
	Method LeftNormal:PVector2D()
		Local n:Float = y
		y = -x 
		x = n
		Return Self
	End Method
	
	Method RightNormal:PVector2D()
		Local n:Float = y
		y = x
		x = -n
		Return Self
	End Method
	
	Method Normalize:PVector2D()
		Divide(Magnitude())
		Return Self
	End Method
		
	Method GetAngle:Float()
		Return ATan2(y,x)
	End Method
	
	Method Rotate:PVector2D(angle:Float)
		Local c:Float = Cos(angle)
		Local s:Float = Sin(angle)
		Local t:Float = x * c - y * s
		y = y * c + x * s
		x = t
		Return Self		
	End Method
	
	Method ToString:String()
		Return x+", "+y
	End Method
	
	Method Draw:Void(canvas:Canvas,x:Float=0,y:Float=0)
		canvas.DrawLine(x,y,x+Self.x,y+Self.y)
	End Method
	
End Class

Function Projection:PVector2D(this:PVector2D,into:PVector2D,destination:PVector2D=Null)
	
	If destination = Null destination = New PVector2D
		
	Return destination.Set(into).Normalize().Multiply(destination.DotProduct(this))
	
End Function

Function CrossProjection:PVector2D(this:PVector2D,into:PVector2D,destination:PVector2D=Null)
	
	If destination = Null destination = New PVector2D
	
	Return destination.Set(into.y,-into.x).Normalize().Multiply(destination.DotProduct(this))
		
End Function

