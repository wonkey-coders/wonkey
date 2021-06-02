' Camouflage pattern generator

#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class camopattern
	Field maplayer:Int[,]
	Field mapwidth:Int,mapheight:Int
	Field screenwidth:Int,screenheight:Int	
	Field im:Image
	Field can:Canvas
	Method New(w:Int,h:Int)
		mapwidth = w
		mapheight = h
		im = New Image(mapwidth,mapheight)
		can = New Canvas(im)
		' Create a green background
		can.Clear(New Color(1.0/255.0*80.0,1.0/255.0*120.0,1.0/255.0*80.0))
		can.Flush()
		maplayer = New Int[mapwidth,mapheight]
		' Create the brown pattern
		createpattern(New Color(1.0/255.0*100.0,1.0/255.0*86.0,1.0/255.0*60.0))
		' Create the Yellow pattern
		createpattern(New Color(1.0/255.0*200.0,1.0/255.0*185.0,1.0/255.0*130.0))
		' Create the Black pattern
		createpattern(New Color(1.0/255.0*50.0,1.0/255.0*60.0,1.0/255.0*65.0))
		
	End Method
	' Here we create the pattern
	Method createpattern(mycol:Color)
		maplayer = New Int[mapwidth,mapheight]
		
		' Create random dots on the layer1
		For Local i:Int=0 Until (mapwidth*mapheight)/2000
			Local x:Int=Rnd(mapwidth)
			Local y:Int=Rnd(mapheight)			
			maplayer[x,y] = 1
		Next
		' Grow the layers
		For Local i:Int=0 Until (mapwidth*mapheight)*2
			Local x:Int=Rnd(mapwidth)
			Local y:Int=Rnd(mapheight)
			If maplayer[x,y] = 1
				For Local y2:Int=y-Rnd(2) To y+Rnd(2)
				For Local x2:Int=x-Rnd(5) To x+Rnd(5)
					If x2<0 Or y2<0 Or x2>=mapwidth Or y2>=mapheight Then Continue
					maplayer[x2,y2] = 1
				Next
				Next
			End If
		Next
		' Put the layer on the image
		can.Color = mycol
		For Local y:Int=0 Until mapheight
		For Local x:Int=0 Until mapwidth
			If maplayer[x,y] = 1
				can.DrawPoint(x,y)
			End If
		Next
		Next
		can.Flush()
	End Method
	' Draw the image
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawImage(im,0,0)
	End Method
End Class

Global mycamopattern:camopattern

Class MyWindow Extends Window

	Method New()		
		mycamopattern = New camopattern(Width,Height)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mycamopattern.draw(canvas)
		If Keyboard.KeyReleased(Key.Space) Then 
			SeedRnd(Millisecs())
			mycamopattern = New camopattern(Width,Height)
		End If
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
