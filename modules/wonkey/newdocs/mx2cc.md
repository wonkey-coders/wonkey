
@manpage The mx2cc compiler

# The mx2cc compiler

Mx2cc is the command line compiler for monkey2. The actual executable is named differently depending on the OS:

* Windows: /bin/mx2cc_windows.exe  
* MacOS: /bin/mx2cc_macos  
* Linux: /bin/mx2cc_linux  

The command line options for mx2cc are:

<div class=syntax>
`mx2cc` _command_ _options_ _input_
</div>

Valid commands are:

* `makeapp` - make an app. _input_ should be a monkey2 file path.
* `makemods` - make a set of modules. _input_ should be a space separated list of module names, or nothing to make all modules.
* `makedocs` - make the documentation for a set of modules. _input_ should be a space separated list of module names, or nothing to make all modules.

Valid options are:

* `clean` - rebuilds everything from scratch.
* `verbose` - provides more information while building.
* `target=`_target_ - set target to `desktop` (the default) or `windows`, `macos`, `linux`, `emscripten`, `wasm`, `android`, `ios`. `desktop` is an alias for current host.
* `config=`_config_ - set config to `debug` (the default) or `release`.
* `apptype=`_apptype_ set apptype to `gui` (the default) or `console`.

