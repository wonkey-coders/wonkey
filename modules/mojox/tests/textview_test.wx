
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

#Import "assets/mainwindow.monkey2@/"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "TextView Demo",640,480,WindowFlags.Resizable )
		
		Local textView:=New TextView( "Hello World!" )
		
		textView.Text=stringio.LoadString( "asset::mainwindow.monkey2" )
		
		textView.ContentView.Style.Border=New Recti( -32,-32,32,32 )
		textView.ContentView.Style.BorderColor=Color.Blue
		textView.ContentView.InvalidateStyle()
		
		ContentView=textView
		
		textView.MakeKeyView()
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
