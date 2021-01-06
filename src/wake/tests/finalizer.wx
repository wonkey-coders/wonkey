Namespace test

Global n:Int

Class T
End

Function F()
	Print "OOPS"
End

Class C
	
	Field c:T=New T
	field v:=New Int[10]
	Field f:Void()=F
	
	Method Finalize() Override
		n+=1
		Assert( Not c And Not v )
'		Print "Finalizing:"+n
		f()
	End

End

Function Main()
	
	Print "Hello World!"
	
	GCSetTrigger( 65536 )
	
	For Local i:=0 Until 100000
		
		For Local j:=0 Until 1000
		
			Local c:=New C
		Next
		
		Print "One"
		
		GCCollect()
		
		Print n
		
		Print "Two"
		
		GCCollect()
		
		Print n
		
	Next

End
