#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Enum palette
	green=1,greenlight=2,greendark=3,greenlighter=5
	brown=10,brownlight=11,browndark=12,
	black=13	
End Enum
Class art
	Field mw:Int,mh:Int
	Field map:Int[,]
	Field treeim:Image
	Field treecan:Canvas
	Method New(w:Int,h:int)
		Self.mw = w
		Self.mh = h
		map = New Int[w,h]
		generatetree()
		createimage()
	End Method
	'
	'
	'
	Method createimage()
		treeim = New Image(mw,mh)
		treecan = New Canvas(treeim)
		treecan.Clear(New Color(0,0,0,0))
		treecan.Flush()
		drawmap(treecan,0,0,1)
		treecan.Flush()
	End Method
	'
	'
	'
	Method generatetree()
		'outlines black
		fillrect(mw/2-mw/8,mh-mh/4,mw/4,mh/4,palette.black)
		filloval(mw/2,mh/2,mw/3,palette.black)
		' tree main
		filloval(mw/2,mh/2.6,mw/4-2,palette.green)
		filloval(mw/2,mh/2-1,mw/3-1,palette.green)
		' stump
		fillrect(mw/2-mw/8+1,mh-mh/4+1,mw/4-2,mh/4-2,palette.browndark)
		' sides
		'fillrect(mw/2-mw/6,mh-mh/8,mw/6,mh/8,palette.browndark)
		'fillrect(mw/1.9,mh-mh/8,mw/6,mh/8,palette.browndark)
		For Local y:Int=mh-mh/10 Until mh-1
			map[mw/2-mw/6,y] = palette.browndark
			map[mw/2-mw/6+1,y-1] = palette.browndark
			map[mw/2-mw/6+1,y+1] = palette.browndark

			map[mw/1.55,y] = palette.browndark
			map[mw/1.55-1,y-1] = palette.browndark
			map[mw/1.55-1,y+1] = palette.browndark
		Next
		fillrect(mw/2-mw/6,mh-2,mw/3.1,1,palette.black)
		'
		' leaves light
		Local an:Float=0
		For Local x:Int=0 Until mw/2.3
			For Local y:Int=0 Until 5
				Local c:Int=palette.greenlighter
				If y>1 Then 				
					c = palette.greenlight
				End If
				Local y2:Float=y+mh/2-mh/5
				Local x2:Float=x+mw/2-mw/4
				x2 += Cos(an)*3
				y2 += Sin(an)*3
				an-=.05
				'x2 += Cos(x)
				'y2 += Sin(x)
				map[x2,y2] = c
				map[x2+1,y2+1] = c
			Next
		Next

		' leases center
		an=0
		Local st:Int=0		
		For Local x:Int=0 Until mw/1.8
			st+=1
			If st>mw/20 Then st=0
			For Local y:Int=0 Until 3
				Local c:Int=palette.greendark
				Local y2:Float=y+mh/1.9
				Local x2:Float=x+mw/2-mw/3.5
				x2 += Cos(an)*3
				y2 += Sin(an)*3
				an-=.08
				'x2 += Cos(x)
				'y2 += Sin(x)
				If st<mw/40
				map[x2,y2] = c
				map[x2+1,y2+1] = c
				map[x2+1,y2-1] = c
				Endif
			Next
		Next

	
		' leases bottom dark
		an=0
		For Local x:Int=0 Until mw/2.3
			For Local y:Int=0 Until 5
				Local c:Int=palette.green
				If y>1 Then 				
					c = palette.greendark
				End If
				Local y2:Float=y+mh/2+mh/6
				Local x2:Float=x+mw/2-mw/4
				x2 += Cos(an)*3
				y2 += Sin(an)*3
				an-=.05
				'x2 += Cos(x)
				'y2 += Sin(x)
				map[x2,y2] = c
				'map[x2+1,y2+1] = c
				For Local z:Int=y2+1 To mh
					If map[x2,z] <> palette.green Then Exit
					map[x2,z] = palette.greendark
				Next
			Next
		Next


	End Method
	'
	' Create a rectangle of colval inside map[,]
	'
	Method fillrect(x1:Int,y1:Int,w:Int,h:Int,colval:Int)
		For Local y2:Int=y1 Until y1+h
		For Local x2:Int=x1 Until x1+w
			If x2<0 Or y2<0 Or x2>=mw Or y2>=mh Then Continue
			map[x2,y2] = colval
		Next
		Next
	End Method
	'
	' Create a filled circle of colval inside map[,]
	'
    Method filloval(x1:Int,y1:Int,radius:Int,colval:Int)
        For Local y2:Int=-radius To radius
        For Local x2:Int=-radius To radius
            If (y2*y2+x2*x2) <= radius*radius+radius*0.8
            	Local x3:Int = x2+x1
            	Local y3:Int = y2+y1
				If x3<0 Or y3<0 Or x3>=mw Or y3>=mh Then Continue
            	map[x3,y3] = colval                            
            End If
        Next
        Next      
    End Method    
    '
    '
    '
    Method drawmap(canvas:Canvas,x:Int,y:Int,scale:Int=1)
	    For Local y1:Int=0 Until mh
		For Local x1:Int=0 Until mw
			Local x2:Int=(x1*scale)+x
			Local y2:Int=(y1*scale)+y
			Select map[x1,y1]
				Case 0 ' nothing
					Continue
				Case palette.black 'black
					canvas.Color = Color.Black
				Case palette.green 'green base
					canvas.Color = Color.Green.Blend(Color.Black,.2)
				Case palette.browndark 'green base
					canvas.Color = Color.Brown.Blend(Color.Black,.5)
				Case palette.greenlight
					canvas.Color = Color.Green.Blend(Color.White,.3)
				Case palette.greenlighter
					canvas.Color = Color.Green.Blend(Color.White,.6)

				Case palette.greendark
					canvas.Color = Color.Green.Blend(Color.Black,.5)

			End Select
			canvas.DrawRect(x2,y2,scale,scale)
		Next
		Next
	End Method
End Class

Global myart:art

Class MyWindow Extends Window
	
	Method New()
		myart = New art(64,64)
	End method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		canvas.Clear(Color.Green)
		canvas.Color = Color.White
		For Local y:Int=0 Until 10
		For Local x:Int=0 Until 10
			canvas.DrawImage(myart.treeim,x*64,y*64)
		Next
		Next
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method

End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
