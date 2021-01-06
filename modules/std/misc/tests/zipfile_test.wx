
#Import "assets/test_zip.zip"

#Import "<std>"

Using std..

Function Main()

	Local zip:=ZipFile.Open( "asset::test_zip.zip" )
	
	For Local file:=Eachin zip.Files
		Print file
	Next
	
	If Not zip.Extract( DesktopDir() ) Print "Failed to extract ZIP"
	
	zip.Close()
	
End

