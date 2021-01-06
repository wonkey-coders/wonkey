
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
	
		Super.New( "Dialogs Demo",640,480,WindowFlags.Resizable )
	
		Local toolBar:=New ToolBar
		
		toolBar.AddAction( "Modal Text Dialog" ).Triggered=Lambda()

			TextDialog.Run( "Modal Text Dialog","This is a text dialog for displaying simple text!",New String[]( "Okay" ),0,0 )

		End
		
		toolBar.AddAction( "Modeless Text Dialog" ).Triggered=Lambda()
		
			Local dialog:=New TextDialog( "Modeless Text Dialog","Click 'Close' to close" )
			
			dialog.AddAction( "Close" ).Triggered=Lambda()
			
				dialog.Close()
			End
			
			dialog.Open()

		End
		
		toolBar.AddAction( "Modeless Progress Dialog" ).Triggered=Lambda()
		
			Local progress:=New ProgressDialog( "Modeless Progress Dialog","Performing incredibly intense calculations..." )
			
			progress.AddAction( "Close" ).Triggered=Lambda()
			
				progress.Close()
			End
			
			progress.Open()
		End
		
		ContentView=toolBar
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
