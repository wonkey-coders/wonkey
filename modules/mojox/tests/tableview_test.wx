
#import "<std>"
#import "<mojo>"
#import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Text",320,240,WindowFlags.Resizable )
		
		Local tableView:=New TableView
		
		tableView.AddColumn( "Column1",,"25%" )
		tableView.AddColumn( "Column2",,"25%" )
		tableView.AddColumn( "Column3",,"25%" )
		tableView.AddColumn( "Column4",,"25%" )
		
		tableView.AddRows( 100 )
		
		For Local y:=0 Until 100
			For Local x:=0 Until 4
				tableView[x,y]=New Label( "X="+x+", Y="+y )
			Next
		Next
		
'		Local dialog:=New Dialog( "Table" )
'		dialog.ContentView=tableView
'		dialog.Open()
		
		ContentView=tableView
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
