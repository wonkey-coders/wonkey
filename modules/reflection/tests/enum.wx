
Namespace test

#Reflect test

Enum E
	A,B,C
End

Global G:E

Function Main()
	
	Print Typeof<E>

	Local e:=E.A
	
	Print Typeof( e )
	
	Local type:=Typeof( e )
	
	For Local decl:=Eachin type.GetDecls()
		
		Local e:=decl.Get( Null )
		
		Print decl.Name+"="+e.EnumValue
	
	Next
	
	Local g:=TypeInfo.GetType( "test" ).GetDecl( "G" )
	
	'one way To set an enum...
	g.Set( Null,type.MakeEnum( E.A ) )
	Print g.Get( Null ).EnumValue
	
	'another way to set an enum...!
	g.Set( Null,type.MakeEnum( 2 ) )
	Print g.Get( Null ).EnumValue
	
	
End
