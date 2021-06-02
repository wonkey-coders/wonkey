#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
    Field map := New Int[][] (
        New Int[]( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 1, 1, 1, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 1, 1, 1, 1, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 ),
        New Int[]( 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ) )	
        Field tilewidth:Int
        Field tileheight:Int        
	Method New()
		' Set The title of the window...
		Title="Tilemap example Array of Arrays....."
		tilewidth = Width/map[0].Length
		tileheight = Height/map.Length
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Clear with black color
		canvas.Clear(Color.Black)
		canvas.Color = Color.White
		For Local y:Int=0 Until map.Length
		For Local x:Int=0 Until map[0].Length
			If map[y][x] = 1				
				canvas.DrawRect(x*tilewidth,y*tileheight,tilewidth,tileheight)
			End If
		Next
		Next		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
