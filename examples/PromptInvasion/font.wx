#import "<mojo>"
#import "<std>"
Private 
Global __Afont:Font
Public
Function SetAFont:Font(url:String)
		If __Afont = Null
			__Afont = New Font
		Endif
		__Afont.LoadFont(url)
		Return __Afont
End Function

Function RenderText:Void(canvas:Canvas,txt:String,x:Float,y:Float)
	If __Afont = Null  RuntimeError("font not initialized")
	__Afont.Render(canvas,txt,x,y)
End Function

Function GetActiveFont:Font()
	Return __Afont
End Function

Class Font
 	
	Class Glyph
		Field id:Int
		Field x:Int
		Field y:Int
		Field width:Int
		Field height:Int
		Field xOffset:Float
		Field yOffset:Float
		Field xAdvance:Float
		Field page:Int
		Field characterName:String
		Field atlas:Image
		
		Method Render(canvas:Canvas,px:Float,py:Float,angle:float = 0)
			canvas.DrawRect(px+xOffset,py+yOffset,width,height,atlas,x,y)
		End Method
	End Class

	Method New()
		font = New Map<Int,Glyph>
	End Method
	
	Method  LoadFont(url:String)
		Local text:string = LoadString("asset::"+url+".fnt")
		If text = Null Print "unable to load font"
		Local lines:= text.Split(String.FromChar(10))
		font.Clear()
		For Local line := Eachin lines
			Select True
				Case line.Contains("info face")
					Local i := 10
					If line[i] = 34
						i += 1
						Local n:String = ""
						While line[i]<>34
							n += line.Mid(i,1)
							i+=1
						Wend
						fontName = n
					Endif
					size = Int(GetString(line,"Size="))
				Case line.Contains("common")
					lineHeight = Float(GetString(line,"lineHeight="))
					atlasWidth = Float(GetString(line,"scaleW="))
					atlasHeight = Float(GetString(line,"scaleH="))
					pages = Float(GetString(line,"pages="))
					atlas = New Image[pages]
				Case line.Contains("page id")
					atlasName = GetString(line,"file=")
					atlasName = atlasName.Mid(1,atlasName.Length-2)
					atlas[0] = Image.Load("asset::"+atlasName)
					If atlas[0] = Null Print "invalid image "+atlasName
				Case line.Contains("chars count")
					charsCount = Int(GetString(line,"chars count="))
				Case line.Contains("char id")
					Local glyph := New Glyph
				 	glyph.id = Int( GetString(line,"char id="))
					glyph.x = Int(GetString(line,"x="))
					glyph.y = Int(GetString(line,"y="))
					glyph.width = Int(GetString(line,"width="))
					glyph.height = Int(GetString(line,"height="))
					glyph.xOffset = Int(GetString(line,"xoffset="))
					glyph.yOffset = Int(GetString(line,"yoffset="))
					glyph.xAdvance = Int(GetString(line,"xadvance="))
					glyph.page = Int( GetString(line,"page="))
					glyph.characterName = GetString(line,"letter=")
					glyph.characterName = glyph.characterName.Mid(1,glyph.characterName.Length-2)
					glyph.atlas = atlas[glyph.page]
					font.Add(glyph.id,glyph)
			End Select
		Next
	End Method
	
	Property Name:String()
		Return fontName
	End
	
	Property Height:Float()
		Return size
	End 
	
	Property CharacterCount:int()
		Return charsCount
	End
	
	Method TextWidth:Int(text:string)
		Local width := 0
		For Local char := Eachin text
			Local glyph := font.Get(char)
			If glyph 
				width += glyph.xAdvance
			Else
				width += 8
			Endif
		Next
		Return width
	End Method
	
	Method Render(canvas:Canvas,txt:String,x:float,y:Float)
		For Local char := Eachin txt
			Local glyph := font.Get(char)
			If glyph = Null
				Print "Invalid Character in text " + txt
				DebugStop()
			Else
				glyph.Render(canvas,x,y)
				x += glyph.xAdvance
			Endif
		Next
	End Method
	
	Private
	
	Method GetString:String(line:String,s:String)
		Local index:Int = s.Length + line.Find(s)
		Local text:String = ""
		While index < line.Length And line[index] <> 32 
			text += line.Mid(index,1)
			index += 1
		Wend
	 	Return text
	End Method
	
	Field fontName:string
 	Field size:Float
 	Field lineHeight:Float
 	Field atlasWidth:Float
 	Field atlasHeight:Float
 	Field pages:Float
 	Field charsCount:Int
 	Field atlas:Image[]
 	Field atlasName:string
 	
 	Field font:Map<Int,Glyph>
 	
End Class
 
 