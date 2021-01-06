
@manpage Namespaces and using.

### Namespaces and using.

Monkey2 provides simple support for namespaces.

Each file can have a Namespace directive at the top that specifies the ‘scope’ of all the declarations (functions, globals, classes etc) in the file. For example:

```
'***** file1.monkey2 *****
'
Namespace myapp 'declare namesapce
 
Global SomeGlobal:Int
 
Function SomeFunction()
End
```

The ‘namespace myapp’ at the top here means that the SomeGlobal and SomeFunction declarations end up in the ‘myapp’ namespace. If you don’t have a Namespace at the top of a source file, a ‘default’ namespace is used. It is recommended that you use Namespace for all substantial projects though.

To access stuff declared in a namespace, use the ‘.’ operator. For example, you can access the SomeGlobal variable above using myapp.SomeGlobal.

However, you don’t need to do this if the declaration being accessed is in the same namespace (or a ‘parent’ namespace…see below) as the code doing the accessing. For example, any code within the above file can use SomeGlobal and SomeFunction without the need for  a ‘myapp.’ prefix, as that code is also in the myapp namespace.

This also applies to multifile projects. If 2 separate monkey2 files are in the same namespace, then they can freely access each other declarations without the need for a namespace prefix.

You can almost think of namespace as simple classes – albeit classes that can’t be new’d so can’t have fields or methods. The name of the class provides a ‘scope’ for the globals and functions declared in the class, and declarations with the class can directly access other declarations in the same class.

Namespaces are also hierarchical. While ‘Namespace myapp’ creates a simple ‘top level’ namespace, it’s also possible to create child namespaces using ‘.’. For example ‘Namespace myapp.utils’ referes to a ‘utils’ namespace within the top level ‘myapp’ namespace.

Finally, the Using directive can make it easier to access frequently used declarations inside a namespace. For example, the ChangeDir and CurrentDir functions are declared in the ‘std.filesystem’ namespace, but (depending on your self discipline level) it can be a hassle having to use std.filesystem.ChangeDir and std.filesystem.CurrentDir all the time.

To help out here, the ‘Using’ directive can be used to instruct the compiler to search a particular namespace for identifiers that it can’t normally find. For example:

```
Namespace myapp
 
Using std.filesystem
 
Function Main()
   ChangeDir( ".." )
   Print CurrentDir()
End
```

Without the Using declaration in the above code, you would need to use std.filesystem.ChangeDir and std.filesystem.CurrentDir.

You can have multiple Usings in an app, and Usings must appear at the top of a file, before any declarations.

The namespace specified in a Using must be ‘absolute’. That is, the namespace of the file is not taken into account when resolving the Using namespace.
