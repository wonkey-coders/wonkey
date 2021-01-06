
Namespace test

Function F1<T>() Where T Implements INumeric
	Print "F1<T>() INumeric"
End

Function F1<T>() Where T=String
	Print "F1<T>() String"
End

Function F1<T>( t:T )
	Print "F1<T>(T)"
End

Function F1( t:Int )
	Print "F1(Int)"
End

Function F1<T>( p:T() )
	Print "F1<T>(T())"
End

Function F1( p:Void() )
	Print "F1(Void())"
End

Function F1( p:Int(Int) )
	Print "F1(Int(Int))"
End

Function F1<R,A>( f:R(A) )
	Print "F1<R,A>(R(A))"
End

Function P()
End

Function P2:Int()
	Return Null
End

Function P3:Int( i:Int )
	Return Null
End

Function P4:Int( x:Float )
	Return Null
End

Function Main()

	F1<Int>()		'F1<T>() INumeric
	F1<String>()	'F1<T>() String
	F1( "yes" )		'F1<T>(T)
	F1( 100 )		'F1(Int)
	F1( P )			'F1(Void())
	F1( P2 )		'F1<T>(T())
	F1( P3 )		'F1(Int(Int))
	F1( P4 )		'F1<R,A>(R(A))
	
End
