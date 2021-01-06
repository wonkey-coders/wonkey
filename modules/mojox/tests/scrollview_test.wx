
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Button Demo",640,480,WindowFlags.Resizable )

		Local textView:=New TextView
		
		textView.AddView( New Label( "CRAZY STUFF!" ),"top" )
		
		textView.AddView( New Label( "SERIOUSLY" ),"left",100,True )

		textView.AddView( New Label( "SERIOUSLY" ),"right",100,True )

		ContentView=textView
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

