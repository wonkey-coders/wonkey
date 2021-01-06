
@manpage User defined types

### User defined types

@#### Classes

A class is a kind of 'blueprint' for creating objects at runtime.

The syntax for declaring a class is:

<div class=syntax>
`Class` _Identifier_ [ `<` _GenericTypeIdents_ `>` ] [ `Extends` _SuperClass_ ] [ `Implements` _Interfaces_ ] [ _Modifier_ ]  
	...Class Members...
`End`
</div>

_SuperClass_ defaults to `Object` if omitted.

_Interfaces_ is a comma separated list of interface types.

_Modifier_ can be one of:

* `Abstract` - class cannot be instantiated with 'New', it must be extended.
* `Final` - class cannot be extended.

Classes can contain const, global, field, method and function declarations, as well as other user defined types.

Once you have declared a class, you can create objects (or 'instances') of that class at runtime using the `New` operator.

Classes are 'reference types', meaning that class instances are really just a 'handle' or 'pointer' to the actual class data.


@#### Structs

Structs are similar classes, but differ in several important ways:

* A struct is a 'value type', whereas a class is a 'reference type'. This means that when you assign a struct to a variable, pass a struct to a function or return a struct from a function, the entire struct is copied in the process.

* Stucts are statically typed, whereas classes are dynamically typed.

* Struct methods cannot be virtual.

* A struct cannot extend anything.

To declare a struct:

<div class=syntax>
`Struct` _Identifier_ [ `<` _GenericTypeIdents_ `>` ]
	...Struct members...
`End`
</div>

A struct can contain const, global, field, method and function declaratins, as well as other user defined types.


@#### Interfaces

To declare an interface:

<div class=syntax>
`Interface` _Identifier_ [ `<` _GenericTypeIdents_ `>` ] [ `Extends` _Interfaces_ ]
	...Interface members...
`End`
</div>

_Interfaces_ is a comma separated list of interface types.

An interface can contain consts, globals, methods, functions, properties and other user defined types.

Interface methods are always 'abstract' and cannot declare any code.

Example for using properties in an interface:
```
Interface IExample

	' Property with Setter
	Property IntProp1( a:Int )

	' Property with Getter
	Property IntProp2:Int()

	' Property with Setter + Getter
	Property IntProp3:Int()
	Setter( a:Int )

End
```


@#### Fields

Fields are variables that live inside the memory allocated for an instance of a class or struct. To declare a field variable:

<div class=syntax>
`Field` _identifier_ `:` _Type_ [ `=` _Expression_ ]
</div>

...or...

<div class=syntax>
`Field` _identifier_ `:=` _Expression_
</div>

For struct fields, _Expression_ must not contain any code that has side effects.


@#### Methods

To declare a method:

<div class=syntax>
`Method` _Identifier_ [ `<` _GenericTypeIdents_ `>` ] [ `:` _ReturnType_ ] `(` _Arguments_ `)` [ _Modifiers_ ]
	...Statements...
`End`
</div>

_ReturnType_ defaults to `Void` if omitted.

_Arguments_ is a comma separated list of parameter declarations.

_Modifiers_ can only be used with class methods, and can be one of:

* `Abstract` - method is abstract and has no statements block or `End` terminator. Any class with an abstract method is implicitly abstract.
* `Virtual` - method is virtual and can be dynamically overridden by a subclass method.
* `Override` - method is virtual and overrides a super class or interface method.
* `Override Final` - method is virtual, overrides a super class or interace method and cannot be overridden by subclasses.
* `Final` - method is non-virtual and cannot be overridden by a subclass method.  

Methods are 'Final' by default.


@#### Properties

To declare a read/write property:

<div class=syntax>
`Property` _Identifier_ `:` _Type_ `()`
	...getter code...
`Setter` `(` _Identifier_ `:` _Type_ `)`
	...setter code...
`End`
</div>

To declare a read only property:

<div class=syntax>
`Property` _Identifier_ `:` _Type_ `()`
	...getter code...
`End`
</div>

To declare a write only property:

<div class=syntax>
`Property` `(` _Identifier_ `:` _Type_ `)`
	...setter code...
`End`
</div>

@#### Conversion Operators

You can also add 'conversion operators' to classes and structs. These allow you to convert from a custom class or struct type to an unrelated type, such as another class or struct type, or a primitive type such as String.

The syntax for declaring a conversion operator is:

<div class=syntax>
`Operator To` [ `<` GenericTypeIdents `>` ] `:` _Type_ `()`
	...Statements...
`End`
</div>

Conversion operators cannot be used to convert a class type to a base class type, or from any type to bool.

For example, we can add a string conversion operator to a class like this:

```
Struct Vec2

	Field x:Float
	Field y:Float

	Method New( x:Float,y:Float )
		Self.x=x
		Self.y=y
	End

	Method ToString:String()
		Return "Vec2("+x+","+y+")"
	End

	' The string conversion operator
	Operator To:String()
		Return "Vec2("+x+","+y+")"
	End
End
```

This will allow Vec2 values to be implictly converted to strings where possible, for example:

```
Local v:=New Vec2

Print v
```

We no longer need to use '.ToString()' when printing the string. Since Print() takes a string argument, and Vec2 has a conversion operator that returns a string, the conversion operator is automatically called for you.

@#### Extensions

Extensions allow you to add extra methods and functions to existing classes or structs. Fields cannot be added this way. Private members cannot be accessed by extensions.
```
Struct Foo
	Field i:Int=0
End
```
```
Struct Foo Extension
	Method Increment()
		i+=1
	End
End
```

@#### Encapsulation

There are three levels of encapsulation for class and struct members:

-`Public` members can be accessed from anywhere. It is the default encapsulation level.

-`Protected` members can only be accessed by the base class and the derived ones or by class/struct extensions. Code existing in the same source file have acces to `Protected` members too.

-`Private` members can only be accessed by the base class. Code existing in the same source file have acces to `Private` members too.

There is also the `Internal` privacy level, used to declare module internal accessibility.

example:
```
Class Foo
	'public by default'
	Field i:Int

	Protected

	Field someProtectedThing:Int
	Method doSomething()
		Print "Doing something"
	End

	Private

	Field _somePrivateThing:String
End
```

@#### Alias

An `Alias` allows you to create a synonym for a previously declared type.

<div class=syntax>
`Alias` _Identifier_ `:` _Type_
</div>

<br>
You can use your newly declared `Alias` instead of the original type anywhere in your code. For example:


```
Alias FantasticNumber:Int
Alias FantasticString:String

Local myInt:FantasticNumber = 123
Local myString:FantasticString = "abc"
```
