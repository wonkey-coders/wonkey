#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class pulldownmenu
	Field menu:String[] = New String[]("About","File","Settings","Selection")
	Field mysubmenu:= New Stack<alist>
	Field menuopen:Bool=False
	Class alist
		Field id:String
		Field lx:Int,ly:Int
		Field lw:Int,lh:Int
		Field item:= New Stack<String>
		Method New(id:String,x:Int,y:Int,w:Int,h:int)
		Self.id = id
		lx = x
		ly = y
		lw = w
		lh = h
		item.Push("This")
		item.Push("is")
		item.Push("a")
		item.Push("test")
		End Method
		Method draw(canvas:Canvas)
			canvas.Color=Color.White
			canvas.DrawRect(lx,ly,lw,lh)
			canvas.Color=Color.Black
			Local y:=0
			For Local i:=Eachin item
				canvas.DrawText(i,lx,ly+y*15)
				y+=1
			Next
		End Method		
	End Class
	Method New()
		
	End Method
	Method update()
		' press on menu items
		If Mouse.ButtonReleased(MouseButton.Left) Then 
		For Local i:=0 Until menu.Length
			If rectsoverlap(Mouse.X,Mouse.Y,1,1,i*80,0,80,15)
				'App.Terminate()
				If i=0					
					If menuopen = True
						mysubmenu.Clear()
						menuopen = False
						return
					End If 
					If menuopen = False
						mysubmenu.Clear()
						mysubmenu.Push(New alist("About",i*80,15,200,300))			
						menuopen = True
					End If
				End If
				If i=1
					If menuopen = True
						mysubmenu.Clear()
						menuopen = False
						return
					End If 
					If menuopen = False
						mysubmenu.Clear()
						mysubmenu.Push(New alist("File",i*80,15,200,300))			
						menuopen = True
					End If
				End If
				If i=2
					If menuopen = True
						mysubmenu.Clear()
						menuopen = False
						Return
					End If 
					If menuopen = False
						mysubmenu.Clear()
						mysubmenu.Push(New alist("Settings",i*80,15,200,300))			
						menuopen = True
					End If
				End If
				If i=3
					If menuopen = True
						mysubmenu.Clear()
						menuopen = False
						Return
					End If 
					If menuopen = False
						mysubmenu.Clear()
						mysubmenu.Push(New alist("Selection",i*80,15,200,300))			
						menuopen = True
					End If
				End If
				
			Endif
		Next		
		End If 
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		For Local x:=0 Until menu.Length
			canvas.DrawText(menu[x],x*80,0)			
		Next
		For Local i:=Eachin mysubmenu
			i.draw(canvas)
		Next
	End Method
	method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End Method	
End Class

Global mypulldownmenu:pulldownmenu

Class MyWindow Extends Window

	Method New()
		mypulldownmenu = New pulldownmenu()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mypulldownmenu.update()
		mypulldownmenu.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
