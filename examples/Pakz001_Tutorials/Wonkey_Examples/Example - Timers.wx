#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Field timer:Timer
	Field timer2:Timer
	Field cnt:=0
	field cnt2:=0

	Method New()
		' start running a timer that calls
		' a function
		timer = New Timer( 60,OnUpdate ) '60 every 1000 millisecs()
		timer2 = New Timer(1,subroutine)
	End Method
	
	Method subroutine()
		cnt2+=1
	End Method
	
	Method OnUpdate()
		cnt+=1
	End Method
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		canvas.DrawText("Timer 60 ticks every second",0,0)
		canvas.DrawText(cnt,320,0)
		canvas.DrawText("Timer 1 tick every second",0,15)
		canvas.DrawText(cnt2,320,15)
	End Method	
	
	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
			Case EventType.KeyDown
			Select event.Key
				Case Key.Escape
			    instance.Terminate() 'exit with escape			    
			End Select
		End Select		
	End Method
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
