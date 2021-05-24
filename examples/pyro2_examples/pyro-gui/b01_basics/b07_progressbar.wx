#Import "../assets/progressbar/"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-gui>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.gui..

Class PyroExample Extends Window

	Field progressBar:GuiHProgressBar
	Field layer:GuiLayer
	Field virtualResolution:=New Vec2i( 640,480 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )
		layer.ClearColor=New Color( 0,.25,0,1 )

		progressBar=New GuiHProgressBar
		progressBar.Layer=layer
		progressBar.Maximum=240
		progressBar.Value=120
		progressBar.Location=New Vec2f( 320,352 )

'		progressBar.Handle=New Vec2f( 0,0 )

		progressBar.Surface.DrawData( GuiState.Idle ).Image=Content.GetImage( "asset::progressbar_0.png" )
		progressBar.Surface.DrawData( GuiState.Ghost ).Image=Content.GetImage( "asset::progressbar_0.png" )
		progressBar.Surface.DrawData( GuiState.Ghost ).Color=New Color( .5,.5,.5,.5 )

		progressBar.Indicator.DrawData( GuiState.Idle ).Image=Content.GetImage( "asset::progressbar_1.png" )
		progressBar.Indicator.DrawData( GuiState.Ghost ).Image=Content.GetImage( "asset::progressbar_1.png" )
		progressBar.Indicator.DrawData( GuiState.Ghost ).Color=New Color( .5,.5,.5,.5 )

'		progressBar.Scale=New Vec2f( .5,.5 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		If Keyboard.KeyDown( Key.Left ) progressBar.Value-=1
		If Keyboard.KeyDown( Key.Right ) progressBar.Value+=1

		If progressBar.Value<0 progressBar.Value=progressBar.Maximum
		If progressBar.Value>progressBar.Maximum progressBar.Value=0

		layer.Draw( canvas )
		
		canvas.DrawText( "Use cursor keys left / right to change the values.",8,8 )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
