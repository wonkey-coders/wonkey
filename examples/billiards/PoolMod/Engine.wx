#Import "PoolMod"
'******************************************************************************************
'
'		elastic/non elastic ball/cirlcle collision engine
'
'******************************************************************************************

' Collision storage.
Class ElasticEngine
	Field wallList:List<VectorObject>
	Field ballList:List<Ball>
	Field colls:CollisionTrend[] = New CollisionTrend[99]
	
	Field totalCol:Int
	Field nearesBall:Ball
	Field colCount:Int
	Field firstCollision:Ball
	
	Method New()
		wallList= New List<VectorObject>
		ballList= New List<Ball>
		For Local i:Int=0 Until 99
			colls[i]= New CollisionTrend()
		End
	End
	
	Method SetGravity(vx:Float,vy:Float)
		VectorObject.SetGlobalGravity(vx,vy)
	End
	
	Method SetFriction(f:Float)
		VectorObject.SetGlobalFriction(f)
	End
	
	Method RemoveWalls()
		wallList.Clear()
	End
	
	Method AddWall:List<VectorObject>.Node(t_wall:VectorObject)
		Return wallList.AddLast(t_wall)
	End
	
	Method AddLineWallImage:LineWall(x1:Float,y1:Float,x2:Float,y2:Float,image:Image,color:Color)
		Local line:LineWall= New LineWall(x1,y1,x2,y2,Null,1.0,1.0)
		Local animation:AImageLineStained= New AImageLineStained(line.P,line.V.x,line.V.y,image,color)
		line.SetAnimation(animation)
		AddWall(line)
		Return line
	End
	
	Method AddLineWallOutline:LineWall(x1:Float,y1:Float,x2:Float,y2:Float,image:Image,color:Color)
		Local line:LineWall=New LineWall(x1,y1,x2,y2,Null,1.0,1.0)
		Local animation:APixelLine= New APixelLine(line.P,line.V.x,line.V.y,color)
		line.SetAnimation(animation)
		AddWall(line)
		Return line
	End
	
	Method AddArcWallImage:ArcWall(x:Float,y:Float,radius:Float,startAngle:Float,endAngle:Float,image:Image,color:Color)
		Local arc:ArcWall=New ArcWall(x,y,radius,startAngle,endAngle,Null,1.0,1.0)
		Local animation:AImageArcStained= New AImageArcStained(arc.P,image,color)
		arc.SetAnimation(animation)
		AddWall(arc)
		Return arc
	End
	
	Method AddArcWallOutline:ArcWall(x:Float,y:Float,radius:Float,startAngle:Float,endAngle:Float,color:Color)
		Local arc:ArcWall=New ArcWall(x,y,radius,startAngle,endAngle,Null,1.0,1.0)
		Local animation:APixelArc=New APixelArc(arc.P,radius,startAngle,endAngle,color)
		arc.SetAnimation(animation)
		AddWall(arc)
		Return arc
	End
	
	Method AddBall:List<Ball>.Node(ball:Ball) 
		ball.node=ballList.AddLast(ball)
		Return ball.node
	End
	
	Method Add3DBall:Ball(x:Float,y:Float,radius:Float,vx:Float,vy:Float,image:Image,color:Color,txtColor:Color,number:Int,displayFloat:Int)
		Local ball:Ball=New Ball(x,y,radius,vx,vy,Null,1.0,1.0,1.0,number,False)
		Local animation:ObjectAnimation= New ABall3D(ball.P,radius,image,color,txtColor,number)
		ball.SetAnimation(animation)
		AddBall(ball)
		Return ball
	End
	
	Method Process()
		
		Local distance:Float=INVALID_DISTANCE
		Local done:Int=0
		nearesBall = Null
		Local nearestObject:VectorObject
		colCount = -1
		For Local ball:Ball = Eachin ballList
			For Local ball2:Ball = Eachin ballList.Backwards()
				If ball=ball2 Exit
				If(Not ball.IsMoving() And Not ball2.IsMoving()) Continue
				Local balla:Ball
				Local ballb:Ball
				If(ball.L>=ball2.L)
					balla=ball2
					ballb=ball
				Else
					balla=ball
					ballb=ball2
				End
				Local oldL:Float=ballb.L
				Local d:Float=balla.Distance(ballb)
				If d=INVALID_DISTANCE
					Continue
				Else
					If d<distance
						distance=d
						colCount=0
						colls[colCount].ball=ballb
						colls[colCount].obj= balla
						colls[colCount].cdx=balla.cdx
						colls[colCount].cdy=balla.cdy
						colls[colCount].oldL=oldL
					Else
						If d=distance
							colCount+=1
							colls[colCount].ball=ballb
							colls[colCount].obj= balla
							colls[colCount].cdx=balla.cdx
							colls[colCount].cdy=balla.cdy
							colls[colCount].oldL=oldL
						End
					End
				End
			End
			For Local t_wall:VectorObject = Eachin wallList
				Local d2:Float=t_wall.Distance(ball)
				If d2 = INVALID_DISTANCE
					Continue
				Else
					If d2 < distance
						distance=d2
						colCount=0
						colls[colCount].ball=ball
						colls[colCount].obj=t_wall
						colls[colCount].cdx=t_wall.cdx
						colls[colCount].cdy=t_wall.cdy
						colls[colCount].oldL=0
					Else
						If d2 = distance
							colCount+=1
							colls[colCount].ball=ball
							colls[colCount].obj=t_wall
							colls[colCount].cdx=t_wall.cdx
							colls[colCount].cdy=t_wall.cdy
							colls[colCount].oldL=0
						End
					End
				End
			End
		End
		If distance = INVALID_DISTANCE
			distance=1.0
			done=True
		End
		
		For Local ball3:Ball = Eachin ballList
			ball3.Advance(distance)
		End
		
		For Local i:Int=0 to colCount
			colls[i].obj.Bounce(colls[i].ball,colls[i].cdx,colls[i].cdy)
			If(Not((firstCollision)<>Null))
				Local b1:Ball=Cast<Ball>(colls[i].obj)
				Local b2:Ball=colls[i].ball
				If(((b1)<>Null) And b1.num=16)
					firstCollision=b2
				Else
					If b2.num = 16 And b1 firstCollision=b1
				End
			End
		End
		If totalCol>=0 totalCol+=colCount+1
		If Not done Process()
	End
	
	Method Update(timeFrame:Float)
	
		If(timeFrame = 0.0) Return
		If(timeFrame > 3.0) timeFrame=3.0
		
		For Local ball:Ball = Eachin ballList
			ball.updateIn(timeFrame)
		End
		totalCol = 0
		Process()
		For Local ball2:Ball = Eachin ballList
			ball2.updateOut(timeFrame)
		End	
	End
	
	Method RemoveBall(ball:Ball)
		ball.node.Remove()
	End
	
	Method BallsMoving:Bool()
		For Local b:Ball = Eachin ballList
			If b.IsMoving() Return True
		End
		Return False
	End
	
	Method GetFirstCollision:Ball()
		Return firstCollision
	End
	
	Method ClearFirstCollision()
		firstCollision = Null
	End
	
	Method Render(canvas:Canvas)
		For Local ball:Ball = Eachin ballList
			If(ball.P.x<0.0 Or ball.P.x>DEVICE_WIDTH Or ball.P.y<0.0 Or ball.P.y>DEVICE_HEIGHT)
				RuntimeError("ball exited screen ")
			End
			ball.Render(canvas)
		End
		'For Local wall := Eachin wallList
		'	wall.Render(canvas)
		'Next
		Return
	End
	
	Method CollisionDistance2Ghost(ghost:GhostBall)
		Local distance:Float=INVALID_DISTANCE
		Local cdx:Float, cdy:Float
		For Local b:Ball = Eachin ballList
			cdx=ghost.cn.x
			cdy=ghost.cn.y
			Local dist:Float=b.CollisionDistance2Ghost(ghost)
			If(dist<distance)
				distance=dist
				ghost.colBall=b
			Else
				ghost.cn.x=cdx
				ghost.cn.y=cdy
			End
		End
		For Local w:VectorObject = Eachin wallList
			cdx=ghost.cn.x
			cdy=ghost.cn.y
			Local dist2:Float=w.CollisionDistance2Ghost(ghost)
			If(dist2<distance)
				ghost.colBall = Null
				distance=dist2
			Else
				ghost.cn.x=cdx
				ghost.cn.y=cdy
			End
		End
		ghost.distance=distance
	End
End

Class CollisionTrend
	Field temp:PVector2D
	Method New()
		temp=New PVector2D()
	End
	Field ball:Ball
	Field obj:VectorObject
	Field cdx:Float
	Field cdy:Float
	Field oldL:Float
End
