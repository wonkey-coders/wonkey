Namespace test

#Import "<std>"
#Import "<mojo>"

#Import "gamecontrollerdb.txt"

Using std..
Using mojo..

Function Format:String( v:Float )
	Local s:=Sgn(v)
	Local n:=Int( Abs(v)*100 )
	Return (s>=0 ? "+" Else "-")+(n/100)+"."+(n Mod 100)
End

Class Player

	Field id:Int
	Field controller:GameController
	
	Global used:=New StringMap<Bool>
	
	Method New( id:Int )
		Self.id=id
	End
	
	Method Update( canvas:Canvas )
		
		canvas.DrawText( "Player "+id,0,0 )

		'check if attached
		If Not controller?.Attached
			controller=GameController.Open( id )
			If Not controller
				canvas.DrawText( "No game controller available",0,16 )
				Return
			Endif
		Endif
		
		'draw controller info.		
		canvas.DrawText( "Name="+controller.Name,0,16 )
		
		For Local i:=0 Until 6
			Local axis:=Cast<GameControllerAxis>( i )
			Local name:="A"+i'GameController.GetAxisName( axis )
			Local v:=Format( controller.GetAxis( axis ) )
			canvas.DrawText( name+"="+v,i * 80,32 )
		Next
		
		For Local i:=0 Until 15
			Local button:=Cast<GameControllerButton>( i )
			Local name:="B"+i'"GameController.GetButtonName( button )
			canvas.DrawText( name+"="+Int( controller.ButtonDown( button ) ),(i Mod 8)*80,(i/8)*16+48 )
		Next
			
	End
	
End

'***** MainWindow *****

Class MainWindow Extends Window
	
	Field players:=New Player[4]

	Method New()
		Super.New( "Game controller test",640,480 )
		
		GameController.AddMappingsFromFile( "asset::gamecontrollerdb.txt" )
		
		For Local i:=0 Until 4
			players[i]=New Player( i )
		Next
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		RequestRender()
	
		canvas.DrawText( "NumJoysticks="+Joystick.NumJoysticks(),0,0 )
		
		canvas.PushMatrix()
		
		canvas.Translate( 0,16 )
		
		For Local i:=0 Until 4
			
			players[i].Update( canvas )
			
			canvas.Translate( 0,96 )
		Next
		
		canvas.PopMatrix()
		
	End
	
End

Function Main()

	New AppInstance
	
	New MainWindow
	
	App.Run()
	
End