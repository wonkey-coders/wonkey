#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
' City resource window coordinates and variables
Global resourcex:Int
Global resourcey:Int
Global resourcew:Int
Global resourceh:Int
' count is the amount used and surplus is what we have left
Global resourcecount:Int
Global resourcesurpluscount:Int
Global resourcefoodsurpluscount:Int
Global resourcefoodcount:Int



Class MyWindow Extends Window

	Method New()
		' fil in the variables
		resourcex = 100
		resourcey = 100
		resourcew = 200
		resourceh = 80
		resourcecount = 0
		resourcesurpluscount = 2
		resourcefoodcount = 0
		resourcefoodsurpluscount = 2
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawText("Press Space or Press Left Mouse for Random food/resource count",0,0)
		' Run the function that draws the city food
		' overview window.
		drawresourcewindow(canvas)
		' If we press the space bar then make the food and resource count
		' variables a random number
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left) Then 
			If Rnd(2)<1 ' once in a while
				resourcefoodcount=Rnd(1,20) 
				resourcecount=Rnd(1,20) 
				resourcefoodsurpluscount=Rnd(0,10) 
				resourcesurpluscount=Rnd(0,10) 
				
			Else 'every other once in a while
				resourcefoodcount=Rnd(1,100) 
				resourcecount=Rnd(1,100) 
				resourcefoodsurpluscount=Rnd(0,100) 
				resourcesurpluscount=Rnd(0,100) 
			End If		 	
		 	
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Based on the Civilization 1 city resources window
'
Function drawresourcewindow(canvas:Canvas)
	'draw the white outline
	canvas.Color = Color.White
	canvas.DrawRect(resourcex-2,resourcey-2,resourcew+4,resourceh+4)
	'Draw the black screen
	canvas.Color = Color.Black
	canvas.DrawRect(resourcex,resourcey,resourcew,resourceh)
	' Draw a title label
	canvas.Color = Color.White
	canvas.DrawText("City Resources : ",resourcex,resourcey-15)
	
	'Lambda functions below
	
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
	
	'
	' This function draws a particula resource.
	' tp = 0 - food
	' tp = 1 - resource (goods ore ect.)
	'	
	Local drawresource:=Lambda:Void(tp:String)
	
		' Count how much space we must have between the food 
		' images. Store the step value in mx
		Local mx:Float=16	
		Repeat
			If tp = 0
				If ( Float(resourcew-48)/mx) > (resourcefoodcount+resourcefoodsurpluscount)-1
					Exit
				Else
					mx -= .1		
				End If
			Else 
				If ( Float(resourcew-48)/mx) > (resourcecount+resourcesurpluscount)-1
					Exit
				Else
					mx -= .1		
				End If
			End If				
		Forever

		' Here we go from left to right and draw
		' the images.
		'
		Local x:Float=0,y:Float
		Local count:Int
		Local switch:Bool=False
		Repeat

			If tp = 0 Then mydrawfood(resourcex+x+8,resourcey+y+8)
			If tp = 1 Then mydrawresource(resourcex+x+8,resourcey+y+32)
			' Left to right
			x+=mx
			count+=1
			' if we are at the end of the window
			' then exit (everything drawn)
			If x > Float(resourcew-16) Then
				Exit
			End If

			If switch = False  And resourcefoodcount>0
				If tp = 0 And count > resourcefoodcount-1 Then 
					x+=16
					switch = True
				End If
			End If
			If switch = False  And resourcecount>0
				If tp = 1 And count > resourcecount-1
					x+=16
					switch = True
				End If
			End If
			
			' If we drawn the food and resourses then draw the
			' surplus
			If tp = 1 And count+1 > resourcecount + resourcesurpluscount Then Exit
			If tp = 0 And count+1 > resourcefoodcount + resourcefoodsurpluscount Then exit
		Forever
	End Lambda

	' This calls the functions and fills the resource window
	'
	drawresource(0)
	drawresource(1)
	canvas.Color = Color.White
	canvas.DrawText("Food :",resourcex,resourcey+48)
	mydrawfood(resourcex+60,resourcey+56)
	canvas.DrawText("Resource :",resourcex+80,resourcey+48)
	mydrawresource(resourcex+180,resourcey+56)
	
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
