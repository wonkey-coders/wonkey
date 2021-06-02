'
' Draw Some cartoonish clouds using the drawoval and outline commands
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	Class cloud
		Field px:Float,py:Float
		Field pw:Float,ph:Float
		Field mx:Float
		Field sw:Int
		Method New(x:Int,y:Int,w:Int,h:Int,screenwidth:Int)
			Self.px = x
			Self.py = y
			Self.pw = w
			Self.ph = h
			Self.sw = screenwidth
			mx = Rnd(.05,.25)
		End Method
		Method update()
			px += mx
			If px > sw+pw Then px=0-(pw*2)
		End Method
		' This method draws a cloud/
		' at x,y with width w and height h
		Method draw(canvas:Canvas)
				
			' Create a outline (draw border around oval)
			canvas.OutlineMode = OutlineMode.Solid
			canvas.OutlineColor = Color.Black
			canvas.OutlineWidth = 4
			canvas.Color = Color.White
			' Draw 7 plumps (go around in a circle)
			For Local angle:Float=0 Until TwoPi Step TwoPi/7
				Local x2:Float=Cos(angle)*pw
				Local y2:Float=Sin(angle)*ph
				canvas.DrawOval(x2+px,y2+py,pw,ph)
			Next
			' Turn off the outline mode 
			canvas.OutlineMode = OutlineMode.None
			' Draw a white oval to erase the center of the cloud
			canvas.DrawOval(px-pw/2,py-ph/2,pw+pw,ph+ph)
		End Method
	End Class
	' Here we create a array of 10 clouds
	Field mycloud:cloud[] = New cloud[10]
	Method New()		
		For Local i:Int=0 Until 10
			' create our objects (class) inside our array
			' x,y,w,h,our screen width(for scrolling)
			mycloud[i] = New cloud(Rnd(-Width*.5,Width),Rnd(Height),Rnd(30,150),Rnd(20,60),Width)
		Next		
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Blue sky
		canvas.Clear(Color.Blue)
		' Draw our clouds
		For Local i:=Eachin mycloud
			i.draw(canvas)
			i.update()
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
End Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
