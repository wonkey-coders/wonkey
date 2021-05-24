' Import assets:
#Import "../assets/vulcano.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"

Using std..
Using mojo..
Using pyro.framework..

Class PyroExample Extends Window

	Field background:Image
	Field fade:=1.0

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		background=Image.Load( "asset::vulcano.png" )
		background.Handle=New Vec2f( .5,.5 )
		
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		If Keyboard.KeyDown( Key.Left ) fade-=.01
		If Keyboard.KeyDown( Key.Right ) fade+=.01

		If fade<0 fade=0
		If fade>1 fade =1
		
		canvas.DrawImage( background,320,240 )

		DrawFader( canvas,fade,Color.Black )												' DrawFader is drawing a rectange the size of the canvas with the given color.

		canvas.Color=Color.White
		canvas.DrawText( "Use cursor keys left/right to change the values.",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
