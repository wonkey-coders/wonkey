
Global g:C

Function Test2()
	
	g=Null
End

Class C
	
	Field x:Int=-1
	
	Method Test()

		Test2()
		
		x=100
		
		For Local i:=0 Until 10
			GCCollect()
			Local t:=New C
		Next
		
		Print x
	
	End
End

Struct S
	
	Field c:C
	
End

Function Test( c:C )
	
	Test2()
	
	c.x=100
	
	For Local i:=0 Until 10
		GCCollect()
		Local t:=New C
	Next
	
	Print c.x
	
End

Function Test( s:S )
	
	Test2()
	
	s.c.x=100
	
	For Local i:=0 Until 10
		GCCollect()
		Local t:=New C
	Next
	
	Print s.c.x
	
End

Function Main()
	
	'should print 100 3 times...
	
	g=New C
	
	Test( g )
	
	g=New C
	
	g.Test()
	
	Local s:S
	
	g=New C
	
	s.c=g
	
	Test( s )
	
End
	