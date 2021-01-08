
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window
	
	Method New()
		
		Local listView:=New ListView
		
		Local modes:=App.EnumDisplayModes()
		
		listView.AddItem( "(Windowed mode)")
		
		For Local mode:=Eachin modes
			
			listView.AddItem( mode.width+","+mode.height+","+mode.depth+","+mode.hertz )
			
		Next
		
		listView.ItemClicked+=Lambda( item:ListView.Item )
		
			Local index:=listView.IndexOfItem( item )
		
			If Not index
				Print "Ending fullscreen"
				If Fullscreen EndFullscreen()
				Return
			Endif
			
			Local mode:=modes[ index-1 ]
			
			Print "Setting display mode:"+mode
			
			If Fullscreen EndFullscreen()
			
			BeginFullscreen( mode.width,mode.height,mode.hertz )
		End
			
		ContentView=listView
	End
	
End

Function Main()
	
	New AppInstance
	
	New MyWindow
	
	App.Run()
End
