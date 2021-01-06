
@manpage Reflection

### Reflection

To use reflection in your code, you first need to import the reflection module.

```
#Import "<reflection>"
```

@#### Typeof and TypeInfo

The Typeof operator return a TypeInfo object, that contains various properties and methods for inspecting types at runtime. There are 2 ways to use Typeof:

```
Local type:=Typeof( expression )
Local type:=Typeof< type >
```

The use of seperate () and <> delimeters is to prevent the parser getting confused by complex expressions.

TypeInfo objects have a To:String operator (mainly for debugging) so can be printed directly:

```
Print Typeof<Int>
Print Typeof<Int Ptr>
Local t:=10
Print Typeof( t )
Print Typeof( "yes" )
```

Typeof returns the 'static' type of a class object. To get the actual instance type, use the Object.InstanceType property:

```
Class C
End

Class D Extends C
End

Function Main()
	Local c:C=new D
	Print Typeof( c )		'Class default.C
	Print c.InstanceType	'Class default.D
End
```

You can retrieve the type of the value contained in a variant using the Variant.Type property:

```
Local v:=Variant( 10 )	'creates a variant containing an int.
Print v.Type			'prints 'Int'
```

TypeInfo also includes functions for inspecting all user defined types:

`Function TypeInfo.GetType( name:String )`

Returns the TypeInfo for a named type. A named type is a namespace or class declared by your app - it does not include primitive types, pointer types, array types etc. Class names must be prefixed by the namespace they are declared in.

To get an array of ALL named types:

`Function TypeInfo.GetTypes:TypeInfo[]()`


@#### DeclInfo objects

TypeInfo objects for namespaces and classes also contain a set of DeclInfo objects. A DeclInfo represents the member declarations inside of a namespace or class. Currently, only global, field, method and function members are supported. DeclInfo objects also have a To:String operator to help with debugging.

You can inspect the member decls of a type using the TypeInfo.GetDecls method:

```
Namespace mynamespace

Global test:Int

Function Main()

	Local type:=TypeInfo.GetType( "mynamespace.MyClass" )

	For Local decl:=Eachin type.GetDecls()
		Print decl
	Next
End
```

You can retrieve a single unique member using TypeInfo.GetDecl:

```
Local type:=TypeInfo.GetType( "mynamespace.MyClass" )

Local ctor:=type.GetDecl( "New" )
```

There may be several decls with the same name due to method and function overloading, in which case the simple GetDecl above will fail and return null. In this case, you either need to inspect each decl individually to find the one you want, or you can pass an additional TypeInfo parameter to GetDecl:

```
Local type:=TypeInfo.GetType( "MyNamespace.MyClass" )

Local ctor:=type.GetDecl( "New",Typeof<Void()> )
```

This will return the default constructor for MyClass, assuming there is one.


@#### Getting and setting variables

Member decls that represent variables (ie: fields and globals) can be read and written using the DeclInfo.Get and Decl.Info.Set methods:

```
Namespace mynamespace

Global MyGlobal:Int

Function Main()

	Local vdecl:=TypeInfo.GetType( "mynamespace" ).GetDecl( "MyGlobal" )

	vdecl.Set( Null,10 )

	Print MyGlobal

	Print Cast<Int>( vdecl.Get( Null ) )
End
```

The first parameter of Set and Get is an object instance, which must be non-null for getting and setting fields.

The second parameter of Set is a variant, and is the value to assign to the variable. The type of the value contained in the variant must match the variable type exactly, or a runtime error will occur.

Note that since any value can be cast to a variant, we can just provide the literal value '10' for Set and it will be implictly converted to a variant for us. On the other hand, we must explicitly cast the result of Get() from a variant back to the type of value we want.


@#### Invoking methods and functions

To invoke methods and functions, use the DeclInfo.Invoke method:

```
namespace mynamespace

Function Test( msg:String )

	Print "Test! msg="+msg
End

Function Main()

	Local fdecl:=TypeInfo.GetType( "mynamespace" ).GetDecl( "Test" )

	fdecl.Invoke( Null,New Variant[]( "Hello Test!" ) )
End
```

The first parameter of Invoke is an object instance, which must be non-null for invoking methods.

The second parameter of Invoke is an array of variants that represents the parameters for the call. The types of these parameters must match the parameter types of the actual method or function exactly, or a runtime error will occur.


@#### Limitations

Currently, typeinfo is only generated for non-generic, non-extension, non-extern 100% pure monkey2 globals, fields, function, methods, classes and namespaces. You can still use other types (structs etc) with variants etc, but you wont be able to inspect their members.

Typeinfo may be stripped out by the linker. I've added a little hack to mojo to keep module typeinfo 'alive', but there is still work to do here. If you find the linker stripping out typeinfo, you can prevent it doing so for now by adding a 'Typeof' to Main() referencing the type you want to keep alive. Or, you can set MX2_WHOLE_ARCHIVE in bin/env_blah.txt to '1' to force the linker to include ALL code, but this will of course produce larger executables.
