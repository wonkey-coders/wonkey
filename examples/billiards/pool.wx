
#Import "PoolMod/PoolMod"

Function Main()
	
	New AppInstance
	
	New Game
	
	App.Run()
End

Class Game Extends Window

	Field state:Int=0
	Field fontImg:Image[]
	Field frame1:FrameAnimation
	Field frame2:FrameAnimation
	Field pvcBtn:Button2
	Field pvpBtn:Button2
	Field soloBtn:Button2
	Field scores:Button2
	Field pool8:Pool
	Field poolSolo:Pool
	Field alpha:Float=.0
	Field started:Int=0
	Field down:Int=0
	Field pool:Pool
	
	Method New(title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null)
		Super.New( title,width,height,flags )
		state=1
		atlasImg=Image.Load("asset::poolAtlasb.png")
		If atlasImg = Null RuntimeError("Unable to load poolatlasb.png")
		media=New Media(atlasImg)
		LargeText=New VaryFont(atlasImg)
		fontImg=LoadFrames(atlasImg,0,512,10,16,96)
		If Not fontImg RuntimeError("Unable to load fontImg.png")
		SetFont(fontImg,32)
		Text=New BitmapText(fontImg,77)
		frame1=New FrameAnimation(media,50,50,DEVICE_WIDTH-100,DEVICE_HEIGHT-100,2,40)
		frame2=New FrameAnimation(media,50,20,DEVICE_WIDTH-100,DEVICE_HEIGHT-40,0,40)
		Local buttonImg:Image[]=media.buttonImg
		pvcBtn=New Button2(buttonImg,(DEVICE_WIDTH-buttonImg[0].Width)/2,120,"VS Computer",Null)
		pvpBtn=New Button2(buttonImg,(DEVICE_WIDTH-buttonImg[0].Width)/2,200,"VS Player",Null)
		soloBtn=New Button2(buttonImg,(DEVICE_WIDTH-buttonImg[0].Width)/2,280,"VS Time",Null)
		scores=New Button2(buttonImg,(DEVICE_WIDTH-buttonImg[0].Width)/2,360,"Scores",Null)
		inputName=New TextFieldGui(150,150,"Player 1",Null,200)
		pool8= New EightBall()
		poolSolo= New PoolSoloTime()
		scoreTableVsTime= New ScoreTable("scoreTable.dat")
		alpha=0.0
		started=1
		frame1.Init()
	End
	
	Method OnUpdate:Int()
		
		If Mouse.ButtonDown(MouseButton.Left) Self.down=1
		If state=1
			If(Mouse.ButtonDown(MouseButton.Left)=0 And down=1)
				frame2.Init()
				alpha=0
				down=0
				state=2
			End
		ElseIf state=2
			pvcBtn.Update()
			pvpBtn.Update()
			soloBtn.Update()
			scores.Update()
			If True = pvcBtn.GetState()
				pool=pool8
				pool.SetupPVC()
				state=6
				pool.Reset()
			Elseif True = pvpBtn.GetState()
				pool = pool8
				pool.SetupPVP()
				state = 6
				pool.Reset()
			Elseif True = soloBtn.GetState()
				pool = poolSolo
				pool.SetupTimed()
				state=6
				pool.InitGame()
			Elseif True = scores.GetState()
				state=7
				scoreTableVsTime.InitFrame()
			End
		ElseIf(state=6)
			If pool.Update()=0
				Self.state=7
				Local record:Record=Self.pool.GetRecord()
				scoreTableVsTime.SetRecord(record)
				scoreTableVsTime.SaveTable()
				scoreTableVsTime.InitFrame()
			End
		ElseIf state=7
			If scoreTableVsTime.Update()=False
				Self.frame2.Init()
				Self.alpha=0
				Self.down=0
				Self.state=2
			End
		Elseif(state=4)
		End
		Return 1
	End
	
	Method OnRender(canvas:Canvas) Override

		OnUpdate()

		App.RequestRender()

		canvas.Color = New Color(1,1,1)
		canvas.DrawImage(media.titleImg,0.0,0.0)
		If(state=1)
			Self.frame1.Render(canvas)
			If(started=1)
				canvas.Color = New Color(1,1,1)
				canvas.DrawImage(media.titleImg,0.0,0.0)
				Self.started=0
			Else
				If Self.frame1.Update()=0
					canvas.DrawImage(media.logoImg,180.0,60.0)
					Local str:String="HEXOBOT"
					Local x:Int=(DEVICE_WIDTH-LargeText.TextWidth(str))/2
					Local y:Int=340
					If(Self.alpha<1.0)
						 canvas.Alpha = alpha
						Self.alpha+=.02
					End
					str="Touch To Continue"
					canvas.Color = New Color(1,1,1)
					x= (DEVICE_WIDTH-Text.Width(str))/2
					y=DEVICE_HEIGHT-80
					Text.Draw(canvas,str,x,y)
				End
			End
			canvas.Alpha = 1.0
		ElseIf(state=2)
			Self.frame2.Render(canvas)
			If(Self.frame2.Update()=0)
				canvas.DrawImage(media.logoImg,180.0,60.0,0)
				If(Self.alpha<1.0)
					canvas.Alpha = alpha
					alpha+=0.02
				End
				pvcBtn.Render(canvas)
				pvpBtn.Render(canvas)
				soloBtn.Render(canvas)
				scores.Render(canvas)
			End
			canvas.Alpha = 1.0
		Elseif(state=6)
			Self.pool.Render(canvas)
		Elseif(state=7)
			scoreTableVsTime.Render(canvas)
		End
	End
End


Global atlasImg:Image

Global inputName:TextFieldGui

Class Pool
	Field engine:ElasticEngine
	Field ballList:List<Ball>
	Field arcList:List<ArcWall>
	Field pottedList:List<Ball>
	Field turnList:List<Ball>
	Field tableImg:Image
	Field arrowsImg:Image
	Field ballImg:Image
	Field railAnimation:RailAnimation
	Field Exiting:Int=0
	Field player:Record
	Field state:Int=0
	Field cue:Ball
	
	Field activePlayer:User
	Field otherPlayer:User
	Field incrementer:Int=0
	Field scoreLevel:Int=1
	Field maxLevel:Int=15
	Field decrementer:Int=0
	
	Field user:User
	Field minLevel:Int
	
	Method Setup16()
		For Local a:ArcWall = Eachin arcList
			Select a.num
				Case 1 a.SetTarget(a.P.x+16.0,a.P.y+16.0)
				Case 2 a.SetTarget(a.P.x,a.P.y+15.0)
				Case 3 a.SetTarget(a.P.x-16.0,a.P.y+16.0)
				Case 4 a.SetTarget(a.P.x-16.0,a.P.y-16.0)
				Case 5 a.SetTarget(a.P.x,a.P.y-15.0)
				Case 6 a.SetTarget(a.P.x+16.0,a.P.y-16.0)
			End Select
		Next
		Self.engine.Add3DBall(180.8,180.0,10.0,0.0,0.0,media.ballImg,new Color(1,1,.1),new Color(.6,.2,.6),1,0)
		Self.engine.Add3DBall(162.6,170.0,10.0,0.0,0.0,media.ballImg,new Color(.3,.3,1),new Color(1,1,0),2,0)
		Self.engine.Add3DBall(162.6,190.0,10.0,0.0,0.0,media.ballImg,new Color(1,.25,.25),new Color(1,1,0),3,0)
		Self.engine.Add3DBall(144.4,160.0,10.0,0.0,0.0,media.ballImg,new Color(.35,.2,1),new Color(1,1,0),4,0)
		Self.engine.Add3DBall(144.4,200.0,10.0,0.0,0.0,media.ballImg,new Color(1,.35,.12),new Color(0,1,1),5,0)
		Self.engine.Add3DBall(126.2,150.0,10.0,0.0,0.0,media.ballImg,new Color(.12,.8,.12),New Color(0,0,1),6,0)
		Self.engine.Add3DBall(126.2,170.0,10.0,0.0,0.0,media.ballImg,new Color(.8,.1,.1),new Color(.9,.9,.9),7,0)
		Self.engine.Add3DBall(144.4,180.0,10.0,0.0,0.0,media.ballImg,new Color(.35,.35,.35),new Color(.93,.93,.93),8,0)
		Self.engine.Add3DBall(126.2,190.0,10.0,0.0,0.0,media.ballImg,new Color(1,1,.1),new Color(.6,.2,.6),9,0)
		Self.engine.Add3DBall(126.2,210.0,10.0,0.0,0.0,media.ballImg,new Color(.3,.3,1),new Color(1,1,0),10,0)
		Self.engine.Add3DBall(108.0,140.0,10.0,0.0,0.0,media.ballImg,new Color(1,.25,.25),new Color(1,1,0),11,0)
		Self.engine.Add3DBall(108.0,160.0,10.0,0.0,0.0,media.ballImg,new Color(.35,.2,1),new Color(1,1,0),12,0)
		Self.engine.Add3DBall(108.0,180.0,10.0,0.0,0.0,media.ballImg,new Color(1,.35,.12),new Color(0,1,1),13,0)
		Self.engine.Add3DBall(108.0,200.0,10.0,0.0,0.0,media.ballImg,new Color(.12,.8,.12),New Color(0,0,1),14,0)
		Self.engine.Add3DBall(108.0,220.0,10.0,0.0,0.0,media.ballImg,new Color(.8,.1,.1),new Color(.9,.9,.9),15,0)
		Self.cue=Self.engine.Add3DBall(490.0,180.0,10.0,-15.0,0.05,media.ballImg,new Color(1,1,1),new Color(.6,.2,.6),16,0)
	End
	Method SetupPVC() Abstract
	Method Reset() Abstract
	Method SetupPVP() Abstract
	Method SetupTimed() Abstract
	Method InitGame() Abstract
	Method Update:Int() Abstract
	
	Method GetRecord:Record()
		Return Self.player
	End
	
	Method Render(canvas:Canvas) Abstract

	Method BallInHole()
		For Local a:ArcWall = Eachin arcList
			For Local b:Ball = Eachin ballList
				If(a.BallInside(b))
					engine.RemoveBall(b)
					pottedList.AddLast(b)
					turnList.AddLast(b)
					railAnimation.AddJob(b)
					media.PlayPocketCol()
					If(b.num<16)
						incrementer+=5000
						player.score+=scoreLevel*100
						scoreLevel+=1
						If scoreLevel>maxLevel scoreLevel=maxLevel
						player.IncrementPocketed()
					Else
						decrementer += 30000
						media.PlayScratch()
					End
				End
			End
		End
	End
	Method ListContains:Bool(list:List<Ball>,num:Int)
		For Local b2:Ball = Eachin list
			If(b2.num=num)
				Return True
			End
		End
		Return False
	End

	Method ListContains:Bool(list:List<Ball>,b:Ball)
		For Local b2:Ball = Eachin list
			If(b2=b) Return True
		Next
		Return False
	End
	
	Method RestoreCue() Virtual	
		state=9
		cue.Init(0,0)
		cue.SetPosition(490,180)
		turnList.RemoveEach(cue)
		pottedList.RemoveEach(cue)
		railAnimation.RemoveCueBall()
		engine.AddBall(cue)
	End
	
	Method ListContainsSolids:Bool(list:List<Ball>)
		For Local b:Ball = Eachin list
			If(b.num<8) Return True
		End
		Return False
	End
	
	Method ListContainsStripes:Bool(list:List<Ball>)
		For Local b:Ball = Eachin list
			If(b.num>8 And b.num<16) Return True
		End
		Return False
	End
	
End

Class EightBall Extends Pool
	Field inacuracy:Float
	Field timeFrame:Float
	Field lastTime:Float
	Field down:Int=0

	Field finalText1:String=""
	Field finalText2:String=""
	
	Method Init()
		Self.Exiting=1
	End
	
	Method New()
		inacuracy=0.4
		engine=New ElasticEngine()
		engine.SetGravity(0.0,0.0)
		engine.SetFriction(0.98)
		ballList=Self.engine.ballList
		arcList=New List<ArcWall>
		pottedList= New List<Ball>
		turnList=New List<Ball>
		tableStorage= New TableStorage()
		tableStorage.GetTable(0,Self.engine,Self.arcList)
		tableImg=media.tableImg
		arrowsImg=media.arrowsImg
		ballImg=media.ballImg
		railAnimation=New RailAnimation()
		railAnimation.ShowStops(0)
		Init()
		player=New Record()
		state=1
		Setup16()
		lastTime = Millisecs()
	End

	Method SetupTimed() Override
		RuntimeError("invald attemp to create 8ball pool timed")
	End
	
	Method SetupPVC() Override
		Self.activePlayer= New Player("Player 1",cue,engine,media.ghostImg,media.ballImg,media.stickImg,media.rotatorImg,media.buttonImg,media.stripImg,media.frameTopImg,media.frameBotImg,media.topImg,media.botImg,media.lrImg,media.meterImg,media.stretchImg,media.sliderImg)
		Self.otherPlayer= New Cpu("Cpu",cue,engine,arcList,media.stickImg,media.ballImg,inacuracy)
	End
	
	Method SetupPVP() Override
		Self.activePlayer=New Player("Player 1",cue,engine,media.ghostImg,media.ballImg,media.stickImg,media.rotatorImg,media.buttonImg,media.stripImg,media.frameTopImg,media.frameBotImg,media.topImg,media.botImg,media.lrImg,media.meterImg,media.stretchImg,media.sliderImg)
		Self.otherPlayer=New Player("Player 2",cue,engine,media.ghostImg,media.ballImg,media.stickImg,media.rotatorImg,media.buttonImg,media.stripImg,media.frameTopImg,media.frameBotImg,media.topImg,media.botImg,media.lrImg,media.meterImg,media.stretchImg,media.sliderImg)
	End
	
	Method InitGame() Override
	End
	
	Method Reset() Override
		For Local b:Ball= Eachin Self.pottedList
			Self.engine.AddBall(b)
			Self.pottedList.RemoveEach(b)
		End
		Self.turnList.Clear()
		Self.railAnimation.Reset()
		For Local b2:Ball = Eachin Self.ballList
			b2.Init(0.0,0.0)
			If(b2.num=1)
				b2.SetPosition(180.8,180.0)
			ElseIf(b2.num=2)
				b2.SetPosition(162.6,170.0)
			ElseIf(b2.num=3)
				b2.SetPosition(162.6,190.0)
			ElseIf(b2.num=4)
				b2.SetPosition(144.4,160.0)
			ElseIf(b2.num=5)
				b2.SetPosition(144.4,200.0)
			ElseIf(b2.num=6)
				b2.SetPosition(126.2,150.0)
			ElseIf(b2.num=7)
				b2.SetPosition(126.2,170.0)
			ElseIf(b2.num=8)
				b2.SetPosition(144.4,180.0)
			ElseIf(b2.num=9)
				b2.SetPosition(126.2,190.0)
			ElseIf(b2.num=10)
				b2.SetPosition(126.2,210.0)
			ElseIf(b2.num=11)
				b2.SetPosition(108.0,140.0)
			ElseIf(b2.num=12)
				b2.SetPosition(108.0,160.0)
			ElseIf(b2.num=13)
				b2.SetPosition(108.0,180.0)
			ElseIf(b2.num=14)
				b2.SetPosition(108.0,200.0)
			ElseIf(b2.num=15)
				b2.SetPosition(108.0,220.0)
			ElseIf(b2.num=16)
				b2.SetPosition(490.0,180.0)
			End
			b2.ResetAnimation()
		Next
		
		Self.state=2
		Self.Exiting=1
		Self.down=False
	
	End
	
	Method AssignBalls()
		For Local b:Ball = Eachin Self.turnList
			If(Self.activePlayer.OwnsSolids())
				If(b.num<=8)
					Self.activePlayer.AddBall(b)
				Else
					If(b.num>8)
						Self.otherPlayer.AddBall(b)
					End
				End
			Else
				If(Self.activePlayer.OwnsStripes())
					If(b.num>=8)
						Self.activePlayer.AddBall(b)
					Else
						Self.otherPlayer.AddBall(b)
					End
				Else
					If(b.num<8)
						Self.activePlayer.SetToSolids()
						Self.otherPlayer.SetToStripes()
						Self.activePlayer.AddBall(b)
					Else
						If(b.num>8)
							Self.activePlayer.SetToStripes()
							Self.otherPlayer.SetToSolids()
							Self.activePlayer.AddBall(b)
						Else
							Self.activePlayer.AddBall(b)
						End
					End
				End
			End
		End
	End
	
	Method ResolveTurn()
		If Self.turnList.Empty
			Self.Exiting=0
			Self.state=10
			Return
		End
		Self.state=3
		If(Self.Exiting=1)
			For Local b:Ball = Eachin turnList
				If(b.num<8)
					activePlayer.SetToSolids()
					otherPlayer.SetToStripes()
					Exit
				End
				If(b.num>8 And b.num<16)
					activePlayer.SetToStripes()
					otherPlayer.SetToSolids()
					Exit
				End
			End
			If ListContains(turnList,cue)
				state=9
				If ListContains(turnList,8)
					state=7
				Else
					RestoreCue()
				End
			Else
				If(ListContains(Self.turnList,8))
					state=6
				End
			End
			For Local b2:Ball = Eachin turnList
				If(activePlayer.OwnsSolids())
					If b2.num<=8
						activePlayer.AddBall(b2)
					Elseif b2.num>8 And b2.num<16
						otherPlayer.AddBall(b2)
					Else
						RestoreCue()
					End
				Else
					If activePlayer.OwnsStripes()
						If b2.num>=8 And b2.num<16
							activePlayer.AddBall(b2)
						Elseif b2.num<8
							otherPlayer.AddBall(b2)
						Else
							RestoreCue()
						End
					ElseIf b2.num=8
						activePlayer.AddBall(b2)
					End
				End
			End
			Self.Exiting=0
		Else
			Local b3:Ball=engine.GetFirstCollision()
			If activePlayer.CompletedSet()=True
				If ListContains(turnList,8)
					state=6
					If ListContains(turnList,cue) state=7
					If activePlayer.OwnsSolids()
						If b3.num>8 And b3.num<16 state=7
					Else
						If b3.num<8 Self.state=7
					End
				Else
					If ListContains(turnList,cue)
						state=7
					Else
						state=10
					End
				End
			Else
				If b3<>Null
					If b3.num<8 And activePlayer.OwnsStripes() state=10
					If b3.num>8 And b3.num<16 And activePlayer.OwnsSolids() state=10
				End
				If activePlayer.OwnsSolids()
					If ListContainsSolids(turnList)=False state=10
				Else
					If activePlayer.OwnsStripes()
						If ListContainsStripes(turnList)=False state=10
					End
				End
				If ListContains(turnList,cue) RestoreCue()
				If ListContains(turnList,8) state=7
				Self.AssignBalls()
			End
		End
		Self.turnList.Clear()
		Return
	End
	
	Method SwitchPlayers()
		Self.user=activePlayer
		Self.activePlayer=otherPlayer
		Self.otherPlayer=user
	End
	
	Method Update:Int() Override
		Local SelfTime:Float = Millisecs()
		timeFrame=(SelfTime-lastTime)/30.0
		lastTime=SelfTime
		Local done:Int=0
		If state=1
			state=2
			activePlayer.SetButtonText("position")
			activePlayer.Init()
		ElseIf state=2
			If Not activePlayer.Positioning()
				state=3
				activePlayer.SetButtonText("Shoot")
				activePlayer.Init()
			End
		ElseIf state=3
			If Not activePlayer.Aiming()
				state=4
			End
		ElseIf state=4
			If Not activePlayer.ShootingAnimating()
				lastTime=(Millisecs())
				state=5
			End
		ElseIf state=5
			engine.Update(timeFrame)
			BallInHole()
			If Not engine.BallsMoving()
				ResolveTurn()
				engine.ClearFirstCollision()
				activePlayer.Init()
			End
		ElseIf state=10 
			SwitchPlayers()
			activePlayer.Init()
			state=3
		ElseIf state=9
			SwitchPlayers()
			activePlayer.SetButtonText("position")
			activePlayer.Init()
			state=2
		ElseIf state=6
			finalText1=activePlayer.name+" WINS GAME"
			finalText2=otherPlayer.name+" LOST GAME"
			state=8
		ElseIf state=7
			finalText1=otherPlayer.name+" WINS GAME"
			finalText2=activePlayer.name+" LOST GAME"
			state=8
		ElseIf state=8
			If Mouse.ButtonDown(MouseButton.Left) down=1
			If Not Mouse.ButtonDown(MouseButton.Left) And down=1 done=1
		Endif 
		railAnimation.Update(timeFrame*2.0)
		Return Not done	
	End Method 
	
	Method Render(canvas:Canvas) Override
		canvas.DrawImage(media.railImg,5.0,360.0,0)
		Self.railAnimation.Render(canvas)
		canvas.Color = New Color(1,1,1)
		canvas.DrawImage(Self.tableImg,0.0,0.0,0)
		Self.engine.Render(canvas)
		canvas.Color = New Color(1,1,1)
		If(state=2)
			canvas.Alpha = .2
			canvas.DrawRect(466.0,37.0,140.0,288.0)
			canvas.Alpha = .3
			canvas.DrawImage(arrowsImg,cue.P.x,cue.P.y,0)
			canvas.Alpha = 1.0
			activePlayer.RenderButton(canvas)
		Elseif state=4 Or state=3
			activePlayer.Render(canvas,1)
		ElseIf state=8
			Text.Draw(canvas,finalText1,200,100)
			Text.Draw(canvas,finalText2,200,150)
		End
		Local x:Float=25.0
		canvas.Color = New Color(1,1,1)
	End
	
End

Class TableStorage
	Field currentTable:Int=0
	Method New()
		Self.currentTable=-1
	End
	Field table:Table
	
	Method GetTable:Table(index:Int,engine:ElasticEngine,arcList:List<ArcWall>)
		If currentTable=index
			Return Self.table
		Else
			If(index<1 And index>-1)
				If index = 0
					engine.RemoveWalls()
					Local wall:Wall[]=New Wall[](New Arc(28.0,28.0,17.0,135.0,315.0,0.0,0.0,media.arcImg,New Color(1,0,0)),
					New Line(41.0,17.0,58.0,34.0,media.lineImg,new Color(1,0,0)),
					New Line(59.0,34.0,296.0,34.0,media.lineImg,new Color(1,0,0)),
					New Line(296.0,33.0,303.0,25.0,media.lineImg,new Color(1,0,0)),
					New Line(303.0,24.0,303.0,19.0,media.lineImg,new Color(1,0,0)),
					New Arc(320.0,18.0,17.0,180.0,360.0,0.0,0.0,media.arcImg,new Color(1,0,0)),
					New Line(338.0,19.0,338.0,24.0,media.lineImg,new Color(1,0,0)),
					New Line(337.0,25.0,345.0,33.0,media.lineImg,new Color(1,0,0)),
					New Line(345.0,34.0,582.0,34.0,media.lineImg,new Color(1,0,0)),
					New Line(583.0,33.0,599.0,17.0,media.lineImg,new Color(1,0,0)),
					New Arc(612.0,28.0,17.0,225.0,405.0,0.0,0.0,media.arcImg,new Color(1,0,0)),
					New Line(624.0,41.0,609.0,57.0,media.lineImg,new Color(1,0,0)),
					New Line(608.0,57.0,608.0,304.0,media.lineImg,new Color(1,0,0)),
					New Line(609.0,305.0,624.0,320.0,media.lineImg,new Color(1,0,0)),
					New Arc(613.0,333.0,17.0,-45.0,135.0,0.0,0.0,media.arcImg,new Color(1,0,0)),
					New Line(599.0,344.0,584.0,328.0,media.lineImg,new Color(1,0,0)),
					New Line(584.0,327.0,345.0,327.0,media.lineImg,new Color(1,0,0)),
					New Line(344.0,328.0,338.0,335.0,media.lineImg,new Color(1,0,0)),
					New Line(338.0,336.0,338.0,341.0,media.lineImg,new Color(1,0,0)),
					New Arc(320.0,342.0,17.0,0.0,180.0,0.0,0.0,media.arcImg,new Color(1,0,0)),
					New Line(303.0,341.0,303.0,336.0,media.lineImg,new Color(1,0,0)),
					New Line(303.0,335.0,296.0,328.0,media.lineImg,new Color(1,0,0)),
					New Line(295.0,327.0,59.0,327.0,media.lineImg,new Color(1,0,0)),
					New Line(58.0,328.0,41.0,344.0,media.lineImg,new Color(1,0,0)),
					New Arc(27.0,333.0,17.0,45.0,225.0,0.0,0.0,media.arcImg,new Color(1,0,0)),
					New Line(16.0,320.0,31.0,305.0,media.lineImg,new Color(1,0,0)),
					New Line(33.0,304.0,33.0,58.0,media.lineImg,new Color(1,0,0)),
					New Line(32.0,57.0,17.0,43.0,media.lineImg,new Color(1,0,0)))
					table=New Table(wall,engine,arcList)
					Return table
				End
			End
		End
		Return Null
	End
End

Global tableStorage:TableStorage

Class Table

	Method New(wall:Wall[],engine:ElasticEngine,arcList:List<ArcWall>)
		Local n:Int=1, t:Int=0
		While(t < wall.Length)
			Local w:Wall=wall[t]
			t=t+1
			If w.name ="Line"
				Local l:Line=Cast<Line>(w)
				If l.image
					engine.AddLineWallImage(l.x1,l.y1,l.x2,l.y2,w.image,New Color(0,0,0))
				Else
					engine.AddLineWallOutline(l.x1,l.y1,l.x2,l.y2,Null,l.color)
				Endif
			ElseIf w.name ="Arc"
				Local a:Arc=Cast<Arc>(w)
				If a.image
					Local w:ArcWall=engine.AddArcWallImage(a.x1,a.y1,a.radius,a.startAngle,a.endAngle,a.image,New Color(1,1,1))
					arcList.AddLast(w)
					w.num=n
					n+=1
				Else
					Local w:ArcWall=engine.AddArcWallOutline(a.x1,a.y1,a.radius,a.startAngle,a.endAngle,a.color)
					If arcList = Null Then RuntimeError("arclist not initialized")
					arcList.AddLast(w)
					w.num=n
					n+=1
				Endif
			ElseIf(w.name ="Circle")

			Endif
		End
	End
End

Class PoolSoloTime Extends Pool
	
	Field blinkOn:Int=0
	Field timed:Int
	Field minutes:Int
	Field seconds:Int
	Field lastTime:Float
	Field timeFrame:Float
	Field blinkTime:Int
	Field blink:Int
	Field oldTime:Int
	
	Field endTime:Int=0
	Field time:Int=0
		
	Field down:Int=0

	Method New()
		Self.engine=New ElasticEngine()
		Self.engine.SetGravity(0.0,0.0)
'		Self.engine.SetFriction(0.970)
		Self.ballList=Self.engine.ballList
		Self.arcList=New List<ArcWall>
		Self.pottedList= New List<Ball>
		Self.turnList= New List<Ball>
		tableStorage= New TableStorage()
		tableStorage.GetTable(0,Self.engine,Self.arcList)
		Self.tableImg=media.tableImg
		Self.arrowsImg=media.arrowsImg
		Self.ballImg=media.ballImg
		Self.railAnimation=New RailAnimation()
		Self.railAnimation.ShowStops(0)
		Self.Exiting=1
		Self.Setup16()
		Self.player=New Record()
		Self.player.SetName("Player")
		Self.blinkOn=0
	End
	
	Method SetupPVC() Override
		RuntimeError("invalid Setup in Solo Play")
	End
	Method SetupPVP() Override
		RuntimeError("invalid Setup in Solo Play")
	End
	
	Method InitTime()
		Self.endTime=Millisecs()+180000
		Self.time=180000
	End
	
	Method SetupTimed() Override
		Self.activePlayer= New Player("",cue,engine,media.ghostImg,  media.ballImg,media.stickImg,media. rotatorImg,media.buttonImg,media.stripImg,  media.frameTopImg,media.  frameBotImg,media.  topImg,media.  botImg,  media.lrImg,  media.meterImg,media.stretchImg,media.sliderImg)
		Self.InitTime()
	End
	
	Method Reset() Override
		For Local b:Ball = Eachin Self.pottedList
			Self.engine.AddBall(b)
			Self.pottedList.RemoveEach(b)
		End
		
		Self.turnList.Clear()
		Self.railAnimation.Reset()
		
		For Local b2:Ball = Eachin Self.ballList
			b2.Init(0.0,0.0)
			If b2.num=1
				b2.SetPosition(180.8,180.0)
			Elseif(b2.num=2)
				b2.SetPosition(162.6,170.0)
			Elseif(b2.num=3)
				b2.SetPosition(162.6,190.0)
			Elseif(b2.num=4)
				b2.SetPosition(144.4,160.0)
			Elseif(b2.num=5)
				b2.SetPosition(144.4,200.0)
			Elseif(b2.num=6)
				b2.SetPosition(126.2,150.0)
			Elseif(b2.num=7)
				b2.SetPosition(126.2,170.0)
			Elseif(b2.num=8)
				b2.SetPosition(144.4,180.0)
			Elseif(b2.num=9)
				b2.SetPosition(126.2,190.0)
			Elseif(b2.num=10)
				b2.SetPosition(126.2,210.0)
			Elseif(b2.num=11)
				b2.SetPosition(108.0,140.0)
			Elseif(b2.num=12)
				b2.SetPosition(108.0,160.0)
			Elseif(b2.num=13)
				b2.SetPosition(108.0,180.0)
			Elseif(b2.num=14)
				b2.SetPosition(108.0,200.0)
			Elseif(b2.num=15)
				b2.SetPosition(108.0,220.0)
			End
			b2.ResetAnimation()
		End
		Exiting=1
	End
	
	Method InitGame() Override
		player.Reset()
		activePlayer.ResetBalls()
		Reset()
		Exiting=1
		state=12
		cue.SetPosition(490.0,180.0)
		InitTime()
	End
	
	Method RestoreCue() Override
		state=9
		cue.Init(0.0,0.0)
		cue.SetPosition(320.0,180.0)
		turnList.RemoveEach(cue)
		pottedList.RemoveEach(cue)
		railAnimation.RemoveCueBall()
		engine.AddBall(cue)
	End
	
	Method ResolveTurn()
		Self.state=3
		If Not turnList.Empty
			For Local b:Ball = Eachin Self.turnList
				If(b.num<16)
					activePlayer.AddBall(b)
				Else
					RestoreCue()
					player.UpdateBallSinRow(Self.scoreLevel)
					scoreLevel=Self.minLevel
				End
			End
			Self.turnList.Clear()
		Else
			Self.scoreLevel=Self.minLevel
		End
		If(Self.activePlayer.CompletedAll()=True)
			player.IncrementCompletedSets()
			activePlayer.ResetBalls()
			Reset()
		End
		Self.Exiting=0
	End

	Method Update:Int() Override
		If(decrementer>0)
			decrementer-=500
			endTime-=500
		End
		If incrementer>0
			incrementer-=200
			endTime+=500
			timed+=500
			If(timed>=2000)
				media.PlayBeep()
				timed=0
			End
		End
		time= (endTime-Millisecs())/1000
		minutes= time/60
		seconds=time Mod 60
		Local SelfTime:Float= Millisecs()
		timeFrame=(SelfTime-lastTime)/30.0
		lastTime=SelfTime
		If time<=0
			player.UpdateBallSinRow(Self.scoreLevel)
			state=6
			blinkOn=0
		Else
			If time<=10
				blinkOn=1
				If Millisecs()>= blinkTime+300
					blink = Not (blink<>0)
					blinkTime = Millisecs()
				End
				If time<oldTime media.PlayBeepB()
				oldTime = time
			Else
				oldTime=time
				blinkTime=Millisecs()
				blinkOn=0
			End
		End
		Local done:Int=0
		If state=12
			state = 1
			Local t_7:Int=inputName.Update()
			If(t_7=-1)
				Return 0
			Else
				If(t_7=0)
					player.SetName(inputName.GetText())
					state=1
				End
			End
		Elseif state=1
			state=2
			activePlayer.SetButtonText("position")
			activePlayer.Init()
		Elseif state=2
			If activePlayer.Positioning()=False
				state=3
				activePlayer.SetButtonText("Shoot")
				activePlayer.Init()
				InitTime()
			End
		Elseif state=3
			If activePlayer.Aiming()=False state=4
		Elseif state=4
			If activePlayer.ShootingAnimating()=False state=5
		Elseif state=5
			engine.Update(timeFrame)
			BallInHole()
			If engine.BallsMoving()=False
				ResolveTurn()
				engine.ClearFirstCollision()
				activePlayer.Init()
			End
		Elseif state=9
			activePlayer.SetButtonText("Shoot")
			activePlayer.Init()
			state=3
		Elseif state=6
			If Mouse.ButtonDown(MouseButton.Left)<>0 down=1
			If Mouse.ButtonDown(MouseButton.Left)=0 And down=1
				down=0
				done=1
			End
		Elseif state=8
		Endif
		Self.railAnimation.Update(timeFrame*3.0)
		Return Not done
	End
	
	Method Render(canvas:Canvas) Override	
		canvas.DrawImage(media.railImg,5.0,360.0,0)
		railAnimation.Render(canvas)
		canvas.Color = New Color(1,1,1)
		canvas.DrawImage(tableImg,0.0,0.0,0)
		engine.Render(canvas)
		If(state=12)
			canvas.Color = New Color(1,1,1)
			inputName.Render(canvas)
		Elseif(state=2)
			canvas.Alpha = .2
			canvas.DrawRect(466.0,37.0,140.0,288.0)
			canvas.Alpha = .3
			canvas.DrawImage(arrowsImg,cue.P.x,cue.P.y,0)
			canvas.Alpha = 1.0
			activePlayer.RenderButton(canvas)
		ElseIf(state=4 Or state=3)
			If decrementer>0
				canvas.Color = New Color(1,.4,0)
			Else
				canvas.Color = New Color(1,1,1)
			End
			Local sec:String=String(seconds)
			If(sec.Length = 1) sec="0"+sec
			If blinkOn
				If blink Text.Draw(canvas,"Time Left       "+String(minutes)+":"+sec,400,370)
			Else
				Text.Draw(canvas,"Time Left       "+String(minutes)+":"+sec,400,370)
			End
			canvas.Color = New Color(1,1,1)
			Text.Draw(canvas,"Score           "+String(player.score),400,400)
			Text.Draw(canvas,"Multiplier 100 x"+String(scoreLevel),400,430)
			activePlayer.Render(canvas,0)
		ElseIf(state=5)
			If decrementer > 0
				canvas.Color = New Color(1,.4,0)
			Else
				canvas.Color = New Color(1,1,1)
			End
			Local sec2:String=String(seconds)
			If sec2.Length=1  sec2="0"+sec2
			If blinkOn<>0
				If blink Text.Draw(canvas,"Time Left       "+String(minutes)+":"+sec2,400,370)
			Else
				Text.Draw(canvas,"Time Left       "+String(minutes)+":"+sec2,400,370)
			End
			canvas.Color = New Color(1,1,1)
			Text.Draw(canvas,"Score           "+String(player.score),400,400)
			Text.Draw(canvas,"Multiplier 100 x"+String(scoreLevel),400,430)		
		ElseIf(state=6)
			Local tx:Int=120
			Local ty:Int=100
			canvas.Alpha = .7
			canvas.Color = New Color(.2,0,1)
			canvas.DrawRect(tx-20,ty-20,400.0,240.0)
			canvas.Alpha = 1.0
			canvas.Color = New Color(1,1,1)
			canvas.DrawText("Name                       "+player.name,tx,ty+0,0.0,0.0)
			canvas.DrawText("Score                      "+String(player.score),tx,ty+30,0.0,0.0)
			canvas.DrawText("completed Sets             "+String(player.mostCompletedSets),tx,ty+60,0.0,0.0)
			canvas.DrawText("Most Balls In A Row        "+String(player.mostBallSinRow),tx,ty+90,0.0,0.0)
			canvas.DrawText("Most Pocketed              "+String(player.mostPocketed),tx,ty+120,0.0,0.0)
			canvas.DrawText(" Press to exit             ",tx+100,ty+170,0.0,0.0)
		ElseIf(state=8)

		End
	End
End


Global scoreTableVsTime:ScoreTable

Class User
	Field ballList:List<Ball>

	Field cue:Ball
	Field position:PVector2D
	Field ballImg:Image
	Field ghostImg:Image[]
	Field cueStick:CueStick
	Field name:String=""
	Global firstShot:Int
	Field completedSet:Int=0
	Field engine:ElasticEngine
	Field ghostBall:GhostBall
	Field control:Control
	Field button:Button2
	Field ballOwnerType:Int=0
	Field angle:Float
	Field oldAngle:Float
	
	Method New()
		ballList=New List<Ball>
	End
	
	Method SetButtonText(str:String) Virtual
		Return
	End
	
	Method Init() Abstract
	Method Positioning:Bool() Abstract
	Method Aiming:Bool() Abstract

	Method ShootingAnimating:Bool() Abstract

	Method SetToSolids()
		ballOwnerType=2
	End

	Method SetToStripes()
		ballOwnerType=1
	End
	Method OwnsSolids:Bool()
		Return ballOwnerType=2
	End
	
	Method AddBall(b:Ball)
		Self.ballList.AddLast(b)
	End

	Method OwnsStripes:Bool()
		Return Self.ballOwnerType=1
	End
	
	Method CompletedSet:Bool()
		Return Self.ballList.Count()=7
	End
	
	Method RenderButton(canvas:Canvas) Abstract

	Method Render(canvas:Canvas,state:Int) Virtual
		canvas.Color = New Color(0.0,0.0,0.0)
		Text.Draw(canvas, name,544,371)
		canvas.Color = New Color(1,1,1)
		Text.Draw(canvas,Self.name,545,370)
		Local lowy:Float=370.0
		Local hiy:Float=371.0
		Local lowx:Float=400.0
		Local hix:Float=401.0
		Local t_1:Int=ballOwnerType
		
		If ballOwnerType = 2
			canvas.Color = New Color(0,0,0)
			Text.Draw(canvas,"SOLIDS",lowx,hiy)
			canvas.Color = New Color(1,1,1)
			Text.Draw(canvas,"SOLIDS",hix,lowy)
		ElseIf ballOwnerType = 1
			canvas.Color = New Color(0,0,0)
			Text.Draw(canvas,"STRIPES",lowx,hiy)
			canvas.Color = New Color(1,1,1)
			Text.Draw(canvas,"STRIPES",hix,lowy)
		Else
			canvas.Color = New Color(0.0,0.0,0.0)
			Text.Draw(canvas,"Game Is Open",lowx,hiy)
			canvas.Color = New Color(1,1,1)
			Text.Draw(canvas,"Game Is Open",hix,lowy)
		End
	End
	
	Method ResetBalls()
		Self.ballList.Clear()
	End
	
	Method CompletedAll:Bool()
		Return Self.ballList.Count()=15
	End
	
End Class

Class Player Extends User
	
	Field oldTouch:Int=0
	Field oldMouseDown:Int=0
	Field oldMouseX:Int=0
	Field oldMouseY:Int=0
	Field rotatorImg:Image
	
	Method New(name:String,cue:Ball,engine:ElasticEngine,t_ghostImg:Image[],ballImg:Image,stickImg:Image[],rotatorImg:Image,buttonImg:Image[],stripImg:Image,frameTopImg:Image[],frameBotImg:Image[],topImg:Image,botImg:Image,lrImg:Image[],meterImg:Image,stretchImg:Image,sliderImg:Image)
		Self.cue=cue
		Self.position=cue.P
		Self.ballImg=ballImg
		Self.ghostImg=t_ghostImg
		Self.cueStick=New CueStick(cue.P,cue.radius+1.0,stickImg,180.0)
		Self.name=name
		User.firstShot=1
		Self.completedSet=0
		Self.engine=engine
		Self.ghostBall=New GhostBall(cue.P,cue.radius,t_ghostImg,180.0,stripImg)
		Self.control=New Control(cue,5,420,.5,meterImg,stretchImg,sliderImg,40)
		Self.oldTouch=0
		Self.button=New Button2(buttonImg,360,400,"shoot",Null)
		Self.rotatorImg = rotatorImg
	End

	Method Init() Override
		ghostBall.dx=Cos(cueStick.angle)
		ghostBall.dy=Sin(cueStick.angle)
		cueStick.SetAngle(cueStick.angle)
		engine.CollisionDistance2Ghost(ghostBall)
	End
	
	Method Positioning:Bool() Override
		button.Update()
		If button.GetState()
			Local overlapping:Int=0
			For Local b:Ball = Eachin engine.ballList
				If b=cue Continue
				Local vx:Float=Self.cue.P.x-b.P.x
				Local vy:Float=Self.cue.P.y-b.P.y
				If(vx*vx+vy*vy<=4.0*b.radius*b.radius)
					overlapping=1
				End
			End
			If overlapping=0 Return False
		End
		If Mouse.ButtonDown(MouseButton.Left)
			If oldMouseDown
				engine.CollisionDistance2Ghost(Self.ghostBall)
				cue.P.x+=Mouse.X-(oldMouseX)
				cue.P.y+=Mouse.Y-(oldMouseY)
				If cue.P.x<476.0 cue.P.x=476.0
				If cue.P.x>596.0 cue.P.x=596.0
				If cue.P.y<47.0  cue.P.y=47.0
				If cue.P.y>315.0 cue.P.y=315.0
			End
		End
		oldMouseDown=Mouse.ButtonDown(MouseButton.Left)
		oldMouseX=Mouse.X
		oldMouseY=Mouse.Y
		Return True
	End
	
	Method SetButtonText(str:String) Override
		button.SetText(str)
	End
	
	Method Aiming:Bool() Override
		If control.Update()
			angle=control.angle
			cueStick.SetAngle(angle)
			If control.Length<0.0
				cueStick.SetDistance(0.0)
			Else
				If control.Length>40.0
					cueStick.SetDistance(40.0)
				Else
					cueStick.SetDistance(control.Length)
				End
			End
			ghostBall.dx=Cos(angle)
			ghostBall.dy=Sin((angle))
			engine.CollisionDistance2Ghost(ghostBall)
			oldAngle=angle
		Else
			If(control.Length>0.0)
				cueStick.SetAnimation2()
				control.Length=0.0
				Return False
			End
		End
		Return True
	End
	
	Method ShootingAnimating:Bool() override
		If cueStick.Update()=0
			cue.Init(cueStick.dx*40.0*control.volume,cueStick.dy*40.0*control.volume)
			media.PlayShootCol()
			Return False
		End
		Return True
	End
	
	Method RenderButton(canvas:Canvas) Override
		button.Render(canvas)
	End
	
	Method Render(canvas:Canvas,status:Int) Override
		control.Render(canvas)
		canvas.DrawImage(rotatorImg,position.x,position.y,-angle-1.6,1.0,1.0)
'		If status Render(canvas,1)
		ghostBall.Render(canvas)
		cueStick.Render(canvas)
	End
End

Class CueStick
	Field position:PVector2D
	Field len:Float=.0
	Field image:Image[]
	Field rotatorImg:Image
	Field offset:Float=.0
	Field angle:Float=.0
	Field dx:Float=.0
	Field dy:Float=.0
	Field offsetx:Float=.0
	Field offsety:Float=.0
	Field distance:Float=.0
	Field animStep:Float=.0
	Field animx:Float=.0
	Field animy:Float=.0
	Field animAngle:Float=.0
	Field animDelay:Int=0
	Field power:Float=.0
	
	Method SetAngle(ang:Float)
		If ang<>angle
			angle=ang
			dx=Cos(angle)
			dy=Sin(angle)
			offsetx=-dx*len
			offsety=-dy*len
		End
	End
	
	Method New(pos:PVector2D,offset:Float,image:Image[],angle:Float)
		Self.position=pos
		Self.len=offset
		Self.image=image
		Self.offset=offset
		Self.SetAngle(angle)
		Self.rotatorImg = rotatorImg
	End

	Method SetDistance(d:Float)
		distance=d
		animStep=30.0
		animx=-dx*distance
		animy=-dy*distance
	End

	Method SetAnimation2()
		animAngle=0
		animDelay=Millisecs()+1
	End

	Method Update:Int()
		If animDelay<Millisecs()
			If animAngle >= 90.0
				animx=0.0
				animy=0.0
				distance=0.0
				animAngle=0.0
				Return 0
			Else
				Local Length:Float=Cos(animAngle*ATR)* distance
				animx=-dx*Length
				animy=-dy*Length
				If animAngle < 90.0 animAngle += animStep
			End
			animDelay=Millisecs()+1
		End
		Return 1
	End

	Method Render(canvas:Canvas)
		canvas.Color = New Color(1,1,1)
		Local x:Float=position.x+offsetx+animx
		Local y:Float=position.y+offsety+animy
		canvas.DrawImage(image[0],x,y,-angle,1.0,1.0)
	End

	Method SetAngleCpu(ang:Float)
		If ang<>Self.angle
			angle=ang
			dx=Cos(angle)
			dy=Sin(angle)
			offsetx=-dx*len
			offsety=-dy*len
		End
	End

	Method Init(d:Float)
		animStep=d/4.0
		animx=0.0
		animy=0.0
	End
	
	Method UpdateCpu:Int()
		If(Self.animDelay<Millisecs())
			If(animAngle>=90.0)
				animx=0.0
				animy=0.0
				animAngle=0.0
				Return 0
			Else
				Local Length:Float=-Sin(animAngle*ATR)*30.0
				animx=Length*dx
				animy=Length*dy
				If animAngle>90.0
					Local pwr:Float = power/4.0
					If pwr<1.0 pwr=1.0
					animAngle += animStep*pwr
				Else
					animAngle += animStep
				End
			End
			animDelay=Millisecs()+1
		End
		Return 1
	End
End

Class Control
	Field x:Int
	Field y:Int
	Field width:Float
	Field height:Float
	Field meterImg:Image
	Field stretchImg:Image
	Field sliderImg:Image
	Field volume:Float
	Field sliderx:Int
	Field framed:Int
	Field active:Int
	Field oldMouseDown:Int
	Field maxValue:Float
	Field stp:Float
	Field cue:Ball
	
	Field topLRImg:Image[]
	Field botLRImg:Image[]
	Field midTopImg:Image
	Field midBotImg:Image
	Field midLRImg:Image[]
	Field tw:Float
	Field th:Float
	
	Field x2:Float
	Field vx:Float
	Field y2:Float
	Field vy:Float
	Field dx:Float
	Field dy:Float
	Field Length:Float
	Field activeVolume:Float
	Field angle:Float
	
	Method New(cue:Ball,x:Int,y:Int,volume:Float,meterImg:Image,stretchImg:Image,sliderImg:Image,maxValue:Int)
		Self.x=x
		Self.y=y
		Self.width= meterImg.Width
		Self.height= meterImg.Height
		Self.meterImg=meterImg
		Self.stretchImg=stretchImg
		Self.sliderImg=sliderImg
		Self.stretchImg=stretchImg
		If volume>1.0 volume=1.0
		If volume<0.0 volume=0.0 
		Self.volume=volume
		Self.sliderx= volume*Self.width
		Self.framed = 0
		Self.active = 0
		Self.oldMouseDown = 0
		Self.maxValue=(maxValue)
		Self.stp=Self.width/maxValue
		Self.cue=cue
	End

	Method SetFrame(tlrImg:Image[],blrImg:Image[],mtImg:Image,mbImg:Image,mlrImg:Image[])
		Self.topLRImg=tlrImg
		Self.botLRImg=blrImg
		Self.midTopImg=mtImg
		Self.midBotImg=mbImg
		Self.midLRImg=mlrImg
		Self.tw= tlrImg[0].Width
		Self.th= tlrImg[0].Height
		Self.framed=1
	End
	
	Method Update:Int()
		Local state:Int=1
		If Mouse.ButtonDown(MouseButton.Left)
			If Self.oldMouseDown
				Self.vx=Mouse.X-Self.x2
				Self.vy=Mouse.Y-Self.y2
				Self.Length=Self.vx*-Self.dx+Self.vy*-Self.dy
				If(Self.Length>Self.maxValue)
					Self.volume=Self.maxValue*Self.stp/Self.width
				Else
					If(Self.Length<0.0)
						Self.volume=0.0
					Else
						Self.volume=Self.Length*Self.stp/Self.width
					End
				End
			Else
				Self.x2=Mouse.X
				Self.y2=Mouse.Y
			End
		Else
			If Self.oldMouseDown
				Self.vx=Mouse.X-Self.x2
				Self.vy=Mouse.Y-Self.y2
				Self.Length=Self.vx*-Self.dx+Self.vy*-Self.dy
				If(Self.Length>Self.maxValue And Self.Length>=0.0)
					Self.volume=Self.maxValue*Self.stp/Self.width
				Else
					If(Self.Length<0.0)
						Self.volume=0.0
					Else
						Self.volume=Self.Length*Self.stp/Self.width
					End
				End
				Self.oldMouseDown=Mouse.ButtonDown(MouseButton.Left)
				Return 0
			Else
				Self.volume=Self.activeVolume
				Self.vx=Mouse.X-Self.cue.P.x
				Self.vy=Mouse.Y-Self.cue.P.y
				Self.angle=(ATan2(Self.vy,Self.vx))
				Self.dx=Cos((Self.angle))
				Self.dy=Sin((Self.angle))
			End
		End
		Self.oldMouseDown=Mouse.ButtonDown(MouseButton.Left)
		Self.sliderx=((Self.volume*Self.width))
		Return 1
	End
	
	Method Render(canvas:Canvas)
		If framed
			Local px:Float=x-tw
			Local py:Float=y-th
			canvas.DrawImage(topLRImg[0],px,py)
			canvas.DrawImage(midTopImg,px+tw,py,0.0,width,1.0)
			canvas.DrawImage(topLRImg[1],px+width+tw,py)
			canvas.DrawImage(midLRImg[0],px,py+th,0.0,1.0,height)
			canvas.DrawImage(midLRImg[1],px+tw+width,py+th,0.0,1.0,height)
			canvas.DrawImage(botLRImg[0],px,py+th+height)
			canvas.DrawImage(midBotImg,px+tw,py+th+height,0.0,width,1.0)
			canvas.DrawImage(botLRImg[1],px+tw+width,py+th+height)
		End
		canvas.DrawImage(meterImg,x,y,0)
		Local w:Float=(1.0-volume)*width
		canvas.DrawImage(stretchImg,x+sliderx,y,0.0,w,1.0)
		canvas.DrawImage(sliderImg,x+sliderx,y,0)
		Text.Draw(canvas,"POWER",x+50,y+10)
	End
End

Class Cpu Extends User
	Field pocketList:List<ArcWall>
	Field activeBallList:List<Ball>
	Field aimWait:Int=0
	Field delay:Int=0
	Field inacuracy:Float=.0
	Field power:Float=.0

	Method New(name:String,cue:Ball,engine:ElasticEngine,arcList:List<ArcWall>,stickImg:Image[],ballImg:Image,inacuracy:Float)
		Self.cue=cue
		Self.position=cue.P
		Self.cueStick= New CueStick(cue.P,cue.radius+1.0,stickImg,180.0)
		Self.ballImg=ballImg
		Self.pocketList=arcList
		Self.activeBallList=engine.ballList
		Self.aimWait=100
		Self.delay=Millisecs()+Self.aimWait
		Self.inacuracy=inacuracy
		Self.name=name
		Self.engine=engine
	End

	Method Init() Override
		
	End
	
	Method Positioning:Bool() Override
		Repeat
			cue.P.x=Rnd(476,596)
			cue.P.y=Rnd( 47,315)
			Local overlapped:Int=0
			For Local b:Ball = Eachin engine.ballList
				If b=cue
					Continue
				End
				Local vx:Float=b.P.x-Self.cue.P.x
				Local vy:Float=b.P.y-Self.cue.P.y
				If (vx*vx+vy*vy<=4.0*b.radius*b.radius)
					overlapped=1
					Exit
				End
			End
			
			If overlapped=0 Exit
		Forever
		cue.Init(0.0,0.0)
		Return False
	End
	
	Method Get8Ball:Ball()
		For Local b:Ball = Eachin activeBallList
			If(b.num=8)
				Return b
			End
		End
		Return Null
	End
	
	Method PathToPocket:Bool(b1:Ball,dx:Float,dy:Float)
		For Local b2:Ball = Eachin Self.activeBallList
			If(b2=b1 Or b2=Self.cue)
				Continue
			End
			Local vx:Float=b2.P.x-b1.P.x
			Local vy:Float=b2.P.y-b1.P.y
			Local dp:Float=vx*dy-vy*dx
			If(Abs(dp)<b1.radius+b2.radius)
				Local dp2:Float=vx*dx+vy*dy
				If(dp2>0.0)
					Return False
				End
			End
		End
		Return True
	End
	
	Method PathToBall:Bool(b1:Ball,dx:Float,dy:Float,skipBall:Ball)
		Local vx:Float=skipBall.P.x-b1.P.x
		Local vy:Float=skipBall.P.y-b1.P.y
		Local len:Float=vx*dx+vy*dy
		For Local b3:Ball = Eachin activeBallList
			If(b3=b1 Or b3=skipBall) Continue
			Local vx2:Float=b3.P.x-b1.P.x
			Local vy2:Float=b3.P.y-b1.P.y
			Local dp:Float=vx2*dy-vy2*dx
			If(Abs(dp)<b1.radius+b3.radius)
				Local dp2:Float=vx2*dx+vy2*dy
				If(dp2>0.0 And dp2<Abs(len)) Return False
			End
		End
		Return True
	End

	Method FindBestPocket:ArcWall(ball:Ball)
		Local distance:Float=INVALID_DISTANCE
		Local pocket:ArcWall
		For Local arc:ArcWall = Eachin pocketList
			Local dx1:Float
			Local dy1:Float
			Local vx1:Float=arc.target.x-ball.P.x
			Local vy1:Float=arc.target.y-ball.P.y
			Local vx2:Float=cue.P.x-ball.P.x
			Local vy2:Float=cue.P.y-ball.P.y
			Local dp:Float=vx1*vx2+vy1*vy2
			If(dp<0.0)
				Local d1:Float=Sqrt(vx1*vx1+vy1*vy1)
				If(d1>0.0)
					dx1=vx1/d1
					dy1=vy1/d1
				End
				If(d1=0.0 Or Self.PathToPocket(ball,dx1,dy1))
					Local px:Float=ball.P.x-dx1*(arc.radius+ball.radius)
					Local py:Float=ball.P.y-dy1*(arc.radius+ball.radius)
					vx1=px-cue.P.x
					vy1=py-cue.P.y
					d1=Sqrt(vx1*vx1+vy1*vy1)
					Local ang:Float=(ATan2(vy1,vx1))
					If(PathToBall(cue,Cos((ang)),Sin((ang)),ball))
						If(d1<distance)
							distance=d1
							angle=ang
							pocket=arc
						End
					End
				End
			End
		End
		Return pocket
	End

	Method GetRndSolidBall:Ball()
		Local counter:Int=0
		For Local b:Ball = Eachin activeBallList
			If(b.num<8)
				counter+=1
			Else
				Continue
			End
		End
		If counter
			If counter>1 counter=Rnd(1.0,(counter+1))
			Local n:Int=1
			For Local b2:Ball = Eachin activeBallList
				If b2.num < 8
					If(n=counter) Return b2
					n+=1
				Endif
			End
		End
		Return Null
	End

	Method GetRndStripedBall:Ball()
		Local counter:Int=0
		Local low:Int=0
		For Local b:Ball = Eachin activeBallList
			If(b.num>=8 And b.num<16)
				counter+=1
			Else
				low+=1
			End
		End
		counter=(((low)+Rnd(1.0,(counter+1))))
		Local n:Int=1
		For Local b2:Ball = Eachin activeBallList
			If n=counter Return b2
			n+=1
		End
		Return Null
	End

	Method GetRndBall:Ball()
		Local counter:Int=Self.activeBallList.Count()
		counter=((Rnd(0.0,(counter-1))))
		Local n:Int=0
		For Local b:Ball = Eachin activeBallList
			If n=counter Return b
			n+=1
		End
		Return Null
	End
	
	Method Aiming:Bool() Override
		Local vx:Float
		Local vy:Float
		If ballList.Count() = 7
			Local b:Ball=Get8Ball()
			Local pocket:ArcWall=FindBestPocket(b)
			If pocket
				vx=b.P.x-pocket.target.x
				vy=b.P.y-pocket.target.y
				Local len:Float=Sqrt(vx*vx+vy*vy)
				Local px:Float=b.P.x+vx/len*(b.radius+cue.radius)
				Local py:Float=b.P.y+vy/len*(b.radius+cue.radius)
				vx=px-cue.P.x
				vy=py-cue.P.y
			Else
				vx=b.P.x-cue.P.x
				vy=b.P.y-cue.P.y
			End
		Else
			Local ball:Ball
			Local pocket2:ArcWall
			Local distance:Float=INVALID_DISTANCE
			For Local b2:Ball = Eachin activeBallList
				If(ballOwnerType=2 And b2.num>7) Continue
				If(ballOwnerType=1 And b2.num<9) Continue
				If(b2.num=8 Or b2=cue) Continue
				
				Local pkt:ArcWall=FindBestPocket(b2)
				If pkt
					vx=pkt.target.x-b2.P.x
					vy=pkt.target.y-b2.P.y
					Local ln:Float=Sqrt(vx*vx+vy*vy)
					If(ln<distance)
						distance=ln
						pocket2=pkt
						ball=b2
					End
				End
			End
			
			If distance < INVALID_DISTANCE
				vx=ball.P.x-pocket2.target.x
				vy=ball.P.y-pocket2.target.y
				angle= ATan2(vy,vx)
				Local px2:Float = ball.P.x+Cos(angle)*(cue.radius+ball.radius)
				Local py2:Float = ball.P.y+Sin(angle)*(cue.radius+ball.radius)
				vx=px2-cue.P.x
				vy=py2-cue.P.y
			Else
				Local t:Int=Self.ballOwnerType
				If t = 2
					ball = GetRndSolidBall()
				Elseif t = 1
					ball=GetRndStripedBall()
				Else
					ball=GetRndBall()
				End
				If ball
					vx=ball.P.x-cue.P.x 
					vy=ball.P.y-cue.P.y
				Else
					vx = Cos(cueStick.angle)
					vy = Sin(cueStick.angle)
				Endif
			End
		End
		angle=ATan2(vy,vx)
		cueStick.SetAngleCpu(angle)
		power=Rnd(10.0,50.0)
		cueStick.Init(power)
		Return False
	End
	
	Method SetButtonText(str:String) Override
	End
	
	Method ShootingAnimating:Bool() Override
		If Self.cueStick.UpdateCpu()=0
			cue.Init(Self.cueStick.dx*power,cueStick.dy*power)
			Return False
		End
		Return True
	End
	
	Method RenderButton(canvas:Canvas) Override
	End
	
	Method Render(canvas:Canvas,status:Int) Override
		If status Super.Render(canvas,1)
		cueStick.Render(canvas)
	End
End