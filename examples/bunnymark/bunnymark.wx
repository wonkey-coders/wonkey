Namespace bunnies
 
#Import "assets/wabbit_alpha.png"
 
#Import "<std>"
#Import "<mojo>"
 
Using std..
Using mojo..

Global VirtualSize:=New Vec2i( 640,480 )
 
Const initialCount := 10000
 
Function Main()
	New AppInstance
	New Bunnymark
	App.Run()
End Function
 
'******************************************************************************************************
 
Class Bunnymark Extends Window 
	
	Field atlas:Image
	
	Field frames:=New Image[4]
	
	Field bunnies := New Stack<Bunny>
	
	Method New()
		Super.New("Bunnymark", 1024, 768, WindowFlags.Resizable )
		
		Layout="letterbox"
		
		atlas=Image.Load( "asset::wabbit_alpha.png" )
		
		For Local j:=0 Until 2
			For Local i:=0 Until 2
				frames[ j*2+i ]=New Image( atlas,i*32,j*64,32,64 )
				frames[ j*2+i ].Handle=New Vec2f( .5,.5 )
			Next
		Next
		
		For Local n:= 0 Until initialCount
			bunnies.Push( New Bunny( 512, 384,frames[ Rnd(4) ] ) )
		Next
	End
	
	Method OnMeasure:Vec2i() Override
		
		Return VirtualSize
	End
	
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()
		
		canvas.Color = Color.White 
		canvas.DrawRect( 0, 0, App.ActiveWindow.Width , 25 )
		
		For Local bunny:=Eachin bunnies
			bunny.Update( canvas )
		Next
		
		canvas.Color = Color.Black
		canvas.DrawText( "Bunnymark="+bunnies.Length+"  FPS="+App.FPS+"  (LMB=+10 MMB=+100 RMB=+1000 +Alt=Remove)",10,5 )
 
	End	
	
	Method OnMouseEvent( event:MouseEvent ) Override
 
		If event.Type = EventType.MouseDown
			Local _len := 0  
			If event.Button = MouseButton.Left
				_len = 10
			Elseif event.Button = MouseButton.Middle
				_len = 100
			Elseif event.Button = MouseButton.Right
				_len = 1000
			End  
			
			If Keyboard.KeyDown( Key.LeftAlt ) Or Keyboard.KeyDown( Key.RightAlt )
				For Local n := 1 To _len
					If bunnies.Length Then bunnies.Pop()
				Next
			Else
				For Local n := 1 To _len
					bunnies.Push( New Bunny( Mouse.X, Mouse.Y,frames[ Rnd(4) ] ) )
				Next
			End
		End
		
	End	
 
End
 
 
'******************************************************************************************************
 
 
Class Bunny
	
	Global gravity := 0.1
	Global border := 32.0
	
	Field x: Float 
	Field y: Float 
	Field xspeed: Float
	Field yspeed: Float
	Field maxBounce:= 5.0
 
	Field image:Image
	
	Method New( x:Float,y:Float,image:Image )
		Self.x = x
		Self.y = y
		
		xspeed = Rnd( -10, 10 )
		
		Self.image=image
	End
	
	
	Method Update:Void( canvas:Canvas )
		yspeed += gravity
 
		y += yspeed
		x += xspeed
		
		If y < border*2
			y = border*2
			yspeed *= -1
			yspeed = Clamp( yspeed, 0.0, Float( maxBounce ) )
		End
		
		If y > App.ActiveWindow.Height - border
			y = App.ActiveWindow.Height - border
			yspeed = -random.Rnd( maxBounce * 3 )
		End
		
		If( x < border ) Or ( x > App.ActiveWindow.Width - border )
			xspeed *= -1
			x = Clamp( x, border, Float(App.ActiveWindow.Width - border ) )
		End
		
		canvas.DrawImage( image,x,y )
	End
	
End