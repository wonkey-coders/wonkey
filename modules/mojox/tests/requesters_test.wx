
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "TreeView Demo",640,480,WindowFlags.Resizable )
		
		Local toolBar:=New ToolBar
		
		toolBar.AddAction( "String" ).Triggered=Lambda()

			Alert( "String entered:"+RequestString() )
		
		End
		
		ContentView=toolBar
		
		App.Idle+=OnIdle
	End
	
	Method OnIdle()
	
		App.RequestRender()
		
		App.Idle+=OnIdle
	End

End


Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

