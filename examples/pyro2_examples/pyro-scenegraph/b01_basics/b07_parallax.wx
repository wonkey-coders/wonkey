' Import assets:
#Import "../assets/extrial_bg.png"
#Import "../assets/extrial_fg.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																							' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 320,192 )																		' Backing global for virtual resolution.

Class PyroExample Extends Window

	' Backing fields:
	Field camera:Camera
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		' To use sprites you need to setup the scene with a camera and atleast 1 layer:
		scene=New Scene( Self )																						' Create a scene.
		camera=New Camera( scene )																					' Setup camera.

		' Create 2 layers for parallax scrolling:
		Local layer:=New Layer[]( New Layer( scene ),New Layer( scene ) )
		layer[0].Multiplier=New Vec2f( .5,1 )																		' The layer Multiplier ( default 1,1 ) is set to .5,1 so that the layer scroll 'slower' when the camera moves.
		
		' Create the background sprites:
		For Local i:=0 Until 2
		Local sprite:=New LayerSprite( layer[0],Content.GetImage( "asset::extrial_bg.png" ) )
		sprite.X=virtualResolution.X/2+i*Content.GetImage( "asset::extrial_bg.png" ).Width
		sprite.Y=virtualResolution.Y/2
		Next
			
		' Create the foreground sprites:
		For Local i:=0 Until 4
		Local sprite:=New LayerSprite( layer[1],Content.GetImage( "asset::extrial_fg.png" ) )
		sprite.X=virtualResolution.X/2+i*Content.GetImage( "asset::extrial_fg.png" ).Width
		sprite.Y=virtualResolution.Y/2
		Next
			
		' Create the logo sprite:

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		' Scrolling keys:
		If Keyboard.KeyDown( Key.Left ) camera.X-=5
		If Keyboard.KeyDown( Key.Right ) camera.X+=5
		If Keyboard.KeyDown( Key.Up ) camera.Y-=5
		If Keyboard.KeyDown( Key.Down ) camera.Y+=5

		scene.Update()																							' Update must be called before Draw!

		scene.Draw( canvas )																					' Draw all scene objects to canvas.

		canvas.DrawText( "Use cursor keys to scroll.",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
