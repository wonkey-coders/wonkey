
'Ok, not quite *all* types, but getting there...
'
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"
#Import "<mojo3d>"

#Reflect std..
#Reflect mojo..
#Reflect mojox..
#Reflect mojo3d..

Function Main()
	
	'This is all reflection.DebugTypes really does-ish...
	'
	For Local type:=Eachin TypeInfo.GetTypes()
		
		Print type
		
		For Local decl:=Eachin type.GetDecls()
			
			Print " "+decl
		Next
		
		Print ""
	End
	
	Print "Done!"

End
