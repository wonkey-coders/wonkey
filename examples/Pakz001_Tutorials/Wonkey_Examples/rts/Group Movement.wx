#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class world
	Class point
		Field x:Int,y:Int,val:Int
		Method New(x:Int,y:Int,val:Int)
			Self.x = x
			Self.y = y
			Self.val = val
		End Method
	End Class
	Field tilewidth:Float,tileheight:Float
	Field mapwidth:Int,mapheight:Int
	Field screenwidth:Int,screenheight:Int
	Field pathto:Int[,]
	Method New(screenwidth:Int,screenheight:Int,mapwidth:Int,mapheight:Int)
		Self.screenwidth = screenwidth
		Self.screenheight = screenheight
		Self.mapwidth = mapwidth
		Self.mapheight = mapheight
		Self.tilewidth = Float(screenwidth) / Float(mapwidth)
		Self.tileheight = Float(screenheight) / Float(mapheight)
		pathto = New Int[mapwidth,mapheight]
		createpathto(20,20)
	End Method
	Method update()
		If Mouse.ButtonReleased(MouseButton.Left)
		Local destx:Int=Mouse.X / tilewidth
		Local desty:Int=Mouse.Y / tileheight
		createpathto(destx,desty)
		End If
	End Method
	Method createpathto(destx:Int,desty:Int)
		pathto = New Int[mapwidth,mapheight]
		' Flood the path
		Local mypoint:Stack<point> = New Stack<point>
		mypoint.Push(New point(destx,desty,1))
		pathto[destx,desty] = 1
		While mypoint.Length > 0
			Local x:Int=mypoint.Get(0).x
			Local y:Int=mypoint.Get(0).y
			Local v:Int=mypoint.Get(0).val
			mypoint.Erase(0)
			For Local y2:Int=y-1 To y+1
			For Local x2:Int=x-1 To x+1
				If x2<0 Or x2>=mapwidth Or y2<0 Or y2>=mapheight Then Continue
				If pathto[x2,y2] = 0
					pathto[x2,y2] = v+1
					mypoint.Push(New point(x2,y2,v+1))
				End if
			Next
			Next
		Wend
	End Method	
End Class

Class units
	Field px:Float,py:Float
	Field pw:Int=8,ph:Int=8
	Field speed:Float
	Field deleteme:Bool=False
	Field selected:Bool=False
	Field moving:Bool=True
	Field shakestop:Int=0
	Method New(x:Int,y:Int)
		Self.px = x
		Self.py = y
		speed = Rnd(.05,.3)		
	End Method	
	Method update()
		If moving=False Then Return
		Local tx:Int=px/myworld.tilewidth
		Local ty:Int=py/myworld.tileheight
		Local v:Int
		If tx<0 Or ty<0 Or tx>=myworld.mapwidth Or ty>=myworld.mapheight Then 			
			v=100
			Else
			v=myworld.pathto[tx,ty]
		End if
		For Local y:Int=-1 To 1
		For Local x:Int=-1 To 1
			If tx+x<0 Or ty+y<0 Or tx+x>=myworld.mapwidth Or ty+y>=myworld.mapheight Then Continue
			If myworld.pathto[tx+x,ty+y] <= v Then
				If myworld.pathto[tx+x,ty+y] > 1
					Local dont:Bool=False
					For Local i:Int=0 Until myunits.Length
						If myunits.Get(i).px <> px And myunits.Get(i).py <> py							
							If distance(myunits.Get(i).px,myunits.Get(i).py,px,py) < 16
								dont=True
							End If							
						End If						
					Next
					If dont=True Then Return
					px += Float(x)*speed
					py += Float(y)*speed

				End If
			End If
		Next
		Next
		' Push them appart if to close to each other
		
		For Local i:Int=0 Until myunits.Length
		For Local j:Int=0 Until myunits.Length
			If i<>j			
				Local x1:Int=myunits.Get(i).px
				Local y1:Int=myunits.Get(i).py				
				Local x2:Int=myunits.Get(j).px
				Local y2:Int=myunits.Get(j).py
				
				If distance(x1,y1,x2,y2) < 20 Then
					Local a:Float=getangle(x2,y2,x1,y1) 
					myunits.Get(i).px += Cos(a+Rnd(-Pi/2,Pi/2))/10
					myunits.Get(i).py += Sin(a+Rnd(-Pi/2,Pi/2))/10
				End if
			End If
		Next
		Next

	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.Pink
		canvas.DrawOval(px,py,pw,ph)
	End Method
	Method distance:Int(x1:Int,y1:Int,x2:Int,y2:Int)
		Return Abs(x2-x1)+Abs(y2-y1)
	End Method
	Function getangle:float(x1:Int,y1:Int,x2:Int,y2:Int)
		Return ATan2(y2-y1, x2-x1)
	End Function 	
End Class

Global myworld:world
Global myunits:Stack<units>

Class MyWindow Extends Window
	
	Method New()
		SeedRnd(Microsecs())
		myworld = New world(Width,Height,50,50)
		myunits = New Stack<units>
		For Local i:Int=0 Until 15
			myunits.Push(New units(Rnd(myworld.mapwidth)*myworld.tilewidth,Rnd(myworld.mapheight)*myworld.tileheight))
		Next
	End method
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
		myworld.update()
		
		For Local i:Int=0 Until myunits.Length
			myunits.Get(i).update()
		Next

		For Local i:Int=0 Until myunits.Length
			myunits.Get(i).draw(canvas)
		Next
		
		canvas.Color = Color.White
		canvas.DrawText("Press mouse on screen to move units..",0,0)
	End Method	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
