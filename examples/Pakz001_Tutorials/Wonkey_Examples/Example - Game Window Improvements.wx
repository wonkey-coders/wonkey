#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' What improvements are in the city and how much
' do they give and cost the city...
'
'
' These are the variables for the improvements window.
' x and y and w and height.
'
Global improvementsx:Int
Global improvementsy:Int
Global improvementsw:Int
Global improvementsh:Int
'In each list item this class is used
Class improvements
	Field name:String
	Field amount:Int'how much of these do we have
	Field foodout:Int 'how much food cost per turn
	Field resourceout:Int 'how much resource cost per turn
	Field foodin:Int'how much food generated per turn
	Field resourcein:Int'how much resources generated per tun
	' When we create a new item we set it with
	' the name, the amount there and the food it costs
	' the resources it costs and the food it generates
	' and the resources it generates.
	Method New(name:String,amount:Int,foodout:Int,resourceout:int,foodin:int,resourcein:Int)
		Self.name = name
		Self.amount = amount
		Self.foodout = foodout 'total amount needs to be inputted
		Self.resourceout = resourceout'total amount needs to be inputted
		Self.foodin = foodin'total amount needs to be inputted
		Self.resourcein = resourcein'total amount needs to be inputted
	End Method	
End Class
' This is the list we use for the window (fileld with a class)
Global improvementslist:List<improvements>
' The page position. (next page - previous page)
Global improvementslistpos:Int=0


Class MyWindow Extends Window

	Method New()
		' Set up the window variables
		improvementsx = 100
		improvementsy = 100
		improvementsw = 180
		improvementsh = 200
		improvementslist = New List<improvements>
		improvementslist.Add(New improvements("Barracks",1,0,1,0,0))
		improvementslist.Add(New improvements("Walls",1,0,1,0,0))
		improvementslist.Add(New improvements("Farm",3,0,0,30,0))
		improvementslist.Add(New improvements("Mine",2,0,0,0,2))
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		'
		canvas.DrawText("Press Space or Press Right Mouse for Random inventory",0,0)
		' Run the function that draws the city food
		' overview window.
		drawimprovementswindow(canvas)
		' If we press the space bar then make the foodcount
		' variable a random number
		If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Right) Then 
			If Rnd(2)<1.5 ' once in a while
				improvementslist = New List<improvements>				
				improvementslist.Add(New improvements("First",Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5)))
				Local total:Int=Rnd(20,50) 
				For Local i:=0 Until total
					improvementslist.Add(New improvements("City thing",Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5)))
				Next				
				improvementslist.Add(New improvements("Last",Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5),Rnd(0,5)))
			Else 'every other once in a while
				improvementslist = New List<improvements>
				improvementslist.Add(New improvements("First",Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25)))
				Local total:Int=Rnd(5,50)
				For Local i:=0 Until total
					improvementslist.Add(New improvements("City thing",Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25)))
				Next								
				improvementslist.Add(New improvements("Last",Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25),Rnd(0,25)))
			End If		 	
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

' Based somewhat on the Civilization 2 city
' screen.
'
Function drawimprovementswindow(canvas:Canvas)
	'draw the white outline
	canvas.Color = Color.White
	canvas.DrawRect(improvementsx-2,improvementsy-2,improvementsw+4,improvementsh+4)
	'Draw the black screen
	canvas.Color = Color.Black
	canvas.DrawRect(improvementsx,improvementsy,improvementsw,improvementsh)
	' Draw a title label
	canvas.Color = Color.White
	canvas.DrawText("City Improvements : ",improvementsx,improvementsy-15)
	'
	'Lambda functions below
	
	' Drawing function (draw the food)
	Local mydrawfood := Lambda:Void(x:Int,y:Int,dark:Bool)
		' Draw the food images
		canvas.Color = Color.Grey
		canvas.DrawCircle(x,y,8)		
		canvas.Color = New Color(.2,.2,.2)
		canvas.DrawCircle(x,y,7)
		If dark = False Then
			canvas.Color = Color.Red
			canvas.DrawCircle(x,y,6)
			canvas.Color = Color.Brown
			canvas.DrawCircle(x,y,5)				
			canvas.Color = New Color(.9,.7,.3)
			canvas.DrawCircle(x-1,y-1,2)				
		Else
			canvas.Color = New Color(.3,0,0)
			canvas.DrawCircle(x,y,6)
			canvas.Color = New Color(.4,.2,.0)
			canvas.DrawCircle(x,y,5)				
			canvas.Color = New Color(.6,.3,.1)
			canvas.DrawCircle(x-1,y-1,2)							
		End If
	End Lambda
	'Drawing function(draw the resource)
	Local mydrawresource := Lambda:Void(x:Int,y:Int,dark:Bool)
		' Draw the resource image
		canvas.Color = Color.Grey
		canvas.DrawCircle(x,y,8)		
		If dark = False
			canvas.Color = New Color(.2,.2,.2)
			canvas.DrawCircle(x,y,7)
			canvas.Color = New Color(.7,.7,.7)
			canvas.DrawCircle(x,y,6)				
			canvas.Color = Color.White
			canvas.DrawCircle(x-1,y-1,2)				
		Else
			canvas.Color = New Color(.2,.2,.2)
			canvas.DrawCircle(x,y,7)
			canvas.Color = New Color(.4,.4,.4)
			canvas.DrawCircle(x,y,6)				
			canvas.Color = New Color(.6,.6,.6)
			canvas.DrawCircle(x-1,y-1,2)							
		End If
	End Lambda	
	' table num x
	Local t1x:Int=0
	Local t2x:Int=90
	Local t3x:Int=130
	Local t4x:Int=170
	Local t5x:Int=210
	' window x and y
	Local x1:Int=improvementsx
	Local y1:Int=improvementsy
	'
	Local itemsfitonpage:Int=(improvementsh-20)/20
	
	' pages interaction
	If improvementslist.Count() > itemsfitonpage		
		Local prevpagebuttonx:Int=x1
		Local prevpagebuttony:Int=y1+improvementsh-20
		Local pagebuttonw:Int=86
		Local pagebuttonh:Int=20
		Local nextpagebuttonx:Int=x1+pagebuttonw
		Local nextpagebuttony:Int=y1+improvementsh-20
		canvas.Color = Color.Yellow
		canvas.DrawText("Prev. Page",prevpagebuttonx,prevpagebuttony)
		canvas.DrawText("Next. Page",nextpagebuttonx,nextpagebuttony)
		If rectsoverlap(nextpagebuttonx,nextpagebuttony,pagebuttonw,pagebuttonh,Mouse.X,Mouse.Y,1,1)
			If Mouse.ButtonReleased(MouseButton.Left)
				If improvementslistpos+itemsfitonpage<improvementslist.Count() Then
					improvementslistpos+=itemsfitonpage									
				End If
			End If
		End If
		If rectsoverlap(prevpagebuttonx,prevpagebuttony,pagebuttonw,pagebuttonh,Mouse.X,Mouse.Y,1,1)
			If Mouse.ButtonReleased(MouseButton.Left)
				If improvementslistpos-itemsfitonpage >= 0
					improvementslistpos-=itemsfitonpage
				End If
			End If
		End If

	End If
	' draw variables
	Local y2:Int=0 'Increases with every line drawn with lineheight estimate(20)
	Local count:Int=0 'Holds the current position in the each loop
	Local drawnonpage:Int=0 'Holds the amount of lines we drawn
	'Loop through the city improvements items list
	For Local i:=Eachin improvementslist		
		' We will draw the list if it is at the current page position and until
		' we have drawn all the items that fit on the page.		
		If count >= improvementslistpos And drawnonpage<itemsfitonpage then
			' count how many we have drawn
			drawnonpage+=1
			canvas.Color = Color.White
			canvas.DrawText(i.name,x1+t1x,y1+y2)
			' draw the in/out
			Local sx:Float=20
			' total count of all to be drawn
			Local tc:Int=i.foodin+i.resourcein+i.foodout+i.resourceout
			' space we have to draw it in
			Local space:Int=improvementsw-t2x-10
			' get the x spacing based on the total amount
			' of things to be drawn.
			Repeat
				If Float(tc)*sx > space
					sx-=.1
				Else
					Exit
				End If
			Forever
			' Draw the costs and gains		
			Local x2:Float=-sx
			' foodin
			For Local i2:Int=0 Until i.foodin
				mydrawfood(x1+x2+t2x+sx,y1+y2+10,False)
				x2+=sx		
			Next		
			' resourcein
			For Local i2:Int=0 Until i.resourcein
				mydrawresource(x1+x2+t2x+sx,y1+y2+10,False)
				x2+=sx		
			Next
			' foodout
			For Local i2:Int=0 Until i.foodout
				mydrawfood(x1+x2+t2x+sx,y1+y2+10,True)
				x2+=sx		
			Next
			' resourceout
			For Local i2:Int=0 Until i.resourceout
				mydrawresource(x1+x2+t2x+sx,y1+y2+10,True)
				x2+=sx		
			Next		
			'
			y2+=20 'for the next line position increase 20 pixels
		End If
		count+=1
	Next
End Function

' Helper function (rectangle collision)
Function rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
    Return True
End	 Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
