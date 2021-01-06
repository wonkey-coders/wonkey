
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "DockingView Demo",640,480,WindowFlags.Resizable )
		
		Local dockingView:=New DockingView
		
		dockingView.AddView( New Button( "Top" ),"top","25%" )
		
		dockingView.AddView( New Button( "Bottom" ),"bottom","25%" )
		
		dockingView.AddView( New Button( "Left" ),"left","25%" )
		
		dockingView.AddView( New Button( "Right" ),"right","25%" )
		
		dockingView.ContentView=New TextView( "ContentView" )
		
		ContentView=dockingView
		
		dockingView.ContentView.MakeKeyView()
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

