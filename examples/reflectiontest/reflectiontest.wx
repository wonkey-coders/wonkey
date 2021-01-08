
Namespace test

#Import "<std>"

#Reflect test
#Reflect std..

'A test global...
'
Global G:Int

'A test class...
'
Class C

	Method Update( msg:String )
		Print "C.Update! msg="+msg
	End
	
End

Function Main()

	'Some Typeof examples...
	'
	Local x:=10 
	Print "Typeof( x )="+Typeof( x )
	Print "Typeof( Main )="+Typeof( Main )
	Print "Typeof<Int Ptr[]>="+Typeof<Int Ptr[]>
	Print "Typeof<C>="+Typeof<C>
	
	'Show all decls
	'
	For Local type:=Eachin TypeInfo.GetTypes()
		Print type
		For Local decl:=Eachin type.GetDecls()
			Print "~t"+decl
		Next
	Next

	'Dynamically create a 'C' and invoke Update:
	'
	Local ctype:=TypeInfo.GetType( "test.C" )
	Local ctor:=ctype.GetDecl( "New" )
	Local cvar:=ctor.Invoke( Null,Null )
	ctype.GetDecl( "Update" ).Invoke( cvar,New Variant[]( "Hello world!" ) )
	Cast<C>( cvar ).Update( "Hello again!" )
	
	'Modify the 'G' global:
	'
	Local g:=TypeInfo.GetType( "test" ).GetDecl( "G" )
	g.Set( Null,1234 )
	Print Int( g.Get( Null ) )
	Print G
	
End
