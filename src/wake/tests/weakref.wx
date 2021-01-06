
Global weakRef:WeakRef

Class C
End

Function Test()
	
	weakRef=New WeakRef( New C )
End

Function Main()
	
	Test()
	
'	Local tmp:=weakRef.Target	'should keep weakref alive
	
	Print "weakRef valid="+(weakRef.Target<>Null)	'true
	
	GCCollect()
	GCCollect()

	Print "weakRef valid="+(weakRef.Target<>Null)	'false
	
End
