
Namespace mojo3d

#Import "native/internaledges.cpp"
#Import "native/internaledges.h"

Extern Private
 
Function CreateInternalEdgeInfo( mesh:btBvhTriangleMeshShape )="bbBullet::createInternalEdgeInfo"

Private
	
Global emptyShape:=New btEmptyShape

Public
	
Class Collider Extends Component
	
	Const Type:=New ComponentType( "Collider",10,ComponentTypeFlags.Singleton )
	
	Method New( entity:Entity )
		
		Super.New( entity,Type )
	End
	
	Method New( entity:Entity,collider:Collider )
		
		Super.New( entity,Type )
	End

	Property Margin:Float()
		
		Return Validate().getMargin()
	
	Setter( margin:Float )
		
		Validate().setMargin( margin )
	End

	Method CalculateLocalInertia:Vec3f( mass:Float )
		
		Return Validate().calculateLocalInertia( mass )
	End
	
	Method Validate:btCollisionShape()
		
		If _btshape Return _btshape
		
		_btshape=OnCreate()
		
		Return _btshape
	End
	
Protected

	Method OnCreate:btCollisionShape() Abstract
	
	Method Invalidate()
		
		If Not _btshape  Return
		
		_btshape.destroy()
		_btshape=Null
		
		Entity.RigidBody?.ColliderInvalidated()
	End
	
	function SetOrigin:btCollisionShape( shape:btCollisionShape,origin:Vec3f )
		
		If origin=Null Return shape
		
		Local tshape:=New btCompoundShape( False,1 )
		
		tshape.addChildShape( AffineMat4f.Translation( origin ),shape )
		
		Return tshape
	End
	
	Private
	
	Field _btshape:btCollisionShape
	
End

Class ConvexCollider Extends Collider
	
	Method New( Entity:Entity )
		
		Super.New( Entity )
	End
	
	Method New( entity:Entity,collider:ConvexCollider )
		
		Super.New( entity,collider )
	End
	
End

Class BoxCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		Box=New Boxf( -1,1 )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:BoxCollider )
		
		Super.New( entity,collider )
		
		Box=collider.Box
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Box:Boxf()
		
		Return _box
	
	Setter( box:Boxf )
		
		_box=box
		
		Invalidate()
	End
	
	Protected
	
	Method OnCopy:BoxCollider( entity:Entity ) Override
		
		local collider:=New BoxCollider( entity,Self )
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override

		Local shape:=New btBoxShape( _box.Size/2 )
		
		Return SetOrigin( shape,_box.Center )
	End
	
	Private
	
	Field _box:=New Boxf( -1,1 )
End

Class SphereCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:SphereCollider )
		
		Super.New( entity,collider )
		
		Radius=collider.Radius
		Origin=collider.Origin
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Radius:Float()
		
		Return _radius
	
	Setter( radius:Float )
		
		_radius=radius
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Origin:Vec3f()
		
		Return _origin
		
	Setter( origin:Vec3f )
		
		_origin=origin
		
		Invalidate()
	End
	
	Protected
	
	Method OnCopy:SphereCollider( entity:Entity ) Override
		
		Local collider:=New SphereCollider( entity,Self )
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override
		
		Local shape:=New btSphereShape( _radius )
		
		return SetOrigin( shape,_origin )
	End
	
	Private
	
	Field _radius:Float=1
	
	Field _origin:Vec3f
	
End

Class CylinderCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:CylinderCollider )
		
		Super.New( entity,collider )
		
		Radius=collider.Radius
		Length=collider.Length
		Axis=collider.Axis
		Origin=collider.Origin
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Radius:Float()
		
		Return _radius
		
	Setter( radius:Float )
		
		_radius=radius
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Length:Float()
		
		Return _length
		
	Setter( length:Float )
		
		_length=length
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Axis:Axis()
		
		Return _axis
		
	Setter( axis:Axis )
		
		_axis=axis
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Origin:Vec3f()
		
		Return _origin
	
	Setter( origin:Vec3f )
		
		_origin=origin
		
		Invalidate()
	End

	Protected

	Method OnCopy:CylinderCollider( entity:Entity ) Override
		
		Local collider:=New CylinderCollider( entity )
		
		collider.Radius=Radius
		collider.Length=Length
		collider.Axis=Axis
		collider.Origin=Origin
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override

		Local shape:btCollisionShape
		
		Select _axis
		case Axis.X
			shape=New btCylinderShapeX( New btVector3( _length/2,_radius,_radius ) )
		Case Axis.Y
			shape=New btCylinderShape ( New btVector3( _radius,_length/2,_radius ) )
		case Axis.Z
			shape=New btCylinderShapeZ( New btVector3( _radius,_radius,_length/2 ) )
		Default
			RuntimeError( "Invalid Cylinder Axis" )
		End
		
		Return SetOrigin( shape,_origin )
	End
	
	Private
	
	Field _radius:Float=0.5
	Field _length:Float=1.0
	Field _axis:Axis=geom.Axis.Y
	Field _origin:Vec3f

End

Class CapsuleCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:CapsuleCollider )
		
		Super.New( entity,collider )
		
		Radius=collider.Radius
		Length=collider.Length
		Axis=collider.Axis
		Origin=collider.Origin
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Radius:Float()
		
		Return _radius
		
	Setter( radius:Float )
		
		_radius=radius
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Length:Float()
		
		Return _length
		
	Setter( length:Float )
		
		_length=length
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Axis:Axis()
		
		Return _axis
		
	Setter( axis:Axis )
		
		_axis=axis
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Origin:Vec3f()
		
		Return _origin
	
	Setter( origin:Vec3f )
		
		_origin=origin
		
		Invalidate()
	End

	Protected
	
	Method OnCopy:CapsuleCollider( entity:Entity ) Override
		
		Local collider:=New CapsuleCollider( entity,Self )
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override
		
		Local shape:btCollisionShape
		
		Select _axis
		Case Axis.X
			shape=New btCapsuleShapeX( _radius,_length )
		Case Axis.Y
			shape=New btCapsuleShape ( _radius,_length )
		Case Axis.Z
			shape=New btCapsuleShapeZ( _radius,_length )
		Default
			RuntimeError( "Invalid Capsule Axis" )
		End
		
		Return SetOrigin( shape,_origin )
	End
	
	Private
	
	Field _radius:Float=0.5
	Field _length:Float=1.0
	Field _axis:Axis=geom.Axis.Y
	Field _origin:Vec3f

End

Class ConeCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End

	Method New( entity:Entity,collider:ConeCollider )
		
		Super.New( entity,collider )
		
		Radius=collider.Radius
		Length=collider.Length
		Axis=collider.Axis
		Origin=collider.Origin
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Radius:Float()
		
		Return _radius
		
	Setter( radius:Float )
		
		_radius=radius
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Length:Float()
		
		Return _length
		
	Setter( length:Float )
		
		_length=length
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Axis:Axis()
		
		Return _axis
		
	Setter( axis:Axis )
		
		_axis=axis
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Origin:Vec3f()
		
		Return _origin
	
	Setter( origin:Vec3f )
		
		_origin=origin
		
		Invalidate()
	End

	Protected
	
	Method OnCopy:ConeCollider( entity:Entity ) Override
		
		Local collider:=New ConeCollider( entity,Self )
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override
		
		Local shape:btCollisionShape
		
		Select _axis
		Case Axis.X
			shape=New btConeShapeX( _radius,_length )
		Case Axis.Y
			shape=New btConeShape ( _radius,_length )
		Case Axis.Z
			shape=New btConeShapeZ( _radius,_length )
		Default
			RuntimeError( "Invalid Cone Axis" )
		End

		Return SetOrigin( shape,_origin )
	End
	
	Private
	
	Field _radius:Float=0.5
	Field _length:Float=1.0
	Field _axis:Axis=geom.Axis.Y
	Field _origin:Vec3f
	
End

Class ConvexHullCollider Extends ConvexCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:ConvexHullCollider )
		
		Super.New( entity,collider )
		
		Mesh=collider.Mesh
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property Mesh:Mesh()
		
		Return _mesh
	
	Setter( mesh:Mesh ) 
		If mesh=_mesh Return
		
		_mesh=mesh
		
		Invalidate()
	End

	Private
	
	Field _mesh:Mesh	
	
	Method OnCreate:btCollisionShape() Override
		
		If Not _mesh Return emptyShape
		
		Local vertices:=_mesh.GetVertices()
		
		Local points:=New btScalar[vertices.Length*3]
		
		For Local i:=0 Until vertices.Length
			libc.memcpy( points.Data+i*3,Varptr( vertices[i].position ),12 )
		Next
		
		Local shape:=New btConvexHullShape( points.Data,points.Length/3,12 )
		
		Return shape
	End
	
End

Class ConcaveCollider Extends Collider

	Method New( entity:Entity )
		
		Super.New( entity )
	End
	
	Method New( entity:Entity,collider:ConcaveCollider )
		
		Super.New( entity,collider )
	End
		
End

Class MeshCollider Extends ConcaveCollider
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:MeshCollider )
		
		Super.New( entity,collider )
		
		UseInternalEdgeInfo=collider.UseInternalEdgeInfo
		Mesh=collider.Mesh
		
		AddInstance( collider )
	End
	
	[jsonify=1]
	Property UseInternalEdgeInfo:Bool()
		
		Return _internalEdgeInfo
	
	Setter( internalEdgeInfo:Bool )
		If internalEdgeInfo=_internalEdgeInfo Return
		
		_internalEdgeInfo=internalEdgeInfo
		
		Invalidate()
	End
	
	[jsonify=1]
	Property Mesh:Mesh()
		
		Return _mesh
	
	Setter( mesh:Mesh )
		If mesh=_mesh Return
		
		_mesh=mesh
		
		Invalidate()
	End

	Protected
	
	Method OnCopy:MeshCollider( entity:Entity ) Override
		
		Local collider:=New MeshCollider( entity,Self )
		
		Return collider
	End
	
	Method OnCreate:btCollisionShape() Override
		
		If Not _mesh Return emptyShape
		
		Local vertices:=_mesh.GetVertices()
		_vertices=New btScalar[vertices.Length*3]
		For Local i:=0 Until vertices.Length
			libc.memcpy( _vertices.Data+i*3,Varptr( vertices[i].position ),12 )
		Next
		
		Local indices:=_mesh.GetAllIndices()
		_indices=New Int[indices.Length]
		libc.memcpy( _indices.Data,indices.Data,_indices.Length*4 )
		
		_btmesh=New btTriangleIndexVertexArray( _indices.Length/3,_indices.Data,12,_vertices.Length,_vertices.Data,12 )
		
		Local shape:=New btBvhTriangleMeshShape( _btmesh,True,True )
		
		If _internalEdgeInfo CreateInternalEdgeInfo( shape )
		
		Return shape
	End
	
	Private
	
	Field _mesh:Mesh
	Field _vertices:btScalar[]
	Field _indices:Int[]
	Field _btmesh:btTriangleIndexVertexArray
	Field _internalEdgeInfo:Bool
	
End

Class TerrainCollider Extends ConcaveCollider

	Method New( entity:Entity )
		
		Super.New( entity )
		
		Bounds=New Boxf( -1,1 )
		
		AddInstance()
	End
	
	Method New( entity:Entity,collider:TerrainCollider )
		
		Super.New( entity,collider )
		
		Heightmap=collider.Heightmap
		Bounds=collider.Bounds
		UseDiamondSubdivision=collider.UseDiamondSubdivision
		UseZigzagSubdivision=collider.UseZigzagSubdivision
		
		AddInstance( collider )
	End
	
	Property Heightmap:Pixmap()
		
		Return _heightmap
		
	Setter( heightmap:Pixmap )
		
		If heightmap=_heightmap Return
		
		Assert( heightmap.Format=PixelFormat.I8,"Heightmap must be in I8 format" )
		
		_heightmap=heightmap
		
		Invalidate()
		
		_shape=Null
	End
	
	Property Bounds:Boxf()
		
		Return _bounds
	
	Setter( bounds:Boxf )
		
		_bounds=bounds
		
		Invalidate()
	End
	
	Property UseDiamondSubdivision:Bool()
		
		Return _diamondSubdiv
		
	Setter( diamondSubdiv:Bool )
			
		_diamondSubdiv=diamondSubdiv
		
		If _shape _shape.setUseDiamondSubdivision( _diamondSubdiv )
	End
	
	Property UseZigzagSubdivision:Bool()
		
		Return _zigzagSubdiv
	
	Setter( zigzagSubdiv:Bool )
		
		_zigzagSubdiv=zigzagSubdiv

		If _shape _shape.setUseZigzagSubdivision( _zigzagSubdiv )
	End
	
	Protected
	
	Method OnCreate:btCollisionShape() Override
		
		If Not _shape
			_shape=New btHeightfieldTerrainShape( _heightmap.Width,_heightmap.Height,_heightmap.Data,1.0/255.0,0.0,1.0,1,PHY_UCHAR,False )
			_shape.setUseDiamondSubdivision( _diamondSubdiv )
			_shape.setUseZigzagSubdivision( _zigzagSubdiv )
		Endif
		
		_shape.setLocalScaling( New Vec3f( _bounds.Width/_heightmap.Width,_bounds.Height,_bounds.Depth/_heightmap.Height ) )
		
		Return SetOrigin( _shape,_bounds.Center )
	End
	
	Private
	
	Field _heightmap:Pixmap
	Field _bounds:Boxf
	
	Field _diamondSubdiv:Bool
	Field _zigzagSubdiv:Bool
	
	Field _shape:btHeightfieldTerrainShape

End
