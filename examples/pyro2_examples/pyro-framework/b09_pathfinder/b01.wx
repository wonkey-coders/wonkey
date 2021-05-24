#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"																	' Import pyro framework.

Using std..
Using mojo..
Using pyro.framework..

Global data:Int[,]
Global finish:=New Vec2i
Global pathFinder:=New Pathfinder
Global size:=New Vec2i( 40,22 )
Global space:=16
Global start:=New Vec2i

Function InitData:Int[,]( size:Vec2i )

    Local data:=New Int[size.X,size.Y]

   	Return data

End Function

Class PyroExample Extends Window

	Method New()

		data=InitData( size )																' Create data map.

		start=New Vec2i( 1,1 )																' Set start of the path.
		finish=New Vec2i( size.X-2, size.Y-2 )												' Set finish of the path.
		
	End

	Method Clear()
	
		For Local x:=0 Until size.X
			For Local y:=0 Until size.Y
				data[x,y]=0
			Next
		Next

	End Method

	' Draws the data:
	Method DrawData( canvas:Canvas )
		For Local x:=0 Until size.X
			For Local y:=0 Until size.Y
				If data[x,y]=1
			 		canvas.DrawRect( x*space,y*space,space,space )
				Endif
			Next
		Next
	End Method

	' Draws the grid:
	Method DrawGrid( canvas:Canvas )
		For Local x:=0 Until size.X+1
			canvas.DrawLine( x*space,0,x*space,size.Y*space )
		Next
		For Local y:=0 Until size.Y+1
			canvas.DrawLine( 0,y*space,size.X*space,y*space )
		Next
	End Method

	' Draws the 'instructions':
	Method DrawInfo( canvas:Canvas )

		Local x:=16
		Local y:=size.Y*space+16

		canvas.BlendMode=BlendMode.Alpha

		canvas.Color=New Color( 1,1,0,1 )
 		canvas.DrawRect( x,y,space,space )

		canvas.Color=New Color( 1,1,1,1 )
		canvas.DrawText( "= start ( use mouse + [s] to change )",x+space+4,y )

		y+=space+4

		canvas.Color=New Color( 0,0,1,1 )
 		canvas.DrawRect( x,y,space,space )

		canvas.Color=New Color( 1,1,1,1 )
		canvas.DrawText( "= finish ( use mouse + [f] to change )",x+space+4,y )

		y+=space+4

		canvas.Color=New Color( 1,0,0,1 )
 		canvas.DrawRect( x,y,space,space )

		canvas.Color=New Color( 1,1,1,1 )
		canvas.DrawText( "= wall ( use [left] / [right] mouse button to draw / erase )",x+space+4,y )

		y+=space+4

		canvas.Color=New Color( 0,1,0 )
		canvas.DrawOval( x+space/4,y+space/4,space/2,space/2 )

		canvas.Color=New Color( 1,1,1,1 )
		canvas.DrawText( "= calculated path",x+space+4,y )

		y+=space+8

		canvas.Color=New Color( 1,1,1,1 )
		canvas.DrawText( "[space] to calculate path",x,y )

	End

	' Draws the path:
	Method DrawPath( canvas:Canvas )

		If pathFinder.GetPathArray().Length>0

			Local x:=start.X
			Local y:=start.Y

			canvas.DrawOval( ( x*space )+( space/4 ),( y*space )+( space/4 ),space/2,space/2 )

			For Local i:=0 Until pathFinder.GetPathArray().Length-1

				Local direction:=pathFinder.GetPathArray()[i]

				Select direction
					Case "U"
						y-=1
					Case "R"
						x+=1
					Case "D"
						y+=1
					Case "L"
						x-=1
				End Select

				canvas.DrawOval( ( x*space )+( space/4 ),( y*space )+( space/4 ),space/2,space/2 )

			Next

		End If

	End Method

	' Editor logic:
	Method Editor()

		Local x:=App.MouseLocation.X
		Local y:=App.MouseLocation.Y

		x/=space
		y/=space
		
		If x<0 Return
		If y<0 Return
		If x>size.X-1 Return
		If y>size.Y-1 Return

		If Mouse.ButtonDown( MouseButton.Left )
			data[x,y]=1
		Endif

		If Mouse.ButtonDown( MouseButton.Right )
			data[x,y]=0
		Endif

		If Keyboard.KeyDown( Key.S )
			start=New Vec2i( x,y )
		Endif

		If Keyboard.KeyDown( Key.F )
			finish=New Vec2i( x,y )
		Endif

	End

	Method OnRender( canvas:Canvas ) Override

		Editor()

		If Keyboard.KeyDown( Key.C ) Clear()											' Clear the map.

		If Keyboard.KeyDown( Key.Space )

			pathFinder.SetMap( data,start,finish )										' Prepare the path finder by setting the map and start / finish.
	
			' Search for path
			Select pathFinder.Search()
				Case True
					Print "Path found: "+pathFinder.GetPathString()
				Case False
					Print "No path: "
			End Select

		Endif
	
		App.RequestRender()

		DrawInfo( canvas )

 		canvas.Color=New Color( 1,1,0,1 )
 		canvas.DrawRect( start.X*space,start.Y*space,space,space )

 		canvas.Color=New Color( 0,0,1,1 )
 		canvas.DrawRect( finish.X*space,finish.Y*space,space,space )

 		canvas.Color=New Color( 1,0,0,1 )
		DrawData( canvas )

		canvas.Color=New Color( .25,.25,.25,1 )
		DrawGrid( canvas )

		canvas.Color=New Color( 0,1,0,1 )
		DrawPath( canvas )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
