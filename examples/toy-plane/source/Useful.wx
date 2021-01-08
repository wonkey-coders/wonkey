
Namespace useful

Const degToRad :Double = Pi / 180.0
Const radToDeg :Double = 180.0 / Pi
Const one :Double = 1.0					'This is just to ensure 1.0 is a double, not float

'*********************** Math functions ***********************

Function DeltaMultiply:Double( value:Double, multiplier:Double, delta:Double )
	Local attenuation := ( one - ( ( one - multiplier ) * delta ) )
	Return( value * attenuation )
End


Function DeltaMultiply:Vec2<Double>( vec:Vec2<Double>, multiplier:Double, delta:Double )
	Local attenuation := ( one - ( ( one - multiplier ) * delta ) )
	Return( vec * attenuation )
End


Function Smooth:Double( source:Double, target:Double, rate:Double = 5.0, delta:Double = 1.0 )
	If rate <= 1.0 Then Return target
	Return source + ( (source - target) / (-rate / delta) )
End

'   Function Lerp:Double( source:Double, target:Double, rate:Double = 2.0, delta:Double = 1.0 )
'   End


Function Quantize:Double( number:Double, size:Double )
	If size Then Return Round( number / size ) * size
	Return number
End


Function QuantizeDown:Double( number:Double, size:Double )		'Snaps to nearest lower value multiple of size
	If size Then Return Floor( number / size ) * size
	Return number
End

Function QuantizeUp:Double( number:Double, size:Double )		'Snaps to nearest upper value multiple of size
	If size Then Return Ceil( number / size ) * size
	Return number
End


'Function AngleBetween:Double(x1:Double, y1:Double, x2:Double, y2:Double)
'	Return ATan2((x2 - x1), (y2 - y1))' * radToDeg
'End


Function AngleBetween:Double(x1:Double, y1:Double, x2:Double, y2:Double)
	Return ATan2((y2 - y1), (x2 - x1)) * radToDeg
End


Function RadToDeg:Double ( rad:Double )
	Return rad * radToDeg	'( 180.0 / Pi )
End


Function DegToRad:Double( deg:Double )
	Return deg * degToRad	'( Pi / 180.0 )
End


Function NearestPow:Int( number:Int )
	Return Pow( 2, Ceil( Log( number )/Log( 2 ) ) )
End


Function Truncate:String( number:Double, decimals:Int = 1 )
	Local arr:String[] = String(number).Split(".")
	If arr.Length > 1
		Return arr[0] + "." + arr[1].Left( decimals )
	Else
		Return arr[0]
	End
End

Function Truncate:String( vec:Vec2<Float>, decimals:Int = 1 )
	Return Truncate( vec.X, decimals ) + ", " + Truncate( vec.Y, decimals )
End

Function Truncate:String( vec:Vec3<Float>, decimals:Int = 1 )
	Return Truncate( vec.X, decimals ) + ", " + Truncate( vec.Y, decimals ) + ", " + Truncate( vec.Z, decimals )
End




'*********************** Array functions ***********************

Function ArrayContains<T>:Bool( arr:T[], value:T )
	For local n := 0 Until arr.Length
		If arr[ n ] = value Then Return True
	End
	Return False
End
