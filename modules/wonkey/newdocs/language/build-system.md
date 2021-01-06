
@manpage Build System

### The build system

Monkey2 includes  a simple build system that converts monkey2 files to C++, compiles the C++ code, and links the resultant object files.

The build system also allows you to import several types of non-monkey2 files into a project for compilation and/or linking. This is done using a system import directive:

`#Import` `"<`_system\_file_`>"`

...or or a local import directive:

`#Import `"_local\_file_"`

Import directives can appear any where in a monkey2 source file, but it's generally tidiest if they are placed at the top of the file.


@#### System Imports

System files are files that are generally provided with the compiler toolset, and that the compiler and/or linker are configured to find automatically. Monkey2 recognizes the following system file types:

| System file type suffix	| System file type
|:--------------------------|:----------------
| .o, .obj, .a, .lib		| Static library.
| .so, .dll, .dylib			| Dynamic library.
| .framework				| MacOS framework.
| .h, .hh, .hpp				| C/C++/Objective C header.
| .monkey2					| Monkey2 module.

Note that system file names are enclosed by `<` and `>` characters, while local file names are not.

An example of importing a system library:

`#Import "<wsock32.a>"`

If no extension is provided for a system import, Monkey2 will assume you are importing a monkey2 module, eg:

`#Import "<std>"`

This will import the monkey2 'std' module. This is effectively the same as:

`#Import "<std.monkey2>"`


@#### Local Imports

Local files are files that are located relative to the monkey2 file that imports them.

Monkey2 recognizes the following local file types:

| Local file type suffix		| Local file type
|:------------------------------|:---------------
| .o, .obj						| Object file.
| .a, .lib						| Static library.
| .so, .dll, .dylib				| Dynamic library.
| .framework					| MacOS framework.
| .exe							| Windows executable.
| .c, .cc, .cxx, .cpp, .m, .mm	| C/C++/Objective C source code.
| .h, .hh, .hpp					| C/C++/Objective C header.
| .monkey2						| Monkey2 source code.

It is also possible to add local 'include directories', 'library directories' and 'framework directories' with import. This is done using syntax similar to a local import, but replacing the filename with a wildcard.

For example, to add an include directory:

`#Import "`_include\_directory_`/*.h"`

This will allow you to import any header file inside 'include\_directory' using...

`#Import "<`_include\_file_`>"`

...without having to specify the full path of the file.

To add a library directory:

`#Import "`_staticlib\_directory_`/*.a"`

To add a MacOS framework directory:

`#Import "`_framework\_directory_`"/*.framework"`
