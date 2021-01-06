
Class C
	
	Field x:Int=10
	
	Method Test2:String()
		Return "Test2 - x="+x
	End
End

Class C Extension
	
	Method Test:String()
		Return "x="+x
	End
End

Function Call( f:String() )
	
	Print "f()="+f()
End


Function Main()
	
	Local c:=New C
	
	Call( c.Test2 )
	Call( c.Test )
End
