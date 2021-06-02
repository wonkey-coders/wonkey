#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' How much food does the city have in it's stores....
'
'
'

'
' These are the variables for the city food window.
' x and y and w and height and the total count of food
'
Global foodsx:Int
Global foodsy:Int
Global foodsw:Int
Global foodsh:Int
Global foodcount:Int


Class MyWindow Extends Window

	Method New()
		' Set up the window variables
		foodsx = 100
		foodsy = 100
		foodsw = 150
		foodsh = 200
		foodcount = 10
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawText("Press Space or Press Left Mouse for Random food count",0,0)
		' Run the function that draws the city food
		' overview window.
		drawfoodwindow(canvas)
		' If we press the space bar then make the foodcount
		' variable a random number
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then 
			If Rnd(2)<1 ' once in a while
				foodcount=Rnd(1,20) 
			Else 'every other once in a while
				foodcount=Rnd(1,500) 
			End If		 	
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Based on the Civilization 1 city food
' screen.
'
Function drawfoodwindow(canvas:Canvas)
	'draw the white outline
	canvas.Color = Color.White
	canvas.DrawRect(foodsx-2,foodsy-2,foodsw+4,foodsh+4)
	'Draw the black screen
	canvas.Color = Color.Black
	canvas.DrawRect(foodsx,foodsy,foodsw,foodsh)
	' Draw a title label
	canvas.Color = Color.White
	canvas.DrawText("Food in City : ",foodsx,foodsy-15)
	' Count how much space we must have between the food 
	' images.
	Local mx:Float=16,my:Float=16
	Local exitloop:Bool=False
	While exitloop = False
		If ( (Float(foodsw-16)/my) * (Float(foodsh-8)/my )) > foodcount
		exitloop = True
		Else
		mx -= .1
		my -= .1
		End If
	Wend
	'
	' Drawing function (draw the food)
	Local mydrawfood := Lambda:Void(x:Int,y:Int)
		' Draw the food images
		canvas.Color = Color.Grey
		canvas.DrawCircle(x,y,8)		
		canvas.Color = New Color(.2,.2,.2)
		canvas.DrawCircle(x,y,7)
		canvas.Color = Color.Red
		canvas.DrawCircle(x,y,6)
		canvas.Color = Color.Brown
		canvas.DrawCircle(x,y,5)				
		canvas.Color = New Color(.9,.7,.3)
		canvas.DrawCircle(x-1,y-1,2)				
	End Lambda
	
	' Draw the food images 
	Local x:Float,y:Float
	Local count:Int
	Repeat
		' Draw the food images
		mydrawfood(foodsx+x+8,foodsy+y+8)
		' Left top down
		y+=my
		count+=1
		' if we are at the bottom then
		' increase x and reset y
		If y > Float(foodsh-16) Then
			x += mx
			y = 0
			' If the screen if filled then exit
			If x > Float(foodsw-16) Then 
				Exit
			End If
		End If
		' If the counter is bigger then the amount of food
		' then exit
		If count > foodcount Then Exit
	Forever
	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
