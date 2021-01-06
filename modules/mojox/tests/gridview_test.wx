
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window
	
	Field mainView:GridView
	
	Field gameView:Label
	Field view1:Label
	Field view2:Label
	
	Method New()
		Super.New( "GridView",640,480,WindowFlags.Resizable )

		'Create GameView		
		gameView=New Label
		gameView.Layout="fill"
		gameView.Text="GameView"
		gameView.TextGravity=New Vec2f( .5 )
		Local gameViewStyle:=gameView.Style.Copy()
		gameViewStyle.BackgroundColor=Color.Red
		gameView.Style=gameViewStyle
		
		'Create View1
		view1=New Label
		view1.Layout="fill"
		view1.Text="View1"
		view1.TextGravity=New Vec2f( .5 )
		Local view1Style:=view1.Style.Copy()
		view1Style.BackgroundColor=Color.Green
		view1.Style=view1Style
		
		'Create View2
		view2=New Label
		view2.Layout="fill"
		view2.Text="View2"
		view2.TextGravity=New Vec2f( .5 )
		Local view2Style:=view2.Style.Copy()
		view2Style.BackgroundColor=Color.Blue
		view2.Style=view2Style

		'Create Main GridView
		mainView=New GridView( 8,8 )
		mainView.AddView( gameView,0,0,8,4 )
		mainView.AddView( view1,0,4,4,4 )
		mainView.AddView( view2,4,4,4,4 )
		
		ContentView=mainView
	End
	
End

Function Main()
	
	New AppInstance
	New MyWindow
	App.Run()
	
End
