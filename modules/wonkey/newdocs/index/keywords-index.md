
@manpage Keywords

@#### Abstract

Used while declaring classes: class cannot be instantiated with `New`, it must be extended.

See [[user-defined-types.classes|Classes]].


@#### Alias

Used for convenience types. For example `Vec2i` is a convenience type alias for `Vec2<Int>`.

Used to import extern typedefs too.

See [[user-defined-types.alias|Alias]].


@#### Array

`Array` is not currently used but is reserved for future use.

See [[language-reference.arrays|Arrays]].


@#### Case

To be combined with with the `Select` statement.

See [[conditional-statements.select|Select]].


@#### Cast

Allows you to cast custom pointers.

See [[built-in-types.explicit-type-conversions|explicit type conversions]] and [[expressions.operators|operators]] and [[pointers.casting|Pointers]].


@#### Catch

The `Catch` keyword is part of the Try/Catch exception-handling construct.

See [[error-handling.exceptions|exceptions]].


@#### Class

Marks the start of a class object definition.

See [[user-defined-types.classes|Classes]].


@#### Const

Allows you to declare a constant.

See [[variables.consts|Consts]].


@#### Continue

Used to skip a loop.

See [[loop-statements.continue|Continue]].


@#### CString

C style String for external C/C++ parameters. `String` is implicitly converted to `CString` for convenience.


@#### Default

Marks the start of the default code block of a `Select` statement.

See [[conditional-statements.select|Select]].


@#### Delete

`Delete` is reserved for future use.


@#### Eachin

Allows you to use `For` loop with collections.

See [[loop-statements.for-eachin|For Eachin]].


@#### Else

To be combined with the `If` statement.

See [[conditional-statements.if|If]].


@#### Elseif

To be combined with the `If` statement.

See [[conditional-statements.if|If]].


@#### End

Ends a declaration or statment block.


@#### Endif

Ends `If` statement.

See [[conditional-statements.if|If]].


@#### Enum

32 Bit integer Enumerated Type.

See [[enums|Enums]].

@#### Exit

Used to terminate a loop.

See [[loop-statements.exit|Exit]].


@#### Extends

Used for class declaration.

See [[user-defined-types.classes|Classes]].


@#### Extension

Used to add some features to an existing user defined type without inheritance.

See [[user-defined-types.extensions|Extensions]].


@#### Extern

Marks the start of definitions for C/C++ imports.

See [[native-code|native code]].


@#### False

Boolean False value


@#### Field

Fields are variables that live inside the memory allocated for an instance of a class or struct.

See [[user-defined-types.classes|Classes]].


@#### Final

Methods declared as `Final` are non-virtual and cannot be overridden by a subclass method.

See [[user-defined-types.classes|Classes]].


@#### For

Marks the start of a `For` loop

See [[loop-statements.for|For]].


@#### Forever

Used at the end of a `Repeat` loop. The loop will loop forever unless `Exit` is called.

See [[loop-statements.repeat|Repeat]].


@#### Friend

`Friend` is reserved for future use.


@#### Function

Used to declare a function within a struct, a class or at global scope.

See [[functions|Functions]].


@#### Getter

Used to declare the getter for a property.

See [[user-defined-types.properties|Properties]].


@#### Global

Global variables live in global memory and exist for the lifetime of the application.

See [[variables.global-variables|global variables]].


@#### If

The `If` statement allows you to conditionally execute a block of statements depending on the result of a series of boolean expressions.

See [[conditional-statements.if|If]].


@#### Implements

Used to declare classes implementing an interface.
`Implements` can also be combined with `where` to check generics type constrain.

See [[user-defined-types.interfaces|Interfaces]].


@#### Import

Assets and code files can be imported with 'Import'

See [[modules-and-applications.importing-modules|Importing modules]].


@#### Inline

`Inline` is reserved for future use.


@#### Interface

Interfaces are Class models definition. It's a pure abstract object to be implemented by a `Class`.

See [[user-defined-types.interfaces|Interfaces]].


@#### Internal

`Internal` may appear at file or class scope and is used to declare module internal accessibility.


@#### Lambda

A lambda function is a special type of function that can be declared in the middle of an expression.

See [[functions.lambda-functions|Lambda function]].


@#### Local

Local variables live on the stack. They are lost once their scope is exited.

See [[variables.local-variables|Local variables]].


@#### Method

A Method is special type of function associated with a Class or a Struct. It can acces the object fields.

See [[user-defined-types.methods|Methods]].


@#### Namespace

All identifiers declared in a monkey2 program file end up inside a 'namespace'.

See [[namespaces.declaring-namespaces|Declaring namespaces]].


@#### New

`New` calls a Class, Struct or Array constructor. It must be called before using a Class or an Array. It is advised to call it before using a struct.


@#### Next

Used at the end of a `For` loop.

See [[loop-statements.for|For]].


@#### Operator

`Operator` is used to declare special methods using a set of available expressions (+,-,/,<>,...)

See [[expressions.operator-overloading|Operator overloading]].


@#### Override

Used to override a virtual method when declaring a sub-class.

See [[user-defined-types.classes|Classes]].


@#### Print

Prints a String or a numeric value to the output console.


@#### Private

Sets the acces control of a Class or Struct members to "Private". Private members can only be accessed by the original class OR by any code within the same .monkey2 file.

See [[user-defined-types.encapsulation|Encapsulation]].


@#### Property

Property is a special type of field that may include some getter/setter additionnal code if desired.

See [[user-defined-types.properties|Properties]].


@#### Protected

Sets the acces control of a Class or Struct members to "Protected". Protected members can only be accessed by the original class and subclasses OR by any code within the same .monkey2 file.

See [[user-defined-types.encapsulation|Encapsulation]].


@#### Protocol

`Protocol` is reserved for future use.


@#### Ptr

Used to declare pointers.

See [[pointers.declarations|Pointers]]


@#### Public

Sets the acces control of a Class or Struct members to "Public". Public members can be accessed from anywhere. It's the default level.

See [[user-defined-types.encapsulation|Encapsulation]].


@#### Repeat

Used to start a `Repeat` loop

See [[loop-statements.repeat|Repeat]].


@#### Return

Used to end and return the expected value of a `Function`, `Method` or `Operator`


@#### Select

The Select statement allows you to execute a block of statements depending on a series of comparisons. `Select` combines with `Case` and `Default`

See [[conditional-statements.select|Select]].


@#### Setter

Marks the start of a Property setter definition.

See [[user-defined-types.properties|Properties]].


@#### Static

`Static` is reserved for future use.


@#### Step

Defines the incrementation step for `Next` loops.

See [[loop-statements.for|For]].


@#### Struct

Used to declare a `Struct`

See [[user-defined-types.structs|Structs]].


@#### Then

Facultative keyword used in combination with the `If` keyword.


@#### Throw

The `Throw` keyword is part of the Try/Catch exception-handling construct.

See [[error-handling.exceptions|exceptions]].


@#### Throwable

The Throwable class must be extended by all classes that are intended to be used with `Throw`.

See [[error-handling.exceptions|exceptions]].


@#### To

Defines range of values to be assigned to the index variable in a For/Next loop.

See [[loop-statements.for|For]].


@#### Try

Declares the start of a Try/Catch block.

See [[error-handling.exceptions|exceptions]].


@#### TypeInfo

Returns the type of a variable/object.

See [[reflection.typeof-and-typeinfo|Typeof and TypeInfo]].


@#### Until

Marks the end of a Repeat/Until loop. The `Until` keyword is also found as a modifier in For/Next loops.

See [[loop-statements.repeat|Repeat]].


@#### Using

The `Using` directive provides a way to add namespace 'search paths' for locating identifiers.

See [[namespaces.accessing-namespaces|Accessing namespaces]].


@#### Var

`Var` is reserved for future use.


@#### Variant

The `Variant` type is a primitive type that can be used to 'box' values of any type.

See [[variants|Variants]].


@#### Varptr

`Varptr` is used to reference pointers.

See [[pointers.referencing|Pointers]].


@#### Virtual

A virtual method is a method that can be overriden.

See [[user-defined-types.methods|Methods]].


@#### Wend

Wend, short for While [loop] End, marks the end of a While loop.

See [[loop-statements.while|While]].


@#### Where

`Where` allows generic type constrains.


@#### While

Marks the start of a While loop.

See [[loop-statements.while|While]].
