
Namespace std.geom

Alias Boxf:Box<Float>

Struct Box<T>

	Const FullBounds:=New Box( -1000000,-1000000,-1000000,1000000,1000000,1000000 )

	Const EmptyBounds:=New Box( 1000000,1000000,1000000,-1000000,-1000000,-1000000 )
	
	Field min:Vec3<T>
	Field max:Vec3<T>
	
	Method New()
	End
	
	Method New( p:Vec3<T> )
		Self.min=p
		Self.max=p
	End
	
	Method New( min:T,max:T )
		Self.min=New Vec3<T>( min )
		Self.max=New Vec3<T>( max )
	End
	
	Method New( min:Vec3<T>,max:Vec3<T> )
		Self.min=min
		Self.max=max
	End
	
	Method New( x0:T,y0:T,z0:T,x1:T,y1:T,z1:T )
		min.x=x0;min.y=y0;min.z=z0
		max.x=x1;max.y=y1;max.z=z1
	End
	
	Operator To:String()
		Return "Box("+min+","+max+")"
	End
	
	Operator To<C>:Box<C>()
		Return New Box<C>( min,max )
	End
	
	Property Empty:Bool()
		Return max.x<=min.x Or max.y<=min.y Or max.z<=min.z
	End
	
	Property Center:Vec3<T>()
		Return (min+max)/2
	End
	
	Property Size:Vec3<T>()
		Return max-min
	End
	
	Property Width:T()
		Return max.x-min.x
	End
	
	Property Height:T()
		Return max.y-min.y
	End
	
	Property Depth:T()
		Return max.z-min.z
	End
	
	Operator+:Box( v:Vec3<T> )
		Return New Box( min+v,max+v )
	End
	
	Operator+=( v:Vec3<T> )
		min+=v
		max+=v
	End
	
	Operator-:Box( v:Vec3<T> )
		Return New Box( min-v,max-v )
	End
	
	Operator-=( v:Vec3<T> )
		min-=v
		max-=v
	End
	
	Operator&:Box( box:Box )
		Return New Box(
			Max( min.x,box.min.x ),
			Max( min.y,box.min.y ),
			Max( min.z,box.min.z ),
			Min( max.x,box.max.x ),
			Min( max.y,box.max.y ),
			Min( max.z,box.max.z ) )
	End
	
	Operator&=( box:Box )
		min.x=Max( min.x,box.min.x )
		min.y=Max( min.y,box.min.y )
		min.z=Max( min.z,box.min.z )
		max.x=Min( max.x,box.max.x )
		max.y=Min( max.y,box.max.y )
		max.z=Min( max.z,box.max.z )
	End
	
	Operator|:Box( box:Box )
		Return New Box(
			Min( min.x,box.min.x ),
			Min( min.y,box.min.y ),
			Min( min.z,box.min.z ),
			Max( max.x,box.max.x ),
			Max( max.y,box.max.y ),
			Max( max.z,box.max.z ) )
	End
	
	Operator|=( box:Box )
		min.x=Min( min.x,box.min.x )
		min.y=Min( min.y,box.min.y )
		min.z=Min( min.z,box.min.z )
		max.x=Max( max.x,box.max.x )
		max.y=Max( max.y,box.max.y )
		max.z=Max( max.z,box.max.z )
	End
	
	Operator|:Box( p:Vec3<T> )
		Return New Box(
			Min( min.x,p.x ),
			Min( min.y,p.y ),
			Min( min.z,p.z ),
			Max( max.x,p.x ),
			Max( max.y,p.y ),
			Max( max.z,p.z ) )
	End
	
	Operator|=( p:Vec3<T> )
		min.x=Min( min.x,p.x )
		min.y=Min( min.y,p.y )
		min.z=Min( min.z,p.z )
		max.x=Max( max.x,p.x )
		max.y=Max( max.y,p.y )
		max.z=Max( max.z,p.z )
	End
	
	Method Contains:bool( box:Box )
		Return min.x>=box.min.x And max.x<=box.max.x And min.y>=box.min.y And max.y<=box.max.y And min.z>=box.min.z And min.z<=box.max.z
	End
	
	Method Intersects:Bool( box:Box )
		Return min.x<box.max.x And max.x>box.min.x And min.y<box.max.y And max.y>box.min.y And min.z<box.max.z And max.z>box.min.z
	End
	
	Method Corner:Vec3<T>( index:int )
		Select index
		Case 0 Return min
		case 1 Return New Vec3<T>( max.x,min.y,min.z )
		case 2 Return New Vec3<T>( min.x,max.y,min.z )
		case 3 Return New Vec3<T>( max.x,max.y,min.z )
		Case 4 Return New Vec3<T>( min.x,min.y,max.z )
		Case 5 Return New Vec3<T>( max.x,min.y,max.z )
		Case 6 Return New Vec3<T>( min.x,max.y,max.z )
		Case 7 Return max
		End
		RuntimeError( "Invalid box corner index: "+index )
		Return Null
	End
	
End
