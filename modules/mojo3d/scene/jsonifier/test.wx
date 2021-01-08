Namespace test

#Reflect test

#Import "<std>"

#Import "jsonifier"
#Import "invocation"
#Import "jsonifierexts"
#Import "comparejson"

Using std..
Using jsonifier..

Global editing:=True
Global jsonifier:=New Jsonifier

Class Component
	
	'simple contructor
	Method New( entity:Entity )
		
		_entity=entity
		
		_entity.AddComponent( Self )
	End

	'copy contructor
	Method New( component:Component,entity:Entity )
		
		Self.New( entity )
	End
	
	Property Entity:Entity()
		
		Return _entity
	End
	
	Protected
	
	Method OnCopy:Component( entity:Entity ) Abstract
	
	Method SaveInitialState()
		
		If editing jsonifier.AddInstance( Self,New Variant[]( _entity ) )
	End
	
	Method SaveInitialState( component:Component )
		
		If editing jsonifier.AddInstance( Self,New Variant[]( component,_entity ) )
	End
	
	Private
	
	Field _entity:Entity
	
End

Class Behaviour Extends Component
	
	'simple contructor
	Method New( entity:Entity )
		
		Super.New( entity )
		
		Color=graphics.Color.White
			
		SaveInitialState()
	End
	
	'copy constructor
	Method New( behaviour:Behaviour,entity:Entity )
		
		Super.New( entity )
		
		Color=behaviour.Color
		
		SaveInitialState( behaviour )
	End
	
	Property Color:Color()
		
		Return _color
		
	Setter( color:Color )
		
		_color=color
	End
	
	Internal
	
	Method OnCopy:Behaviour( entity:Entity ) Override
		
		Return New Behaviour( Self,entity )
	End
	
	Private
	
	Field _color:Color
End

Class Entity
	
	'simple ctor
	Method New( parent:Entity )
		
		_parent=parent
		
		If _parent _parent._children.Add( Self )
	End
	
	'copy ctor
	Method New( entity:Entity,parent:Entity )
		
		Self.New( parent )
	End
	
	Property Visible:Bool()
		
		Return _visible
	
	Setter( visible:Bool )
		
		_visible=visible
	End
	
	Method Copy:Entity( parent:Entity ) Virtual
		
		Local copy:=OnCopy( parent )
		
		CopyTo( copy )
		
		Return copy
	End
	
	Method AddComponent<T>:T()
		
		Local component:=New T( Self )
		
		Return component
	End
	
	Protected
	
	Method OnCopy:Entity( parent:Entity ) Virtual
		
		Return New Entity( Self,parent )
	End
	
	Method CopyTo( copy:Entity )
		
		For Local child:=Eachin _children
			
			child.CopyTo( child.OnCopy( copy ) )
		Next
		
		For Local c:=Eachin _components
			
			c.OnCopy( copy )
		Next
	End
	
	Method SaveInitialState()
		
		If editing jsonifier.AddInstance( Self,New Variant[]( _parent ) )
	End

	Method SaveInitialState( entity:Entity )
		
		If editing jsonifier.AddInstance( Self,New Variant[]( entity,_parent ) )
	End
	
	Private
	
	Field _parent:Entity
	
	Field _children:=New Stack<Entity>
	
	Field _visible:Bool
	
	Field _components:=New Stack<Component>
	
	Method AddComponent( component:Component )
		
		_components.Add( component )
	End
	
End

Class Camera Extends Entity
	
	Method New( parent:Entity )

		Super.New( parent )
		
		FOV=90
		
		SaveInitialState()
		
		Visible=True
	End
	
	Method New( camera:Camera,parent:Entity )
		
		Super.New( camera,parent )
		
		FOV=camera.FOV
		
		SaveInitialState( camera )
		
		Visible=True
	End
	
	Property FOV:Float()
	
		Return _fov
	
	Setter( fov:Float )
		
		_fov=fov
	End
	
	Method Copy:Camera( parent:Entity ) Override
		
		Local camera:=OnCopy( parent )
		
		CopyTo( camera )
		
		Return camera
	End

	Protected
		
	Method OnCopy:Camera( parent:Entity ) Override
		
		Return New Camera( Self,parent )
	End
	
	Private
	
	Field _fov:Float
	
End

Class Light Extends Entity
	
	Method New( parent:Entity )
		
		Super.New( parent )
		
		SaveInitialState()
		
		Visible=True
	End

	Method New( light:Light,parent:Entity )
		
		Super.New( parent )
		
		SaveInitialState( light )
		
		Visible=True
	End

	Method Copy:Light( parent:Entity ) Override
		
		Local light:=OnCopy( parent )
		
		CopyTo( light )
		
		Return light
	End

	Protected
		
	Method OnCopy:Light( parent:Entity ) Override
		
		Return New Light( Self,parent )
	End
	
End

Class Model Extends Entity
	
	Method New( parent:Entity )
		
		Super.New( parent )
		
		Mesh=""
		
		SaveInitialState()
		
		Visible=True
	End
	
	Method New( model:Model,parent:Entity )
		
		Super.New( parent )
		
		Mesh=model.Mesh
		
		SaveInitialState( model )
		
		Visible=True
	End
	
	Property Mesh:String()
		
		Return _mesh
		
	Setter( mesh:String )
		
		_mesh=mesh
	End
	
	Function Load:Model( path:String,parent:Entity )
		
		Local model:=New Model( parent,True )
		
		model.Mesh="<"+path+">"
		
		If editing jsonifier.AddInstance( model,"Load",New Variant[]( path,parent ) )
		
		Return model
	End
	
	Method Copy:Model( parent:Entity ) Override
		
		Local model:=OnCopy( parent )
		
		CopyTo( model )
		
		Return model
	End

	Protected
		
	Method OnCopy:Model( parent:Entity ) Override
		
		Return New Model( Self,parent )
	End
	
	Private
	
	Field _mesh:String
	
	Method New( parent:Entity,loading:Bool )
		
		Super.New( parent )
	End

End

Function CreateScene()
	
	Print "CreateScene"

	jsonifier=New Jsonifier
	
	Local model1:=Model.Load( "model1.png",Null )
	
	Local behavour1:=New Behaviour( model1 )
	
	Local model2:=model1.Copy( Null )
	
End

Function CreateScene2()
	
	Print "CreateScene"

	jsonifier=New Jsonifier
	
	Local camera:=New Camera( Null )
	
	Local light:=New Light( Null )
	
	Local root:=Model.Load( "blah.txt",Null )
	
	For Local i:=0 Until 3
		
		Local model:=New Model( root )
		
		Local component:=New Behaviour( model )
	Next
	
	Local copy:=root.Copy( Null )
	
End

Function SaveScene:JsonObject()
	
	Print "SaveScene"

	Local jobj:=jsonifier.JsonifyInstances()
	
	Return jobj
End

Function LoadScene( jobj:JsonObject )
	
	Print "LoadScene"
	
	jsonifier=New Jsonifier
	
	jsonifier.DejsonifyInstances( jobj )
End

Function Main()
	
	CreateScene()
	
	Local saved1:=SaveScene()
	
	LoadScene( saved1 )
	
	Local saved2:=SaveScene()
	
	If CompareJson( saved1,saved2 )=0
		Print saved1.ToJson()+"~nSuccess!"
	Else
		Print "saved1:~n"+saved1.ToJson()+"~nsaved2:~n"+saved2.ToJson()+"~nError!"
	Endif
	
End
