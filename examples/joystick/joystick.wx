
Namespace test

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Function Format:String( v:Float )
	Local s:=Sgn(v)
	Local n:=Int( Abs(v)*100 )
	Return (s>=0 ? "+" Else "-")+(n/100)+"."+(n Mod 100)
End

Class Player

	Field id:Int
	Field joystick:Joystick
	
	Method New( id:Int )
		Self.id=id
		Self.joystick=Joystick.Open( id )
	End
	
	Method Update( canvas:Canvas )
		
		canvas.DrawText( "Player "+id,0,0 )
		
		'update joystick state
		If joystick And Not joystick.Attached 
			joystick.Close()
			joystick=Null
		Endif
		
		If Not joystick
			joystick=Joystick.Open( id )
			If Not joystick
				canvas.DrawText( "No Joystick available",0,16 )
				Return
			Endif
		Endif

		'draw joystick info.		
		canvas.DrawText( "Name="+joystick.Name,0,16 )
		canvas.DrawText( "GUID="+joystick.GUID,0,32 )
		
		For Local axis:=0 Until 6
			Local v:=Format( joystick.GetAxis( axis ) )
			canvas.DrawText( "A"+axis+"="+v,axis * 80,48 )
		Next
		
		For Local button:=0 Until 15
			canvas.DrawText( "B"+button+"="+Int( joystick.ButtonDown( button ) ),(button Mod 8)*80,(button/8)*16+64 )
		Next
			
	End
	
End

'***** MainWindow *****

Class MainWindow Extends Window
	
	Field players:=New Player[4]

	Method New()
		Super.New( "Joystick test",640,480 )
		
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