#Import "../assets/inputbox.png"
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

		Local inputBox:=New GuiInputBox[4]
		Local y:=96

		For Local i:= 0 Until inputBox.Length

			inputBox[i]=New GuiInputBox
			inputBox[i].Layer=layer
			inputBox[i].Width=256
			inputBox[i].Height=80
			inputBox[i].Location=New Vec2f( 320,y )
			inputBox[i].Border=40
			inputBox[i].Surface.PatchData=New Int[](8)
			inputBox[i].Surface.DrawData( GuiState.Idle ).Image=Content.GetImage( "asset::inputbox.png" )
			inputBox[i].Text="Type me"
			inputBox[i].Font=Content.GetFont( "asset::comici.ttf",21 )
	
			y+=88

		Next

		KeyboardReceiver=inputBox[0]																	' Keyboard to inputBox[0]

	End

	Method OnKeyEvent( event:KeyEvent ) Override
		layer.SendKeyEvent( event )																		' Send key events to gui layer.
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
