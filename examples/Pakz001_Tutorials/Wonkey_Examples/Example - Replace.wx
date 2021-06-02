#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..



Class map
	Field map:String[,] = New String[10,40]	
	Method New()
		For Local i:=0 Until 110*40
			Local ns:String
			For Local ii:=0 Until 10
				ns+=String.FromChar(Rnd(255))
			Next
			map[Rnd(0,10),Rnd(0,40)] = ns
		Next		
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		For Local y:=0 Until 40
		For Local x:=0 Until 10
			canvas.DrawText(map[x,y],x*64,y*16)
		Next
		Next
	End Method 
End Class 

Global mymap:map

Class MyWindow Extends Window

	Method New()
		mymap = New map()
		
		'
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' if key escape then quit
		mymap.draw(canvas)
		For Local y:=0 until 40
		For Local x:=0 Until 10
			Local a:String=mymap.map[x,y]
			a=mymap.map[x,y]
			a = a.Replace(String.FromChar(Rnd(255)),"")		
			mymap.map[x,y]=a
		Next
		Next
			
		Local cnt:=0
		For Local y:=0 until 40
		For Local x:=0 Until 10
			If mymap.map[x,y] <> "" Then cnt+=1
		Next
		Next
		If cnt<40*3 Then 
			mymap = New map()
		End If
		'
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
