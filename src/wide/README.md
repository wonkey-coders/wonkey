# Wide (Wonkey IDE)
An IDE for Wonkey programming language.

## Benefits & Goals
* Autocompletion for keywords, modules and user's code (WIP).
* On-the-fly parser - see errors w/o build (not all errors).
* "Find in project" dialog.
* CodeTree and NavigationList for comfortable code jumping (todo).
* Code folding and bookmarks (todo).
* Doc's hints directly inside of code area (todo).

## More info
 Github page: https://github.com/wonkey-coders

Discord channel : https://discord.gg/ZHpRAFp

## Notes for contributors
Please, take a look at code style. It based on original Ted2Go.

Will be super-cool if you can write the same style to make this project consistent.

`Local abc:="ABC"` ' there is no spaces in assignment

`digit=8`

`callSomeMethod( param1,param2 )` 'there are spaces in bracket bounds

```
Method check:Bool( value:Double ) 'spaces in declaration
                          ' empty line after method name (can ignore if there is one-line body)
   Return value > 1.75
End
```
