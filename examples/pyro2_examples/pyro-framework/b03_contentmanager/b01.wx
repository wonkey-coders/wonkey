#Import "../assets/comici.ttf"
#Import "../assets/playniax.png"
#Import "../assets/test.wav"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"																					' Import pyro framework.

Using std..
Using mojo..

Using pyro.framework..

Class PyroExample Extends Window

	' By using the Content.Get... commands instead of the Load commands makes sure an asset is only loaded once in memory!
	Field font:=Content.GetFont( "asset::comici.ttf",32 )
	Field image:=Content.GetImage( "asset::playniax.png" )
	Field sound:=Content.GetSound( "asset::test.wav" )

	Method New()

	End

	Method OnRender( canvas:Canvas ) Override

		App.RequestRender()

		If Keyboard.KeyHit( Key.Space ) sound.Play()
		If Keyboard.KeyHit( Key.S ) Print Content.ToString() ; Print ""
	
		canvas.Clear( New Color( .25,0,0 ) )
		
		canvas.Font=font
		canvas.DrawText( "SPACE = play sound, S = show loaded content in console",0,0 )

		canvas.DrawImage( image,Width*.5-image.Width*.5,Height*.5-image.Height*.5 )	

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
