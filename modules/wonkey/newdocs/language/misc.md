
@manpage Miscellaneous

### Miscellaneous

@#### Inline Code comments

Inline comments can be done with the `'` character.
```
Print "hello!" 'this line prints hello! on the output console
```

Multiline comments can be made with the `#Rem` preprocessor. See [[language-reference.preprocessor|preprocessor]]

@#### Line breaks in code

Lines can currently only be split after ‘[‘, ‘(‘ or ‘,’ tokens and operators.

```
Local integer := 1 +
                 2 *
                 3 /
                 4 -
                 5 Mod
                 6

    Local l := "line 1~q"+
               "line 2~q"+
               "line 3~q"+
               "line 4~q"

    Local flag := mojo.app.WindowFlags.Resizable |
                  mojo.app.WindowFlags.HighDPI   |
                  mojo.app.WindowFlags.Center

    If 5 =
           5 Or
                1 <
                    2 And
                          3 >
                              4 Then Print "okay"
```

@#### Print

Writes a String or a numeric value to the output console.

```
Print "Hello world" 'printing a String
Print myFloat 'printing a Float
```

@#### $ Hexadecimal

Hexadecimal numbers can be entered using the $ symbol
```
Local i:=$A0F
```

@#### File privacy levels

Privacy levels can be set at file scope:

-`Public` can be accessed from anywhere. It is the default level.

-`Private` can be accessed within the file only.

-`Internal` can be accessed from the same module only.

