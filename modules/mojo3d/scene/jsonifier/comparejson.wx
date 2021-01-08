Namespace mojo3d.jsonifier

Function CompareJson:Int( x:JsonObject,y:JsonValue )
	If y=JsonValue.NullValue Return 1
	Local r:=Cast<JsonObject>( y )
	If Not r Return 1
	Local xit:=x.All(),rit:=r.All()
	While Not xit.AtEnd And Not rit.AtEnd
		Local cmp:=xit.Current.Key<=>rit.Current.Key
		If cmp Return cmp
		cmp=CompareJson( xit.Current.Value,rit.Current.Value )
		If cmp Return cmp
		xit.Bump()
		rit.Bump()
	Wend
	Return x.Count()<=>r.Count()
End

Function CompareJson:Int( x:JsonArray,y:JsonValue )
	If y=JsonValue.NullValue Or y.IsBool Or y.IsNumber Or y.IsString Return 1
	Local r:=Cast<JsonArray>( y )
	If Not r Return -1
	For Local i:=0 Until Min( x.Length,r.Length )
		Local cmp:=CompareJson( x[i],r[i] )
		If cmp Return cmp
	Next
	Return x.Length<=>r.Length
End

Function CompareJson:Int( x:JsonString,y:JsonValue )
	If y=JsonValue.NullValue Or y.IsBool Or y.IsNumber Return 1
	Local r:=Cast<JsonString>( y )
	Return r ? x.Data<=>r.Data Else -1
End

Function CompareJson:Int( x:JsonNumber,y:JsonValue )
	If y=JsonValue.NullValue Or y.IsBool Return 1
	Local r:=Cast<JsonNumber>( y )
	Return r ? x.Data<=>r.Data Else -1
End

Function CompareJson:Int( x:JsonBool,y:JsonValue )
	If y=JsonValue.NullValue Return 1
	Local r:=Cast<JsonBool>( y )
	Return r ? x.Data<=>r.Data Else -1
End

Function CompareJson:Int( x:JsonValue,y:JsonValue )
	If x=JsonValue.NullValue Return y=JsonValue.NullValue ? 0 Else -1
	Local jbool:=Cast<JsonBool>( x )
	If jbool Return CompareJson( jbool,y )
	Local jnumber:=Cast<JsonNumber>( x )
	If jnumber Return CompareJson( jnumber,y )
	Local jstring:=Cast<JsonString>( x )
	If jstring Return CompareJson( jstring,y )
	local jarray:=Cast<JsonArray>( x )
	If jarray Return CompareJson( jarray,y )
	Local jobj:=Cast<JsonObject>( x )
	If jobj Return CompareJson( jobj,y )
	RuntimeError( "TODO" )
	Return 0
End

#rem
Function RndJson:JsonValue( range:Int=6 )
	
	Select Int( Rnd( range ) )
	Case 0 
		Return JsonValue.NullValue
	Case 1 
		Return Rnd()>.5 ? JsonBool.TrueValue Else JsonBool.FalseValue
	Case 2 
		Return New JsonNumber( Rnd(10000) )
	Case 3 
		Return New JsonString( Rnd(10000) )
	Case 4
		Local data:=New Stack<JsonValue>( Rnd( 10,20 ) )
		For Local i:=0 Until data.Length
			data[i]=RndJson( 4 )
		Next
		Return New JsonArray( data )
	Case 5
		Local data:=New StringMap<JsonValue>
		For Local i:=0 Until Rnd( 10,20 )
			data[ Rnd(100) ]=RndJson( 4 )
		Next
		Return New JsonObject( data )
	End
	Return Null
End

Function Main()
	
	Print "Start..."
	
	For Local i:=1 To 100000
		
		Local x:=RndJson()
		Local y:=RndJson()
		
		Local cmp1:=CompareJson( x,y )
		Local cmp2:=CompareJson( y,x )
		
		If cmp1<0 Assert( cmp2>=0 )
		If cmp1=0 Assert( cmp2 =0 )
		If cmp1>0 Assert( cmp2<=0 )
	End
	
	Print "Success!"
		
End
#end