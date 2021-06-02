#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class battleui
	Field Width:Int,Height:Int
	Field phealth:Int
	Field pattack:Int
	Field pdefence:Int
	Field npchealth:Int
	Field npcattack:Int
	Field npcdefence:Int
	Field battlestate:Int
	Field uititle:String = "Battle Screen"
	Field timer:Int
	Field cursory:Int
	Enum state
		intro=1,		
		fighting=2,
		victory=3,
		selattack=4
	End Enum
	Enum loot
		healthpotion=1,
		diamond=2		
	End Enum 
	Method New(width:Int,height:Int)
		Width = width
		Height = height
		timer = 120
		battlestate = state.selattack
		npchealth = Rnd(4,12)
		npcattack = Rnd(1,10)
		npcdefence = Rnd(1,10)
		phealth = Rnd(20,100)
		pattack = Rnd(10,50)
		pdefence = Rnd(1,50)
	End Method
	Method update()
		Select battlestate
			Case state.selattack
			If Keyboard.KeyReleased(Key.Down) Then cursory+=1
			If Keyboard.KeyReleased(Key.Up) Then cursory-=1
			cursory = Clamp(cursory,0,2)
		End Select
	End Method
	Method draw(canvas:Canvas)
		canvas.Clear(Color.Black)
		canvas.Color=Color.White
		canvas.Scale(2,2)
		canvas.DrawText(uititle,0,0)
		' draw the player stats
		canvas.DrawText("Player",32,50)
		canvas.DrawText("Health : "+phealth,32,70)
		canvas.DrawText("Attack : "+pattack,32,90)
		canvas.DrawText("Defence : "+pdefence,32,110)
		' draw the enemy stats
		canvas.DrawText("Enemy",196,50)
		canvas.DrawText("Health : "+npchealth,196,70)
		canvas.DrawText("Attack : "+npcattack,196,90)
		canvas.DrawText("Defence : "+npcdefence,196,110)
		
		' draw the user interface is needed
		Select battlestate
			Case state.selattack
			' selection
				Local s:String[] = New String[]("Attack","Run Away","Use Health Potion")
				s[cursory] = "->"+s[cursory]+"<-"
				canvas.DrawText(s[0],Width/4       ,Height/2-40,.5,.5)
			canvas.DrawText(s[1],Width/4         ,Height/2-25,.5,.5)
			canvas.DrawText(s[2],Width/4,Height/2-10,.5,.5)
			'
		End Select
	End Method
End Class 

Global mybattleui:battleui

Class MyWindow Extends Window

	Method New()
		mybattleui = New battleui(Width,Height)
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		mybattleui.update()
		mybattleui.draw(canvas)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
