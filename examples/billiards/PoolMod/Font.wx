#Import "PoolMod"

Private 
Global __Afont:AngelFont
Public

Function LoadAngelFont:AngelFont(url:String)
	Local font:AngelFont = New AngelFont()
	font.italicSkew = 0.15
	font.LoadFont(url)
	Return font
End Function	

Function SetAngelFont:Void(font:AngelFont)
		__Afont = font
End Function

Function GetActiveFont:AngelFont()
	Return __Afont
End

Function ATextWidth:Int(str:String)
	Return __Afont.TextWidth(str)
End Function

Function AFontHeight:Int()
	If __Afont = Null  RuntimeError("font not initialized")
	Return __Afont.height
End function	

Function ATextHeight:Int(str:String)
	Return __Afont.TextHeight(str)
End Function

	
Function RenderText:Void(canvas:Canvas,txt:String,x:Float,y:Float)
	If __Afont = Null  RuntimeError("font not initialized")
	__Afont.RenderText(canvas,txt,x,y)
End Function

Function GetChars:Char[]()
	If __Afont = Null RuntimeError("font not initialized")
	Return __Afont.chars
End Function


Class Char
	Field asc:Int
	Field x:Int
	Field y:Int
	
	Field width:Int
	Field height:Int = 0
	
	Field xOffset:Int = 0
	Field yOffset:Int = 0
	Field xAdvance:Int = 0
	
	
	Method New(x:Int,y:Int, w:Int, h:Int, xoff:Int=0, yoff:Int=0, xadv:Int=0)
		Self.x = x
		Self.y = y
		Self.width = w
		Self.height = h
		
		Self.xOffset = xoff
		Self.yOffset = yoff
		Self.xAdvance = xadv
	End
	
	Method Render(canvas:Canvas,fontImage:Image, linex:float,liney:Float)
		canvas.DrawRect(linex+xOffset,liney+yOffset,width,height,fontImage, x,y)
	End Method

	Method toString:String()
		Return String.FromChar(asc)+"="+asc
	End Method
	
End Class

Class KernPair
	Field first:String
	Field second:String
	Field amount:Int
	
	
	Method New(first:Int, second:Int, amount:Int)
		Self.first = first
		Self.second = second
		Self.amount = amount
	End
#Rem		
	Method toString:String()
		Return "first="+String.FromChar(first)+" second="+String.FromChar(second)+" amount="+amount
	End Method
#End
End Class

Class AngelFont
	Private
	
	field _list:StringMap<AngelFont> = New StringMap<AngelFont>
	
	Field image:Image	
	Field chars:Char[] = New Char[256]
	Field kernPairs:StringMap<KernPair> = New StringMap<KernPair>
	Field iniText:String

	Field xOffset:Int
	Field yOffset:Int
	
	Field prevMouseDown:Bool = False

	Public
	Const ALIGN_LEFT:Int = 0
	Const ALIGN_CENTER:Int = 1
	Const ALIGN_RIGHT:Int = 2
	
	Global error:String
	
	Field name:String
	Field useKerning:Bool = True

	Field lineGap:Int = 5
	Field height:Int = 0
	Field heightOffset:Int = 9999
	Field scrollY:Int = 0
	
	Field italicSkew:Float = 0.25
	
	Method New(url:String="")
		If url <> ""
			Self.LoadFont(url)
			Self.name = url
			_list.Add(url,Self)
		Endif
	End Method
	
	Method GetChars:Char[]()
		Return chars
	End

	Method LoadFont:Void(url:String)
		
		error = ""
		iniText = LoadString(url+".txt")
		Local lines:= iniText.Split(String.FromChar(10))
		For Local line:= Eachin lines
		
			line=line.Trim()
			
			If line.StartsWith("id,") Or line = "" Continue
			If line.StartsWith("first,")
				Continue
			Endif
			Local data:string[] = line.Split(",")
			
			For Local i:=0 Until data.Length
				data[i]=data[i].Trim()
			Next
			
			error += data.Length+","	'+"-"+line
			If data.Length > 0
				If data.Length = 3
					kernPairs.Add(String.FromChar(Int(data[0]))+"_"+String.FromChar(Int(data[1])), New KernPair(Int(data[0]), Int(data[1]), Int(data[2])))
				Else
					If data.Length >= 8
						chars[Int(data[0])] = New Char(Int(data[1]), Int(data[2]), Int(data[3]), Int(data[4]),  Int(data[5]),  Int(data[6]),  Int(data[7]))
						Local ch := chars[Int(data[0])]
						If ch.height > Self.height Self.height = ch.height
						If ch.yOffset < Self.heightOffset Self.heightOffset = ch.yOffset
					Endif
				Endif
			Endif
		Next
		
		image = Image.Load(url+".png")
	End Method
	
	Method RenderItalic:Void(canvas:Canvas,txt:string,x:Float,y:Float)
		Local th:float=TextHeight(txt)
		
		canvas.PushMatrix()
		'Transform 1,0,-italicSkew,1, x+th*italicSkew,y
		RenderText(canvas,txt,0,0)
		canvas.PopMatrix()		
	End 
	
	Method RenderBold:Void(canvas:Canvas,txt:String, x:Int, y:Int)
		RenderText(canvas,txt, x,y)
		RenderText(canvas,txt, x+1,y)
	End
	
	
	Method RenderText:Void(canvas:Canvas,txt:String, x:Int, y:Int)
		Local prevChar:String = ""
		xOffset = 0
		
		For Local i:= 0 Until txt.Length
			Local asc:Int = txt[i]
			Local ac:Char = chars[asc]
			Local thisChar:String = String.FromChar(asc)
			If ac  <> Null
				If useKerning
					Local key:String = prevChar+"_"+thisChar
					If kernPairs.Contains(key)
						xOffset += kernPairs.Get(key).amount
					Endif
				Endif
				ac.Render(canvas,image, x+xOffset,y)
				xOffset += ac.xAdvance
				prevChar = thisChar
			Endif
		Next
	End Method
	
	Method RenderText:Void(canvas:Canvas,txt:String, x:Int, y:Int, align:Int)
		xOffset = 0
		Select align
			Case ALIGN_CENTER
				RenderText(canvas,txt,x-(TextWidth(txt)/2),y)
			Case ALIGN_RIGHT
				RenderText(canvas,txt,x-TextWidth(txt),y)
			Case ALIGN_LEFT
				RenderText(canvas,txt,x,y)
		End Select
	End Method

	Method RenderHTML:Void(canvas:Canvas,txt:String, x:Int, y:Int)
		Local prevChar:String = ""
		xOffset = 0
		Local italic:Bool = False
		Local bold:Bool = False
		Local th:Float=TextHeight(txt)
		
		For Local i:= 0 Until txt.Length
			While txt.Mid(i,1) = "<" '[i..i+1] = "<"
				Select txt.Mid(i+1,2) '[i+1..i+3]
					Case "i>"
						italic = True
						i += 3
					Case "b>"
						bold = True
						i += 3
					Default
						Select txt.Mid(i+1,3) '[i+1..i+4]
							Case "/i>"
								italic = False
								i += 4
							Case "/b>"
								bold = False
								i += 4
						End
				End
				If i >= txt.Length
					Return
				End
			Wend
			Local asc:Int = txt[i]
			Local ac:Char = chars[asc]
			Local thisChar:String = String.FromChar(asc)
			If ac  <> Null
				If useKerning
					Local key:String = prevChar+"_"+thisChar
					If kernPairs.Contains(key)
						xOffset += kernPairs.Get(key).amount
					Endif
				Endif
				If italic = False
					ac.Render(canvas,image, x+xOffset,y)
					If bold
						ac.Render(canvas,image, x+xOffset+1,y)
					End
				Else
					canvas.PushMatrix()
						'Transform 1,0,-italicSkew,1, (x+xOffset)+th*italicSkew,y
						ac.Render(canvas,image, 0,0)
						If bold
							ac.Render(canvas,image, 1,0)
						Endif					
					canvas.PopMatrix()		
				End	
				xOffset += ac.xAdvance
				prevChar = thisChar
			Endif
		Next
	End Method
	
	Method RenderHTML:Void(canvas:Canvas,txt:String, x:Int, y:Int, align:Int)
		xOffset = 0
		Select align
			Case ALIGN_CENTER
				RenderHTML(canvas,txt,x-(TextWidth(StripHTML(txt))/2),y)
			Case ALIGN_RIGHT
				RenderHTML(canvas,txt,x-TextWidth(StripHTML(txt)),y)
			Case ALIGN_LEFT
				RenderHTML(canvas,txt,x,y)
		End Select
	End Method
	
	Function StripHTML:String(txt:String)
		Local plainText:String = txt.Replace("</","<")
		plainText = plainText.Replace("<b>","")
		Return plainText.Replace("<i>","")
	End

	Method TextWidth:Int(txt:String)
		Local prevChar:String = ""
		Local width:Int = 0
		For Local i:= 0 Until txt.Length
			Local asc:Int = txt[i]
			Local ac:Char = chars[asc]
			Local thisChar:String = String.FromChar(asc)
			If ac  <> Null
				If useKerning
					Local key:String = prevChar+"_"+thisChar
					If kernPairs.Contains(key)
						width += kernPairs.Get(key).amount
					Endif
				Endif
				width += ac.xAdvance
				prevChar = thisChar
			Endif
		Next
		Return width
	End Method
	
	Method TextHeight:Int(txt:String)
		Local h:Int = 0
		For Local i:= 0 Until txt.Length
			Local asc:Int = txt[i]
			Local ac:Char = chars[asc]
			If ac.height+ac.yOffset > h h = ac.height+ac.yOffset
		Next
		Return h
	End

End Class

Global Text:BitmapText

Class BitmapText
	
	Field chWidth:Int
	Field chHeight:Int

	Field count:Int
		
	Field image:Image[]
	
	Field upper:Int
	
	Method New(image:Image[],count:Int)
		Self.chWidth = image[0].Width
		Self.chHeight = image[0].Height
		Self.image = image
		Self.count = count
	End Method

	Method CharWidth:Int()
		Return chWidth
	End Method
	
	Method CharHeight:Int()
		Return chHeight
	End Method
	
	Method Width:Int(str:String)
		Return str.Length * chWidth
	End Method
	
	Method Height:Int()
		Return chHeight
	End Method
	
	Method Draw:Void(canvas:Canvas,str:String,x:Int,y:Int)
		Local tx:Int = x
		Local ty:Int = y
		For Local c:Int = Eachin str
			c &= $FF
			If c < 91
				c -= 32
			Else
				c -= 64
			Endif
			canvas.DrawImage(image[c],tx,ty)
			tx += chWidth
		Next
	End Method

End Class

Global LargeText:VaryFont

Class VaryFont
	Field fontImg:Image[]
	
	Const COUNT:Int = 94
	
						
	Global param:Int[][] = New Int[][](New Int[]( 12,355,29,45),New int[]( 41,355,29,30),New Int[]( 70,355,29,47),New Int[](100,355,24,47),New Int[](128,355,29,47),New Int[](157,355,30,47),
									   New Int[](193,355,15,28),New Int[](222,355,19,48),New Int[](247,355,19,48),New Int[](276,355,22,32),New Int[](302,355,28,39),New Int[](337,355,16,49),
									   New Int[](363,355,23,34),New Int[](394,355,16,44),New int[](419,355,25,44),New int[](447,355,28,44),New int[](477,355,26,44),New int[](506,355,25,44),
									   New Int[](536,355,24,44),New int[](563,355,27,44),New int[](593,355,25,44),New int[](622,355,27,44),New int[](651,355,26,44),New int[](679,355,27,44),
									   New int[](708,355,26,44),New int[](744,355,15,44),New int[](773,355,15,51),New int[](796,355,25,38),New int[](825,355,26,38),New int[](855,355,24,38),
									   New int[](885,355,23,44),New int[](910,355,30,47),New int[](939,355,31,44),New int[](970,355,27,44),New int[]( 12,403,27,44),New int[]( 42,403,27,44),
									   New int[]( 72,403,24,44),New int[](100,403,25,44),New int[](128,403,27,44),New int[](158,403,26,44),New int[](189,403,23,44),New int[](216,403,23,44),
									   New Int[](245,403,29,44),New Int[](275,403,25,44),New Int[](302,403,27,44),New Int[](332,403,27,44),New Int[](360,403,27,44),New Int[](391,403,26,44),
									   New Int[](417,403,29,46),New Int[](448,403,28,44),New Int[](477,403,25,44),New Int[](505,403,29,44),New Int[](535,403,26,44),New Int[](562,403,30,44),
									   New Int[](591,403,30,44),New Int[](621,403,29,44),New Int[](650,403,28,44),New Int[](680,403,27,44),New Int[](714,403,20,47),New Int[](739,403,24,44),
									   New Int[](768,403,19,47),New Int[](794,403,29,26),New Int[](822,426,32,48),New Int[](857,403,18,20),New Int[](883,403,26,44),New Int[](912,403,27,44),
									   New Int[](940,403,25,44),New Int[](970,403,26,44),New Int[]( 12,449,27,44),New Int[]( 43,449,24,44),New Int[]( 71,449,26,49),New Int[](100,449,26,44),
						   			   New Int[](131,449,18,44),New Int[](159,449,20,49),New Int[](187,449,27,44),New Int[](217,449,24,44),New Int[](245,449,28,44),New Int[](274,449,26,44),
									   New Int[](303,449,27,44),New Int[](332,449,26,49),New Int[](361,449,26,49),New Int[](392,449,24,44),New Int[](421,449,24,44),New Int[](450,449,24,44),
									   New Int[](479,449,24,44),New Int[](506,449,26,44),New Int[](534,449,29,44),New Int[](563,449,27,44),New Int[](592,449,27,49),New Int[](622,449,25,44),
									   New Int[](654,449,21,48),New Int[](686,449,13,48),New Int[](711,449,21,48),New Int[](735,449,31,34))


	Method New(image:Image)
		fontImg = New Image[COUNT]
		For Local i:Int = 0 Until COUNT
			fontImg[i] = New Image(image,param[i][0],param[i][1],param[i][2],param[i][3])
		Next
	End Method
	
	Method TextWidth:Int(str:String)
		Local l:Int= 0	
		For Local n:Int = Eachin str
			Local i:Int = GetIndex(n)
			If i > -1
				l += param[i][2]
			Else
				l += 20
			Endif
		Next
		Return l
	End Method
	
	Method TextHeight:Int(str:String)
		Local l:Int = 0
		If str > 0
			l = param[0][3]
		Endif
		Return l
	End Method

	Method GetIndex:Int(n:Int)
			If n >32 And n < 128 Then Return n-33
			Return -1
	End Method	

	Method Draw:Void(canvas:Canvas,str:String,x:Float,y:Float)
		If str.Length = 0 Return
		For Local n:Int = Eachin str
			Local i:Int = GetIndex(n)
			If i > -1
				canvas.DrawImage(fontImg[i],x,y)
				x += param[i][2]
			Else
				x += 20
			Endif
		Next
	End Method

End Class
