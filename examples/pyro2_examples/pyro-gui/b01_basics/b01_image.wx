#Import "../assets/gz_background.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-gui>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.gui..

Class PyroExample Extends Window

	Field layer:GuiLayer
	Field virtualResolution:=New Vec2i( 1024,768 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )

		Local image:=New GuiImage( layer,Image.Load( "asset::gz_background.png" ) )
		image.Location=New Vec2f( 512,384 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		layer.Draw( canvas )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
