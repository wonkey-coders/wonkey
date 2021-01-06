
@manpage Asset management

### Asset management

Monkey2 provides a simple system for managing assets. This allows you to import and use images, files, fonts, and sounds in a consistent way, regardless of the target platform you are deploying to.

For the following examples, assume a project folder structure like this:

```
main.monkey2
images/image1.png
images/image2.png
sounds/sound1.wav
sounds/sound2.wav
```

@#### Importing Assets

Import assets for use in your project by using an Import directive.

```
'individual files

#Import "relative/local/path/to/your/file"

'entire folders

#Import "relaive/local/path/"
```

When importing entire folders, Make sure to include the trailing slash at the end to let the compiler know it's a folder.

```
'import the entire images subfolder

#Import "images/"

'import a specific sound

#Import "sounds/sound1.wav"
```

These import directives can go anywhere in your source file, but standard practice is to put them at the top of the file.

@#### Using Imported Assets

Once you've imported your assets, you can reference them by prefixing the imported filename with `asset::`
This allows you to use them with a function or method that asks for a String path to a file.

```
#Import "images/image1.png"

Local myImage:Image = Image.Load("asset::image1.png")
```

If you imported a folder containing several assets, you can reference any of the assets in this way.

```
#Import "images/"

Local image1:Image = Image.Load("asset::image1.png")
Local image2:Image = Image.Load("asset::image2.png")

```


@#### Importing into a subfolder with "@/"

If you want to maintain a folder structure when importing, you can specify a target subfolder with `@/target/path/` after the path in the import directive.

```
'imports image1.jpg into a subfolder called images

#Import "images/image1.jpg@/images/"
```

`@/` also works when importing entire folders:

```
'imports everything from images/ into a subfolder called images/

#Import "images/@/images/"
```

The destination folder name doesn't have to be the same as the source folder name.
```
'imports everything from images/ into a subfolder called data/

#Import "images/@/data/"
```

When using the files in your code, make sure to add the target subfolder after `asset::`, for example:

```
#Import "images/image1.png@data/"

Local image:Image = Image.Load("asset::data/image1.png")
```
