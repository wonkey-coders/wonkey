
Function Main()

	Local arr:=New Int[10]
	For Local i:=0 Until 10
		arr[i]=i
	Next
	
	Print ""
	For Local i:=Eachin arr
		Print arr[i]			'0...9
	Next

	arr=arr.Resize( 20 )
	Print ""
	For Local i:=Eachin arr
		Print arr[i]			'0...9, 0,0,0...
	Next
	
	arr.CopyTo( arr,0,10,10 )
	Print ""
	For Local i:=Eachin arr
		Print arr[i]			'0...9, 0...9
	Next

	arr=arr.Resize( 5 )
	Print ""
	For Local i:=Eachin arr
		Print arr[i]			'0...4
	Next
	
End
