
@manpage Preprocessor directives and symbols

#Preprocessor directive and symbols


This section list the directives and symbols that can be used with the [[preprocessor|preprocessor]].


@### Preprocessor directives


@#### #If

The `#If` directive allows you to conditionally execute a block of statements depending on the result of a series of boolean expressions.


@#### #Else if

To be combined with #if


@#### #Else

To be combined with #if


@#### #EndIf

Ends an #if


@#### #Rem

Used to for multiline comments


@#### #End

Ends an #if or #rem


@#### #Import

Used to import modules, code or assets.

See [[modules-and-applications|Modules and applications]] and [[asset-management|Asset management]].


@### Preprocessor symbols

@#### \_\_TARGET\_\_

The \_\_TARGET\_\_ symbol is set to the current build target and will be one of the following values: “windows”, “macos”, “linux”, “emscripten”, “android” or “ios” – ie: the precise build target.


@#### \_\_CONFIG\_\_

The \_\_CONFIG\_\_ symbol is set to the current build config and will be set to either "debug" or "release".

@#### \_\_ARCH\_\_

The \_\_ARCH\_\_ symbol is set to the current build architecture and will be set to either "x86" or "x64".

@#### \_\_COMPILER\_\_

The \_\_COMPILER\_\_ symbol is set to the current build tool-chain and will be set to either "gcc" or "msvc" (on Windows only).


@#### \_\_DESKTOP\_TARGET\_\_

True if the current build target is desktop (“windows”, “macos” or “linux”), false otherwise.


@#### \_\_MOBILE\_TARGET\_\_

True if the current build target is mobile (“android” or “ios”), false otherwise.


@#### \_\_WEB\_TARGET\_\_

True if the current build target is web (“emscripten”), false otherwise.


@#### \_\_DEBUG\_\_

True if the current build config is "debug", false otherwise.


@#### \_\_RELEASE\_\_

True if the current build config is "release", false otherwsie.


@#### \_\_MAKEDOCS\_\_

True if mx2cc is currently making docs, false otherwise.
