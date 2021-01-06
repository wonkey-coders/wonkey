
Namespace std.jsonify

Using std.json
Using std.geom

Function ToJson:JsonValue( rect:Recti )
	Return New JsonArray( New JsonValue[]( New JsonNumber( rect.min.x ),New JsonNumber( rect.min.y ),New JsonNumber( rect.max.x ),New JsonNumber( rect.max.y ) ) )
End
	
Function ToRecti:Recti( jvalue:JsonValue )
	Local jarr:=jvalue.ToArray()
	Return New Recti( jarr[0].ToNumber(),jarr[1].ToNumber(),jarr[2].ToNumber(),jarr[3].ToNumber() )
End
