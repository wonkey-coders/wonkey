#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Class item
	Field can:Canvas
	Field image:Image
	Field rot:float
	Field rotspd:Float
	Field firstname:String
	Field secondname:String
	Field name:String[] = New String[]( "Hardcore",
										"Dwarver",
										"Lighting",
										"Electrifying",
										"Hander",
										"Left",
										"Right",
										"Fast",
										"Flamer",
										"Shell",
										"Rifle",
										"Bazooka",
										"Laser",
										"Shotgun",
										"Lance",
										"Sword",
										"Knife",
										"Club",
										"Shield",
										"Force",
										"Gravity",
										"Computer",
										"Teleporter",
										"Torturer",
										"Slow",
										"Cutting",
										"Disecting",
										"Duster",
										"Spoon")
	Method New()
		rot=Rnd(TwoPi)
		rotspd= Rnd(-0.2,0.2)

		image = New Image(64,64)
		can = New Canvas(image)
		image.Handle=New Vec2f( .5,.5 )
		makeimage()
		getname()
	End Method
	Method getname()
		Local a:Int = Rnd()*name.Length
		firstname = name[a]
		a = Rnd()*name.Length
		secondname = name[a] + " " + Round(Rnd()*10)
	End Method
	Method makeimage()
		can.Color = Color.None
		can.BlendMode=BlendMode.Opaque
		can.DrawRect(0,0,64,64)	
		Local w:Int=Rnd(4,30)
		Local h:Int=Rnd(4,30)
		For Local i:=0 Until 10
			Local a:Float=Rnd()
			can.Color = New Color(a,a,a)
			If Rnd() <0.1 Then
			Local a:Int=Rnd()*4
			Select a
				Case 0 
				can.Color = New Color(Rnd(.2,1),0,0)
				Case 1
				can.Color = New Color(0,Rnd(.2,1),0)
				Case 2 
				can.Color = New Color(0,0,Rnd(.2,1))
				Case 3
				can.Color = New Color(Rnd(.2,1),Rnd(.2,1),0)
			End Select
			End If
			can.DrawTriangle(   New Vec2f(32+Rnd(-w,w),32+Rnd(-h,h)),
								New Vec2f(32+Rnd(-w,w),32+Rnd(-h,h)),
								New Vec2f(32+Rnd(-w,w),32+Rnd(-h,h)))
		Next
		can.Flush()
	End Method 
End Class 

Global myitem:List<item> = New List<item>

Class MyWindow Extends Window
	Field cnt:Int
	Method New()
		For Local y:=0 To 3
		For Local x:=0 To 3
			myitem.AddLast(New item())
		Next
		Next
		ClearColor = Color.Black
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		cnt+=1		
		If Keyboard.KeyReleased(Key.Space) Or cnt>500
			cnt=0
			Local a:Int=Microsecs()
			SeedRnd(a)
			For Local i:=Eachin myitem
				i.makeimage()
				i.getname()
			Next
		end If
		Local x:Int=0
		Local y:Int=0
		canvas.Color = Color.White
		For Local i:=Eachin myitem
			canvas.DrawImage(i.image,x*120+96,y*96+32+32,i.rot)
			canvas.DrawText(i.firstname,x*120+96,y*96+32+32+32)
			canvas.DrawText(i.secondname,x*120+96,y*96+32+32+20+32)
			i.rot+=i.rotspd

			If i.rot<0 Then i.rot=Float(TwoPi)
			If i.rot>Float(TwoPi) Then i.rot=0
			x+=1
			If x>3 Then y+=1;x=0
		Next
		canvas.Color = Color.White
		canvas.DrawText("Press Space to generate new items - press escape to end",0,0)
		'if press escape then end
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
