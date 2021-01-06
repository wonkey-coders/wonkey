
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Button Demo",640,480,WindowFlags.Resizable )
		
		Local progressBar:=New ProgressBar
		
		Local dockingView:=New DockingView
		dockingView.AddView( progressBar,"top" )

		ContentView=dockingView
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
