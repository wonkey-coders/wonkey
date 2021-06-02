#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
' City Population window

'
' These are the variables for the city population window.
' x and y and w and height and the 
' current population count
'
Global popx:Int
Global popy:Int
Global popw:Int
Global poph:Int
Global popcount:Int



Class MyWindow Extends Window

	Method New()
		' Set up the population window variables
		popx = 100
		popy = 100
		popw = 320
		poph = 40
		popcount = 4
		

	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawText("Press Space or Press Left Mouse for Random production.",0,0)
		' Run the function that draws the city build
		' overview window.
		drawpopulationwindow(canvas)
		' If we press the space bar then make the population count
		' variable a random number
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then 
			SeedRnd(Millisecs())
			If Rnd(2)<1 ' once in a while
				popcount = Rnd(1,10)							
			Else 'every other once in a while
				popcount = Rnd(10,100)								
			End If		 			 	
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Based on the Civilization 1 population window
'
Function drawpopulationwindow(canvas:Canvas)
	'draw the white outline
	canvas.Color = Color.White
	canvas.DrawRect(popx-2,popy-2,popw+4,poph+4)
	'Draw the black screen
	canvas.Color = Color.Black
	canvas.DrawRect(popx,popy,popw,poph)
	' Draw a title label
	canvas.Color = Color.White
	canvas.DrawText("Population : ",popx,popy-15)
	' Count how much space we must have between the people
	' images.
	Local mx:Float=16,my:Float=16
	Local exitloop:Bool=False
	While exitloop = False
		If ( (Float(popw-16)/my) ) > popcount
		exitloop = True
		Else
		mx -= .1
		my -= .1
		End If
	Wend
	
	'Drawing function(draw the resource)
	Local mydrawperson := Lambda:Void(x:Int,y:Int)
		' Draw the resource image
		'head
		canvas.Color = New Color(.8,.6,.2)
		canvas.DrawCircle(x,y,5)		
		'headhighlight
		canvas.Color = New Color(1,.8,.5)
		canvas.DrawCircle(x-2,y-2,1)
		'eyes
		canvas.Color = New Color(1,1,1)
		canvas.DrawCircle(x-2,y,1)
		canvas.DrawCircle(x+3,y,1)
		canvas.Color = New Color(0,0,0)
		canvas.DrawPoint(x-1,y)
		canvas.DrawPoint(x+2,y)
		'mouth
		canvas.Color = New Color(0,0,0)
		canvas.DrawPoint(x,y+4)
		'body
		canvas.Color = New Color(.1,.4,1)		
		canvas.DrawOval(x-2,y+3,8,8)				
		'body highlight
		canvas.Color = New Color(.4,.7,1)		
		canvas.DrawOval(x-6,y+3,12,2)				
		'arms
		canvas.Color = New Color(.3,.7,1)		
		canvas.DrawOval(x-7,y+3,5,11)				
		canvas.DrawOval(x,y+3,5,11)				
		'arms highlight
		canvas.Color = New Color(.6,1,3)		
		canvas.DrawOval(x-7,y+5,2,3)				
		canvas.DrawOval(x,y+5,2,3)				
		'legs
		canvas.Color = New Color(.7,.3,.1)		
		canvas.DrawOval(x-5,y+9,4,10)				
		canvas.DrawOval(x,y+9,4,10)				
		'feet
		canvas.Color = New Color(.9,.5,.2)		
		canvas.DrawOval(x-5,y+15,3,3)				
		canvas.DrawOval(x,y+15,3,3)				
	End Lambda
	
	' Draw the population images 
	Local x:Float,y:Float
	Local count:Int
	Repeat
		' Draw the population image
		mydrawperson(popx+x+8,popy+y+8)
		' Left top down
		x+=mx
		count+=1		
		' if we are at the bottom then
		' increase x and reset y
		If x > Float(popw-16) Or count>popcount Then
			Exit
		End If
	Forever
	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
