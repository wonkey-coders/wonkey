#Import "<std>"
#Import "<mojo>"



Using std..
Using mojo..

Class npc
	Field nx:Int,ny:Int,nw:Int,nh:Int
	Field id:String
	Field hasquest:Bool
	Method New(id:String,x:Int,y:Int)
		Self.nx = x
		Self.ny = y
		Self.nw = 10
		Self.nh = 10
		Self.id = id
		Select id
			Case "Old man"
			hasquest = True
		End Select
	End Method
	Method draw(canvas:Canvas)
		Select id
			Case "Old man"
			canvas.Color = Color.Yellow
			canvas.DrawRect(nx,ny,nw,nh)
		End Select
	End Method	
End Class

Class player
	Field px:Float,py:Float
	Field pw:Int,ph:Int
	Field pinv:Int[] = New Int[50]
	Field delay:Double
	Field lock:Bool=False
	Enum inventory
		gold=1,
		xp=2,
		flowers=3
	End Enum 
	Method New(x:Int,y:int)
		pw = 10
		ph = 10
		Self.px = x
		Self.py = y		
	End Method
	Method update()
		If lock = True Then Return
		If Keyboard.KeyDown(Key.Right)
			px+=1
		End If
		If Keyboard.KeyDown(Key.Left)
			px-=1
		End If
		If Keyboard.KeyDown(Key.Up)
			py-=1
		End If
		If Keyboard.KeyDown(Key.Down)
			py+=1
		End If
		harvest()
		If Keyboard.KeyReleased(Key.Space) Then inact()
		If Keyboard.KeyReleased(Key.Q) Then resetquests()
	End Method
	Method resetquests()
		For Local i:=Eachin myquest
			i.queststate = i.state.begin
		Next
	End Method
	Method inact()
		If delay>Millisecs() Then Return
		For Local i:=Eachin mynpc
			If rectsoverlap(px,py,pw,ph,i.nx,i.ny,i.nw,i.nh)
				If i.id = "Old man"
					If hasquest("Old man") = False
						myquest.Push(New quest("Old man",10,10))
						myquestui.setquest(i.id)
						myquestui.delay = Millisecs() + 300
						myplayer.lock = True
						myquestui.active = True
					Else 'has a quest						
						myquestui.setquest(i.id)
						myquestui.delay = Millisecs() + 300
						myplayer.lock = True
						myquestui.active = True
					End If
				End If
			End If 	
		Next
	End Method
	Method hasquest:Bool(id:string)
		For Local i:=Eachin myquest
			If i.id = id Then Return True
		Next
		Return False
	End Method
	Method harvest()
		Local tx:Int=(px+myworld.tw/2)/myworld.tw
		Local ty:Int=(py+myworld.tw/2)/myworld.th
		If myworlditems.map[tx,ty] = myworlditems.item.flower
		If myworlditems.mapinvisible[tx,ty] = False
			pinv[inventory.flowers] +=1
			myworlditems.mapinvisible[tx,ty] = True
			myworlditems.mapregrow[tx,ty] = 10
		End If
		End If 
	End Method
	Method draw(canvas:Canvas)
		canvas.Color = Color.White
		canvas.DrawRect(px,py,pw,ph)
		'draw inventory
		canvas.Color = Color.Black
		Local x:Int=0
		Local y:Int=myworld.sh-32
		canvas.DrawRect(0,y,myworld.sw,32)
		canvas.Color = Color.White
		canvas.DrawText("Flowers :"+pinv[inventory.flowers],x,y+4)
		canvas.DrawText("Gold :"+pinv[inventory.gold],x+100,y+4)
		canvas.DrawText("Xp :"+pinv[inventory.xp],x+200,y+4)
	End Method
	Method rectsoverlap:Bool(x1:Int, y1:Int, w1:Int, h1:Int, x2:Int, y2:Int, w2:Int, h2:Int)
	    If x1 >= (x2 + w2) Or (x1 + w1) <= x2 Then Return False
	    If y1 >= (y2 + h2) Or (y1 + h1) <= y2 Then Return False
	    Return True
	End	Method
End Class

Class worlditems
	Field map:Int[,] = New Int[1,1]
	Field mapinvisible:Float[,] = New float[1,1]
	Field mapregrow:Int[,] = New Int[1,1]
	Field sw:Int,sh:Int,mw:Int,mh:Int
	Field tw:Float,th:Float
	Field delay:Int
	Enum item
		flower=1		
	End Enum 
	Method New(sw:Int,sh:Int,mw:Int,mh:int)		
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		Self.tw = Float(sw)/Float(mw)
		Self.th = Float(sh)/Float(mh)
		map = New Int[mw,mh]
		mapinvisible = New float[mw,mh]
		mapregrow= New int[mw,mh]
		makemap()		
	End Method
	Method makemap()
		' add some flowers
		SeedRnd(50)
		For Local i:=0 Until 10
			Local x:Int=Rnd(0,10)	
			Local y:Int=Rnd(0,10)
			x+=5
			y+=5
			map[x,y] = item.flower
		Next
	End Method
	Method update()
		delay -=1
		If delay <=0
			delay = 60
			For Local y:=0 Until mh
			For Local x:=0 Until mw
				If myworlditems.mapregrow[x,y] > 0
					myworlditems.mapregrow[x,y] -=1
					If myworlditems.mapregrow[x,y] = 0
						myworlditems.mapinvisible[x,y] = False					
					End If
				End If
			Next
			Next
		End If
	End Method
	Method draw(canvas:Canvas)
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local t:Int=map[x,y]
			If t>0
			Select t
				Case item.flower
				If mapinvisible[x,y] = False
				canvas.Color = New Color(.1,.5,.2)
				canvas.DrawRect(x*tw+3,y*th+th/2,3,th/2)
				canvas.Color = New Color(1,.3,.1)
				canvas.DrawCircle(x*tw+tw/3,y*th,tw/2)
				Else 'show hole itheground
				canvas.Color = New Color(.5,.3,.1)
				canvas.DrawCircle(x*tw+tw/3,y*th+th/3,tw/3)
				End If
			End Select
			End If
		Next
		Next
	End Method
End Class

Class world
	Field map:Int[,] = New Int[1,1]
	Field mw:Int,mh:Int,sw:Int,sh:Int
	Field tw:Float,th:Float
	Enum tile
		grass = 1,
		road = 2,
		water = 3	
	End Enum
	
	Method New(sw:Int,sh:Int,mw:int,mh:Int)
		Self.sw = sw
		Self.sh = sh
		Self.mw = mw
		Self.mh = mh
		Self.tw = Float(sw)/Float(mw)
		Self.th = Float(sh)/Float(mh)
		map = New Int[mw,mh]
		makemap()
	End Method
	Method makemap()
		'make grass
		For Local y:=0 until mh
		For Local x:=0 until mw
			map[x,y] = tile.grass
		Next
		Next		
		'make a river
		For Local y:=16 until 25
		For Local x:=0 until mw
			map[x,y] = tile.water
		Next
		Next
		' make a road
		For Local y:=0 Until mh
		For Local x:=32 Until 37		
			map[x,y] = tile.road
		Next
		Next
	End Method
	Method draw(canvas:Canvas)
		For Local y:=0 Until mh
		For Local x:=0 Until mw
			Local t:Int=map[x,y]
			If t>0
			Select t
				Case tile.grass 'grass
				canvas.Color = Color.Green
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case tile.road 'road
				canvas.Color = Color.Brown
				canvas.DrawRect(x*tw,y*th,tw,th)
				Case tile.water 'water
				canvas.Color = Color.Blue
				canvas.DrawRect(x*tw,y*th,tw,th)				
			End Select 
			End If
		Next
		Next
	End Method
End Class

Class quest
	Field id:String
	Field goldreward:Int
	Field xpreward:Int
	Field queststate:Int
	Enum state
		begin=1,
		waiting=2,
		complete=3
	End Enum 
	Method New(id:String,xp:Int,gold:int)
		queststate = state.begin
		Self.id = id
		goldreward = gold
		xpreward = xp
	End Method	
End Class 

Class questui
	Field id:String
	Field questtext:String
	Field queststatus:String
	Field active:Bool
	Field qx:Int,qy:Int,qw:Int,qh:Int
	Field delay:Double
	Method New()
		qx = 50
		qy = 50
		qw = 320
		qh = 200
		active = False
	End Method
	Method setquest(id:String)
		Self.id = id
		For Local i:=Eachin myquest
			If i.id = id Then 
				Select id
					Case "Old man"
					Select i.queststate
						Case i.state.begin
						questtext = "Would you please get me|"
						questtext+= "5 flowers?|I will pay you|"
						questtext+= "10 gold.(Press a to accept)"
						Case i.state.waiting
						questtext = "Did you get me the flowers?|"
						questtext+= "(Press g to give)"
						Case i.state.complete
						questtext = "Nice day is it not?"						
					End Select
				End Select
			End If
		Next
	End Method
	Method update()
		If active = False Then Return
		'
		If Keyboard.KeyReleased(Key.A) 'accept quest from npc
			For Local i:=Eachin myquest
				If i.id = id
					If i.queststate = i.state.begin Then 'accept quest from id
						i.queststate = i.state.waiting
						active = false
						myplayer.lock = False
					End If
				End If
			Next				
		End If
		If Keyboard.KeyReleased(Key.G) 'Give fetched
			For Local i:=Eachin myquest
				If i.id = id
					If i.queststate = i.state.waiting Then 'Give if possible
						If myplayer.pinv[myplayer.inventory.flowers] >= 5
							myplayer.pinv[myplayer.inventory.flowers] -=5
							myplayer.pinv[myplayer.inventory.gold] += 10
							myplayer.pinv[myplayer.inventory.xp] += 3
							i.queststate = i.state.complete
							active = false
							myplayer.lock = False							
						End If
					End If
				End If
			Next				
		End If

		'
		If delay>Millisecs() Then Return
		If Keyboard.KeyReleased(Key.Space)
			active = False
			myplayer.delay = Millisecs()+300
			myplayer.lock = False
		End If
	End Method
	Method draw(canvas:Canvas)
		If active = False Then Return
		canvas.Color = Color.Black
		canvas.DrawRect(qx,qy,qw,qh)
		canvas.Color = Color.White
		Local y1:Int=qx+10
		Local x1:Int=qy+10
		Local x2:Int=0
		Local y2:Int=0
		For Local i:=0 Until questtext.Length
			Local s:String=questtext.Mid(i,1)
			If s="|" Then 
				y2+=15
				x2=0
				s=""
			End If
			If s<>"" Then x2+=10			
			canvas.DrawText(s,x1+x2,y1+y2)
		Next
		canvas.DrawText("Press space to exit.",x1,y1+qh-30)
	End Method 
End Class

Global myquest:Stack<quest> = New Stack<quest>
Global myquestui:questui
Global myworld:world
Global myworlditems:worlditems
Global myplayer:player
Global mynpc:Stack<npc> = New Stack<npc>


Class MyWindow Extends Window

	Method New()
		myworld = New world(Width,Height,64,64)
		myworlditems = New worlditems(Width,Height,64,64)
		myquestui = New questui()
		myplayer = New player(300,300)
		mynpc.Push(New npc("Old man",500,200))
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		myplayer.update()
		myworlditems.update()
		myworld.draw(canvas)
		myworlditems.draw(canvas)
		For Local i:=Eachin mynpc
			i.draw(canvas)
		Next
		myplayer.draw(canvas)
		myquestui.update()
		myquestui.draw(canvas)
		' if key escape then quit
		canvas.Color = Color.Black
		canvas.DrawRect(0,0,Width,12)
		canvas.Color = Color.White
		canvas.DrawText("Press space on npc to interact. Cursors to move. q - reset quest",0,0)
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
