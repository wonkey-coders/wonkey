Namespace mojo.graphics

Private

Function GetArg:String( name:String,args:String )
	
	Local i0:=args.Find( name+"=" )
	If i0=-1 Return 0
	
	i0+=name.Length+1
	
	Local i1:=args.Find( " ",i0 )
	If i1=-1 Return 0
	
	Return args.Slice( i0,i1 )
End

Function GetIntArg:Int( name:String,args:String )
	
	Return Int( GetArg( name,args ) )
End
		
Public

Class AngelFont Extends Font
	
	Method GetGlyph:Glyph( char:Int ) Override
		
		If char>=0 And char<_glyphs.Length Return _glyphs[char]
		
		Return _glyphs[0]
	End
	
	Method GetGlyphPage:Image( char:Int ) Override

		If char>=0 And char<_glyphs.Length Return _pages[ _glyphs[char].page ]
		
		Return _pages[0]
	End
	
	Method GetKerning:Float( firstChar:Int,secondChar:Int ) Override
		
		If Not _kernings.Length Return 0
		
		Local min:=0,max:=_kernings.Length
		
		While max>min
			
			Local mid:=(min+max)/2
			
			If firstChar>_kernings[mid].first
				min=mid+1
			Else If firstChar<_kernings[mid].first
				max=mid
			Else If secondChar>_kernings[mid].second
				min=mid+1
			Else If secondChar<_kernings[mid].second
				max=mid
			Else
				Return _kernings[mid].amount
			Endif
			
		Wend
		
		Return 0
	End
	
	Function Load:AngelFont( path:String,shader:Shader=Null,textureFlags:TextureFlags=TextureFlags.FilterMipmap )
		
		Local fnt:=LoadString( path,True )
		If Not fnt
			If Not ExtractRootDir( path ) fnt=LoadString( "font::"+path,True )
			If Not fnt Return Null
		Endif
		
		Local dir:=ExtractDir( path )
		
		Local lines:=fnt.Split( "~n" )
		
		Local pages:=New Stack<Image>
		Local glyphs:=New Stack<Glyph>
		Local kernings:=New Stack<Kerning>
		
		Local height:=0.0,minChar:=$ffff,maxChar:=0
		
		for Local i:=0 Until lines.Length
			
			Local line:=lines[i].Trim()
			If Not line Continue
			
			Local i:=line.Find( " " )
			If i=-1 Continue
			
			Local tag:=line.Slice( 0,i ).Trim()
			Local args:=line.Slice( i+1 ).Trim()+" "
			
			Select tag
			Case "common"
				
				height=GetIntArg( "lineHeight",args )
				
			Case "page"
				
				Local id:=GetIntArg( "id",args )
				Local file:=GetArg( "file",args )
				
				Local fpath:=dir+file.Slice( 1,-1 )
				
				Local pixmap:=Pixmap.Load( fpath,Null,True )
				
				Local pshader:=shader ?Else (pixmap.Format=PixelFormat.I8 ? Shader.Open( "font" ) Else Shader.Open( "sprite" ))
				
				Local image:=New Image( pixmap,textureFlags,pshader )
				
				If id>=pages.Length pages.Resize( id+1 )
					
				pages[id]=image
				
			Case "char"
				
				Local id:=GetIntArg( "id",args )
				Local x:=GetIntArg( "x",args )
				Local y:=GetIntArg( "y",args )
				Local w:=GetIntArg( "width",args )
				Local h:=GetIntArg( "height",args )
				Local tx:=GetIntArg( "xoffset",args )
				Local ty:=GetIntArg( "yoffset",args )
				Local advance:=GetIntArg( "xadvance",args )
				Local page:=GetIntArg( "page",args )
				Local chnl:=GetIntArg( "chnl",args )
			
				Local glyph:Glyph
				glyph.rect=New Recti( x,y,x+w,y+h )
				glyph.offset=New Vec2f( tx,ty )
				glyph.advance=advance
				glyph.page=page
				
				If id>=glyphs.Length glyphs.Resize( id+1 )
					
				glyphs[id]=glyph
				
				minChar=Min( id,minChar )
				maxChar=Max( id,maxChar )
				
			Case "kerning"
				
				Local kerning:Kerning
				kerning.first=GetIntArg( "first",args )
				kerning.second=GetIntArg( "second",args )
				kerning.amount=GetIntArg( "amount",args )
				
				kernings.Add( kerning )
			End
			
		Next
		
		kernings.Sort( Lambda:Int( x:Kerning,y:Kerning )
			If x.first<y.first Return -1
			If x.first>y.first Return  1
			If x.second<y.second Return -1
			If x.second>y.second Return  1
			Return 0
		End )
		
'		Print "Kernings:"
'		For Local k:=Eachin kernings
'			Print "first="+k.first+" second="+k.second+" amount="+k.amount
'		Next
		
		Local font:=New AngelFont( height,minChar,maxChar-minChar+1,glyphs.ToArray(),pages.ToArray(),kernings.ToArray() )
		
		Return font
	End
	
	Private
	
	Field _glyphs:Glyph[]
	Field _pages:Image[]
	Field _kernings:Kerning[]
	
	Struct Kerning
		Field first:Int
		Field second:Int
		Field amount:Int
	End
	
	Method New( height:Float,firstChar:Int,numChars:Int,glyphs:Glyph[],pages:Image[],kernings:Kerning[] )
		
		Init( height,firstChar,numChars )
		
		_glyphs=glyphs
		_pages=pages
		_kernings=kernings
	End

End
