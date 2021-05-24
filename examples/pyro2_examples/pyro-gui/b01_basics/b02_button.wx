#Import "../assets/button.png"
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

		button=New GuiButton
		button.Layer=layer
		button.Location=New Vec2f( 320,240 )
		button.Width=256
		button.Height=64
'		button.Scale=New Vec2f( .5,.5 )
		button.Name="button"

		' Button surface settings:
		button.Surface.DrawData( GuiState.Idle ).Image=Image.Load( "asset::button.png" )
		button.Surface.DrawData( GuiState.Idle ).Color=New Color( .5,.5,.5,1 )
'		button.Surface.DrawData( GuiState.RollOver ).Color=New Color( 1,0,0,1 )
'		button.Surface.DrawData( GuiState.Down ).Color=New Color( 1,1,0,1 )
		button.Surface.DrawData( GuiState.Down ).Scale=New Vec2f( .98,.98 )
		button.Surface.PatchData=New Int[](8)													' 9 patch border settings.

		' Button label settings:
		button.Label.DrawData( GuiState.Idle ).Color=New Color( .5,.5,.5,1 )
		button.Label.DrawData( GuiState.Down ).Scale=button.Surface.DrawData( GuiState.Down ).Scale

		' Button text settings:
		button.Text="Click me"
		button.Font=Font.Load( "asset::comici.ttf",32 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		If button.Hit Print "Button hit"
		If button.Released Print "Button released"
		If button.Entered Print "Button entered"
		If button.Left Print "Button left"

		layer.Draw( canvas )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
