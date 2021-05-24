''#Import "../../../_pyro-include.monkey2"

#Import "../assets/fire.txt"
#Import "../assets/light.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-scenegraph>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.scenegraph..

Global camera:Camera
Global fire:Emitter
Global layer:Layer
Global scene:Scene
Global virtualResolution:=New Vec2i( 640,480 )

Class PyroTest Extends Window

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Layout="letterbox"

		ClearColor=New Color( .25,0,0 )

		scene=New Scene( Self )
		camera=New Camera( scene )
		layer=New Layer( scene )
		
		fire=New Emitter( "asset::fire.txt" )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		fire.Play( layer,MouseLocation )

		scene.Update()

		scene.Draw( canvas )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroTest( "Pyro test",640,480 )
	
	App.Run()

End
