
Namespace test

#Import "<reflection>"

#Reflect test

Using reflection..
Using std..

Class C
	
	Field _name:="Brian"
	
	Field _pos:=New Vec3f( 1,2,3 )
	
	Property Name:String()
		
		Return _name
	
	Setter( name:String )
		
		_name=name
	End
	
End

Class C Extension
	
	Property Position:Vec3f()
		
		Return _pos
	
	Setter( pos:Vec3f )
		
		_pos=pos
	End
	
End

Function Main()
	
	Local c:=New C
	
	Print "Name="+c.Name

	'set name using reflection	
	SetProperty( "Name",c,"Douglas" )
	
	'get name using reflection
	Print "Name="+GetProperty<String>( "Name",c )
	
	Print "Position="+c.Position
	
	'set position using reflection
	SetProperty( "Position",c,New Vec3f( 4,5,6 ) )
	
	'set position using reflection
	Print "Position="+GetProperty<Vec3f>( "Position",c )
	
End
