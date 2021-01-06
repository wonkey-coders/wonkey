
@manpage Multifile projects

### Multifile projects.

To add additional source files to a monkey2 project, you use the #Import directive. #Import can also be used to import other stuff into a project, but more on that late

\#Imports should appear at the top of a source file before any declarations occur. #Import takes one parameter – the path to the file to import. If the file is a '.monkey2' file, the extensions can be omitted, eg:


```
'file1.monkey2
'
#Import "file2"
#Import "file3"

Function Something()
End
```

The import path can be relative or absolute, and contain “../” etc, making it easy to get at source files located anywhere.

When you build a monkey2 app (or module), the compiler starts with a single ‘root’ monkey2 source file and searches for all other monkey2 files reachable – directly or indirectly – from that root file via #Import directives. All files found via #Import this way will ultimately be included in the project and built  by the compiler.

You only need to #Import a particular file once per project – duplicate #Imports of the same file are ignored by the compiler.

Code in any imported monkey2 file can use code in any other imported monkey2 file, regardless of whether or not the files #Import each other. For example:

```
'***** file1.monkey2 *****
'
#Import "file2"
#Import "file3"

Function Func1()
   Func1()
   Func2()
   Func3()
End

'***** file2.monkey2 *****

Function Func2()
   Func1()
   Func2()
   Func3()
End

'***** file3.monkey2 *****

Function Func3()
   Func1()
   Func2()
   Func3()
End
```

This is perfectly valid, as long as file1.monkey2 is the ‘root file’ you compile.

You may encapsulate some code within a file by using the `Private` keyword. That code will only be accessible within the file. The `Public` keyword allows you to go back to the default public privacy level.

```
'***** file1.monkey2 *****
'
#Import "file2"

Function Func1()
   Func1()
   Func2()
   Func3() 'this call is not valid, Func3 is private to file2.monkey!
   Func4()
End

'***** file2.monkey2 *****

Function Func2()
   Func1()
   Func3() 'here the call is valid
End

Private 'entering private declarations

Function Func3()
   'some statements
End

Public 'back to public declarations

Function Func4()
   'some statements
End

```
