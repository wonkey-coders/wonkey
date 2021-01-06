
@manpage Native code

### Integration with native code

In order to allow monkey2 code access to native code, monkey2 provides the 'extern' directive.

Extern begins an 'extern block' and must appear at file scope. Extern cannot be used inside a class or function. An extern block is ended by a plain 'public' or 'private' directive.

Declarations that appear inside an extern block describe the monkey2 interface to native code. Therefore, functions and methods that appear inside an extern block cannot have any implementation code, as they are already implemented natively.

Otherwise, declarations inside an extern block are very similar to normal monkey2 declarations, eg:

```
Extern

Struct S
   Field x:Int
   Field y:Int
   
   Method Update()   'note: no code here - it's already written.
   Method Render()   'ditto...
End

Global Counter:Int

Function DoSomething( x:int,y:Int )
```

You can declare the following inside extern blocks:

* Consts

* Globals

* Structs

* Classes

* Functions


You cannot declare the following inside extern blocks:

* Generic functions or types

* Operator methods


@#### Extern symbols

By default, monkey2 will use the name of an extern declaration as its 'symbol'. That is, when monkey2 code that refers to an extern declaration is compiled, it will use the name of the declaration directly in the generated output code.

You can modify this behaviour by providing an 'extern symbol' immediately after the declarations type, eg:

```
Extern

Global Player:Actor="mylib::Player"

Class Actor="mylib::Actor"
	Method Update()
	Method Render()
	Function Clear()="mylib::Actor::Clear"
End
```

@#### Extern classes

Extern classes are assumed by default to be *real* monkey2 classes - that is, they must extend the native bbObject class. 

However, you can override this by declaring an extern class that extends `Void`. Objects of such a class are said to be native objects and differ from normal monkey object in several ways:

* A native object is not memory managed in any way. It is up to you to 'delete' or otherwise destroy it.

* A native object has no runtime type information, so it cannot be downcast using the `Cast<>` operator.
