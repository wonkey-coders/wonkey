
Class C
	
	Method New( str:String )
	End
	
	Method ToString:String()
		
		Return "X"
	End
	
End

Class D Extends C
	
	
	Method New( e:E )
		
		Super.New( e.c.ToString() )
	End

End

Class E
	
	Field c:C
End

Function Main()
	
	Local c:=New C( "X" )
	
	Local e:=New E
	
	Local d:=New D( e )

End


	
	
