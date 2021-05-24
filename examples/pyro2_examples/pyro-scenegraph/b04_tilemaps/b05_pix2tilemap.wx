' Pixmap to tilemap example:

#Import "../assets/antonio.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global camera:Camera
Global layer:Layer
Global scene:Scene
Global virtualResolution:=New Vec2i( 640,480 )

Class PyroExample Extends Window

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		scene=New Scene( Self )
		camera=New Camera( scene )
		camera.ClearColor=New Color( 0,.1,0 )
		layer=New Layer( scene )
		layer.TileSize=New Vec2i( 16,16 )
		
		PixmapToTilemap( layer,"asset::antonio.png",0,0 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		If Keyboard.KeyDown( Key.Left ) camera.X-=5
		If Keyboard.KeyDown( Key.Right ) camera.X+=5
		If Keyboard.KeyDown( Key.Up ) camera.Y-=5
		If Keyboard.KeyDown( Key.Down ) camera.Y+=5

		scene.Update()

		scene.Draw( canvas )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
