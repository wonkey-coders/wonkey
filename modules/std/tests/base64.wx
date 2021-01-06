
#Import "<std>"

Using std..

Function Main()
	
	For Local i:=1 To 10000
		
		Local length:=(i Mod 100)+100
		
		Local data:=New DataBuffer( length )
		
		For Local i:=0 Until length
			data.PokeByte( i,Rnd(256) )
		Next
		
		Local str:=EncodeBase64( data )
		
		Local data2:=DecodeBase64( str )
		
		If data.Length<>data2.Length
			Print "Failed: Different lengths!"
			Return
		Endif
		
		If libc.memcmp( data.Data,data2.Data,data.Length )
			Print "Failed: Different data!"
			Return
		Endif
		
		'Print "test OK"
		
	Next
	
	Print "Test OK"
End
		
		
