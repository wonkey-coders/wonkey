
@manpage Preprocessor

### Preprocessor

Monkey2 includes a simple preprocessor that allows you to conditionally compile code depending on a number of build setttings.

The preprocessor supports the following statements: #If, #Else, #ElseIf, #EndIf, #Rem, #End. Preprocessor statements must begin on a new line.

Preprocessor expressions may only use the 'And', 'Or' and comparison operators.

The following symbols may be used in preprocessor expressions:

| Symbol			| Type		| Meaning
|:----------------------|:------|:--------------------------------------------:
| \_\_TARGET\_\_			| String	| The current build target. One of: "windows", "macos", "linux", "android", "ios", "emscripten"
| \_\_ARCH\_\_			| String	| The current build architecture. One of: "x86", "x64"
| \_\_CONFIG\_\_			| String	| The current build config. One of: "release", "debug"
| \_\_COMPILER\_\_			| String	| The current build tool-chain. One of: "gcc", "msvc"
| \_\_DESKTOP\_TARGET\_\_	| Bool		| True if the current build target is windows, macos or linux.
| \_\_MOBILE\_TARGET\_\_	| Bool		| True if the current build target is android or ios.
| \_\_WEB\_TARGET\_\_		| Bool		| True if the current build target is emscripten.
| \_\_DEBUG\_\_			| Bool		| True if the current build config is debug.
| \_\_RELEASE\_\_		| Bool		| True if the current build config is release.

For example, to include code in debug builds only, use something like:

```
#If __DEBUG__
Print "This code is only included in debug builds."
#Endif
```

To include code on desktop or mobile builds, use:

```
#If __DESKTOP_TARGET__ Or __MOBILE_TARGET__
Print "This code is only include in desktop and mobile builds."
#Endif
```
