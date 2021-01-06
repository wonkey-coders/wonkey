
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

#Import "assets/monkey2.png"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "Simple Mojo Gui App",640,480,WindowFlags.Resizable )
		
		Local icon:=Image.Load( "asset::monkey2.png" )
		
		Local list:=New ListView
		For Local i:=0 until 100
			list.AddItem( "Hello there!~nThis is a wide listview!~nWith an icon!",icon )
			list.AddItem( "there" )
			list.AddItem( "this" )
			list.AddItem( "is" )
			list.AddItem( "listview" )
			list.AddItem( "Hello there this is a wide listview!" )
			list.AddItem( "there" )
			list.AddItem( "this" )
			list.AddItem( "is" )
			list.AddItem( "listview" )
			list.AddItem( "Hello there this is a wide listview!" )
			list.AddItem( "there" )
			list.AddItem( "this" )
			list.AddItem( "is" )
			list.AddItem( "listview" )
		Next
		
		list.ItemClicked+=Lambda( item:ListView.Item )
			Local index:=list.IndexOfItem( item )
			
			Print "Item "+index+" clicked"
		End
		
		ContentView=list
	End

End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
