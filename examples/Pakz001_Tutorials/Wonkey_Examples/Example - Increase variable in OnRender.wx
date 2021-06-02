#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance

Class MyWindow Extends Window

	Field t:Int=0
	
	Method New()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender()
		t+=1
		canvas.DrawText(t,0,0)		
	End Method	
	
	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
			Case EventType.KeyDown
			Select event.Key
				Case Key.Escape
			    instance.Terminate()
			End Select
		End Select		
	End Method
	
End	Class

Function Main()
	instance = New AppInstance	
	
	New MyWindow
	
	App.Run()
	
End Function
