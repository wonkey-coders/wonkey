#Import "../assets/comici.ttf"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-gui>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.gui..

Class PyroExample Extends Window

	Field button:GuiButton
	Field layer:GuiLayer
	Field virtualResolution:=New Vec2i( 640,480 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )
		layer.ClearColor=New Color( 0,.25,0,1 )

		Local label:=New GuiLabel
		label.Layer=layer
		label.Location=New Vec2f( 320,240 )
		label.Text="Hello world"
		label.Font=Font.Load( "asset::comici.ttf",48 )

		' Set more gui states if you like:
'		label.Label.DrawData( GuiState.Idle ).Color=New Color( 1,1,1,1 )
'		label.Label.DrawData( GuiState.RollOver ).Color=New Color( 1,0,0,1 )
'		label.Label.DrawData( GuiState.Down ).Color=New Color( 1,1,0,1 )

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
