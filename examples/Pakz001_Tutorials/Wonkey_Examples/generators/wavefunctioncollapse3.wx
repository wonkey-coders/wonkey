'
' Wave Function Collapse (2d tilemap)
'

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class wfc
	Field mapwidth:Int,mapheight:Int
	Field screenwidth:Int,screenheight:Int
	Field tilewidth:Float,tileheight:Float
	Field map:Int[,]
	Field module:Stack<Stack<Stack<Int>>> = New Stack<Stack<Stack<Int>>>
	Method New(sw:Int,sh:Int,mw:Int,mh:Int)
		'Print "1"[0]
		map = New Int[mw,mh]
		mapwidth = mw
		mapheight = mh
		screenwidth = sw
		screenheight = sh
		tilewidth = Float(screenwidth)/Float(mapwidth)
		tileheight = Float(screenheight)/Float(mapheight)
		initmodules()
		collapse()
	End Method
	'Here we create the modules. For each tile we
	'create in each of the 8 sides which other tiles are valid	
	Method initmodules()
		Local air:Int[] = New int[](0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,
									-1,-1,-1,-1,-1,3 ,3 ,3 , 'water top only at bottom of air
									-1,-1,-1,-1,-1,4 ,4 ,4 , 'sand top only at bottom of air
									-1,-1,-1,5 ,-1,-1,-1,-1, 'sand right 
									-1,-1,-1,'sand right top(6)
	End Method						
	Method collapse()
	End Method
	Method drawmap(canvas:Canvas)
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			Local x1:Int=x*tilewidth
			Local y1:Int=y*tileheight
			Select map[x,y]
				Case 0 'air
					canvas.Color = Color.Blue.Blend(Color.White,.5)
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 1 'sand
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 2 'water
					canvas.Color = Color.Blue
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
				Case 3 'water top
					canvas.Color = Color.Blue
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Blue.Blend(Color.White,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
				Case 4 'sand top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.White,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
				Case 5 'sand right
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1+tilewidth-3,y1,3,tileheight+1)
				Case 6 'sand right top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
					canvas.DrawRect(x1+tilewidth-3,y1,3,tileheight+1)					
				Case 7 'sand left top
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,tilewidth+1,3)
					canvas.DrawRect(x1,y1,0,tileheight+1)					
				Case 8 ' sand left
					canvas.Color = Color.Brown
					canvas.DrawRect(x1,y1,tilewidth+1,tileheight+1)
					canvas.Color = Color.Green.Blend(Color.Black,.3)
					canvas.DrawRect(x1,y1,3,tileheight+1)
					
			End Select
		Next
		Next
	End Method
End Class

Global mywfc:wfc

Class MyWindow Extends Window

	Method New()
		mywfc = New wfc(Width,Height,20,15)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mywfc.drawmap(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
