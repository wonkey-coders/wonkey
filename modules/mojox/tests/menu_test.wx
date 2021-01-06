#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window
	
	Field menuBar:MenuBar

	Method New()
		Super.New( "Dialogs Demo",640,480,WindowFlags.Resizable )
		
		Local fileMenu:=New Menu( "File" )
		
		Local recentFiles:=New Menu( "Recent Files..." )
		recentFiles.AddAction( "File1" )
		recentFiles.AddAction( "File2" )
		recentFiles.AddAction( "File3" )
		recentFiles.AddAction( "File4" )
		recentFiles.AddAction( "File5" )
		
		fileMenu.AddAction( "Open" ).Triggered=Lambda()
			Alert( "Open Selected..." )
		End
		
		fileMenu.AddSubMenu( recentFiles )
		
		fileMenu.AddAction( "Save" ).Triggered=Lambda()
			Alert( "Save Selected..." )
		End
		
		fileMenu.AddSeparator()

		fileMenu.AddAction( "Close" ).Triggered=Lambda()
			Alert( "Close Selected..." )
		End
		
		fileMenu.AddAction( "Quit" ).Triggered=Lambda()
			App.Terminate()
		End
		
		Local editMenu:=New Menu( "Edit" )

		editMenu.AddAction( "Cut" ).Triggered=Lambda()
			Alert( "Cut Selected..." )
		End
		
		editMenu.AddAction( "Copy" ).Triggered=Lambda()
			Alert( "Copy Selected..." )
		End
		
		editMenu.AddAction( "Paste" ).Triggered=Lambda()
			Alert( "Paste Selected..." )
		End

		menuBar=New MenuBar
		
		menuBar.AddMenu( fileMenu )
		menuBar.AddMenu( editMenu )
		
		ContentView=menuBar
	End
	
	Method OnMouseEvent( event:MouseEvent ) Override
	
		Select event.Type
		Case EventType.MouseUp
			Select event.Button
			Case MouseButton.Right
			
				Local menu:=New Menu
				menu.AddAction( "Action 1" )
				menu.AddAction( "Action 2" )
				menu.AddAction( "Action 3" )
				
				menu.Open( event.Location,event.View,menuBar )
				
				event.Eat()
			End
		End
	End
	
End


Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End

