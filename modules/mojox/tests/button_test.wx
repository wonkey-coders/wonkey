
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Button Demo",640,480,WindowFlags.Resizable )
		
		Local label:=New Label( "Idle" )
		label.Gravity=New Vec2f( .5,0 )
		
		Local button:=New Button( "Click ME!" )
		
		button.Clicked=Lambda()
			Global n:=0
			n+=1
			label.Text="Clicked #"+n
		End
		
		button.DoubleClicked=Lambda()
			Global n:=0
			n+=1
			label.Text="Double clicked #"+n
		End
		
		button.RightClicked=Lambda()
			Global n:=0
			n+=1
			label.Text="Right clicked #"+n
		End
		
		Local dockingView:=New DockingView
		dockingView.AddView( label,"top" )
		dockingView.ContentView=button

		ContentView=dockingView
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

