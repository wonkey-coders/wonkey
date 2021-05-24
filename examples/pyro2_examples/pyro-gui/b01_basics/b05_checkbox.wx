#Import "../assets/checkbox/"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-gui>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.gui..

Class PyroExample Extends Window

	Field checkbox:=New GuiCheckbox[3]
	Field layer:GuiLayer
	Field virtualResolution:=New Vec2i( 640,480 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )

		checkbox[0]=New GuiCheckbox
		checkbox[0].Layer=layer
		checkbox[0].Surface.DrawData( GuiState.Idle,0 ).Image=Image.Load( "asset::joy1.png" )
		checkbox[0].Surface.DrawData( GuiState.Down,0 ).Image=Image.Load( "asset::joy2.png" )
		checkbox[0].Surface.DrawData( GuiState.Idle,1 ).Image=Image.Load( "asset::touch1.png" )
		checkbox[0].Surface.DrawData( GuiState.Down,1 ).Image=Image.Load( "asset::touch2.png" )
		checkbox[0].Location=New Vec2f( 320,120 )
		checkbox[0].Name="checkbox 1"

		checkbox[1]=New GuiCheckbox
		checkbox[1].Layer=layer
		checkbox[1].Surface.DrawData( GuiState.Idle,0 ).Image=Image.Load( "asset::on.png" )
		checkbox[1].Surface.DrawData( GuiState.Down,0 ).Image=Image.Load( "asset::nop.png" )
		checkbox[1].Surface.DrawData( GuiState.Idle,1 ).Image=Image.Load( "asset::off.png" )
		checkbox[1].Surface.DrawData( GuiState.Down,1 ).Image=Image.Load( "asset::nop.png" )
		checkbox[1].Location=New Vec2f( 320,240 )
		checkbox[1].Name="checkbox 2"

		checkbox[2]=New GuiCheckbox
		checkbox[2].Layer=layer
		checkbox[2].Surface.DrawData( GuiState.Idle,0 ).Image=Image.Load( "asset::checkbox1.png" )
		checkbox[2].Surface.DrawData( GuiState.RollOver,0 ).Image=Image.Load( "asset::checkbox2.png" )
		checkbox[2].Surface.DrawData( GuiState.Down,0 ).Image=Image.Load( "asset::checkbox3.png" )
		checkbox[2].Surface.DrawData( GuiState.Idle,1 ).Image=Image.Load( "asset::checkbox4.png" )
		checkbox[2].Surface.DrawData( GuiState.RollOver,1 ).Image=Image.Load( "asset::checkbox5.png" )
		checkbox[2].Surface.DrawData( GuiState.Down,1 ).Image=Image.Load( "asset::checkbox6.png" )
		checkbox[2].Scale=New Vec2f( 2,2 )
		checkbox[2].Location=New Vec2f( 320,360 )
		checkbox[2].Name="checkbox 3"

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		For Local i:=0 Until checkbox.Length
			If checkbox[i].Released Print checkbox[i].Name+" frame="+checkbox[i].Frame
		Next
		
		layer.Draw( canvas )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
