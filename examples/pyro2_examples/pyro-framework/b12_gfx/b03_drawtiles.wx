' This examples draws a seemingless tile background from one single image.

#Import "../assets/tile128.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"

Using std..
Using mojo..
Using pyro.framework..

Class PyroExample Extends Window

	Field tileImage:=Image.Load( "asset::tile128.png" )
	Field x:=0.0
	Field y:=0.0

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		If Keyboard.KeyDown( Key.Left) x-=5
		If Keyboard.KeyDown( Key.Right) x+=5
		If Keyboard.KeyDown( Key.Up) y-=5
		If Keyboard.KeyDown( Key.Down) y+=5

		DrawTiles( canvas,tileImage,x,y,640,480 )
		
		canvas.DrawText( "Use cursor keys to scroll",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End