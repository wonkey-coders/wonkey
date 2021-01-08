#Import "PoolMod"

Const RTA:Float = 180.0/Pi
Const ATR:Float = Pi/180.0
Const INVALID_DISTANCE:Float = 100000000
Const DEVICE_WIDTH:Int = 640
Const DEVICE_HEIGHT:Int = 480

'***********************************************************************************
'
'		renders a circle at a distance relative to a ball current position
'
'***********************************************************************************

Function RenderAtDistance:Void(canvas:Canvas,ball:Ball,distance:Float)
	If Not ball.image
		RenderCircle(canvas,ball.P.x+ball.V.x*distance,ball.P.y+ball.V.y*distance,ball.radius)
	Else
		canvas.DrawImage(ball.image,ball.P.x+ball.V.x*distance,ball.P.y+ball.V.y*distance)
	Endif
End Function

''***********************************************************************************
'
'		renders an arc at position x,y and radius,
'		starting angle, and ending angle.
'
'************************************************************************************

Function RenderArc:Void(canvas:Canvas,x:Float, y:Float, radius:Float, startAngle:Float, endAngle:Float)
	
	'If angles are equal nothing to draw
	If startAngle = endAngle Then Return
	
	'make the arc clockwise
	If startAngle > endAngle
		' swap angles if order is counter-clockwise
		Local ta:Float = endAngle
		endAngle = startAngle
		startAngle = ta
	Endif
	
	'number of degrees to render
	Local angle:Float = endAngle - startAngle
	
	' no more than 360 degrees to render
	If angle > 360.0 angle = 360.0
	
	' set the step to advance one unit at a tme
	Local stp:Float = 1.0/(RTA * radius)
	
	'set the accumulator to the starting angle
	Local AccumAngle:Float = startAngle
	
	' repeat until the arc is completely drawn
	While AccumAngle < (startAngle+angle)
		
		'draw a pixel around the arc
		canvas.DrawPoint(x + Cos(AccumAngle*ATR) * radius, y + Sin(AccumAngle*ATR) * radius)
		
		'advance to next angle
		AccumAngle += stp
	
	Wend
End Function 

'***********************************************************************************
'
'		draws a circle at x,y and radius
'
'***********************************************************************************

Function RenderCircle:Void(canvas:Canvas,x:Float,y:Float,radius:Float)
		'start angle
		Local angle:Float = 0.0
		
		' distance between each point
		Local stp:Float = 1.0/(RTA * radius)
	
		'rotate upto 360 degrees
		While angle < 360.0
	
			canvas.DrawPoint(x + Cos(angle*ATR) * radius, y + Sin(angle*ATR) * radius)
			
			'increment the position to draw the next point
			angle += stp
	
		Wend

End Function

'***********************************************************************************
'
'	Draws a line with of specific width
'
'
'***********************************************************************************

Function DrawLine_W:Void(canvas:Canvas,XPos:Float,YPos:Float,XPos2:Float,YPos2:Float,Thickness:Float=3,roundedEnds:Int=False)
	
	Local Coords:Float[] = New Float[8] 
	
	Local vx:Float = XPos2 - XPos
	Local vy:Float = YPos2 - YPos
	
	Local Angle:Float = ATan2(vy,vx)
	
	Local c:Float = Cos(Angle*ATR)
	Local s:Float = Sin(Angle*ATR)
	Local LineLength:Float=vx*c+vy*s
	
	Local cl:Float = LineLength*c
	Local sl:Float = LineLength*s
	
	Local r:Float = Thickness/2.0
	
	Local sr:Float = s*r
	Local cr:Float = c*r
	
	'Left top coords
	Coords[0]=XPos+sr
	Coords[1]=YPos-cr
	
	'Right top coords
	Coords[2]=cl+XPos+sr
	Coords[3]=sl+YPos-cr
	
	'Right bottom coords
	Coords[4]=cl-sr+XPos
	Coords[5]=sl+cr+YPos
	
	'Left bottom coords
	Coords[6]=XPos-sr
	Coords[7]=YPos+cr
	
	canvas.DrawPoly(Coords)	
	
	If roundedEnds = True	
		canvas.DrawCircle(XPos,YPos,r)
		canvas.DrawCircle(XPos2,YPos2,r)
	Endif

End Function


Function LoadFrames:Image[](img:Image,x:Int,y:Int,width:Int,height:Int,count:Int)
	Local frames:Image[] = New Image[count]
	Local index:Int = 0
	Local posx:Int = x
	Local posy:Int = y
	While index < count
		If posx > (img.Width-width)
			Print posx
			posx = 0
			posy += height	
		Endif
		frames[index] = New Image(img,posx,posy,width,height)
		index += 1
		posx += width
	Wend
	Return frames
End Function


Class sysFont
	Global font:Image[]
	Global width:Int
	Global height:Int
	Global firstChar:Int
	
	Function Set(image:Image[],first:Int)
		font = image
		width = image[0].Width
		height = image[0].Height
	End Function
	
	Function Draw(canvas:Canvas,text:String,x:Float,y:Float)
		For Local i:Int=0 Until text.Length
			Local ch:Int=text[i]-firstChar
			If ch>=0 And ch<font.Length
				canvas.DrawImage(font[ch],x+i*width,y)
			Endif
		Next		
	End Function
	
End Class

Function SetFont( font:Image[],firstChar:Int=32 )
	sysFont.Set(font,firstChar)
End

Function GetFont:Image[]()
	Return sysFont.font
End

Function TextWidth:Float( text:string )
	If sysFont.font 
		Return text.Length * sysFont.width
	Endif
	RuntimeError("No Font Available")
	Return 0
End

Function TextHeight:Float()
	If sysFont.font 
		Return sysFont.height
	Endif
	RuntimeError("No Font Available")
	Return 0
End

Function FontHeight:Float()
	If sysFont.font 
		Return sysFont.height
	Endif
	RuntimeError("No Font Available")
	Return 0
End

Function DrawText(canvas:Canvas,text:String,x:Float,y:Float )
	sysFont.Draw(canvas,text,x,y)
End


Class PVector2D
	Field x:Float
	Field y:Float
	
	Method New()
	End Method
	
	Method New(x:Float,y:Float)
		Set(x,y)
	End Method
	
	Method New(x1:Float,y1:Float,x2:Float,y2:Float)
		Set(x2-x1,y2-y1)
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
	
	Method LeftNormal()
		Local n:Float = y
		y = -x 
		x = n
	End Method
	
	Method RightNormal()
		Local n:Float = y
		y = x
		x = -n
	End Method
	
	Method Normalize:PVector2D()
		Divide(Magnitude())
		Return Self
	End Method
		
	Method GetAngle:Float()
		Return ATan2(y,x)
	End Method
	
	Method ToString:String()
		Return x+"  "+y
	End Method
	
	Method Draw:Void(canvas:Canvas,x:Float,y:Float)
		canvas.DrawLine(x,y,x+x,y+y)
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

