
Namespace mojo3d.vr

Struct HmdMatrix34_t Extension
	
	Operator To:AffineMat4f()
	
		Local r:AffineMat4f
		
		'negate Z components and scale by 1,1,-1...

		r.m.i.x= m[0][0] ; r.m.i.y= m[1][0] ; r.m.i.z=-m[2][0]
		r.m.j.x= m[0][1] ; r.m.j.y= m[1][1] ; r.m.j.z=-m[2][1]
		r.m.k.x=-m[0][2] ; r.m.k.y=-m[1][2] ; r.m.k.z= m[2][2]
		r.t.x=   m[0][3] ; r.t.y=   m[1][3] ; r.t.z=  -m[2][3]
		
		Return r
	End
End

Struct HmdMatrix44_t Extension
	
	Operator To:Mat4f()
		Local r:Mat4f
		r.i.x=m[0][0] ; r.i.y=m[1][0] ; r.i.z=m[2][0] ; r.i.w=m[3][0]
		r.j.x=m[0][1] ; r.j.y=m[1][1] ; r.j.z=m[2][1] ; r.j.w=m[3][1]
		r.k.x=m[0][2] ; r.k.y=m[1][2] ; r.k.z=m[2][2] ; r.k.w=m[3][2]
		r.t.x=m[0][3] ; r.t.y=m[1][3] ; r.t.z=m[2][3] ; r.t.w=m[3][3]
		Return r
	End

End

Struct HmdVector3_t Extension
	
	Operator To:Vec3f()
		Local r:Vec3f
		r.x=v[0] ; r.y=v[1] ; r.z=v[2]
		Return r
	End
	
End

Struct AffineMat4f Extension
	
	Operator To:HmdMatrix34_t()
		Local r:HmdMatrix34_t
		r.m[0][0]= m.i.x ; r.m[1][0]= m.i.y ; r.m[2][0]=-m.i.z
		r.m[0][1]= m.j.x ; r.m[1][1]= m.j.y ; r.m[2][1]=-m.j.z
		r.m[0][2]=-m.k.x ; r.m[1][2]=-m.k.y ; r.m[2][2]= m.k.z
		r.m[0][3]=   t.x ; r.m[1][3]=   t.y ; r.m[2][3]=  -t.z
		Return r
	End
	
End

Struct Mat4f Extension
	
	Operator To:HmdMatrix44_t()
		Local r:HmdMatrix44_t
		r.m[0][0]=i.x ; r.m[1][0]=i.y ; r.m[2][0]=i.z ; r.m[3][0]=i.w
		r.m[0][1]=j.x ; r.m[1][1]=j.y ; r.m[2][1]=j.z ; r.m[3][1]=j.w
		r.m[0][2]=k.x ; r.m[1][2]=k.y ; r.m[2][2]=k.z ; r.m[3][2]=k.w
		r.m[0][3]=t.x ; r.m[1][3]=t.y ; r.m[2][3]=t.z ; r.m[3][3]=t.w
		Return r
	End

End

Struct Vec3f Extension
	
	Operator To:HmdVector3_t()
		Local r:HmdVector3_t
		r.v[0]=x ; r.v[1]=y ; r.v[2]=z
		Return r
	End
End

Function Frustum:Mat4f( left:Float,right:Float,bottom:Float,top:Float,near:Float,far:Float )

	Local w:=right-left,h:=top-bottom,d:=far-near,r:Mat4f
	
	r.i.x= 2/w
	r.j.y= 2/h
	r.k.x=-(right+left)/w
	r.k.y=-(top+bottom)/h
	r.k.z= (far+near)/d
	r.k.w= 1
	r.t.z= -2*far*near/d
	
	Return r
End
