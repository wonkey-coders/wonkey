#Import "<std>"
#Import "<mojo>"

' Testing/learning bsp

Using std..
Using mojo..

Class MyWindow Extends Window

	Class zone
		Field id:Int
		Field parent:Int
		Field child:Int
		Field layer:Int
		Field x:Int,y:Int,w:Int,h:Int		
	End Class
	Field z:zone[]
	
	Method New()
		go()
	End method

	Method go()		
		Local d:Int=Rnd(4,20)
		z = New zone[300]
		z[1] = New zone()
		z[1].x = 0
		z[1].y = 0
		z[1].w = Width
		z[1].h = Height
		z[1].parent = -1
		z[1].layer = 1
		'SeedRnd(6)
		
		For Local l:Int=1 Until d
			For Local i:Int=0 Until z.Length
				If z[i] = Null Then Continue
				If z[i].layer = l
					newchildren(i,Rnd(2),l)
				Endif
			Next		
			
		Next
		
	End Method
	
	Method newchildren(parent:Int,hor:Int=True,layer:Int)
		Local a:Int,b:Int
		For Local i:Int=1 Until z.Length
			If z[i] = Null Then 
				a = i
				For Local ii:Int=i+1 Until z.Length
					If z[ii] = Null Then
						b = ii
						i = z.Length
						Exit
					End If
				Next
			End If
		Next
		
		z[a] = New zone()
		z[b] = New zone()
		If hor = 0
			Local l:Int=Rnd(5,z[parent].w)
			z[a].x = z[parent].x
			z[a].y = z[parent].y
			z[a].w = l
			z[a].h = z[parent].h
			z[a].parent = parent
			z[a].layer = layer+1
			z[b].x = z[parent].x+l
			z[b].y = z[parent].y
			z[b].w = z[parent].w-l
			z[b].h = z[parent].h
			z[b].parent = parent
			z[b].layer = layer+1
			
		Else
			Local h:Int=Rnd(5,z[parent].h)
			z[a].x = z[parent].x
			z[a].y = z[parent].y
			z[a].w = z[parent].w
			z[a].h = h
			z[a].parent = parent
			z[a].layer = layer+1
			z[b].x = z[parent].x
			z[b].y = z[parent].y+h
			z[b].w = z[parent].w
			z[b].h = z[parent].h-h
			z[b].parent = parent
			z[b].layer = layer+1			
		End If		
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
		
		For Local i:Int=1 Until z.Length
			If z[i] = Null Then Continue
			canvas.Color = New Color(Rnd(),0,0,.5)
			canvas.DrawRect(z[i].x,z[i].y,z[i].w,z[i].h)
			
		Next
		
		canvas.Color = Color.Blue
		canvas.DrawRect(0,0,Width,15)
		canvas.Color = Color.Red
		canvas.DrawText("Press space to generate new map",0,0)
		If Keyboard.KeyReleased(Key.Space) Then go()

	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
