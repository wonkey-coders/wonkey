#Import "PoolMod"

#Import "data/frame.png"
#Import "data/button.png"

Global __atlas:Image
Global __btnAtlas:Image

Function GetAtlas:Image()
	If __atlas = Null
		__atlas = Image.Load("asset::frame.png")
	Endif
	Return __atlas
End Function

Function GetBtnAtlas:Image()
	If __btnAtlas = Null
		__btnAtlas = Image.Load("asset::button.png")	
	Endif
	Return __btnAtlas
End Function

Class Button
	Field pos:PVector2D
	Field x:Float
	Field y:Float
	Field width:Float
	Field height:Float
	Field text:String
	Field offx:Float
	Field offy:Float
	Field activated:Int
	Field selected:Int
	Field oldDown:Int
	Field image:Image[]
	Field font:AngelFont

	Method New(font:AngelFont,img:Image[],x:Int,y:Int,str:String,p:PVector2D=Null)
		Self.font= font
		If p = Null
			Self.pos = New PVector2D(x,y)
			Self.x = 0
			Self.y = 0
		Else
			pos = p
			Self.x = x
			Self.y = y
		End If
		Self.text = str
		Self.width = img[0].Width
		Self.height = img[0].Height
		Self.offx = offx
		Self.offy = offy
		Self.image = img
		Self.SetText(str)
	End Method
	
	Method SetText:Void(str:String)
		text = str
		If text.Length > 0
			offx = (image[0].Width - font.TextWidth(str))/2.0
			offy = (image[0].Height - font.TextHeight(str))/2.0
		Endif
	End Method
	
	Method Update:Void()
		Local thisDown := Mouse.ButtonPressed(MouseButton.Left)
		If thisDown
			If Not oldDown And inArea()
				selected = True
			Endif
		Elseif oldDown
			If selected = True
				If activated = False
					If inArea()
						activated = True
						selected = False
					Else
						selected = False
					Endif
				Endif
			Elseif activated
				activated = False
			Endif
		Else
			activated = False
		Endif
		oldDown = thisDown
	End Method
	
	Method GetState:Int()
		Local state:Int = activated
		activated = False
		Return state
	End Method

	Method inArea:Int()
		Local tx := Mouse.X
		Local ty := Mouse.Y
		If tx < pos.x+x Return False
		If ty < pos.y+y Return False
		If tx > pos.x+x+width Return False
		If ty > pos.y+y+height Return False
		Return True	
	End Method

	Method Render:Void(canvas:Canvas)
		Local index:Int = 0
		If selected Or inArea() Then index = 1
		canvas.Color = New Color(1,1,1)
		canvas.DrawImage(image[index],pos.x+x,pos.y+y)
		If text.Length > 0
			font.RenderText(canvas,text,pos.x+x+offx+index,pos.y+y+offy+index)	
		Endif
	End Method


End Class


Class Button2 
	Field pos:PVector2D=Null
	Field x:Float
	Field y:Float
	Field text:String=""
	Field width:Float
	Field height:Float
	Field offx:Float
	Field offy:Float
	Field image:Image[]

	Field selected:Int=0
	Field activated:Int=0
	
	Field oldDown:Int=0

	Method SetText:Void(tstr:String)
		text=tstr
		Local tw:Int=tstr.Length*Text.CharWidth()
		offx=(image[0].Width-tw)/2.0
		Local th:Int=image[0].Height-Text.CharHeight()
		offy=th/2.0
	End Method

	Method New(timg:Image[],tx:Int,ty:Int,tstr:String,tp:PVector2D=Null)
		If(tp=Null)
			pos=New PVector2D
			pos.x=tx
			pos.y=ty
			x=0.0
			y=0.0
		Else
			pos=tp
			x=(tx)
			y=(ty)
		Endif
		text=tstr
		width=timg[0].Width
		height=timg[0].Height
		offx=offx
		offy=offy
		image=timg
		SetText(tstr)
		
	End Method
	
	Method inArea:Int()
	
		Local ttx:Float=Mouse.X
		Local tty:Float=Mouse.Y
		If ttx<pos.x+x Return 0
		If tty<pos.y+y	Return 0
		If ttx>pos.x+x+width Return 0
		If tty>pos.y+y+height Return 0
		Return 1
		 
	End Method
	
	Method Update:Void()

		Local SelfDown:Int=Mouse.ButtonDown(MouseButton.Left)

		If SelfDown
			If Not(oldDown) And inArea()
				selected=1
			End
		Elseif oldDown
			If selected=1
				If activated=0
					If inArea()
						activated=1
						selected=0
					Else
						selected=0
					End
				End
			Else
				If activated activated = 0
			End
		End
		oldDown=SelfDown
	End Method

	Method GetState:Int()
		Local tstate:Int=activated
		activated=0
		Return tstate
	End Method

	Method Render:Void(canvas:Canvas)
		Local index:Int=0
		If selected	index=1
		canvas.Color = New Color(1,1,1)
		canvas.DrawImage(image[index],pos.x+x,pos.y+y)
		Text.Draw(canvas,text,pos.x+x+offx+index,pos.y+y+offy+index)
	End Method
	
End Class

Class FrameAnimation

	Field x					:Float
	Field y					:Float
	
	Field px				:Int
	Field py				:Int
	
	Field width				:Int
	Field height			:Int
	
	Field delay				:Int
	Field currentWidth		:Int
	Field currentHeight		:Int
	
	Field stp				:Int
	Field time				:Int
	
	Field animating			:Int
	
	Field frameTopImg		:Image[]
	Field frameBotImg		:Image[]
	Field topImg			:Image
	Field botImg			:Image
	Field lrImg				:Image[]
	Field rectImg			:Image
	
	Method New(media:Media,x:Int,y:Int,width:Int,height:Int,delay:Int = 2,stp:Int = 40)
		Self.x = x
		Self.y = y
		Self.width = width
		Self.height = height
		Self.delay = delay
		Self.currentWidth = 1
		Self.currentHeight = 1
		Self.stp = stp
		Self.frameTopImg = media.frameTopImg
		Self.frameBotImg = media.frameBotImg
		Self.topImg =      media.topImg
		Self.botImg =      media.botImg
		Self.lrImg =       media.lrImg
		Self.rectImg =	   media.rectImg
	End Method
	
	Method Init:Void()
		animating = True
		currentWidth = 1
		currentHeight = 1
		px = x+width/2
		py = y+height/2
		time = Millisecs()
	End Method
	
	Method Update:Int()
		If animating = True
			If Millisecs() > time+delay
				currentWidth += stp		
				currentHeight += stp
				px -= stp/2
				py -= stp/2
				If currentWidth > width  Then 
					currentWidth = width 
					px = x
				Endif
				If currentHeight > height Then
					currentHeight = height 
					py = y
				Endif
				If currentHeight = height And currentWidth = width 
					animating = False
				Endif
				time = Millisecs()
			Endif
		Endif
		Return animating
		
	End Method
		 

	Method Render:Void(canvas:Canvas)

		Local tw:Int = 4
		Local th:Int = 4
		Local fx:Float = px-tw
		Local fy:Float = py-th
		
		canvas.DrawImage(frameTopImg[0],fx,fy)
		canvas.DrawImage(topImg,fx+tw,fy,0,currentWidth,1)
		canvas.DrawImage(frameTopImg[0],fx+currentWidth+tw,fy)
		
		canvas.DrawImage(lrImg[0],fx,fy+th,0,1,currentHeight)
		canvas.DrawImage(lrImg[1],fx+tw+currentWidth,fy+th,0,1,currentHeight)
		
		canvas.DrawImage(frameBotImg[0],fx,fy+th+currentHeight)
		canvas.DrawImage(botImg,fx+tw,fy+th+currentHeight,0,currentWidth,1)
		canvas.DrawImage(frameBotImg[1],fx+tw+currentWidth,fy+th+currentHeight)
		canvas.DrawImage(rectImg,px,py,0,currentWidth,currentHeight)		
	End Method

End Class

Class GuiFrame
	Field x:Float
	Field y:Float
	Field lft:Float
	Field top:Float
	Field right:Float
	Field bottom:Float
	Field width:Float
	Field height:Float
	Field color:Color
	
	Field leftTopImg:Image
	Field leftBotImg:Image
	Field rightTopImg:Image
	Field rightBotImg:Image
	
	Field topImg:Image
	Field botImg:Image
	Field leftImg:Image
	Field rightImg:Image
	Field areaImg:Image
	
	Method New(x:Float,y:Float,width:Float,height:Float,color:Color = New Color(1,1,1))
		Self.x = x
		Self.y = y
		Self.width = width
		Self.height = height
		Self.color = color
		
		Local atlas:Image = GetAtlas()
		Self.leftTopImg = New Image(atlas,0, 0,16,16)
		Self.leftBotImg = new Image(atlas,0,16,16,16)
		Self.rightTopImg = new Image(atlas,16,0,16,16)
		Self.rightBotImg = new Image(atlas,16,16,16,16)
		
		Self.topImg = new Image(atlas,15, 0, 1,16)
		Self.botImg = new Image(atlas,15,16, 1,16)
		Self.leftImg = new Image(atlas,0,15,16, 1)
		Self.rightImg = new Image(atlas,16,15,16,1)
		Self.areaImg = new Image(atlas,16,16,1,1)
		
		Self.lft = x - 8
		Self.top = y - 8
		Self.bottom = y+height
		Self.right  = x+width
		
	End Method
	
	Method Setxy:Void(x:Float,y:Float)

		Self.x = x
		Self.y = y
		Self.lft = x - 8
		Self.top = y - 8
		Self.bottom = y+height
		Self.right  = x+width
	
	End Method
	
	Method SetArea:Void(w:Float,h:Float)
		width = w
		height = h
		bottom = y + height
		right = x + width
	End Method
	
	Method Render:Void(canvas:Canvas)
		
		Local oldColor:Color = canvas.Color
		canvas.Color = color
		
		canvas.DrawImage(leftTopImg, lft, top,0,.5,.5)
		canvas.DrawImage(rightTopImg, right, top,0,0.5,0.5)
		canvas.DrawImage(leftBotImg, lft, bottom,0,0.5,0.5)
		canvas.DrawImage(rightBotImg, right, bottom,0,0.5,0.5)
		
		canvas.DrawImage(topImg, x, top,0,width,.5)
		canvas.DrawImage(botImg, x, bottom,0,width,.5)
		canvas.DrawImage(leftImg,lft,y,0,.5,height)
		canvas.DrawImage(rightImg,right,y,0,.5,height)
		canvas.DrawImage(areaImg,x,y,0,width,height)
		canvas.Color = oldColor
	End Method

End Class

Class Enquiry

	Field x:Int
	Field y:Int
	Field frame:GuiFrame
	Field txtBox:GuiTextBox
	Field okBtn:Button
	Field cancelBtn:Button
	Field startBtn:Button

	Method New(font:AngelFont,txt:String,x:Int,y:Int,width:Int,height:Int)
		frame = New GuiFrame(x-5,y-5,width+5,height+5,New Color($44/255.0,$44/255.0,$AA/255.0))
		txtBox = New GuiTextBox(txt,x,y,width,height)
		Local btnImage:Image[] = LoadFrames(GetBtnAtlas(),0,62,120,62,2)
		okBtn = New Button(font,btnImage,x,y+height-70,"OK")
		cancelBtn = New Button(font,btnImage,x+130,y+height - 70,"Cancel")
		startBtn = New Button(font,btnImage,x+260,y+height - 70,"Restart")
	End Method
	
	Method Update:Void()
		okBtn.Update()
		cancelBtn.Update()
		startBtn.Update()
	End Method
	
	Method IsCanceled:Int()
		Return cancelBtn.GetState() = True
	End Method
	
	Method IsOK:Int()
		Return okBtn.GetState() = True
	End Method
	
	Method IsRestart:Int()
		Return startBtn.GetState() = True
	End Method
	
	Method Render:Void(canvas:Canvas)
		frame.Render(canvas)
		txtBox.Render(canvas)
		okBtn.Render(canvas)
		cancelBtn.Render(canvas)
		startBtn.Render(canvas)
	End Method
End Class

Class StringLine
	Field x:Int
	Field y:Int
	Field txt:String
	
	Method New(txt:String,x:Int,y:Int)
		Self.txt = txt
		Self.x = x
		Self.y = y
	End Method
	
	Method Render:Void(canvas:Canvas)
		RenderText(canvas,txt,x,y)
	End Method
End Class

Class TextFieldGui
	Field pos:PVector2D
	Field x:Int
	Field y:Int
	Field image:Image
	Field cancelBtn:Button2
	Field okBtn:Button2
	Field textField:TextField
	
	Method New(x:Int,y:Int,txt:String,p:PVector2D,blinkDelay:Int)
		If( Not p)
			Self.pos=New PVector2D()
			Self.pos.x=(x)
			Self.pos.y=(y)
			Self.x=0
			Self.y=0
		Else
			Self.pos=p
			Self.x=x
			Self.y=y
		End
		image=media.getNameImg
		cancelBtn=New Button2(media.smallBtnImg,50,110,"Cancel",Self.pos)
		okBtn=New Button2(media.smallBtnImg,200,110,"Ok",Self.pos)
		textField=New TextField(30.0,72.0,txt,15,Null,Self.pos,blinkDelay)
	End
	
	Method Update:Int()
		textField.Update()
		cancelBtn.Update()
		okBtn.Update()
		If cancelBtn.GetState()
			Return -1
		ElseIf okBtn.GetState()
			If textField.GetText()=""
				Return 1
			End
			Return 0
		End
		Return 1
	End
	
	Method GetText:String()
		Return Self.textField.GetText()
	End
	
	Method Render:Void(canvas:Canvas)
		canvas.DrawImage(Self.image,Self.pos.x+(Self.x),Self.pos.y+(Self.y),0)
		textField.Render(canvas)
		cancelBtn.Render(canvas)
		okBtn.Render(canvas)
	End
End

Class GuiTextBox
	
	Field yOffset:Int = 0	
	Field slist:List<StringLine>
	Field align:Int
	
	Const ALIGN:Int = AngelFont.ALIGN_LEFT
	Const lineGap:Int = 5
	
	Method New(text:String,x:Int,y:Int,width:Int,alignment:Int = ALIGN)
		slist = New List<StringLine>
		Local thisLine:String = ""
		Local charOffset:Int = 0
		
		Local wordLen:Int = 0
		Local word:String = ""
		
		align = alignment
		
		yOffset = 0
		For Local i := 0 Until text.Length
			If y+yOffset > DEVICE_HEIGHT
				Return
			Endif		
		
			Local asc:Int = text[i]
			Select asc
				Case 32	' space
					wordLen = ATextWidth(word)
					If charOffset + wordLen > width
						slist.AddLast(New StringLine(thisLine,x,y+yOffset))
						yOffset += lineGap+AFontHeight()
						thisLine = ""
						charOffset = 0
					Endif
					charOffset += wordLen+GetChars()[32].xAdvance
					thisLine += word + " "
					
					word = ""
				Case 10' newline
					wordLen = ATextWidth(word)
					If charOffset + wordLen > width
						slist.AddLast(New StringLine(thisLine,x,y+yOffset))
						yOffset += lineGap+AFontHeight()
						thisLine = ""
					Endif
					thisLine += word
				
					slist.AddLast(New StringLine(thisLine,x,y+yOffset))
					yOffset += lineGap+AFontHeight()
					thisLine = ""
					charOffset = 0
					word = ""
				Default
					Local ch:Char = GetChars()[asc]
					word += String.FromChar(asc)
			End Select
		Next

		If word <> ""
			wordLen = ATextWidth(word)
			If charOffset + wordLen > width
				slist.AddLast(New StringLine(thisLine,x,y+yOffset))
				yOffset += lineGap+AFontHeight()
				thisLine = ""
			Endif
			thisLine += word
		Endif
		If thisLine <> ""
			slist.AddLast(New StringLine(thisLine,x,y+yOffset))
			yOffset += lineGap+AFontHeight()
		Endif
	End Method
		
	Method Render:Void(canvas:Canvas)
		Local node:List<StringLine>.Node = slist.FirstNode()
		canvas.Color = New Color(1,1,0)
		While node.Value
			node.Value.Render(canvas)
			node = node.Succ
		Wend
		canvas.Color = New Color(1,1,1)	
	End
	
End Class


Class TextField
	Field x:Int
	Field y:Int
	Field pos:PVector2D
	Field text:String
	Field maxChars:Int
	Field cursorx:Int
	Field textImg:Image[]
	
	Field blink			:Int
	Field delay			:Int
	Field time			:Int
	
	Method New(x:Float,y:Float,txt:String,maxChr:Int,txtImg:Image[]=Null,p:PVector2D= Null,blinkDelay:Int = 200)
		If p = Null
			pos = New PVector2D(x,y)
			Self.x = 0
			Self.y = 0
		Else
			Self.pos = p
			Self.x = x
			Self.y = y
			
		Endif
		Self.maxChars = maxChr
		If txtImg = Null 
			Self.textImg = GetFont()
		Else
			Self.textImg = txtImg
		Endif
		
		Self.delay = blinkDelay
		Self.time = Millisecs()
		Self.text = txt
		If text.Length > maxChr text = text.Left(maxChr)
		cursorx = text.Length
	End Method
	
	Method SetFont:Void(image:Image[])
		textImg = image
	End Method
	
	Method GetPixelWidth:Int()
		Return (maxChars+1)*textImg[0].Width
	End Method
	
	Method GetText:String()
		Return text
	End Method
	
	Method Update:Void()
		Local chr:Int = Keyboard.GetChar()
		If chr>255 chr = Keyboard.TranslateKey(Cast<Key>(chr))
		
		If chr
			Select chr
				Case Key.Up
				Case Key.Down
				Case Key.Insert
				Case Key.Tab
				Case Key.Enter
				Case Key.Escape			
				Case Key.Backspace
					Print cursorx
					If cursorx > 0
						text = text.Slice(0,cursorx-1)+text.Slice(cursorx,text.Length)
						Print text
						cursorx -= 1
					Endif
				Case Key.PageUp
					cursorx = 0
				Case Key.PageDown
					cursorx = text.Length
				Case Key.KeyEnd
					cursorx = text.Length
				Case Key.Home
					cursorx = 0
				Case Key.Left
					If cursorx > 0 
						cursorx -= 1
					Endif
				Case Key.Right
					If cursorx < text.Length
						cursorx += 1
					Endif
				Default
					If text.Length < maxChars
						text = text.Slice(0,cursorx)+String.FromChar(chr)+text.Slice(cursorx,text.Length)
						cursorx +=1
					Endif	
			End Select
		Endif
		
		If Millisecs() > time+delay
			blink = Not blink
			time = Millisecs()
		Endif

	End Method

	Method Render:Void(canvas:Canvas)
		Text.Draw(canvas,text,pos.x+x,pos.y+y)
		If blink canvas.DrawRect(pos.x+x+Text.Width(text),pos.y+y+Text.Height(),8,3)
	End Method
		

End Class

