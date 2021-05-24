#Import "<std>"
#Import "<mojo>"
#Import "<pyro-framework>"									' Import pyro framework.

Using std..
Using mojo..

Using pyro.framework..

Global deltaTimer:DeltaTimer
Global sprite:=New TestLayerSprite[2]
Global targetFPS:=60

' Simple test object:
Class TestLayerSprite

	Field text:=""
	
	Field x:=0.0
	Field y:=0.0

	Field r:=0.0
	Field g:=0.0
	Field b:=0.0

	Method Draw:Void( canvas:Canvas )

		canvas.Color=New Color( r,g,b,1 )
		canvas.DrawRect( x,y,64,64 )

		canvas.Color=Color.White
		canvas.DrawText( text,x,y+64 )

	End

End

Class PyroExample Extends Window

	Method New()

		deltaTimer=New DeltaTimer							' Create a delta timer.

		' Create 2 test objects:
		sprite[0]=New TestLayerSprite
		sprite[0].r=1
		sprite[0].y=480*.5-72
		sprite[0].text="Normal"

		sprite[1]=New TestLayerSprite
		sprite[1].b=1
		sprite[1].y=480*.5+8
		sprite[1].text="Corrected"
		
	End

	Method DrawInfo:Void( canvas:Canvas )

		Local x:=8
		Local y:=8
		
		' deltaTimer can return the following values:
		canvas.DrawText( "DeltaTime = " + deltaTimer.DeltaTime,x,y )
		y+=16
		canvas.DrawText( "FrameTime = " + deltaTimer.FrameTime,x,y )
		y+=16
		canvas.DrawText( "ElepasedDelta = " + deltaTimer.ElapsedDelta,x,y )
		y+=16
		canvas.DrawText( "ElepasedTime = " + deltaTimer.ElapsedTime,x,y )
		y+=16
		canvas.DrawText( "TimeScale = " + deltaTimer.TimeScale,x,y )
		y+=16

		y+=16

		canvas.DrawText( "TargetFPS = " + deltaTimer.TargetFPS + " ( cursor keys left/right to adjust )",x,y )
		
		y+=16

	End
	
	Method OnRender( canvas:Canvas ) Override
	
		App.RequestRender()

		deltaTimer.Update()										' Update the delta timer.

		deltaTimer.TargetFPS=targetFPS

		sprite[0].x+=8											' Not affected by the tragetFPS.
		sprite[1].x+=8*deltaTimer.DeltaTime						' Multiply by DeltaTime to get the right FPS.

		If sprite[0].x>Width sprite[0].x=-64
		If sprite[1].x>Width sprite[1].x=-64

		If sprite[0].x<-64 sprite[0].x=Width
		If sprite[1].x<-64 sprite[1].x=Width

		' Change target FPS
		If Keyboard.KeyDown( Key.Left ) targetFPS-=1
		If Keyboard.KeyDown( Key.Right ) targetFPS+=1

		DrawInfo( canvas )

		sprite[0].Draw( canvas )
		sprite[1].Draw( canvas )

	End

End

Function Main()

	New AppInstance
	
	New PyroExample
	
	App.Run()

End
