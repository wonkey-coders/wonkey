
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "TabView Demo",960,480,WindowFlags.Resizable )
		
		Local tabView:=New TabView( TabViewFlags.ClosableTabs|TabViewFlags.DraggableTabs )
		
		For Local i:=1 To 10
			tabView.AddTab( "Tab"+i,New TextView( "This is tab view #"+i ) )
		Next
		
		tabView.CurrentIndex=0
		
		tabView.RightClicked=Lambda()
		
			Local menu:=New Menu
			menu.AddAction( "Action 1" )
			menu.AddAction( "Action 2" )
			menu.AddAction( "Action 3" )
			
			menu.Open()
		End
		
		tabView.CloseClicked=Lambda( index:Int )
		
			tabView.RemoveTab( index )
		
			If tabView.CurrentView Or Not tabView.NumTabs Return
			
			If index=tabView.NumTabs index-=1

			tabView.CurrentIndex=index
		End
		
		ContentView=tabView
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

