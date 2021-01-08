Namespace mojo3d.jsonifier

Class MojoJsonifierExt Extends JsonifierExt
	
	Const Instance:=New MojoJsonifierExt

	Method Jsonify:JsonValue( value:Variant,jsonifier:Jsonifier ) Override
		
		Select value.Type
		Case Typeof<TextureFlags>
			Return New JsonNumber( Int( Cast<TextureFlags>( value ) ) )
		End
		
		Return Null
	End

	Method Dejsonify:Variant( jvalue:JsonValue,type:TypeInfo,jsonifier:Jsonifier ) Override
		
		Select type
		Case Typeof<TextureFlags>
			Return Cast<TextureFlags>( Int( jvalue.ToNumber() ) )
		End
		
		Return Null
	End
	
End

Class StdJsonifierExt Extends JsonifierExt
	
	Const Instance:=New StdJsonifierExt

	Method Jsonify:JsonValue( value:Variant,jsonifier:Jsonifier ) Override
		
		Select value.Type
		Case Typeof<Vec2i>
			Local v:=Cast<Vec2i>( value )
			Return jsonifier.Jsonify( New Int[]( v.x,v.y ) )
		Case Typeof<Vec2f>
			Local v:=Cast<Vec2f>( value )
			Return jsonifier.Jsonify( New Float[]( v.x,v.y ) )
		Case Typeof<Recti>
			Local v:=Cast<Recti>( value )
			Return jsonifier.Jsonify( new Int[]( v.min.x,v.min.y,v.max.x,v.max.y ) )
		Case Typeof<Rectf>
			Local v:=Cast<Rectf>( value )
			Return jsonifier.Jsonify( New Float[]( v.min.x,v.min.y,v.max.x,v.max.y ) )
		Case Typeof<Vec3f>
			Local v:=Cast<Vec3f>( value )
			Return jsonifier.Jsonify( New Float[]( v.x,v.y,v.z ) )
		Case Typeof<Boxf>
			Local v:=Cast<Boxf>( value )
			Return jsonifier.Jsonify( New Float[]( v.min.x,v.min.y,v.min.z,v.max.x,v.max.y,v.max.z ) )
		Case Typeof<AffineMat4f>
			Local v:=Cast<AffineMat4f>( value )
			Return jsonifier.Jsonify( New Float[]( v.m.i.x,v.m.i.y,v.m.i.z, v.m.j.x,v.m.j.y,v.m.j.z, v.m.k.x,v.m.k.y,v.m.k.z, v.t.x,v.t.y,v.t.z ) )
		Case Typeof<Color>
			Local v:=Cast<Color>( value )
			Return jsonifier.Jsonify( New Float[]( v.r,v.g,v.b,v.a ) )
		Case typeof<Axis>
			Return New JsonNumber( Int( Cast<Axis>( value ) ) )
		End
		
		Return Null
	End

	Method Dejsonify:Variant( jvalue:JsonValue,type:TypeInfo,jsonifier:Jsonifier ) Override
		
		Select type
		Case Typeof<Vec2i>
			Local v:=jsonifier.Dejsonify<Int[]>( jvalue )
			Return New Vec2i( v[0],v[1] )
		Case Typeof<Vec2f>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New Vec2f( v[0],v[1] )
		Case Typeof<Recti>
			Local v:=jsonifier.Dejsonify<Int[]>( jvalue )
			Return New Recti( v[0],v[1],v[2],v[3] )
		Case Typeof<Rectf>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New Rectf( v[0],v[1],v[2],v[3] )
		Case Typeof<Vec3f>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New Vec3f( v[0],v[1],v[2] )
		Case Typeof<Boxf>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New Boxf( v[0],v[1],v[2],v[3],v[4],v[5] )
		Case Typeof<AffineMat4f>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New AffineMat4f( v[0],v[1],v[2], v[3],v[4],v[5], v[6],v[7],v[8], v[9],v[10],v[11] )
		Case Typeof<Color>
			Local v:=jsonifier.Dejsonify<Float[]>( jvalue )
			Return New Color( v[0],v[1],v[2],v[3] )
		Case Typeof<Axis>
			Return Cast<Axis>( Int( jvalue.ToNumber() ) )
		End
		
		Return Null
	End
	
End

Class InvocationJsonifierExt Extends JsonifierExt
	
	Const Instance:=New InvocationJsonifierExt
	
	Method Jsonify:JsonValue( value:Variant,jsonifier:Jsonifier ) Override
		
		Select value.Type
		Case Typeof<Invocation>
			
			Local v:=Cast<Invocation>( value )
			
			Local jobj:=New JsonObject
			
'			jobj.SetString( "scope",v.Scope.Name )
'			jobj.SetString( "decl",v.Decl.Name )

			Local decl:=v.Scope.Name
			If decl.EndsWith( " Extension" ) decl=decl.Slice( 0,-10 )
			decl+="."+v.Decl.Name
			
			jobj.SetString( "decl",decl )
			jobj.SetString( "type",v.Decl.Type )
			If v.Inst jobj.SetValue( "inst",jsonifier.Jsonify( v.Inst ) )
			jobj.SetValue( "args",jsonifier.Jsonify( v.Args ) )
			
			Return jobj
		End
		
		Return Null
	End
	
	Method Dejsonify:Variant( jvalue:JsonValue,type:TypeInfo,jsonifier:Jsonifier ) Override
		
		Select type
		Case Typeof<Invocation>
			
			Local jobj:=Cast<JsonObject>( jvalue )
			
			Local dname:=jobj.GetString( "decl" )
			Local dtype:=jobj.GetString( "type" )
			Local jinst:=jobj.Contains( "inst" ) ? jobj.GetValue( "inst" ) Else JsonValue.NullValue
			Local jargs:=jobj.GetArray( "args" )

			Local i:=dname.FindLast( "." )
			Local dscope:=dname.Slice( 0,i )
			dname=dname.Slice( i+1 )
			
			Local scope:=TypeInfo.GetType( dscope )
			Local decl:DeclInfo
			
			For Local tdecl:=Eachin scope.GetDecls( dname )
				If String(tdecl.Type)<>dtype Continue
				decl=tdecl
				Exit
			Next
			
			If Not decl
				For Local type:=Eachin reflection.GetTypeExtensions( scope )
					For Local tdecl:=Eachin type.GetDecls( dname )
						If String(tdecl.Type)<>dtype Continue
						scope=type
						decl=tdecl
						Exit
					Next
					If decl Exit
				Next
				Assert( decl )
			Endif
			
			Local type:=dname="New" ? scope Else decl.Type.ReturnType
			
			Local inst:=jsonifier.Dejsonify( jinst,type )'Typeof<Object> )
			
			Local args:=New Variant[jargs.Length]
			For Local i:=0 Until args.Length
				args[i]=jsonifier.Dejsonify( jargs[i],decl.Type.ParamTypes[i] )
			Next
			
			Local ctor:=New Invocation( scope,decl,inst,args )
			
			Return ctor
		End
		
		Return Null
	End
	
End
