
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "TextField Demo",640,480,WindowFlags.Resizable )
		
		Local textField:=New TextField
		
		textField.Entered=Lambda()
			New Fiber( Lambda()
				Alert( "Text Entered: "+textField.Text )
				textField.MakeKeyView()
			End )
		End
		
		Local label:=New Label( "Enter your name:" )

		label.AddView( textField )
		
		ContentView=label

		textField.MakeKeyView()
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
