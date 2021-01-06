
#Import "<std>"
#Import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "FileBrowser Demo",640,480,WindowFlags.Resizable )
		
		Local fileBrowser:=New FileBrowser( CurrentDir() )
		
		fileBrowser.FileClicked=Lambda( path:String )
			Alert( "File Clicked="+path )
		End
		
		fileBrowser.FileRightClicked=Lambda( path:String )
			Alert( "File Right Clicked="+path )
		End
		
		fileBrowser.FileDoubleClicked=Lambda( path:String )
			Alert( "File Double Clicked="+path )
		End
		
		ContentView=fileBrowser
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

