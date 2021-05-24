#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"																					' Import pyro framework.

Using std..
Using mojo..
Using pyro.framework..

Global game:Game
Global loader:Loader
Global window:View

Class Game Extends Screen

	Method OnStart() Override
		Print "Game started"
	End

	Method OnStop() Override
		Print "Game stopped"
	End

	Method OnRender( canvas:Canvas ) Override

		' Example render
		canvas.Clear( New Color( .25,0,0,1 ) )
		canvas.DrawText( "Hello game",0,0 )

	End

	Method OnUpdate() Override
		' Game update code here!
	End

	Method RunOnce() Override
		Print "Game initialized"
	End

End

Class Loader Extends LoaderScreen

	Method OnStart() Override
		Print "Loader started"
	End

	Method OnStop() Override
		Print "Loader stopped"
	End

	Method OnLoading() Override

		' Every 'If Loading' represents a loading step. You can add as many as you need. The delay command is to simulate loading time ( don't use in final code! ).

		If Loading()
			Print "Replace this print command with a load command... ( Current step is "+CurrentStep+" of "+LoadingSteps+" in total )" ; Delay( 1000 )
		Endif

		If Loading()
			Print "Replace this print command with a load command... ( Current step is "+CurrentStep+" of "+LoadingSteps+" in total )" ; Delay( 1000 )
		Endif

		If Loading()
			Print "Replace this print command with a load command... ( Current step is "+CurrentStep+" of "+LoadingSteps+" in total )" ; Delay( 1000 )
		Endif

		' Etc if you need more loading.

	End

	Method OnRender( canvas:Canvas ) Override

		Super.OnRender( canvas )															' Don't forget this!
		
		canvas.DrawText( "Loading: "+CurrentStep+" of "+LoadingSteps,8,8 )					' Can be a progressbar or whatever.

	End

	Method RunOnce() Override
		Print "Loader initialized"
	End

End

Class PyroExample Extends ScreenManager

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		window=Self

		game=New Game
		loader=New Loader
		loader.Set()
		
		loader.FollowUpScreen=game

	End
	
End

Function Main()

	New AppInstance
	
	New PyroExample( "Loader demo",640,480 )
	
	App.Run()

End
