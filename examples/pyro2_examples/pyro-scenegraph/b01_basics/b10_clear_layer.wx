' Import assets:
#Import "../assets/background.png"
#Import "../assets/playniax.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"																						' Import pyro scene.

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global virtualResolution:=New Vec2i( 640,480 )																	' Backing global for virtual resolution.

Class Logo Extends LayerSprite

	Field r:=Rnd( -.05,.05 )

	Method New( layer:Layer,image:Image )
		Super.New( layer,image )
	End
	
	Method OnUpdate() Override
		Rotation+=r
	End

End

Class PyroExample Extends Window

	' Backing fields:
	Field layer:Layer
	Field scene:Scene

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		' To use sprites you need to setup the scene with a camera and atleast 1 layer:
		scene=New Scene( Self )																						' Create a scene.
		Local camera:=New Camera( scene )																			' Setup camera.
		layer=New Layer( scene )																					' Add layer.

		' Create the background sprite:
		' (  Note that the content manager is used to load the images but Image.Load can also be used instead )
		Local background:=New LayerSprite( layer,Content.GetImage( "asset::background.png" ) )
		background.Location=virtualResolution/2																		' Center of the screen.
		background.Tattooed=True																					' Can not be cleared.

		' Create sprites
		For Local i:=0 Until 150
			Local logo:=New Logo( layer,Content.GetImage( "asset::playniax.png" ) )
			logo.Location=New Vec2f( Rnd( virtualResolution.X ),Rnd( virtualResolution.Y ) )
			logo.TaskManager=layer.TaskManager																		' Let the layer do the updating ( culled if needed ).
		Next
		
	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		scene.Update()																								' Update must be called before Draw!

		scene.Draw( canvas )																						' Draw all scene objects to canvas.

		If Keyboard.KeyHit( Key.Space )
			layer.Clear()																							' Clear layer.
		Endif

		canvas.DrawText( "Hit space to clear layer",8,8 )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
