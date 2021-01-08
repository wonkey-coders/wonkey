Namespace mojo3d

Private

'Global nullBody:btRigidBody=New btRigidBody( 0,Null,Null,Null )

Public

Class Joint Extends Component
	
	Const ERP:=0		'error reduction parameter - http://bulletphysics.org/mediawiki-1.5.8/index.php/Definitions
	Const STOP_ERP:=1
	Const CFM:=2
	Const STOP_CFM:=3	'constraint force mixing
	
	Const Type:=New ComponentType( "Joint",-20,ComponentTypeFlags.Singleton )
	
	Method New( entity:Entity )
		
		Super.New( entity,Type )
	End
	
	Method New( entity:Entity,joint:Joint )
		
		Super.New( entity,Type )
	End

	Method SetParam( param:Int,value:Float )
		
		If _btconstraint _btconstraint.setParam( param+1,value )
		
		_params[param]=value
	End
	
	Method GetParam:Float( param:Int )
		
		Return _params[param]
	End
	
Protected

	Field _rvisible:Bool
	
	Field _params:=New Float[4]

	Field _btconstraint:btTypedConstraint
	
	Method OnCreate() Abstract
	
	Method OnBeginUpdate() Override
		
		Validate()
	End

	Method OnDestroy() Override
		
		If Not _btconstraint Return
		
		Entity.Scene.World.btWorld.removeConstraint( _btconstraint )
		_btconstraint.destroy()
		_btconstraint=Null
	End
	
	Method Validate()

		Local rvisible:=Entity.ReallyVisible
		
		If rvisible=_rvisible Return
		
		If rvisible
			If Not _btconstraint 
				OnCreate()
'				_btconstraint.setParam( ERP+1,_params[ERP] )
'				_btconstraint.setParam( STOP_ERP+1,_params[STOP_ERP] )
'				_btconstraint.setParam( CFM+1,_params[CFM] )
'				_btconstraint.setParam( STOP_CFM+1,_params[STOP_CFM] )
			Endif
			Entity.Scene.World.btWorld.addConstraint( _btconstraint )
		Else
			If _btconstraint Entity.Scene.World.btWorld.removeConstraint( _btconstraint )
		Endif
		
		_rvisible=rvisible
	End
	
End

Class BallSocketJoint Extends Joint
	
	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,joint:BallSocketJoint )
		
		Super.New( entity,joint )
		
		ConnectedBody=joint.ConnectedBody
		Pivot=joint.Pivot
		
		AddInstance( joint )
	End
	
	[jsonify=1]
	Property ConnectedBody:RigidBody()
		
		Return _connected
		
	Setter( body:RigidBody )
		
		_connected=body
	End
	
	[jsonify=1]
	Property Pivot:Vec3f()
		
		Return _pivot1
		
	Setter( pivot:Vec3f )
		
		_pivot1=pivot
	End
	
	Protected
	
	Field _connected:RigidBody
	Field _pivot1:Vec3f
	
	Method OnCreate() Override
		
		Local btBody1:=Entity.GetComponent<RigidBody>().btBody
		Assert( btBody1,"BallSocketJoint: No rigid body" )	'todo: fail nicely
		
		If _connected
			Local btBody2:=_connected.btBody
			Assert( btBody2,"BallSocketJoint: No rigid body" )	'todo: fail nicely
			Local tform:=_connected.Entity.InverseMatrix * Entity.Matrix
			Local pivot2:=tform * _pivot1
			_btconstraint=New btPoint2PointConstraint( btBody1,btBody2,_pivot1,pivot2 )
		Else
			_btconstraint=New btPoint2PointConstraint( btBody1,_pivot1 )
		End
	End
		
End

Class HingeJoint Extends Joint

	Method New( entity:Entity )
		
		Super.New( entity )
		
		Axis=New Vec3f( 0,1,0 )
		MinAngle=180
		MaxAngle=-180
		
		AddInstance()
	End
	
	Method New( entity:Entity,joint:HingeJoint )
		
		Super.New( entity,joint )
		
		ConnectedBody=joint.ConnectedBody
		Pivot=joint.Pivot
		Axis=joint.Axis
		MinAngle=joint.MinAngle
		MaxAngle=joint.MaxAngle
		
		AddInstance( joint )
	End
	
	[jsonify=1]
	Property ConnectedBody:RigidBody()
		
		Return _connected
		
	Setter( body:RigidBody )
		
		_connected=body
	End
	
	[jsonify=1]
	Property Pivot:Vec3f()
		
		Return _pivot1
		
	Setter( pivot:Vec3f )
		
		_pivot1=pivot
	End
	
	[jsonify=1]
	Property Axis:Vec3f()
		
		Return _axis1
		
	Setter( axis:Vec3f )
		
		_axis1=axis
	End
	
	Property MinAngle:Float()
		
		Return _minAngle
		
	Setter( angle:Float ) 
		
		_minAngle=angle
		
		SetLimits()
	End
	
	Property MaxAngle:Float()
		
		Return _maxAngle
		
	Setter( angle:Float ) 
		
		_maxAngle=angle
		
		SetLimits()
	End
	
	Protected
	
	Field _connected:RigidBody
	Field _pivot1:Vec3f
	Field _axis1:Vec3f
	Field _minAngle:Float
	Field _maxAngle:Float
	
	Method SetLimits()
		
		If Not _btconstraint Return
		
		Cast<btHingeConstraint>(_btconstraint).setLimit( _minAngle*Pi/180,_maxAngle*Pi/180 )
	End
	
	Method OnCreate() Override
		
		Local btBody1:=Entity.GetComponent<RigidBody>().btBody
		Assert( btBody1,"HingeJoint: No rigid body" )	'todo: fail nicely
		
		If _connected
			Local btBody2:=_connected.btBody
			Assert( btBody2,"HingeJoint: No rigid body" )	'todo: fail nicely
			Local tform:=_connected.Entity.InverseMatrix * Entity.Matrix
			Local pivot2:=tform * _pivot1
			Local axis2:=tform.m * _axis1
			_btconstraint=New btHingeConstraint( btBody1,btBody2,_pivot1,pivot2,_axis1,axis2 )
		Else
			_btconstraint=New btHingeConstraint( btBody1,_pivot1,_axis1 )
		End
		
		SetLimits()
	End
	
End

Class FixedJoint Extends Joint

	Method New( entity:Entity )
		
		Super.New( entity )
		
		AddInstance()
	End
	
	Method New( entity:Entity,joint:HingeJoint )
		
		Super.New( entity,joint )
		
		ConnectedBody=joint.ConnectedBody
		
		AddInstance( joint )
	End
	
	[jsonify=1]
	Property ConnectedBody:RigidBody()
		
		Return _connected
		
	Setter( body:RigidBody )
		
		_connected=body
	End
	
	Protected
	
	Field _connected:RigidBody
	
	Method OnCreate() Override
		
		Local btBody1:=Entity.GetComponent<RigidBody>()?.btBody
		Assert( btBody1,"FixedJoint: No rigid body" )	'todo: fail nicely

		Local btBody2:=_connected?.btBody
		Assert( btBody2,"FixedJoint: No connected rigid body" )	'todo: fail nicely
		
		Local tform:=_connected.Entity.InverseMatrix * Entity.Matrix
		
		_btconstraint=New btFixedConstraint( btBody1,btBody2,New AffineMat4f,tform )
	End
	
End

