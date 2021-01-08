#Import "PoolMod"
#Import "data/poolAtlasb.png"
#Import "data/hit03.ogg"
#Import "data/hit04.ogg"
#Import "data/hit05.ogg"
#Import "data/hit06.ogg"
#Import "data/shoot.ogg"
#Import "data/bank01.ogg"
#Import "data/bank02.ogg"
#Import "data/rackup.ogg"
#Import "data/applaused.ogg"
#Import "data/pocket1.ogg"
#Import "data/fail.ogg"
#Import "data/completion.ogg"
#Import "data/beep.ogg"
#Import "data/beep2.ogg"



Global media:Media

Class Media
	Field titleImg:Image
	Field tableImg:Image
	Field railImg:Image
	Field ballImg:Image
	Field stickImg:Image[]
	Field ghostImg:Image[]
	Field arrowsImg:Image
	Field rotatorImg:Image
	Field buttonImg:Image[]
	Field smallBtnImg:Image[]
	Field stripImg:Image
	
	Field getNameImg:Image
	
	Field logoImg:Image
	Field frameTopImg:Image[]
	Field frameBotImg:Image[]
	Field topImg:Image
	Field botImg:Image
	Field lrImg:Image[]
	Field rectImg:Image
	Field meterImg:Image
	Field stretchImg:Image
	Field sliderImg:Image
	Field ballCol:Sound[] = New Sound[4]
	Field shootCol:Sound
	Field railCol:Sound[] = New Sound[2]
	Field rackUp:Sound
	Field applause:Sound
	Field pocketCol:Sound
	Field pocketChannel:Channel = New Channel
	Field scratchSnd:Sound
	Field completionSnd:Sound
	Field beepSnd:Sound
	Field beepBSnd:Sound
	
	Field arcImg:Image = Null
	Field lineImg:Image = Null
	Field channeltime:Int[] = New Int[8]
	Field colChannel:Channel[] = New Channel[4]
	Field colChanIndex:Int = 0
	Field colLastChanIndex:Int = 3
	Field colFirstChanIndex:Int = 0

	Field scoreChannel:Channel[] = New Channel[5]
	Field scoreChanIndex:Int = 0
	Field scoreLastChan:Int = 5
		
	Method New()
	
	End Method
	
	Method New(atlasImg:Image)
		If(atlasImg = Null) RuntimeError("unable to load GameAtlas.png")
		titleImg = New Image(atlasImg,0,544,640,480)
		tableImg = New Image(atlasImg,0,0,640,360)
		railImg = New Image(atlasImg,640,0,384,41)
		ballImg = New Image(atlasImg,996,104,23,23)
		ballImg.Handle= New Vec2f(.4,.4)
		stickImg = LoadFrames(atlasImg,1,501,392,9,1)
		stickImg[0].Handle = New Vec2f(1.0,.5)
		ghostImg = LoadFrames(atlasImg,640,140,22,22,3)
		ghostImg[0].Handle = New Vec2f(.5,.5)
		ghostImg[1].Handle = New Vec2f(.5,.5)
		ghostImg[2].Handle = New Vec2f(.5,.5)
		arrowsImg = New Image(atlasImg,890,141,47,47)
		arrowsImg.Handle = New Vec2f(23.0/47.0,23.0/47.0)
		rotatorImg = New Image(atlasImg,788,140,101,64)
		rotatorImg.Handle = New Vec2f(51.0/101.0,43.0/64.0) 
		buttonImg = LoadFrames (atlasImg,640,41,190,62,2)
		smallBtnImg = LoadFrames(atlasImg,643,289,130,50,2)
		stripImg = New Image(atlasImg,1015,130,1,3)
		stripImg.Handle = New Vec2f(0.0,.5)
		getNameImg = New Image(atlasImg,641,848,383,176)
		logoImg = New Image(atlasImg,640,545,255,275)
		frameTopImg = LoadFrames(atlasImg,997,128,4,4,2)
		frameBotImg = LoadFrames(atlasImg,997,132,4,4,2)
		topImg = New Image(atlasImg,1000,128,1,4)
		botImg = New Image(atlasImg,1000,132,1,4)
		lrImg = LoadFrames(atlasImg,997,131,4,1,2)
		rectImg = New Image(atlasImg,1011,131,1,1)
		meterImg = New Image(atlasImg,640,103,346,36)
		stretchImg = New Image(atlasImg,988,103,1,36)
		sliderImg = New Image(atlasImg,990,103,4,36)
		ballCol[0] = Sound.Load("asset::hit03.ogg")
		If ballCol[0] = Null RuntimeError("unable to load hit03.ogg")
		ballCol[1] = Sound.Load("asset::hit04.ogg")
		If ballCol[1] = Null RuntimeError("unable to load hti04.ogg")
		ballCol[2] = Sound.Load("asset::hit05.ogg")
		If ballCol[2]  =  Null RuntimeError("unable to lead hit05.ogg")
		ballCol[3]  =  Sound.Load("asset::hit06.ogg")
		If ballCol[3] = Null RuntimeError("unable to load hit06.ogg")
		shootCol = Sound.Load("asset::shoot.ogg")
		If shootCol = Null RuntimeError("unable to load shoot.ogg")
		railCol[0] = Sound.Load("asset::bank01.ogg")
		If railCol[0] = Null RuntimeError("unable to load bank01.ogg")
		railCol[1] = Sound.Load("asset::bank02.ogg")
		If railCol[1] = Null RuntimeError("unable to load bank02.ogg")
		rackUp = Sound.Load("asset::rackup.ogg")
		If rackUp = Null RuntimeError("unable To load rackUp.ogg")
		applause = Sound.Load("asset::applaused.ogg")
		If applause = Null RuntimeError("unable to load applaused.ogg")
		pocketCol = Sound.Load("asset::pocket1.ogg")
		If pocketCol = Null RuntimeError("unable to load pocket1.ogg")
		scratchSnd = Sound.Load("asset::fail.ogg")
		If scratchSnd = Null RuntimeError("unable to load fail.ogg")
		completionSnd = Sound.Load("asset::completion.ogg")
		If completionSnd = Null RuntimeError("unable to load completionSnd.ogg")
		beepSnd = Sound.Load("asset::beep.ogg")
		If beepSnd = Null Print("unable to load beep.ogg")
		beepBSnd = Sound.Load("asset::beep2.ogg")
		If beepBSnd  =  Null RuntimeError("unable to load beep2.ogg")
		For Local i:Int = 0 Until 4
			colChannel[i] = New Channel()
		Next
		
		For Local i:Int = 0 Until scoreLastChan
			scoreChannel[i] = New Channel
		Next
	End Method
	
	
	Method UpdateChannel:Void()
		colChanIndex += 1
		If colChanIndex >= colLastChanIndex colChanIndex = colFirstChanIndex
	End Method
	
	Method PlayPocketCol:Void()
		
		Local t:Int = Millisecs()-channeltime[colChanIndex]
		If(t>200)
			channeltime[colChanIndex] = Millisecs()
			pocketCol.Play()
			UpdateChannel()
		Endif
		
	End Method
	
	Method PlayScratch:Void()
		
		scratchSnd.Play()
		
	End Method
	
	Method PlayBallCol:Void(n:Int)
		
		If(n>3) n = 3
		If(n<0) n = 0
		Local t:Int = Millisecs()-channeltime[colChanIndex]
		If(t>200)
			channeltime[colChanIndex] = Millisecs()
			colChannel[colChanIndex].Play(ballCol[n])
			UpdateChannel()
		Endif
		
	End Method
	
	Method PlayRailCol:Void(n:Int)
		
		Local t:Int = Millisecs()-channeltime[colChanIndex]
		If(t>200)
			channeltime[colChanIndex] = Millisecs()
			colChannel[colChanIndex].Play(railCol[n],0)
			UpdateChannel()
		Endif
		
	End Method
	
	Method updateScoreChan:Void()
		
		scoreChanIndex =(scoreChanIndex + 1) Mod scoreLastChan
		
	End Method
	
	Method PlayBeep:Void()
		
		Local t:Int = Millisecs()-channeltime[scoreChanIndex]
		channeltime[scoreChanIndex] = Millisecs()
		scoreChannel[scoreChanIndex].Play(beepSnd)
		updateScoreChan()
		
	End Method
	
	Method PlayBeepB:Void()
		
		Local t:Int = Millisecs()-channeltime[scoreChanIndex]
		channeltime[scoreChanIndex] = Millisecs()
		scoreChannel[scoreChanIndex].Play(beepBSnd)
		updateScoreChan()
		
	End Method
	
	Method PlayShootCol:Void()
		Local t:Int = Millisecs()-channeltime[colChanIndex]
		If(t>200)
			channeltime[colChanIndex] = Millisecs()
			colChannel[colChanIndex].Play(shootCol)
			UpdateChannel()
		End If
		
	End Method
	
End Class

