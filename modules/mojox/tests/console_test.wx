
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Console Demo",640,480,WindowFlags.Resizable )
		
		Local console:=New Console
		
		console.Write( "Console open.~n" )
		
		New Fiber( Lambda()
			
			Local cmd:="cmd /C dir"
			
			If Not console.Start( cmd )
				console.Write( "Failed to start '"+cmd+"'.~n" )
				Return
			Endif
			
			Repeat
				Local stdout:=console.ReadStdout()
				If Not stdout Exit
				
				console.Write( stdout )
			Forever
			
			console.Write( "Finished!~n" )
		
		End )
		
		ContentView=console
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
