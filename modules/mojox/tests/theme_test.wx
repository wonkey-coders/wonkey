#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

#Import "assets/theme_test/"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Simple Mojo Gui App",640,480,WindowFlags.Resizable )
		
		Local view:=New DockingView

		For Local i:=0 Until 5
			
			Local label:=New Button( "Random Button "+i )
			label.Enabled= i Mod 2=0
			
			view.AddView( label,"top" )
		Next
		
		view.Layout="float"
		
		ContentView=view
	End

End

Function Main()
	SetConfig( "MOJO_INITIAL_THEME","theme_test" )

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
