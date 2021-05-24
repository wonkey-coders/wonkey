#Import "../assets/gz_background.png"
#Import "../assets/gz_logo.png"

#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"
#Import "<pyro-gui>"

Using std..
Using mojo..
Using pyro.framework..
Using pyro.gui..

Class PyroExample Extends Window

	Field guiGroup:GuiGroup
	Field layer:GuiLayer
	Field virtualResolution:=New Vec2i( 1024,768 )

	Method New( title:String,width:Int,height:Int,flags:WindowFlags=WindowFlags.Resizable )

		Super.New( title,width,height,flags )

		Local backgroundImage:=Image.Load( "asset::gz_background.png" )
		Local logoImage:=Image.Load( "asset::gz_logo.png" )

		ClearColor=New Color( .1,.1,.1,1 )

		Layout="letterbox"

		layer=New GuiLayer( Self )

		guiGroup=New GuiGroup( layer )
		guiGroup.Width=backgroundImage.Width
		guiGroup.Height=backgroundImage.Height
		guiGroup.Location=New Vec2f( 512,384 )

		Local background:=New GuiImage
		background.Group=guiGroup
		background.Surface.DrawData( GuiState.Idle ).Image=backgroundImage
		background.Location=New Vec2f( 512,384 )

		Local logo:=New GuiImage
		logo.Group=guiGroup
		logo.Surface.DrawData( GuiState.Idle ).Image=logoImage
		logo.Location=New Vec2f( 512,576 )

	End

	Method OnMeasure:Vec2i() Override
		Return virtualResolution
	End

	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		layer.Update()

		guiGroup.Rotation+=.005

		layer.Draw( canvas )
		
	End

End

Function Main()

	New AppInstance
	
	New PyroExample( "Pyro example",640,480 )
	
	App.Run()

End
