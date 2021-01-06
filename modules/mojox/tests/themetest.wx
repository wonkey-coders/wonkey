
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

#Import "assets/simple_theme.json"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Field _scale:Float=1
	
	Field _image:Image

	Method New()
		Super.New( "Theme Demo",640,480,WindowFlags.Resizable )
		
		App.Theme.Load( "asset::simple_theme.json" )
		
		App.Theme.Scale=New Vec2f( 1.5,1.5 )

		Local menu:=New Menu( "File" )
		menu.AddAction( "Open" )
		menu.AddAction( "Close" )
		menu.AddAction( "Quit" )
		
		Local menuBar:=New MenuBar
		menuBar.AddMenu( menu )
		
		Local docker:=New DockingView
		
		docker.AddView( menuBar,"top" )
		
		Local tabView:=New TabView
		
		Local textView:=New TextView( "Hello World!" )
		
		textView.CursorBlinkRate=2.5
		
		tabView.AddTab( "TextView",textView,True )
		
		docker.ContentView=tabView
		
		Local browser:=New FileBrowser
		
		docker.AddView( browser,"right",200,True )
		
		ContentView=docker
	End
	
	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()
		
		GCCollect()
	End
	
	Method OnMouseEvent( event:MouseEvent ) Override
	
		Select event.Type
		Case EventType.MouseWheel

			If event.Wheel.y>0
				If _scale<4 _scale+=0.125
			Else
				If _scale>.5 _scale-=0.125
			Endif

			App.Theme.Scale=New Vec2f( _scale,_scale )
			
		End
	End

End


Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
