
@manpage Modules and applications

### Modules and Applications

@#### Creating modules

A module consists of a sub-directory inside the top level '/modules/' directory, that contains a 'root' monkey2 file with the same name as the sub-directory and a 'module.json' file , eg:

```
/modules/my-module/
/modules/my-module/my-module.monkey2
/modules/my-module/module.json
```

Module names can contain any valid identifier or the `-` character. However, the `-` character cannot be used twice or more in succession, eg:

```
legal-module-name
illegal--module--name
```

Module names live in a 'flat' namespace so should be as unique as possible.

The 'module.json' file must contain a json object with the following fields:

* `"module"` : string - the name of the module. Must be the same as the directory name.
* `"author"` : string - the author of the module.
* `"version"` : string - the version of the module. This should be in number 'dot' number 'dot' number format, eg: `"1.0.0"`.
* `"depends"` : string array - All modules this module depends on. This will generally include all other modukes #imported by the module, eg: `["libc","std"]`.

A simple module.json file might look like this:

```
{
	"module" : "my-module",
	"version" : "1.0.0",
	"depends" : ["libc","std"]
}
```

To rebuild a module, use the mx2cc 'makemods' option, eg:

```
mx2cc makemods my-module
```

This will cause the root 'modules/my-module/my-module.monkey2' file to be built, along with any local files it imports.

You can also rebuild all modules with:

```
mx2cc makemods
```

This will use the "depends" information in the module.json files to determine the correct order to build the modules in.

Modules must not have cyclic dependancies.

Each module may also declare a single Main:Void() function that can be used to initialize the module.

This function is called *after* global variables (including global Consts) have been initialized but *before* the application's Main is called.

Since modules can't have cyclic dependencies, Mains will always execute in the correct order, eg: if module X imports module Y, then module Y's Main is guaranteed to be called before module X's.

You can use the `Internal` keyword at class or file scope to declare module internal accessibility. 

@#### Importing modules

Once built, a module can be imported into other modules using 'import', eg:

```
#Import "<my-module>"
```
 

@#### Applications

An application is really just a special type of module. It doesn't have to reside in the '/modules/' directory, can't be imported by other modules and produces executable files instead of archives, but is otherwise dealt with just like a module.

An application must declare a Main:Void() function. Actually, there's no difference between the Main declared in the app, and Mains declared in modules. Since the app depends on ALL modules, and NO modules depend on the app, the app's Main just happens to be the last one called.
