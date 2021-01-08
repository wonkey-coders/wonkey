Namespace mojo3d.jsonifier

Class Invocation
	
	Method New( scope:TypeInfo,decl:DeclInfo,inst:Variant,args:Variant[] )
		_scope=scope
		_decl=decl
		_inst=inst
		_args=args
	End
	
	Method New( scope:TypeInfo,decl:String,inst:Variant,args:Variant[] )
		Init( scope,decl,inst,args )
	End
	
	Method New( name:String,inst:Variant,args:Variant[] )
		Local i:=name.FindLast( "." )
		Init( TypeInfo.GetType( name.Slice( 0,i ) ),name.Slice( i+1 ),inst,args )
	End
	
	Property Scope:TypeInfo()
		
		Return _scope
	End
	
	Property Decl:DeclInfo()
		
		Return _decl
	End
	
	Property Inst:Variant()
		
		Return _inst
	End
	
	Property Args:Variant[]()
		
		Return _args
	End
	
	Method Execute:Variant()
		
		Return _decl.Invoke( _inst,_args )
	End
	
	Private
	
	Field _scope:TypeInfo
	Field _decl:DeclInfo
	Field _inst:Variant
	Field _args:Variant[]
	
	Function FindDecl:DeclInfo( scope:TypeInfo,name:String,args:Variant[] )
	
		For Local decl:=Eachin scope.GetDecls( name )
			
			Local ftype:=decl.Type
			If ftype.ParamTypes.Length<>args.Length Continue
			
			Local match:=True
			For Local i:=0 Until args.Length
				
				If args[i]
					
					If args[i].Type.ExtendsType( ftype.ParamTypes[i] ) Continue
					
					If args[i].Type.Kind="Class" And ftype.ParamTypes[i].Kind="Class"
						
						Local obj:=Cast<Object>( args[i] )
						
						If Not obj Or obj.DynamicType.ExtendsType( ftype.ParamTypes[i] ) Continue
						
					Endif
					
				Else
					If ftype.ParamTypes[i].Kind="Class" Continue
				Endif
				match=False
				Exit
			Next
			
			If match Return decl
			
		Next
		
		Return Null
	End

	Method Init( scope:TypeInfo,name:String,inst:Variant,args:Variant[] )
		
		_scope=scope
		_inst=inst
		_args=args
		
		_decl=FindDecl( _scope,name,args )
		
		If Not _decl
			For Local type:=Eachin GetTypeExtensions( _scope )
				_decl=FindDecl( type,name,args )
				If Not _decl Continue
				_scope=type
				Exit
			Next
			Assert( _decl )
		Endif
	End
	
End

