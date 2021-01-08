#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

Global title:String="VGrid 0.1"	
Global AboutApp:=title+" Isometric Cube Experiment" 
Global Controls:="Grow=G,GrowX=X,GrowY=Y,GrowZ=Z,Clear=C,,Zoom=MouseWeel,Rotate=Cursor Keys"
Global Contact:=",github.com/nitrologic/m2"
Global Credits:=",Transpiled by Monkey2 :)"

Const Qube:=27

Const Rubik:=13' -1 -3 -9 (-13) is rubik offset
Const Rubit:=1 shl Rubik
Const RubitMask:=$7ffffff	'bit per neighbor vacancy mask

Global Order4:=New Int[](1,0,0,1,  0,1,-1,0,  -1,0,0,-1,  0,-1,1,0)

Class Cube
	Global CubeCounter:=0
	Field id:int
	Field x:Int
	Field y:Int
	Field z:Int
	Field rubit:=Rubit
	Field image:Image
	Field color:Int
	Field kids:Cube[]
	Field style:Int
	
	Method New(skin:Image)
		image=skin
		CubeCounter+=1
		id=CubeCounter
		Print "id="+id
	End

	Method Clone:Cube()
		Local cube:=New Cube(image)
		Return cube
	End

	Method SortDepth:Int(quadrant:Int)
		local ix:=Order4[quadrant*4+0]
		local iy:=Order4[quadrant*4+1]
		local jx:=Order4[quadrant*4+2]
		local jy:=Order4[quadrant*4+3]			
		Local dx:=x*ix+z*jx
		Local dy:=x*iy+z*jy					
		Return ((dx+dy) Shl 16) + y
	End

	' meet cube at dx,dy,dz offset
	
	Method Meet(cube:Cube,dx:int,dy:int,dz:Int)			
		Local index:=Rubik+dx+dy*3+dz*9
		Local bit:=1 Shl index
		rubit|=bit
		Local mindex:=Rubik-dx-dy*3-dz*9
		Local mbit:=1 Shl mindex
		cube.rubit|=mbit
	End
	
	Const D:=10
	
	Method DrawCube(display:Canvas,zx:Double,zy:Double,rz:Double)
		Assert(rubit<>RubitMask)
		Local sx:Float=(x-z)+zy*y*2
		Local sy:Float=(x+z)+zx*y*2
		display.DrawImage(image,sx*D,sy*D,rz,0.125,0.25)	'facing eye
'		display.DrawImage(image,sx*D,sy*D,0,0.125,0.25)	'facing sky
	end	
end

Global scanCount:int

Class DualAxisStack
	Field root:Cube
	Field org:Vec3<Int>
	Field dim:Vec3<Int>
	Field stack:List<Cube>
	Field ordered:=New Cube[][4] ' quadrant facing 2d march order where y is always up
				
	Method New(rootCube:Cube)
		root=rootCube
		org=New Vec3<int>(-1,-1,-1)
		dim=new Vec3<Int>(3,3,3)
		stack=New List<Cube>		
		stack.AddLast(root)
		BakeSort()
	End
		
	Method BakeSort()		
		Local cullstack:=New List<Cube>()
		For local cube:=Eachin stack
			If cube.rubit<>RubitMask ' level1 view cull
				cullstack.AddLast(cube)
			endif
		Next
		For local quadrant:=0 Until 4			
			Local order:=New List<Cube>(cullstack)
			local func:=Lambda:Int(a:Cube,b:Cube)
				return b.SortDepth(quadrant)-a.SortDepth(quadrant)
			End				
			order.Sort(func)
			ordered[quadrant]=order.ToArray()			
		Next
	End		
end
		
Class DualAxisGrid Extends DualAxisStack
	Field grid:Cube[,,]
	
	Method New(rootCube:Cube)
		Super.New(rootCube)
		grid=New Cube[dim.x,dim.y,dim.z]
	End
		
	Method Skin(xaxis:Bool=True,yaxis:bool=True,zaxis:Bool=True)
		Local dx:=Int(xaxis)
		Local dy:=Int(yaxis)
		Local dz:=Int(zaxis)		

		org=new Vec3<int>(org.x-dx,org.y-dy,org.z-dz)
		dim=New Vec3<Int>(dim.x+dx*2,dim.y+dy*2,dim.z+dz*2)

		grid=New Cube[dim.x,dim.y,dim.z]
		
		For Local point:=Eachin stack
			grid[point.x-org.x,point.y-org.y,point.z-org.z]=point
		Next
		
		' first enamel parse
		
		Local enamel:=New List<Cube>		
		For Local cube:=Eachin stack
			Local sx:=cube.x-org.x
			Local sy:=cube.y-org.y
			Local sz:=cube.z-org.z
			For local x:=-dx To dx
				For Local y:=-dy To dy
					For local z:=-dz To dz
						If (x|y|z)=0 Continue
						If grid[sx+x,sy+y,sz+z]=Null
							Local cube2:=root.Clone()
							cube2.x=cube.x+x							
							cube2.y=cube.y+y
							cube2.z=cube.z+z							
							Assert(sx+x=cube2.x-org.x)
							Assert(sy+y=cube2.y-org.y)
							Assert(sz+z=cube2.z-org.z)
							enamel.AddLast(cube2)
							grid[sx+x,sy+y,sz+z]=cube2
						Endif
					Next
				Next
			Next
		Next
		
		' second vacant parse effect all neighbors of enamel
		
		For Local cube:=Eachin enamel
			stack.AddLast(cube)
			Local sx:=cube.x-org.x
			Local sy:=cube.y-org.y
			Local sz:=cube.z-org.z
			For local x:=-dx To dx
				For Local y:=-dy To dy
					For Local z:=-dz To dz
						If (x|y|z)=0 Continue
						Local cube2:=grid[sx+x,sy+y,sz+z]								
						if cube2<>Null cube.Meet(cube2,x,y,z)
					Next
				Next
			Next
		Next
		
		BakeSort()
	End
		
End

Class Grid
	Field star:Cube
	Field grid:DualAxisGrid
	Field framecount:Int	
	Field skin:Image
	
	Method New(image:Image)
		skin=image
		Clear()
	End
	
	Method Count:Int()
		Return grid.stack.Count()
	End
	
	Method Generate(xaxis:Bool=True,yaxis:bool=True,zaxis:Bool=True)
		grid.Skin(xaxis,yaxis,zaxis)
	End
	
	Method Clear()
		star=New Cube(skin)
		grid=New DualAxisGrid(star)
	end
	
	Field zx:Double
	Field zy:Double
	Field DrawQuadrant:Int

	Method IsoView(display:Canvas, width:double, height:double, theta:Double, scale:Double)
		zx=Cos(theta)
		zy=Sin(theta)
		local tx:=zx*scale
		local ty:=zy*scale
		display.Matrix=new AffineMat3f(tx,ty*0.5,-ty,tx*0.5,width*0.5,height*0.5)		
	End
			
	Method DrawGrid( c:Canvas, width:double, height:double, theta:Double, zoom:Double )	
		c.PushMatrix()
		Local scale:=1.0/zoom
		IsoView(c,width,height,theta,scale)
' calulate draw order so we scan grid from far to near
		Local quadrant:Int=Int(2.5+2*theta/Pi)&3				
		DrawQuadrant=quadrant
		For Local cube:=Eachin grid.ordered[quadrant]
			cube.DrawCube(c,zx,zy,theta)
		Next
		c.PopMatrix()
		framecount+=1		
	End	
End

Class VGrid Extends Window
	Field grid:Grid
	Field status:String
	
	Field zoom:Float
	Field framecount:Int
	Field drawcount:Int
	Field mousecount:Int
	Field cx:Float
	Field cy:Float
	
	Field rot:Double
	Field rotSpeed:Double
	
	Field radius:Float
	
	Global Transparent:=New Color(0,0,0,0)
	Global SmokedGlass:=New Color(0,0,0,0.7)
	
	Method New(title:String)
		Super.New(title,1024,800,WindowFlags.Resizable)		
		ClearColor=Color.Black
		zoom=.2
		radius=2.5			
		grid=New Grid(BallImage())		
	End
	
	Method BallImage:Image()
		local pix:=New Pixmap(128,128)
		pix.Clear(Color.None)
		Circle(pix,64,64,40,Color.Yellow)		
		Circle(pix,64,64,34,Color.Black)		
		Circle(pix,64,64,24,Color.Blue)		
		Circle(pix,42,42,8,Color.White)	
		local image:=new Image(pix)',TextureFlags.Filter|TextureFlags.Mipmap)
		image.Handle=New Vec2f( .5,.5 )
		Return image
	End
	
	function Circle(pix:Pixmap,rx:int,ry:int,r:int,c:Color)
		Local x0:=rx-r
		Local x1:=rx+r
		Local y0:=ry-r
		Local y1:=ry+r
		x0=Max(x0,0)
		y0=Max(y0,0)
		For Local y:=y0 To y1
			For Local x:=x0 To x1
				Local dd:=(x-rx)*(x-rx)+(y-ry)*(y-ry)
				If dd<r*r
					pix.SetPixel(x,y,c)
				endif
			Next
		Next
	End
	
	Method DrawStats(display:Canvas)
		Local cy:=10
		
		display.Color=SmokedGlass
		display.DrawRect(0,0,200,Height)
		display.Color=Color.Grey
		
		Local content:=AboutApp
		content+=",,"+Controls
		content+=",,Count="+grid.Count()
		content+=",Quadrant="+grid.DrawQuadrant
		content+=","+Contact+","+Credits
		
		For Local line:=Eachin content.Split(",")				
			Local cx:=10
			For Local tab:=Eachin line.Split("=")
				tab=tab.Replace(":)",":=")
				display.DrawText(tab,cx,cy)
				cx+=60
			Next
			cy+=16
		Next
	End
	
	Method OnRender( display:Canvas ) Override	
		App.RequestRender()						
		rot+=rotSpeed*rotSpeed*rotSpeed							
		If rot<0
			rot=Pi*2-((-rot) Mod (Pi*2))
		Else		
			rot=rot Mod (Pi*2)
		Endif		
		grid.DrawGrid(display,Width,Height,rot,zoom)
		DrawStats(display)		
	End

	Method Hold()
		rotSpeed=0
		rot=0
	End
	
	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
		Case EventType.KeyDown
			Select event.Key			
			Case Key.C
				grid.Clear()
			Case Key.G
				grid.Generate(True,True,True)
			Case Key.X
				grid.Generate(True,False,False)
			Case Key.Y
				grid.Generate(False,True,false)
			Case Key.Z
				grid.Generate(false,false,True)
			Case Key.Escape
				App.Terminate()
			Case Key.F1
				Fullscreen = Not Fullscreen
			Case Key.Space
				Hold()
			Case Key.Left
				rotSpeed+=1.0/16			
			Case Key.Right
				rotSpeed-=1.0/16
			Case Key.Down
				radius*=0.8			
			Case Key.Up
				radius*=1.2			
			end
		End
	End
								
	Method OnMouseEvent(event:MouseEvent ) Override	
		Select event.Type		
			Case EventType.MouseWheel
				local w:=event.Wheel.Y
				zoom-=w/8.0
				If zoom<1.0/8 zoom=1.0/8				
		End
	End	
End

Function Main()
	Print title
	New AppInstance	
	New VGrid(title)
	App.Run()	
End
