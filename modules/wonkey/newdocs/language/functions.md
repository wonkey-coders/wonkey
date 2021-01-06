
@manpage Functions

### Functions

@#### Global functions

To declare a global function:

`Function` _Identifier_ [ _GenericParams_ ] [ `:` _ReturnType_ ] `(` _Parameters_ `)`
```
	...Statements...
```
`End`

_ReturnType_ defaults to `Void` if omitted.

_Parameters_ is a comma separated list of parameter declarations.


@#### Class methods

The syntax for declaring a class method is:

`Method` _Identifier_ [ _GenericParams_ ] [ `:` _ReturnType_ ] `(` _Parameters_ `)` [ `Virtual`|`Abstract|`Override``|`Final`|`Override Final` ]
```
	...Statements...
```
`End`

If a method is declared `Virtual` or `Abstract`, it can be overriden by methods in derived classes. Overriding methods must have the same return type and parameter types as the class method, and must be declared `Override`.

If a method is declared `Abstract`, no implementation may be provided (ie: no 'statements' or 'End'). Such a method must be overriden by a method in a derived class, and also makes its enclosing class implictly abstract (an abstract class cannot be instantiated).

If a method is declared `Override` or `Override Final`, it must override a virtual method in a base class.

If a method is declared `Final` or `Override Final`, it cannot be overriden by any methods in derived classes.

By default, class methods are final.


@#### Lambda functions

To declare a lambda function:

...`Lambda` [ `:` _ReturnType_ `]` `(` _Parameters_ `)`
```
	...Statements...
```
`End`...

Lambda declarations must appear within an expression, and therefore should not start on a new line.

For example:

```
Local myLambda:=Lambda()
   Print "My Lambda!"
End

myLambda()
```

To pass a lambda to a function:

```
SomeFunc( Lambda()
   Print "MyLambda"
End )
```

Note the closing `)` after the `End` to match the opening `(` after `SomeFunc`.


@#### Function values

Monkey2 supports 'first class' functions.

This means function 'values' can be stored in variables and arrays, passed to other functions and returned from functions.
