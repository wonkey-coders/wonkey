
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "DockingView Demo",640,480,WindowFlags.Resizable )
		
		ClearColor=New Color( .1,.1,.1,1 )

		Local toolBar:=New ToolBar

		For Local i:=1 To 9
		
			If (i+5) Mod 3=0 toolBar.AddSeparator()
		
			toolBar.AddAction( "Tool "+i ).Triggered=Lambda()
				Alert( "Tool "+i+" clicked" )
			End
		
		Next
		
		ContentView=toolBar
	End
	
End


Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

