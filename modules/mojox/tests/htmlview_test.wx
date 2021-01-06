
#import "<std>"
#import "<mojo>"
#import "<mojox>"

#import "assets/about.html"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "HtmlView Demo",640,480,WindowFlags.Resizable )

		Local htmlView:=New HtmlView
		
		htmlView.Go( "asset::about.html" )
		
		Print htmlView.HtmlSource
		
		ContentView=htmlView
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		RequestRender()
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

