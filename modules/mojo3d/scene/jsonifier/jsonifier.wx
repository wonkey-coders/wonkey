Namespace mojo3d.jsonifier

Class Jsonifier

Private
	
	Class Instance
		Field id:String
		Field obj:Variant
		Field ctor:Invocation
		Field initialState:JsonObject
		
		Operator To:String()
			Return "Instance(type="+obj.Type+" dynamic type="+obj.DynamicType+")"
		End
	End
	
	Field _loading:Int
	Field _instLoading:Int
	Field _instsByObj:=New Map<Object,Instance>
	Field _instsById:=New StringMap<Instance>
	Field _insts:=New Stack<Instance>
	
Public

	Method BeginLoading()
		
		_loading+=1

		If _loading>1 Return

		_instLoading=_insts.Length
	End
	
	Method EndLoading()
		
		_loading-=1
		
		If _loading Return
		
		For Local i:=_instLoading Until _insts.Length
			Local inst:=_insts[i]
			Local tobj:=Cast<Object>( inst.obj )
			inst.initialState=JsonifyState( tobj )
		next
	End
	
	Method AddInstance( obj:Variant,ctor:Invocation )
		
		Local tobj:=Cast<Object>( obj )
		
		Local inst:=_instsByObj[tobj]
		If inst
			If inst.ctor Print "Warning: overwriting instance ctor for "+inst
			inst.ctor=ctor
			Return
		Endif
		
		Local id:="#"+_insts.Length
			
		inst=New Instance
		inst.id=id
		inst.obj=obj
		
		_instsByObj[tobj]=inst
		_instsById[id]=inst
		_insts.Add( inst )
		
		If _loading Return

		inst.ctor=ctor
		inst.initialState=JsonifyState( tobj )
	End
	
	Method JsonifyInstances:JsonObject( assetsDir:String="" )
		
		If Not assetsDir assetsDir=AssetsDir()
		
		Local jobj:=New JsonObject
		
		jobj["assetsDir"]=New JsonString( assetsDir )
		
		Local jinsts:=New Stack<JsonValue>
		
		For Local i:=0 Until _insts.Length
			
			Local inst:=_insts[i]
			Local tobj:=Cast<Object>( inst.obj )

			'compute delta state
			Local state:=JsonifyState( tobj )
			
			Local dstate:=New JsonObject
			
			For Local it:=Eachin state.All()
				
				Local x:=it.Value
				Local y:=inst.initialState.GetValue( it.Key )
				
				If CompareJson( x,y )<>0 dstate[it.Key]=x
			Next
			
			'skip objects with no ctor and no delta state...
			If Not inst.ctor And dstate.Empty Continue
			
			Local jobj:=New JsonObject
			
			jobj["type"]=New JsonString( tobj.DynamicType.Name )	'not actually used, cool for debug
			
			jobj["id"]=New JsonString( inst.id )
			
			If inst.ctor jobj["ctor"]=Jsonify( inst.ctor )
				
			If Not dstate.Empty jobj["state"]=dstate
				
			jinsts.Add( jobj )
		Next

		jobj["instances"]=New JsonArray( jinsts )
		
		Return jobj
	End
	
	Method DejsonifyInstances( jobj:JsonObject )
		
		Local assetsDir:=AssetsDir()
		
		If jobj.Contains( "assetsDir" ) SetAssetsDir( jobj.GetString( "assetsDir" ) )
		
		Local jinsts:=jobj.GetArray( "instances" )

		Local jobjsById:=New StringMap<JsonObject>
		
		For Local i:=0 Until jinsts.Length
			
			Local jobj:=jinsts.GetObject( i )
			Assert( jobj.Contains( "id" ) )
			
			Local id:=jobj.GetString( "id" )
			Assert( Not jobjsById.Contains( id ) )
			
			jobjsById[id]=jobj
		Next
		
		Local n:=0,ninsts:=_insts.Length
		
		For Local i:=0 Until jinsts.Length
			
			Local jobj:=jinsts.GetObject( i )
			
			Local inst:Instance
			
			If jobj.Contains( "ctor" ) And i>=ninsts
				Local ctor:=Cast<Invocation>( Dejsonify( jobj["ctor"],Typeof<Invocation> ) )
				Local tobj:=Cast<Object>( ctor.Execute() )
				inst=_instsByObj[tobj]
			Else
				inst=_insts[i]
			Endif
			
			Local id:=jobj.GetString( "id" )
			_instsById[id]=inst
			inst.id=id

			For Local j:=n Until _insts.Length
				
				Local id:=_insts[j].id
				
				Local jobj:=jobjsById[id]
				If Not jobj Or Not jobj.Contains( "state" ) Continue
				
				Local tobj:=Cast<Object>( _insts[j].obj )
				
				DejsonifyState( tobj,jobj.GetObject( "state" ),tobj.DynamicType,False )
			Next
			
			n=_insts.Length
		Next
		
		'set reference type state - do this on a second pass 'coz of forward refs. Probably wont always work?
		For Local j:=0 Until _insts.Length
			
			Local id:=_insts[j].id
			
			Local jobj:=jobjsById[id]
			If Not jobj Or Not jobj.Contains( "state" ) Continue
			
			Local tobj:=Cast<Object>( _insts[j].obj )
			
			DejsonifyState( tobj,jobj.GetObject( "state" ),tobj.DynamicType,True )
		Next
		
		SetAssetsDir( assetsDir )
	End
	'ctor via ctor
	Method AddInstance( obj:Variant,args:Variant[] )
		
		AddInstance( obj,New Invocation( obj.DynamicType,"New",Null,args ) )
	end

	'ctor via method call
	Method AddInstance( obj:Variant,decl:String,inst:Variant,args:Variant[] )
		
		AddInstance( obj,New Invocation( decl,inst,args ) )
	End

	'ctor via function call
	Method AddInstance( obj:Variant,decl:String,args:Variant[] )
		
		AddInstance( obj,New Invocation( decl,Null,args ) )
	End
	
	Method Jsonify:JsonValue( value:Variant )
		
		If Not value Return JsonValue.NullValue
		
		Local type:=value.Type
		Assert( type )

		Select type.Kind
		Case "Primitive"
			Select type
			Case Typeof<Bool>
				Return New JsonBool( Cast<Bool>( value ) )
			Case Typeof<Short>
				Return New JsonNumber( Cast<Short>( value ) )
			Case Typeof<Int>
				Return New JsonNumber( Cast<Int>( value ) )
			Case Typeof<Float>
				Return New JsonNumber( Cast<Float>( value ) )
			Case Typeof<String>
				Return New JsonString( Cast<String>( value ) )
			End
		Case "Array"
			Local n:=value.GetArrayLength()
			Local jarray:=New JsonArray( n )
			For Local i:=0 Until n
				jarray[i]=Jsonify( value.GetArrayElement( i ) )
			Next
			Return jarray
		Case "Enum"
			Return New JsonNumber( value.EnumValue )
		End
		
		If IsInstanceType( type )
			Local obj:=Cast<Object>( value )
			If Not obj Return JsonValue.NullValue
			Local inst:=_instsByObj[obj]
			If inst Return New JsonString( inst.id )
			'For objects that weren't added using AddInstance, eg: textures loaded via Texture.Load instead of Scene.LoadTexture.
			Return JsonValue.NullValue	
'			RuntimeError( "Jsonifier can't find instance of type '"+type+"'" )
		Endif
		
		'try custom jsonifiers
		For Local jext:=Eachin JsonifierExt.All
			Local jvalue:=jext.Jsonify( value,Self )
			If jvalue Return jvalue
		Next
		
		RuntimeError( "No jsonifier found for type '"+type+"'" )
		Return Null
	End
	
	Method Dejsonify<T>:T( jvalue:JsonValue )
		
		Return Cast<T>( Dejsonify( jvalue,Typeof<T> ) )
	End
	
	Method Dejsonify:Variant( jvalue:JsonValue,type:TypeInfo )
		
		Select type.Kind
		Case "Primitive"
			Select type
			Case Typeof<Bool>
				Return jvalue.ToBool()
			Case Typeof<Short>
				Return Short( jvalue.ToNumber() )
			Case Typeof<Int>
				Return Int( jvalue.ToNumber() )
			Case Typeof<Float>
				Return Float( jvalue.ToNumber() )
			Case Typeof<String>
				Return jvalue.ToString()
			End
		Case "Array"
			Local elemType:=type.ElementType
			Local jarray:=Cast<JsonArray>( jvalue )
			Local n:=jarray.Length,v:=elemType.NewArray( n )
			For Local i:=0 Until n
				Local elem:=Dejsonify( jarray[i],elemType )
				v.SetArrayElement( i,elem )
			Next
			Return v
		Case "Enum"
			Return type.MakeEnum( jvalue.ToNumber() )
		End
		
		If IsInstanceType( type )
			If jvalue.IsNull
				Return type.NullValue
			Elseif jvalue.IsString
				Local id:=jvalue.ToString()
				Assert( _instsById.Contains( id ),"Dejsonify error" )
				Return _instsById[id].obj
			Endif
		Endif
		
		'try custom jsonifiers
		For Local jext:=Eachin JsonifierExt.All
			Local value:=jext.Dejsonify( jvalue,type,Self )
			If value Return value
		Next

		RuntimeError( "No dejsonifier found for type '"+type+"'" )
		
		Return Null
	End
	
	Private
	
	Method JsonifyState:JsonObject( obj:Object )
		
		Local jobj:=New JsonObject
		
		JsonifyState( obj,jobj,obj.DynamicType )
		
		Return jobj
	End
	
	Method JsonifyState( obj:Object,jobj:JsonObject,type:TypeInfo )
		
		If type.Kind<>"Class" Return
		
		If type.SuperType JsonifyState( obj,jobj,type.SuperType )
		
		For Local d:=Eachin type.GetDecls()
			
			If d.Kind<>"Property" Continue
			'Note: Add DeclInfo.Access property so we can do public fields only?
			If Not d.Gettable Or Not d.Settable Continue
			
			If Not Int( d.GetMetaValue( "jsonify" ) ) Continue
			
			jobj.SetValue( d.Name,Jsonify( d.Get( obj ) ) )
		Next
		
	End
	
	Method IsInstanceType:Bool( type:TypeInfo )
		
		If type.Kind="Class" Return True
		
		If type=Typeof<Texture> Return True	'Cheeze it for now!
		
		If type.Kind="Array" Return IsInstanceType( type.ElementType )
		
		Return False
	End

	Method DejsonifyState( obj:Object,jobj:JsonObject,type:TypeInfo,instTypes:Bool )
		
		If type.Kind<>"Class" Return
		
		If type.SuperType DejsonifyState( obj,jobj,type.SuperType,instTypes )

		For Local d:=Eachin type.GetDecls()
			
			If d.Kind<>"Property" Continue
			'Note: Add DeclInfo.Access property so we can do public fields only?
			If Not d.Gettable Or Not d.Settable Or Not jobj.Contains( d.Name ) Continue
			
			If Not Int( d.GetMetaValue( "jsonify" ) ) Continue
			
			If IsInstanceType( d.Type )<>instTypes Continue
			
			d.Set( obj,Dejsonify( jobj.GetValue( d.Name ),d.Type ) )
		Next
	
	End
	
End


Class JsonifierExt
	
	Const All:=New Stack<JsonifierExt>
	
	Method New()
		All.Add( Self )
	End
	
	Method Jsonify:JsonValue( value:Variant,jsonifier:Jsonifier ) Abstract
	
	Method Dejsonify:Variant( jvalue:JsonValue,type:TypeInfo,jsonifier:Jsonifier ) Abstract
End

