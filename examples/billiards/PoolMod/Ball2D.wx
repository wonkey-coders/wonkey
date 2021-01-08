
#Import "PoolMod"

Class VectorObject
	
	Global Gravityx:Float
	Global Gravityy:Float
	Global ApplicableGravityx:Float
	Global ApplicableGravityy:Float
	Global SurfaceFriction:Float
	Global ApplicableSurfaceFriction:Float
	
	Field image:Image
	
	Field P:PVector2D
	Field V:PVector2D
	Field D:PVector2D
	Field cp:PVector2D
	Field name:String=""
	
	Field friction:Float
	Field bounce:Float
	Field animation:ObjectAnimation
	
	Field L:Float
	
	Field cdx:Float
	Field cdy:Float
	Field tp:PVector2D

	Function SetGlobalGravity(t_gx:Float,t_gy:Float)
		Gravityx=t_gx
		Gravityy=t_gy
		ApplicableGravityx=t_gx
		ApplicableGravityy=t_gy
	End
	
	Function SetGlobalFriction(f:Float)
		SurfaceFriction=f
		ApplicableSurfaceFriction=f
	End
	
	Method Magnitude:Float(vx:Float,vy:Float)
		Return Sqrt(Self.V.x*Self.V.x+Self.V.y*Self.V.y)
	End

	Method Init(vx:Float,vy:Float)
		Self.V.x=vx
		Self.V.y=vy
		Self.L=Self.Magnitude(vx,vy)
		If(Self.L>0.0)
			Self.D.x=Self.V.x/Self.L
			Self.D.y=Self.V.y/Self.L
		Else
			Self.D.x=0.0
			Self.D.y=0.0
		End
	End
	
	Method SetAnimation(animation:ObjectAnimation)
		Self.animation=animation
	End
	
	Field num:Int
	Field node:List<Ball>.Node
	
	Method Distance:Float(b:Ball)Virtual
		Return 0
	End
	
	Method Bounce(ball:Ball,px:Float,py:Float) Abstract

	Method Render(canvas:Canvas) Abstract

	Method CollisionDistanceB2RW:Float(ball:Ball,x:Float,y:Float,radius:Float)
		Self.tp = Null
		Local vx:Float=x-ball.P.x
		Local vy:Float=y-ball.P.y
		Local totRadiusSq:Float=(ball.radius+radius)*(ball.radius+radius)
		Local distSq:Float=vx*vx+vy*vy
		If(distSq<totRadiusSq And distSq>radius*radius)
			If((ball.P.x-x)*(0.0-ball.V.x)+(ball.P.y-y)*(0.0-ball.V.y)>0.0)
				Local len:Float=Sqrt(distSq)
				Self.cdx=vx/len
				Self.cdy=vy/len
				Self.cp.x=ball.P.x+Self.cdx*ball.radius
				Self.cp.y=ball.P.y+Self.cdy*ball.radius
				Self.tp=Self.cp
				Return 0.0
			End
		End
		Local vx2:Float=x-(ball.P.x+ball.V.x)
		Local vy2:Float=y-(ball.P.y+ball.V.y)
		Local dp:Float=vx*ball.D.x+vy*ball.D.y
		If(dp>0.0)
			Local tvx:Float=dp*ball.D.x
			Local tvy:Float=dp*ball.D.y
			Local x1:Float=ball.P.x+tvx
			Local y1:Float=ball.P.y+tvy
			tvx=x-x1
			tvy=y-y1
			Local llSq:Float=tvx*tvx+tvy*tvy
			Local maxDist:Float=radius+ball.radius
			If(llSq<=maxDist*maxDist)
				Local c:Float=ball.radius+radius
				Local b:Float=Sqrt(llSq)
				Local a:Float=Sqrt(c*c-b*b)
				Local x2:Float=x1-ball.D.x*a
				Local y2:Float=y1-ball.D.y*a
				Local rvx:Float=x2-ball.P.x
				Local rvy:Float=y2-ball.P.y
				Local distSq2:Float=rvx*rvx+rvy*rvy
				If(distSq2<=ball.L*ball.L And vx*rvx+vy*rvy>=0.0)
					vx=x-(ball.P.x+rvx)
					vy=y-(ball.P.y+rvy)
					If((c)<>0.0)
						Self.cdx=vx/c
						Self.cdy=vy/c
					Else
						Self.cdx=0.0
						Self.cdy=0.0
					End
					Self.cp.x=ball.P.x+rvx+Self.cdx*ball.radius
					Self.cp.y=ball.P.y+rvy+Self.cdy*ball.radius
					Self.tp=Self.cp
					Local t_:Float=Sqrt(distSq2)/ball.L
					Return t_
				End
			End
		End
		Return INVALID_DISTANCE
		
	End Method
	
	Method Bounce2Fixed(ball:Ball,dx:Float,dy:Float)
		Local dp:Float=ball.V.x*dx+ball.V.y*dy
		Local vx1:Float=-dp*dx
		Local vy1:Float=-dp*dy
		dp=ball.V.x*dy-ball.V.y*dx
		Local vx2:Float=dp*dy
		Local vy2:Float=-dp*dx
		Local vx:Float=vx1+vx2
		Local vy:Float=vy1+vy2
		ball.Init(vx,vy)
		dp=ball.tvx*dx+ball.tvy*dy
		vx1=-dp*dx
		vy1=-dp*dy
		dp=ball.tvx*dy-ball.tvy*dx
		vx2=dp*dy
		vy2=-dp*dx
		ball.tvx=vx1+vx2
		ball.tvy=vy1+vy2
		Local n:Float=ball.tvx+ball.V.x
		If(n<5.0) n=0.0
		If(n>=5.0) n=1.0
		media.PlayRailCol(n)
	End
	
	Method CollisionDistance2Ghost:Float(ball:GhostBall) Abstract

	Method Distance2Ghost:Float(ghost:GhostBall,x:Float,y:Float,radius:Float)
		Local vx:Float=x-ghost.position.x
		Local vy:Float=y-ghost.position.y
		Local dp:Float=vx*ghost.dy-vy*ghost.dx
		Local c:Float=ghost.radius+radius
		If Abs(dp) < c
			Local dp2:Float=vx*ghost.dx+vy*ghost.dy
			If dp2 > 0.0
				dp2-=Sqrt(c*c-dp*dp)
				vx=ghost.position.x+ghost.dx*dp2-x
				vy=ghost.position.y+ghost.dy*dp2-y
				dp=Sqrt(vx*vx+vy*vy)
				ghost.cn.x=vx/dp
				ghost.cn.y=vy/dp
				Return dp2
			End
		End
		Return INVALID_DISTANCE
	End
	
End Class


'************************************************************************
'
'	Movable vector ball
'
'************************************************************************
Class Ball Extends VectorObject
	Field tv:PVector2D
	
	Field radius:Float
	Field mass:Float
	Field displayFloat:Bool

	Field tvx:Float
	Field tvy:Float

	Method New()
		P=New PVector2D()
		V=New PVector2D()
		D=New PVector2D()
		tv=New PVector2D()
		cp=New PVector2D()
		name="Ball"
	End
	
	Method New(x:Float,y:Float,radius:Float,vx:Float,vy:Float,animation:ObjectAnimation,frictn:Float,bounse:Float,mass:Float,num:Int,displayFloat:Bool)
		P=New PVector2D()
		V=New PVector2D()
		D=New PVector2D()
		tv=New PVector2D()
		cp=New PVector2D()
		name="Ball"
		P.x=x
		P.y=y
		Self.radius=radius
		Init(vx,vy)
		friction=frictn
		bounce=bounse
		Self.mass=mass
		Self.num=num
		Self.displayFloat=displayFloat
		Self.animation=animation
	End
	
	Method SetPosition(x:Float,y:Float)
		P.x=x
		P.y=y
	End
	
	Method ResetAnimation()
		animation.Reset()
	End
	
	Method updateIn(timeFrame:Float)
		V.x+=VectorObject.ApplicableGravityx
		V.y+=VectorObject.ApplicableGravityy
		V.x*=VectorObject.ApplicableSurfaceFriction
		V.y*=VectorObject.ApplicableSurfaceFriction
		V.x*=timeFrame
		V.y*=timeFrame
		Init(V.x,V.y)
	End
	Method IsMoving:Bool()
		Return ((V.x)<>0.0) Or ((V.y)<>0.0)
	End
	Method MovingToBall:Bool(ball:Ball)
		Return (ball.P.x-P.x)*(V.x-ball.V.x)+(ball.P.y-P.y)*(V.y-ball.V.y)>0.0
	End

	Method Distance:Float(ball:Ball) Override
		Local vx:Float=ball.P.x-P.x
		Local vy:Float=ball.P.y-P.y
		
		If(vx*vx+vy*vy<(radius+ball.radius)*(radius+ball.radius))
			If(MovingToBall(ball))
				Local len:Float=Sqrt(vx*vx+vy*vy)
				cdx=vx/len
				cdy=vy/len
				Return 0.0
			End
		End
		If(-vx*ball.V.x-vy*ball.V.y<0.0)
			Return INVALID_DISTANCE
		End
		Local vx1:Float=V.x-ball.V.x
		Local vy1:Float=V.y-ball.V.y
		Local totalRadius:Float=radius+ball.radius
		Local l1:Float=Sqrt(vx1*vx1+vy1*vy1)
		Local dx1:Float=vx1/l1
		Local dy1:Float=vy1/l1
		Local dp:Float=vx*dx1+vy*dy1
		Local vx2:Float=dp*dx1
		Local vy2:Float=dp*dy1
		Local lengt:Float=Sqrt(Pow(ball.P.x-(P.x+vx2),2.0)+Pow(ball.P.y-(P.y+vy2),2.0))
		Local diff:Float=totalRadius-lengt
		tp = Null
		If(diff>0.0)
			Local moveBack:Float=Sqrt(totalRadius*totalRadius-lengt*lengt)
			Local vx4:Float=vx2-moveBack*dx1
			Local vy4:Float=vy2-moveBack*dy1
			Local l4:Float=Sqrt(vx4*vx4+vy4*vy4)
			If(l4<=l1 And vx4*V.x+vy4*V.y>=0.0)
				Local dist:Float=l4/l1
				Local x1:Float=ball.P.x+ball.V.x*dist
				Local y1:Float=ball.P.y+ball.V.y*dist
				Local x2:Float=P.x+V.x*dist
				Local y2:Float=P.y+V.y*dist
				Local vx3:Float=x2-x1
				Local vy3:Float=y2-y1
				l1=Sqrt(vx3*vx3+vy3*vy3)
				If((l1)<>0.0)
					cdx=vx3/l1
					cdy=vy3/l1
				Else
					cdx=0.0
					cdy=0.0
				End
				cp.x=x1+cdx*ball.radius
				cp.y=y1+cdy*ball.radius
				tp=cp
				Return dist
			End
		End
		Return INVALID_DISTANCE
	End

	Method Advance(distance:Float)
		Local vx:Float=V.x*distance
		Local vy:Float=V.y*distance
		If(vx=0.0 And vy=0.0)
			Return
		End
		V.x-=vx
		V.y-=vy
		P.x+=vx
		P.y+=vy
		tvx+=vx
		tvy+=vy
		L-=Sqrt(vx*vx+vy*vy)
	End
	Method updateOut(timeFrame:Float)
		V.x=tvx
		V.y=tvy
		If(cast<ABall3D>(animation)<>Null)
			Cast<ABall3D>(animation).Rotate(tvx,tvy)
		End
		tvx=0.0
		tvy=0.0
		V.x/=timeFrame
		V.y/=timeFrame
		If(Abs(V.x)<0.1 And Abs(V.y)<0.1)
			V.x=0.0
			V.y=0.0
		End
		Init(V.x,V.y)
	End
	
	Method Render(canvas:Canvas) Override
		If((animation)<>Null)
			animation.Render(canvas)
		End
		If(displayFloat)
			canvas.DrawText(num,P.x,P.y,0.0,0.0)
		End
	End
	
	Method BounceB2B(ball:Ball,dx:Float,dy:Float)
		Local vx1:Float=ball.tvx+ball.V.x
		Local vy1:Float=ball.tvy+ball.V.y
		Local dp:Float=V.x*dx+V.y*dy
		Local a1:Float=dp*dx
		Local b1:Float=dp*dy
		dp=V.x*dy-V.y*dx
		Local a2:Float=dp*dy
		Local b2:Float=dp*-dx
		dp=ball.V.x*dx+ball.V.y*dy
		Local a21:Float=dp*dx
		Local b21:Float=dp*dy
		dp=ball.V.x*dy-ball.V.y*dx
		Local a22:Float=dp*dy
		Local b22:Float=dp*-dx
		Local t_P:Float=mass*a1+ball.mass*a21
		Local t_Vn:Float=a1-a21
		Local v2fx:Float=(t_P+t_Vn*mass)/(mass+ball.mass)
		Local v1fx:Float=v2fx-t_Vn
		t_P=mass*b1+ball.mass*b21
		t_Vn=b1-b21
		Local v2fy:Float=(t_P+t_Vn*mass)/(mass+ball.mass)
		Local v1fy:Float=v2fy-t_Vn
		V.x=friction*ball.friction*a2+bounce*ball.bounce*v1fx
		V.y=friction*ball.friction*b2+bounce*ball.bounce*v1fy
		ball.V.x=friction*ball.friction*a22+bounce*ball.bounce*v2fx
		ball.V.y=friction*ball.friction*b22+bounce*ball.bounce*v2fy
		Init(V.x,V.y)
		ball.Init(ball.V.x,ball.V.y)
		dp=tvx*dx+tvy*dy
		a1=dp*dx
		b1=dp*dy
		dp=tvx*dy-tvy*dx
		a2=dp*dy
		b2=dp*-dx
		dp=ball.tvx*dx+ball.tvy*dy
		a21=dp*dx
		b21=dp*dy
		dp=ball.tvx*dy-ball.tvy*dx
		a22=dp*dy
		b22=dp*-dx
		t_P=mass*a1+ball.mass*a21
		t_Vn=a1-a21
		v2fx=(t_P+t_Vn*mass)/(mass+ball.mass)
		v1fx=v2fx-t_Vn
		t_P=mass*b1+ball.mass*b21
		t_Vn=b1-b21
		v2fy=(t_P+t_Vn*mass)/(mass+ball.mass)
		v1fy=v2fy-t_Vn
		tvx=friction*ball.friction*a2+bounce*ball.bounce*v1fx
		tvy=friction*ball.friction*b2+bounce*ball.bounce*v1fy
		ball.tvx=friction*ball.friction*a22+bounce*ball.bounce*v2fx
		ball.tvy=friction*ball.friction*b22+bounce*ball.bounce*v2fy
		vx1-=ball.V.x+ball.tvx
		vy1-=ball.V.y+ball.tvy
		dp=Sqrt(vx1*vx1+vy1*vy1)
		If(dp>20.0)
			media.PlayBallCol(3)
		Else
			If(dp>10.0)
				media.PlayBallCol(2)
			Else
				If(dp>2.0)
					media.PlayBallCol(1)
				Else
					media.PlayBallCol(0)
				End
			End
		End
	End
	
	Method Bounce(ball:Ball,dx:Float,dy:Float) Override
		BounceB2B(ball,dx,dy)
	End
	
	Method CollisionDistance2Ghost:Float(ball:GhostBall) Override
		If num=16 Return INVALID_DISTANCE
		Return Distance2Ghost(ball,P.x,P.y,radius)
	End
End

Class LineWall Extends VectorObject
	
	Method New()
		Self.P=New PVector2D()
		Self.V=New PVector2D()
		Self.D=New PVector2D()
		Self.cp=New PVector2D()
		Self.name="Straight wall"
	End

	Method New(x1:Float,y1:Float,x2:Float,y2:Float,animation:ObjectAnimation,friction:Float,bounce:Float)
		Self.P=New PVector2D()
		Self.V=New PVector2D()
		Self.D=New PVector2D()
		Self.cp=New PVector2D()
		Self.name="Straight wall"
		Self.P.x=x1
		Self.P.y=y1
		Self.Init(x2-x1,y2-y1)
		Self.friction=friction
		Self.bounce=bounce
		Self.animation=animation
	End
	Method Distance:Float(ball:Ball) Override
		Self.tp = null
		Local a:Float=ball.P.x-Self.P.x
		Local b:Float=ball.P.y-Self.P.y
		Local a1:Float=ball.P.x+ball.V.x-Self.P.x
		Local b1:Float=ball.P.y+ball.V.y-Self.P.y
		Local d1:Float=a*Self.D.y-b*Self.D.x
		Local d2:Float=a1*Self.D.y-b1*Self.D.x
		If(Abs(d1)<ball.radius)
			Local vx:Float=ball.P.x-(Self.P.x+Self.V.x)
			Local vy:Float=ball.P.y-(Self.P.y+Self.V.y)
			If(vx*Self.V.x+vy*Self.V.y<=0.0 And a*Self.V.x+b*Self.V.y>=0.0)
				If(d1>0.0 And d1>d2)
					Self.cdx=-Self.D.y
					Self.cdy=Self.D.x
					Return 0.0
				Else
					If(d1<0.0 And d1<d2)
						Self.cdx=Self.D.y
						Self.cdy=-Self.D.x
						Return 0.0
					End
				End
			End
		End
		Local t:Float=0.0
		If(d1>0.0)
			t=(ball.radius-d1)/(d2-d1)
		Else
			If(d1<0.0)
				t=(ball.radius+d1)/(d1-d2)
			End
		End
		If(d1>0.0 And d2>=d1 Or d1<0.0 And d2<=d1)
			Local vx2:Float=ball.P.x-(Self.P.x+Self.V.x)
			Local vy2:Float=ball.P.y-(Self.P.y+Self.V.y)
			If(a*Self.D.x+b*Self.D.y>=0.0 And vx2*Self.D.x+vy2*Self.D.y<0.0)
				Return INVALID_DISTANCE
			End
		End
		If(t<=1.0 And t>=0.0)
			a=ball.V.x*t
			b=ball.V.y*t
			Self.cp.x=ball.P.x+a
			Self.cp.y=ball.P.y+b
			Local vx3:Float=Self.cp.x-Self.P.x
			Local vy3:Float=Self.cp.y-Self.P.y
			Local dp:Float=vx3*Self.D.x+vy3*Self.D.y
			If(dp>0.0)
				vx3=Self.cp.x-(Self.P.x+Self.V.x)
				vy3=Self.cp.y-(Self.P.y+Self.V.y)
				Self.cp.x=Self.P.x+dp*Self.D.x
				Self.cp.y=Self.P.y+dp*Self.D.y
				dp=vx3*Self.D.x+vy3*Self.D.y
				If(dp<0.0)
					If(Abs(d1)<ball.radius)
						Local diff:Float=ball.radius-Abs(d1)
						ball.P.x+=diff*Self.D.y
						ball.P.y-=diff*Self.D.x
					End
					Self.cdx=Self.D.y
					Self.cdy=-Self.D.x
					Self.tp=Self.cp
					Return t
				End
			End
		End
		Local dist:Float=Self.CollisionDistanceB2RW(ball,Self.P.x+Self.V.x,Self.P.y+Self.V.y,0.0)
		If(dist<>INVALID_DISTANCE)
			Return dist
		End
		dist=Self.CollisionDistanceB2RW(ball,Self.P.x,Self.P.y,0.0)
		If(dist=INVALID_DISTANCE)
			Self.tp = null
		End
		
		Return dist
	End
	Method Bounce(ball:Ball,dx:Float,dy:Float) Override
		Self.Bounce2Fixed(ball,dx,dy)
	End
	Method Render(canvas:Canvas) Override
		If((Self.animation)<>Null)
			Self.animation.Render(canvas)
		End
	End
	Method CollisionDistance2Ghost:Float(ball:GhostBall) Override
		Self.tp = null
		Local a:Float=ball.position.x-Self.P.x
		Local b:Float=ball.position.y-Self.P.y
		Local a1:Float=ball.position.x+ball.dx-Self.P.x
		Local b1:Float=ball.position.y+ball.dy-Self.P.y
		Local d1:Float=a*Self.D.y-b*Self.D.x
		Local d2:Float=a1*Self.D.y-b1*Self.D.x
		Local t:Float=0.0
		If(d1>0.0)
			t=(ball.radius-d1)/(d2-d1)
		Else
			If(d1<0.0)
				t=(ball.radius+d1)/(d1-d2)
			End
		End
		If(d1>0.0 And d2>=d1 Or d1<0.0 And d2<=d1)
			Return INVALID_DISTANCE
		End
		If(t>=0.0)
			Local px:Float=ball.position.x+ball.dx*t
			Local py:Float=ball.position.y+ball.dy*t
			Local vx:Float=px-Self.P.x
			Local vy:Float=py-Self.P.y
			Local dp:Float=vx*Self.D.x+vy*Self.D.y
			If(dp>0.0)
				vx=px-(Self.P.x+Self.V.x)
				vy=py-(Self.P.y+Self.V.y)
				dp=vx*Self.D.x+vy*Self.D.y
				If(dp<0.0)
					ball.cn.x=-Self.D.y
					ball.cn.y=Self.D.x
					Return t
				End
			End
		End
		Local dist:Float=Self.Distance2Ghost(ball,P.x+V.x,P.y+V.y,0.0)
		Local dx1:Float=ball.cn.x
		Local dy1:Float=ball.cn.y
		Local dist2:Float=Self.Distance2Ghost(ball,P.x,P.y,0.0)
		If dist2<dist
			dist=dist2
		Else
			ball.cn.x=dx1
			ball.cn.y=dy1
		End
		Return dist
	End
End

'*******************************************************
'
'	static roundwall(circle)
'
'*******************************************************

Class CircleWall Extends VectorObject

	Field radius:Float 'circle radius
	
	Method New()
		P = New PVector2D
		cp = New PVector2D
		name = "round wall"
	End Method
	
	Method New(x:Float,y:Float,radius:Float,animation:ObjectAnimation = Null,friction:Float = 1,bounce:Float=1)
		
		P = New PVector2D
		cp = New PVector2D
		
		name = "round wall"
		
		P.x = x
		P.y = y
		
		Self.radius = radius
		Self.friction = friction
		Self.bounce = bounce
		Self.animation = animation
	
	End Method
	
	Method SetFriction(f:Float)
		friction = f
	End Method
	
	Method Update()
	
	End Method

	'************************************************************************
	'
	'	distance of ball to wall(circle)
	'	returned values
	' 	valid distance distance 0.0 - 1.0.
	'
	'************************************************************************
	
	Method Distance:Float(ball:Ball) Override
		Return CollisionDistanceB2RW(ball,P.x,P.y,radius)
	End Method
	
	'************************************************************************
	'
	'	change movement vector after collision with wal(circle)
	'	
	'************************************************************************
	 
	Method Bounce(ball:Ball,dx:Float,dy:Float) Override
		Bounce2Fixed(ball,dx,dy)
	End Method

	Method Render(canvas:Canvas) Override
		If animation
			animation.Render(canvas)
		Else
			RenderCircle(canvas,P.x,P.y,radius)
		Endif
	End Method

End Class

Class ArcWall Extends VectorObject
	Field pa:PVector2D
	Field np:PVector2D
	Field target:PVector2D
	Field radius:Float
	Field startAngle:Float
	Field endAngle:Float
	
	Method New()
		
		P = New PVector2D()
		V = New PVector2D()
		D = New PVector2D()
		pa = New PVector2D()
		cp = New PVector2D()
		np = New PVector2D()
		name="Arc Wall"
		
	End Method
	
	Method SetAperture()
		
		pa.x = P.x+Cos(startAngle*ATR)*radius
		pa.y = P.y+Sin(startAngle*ATR)*radius
		V.x =  P.x+Cos(endAngle*ATR)*radius-pa.x
		V.y =  P.y+Sin(endAngle*ATR)*radius-pa.y
		Init(V.x,V.y)
		
	End Method
	
	Method New(x:Float,y:Float,radius:Float,startAngle:Float,endAngle:Float,animation:ObjectAnimation=Null,friction:Float=1.0,bounce:Float=1.0)
		
		P=New PVector2D()
		V=New PVector2D()
		D=New PVector2D()
		pa=New PVector2D()
		cp=New PVector2D()
		np=New PVector2D()
		target=New PVector2D()
		name="Arc Wall"
		P.x=x
		P.y=y
		target.x=x
		target.y=y
		Self.radius=radius
		Self.startAngle=startAngle
		Self.endAngle=endAngle
		SetAperture()
		Self.friction=friction
		Self.bounce=bounce
		Self.animation=animation
		
	End Method
	
	Method SetTarget(x:Float,y:Float)
		
		target.x=x
		target.y=y
		
	End Method
	
	Method BallInside:Bool(ball:Ball)
		
		Local vx:Float=ball.P.x-P.x
		Local vy:Float=ball.P.y-P.y
		Return (vx*vx+vy*vy) < (radius * radius)
		
	End Method
	
	Method Distance:float(ball:Ball) Override
		
		If(ball.L = 0.0) Return INVALID_DISTANCE
		
		tp=Null
		Local tcdx:Float
		Local tcdy:Float
		Local dist:Float=Self.CollisionDistanceB2RW(ball,P.x,P.y,radius)
		If(dist<>INVALID_DISTANCE)
			Local vx:Float=tp.x-pa.x
			Local vy:Float=tp.y-pa.y
			If(vx*Self.V.y-vy*Self.V.x>=0.0) Return dist
			Self.tp=Null
			dist=INVALID_DISTANCE
		Endif
		Local vx2:Float=P.x-ball.P.x
		Local vy2:Float=P.y-ball.P.y
		Local vx1:Float=-vx2
		Local vy1:Float=-vy2
		Local totRadius:Float=radius-ball.radius
		Local distSq:Float=vx2*vx2+vy2*vy2
		Local totRadSq:Float=totRadius*totRadius
		If(distSq>totRadSq  And  distSq < radius*radius)
			Local dst:Float=Sqrt(distSq)
			if(dst>0.0)
				cdx=vx1/dst
				cdy=vy1/dst
			Else
				cdx=ball.D.x
				cdy=ball.D.y
			Endif
			vx1=cdx*radius
			vy1=cdy*radius
			cp.x=P.x+vx1
			cp.y=P.y+vy1
			If(vx1*D.y-vy1*D.x>0.0  And  vx1*ball.D.x+vy1*ball.D.y>=0.0)
				tp=cp
				Return 0.0
			Endif
		Endif
		Local dp:Float=vx2*ball.D.y-vy2*ball.D.x
		If(Abs(dp)<radius)
			vx2=dp*ball.D.y
			vy2=dp*-ball.D.x
			Local a:Float=Sqrt(totRadSq-dp*dp)
			Local px:Float=P.x-vx2+a*ball.D.x
			Local py:Float=P.y-vy2+a*ball.D.y
			vx2=px-ball.P.x
			vy2=py-ball.P.y
			dp=vx2*ball.D.x+vy2*ball.D.y
			If(Abs(dp)<=ball.L  And  dp >= 0.0)
				vx2=px-P.x
				vy2=py-P.y
				Local len:Float=radius-ball.radius
				If(len>0.0)
					cdx=vx2/len
					cdy=vy2/len
				Else
					cdx=ball.D.x
					cdy=ball.D.y
				Endif
				px=P.x+cdx*radius
				py=P.y+cdy*radius
				vx2=px-pa.x
				vy2=py-pa.y
				Local dp2:Float=vx2*D.y-vy2*D.x
				If(dp2>=0.0  And  ball.L>0.0)
					cp.x=px
					cp.y=py
					tp=Self.cp
					
					dist=dp/ball.L
					
					Return dist
				Endif
				tp=Null
				dist=INVALID_DISTANCE
			Endif
		Endif
		
		Local nextDist:Float = CollisionDistanceB2RW(ball,pa.x,pa.y,0.0)
		
		If(nextDist<dist)
			dist=nextDist
			np.x=tp.x
			np.y=tp.y
			tcdx=cdx
			tcdy=cdy
		Endif
		
		nextDist=CollisionDistanceB2RW(ball,pa.x+D.x*L,pa.y+D.y*L,0.0)
		
		If(nextDist<dist)
			dist=nextDist
			np.x=tp.x
			np.y=tp.y
			tcdx=cdx
			tcdy=cdy
		Endif
		
		tp=np
		cdx=tcdx
		cdy=tcdy
		
		If dist = INVALID_DISTANCE
			tp=Null
		Endif
		
		Return dist
	End Method
	
	Method Bounce(ball:Ball,dx:Float,dy:Float) Override
		
		Self.Bounce2Fixed(ball,dx,dy)
		
	End Method
	
	Method Render(canvas:Canvas) Override
		
		If Self.animation
			Self.animation.Render(canvas)
		Endif
		
	End Method
	
	Method CollisionDistance2Ghost:Float(ball:GhostBall) Override
		
		Local dx:Float=.0
		Local dy:Float=.0
		Local dist:Float=Distance2Ghost(ball,P.x,P.y,radius)
		
		If(dist <> INVALID_DISTANCE)
			Local px:Float=ball.position.x+ball.dx*dist
			Local py:Float=ball.position.y+ball.dy*dist
			Local vx:Float=px-P.x
			Local vy:Float=py-P.y
			Local ln:Float=Sqrt(vx*vx+vy*vy)
			If(ln > 0.0)
				dx=vx/ln
				dy=vy/ln
				px=P.x+dx*radius
				py=P.y+dy*radius
			Endif
			vx=px-pa.x
			vy=py-pa.y
			If(vx*D.y-vy*D.x>=0.0)
				
				Return dist
			Endif
			dist=INVALID_DISTANCE
		Endif
		
		Local vx2:Float=P.x-ball.position.x
		Local vy2:Float=P.y-ball.position.y
		Local vx1:Float=-vx2
		Local vy1:Float=-vy2
		Local totRadius:Float=radius-ball.radius
		Local distSq:Float=vx2*vx2+vy2*vy2
		Local totRadSq:Float=totRadius*totRadius
		Local dp:Float=vx2*ball.dy-vy2*ball.dx
		
		if(Abs(dp)<radius)
			vx2=dp*ball.dy
			vy2=dp*-ball.dx
			Local a:Float=Sqrt(totRadSq-dp*dp)
			Local px2:Float=P.x-vx2+a*ball.dx
			Local py2:Float=P.y-vy2+a*ball.dy
			vx2=px2-ball.position.x
			vy2=py2-ball.position.y
			dp=vx2*ball.dx+vy2*ball.dy
			
			If(dp>=0.0)
				vx2=px2-P.x
				vy2=py2-P.y
				
				Local len:Float=radius-ball.radius
				
				If(len>0.0)
					cdx=vx2/len
					cdy=vy2/len
				Else
					cdx=ball.dx
					cdy=ball.dy
				Endif
				
				px2=P.x+cdx*radius
				py2=P.y+cdy*radius
				vx2=px2-pa.x
				vy2=py2-pa.y
				Local dp2:Float=vx2*D.y-vy2*D.x
				
				If(dp2>=0.0)
					ball.cn.x=-cdx
					ball.cn.y=-cdy
					
					Return dp
				Endif
				dist=INVALID_DISTANCE
			Endif
		Endif
		
		dx=ball.cn.x
		dy=ball.cn.y
		
		Local nextDist:Float=Distance2Ghost(ball,pa.x,pa.y,0.0)
		
		If(nextDist<dist)
			dist=nextDist
			dx=ball.cn.x
			dy=ball.cn.y
		Endif
		
		nextDist=Distance2Ghost(ball,pa.x+D.x*L,pa.y+D.y*L,0.0)
		
		If(nextDist<dist)
			dist=nextDist
			dx=ball.cn.x
			dy=ball.cn.y
		Endif
		
		ball.cn.x=dx
		ball.cn.y=dy
		
		Return dist
		
	End Method
	
End Class

Class GhostBall
	Field position:PVector2D
	Field cn:PVector2D
	Field radius:Float=.0
	Field image:Image[]
	Field dx:Float=.0
	Field dy:Float=.0
	Field frame:Int=0
	Field delay:Int=0
	Field stripImg:Image
	Field time:Int=0
	
	Field colBall:Ball
	Field distance:Float
	
	Method New(position:PVector2D,radius:Float,image:Image[],angle:Float,stpImg:Image)
		Self.position=position
		Self.cn=New PVector2D()
		Self.radius=radius
		Self.image=image
		Self.dx=Cos(angle*ATR)
		Self.dy=Sin(angle*ATR)
		Self.frame=0
		Self.delay=1
		Self.stripImg=stpImg
		Self.time=Millisecs()
	End

	Method Render(canvas:Canvas)
		Local x:Float=position.x+dx*distance
		Local y:Float=position.y+dy*distance
		
		If Millisecs()>time+delay
			frame=(frame+1) Mod 3
			time=Millisecs()
		End
		
		Local ang:Float=-ATan2(dy,dx)
		canvas.DrawImage(image[frame],x,y)
		canvas.DrawImage(stripImg,position.x,position.y,ang,distance,1.0)
		
		If colBall
			Local r2:Float=colBall.radius*2.0
			canvas.DrawLine(colBall.P.x,colBall.P.y,colBall.P.x-cn.x*r2,colBall.P.y-cn.y*r2)
			Local dp:Float=cn.x*-dx+cn.y*-dy
			Local dx1:Float=dp*cn.x
			Local dy1:Float=dp*cn.y
			dp=cn.y*dx-cn.x*dy
			dx1=dp*cn.y
			dy1=-dp*cn.x
			canvas.DrawLine(x,y,x+dx1*20.0,y+dy1*20.0)
		Else
			Local dp2:Float=cn.x*-dx+cn.y*-dy
			Local dx12:Float=dp2*cn.x
			Local dy12:Float=dp2*cn.y
			dp2=cn.y*dx-cn.x*dy
			dx12+=dp2*cn.y
			dy12+=dp2*-cn.x
			canvas.DrawLine(x,y,x+dx12*20.0,y+dy12*20.0)
		End
	End
End
