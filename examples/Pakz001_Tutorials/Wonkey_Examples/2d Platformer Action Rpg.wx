#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class Tilemap
	Field tilewidth:Int
	Field tileheight:Int
	Field minimapimage:Image
	Field minimapcanvas:Canvas
	Field image:= New Image[10]
	Field canvas:= New Canvas[10]
	Field width:Int,height:Int
	Method New(width:int,height:Int,tilewidth:Int,tileheight:Int)
	
		Self.width=width
		Self.height=height
		Self.tilewidth=tilewidth
		Self.tileheight=tileheight
		initminimap(128,128)
		image[0] = New Image(tilewidth,tileheight)
		canvas[0] = New Canvas(image[0])
		canvas[0].Clear(Color.Black)
		
		canvas[0].Color = Color.White
		canvas[0].DrawLine(0,0,tilewidth,0)
		canvas[0].DrawLine(0,0,0,tileheight)
		canvas[0].Flush()
	End Method 
	Method update()
	End Method 
	Method draw(canvas:Canvas)
		'draw the map
		For Local y:=0 Until height
		For Local x:=0 Until width
			canvas.DrawImage(image[0],x*tilewidth,y*tileheight)
		Next
		Next
		'draw the minimap
		canvas.DrawImage(minimapimage,width-minimapimage.Width,0)
	End Method 
	Method updateminimap()
		
	End Method 
	Method initminimap(w:Int,h:int)
		minimapimage = New Image(w,h)
		minimapcanvas = New Canvas(minimapimage)
		minimapcanvas.Clear(Color.Black)
		updateminimap()
	End Method
End Class 

Global tilemap:Tilemap

Class MyWindow Extends Window

	Method New()
		Super.New("Action Rpg",1366,768)
		tilemap = New Tilemap(Width,Height,32,32)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		tilemap.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
