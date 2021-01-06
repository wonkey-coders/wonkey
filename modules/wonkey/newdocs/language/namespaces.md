
@manpage Namespaces

### Namespaces

All identifiers declared in a monkey2 program file end up inside a 'namespace'. Namespaces are hierarchical, so in addition to identifiers declared by monkey2 code, namespaces can also contain other namespaces.

@#### Declaring namespaces

You control which namespace the identifiers declared in a monkey2 file go with the namespace directive:

`Namespace` _namespace-path_

This directive must appear at the top of the program file, before any actual declarations are made.

A namespace path is a 'dot' separated sequence of identifiers, eg:

`monkey.types`
`std.collections`

The 'dot' separator indicates the namespace hierarchy, eg: `monkey.types` is a 'child' or 'inner' namespace of `monkey`.

If no namespace is specified in a program file, the identifiers go into a default namespace. This is not recommended though, as the default namespace has no name - so anything inside the default namespace cannot be 'seen' by anything outside.

@#### Accessing namespaces

Code can access an identifier in a namespace by prefixing the identifier with the namespace path, eg:

`Local list:=New std.collections.List<Int>`

Here, `std.collections` refers to a namespace, while `List` is an identifier inside  the `std.collections` namespace.

Code inside a particular namespace does not have to use a namespace prefix to find identifiers in the same namespace or in any parent namespace, although it can still do so, eg:

```
Namespace testing

Function Test()
End

Function Main()
	Test()				'works fine...
	testing.Test()		'also works...
End
```

@#### The Using directive

To make it easier to deal with long or complex namespace paths, the using directive provides a way to add namespace 'search paths' for locating identifiers. The using directive looks like this:

`Using` _namespace-path_

A program can have multiple using directives. Using directives must appear at the top of the program file before any program declarations.

Each using directive adds a namespace to a set of 'search paths' that is used to resolve any unknown identifiers in the program code, eg:

```
#Import "<std>"

Using std.collections
 
Function Main()
	Local list:=New List<Int>
End
```

Without the using directive, this program would fail to compile because the `List` identifier cannot be found.

However, the using direct tells the compiler look for `List` in the `std.collections` namespace, where it is successfully located.

If you have multiple using directives and an identifier is found in more than one namespace, you will still get a compile error. In this case, you will need to 'fully qualify' the identifier by prefixing it with the correct namespace path.

Some modules declare many namespaces, and it can often be difficult to remember where everything is. To deal with this, Monkey2 provides a convenient 'double dot' form of Using that will use both a namespace AND all namespaces contained in that namespace. For example:

```
Using std..
```

The double dots must appear at the end of the using.

This will use the std namespace, and the std.collections, std.filesystem etc namespaces too. This works recursively, so any namespaces inside std.collections and std.filesystem are also used.

This can of course lead to more 'duplicate identifier' clashes but is none-the-less very convenient.
