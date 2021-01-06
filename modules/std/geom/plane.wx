
Namespace std.geom

Alias Planef:Plane<Float>

Struct Plane<T>

	Field n:Vec3<T>
	Field d:T
	
	Method New()
	End
	
	Method New( nx:Float,ny:Float,nz:Float,d:Float )
		n.x=nx;n.y=ny;n.z=nz;Self.d=d
	End
	
	Method New( n:Vec3<T>,d:T )
		Self.n=n
		Self.d=d
	End
	
	Method New( p:Vec3<T>,n:Vec3<T> )
		Self.n=n
		Self.d=-n.Dot( p )
	End
	
	Method New( v0:Vec3<T>,v1:Vec3<T>,v2:Vec3<T> )
		n=(v1-v0).Cross(v2-v0).Normalize()
		d=-n.Dot( v0 )
	End
	
	Operator-:Plane()
		Return New Plane( -n,-d )
	End
	
	Method Distance:Double( p:Vec3<T> )
		Return n.Dot( p )+d
	End
	
	Method Nearest:Vec3<T>( p:Vec3<T> )
		Return p-n*Distance( p )
	End
	
	Method Normalize:Plane()
		Local l:=n.Length
		Return New Planef( n/l,d/l )
	End
	
	Method TIntersect:Double( line:Line<T> )
		Return -Distance( line.o )/n.Dot( line.d )
	End
	
	Method Intersect:Vec3<T>( line:Line<T> )
		Return line * TIntersect( line )
	End
	
	Method Intersect:Line<T>( p:Plane<T> )
		Local v:=n.Cross( p.n ).Normalize()
		Local o:=p.Intersect( New Line<T>( n*-d,n.Cross( v ) ) )
		Return New Line<T>( o,v )
	End
	
	Operator To:String()
		Return "Plane("+n+","+d+")"
	End
		
End
