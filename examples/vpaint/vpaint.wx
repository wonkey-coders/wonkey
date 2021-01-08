#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global title:String="VPaint 0.1 Easter-Show-Spew Release"	
Global AboutApp:="VPaint Control,Mouse Button=Lift Pen,Mouse Wheel=Zoom,Space Key=Clear,S Key=Smile Box,C Key=Hold,Cursor Left=-RPM,Cursor Right=+RPM,Cursor Up=+Pen Radius,Cursor Down=+Pen Radius,Hold,F1=Toggle Fullscreen,Click To Start"
Global ContactApp:=",,Latest Source: github.com/nitrologic/m2"

Global instance:AppInstance

Class VPane Extends Image
	Field canvas:Canvas
	Field pixmap:Pixmap

	Method New(w:Int,h:Int,bg:Color)		
		Super.New(w,h,TextureFlags.Dynamic)
		canvas=New Canvas(Self)	
		canvas.Clear(bg)
		canvas.Alpha=0.8
		canvas.Translate(w/2,h/2)
		Handle=New Vec2f(0.5,0.5)
	End
	
	Method Draw(display:Canvas)	
		canvas.Flush()
		display.DrawImage(Self,0,0)
	End
	
	Method Clear(bg:Color)
		canvas.Clear(bg)
	End
	
	Field segcount:Int
	Field edge0:Vec2f
	Field edge1:Vec2f
	
	Method EndSegment()
		segcount=0
	End

	Method FatSegment(x:Float,y:Float,x1:Float,y1:Float,fat:Float)

		If Not canvas Return
				
		Local verts:=New Float[8]
		
		Local dy:Float=y1-y
		Local dx:Float=x1-x
				
		Local len:Float=Sqrt(dx*dx+dy*dy) 
		Local q:Float=fat/len
				
		If segcount=0
			edge0=New Vec2f(x+dy*q,y-dx*q)
			edge1=New Vec2f(x-dy*q,y+dx*q)
		Endif
		segcount+=1
				
		Local v0:=edge0
		Local v1:=New Vec2f(x1+dy*q,y1-dx*q)
		Local v2:=New Vec2f(x1-dy*q,y1+dx*q)
		Local v3:=edge1
				
		canvas.DrawTriangle(v0,v1,v2)
		canvas.DrawTriangle(v0,v2,v3)
				
		edge0=v1
		edge1=v2
	End
	
	Function Curve:Float[](seg:Int,p0:Vec2f,p1:Vec2f,p2:Vec2f,p3:Vec2f)
		Local verts:=New Float[(seg+1)*2]		
		For Local i:Int=0 To seg		
			Local mu:Float=i*1.0/seg			    
        	Local x:Float=CatmullInterpolate(p0.x,p1.x,p2.x,p3.x,mu)
	       	Local y:Float=CatmullInterpolate(p0.y,p1.y,p2.y,p3.y,mu)
          	verts[i*2+0]=x
        	verts[i*2+1]=y
		Next		
		Return verts
	End
	
	Method OpenCurve(p0:Vec2f,p1:Vec2f,p2:Vec2f,p3:Vec2f,fat:Float)
		If Not canvas Return
		Local seg:Int=6
		Local verts:=Curve(seg,p0,p1,p2,p3)
		For Local i:Int=0 Until seg		
			FatSegment(verts[i*2+0],verts[i*2+1],verts[i*2+2],verts[i*2+3],fat)
		Next
	End
		
	Method ClosedCurve(p0:Vec2f,p1:Vec2f,p2:Vec2f,p3:Vec2f,fat:Float)
		If Not canvas Return
		OpenCurve(p3,p0,p1,p2,fat)
		OpenCurve(p0,p1,p2,p3,fat)
		OpenCurve(p1,p2,p3,p0,fat)
		OpenCurve(p2,p3,p0,p1,fat)
		EndSegment()
	End

 	Function CubicInterpolate:Float(y0:Float,y1:Float,y2:Float,y3:Float,mu:Float)
		Local a0:Float,a1:Float,a2:Float,a3:Float,mu2:Float
		mu2 = mu*mu
		a0 = y3 - y2 - y0 + y1
		a1 = y0 - y1 - a0
		a2 = y2 - y0
		a3 = y1
		Return(a0*mu*mu2+a1*mu2+a2*mu+a3)
	End
		
 	Function CatmullInterpolate:Float(y0:Float,y1:Float,y2:Float,y3:Float,mu:Float)
		Local a0:Float,a1:Float,a2:Float,a3:Float,mu2:Float	
		mu2 = mu*mu
		a0 = -0.5*y0 + 1.5*y1 - 1.5*y2 + 0.5*y3
		a1 = y0 - 2.5*y1 + 2*y2 - 0.5*y3
		a2 = -0.5*y0 + 0.5*y2
		a3 = y1
		Return(a0*mu*mu2+a1*mu2+a2*mu+a3)
	End
 	 	
 	Function CubicInterpolate2:Float(p0:Float,p1:Float,p2:Float,p3:Float,x:Float)
		Return p1 + 0.5 * x*(p2-p0+x*(2.0*p0-5.0*p1+4.0*p2-p3+x*(3.0*(p1-p2)+p3-p0)))
	End

	Method FatLine(x:Int,y:Int,x1:Int,y1:Int,fat:Float)
		If Not canvas Return				
		Local dy:Int=y1-y
		Local dx:Int=x1-x				
		Local len:Float=Sqrt(dx*dx+dy*dy) 
		Local q:Float=fat/len				
		Local v0:=New Vec2f(x+dy*q,y-dx*q)
		Local v1:=New Vec2f(x1+dy*q,y1-dx*q)
		Local v2:=New Vec2f(x1-dy*q,y1+dx*q)
		Local v3:=New Vec2f(x-dy*q,y+dx*q)				
		canvas.DrawTriangle(v0,v1,v2)
		canvas.DrawTriangle(v0,v2,v3)
	End


	Method Smile(x:Float,y:Float,r:Float)
		Local v0:=New Vec2f(x-100,y+100)
		Local v1:=New Vec2f(x-100,y-20)
		Local v2:=New Vec2f(x+100,y-20)
		Local v3:=New Vec2f(x+100,y+100)
		EndSegment()
		OpenCurve(v0,v1,v2,v3,r)
		EndSegment()
	End
		
	Method Circle(x:Float,y:Float,r:Float)
		Local v0:=New Vec2f(x-100,y-100)
		Local v1:=New Vec2f(x+100,y-100)
		Local v2:=New Vec2f(x+100,y+100)
		Local v3:=New Vec2f(x-100,y+100)
		EndSegment()
		ClosedCurve(v0,v1,v2,v3,r)
	End

  
End

Class VBrowse

End


Enum AppState
	Title
	Draw
	Browse
End

Const TickMark:String=String.FromChar(65)	'(0xE2 0x9C 0x93)

Class VTool Extends Window
	Method New(title:String)
		Super.New(title,480,34,WindowFlags.Resizable)		
	End
End

Class VPaint Extends Window
	Field appState:AppState

'	Field tool:VTool
	Field pane:VPane
	Field browse:VBrowse
	
	Field zoom:Float
	Field ink:Color
	Field mousex:Int
	Field mousey:Int
	Field mousew:Int
	Field framecount:Int
	Field drawcount:Int
	Field mousecount:Int
	Field cx:Float
	Field cy:Float
	Field rot:Float
	Field rotSpeed:Float
	Field radius:Float
	
	Method ToggleTwo()	
	End
	
	Method New(title:String)
		Super.New(title,720,560,WindowFlags.Resizable)		
		zoom=2
'		pane=New VPane(2048,2048,Color.Black)
		pane=New VPane(4096,4096,Color.Black)
		browse=New VBrowse()
		ink=New Color
		radius=1.0
'		tool=New VTool("Tools")
'		tool.Title="VPaint Pen : RGBCycle"
	End
	
	Method RefreshTitle()	
		Local r:=rotSpeed*rotSpeed*rotSpeed
		Local rpm:Int=Abs(60*60*r/(Pi*2))
		Title="RPM "+rpm+" R="+Int(radius*100)
	End
	
	Method OnRender( display:Canvas ) Override	
		App.RequestRender()						

		Select appState

			Case AppState.Title
				Local cy:=40
				For Local line:=Eachin (AboutApp+","+ContactApp).Split(",")
					Local cx:=50
					For Local tab:=Eachin line.Split("=")
						display.DrawText(tab,cx,cy)
						cx+=120
					Next
					cy+=20
				Next

			Case AppState.Draw
				cx=Width/2
				cy=Height/2
				display.Translate(cx,cy)
				Local scale:=-1.0/zoom
				display.Scale(scale,scale)
				display.Rotate(rot)		
				rot+=rotSpeed*rotSpeed*rotSpeed	
				OnMouseEvent(recentMouseEvent)		
				pane.Draw(display)		
				framecount+=1	
				
				ink=Color.FromHSV( framecount/100.0,1,1 )

				pane.canvas.Color=ink

			Case AppState.Browse
		End

	End

	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
		Case EventType.KeyDown
			Select event.Key
			Case Key.S
				pane.Smile(mousex,mousey,radius)
				pane.Circle(mousex,mousey,radius)
			Case Key.C
				pane.Clear(ink )
			Case Key.Escape
				instance.Terminate()
			Case Key.F1
				Fullscreen = Not Fullscreen
			Case Key.F2
				ToggleTwo()	
			Case Key.Space
				rotSpeed=0
			Case Key.Left
				rotSpeed+=0.1			
			Case Key.Right
				rotSpeed-=0.1
			Case Key.Down
				radius*=0.8			
			Case Key.Up
				radius*=1.2
			Case Key.P
				Local pixmap:=pane.canvas.CopyPixmap( pane.canvas.Viewport )
				pixmap.Save( AppDir()+"vpaint_picture.png" )
				pixmap.Discard()
			End
		End
		RefreshTitle()		
	End
	
	Field linetool:Bool=False
	Field history:=New Vec2f[4]

	Field recentMouseEvent:MouseEvent
	
	Method DrawMode()
		appState=AppState.Draw
	End
							
	Method OnMouseEvent(event:MouseEvent ) Override
	
		If appState=AppState.Title
			If event.Type=EventType.MouseDown
				DrawMode()
			Endif
			Return
		Endif

	
		If event=Null Return
		
		Local mx:Int=event.Location.X
		Local my:Int=event.Location.Y
		Local b:Int=event.Button
				
		mx=(mx-cx)*zoom
		my=(my-cy)*zoom

		Local x:=-Cos(rot)*mx+Sin(rot)*my
		Local y:=-Sin(rot)*mx-Cos(rot)*my
						
		Local w:Int
		
		If recentMouseEvent<>event w=event.Wheel.Y
		
		If mousex=x And mousey=y And mousew=w Return
		
		recentMouseEvent = event
		
		Select event.Type
		
		Case EventType.MouseWheel
			zoom-=w/8.0
			If zoom<1.0/8 zoom=1.0/8
				
		Case EventType.MouseDown
			pane.EndSegment()
			
		Case EventType.MouseMove
			history[0]=history[1]
			history[1]=history[2]
			history[2]=history[3]
			history[3]=New Vec2f(x,y)
		End
		
If linetool
		If drawcount	
			pane.FatLine(mousex,mousey,x,y,radius)		
		Endif
Else
		If drawcount>2 And Not b
'			pane.FatCurve(mx[0],my[0],mx[1],my[1],mx[2],my[2],mx[3],my[3])				
			pane.OpenCurve(history[0],history[1],history[2],history[3],radius)				
		Endif
Endif
		drawcount+=1

		mousex=x
		mousey=y
		mousew=w
		
		mousecount+=1
	End	
End

Function Main()
	Print title
	instance = New AppInstance	
	New VPaint(title)
	App.Run()	
End

Function SaveTGA(path:String, pixmap:Pixmap)
	Local stream:=FileStream.Open(path,"w")
	Local buffer:=New Byte[18]		
	Local w:=pixmap.Width
	Local h:=pixmap.Height	
	buffer[2]=2
	buffer[12]=w & 255
	buffer[13]=w Shr 8
	buffer[14]=h & 255
	buffer[15]=h Shr 8
	buffer[16]=32
	buffer[17]=8
	stream.Write(Varptr buffer[0],18)	
	stream.Write(pixmap.Data,w*h*4)
	stream.Close()
End Function
