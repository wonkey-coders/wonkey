#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
' City current production window. 

'
' These are the variables for the city production window.
' x and y and w and height and the 
' current amount and required amount of resources
'
Global prod2x:Int
Global prod2y:Int
Global prod2w:Int
Global prod2h:Int
Global prod2currentresourcescount:Int
Global prod2requiredresourcescount:Int


Class MyWindow Extends Window

	Method New()
		' Set up the window variables
		prod2x = 100
		prod2y = 100
		prod2w = 150
		prod2h = 200
		prod2currentresourcescount = 0
		prod2requiredresourcescount = 0

	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawText("Press Space or Press Left Mouse for Random production.",0,0)
		' Run the function that draws the city build
		' overview window.
		drawproductionwindow(canvas)
		' If we press the space bar then make the build resources
		' variable a random number
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then 
			If Rnd(2)<1 ' once in a while
				prod2requiredresourcescount = Rnd(30)
				prod2currentresourcescount = Rnd(0,prod2requiredresourcescount)
				

			Else 'every other once in a while
				prod2requiredresourcescount = Rnd(330)
				prod2currentresourcescount = Rnd(0,prod2requiredresourcescount)
				
			End If		 			 	
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Based on the Civilization 1 city build
' production window
'
Function drawproductionwindow(canvas:Canvas)
	'draw the white outline
	canvas.Color = Color.White
	canvas.DrawRect(prod2x-2,prod2y-2,prod2w+4,prod2h+4)
	'Draw the black screen
	canvas.Color = Color.Black
	canvas.DrawRect(prod2x,prod2y,prod2w,prod2h)
	' Draw a title label
	canvas.Color = Color.White
	canvas.DrawText("Currently creating : ",prod2x,prod2y-15)
	' Count how much space we must have between the resources
	' images.
	Local mx:Float=16,my:Float=16
	Local exitloop:Bool=False
	While exitloop = False
		If ( (Float(prod2w-16)/my) * (Float(prod2h-8)/my )) > prod2requiredresourcescount
		exitloop = True
		Else
		mx -= .1
		my -= .1
		End If
	Wend
	
	'Drawing function(draw the resource)
	Local mydrawresource := Lambda:Void(x:Int,y:Int)
		' Draw the resource image
		canvas.Color = Color.Grey
		canvas.DrawCircle(x,y,8)		
		canvas.Color = New Color(.2,.2,.2)
		canvas.DrawCircle(x,y,7)
		canvas.Color = New Color(.7,.7,.7)
		canvas.DrawCircle(x,y,6)				
		canvas.Color = Color.White
		canvas.DrawCircle(x-1,y-1,2)				
	End Lambda
	
	' Draw the food images 
	Local x:Float,y:Float
	Local count:Int
	' if we have nothing to do then exit the method
	If prod2currentresourcescount = 0 Then Return
	' draw everything	
	Repeat
		' Draw the resources images
		mydrawresource(prod2x+x+8,prod2y+y+8)
		' Left top down
		x+=mx
		count+=1
		' if we have nothing more to draw then exit
		If count>prod2currentresourcescount Then Exit
		' if we are at the bottom then
		' increase x and reset y
		If x > Float(prod2w-16) Then
			y += my
			x = 0
			' If the screen if filled then exit
			If y > Float(prod2h-16) Then 
				Exit
			End If
		End If
	Forever
	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
