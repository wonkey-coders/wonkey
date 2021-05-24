#Import "../assets/button.png"

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
	Field sliderKnob:=New GuiSliderKnob[2]
	Field virtualResolution:=New Vec2i( 640,480 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )

		sliderKnob[0]=New GuiSliderKnob
		sliderKnob[0].Layer=layer
		sliderKnob[0].Surface.DrawData( GuiState.Idle ).Image=Image.Load( "asset::button.png" )
		sliderKnob[0].Location=New Vec2f( 48,360 )
		sliderKnob[0].Surface.DrawData( GuiState.Idle ).Color=New Color( .5,.5,.5,1 )
'		sliderKnob[0].Surface.DrawData( GuiState.RollOver ).Color=New Color( 1,0,0,1 )
'		sliderKnob[0].Surface.DrawData( GuiState.Down ).Color=New Color( 1,1,0,1 )
		sliderKnob[0].Surface.DrawData( GuiState.Down ).Scale=New Vec2f( .95,.95 )
		sliderKnob[0].Surface.PatchData=New Int[](8)
		sliderKnob[0].Width=50
		sliderKnob[0].Height=50
		sliderKnob[0].Length=200
'		sliderKnob[0].Scale=New Vec2f( .5,.5 )
		sliderKnob[0].Name="sliderKnob 1"
		sliderKnob[0].Type=1																		' Horizontal mode.
'		sliderKnob[0].Handle=New Vec2f( 0,0 )

		sliderKnob[1]=New GuiSliderKnob
		sliderKnob[1].Layer=layer
		sliderKnob[1].Surface.DrawData( GuiState.Idle ).Image=Image.Load( "asset::button.png" )
		sliderKnob[1].Location=New Vec2f( 48,90 )
		sliderKnob[1].Surface.DrawData( GuiState.Idle ).Color=New Color( .5,.5,.5,1 )
'		sliderKnob[1].Surface.DrawData( GuiState.RollOver ).Color=New Color( 1,0,0,1 )
'		sliderKnob[1].Surface.DrawData( GuiState.Down ).Color=New Color( 1,1,0,1 )
		sliderKnob[1].Surface.DrawData( GuiState.Down ).Scale=New Vec2f( .95,.95 )
		sliderKnob[1].Surface.PatchData=New Int[](8)
		sliderKnob[1].Width=50
		sliderKnob[1].Height=50
		sliderKnob[1].Length=200
'		sliderKnob[1].Scale=New Vec2f( .5,.5 )
		sliderKnob[1].Name="sliderKnob 2"
		sliderKnob[1].Type=2																		' Vertical mode.
'		sliderKnob[1].Handle=New Vec2f( 0,0 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		layer.Draw( canvas )
		
		canvas.Color=Color.White
		canvas.DrawText( sliderKnob[0].Value+"/"+sliderKnob[0].Maximum,8,8 )
		canvas.DrawText( sliderKnob[1].Value+"/"+sliderKnob[1].Maximum,8,8+canvas.Font.Height )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
