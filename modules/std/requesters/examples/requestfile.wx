
Namespace myapp

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class MyWindow Extends Window

	Method New()
		
		'Open file requester...
		'
		Local openname:=RequestFile( "Open file...","image files:png,jpg;audio files:waw,ogg" )
		If openname
			Notify( "RequestFile example","filename selected="+openname )
		Else
			Notify( "RequestFile example","No filename selected" )
		Endif

		'Save file requester...
		'
		Local savename:=RequestFile( "Save file...","image files:png,jpg;audio files:wav,ogg",True,openname )
		If savename
			Notify( "RequestFile example","filename selected="+savename )
		Else
			Notify( "RequestFile example","No filename selected" )
		Endif
		
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
