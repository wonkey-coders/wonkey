#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global instance:AppInstance



Class MyWindow Extends Window

	field map:= new int[10,10]	

	Method New()
		Local cnt:=0
		For Local y:=0 Until 10
		For Local x:=0 Until 10
			map[x,y]=cnt
			cnt+=1
		Next
		Next
	End Method
	
		
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Loop with sync
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		For Local y:=0 Until 10
		For Local x:=0 Until 10
			canvas.DrawText(map[x,y],x*32,y*20)
		Next
		Next
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
