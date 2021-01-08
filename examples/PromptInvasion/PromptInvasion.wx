#Import "<mojo>"
#Import "<std>"
#Import "font"
#Import "vector"

#Import "data/aliens.png"
'#Import "asset::background.png"

#Import "data/chalky.fnt"
#Import "data/chalky.png"

#Import "data/shoota.ogg"
#Import "data/hita.ogg"
#Import "data/Fireball.ogg"
#Import "data/hit.ogg"
#Import "data/explosion.ogg"
#Import "data/bomb0.ogg"
#Import "data/laser.ogg"
#Import "data/woop.ogg"
#Import "data/kickshock.ogg"

Using mojo..
Using std..

Function Main()
	New AppInstance
	
	New Game
	
	App.Run()
End

Const  ATR := 3.14159265/180.0
Global currentTime:Int

Global activeStage:StageBase
Global nextStage:StageBase

Global introStage:Intro
Global menuStage:Menu
Global gameStage:GalVadors
Global optionsStage:Options
Global creditsStage:Credits
Global player:Player

Global enemyBulletList := New List<Bullet>
Global playerBulletList := New List<Bullet>
Global explosionList := New List<Explosion>
Global shipParticleList := New List<Particle>
Global aparticleList:List<ParticleA>
Global specialList:List<Special>

Global bulletStore := New BulletStore(150)
Global explosionStore := New ExplosionStore(50)
Global particleStore := New ParticleStore(50)
Global aparticleStore:AParticleStore

Global media:Media

Global score:Int
Global hiScore:Int

Global mousex:Int
Global mousey:Int
Global mouseDown:Int

Global lapsedTime:Int

Global DeviceWidth:Int
Global DeviceHeight:int

Class Game Extends Window
	
	Field stars:Stars

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )
		Super.New( title,width,height,flags )
		DeviceWidth = width
		DeviceHeight = height
		media = New Media
		introStage = New Intro
		activeStage = introStage
		nextStage = activeStage
		
		Local tstl:Font= SetAFont("chalky")
		aparticleList =New List<ParticleA>
		aparticleStore = New AParticleStore(20)
		stars = New Stars()
		
		SwapInterval=1
	End

	Method OnRender( canvas:Canvas ) Override
	
		mousex = Mouse.X
		mousey = Mouse.Y
		mouseDown = Mouse.ButtonDown(MouseButton.Left)

		currentTime = Millisecs()
		
		If activeStage <> nextStage
			activeStage = nextStage
		Endif
		activeStage.Update()
		stars.Update()

		App.RequestRender()
		canvas.Clear(New Color(0,0,0))
		stars.Render(canvas)
		activeStage.Render(canvas)
		canvas.DrawImage(media.trailImg[0],50,50)
	End
	
End

Class StageBase
	
	Method Update:Void() Abstract
	Method Render:Void(canvas:Canvas) Abstract
	
End Class

Class Intro Extends StageBase
	
	Field startTime:Int
	Field delayAmount:Int
	Field oldScape:Int
	Field image:Image
	
	Method New()
		image = media.alienImg
		Init()
	End Method
	
	Method Init:Void()
		startTime = currentTime
		delayAmount = 2000
	End Method
	
	Method Update:Void() override
		Local scape:Int = Keyboard.KeyDown(Key.Escape) Or Mouse.ButtonDown(MouseButton.Left)
		If currentTime > startTime+delayAmount Or (oldScape And Not scape)
			If Not menuStage
				menuStage = New Menu
			Endif
			nextStage = menuStage
		Endif
		oldScape = scape
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawImage(image,150,100)
		RenderText(canvas,"  PROMPT INVASION",190,230)
	End Method
	
End Class
	
Class Menu Extends StageBase

	Field index:Int
	Field totalOptions:Int
	Field options:String[]
	
	Field hoverColor:Color
	Field defaultColor:Color
	Field clickColor:Color
	Field inactiveColor:Color
	Field currentColor:Color
	
	Field oldMouseDown:Int
	Field alienImg:Image
	
	Const cINTRO:Int = 0
	Const cPLAY:Int = 1
	Const cCONTINUE:Int = 2
	Const cSCORESTABLE:Int = 3
	Const cOPTIONS:Int = 4
	Const cCREDITS:Int = 5
	
	Field px:Float
	Field py:Float
	
	Method New()
		
		totalOptions = 2
		options = New String[totalOptions]
		options[cINTRO] =    "    INTRO"
		options[cPLAY] =     "PLAY GAME"
		
		defaultColor = New Color(1,1,1) 	'$FFFFFF
		hoverColor = New Color(1,1,0) 		'$FFFF00
		clickColor = New Color(0,1,0) 		'$00ff00
		inactiveColor =  New Color(.5,.5,.5)'$888888
		currentColor = New Color(1,1,1) 	'$FFFFFF
		index = -1
	End Method
	
	Method Update:Void() Override
		px = mousex - 200
		py = mousey - 150
		index = -1
		Local y:Int = py / 40.0
		currentColor = defaultColor
		If y >= 0 And y < totalOptions
			Local n:Int = py Mod 40.0
			If n >= 0 And n < 45 And px > 0 And px < 200
				currentColor = hoverColor
				index = y
				If mouseDown
					currentColor = clickColor
				Endif
			Endif
		Endif
		If oldMouseDown And Not mouseDown
			If index > - 1
				Select index
					Case cINTRO
						nextStage = introStage
						introStage.Init()
					Case cPLAY
						gameStage = New GalVadors
						nextStage = gameStage
				End Select
			Endif
		Endif	
		oldMouseDown = mouseDown
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawImage(media.alienImg,150,100)
		RenderText(canvas,"MENU",270,50)
		For Local i:Int = 0 Until totalOptions
			If i = cCONTINUE
				If i = index 
					If 	gameStage
						canvas.Color = currentColor
					Else
						canvas.Color = inactiveColor
					Endif
				Elseif gameStage
					canvas.Color = defaultColor
				Else
					canvas.Color = inactiveColor
				Endif
			Elseif i = index
				canvas.Color = currentColor
			Else
				canvas.Color = New Color(1,1,1) ' 255,255,255
			Endif
			RenderText(canvas,options[i],240,150+i*40)
		Next
		canvas.Color = New Color(1,1,0) '255, 255,  0
		RenderText(canvas,"Music by Kevin MacLeod - incompetech.com",50,400)
		RenderText(canvas,"controlls Z, Left, Right",150,430)
		canvas.Color = New Color(1,1,1) '255,255,255
	End Method

End Class

Class GalVadors Extends StageBase
	Field oldScape:Int
	Field wave:Wave
	Field shipExplosionImg:Image
	Field explosionImg:Image
	Field gameTimer:Timer
	Field meteorList:List<Meteor>
	Field passedLevel:Int
	Field trailImg:Image
	Field Level:Int
	Field ufo:Ufo

	Method New()
		
		player = New Player()

		wave = New Wave(0)

		meteorList = New List<Meteor>
		
		For Local i:Int = 0 Until 10
			Local m:Meteor = New Meteor(Rnd(-16,656),Rnd(-16,494),Rnd(0,360),Rnd(1,5))
			meteorList.AddLast(m)
		Next
		
		gameTimer = New Timer(60000,10,10)
		
		ufo = New Ufo(-50,50)

		media.PlayTune()

		passedLevel = False

		specialList = New List<Special>

		score = 0
		Level = 0
		
	End Method
	
	Method Update:Void() Override


		player.Update()
		UpdateBullets()
		wave.Update()
		If player.state <> player.DEAD
			ProcessCollisions()
		Endif

		ProcessExplosions()
		If player.state <> player.PASSEDLEVEL And player.state <> player.DEAD
			If KilledAll() = True
				If wave.level < 5
					passedLevel = True
					player.state = player.PASSEDLEVEL
				Else
					player.state = player.PASSEDGAME
				Endif
			Elseif gameTimer.Update() = False
				player.state = player.DEAD
			Endif
		Endif
		
		If Not aparticleList.Empty
			Local node := aparticleList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				If node.Value.Update()
					node.Remove()
					aparticleStore.ReturnItem(node.Value)
				Endif
				node = nextNode
			Wend
		Endif
		
		For Local m:Meteor = Eachin meteorList
			m.Update()
		Next

		If Not specialList.Empty
			Local node := specialList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				Local s := node.Value
				If s.Update() = False
					node.Remove()
				Endif
				node = nextNode
			Wend
		Endif
		
		ufo.Update()
		Local key:Int = Keyboard.KeyDown(Key.Escape)


		If oldScape And Not key
			If Cast<GalVadors>(nextStage) 
				media.StopMusic()
			Endif 
			nextStage = menuStage
		Endif
		
		oldScape = key
		
		If passedLevel = True
			If Keyboard.KeyDown(Key.Space) And player.state <> player.PASSEDGAME
				
				wave.SetNextLevel()
				gameTimer.Reset()
				player.state = player.ACTIVE
				passedLevel = False
				ufo.Reset()
				enemyBulletList.Clear()
				playerBulletList.Clear()
				explosionList.Clear()
				shipParticleList.Clear()
				aparticleList.Clear()
				specialList.Clear()
			Endif
		Endif
	End Method
			
	Method KilledAll:Int()
		Return wave.KilledAll()
	End Method
	
	Method UpdateBullets:Void()
		For Local b := Eachin playerBulletList
			b.Update()
		Next
		For Local b := Eachin enemyBulletList
			b.Update()
		Next
		
	End Method
	
	Method ProcessCollisions:Void()
		If Not specialList.Empty
			Local node := specialList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				Local s := node.Value
				If player.Collided(s.pos.x,s.pos.y,s.hitBox)
					Select s.type
						Case Special.HEART
							If player.lifes < 5
								player.lifes  += 1
							Endif
						Case Special.SHIELD
							player.shieldTimer.Reset()
						Case Special.GUN
							player.bulletTimer.Reset()
					End Select
					media.WoopSnd()
					node.Remove()
				Endif
				node = nextNode
			Wend
		Endif
		If Not playerBulletList.Empty
			Local node := playerBulletList.FirstNode()
			While node.Value
				Local nextNode := node.Succ		 
				wave.CollideBullet(node)
				node = nextNode
			Wend
		Endif
		If ufo.active = True
			If Not playerBulletList.Empty
				Local node := playerBulletList.FirstNode()
				While node.Value
					Local nextNode := node.Succ
					Local b := node.Value
					If ufo.Collided(b.pos.x,b.pos.y,b.hitBox)	
						Local e:= explosionStore.GetItem()
						e.Init(ufo.pos.x,ufo.pos.y,100)
						explosionList.AddLast(e)
						ufo.ReleaseSpecial(player)
						ufo.DeActivate()
						media.ExplodeSnd2()
						node.Remove()
						bulletStore.ReturnItem(node.Value)
						Exit
					Endif
					node = nextNode
				Wend
			Endif		
		Endif
		If player.state = player.ACTIVE
			If player.shielded = False
				If wave.CollidedPlayer(player)
					CreateShipExplosion(player.pos.x,player.pos.y)
					Local e := explosionStore.GetItem()
					e.Init(player.pos.x,player.pos.y,100)
					explosionList.AddLast(e)
					If player.lifes = 0
						player.state = player.DEAD
					Else
						player.state = player.SPAWNING
						player.SpawnReset()
					Endif
				Endif
			Endif
		Endif

		If player.state = player.ACTIVE
			If player.shieldTimer.Update() = False
				If Not enemyBulletList.Empty
					Local node := enemyBulletList.FirstNode()
					While node.Value	
						Local nextNode := node.Succ
						Local b := node.Value
						If player.Collided(b.pos.x,b.pos.y,b.hitBox)
							node.Remove()
							bulletStore.ReturnItem(b)
							CreateShipExplosion(player.pos.x,player.pos.y)
							Local e := explosionStore.GetItem()
							e.Init(player.pos.x,player.pos.y,100)
							explosionList.AddLast(e)
							player.state = player.SPAWNING
							media.ExplodeSnd2()
							player.SpawnReset()
						Endif
						node = nextNode
					Wend
				Endif
			Endif
		Endif

		Local dw:Float = DeviceWidth
		Local dh:Float = DeviceHeight
		
		If Not playerBulletList.Empty
			Local node:List<Bullet>.Node = playerBulletList.FirstNode()
			while node.Value
				Local nextNode := node.Succ
				Local b:= node.Value
				If (b.pos.x < 0) Or (b.pos.y < 0) Or (b.pos.x > dw) Or (b.pos.y > dh)
					node.Remove()
					bulletStore.ReturnItem(b)
				Endif
				node = nextNode
			Wend
		Endif
		If Not enemyBulletList.Empty
			Local node := enemyBulletList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				Local b := node.Value
				If (b.pos.x < 0) Or (b.pos.y < 0) Or (b.pos.x > dw) Or (b.pos.y > dh)
					node.Remove()
					bulletStore.ReturnItem(b)
				Endif
				node = nextNode
			Wend
		Endif
	End Method
	
	Method ProcessExplosions:Void()
		If Not explosionList.Empty
			Local node := explosionList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				Local e := node.Value	
				e.Update()
				If e.Done()
					node.Remove()
					explosionStore.ReturnItem(e)
				Endif
				node = nextNode
			Wend
		Endif
		
		If Not shipParticleList.Empty
			Local node := shipParticleList.FirstNode()
			While node.Value
				Local nextNode := node.Succ
				Local e := node.Value
				e.Update()
				If e.Done()
					node.Remove()
					particleStore.ReturnItem(e)
				Endif
				node = nextNode
			Wend
		Endif
	End Method
	
	Method Render:Void(canvas:Canvas) Override

		canvas.Color = New Color(.6,.6,.6) '150,150,150
		For Local m:Meteor = Eachin meteorList
			m.Render(canvas)
		Next
		canvas.Color = New Color(1,1,1) '255,255,255
		player.Render(canvas)
		wave.Render(canvas)

		canvas.BlendMode =  BlendMode.Additive
		For Local p:= Eachin  aparticleList
			p.Render(canvas)
		Next
		
		canvas.Alpha = 1.0
		For Local b := Eachin playerBulletList
			b.Render(canvas)
		Next
		
		For Local b := Eachin enemyBulletList
			b.Render(canvas)
		Next
		
		For Local ex := Eachin explosionList
			ex.Render(canvas)
		Next
		
		canvas.Color = New Color(1,1,1) ' 255,255,255
		For Local pa := Eachin shipParticleList
			pa.Render(canvas)
		Next
		
		For Local s := Eachin specialList
			s.Render(canvas)
		Next
		
		ufo.Render(canvas)
		
		gameTimer.Render(canvas)
		RenderText(canvas,score,500,10)
		canvas.Color = New Color(1,0,1) '255,0,255
		Select player.state
			Case player.PASSEDLEVEL
				RenderText(canvas,"    Level Completed!",140,180)
				RenderText(canvas,"   Final Score "+score,150,220)
				RenderText(canvas,"Press SPACE to CONTINUE.",150,300)
			Case player.DEAD
				RenderText(canvas,"  Game Over - You Lost!",150,180)
				RenderText(canvas,"    Final Score "+score,150,220)
				RenderText(canvas,"  Press 'ESC' to Exit.",150,300)
			Case player.PASSEDGAME	
				RenderText(canvas,"     Game WON",150,180)
				RenderText(canvas,"    Final Score "+score,150,220)
				RenderText(canvas,"Press 'ESC' to Exit.",150,300)
		End Select
		canvas.Color = New Color(1,1,1) '255,255,255
		If player.shielded = True
			canvas.DrawImage(media.specialImg[Special.SHIELD],280,25)
		Endif
		If player.fastRate = True
			canvas.DrawImage(media.specialImg[Special.GUN],280,25)
		Endif
	End Method 	

End Class

Class Options Extends StageBase
	Field oldScape:Int

	Method New()
		
	End Method
	
	Method Update:Void() Override
		Local key:Int = Keyboard.KeyDown(Key.Escape)
		If oldScape And Not key 
			nextStage = menuStage
		Endif
		oldScape = key
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawText("This is the Options Stage",300,240)
	End Method 	

End Class

Class Credits Extends StageBase

	Field oldScape:Int

	Method New()
	End Method
	
	Method Update:Void() Override
		Local key:Int = Keyboard.KeyDown(Key.Escape)
		If oldScape And Not key 
			nextStage = menuStage
		Endif
		oldScape = key
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawText("This is the credits Section",300,240)
	End Method 	

End Class

Class ScoresTable Extends StageBase

	Field oldScape:Int
	

	Method New()
	
	End Method
	
	Method Update:Void() Override
		Local key:Int =Int(Keyboard.KeyDown(Key.Escape))
		If oldScape And Not key 
			nextStage = menuStage
		Endif
		oldScape = key
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawText("This is the Scores Table Section",250,240)
	End Method 	

End Class

Class ScoreKeeper
	Field total:Int
End Class

'**********************************************************************
Class HitBox
	Field min:PVector2D
	Field max:PVector2D
	
	Method New()
	End Method
		
	Method New(minx:Float,miny:Float,maxx:Float,maxy:Float)
		Self.min = New PVector2D(minx, miny)
		Self.max = New PVector2D(maxx, maxy)
	End Method
	
	Method Set:Void(minx:Float,miny:Float,maxx:Float,maxy:Float)

		If min = Null min = New PVector2D
		If max = Null max = New PVector2D
		
		Self.min.Set(minx, miny)
		Self.max.Set(maxx, maxy)
	End Method
	
	Method Render:Void(canvas:Canvas,x:Float,y:Float)
		canvas.DrawLine(x+min.x,y+min.y,x+max.x,y+min.y)
		canvas.DrawLine(x+max.x,y+min.y,x+max.x,y+max.y)
		canvas.DrawLine(x+max.x,y+max.y,x+min.x,y+max.y)
		canvas.DrawLine(x+min.x,y+max.y,x+min.x,y+min.y)
	End Method
	
End Class


Class Entity
	Field parent:PVector2D
	Field mainv:PVector2D
	Field pos:PVector2D
	Field hitBox:HitBox
	Field startTime:Int
	Field frameDelay:Int
	Field totalFrames:Int
	Field angle:Float
	Field d:PVector2D
	Field state:Int

	Field image:Image[]
	Field value:Int

	Const IN_FORMATION:Int = 1
	Const ALIGNING_OUT:Int = 2
	Const LEAVING:Int = 3
	Const ATTACKING:Int = 4
	Const TURNING:Int = 5
	Const RETURNING:Int = 6 
	Const ALIGNING_IN:Int = 7
	Const SWEEPING:Int = 8

	Const ACTIVE:Int = 9
	Const SPAWNING:Int = 10
	Const DEAD:Int = 11
	Const PASSEDLEVEL:Int = 12
	Const PASSEDGAME:Int = 13
	
	Method Update:Void() Abstract
		
	Method Render:Void(canvas:Canvas) Abstract
	
	Method UnRegister:Void() Abstract
	
	Method New()
		parent = New PVector2D
		mainv = New PVector2D
		pos = New PVector2D
		d = New PVector2D
	End Method
	
	Method Collided:Int(px:Float,py:Float,hb:HitBox)
		Local b2x1:Float,b2y1:Float,b2x2:Float,b2y2:Float
		Local b1x1:Float = px + hb.min.x
		Local b1y1:Float = py + hb.min.y
		Local b1x2:Float = px + hb.max.x
		Local b1y2:Float = py + hb.max.y
		Select state
			Case IN_FORMATION,ALIGNING_OUT,ALIGNING_IN
				b2x1 = parent.x + hitBox.min.x
				b2y1 = parent.y + hitBox.min.y
				b2x2 = parent.x + hitBox.max.x
				b2y2 = parent.y + hitBox.max.y
			Default
				b2x1 = pos.x + hitBox.min.x
				b2y1 = pos.y + hitBox.min.y
				b2x2 = pos.x + hitBox.max.x
				b2y2 = pos.y + hitBox.max.y
		End Select
		If b1x1 > b2x2 Return False
		If b1x2 < b2x1 Return False
		If b1y1 > b2y2 Return False
		If b1y2 < b2y1 Return False 	
		Return True
	End Method
	
	Method SetHitBox:Void(minx:Float,miny:Float,maxx:Float,maxy:Float)
		If hitBox= Null
			hitBox = New HitBox(minx,miny,maxx,maxy)
		Else
			hitBox.Set(minx, miny, maxx, maxy)
		Endif
	End Method
	
End Class

Class Player Extends Entity
	Field minx:Float
	Field maxx:Float
	Field direction:Int
	Field delay:Int
	Field StartTime:Int
	Field passedLevel:Int
	Field lifes:Int
	Field trailImg:Image[]
	
	Field shieldTimer:Timer
	Field bulletTimer:Timer
	
	Field bulletRateUp:Int
	Field fastRate:int
	Field shielded:Int
	
	Field decrementRate:int
	
	Field spawnTimer:Timer
	
	Field bulletImg:Image[]
		
	Const SPAWNDELAY:Int = 2000
	
	Method New()
		image = media.playerImg
		
		bulletImg = media.bulletImg 
		trailImg = media.trailImg
		delay = 500
		decrementRate = 400
		startTime = currentTime
		minx = image[0].Handle.X
		Local img:Image = image[0]
		maxx =  DeviceWidth -(img.Width/2)
		hitBox = New HitBox(6-img.Width/2,4-img.Height/2, img.Width/2 -6, img.Height/2)
		minx = image[0].Handle.X
		pos.Set(DeviceWidth / 2,DeviceHeight - 40)
		lifes = 3
		state = ACTIVE
		spawnTimer = New Timer(SPAWNDELAY,0,0)
		bulletTimer = New Timer(5000,0,0)
		shieldTimer = New Timer(5000,0,0)
		bulletTimer.Expire()
		shieldTimer.Expire()
		shielded = False
	End Method
	
	Method UnRegister:Void() Override
	
	End Method
	
	Method SpawnReset:Void()
		spawnTimer.Reset()
	End Method
	
	Method Update:Void() Override
		Local dt:Int = decrementRate
		If bulletTimer.Update() = False
			fastRate = False
			dt = 0
		Else
			fastRate = True
		Endif
		
		If shieldTimer.Update() = False
			shielded = False
		Else
			shielded = True
		Endif
		
		Select state
			Case ACTIVE
				direction = Int(Keyboard.KeyDown(Key.Right)) - Int(Keyboard.KeyDown(Key.Left))
				If (startTime+(delay-dt)) < currentTime
					If Keyboard.KeyDown(Key.Z)
						Local b:Bullet = bulletStore.GetItem()
						b.Init(bulletImg,trailImg,pos.x,pos.y-12,0,-1,10)
						Local bImg:Image = bulletImg[0]
						b.SetHitBox(-bImg.Width/2,-bImg.Height/2,bImg.Width/2,bImg.Height/2)
						playerBulletList.AddLast(b)
						startTime = currentTime
						media.ShootSnd1()
					Endif
				Endif
				pos.x += direction * 5
				If pos.x < minx pos.x = minx
				If pos.x > maxx pos.x = maxx
			Case SPAWNING
				direction = Int(Keyboard.KeyDown(Key.Right)) - Int(Keyboard.KeyDown(Key.Left))
				pos.x += direction * 5
				If pos.x < minx pos.x = minx
				If pos.x > maxx pos.x = maxx
				If spawnTimer.Update() = False
					If lifes > 1
						state = ACTIVE
					Else
						state = DEAD
					Endif
					lifes -= 1
				Elseif lifes = 1
					lifes -= 1
					state = DEAD
				Endif
			Case DEAD
				
		End Select
		
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		Select state
			Case ACTIVE
				If shielded = False
					canvas.DrawImage(image[1],pos.x,pos.y)
				Else
					canvas.Alpha = .8
					canvas.DrawImage(image[0],pos.x,pos.y)				
				Endif
			Case SPAWNING
				canvas.Alpha = .6
				canvas.DrawImage(image[0],pos.x,pos.y)
		End Select
		canvas.Alpha = 1.0
		For Local i:Int = 0 Until lifes
			canvas.DrawImage(image[1],370+i*28,30)
		Next
		'hitBox.Render(canvas,pos.x,pos.y)
	End Method
	
End Class
	
Class Gripper Extends Entity
	Field index:Int

	Method New()
		image = media.gripperImg
		pos.Set(100, 50)
		SetHitBox(-image[0].Handle.X,-image[0].Handle.Y,image[0].Width-image[0].Handle.X,image[0].Height - image[0].Handle.Y)
		startTime = currentTime
		frameDelay = 500
		totalFrames = 2
		state = IN_FORMATION = True
		value = 200
	End Method

	Method Update:Void() Override
		If currentTime > startTime+frameDelay
			index = (index + 1) Mod totalFrames
			startTime = currentTime
		Endif
				
	End Method
	
	Method UnRegister:Void() Override
	
	End Method

	Method Render:Void(canvas:Canvas) Override
		If state = IN_FORMATION
			canvas.DrawImage(image[index],parent.x,parent.y,0,1.3,1.3)
		Else
			canvas.DrawImage(image[index],pos.x,pos.y,0,1.3,1.3)
		Endif
	End Method

End Class

Class Lazer Extends Entity
	Method Update:Void() Override
	End Method
	
	Method UnRegister:Void() Override
	End Method
	
	Method Render:Void(canvas:Canvas) Override
	End Method
End Class


Class Tesla Extends Entity
	Field p:PVector2D
	Field posx:Float
	Field posy:Float
	Field direction:Int
	Field dist:PVector2D
	Field index:Int
	
	Field shootTime:Int
	Field shootDelay:Int
	Field shootAngle:Float
	Field shootAngleStep:Float
	
	Field attackCount:Int
	Field bulletImg:Image[]
	
	Field length:Float
	Field speed:Float

	Global divingCount:Int
	Global attackDelay:Int
	Global attackTime:Int
	Global trailImg:Image[]
	

	Method New(firstAttackTime:Int,attackRate:int)
		image = media.teslaImg
		trailImg = media.trailImg
		bulletImg = media.bulletImg
		Local img:Image = image[0]
		SetHitBox(-img.Width/2,-img.Height/2,img.Width/2,img.Height/2)
		pos.Set(50,50)
		startTime = currentTime
		frameDelay = attackRate
		totalFrames = 2
		state = IN_FORMATION
		divingCount = 0
		attackDelay = 1000
		attackTime = currentTime+firstAttackTime
		shootDelay = 100
		value = 150
		dist = New PVector2D
		p = New PVector2D
	End Method

	Method Update:Void() Override
		If currentTime > startTime+frameDelay
			index = (index + 1) Mod totalFrames
			startTime = currentTime
		Endif
		Select state
			Case IN_FORMATION
				If divingCount < 2 And player.state = player.ACTIVE
					If attackTime+attackDelay < currentTime
						If Rnd(10) > 9.5
							pos.Set(parent)
							p.Set(pos.x,pos.y)
							state = LEAVING		
							posy = 250.0
							posx = Rnd(60,580)
							dist.Set( posx - pos.x, posy - pos.y)
							length = dist.Magnitude()
							Local ang:Float = dist.GetAngle()
							d.Set(Cos(ang), Sin(ang))
							dist.Set(0, 0)
							divingCount += 1
							attackTime = currentTime
							attackCount = 0
							speed = 3
						Endif
					Endif
				Endif						
			Case LEAVING
				dist.Add(d.x * speed,d.y * speed)
				Local len:Float = dist.Magnitude()
				If len < length
					pos.Set(p.x + dist.x, p.y + dist.y)
				Else
					pos.Set(p.x + d.x * length, p.y + d.y * length)
					p.Set(pos.x,pos.y)
					state = ATTACKING
					shootAngle = 45
					shootAngleStep = 12
					shootTime = currentTime
					attackCount = 0
					dist.Set(0,0)
				Endif
			
			Case ATTACKING
				If shootTime + shootDelay < currentTime
					If attackCount < 10
						Local tdx:Float = Cos(shootAngle)
						Local tdy:Float = Sin(shootAngle)
						Local b:Bullet = bulletStore.GetItem()
						b.Init(bulletImg,trailImg,pos.x+tdx*15.0,pos.y+tdy*15,tdx,tdy,5)
						enemyBulletList.AddLast(b)
						attackCount += 1
						shootAngle += shootAngleStep
						shootTime = currentTime
					Else
						state = RETURNING
					Endif
				Endif
			Case RETURNING
				dist.Set(parent.x - pos.x, parent.y - pos.y)
				Local targetAngle:Float = dist.GetAngle()
				pos.Add(Cos(targetAngle) * speed,Sin(targetAngle) * speed)
				angle = targetAngle
				If pos.y <= parent.y 
					pos.Set(parent)
					divingCount -= 1
					state = IN_FORMATION
				Endif			
		End Select
				
	End Method
	
	Method UnRegister:Void() Override
		If state <> IN_FORMATION
			divingCount -= 1
		Endif
	End Method

	Method Render:Void(canvas:Canvas) Override
		If state = IN_FORMATION
			canvas.DrawImage(image[index],parent.x,parent.y,0,1.1,1.1)
		Else
			canvas.DrawImage(image[index],pos.x,pos.y,0,1.1,1.1)
		Endif
	End Method

End Class

Class Boxed Extends Entity
	Field index:Int
	Field posx:Float
	Field posy:Float
	Field vx:Float
	Field vy:Float
	Field speed:Float
	Field length:Float
	Field px:Float
	Field py:Float
	Field laserImg:Image
	Field gunImg:Image
	Field lazer:Lazer
	Field time:Int
	Field delay:Int
	Field shake:float
	
	Global divingCount:Int = 0
	Global attackDelay:Int
	Global attackTime:Int 

	Method New(firstAttackTime:Int,attackRate:int)
		image = media.boxedImg
		laserImg = media.lazerImg
		gunImg = media.gunbImg 
		Local img := image[0]
		SetHitBox(-img.Width/2,-img.Height/2,img.Width/2,img.Height/2)
		state = IN_FORMATION
		attackDelay = attackRate
		attackTime = currentTime + firstAttackTime
		speed = 3
		lazer = New Lazer
		lazer.hitBox = New HitBox(-6,0,6,100)
		value = 100
		time = currentTime
		delay = 100
		index = 0
		shake = 0
	End Method

	Method Update:Void() Override
		Select state
			Case IN_FORMATION
				If divingCount < 2 And player.state = player.ACTIVE
					If attackTime+attackDelay < currentTime
						If Rnd(10) > 9.0
							pos.x = parent.x
							pos.y = parent.y
							px = pos.x
							py = pos.y
							state = LEAVING
							posy = 350.0
							posx = Rnd(60,580)
							vx = posx - pos.x
							vy = posy - pos.y
							length = Sqrt(vx*vx+vy*vy)
							Local ang:Float = ATan2(vy,vx)
							d.Set( Cos(ang),Sin(ang))
							vx = 0
							vy = 0
							divingCount += 1
							attackTime = currentTime
						Endif
					Endif
				Endif	
			Case LEAVING
				vx += d.x * speed
				vy += d.y * speed
				Local len:Float = Sqrt(vx*vx+vy*vy)
				If len < length
					pos.x = px + vx
					pos.y = py + vy
				Else
					pos.Set(px + d.x * length, py + d.y * length)
					px = pos.x
					py = pos.y
					state = SWEEPING
					If player.pos.x < px
						If pos.x > 120
							d.x = -1
						Else
							d.x = 1
						Endif
					Else
						If pos.x < 520
							d.x = 1
						Else
							d.x = -1
						Endif
					Endif
					d.y = 0
					length = 120.0
					vx = 0 
					vy = 0
					media.LaserSnd()
				Endif
			Case SWEEPING
				vx += d.x*speed
				Local len:Float = Sqrt(vx*vx+vy*vy)
				If len < length
					pos.Set(px + vx, py)
				Else
					pos.Set(px + d.x * length,py)
					state = RETURNING
				Endif	
			Case RETURNING
				vx = parent.x - pos.x
				vy = parent.y - pos.y
				Local targetAngle:Float = ATan2(vy,vx)
				pos.Add(Cos(targetAngle) * speed, Sin(targetAngle) * speed)
				angle = targetAngle
				If pos.y <= parent.y 
					pos.Set(parent.x, parent.y)
					divingCount -= 1
					state = IN_FORMATION
				Endif

		End Select
		If time + delay <Millisecs()
			index = (index + 1) Mod 3
			time = Millisecs()
		Endif
		shake = (shake - (3.0*ATR)) Mod TwoPi
	End Method
		
	Method UnRegister:Void() Override
		If state <> IN_FORMATION
			divingCount -= 1
		Endif
	End Method

	Method Render:Void(canvas:Canvas) Override
		If state = IN_FORMATION
			canvas.DrawImage(image[index],parent.x+3*Cos(shake),parent.y+1*Sin(shake),0,1.3,1.3)
		Else
			canvas.DrawImage(image[index],pos.x,pos.y,0,1.3,1.3)
			If state = SWEEPING
				canvas.DrawImage(gunImg,pos.x,pos.y,0,1.3,1.3)
				canvas.DrawImage(laserImg,pos.x,pos.y,0,1,100)
			Endif
		Endif
		'hitBox.Render(canvas,parent.x,parent.y)
	End Method


End Class	

Class Micron Extends Entity
	Field index:Int
	Field targetAngle:Float
	Field vx:Float
	Field vy:Float
	Field length:Float
	Field px:Float
	Field py:Float
	Field pivotx:Float
	Field pivoty:Float
	Field rotate:Float
	Field speed:Float
	Field direction:Int
	Field life:int
	Field bulletImg:Image[]
	Field trailImg:Image[]
	
	Const LEFT:Int = 1
	Const RIGHT:Int = 2
	
	Const TURN_RADIUS:Float = 40.0
	Const RTA:Float = Pi/180.0
	Const STP:Float = 1.0/(RTA * 20)
	
	Global divingCount:Int = 0
	Global attackDelay:Int
	Global attackTime:Int
	Global shootTime:Int
	Global shootDelay:Int

	Method New(firstShotStart:Int,firstAttackStart:int)
		image = media.micronImg
		bulletImg = media.bulletImg
		trailImg  = media.trailImg
		Local img := image[0]
		SetHitBox(-img.Width/2,-img.Height/2,img.Width/2,img.Height/2)
		pos.Set(50, 100)
		startTime = currentTime
		frameDelay = 100
		totalFrames = 4
		state = IN_FORMATION
		speed = 3
		
		attackDelay = 1000
		attackTime = currentTime + firstAttackStart 'first petential attack after 3 seconds
		
		shootDelay = 700
		shootTime = currentTime +  firstShotStart'first potential shot after two seconds.
		
		value = 50
		divingCount = 0
	End Method
	
	Method ShootAttempt:Void()
		If shootTime + shootDelay < currentTime
			If state = IN_FORMATION
				If Abs(parent.x - player.pos.x) < 6
					Local b:Bullet = bulletStore.GetItem()
					b.Init(bulletImg,trailImg,parent.x,parent.y,0,1,10)
					enemyBulletList.AddLast(b)
					shootTime = currentTime
				Else
					If Rnd(10) > 7
						Local b:Bullet = bulletStore.GetItem()
						b.Init(bulletImg,trailImg,parent.x,parent.y,0,1,10)
						enemyBulletList.AddLast(b)
						shootTime = currentTime
					Endif	
				Endif
			Elseif state = ATTACKING
				If Abs(pos.x - player.pos.x) < 2
					Local b:Bullet = bulletStore.GetItem()
					Local tdx:Float = Cos(angle)
					Local tdy:Float = Sin(angle)
					b.Init(bulletImg,trailImg,pos.x+tdx*10.0,pos.y+tdy*10.0,tdx,tdy,10.0)
					enemyBulletList.AddLast(b)
					shootTime = currentTime
				Elseif Rnd(10) > 9
						Local b:Bullet = bulletStore.GetItem()
						Local tdx:Float = Cos(angle)
						Local tdy:Float = Sin(angle)
						b.Init(bulletImg,trailImg,pos.x+tdx*10.0,pos.y+tdy*10.0,tdx,tdy,10.0)
						enemyBulletList.AddLast(b)
						shootTime = currentTime
				Endif
			Endif
		Endif
			 
	End Method

	Method Update:Void() Override
		Select state
			Case IN_FORMATION
				If currentTime > startTime+frameDelay
					index = (index + 1) Mod totalFrames
					startTime = currentTime
				Endif
				If divingCount < 4 And player.state = player.ACTIVE
					If attackTime+attackDelay < currentTime
						If Rnd(1000) > 900.0
							pos.Set(parent)
							state = ALIGNING_OUT
							divingCount += 1
							attackTime = currentTime
						Else
							
						Endif
					Else
						ShootAttempt()
					Endif
				Endif				
			Case ALIGNING_OUT
				angle = (angle + TwoPi) Mod TwoPi 
				vx = player.pos.x - parent.x
				vy = player.pos.y - parent.y
				px = parent.x
				py = parent.y
				length = Sqrt(vx*vx+vy*vy)
				targetAngle = (ATan2(vy,vx)+TwoPi) Mod TwoPi		
				Local difference:Float = Abs(targetAngle-angle)
				'turn toward target	
				Local stp := 5 * ATR			
				If targetAngle < angle				
					If difference > Pi 
						angle += stp
					Elseif difference < Pi
						angle -= stp
					Endif
				Elseif targetAngle > angle
					If difference > Pi
						angle -= stp
					Elseif difference < Pi
						angle += stp
					Endif
				Endif
				'If found stop turning
				
				If difference < 5
					angle = targetAngle
					d.Set(Cos(angle), Sin(angle))
					vx = 0
					vy = 0
					pos.x = parent.x
					pos.y = parent.y
					state = ATTACKING
				Endif
			Case ATTACKING
				vx += d.x * speed
				vy += d.y * speed
				Local len:Float = Sqrt(vx*vx+vy*vy)
				If len >= length
					pos.x = px + vx
					pos.y = py + vy
					state = TURNING
					If player.pos.x < pos.x
						pivotx = pos.x - d.y * TURN_RADIUS
						pivoty = pos.y + d.x * TURN_RADIUS
						rotate = angle - (Pi/2)
						direction = RIGHT
					Else
						pivotx = pos.x + d.y * TURN_RADIUS
						pivoty = pos.y - d.x * TURN_RADIUS
						rotate = angle + (Pi/2)
						direction = LEFT
					Endif
				Else
					pos.Set(px + vx, py + vy)
					ShootAttempt()
				Endif
				
			Case TURNING
				If direction = RIGHT
					angle += STP * 2 
					rotate += STP * 2
					pos.x = pivotx + Cos(rotate) * TURN_RADIUS
					pos.y = pivoty + Sin(rotate) * TURN_RADIUS
					If rotate >= Pi state = RETURNING
				Else 
					angle -= STP * 2
					rotate -= STP * 2
					pos.x = pivotx + Cos(rotate) * TURN_RADIUS
					pos.y = pivoty + Sin(rotate) * TURN_RADIUS
					If rotate <= 0 state = RETURNING
				Endif
			Case RETURNING
				vx = parent.x - pos.x
				vy = parent.y - pos.y
				targetAngle = ATan2(vy,vx)
				pos.Add(Cos(targetAngle) * speed,Sin(targetAngle) * speed)
				angle = targetAngle
				If pos.y <= parent.y 
					pos.Set(parent.x, parent.y)
					targetAngle = Pi * 1.5
					state = ALIGNING_IN
				Endif

			Case ALIGNING_IN
				angle = (angle + TwoPi) Mod TwoPi
				Local difference:Float  = Abs(targetAngle - angle)
				If angle < targetAngle
					If difference < Pi
						angle += 5 * ATR
					Else
						angle -= 5 * ATR
					Endif
				Elseif angle > targetAngle
					If difference < Pi
						angle -= 5.0 * ATR
					Else
						angle += 5.0 * ATR
					Endif
				Endif
				
				If difference < (5 * ATR)
					divingCount -= 1
					angle = targetAngle
					state = IN_FORMATION
				Endif
					
		End Select
	End Method
	
	Method UnRegister:Void() Override
		If state <> IN_FORMATION
			divingCount -= 1
		Endif
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		Select state
			Case IN_FORMATION
				canvas.DrawImage(image[index],parent.x,parent.y,0,1.3,1.3)
			Case ALIGNING_OUT
				canvas.DrawImage(image[index],parent.x,parent.y,-angle-90,1.3,1.3)
			Case ALIGNING_IN
				canvas.DrawImage(image[index],parent.x,parent.y,-angle-90,1.3,1.3)
			Case TURNING
				If direction = RIGHT
					canvas.DrawImage(image[2],pos.x,pos.y,-angle-90,1.3,1.3)			
				Else
					canvas.DrawImage(image[2],pos.x,pos.y,-angle-90,1.3,1.3)
				Endif
			Default
				canvas.DrawImage(image[2],pos.x,pos.y,-angle-90,1.3,1.3)
		End Select
		'hitBox.Render(canvas,parent.x,parent.y)
	End Method
End Class

Class Ufo Extends Entity
	Field frame:Float
	Field speed:Float
	Field dir:Float
	Field delay:Int
	Field stage:Int
	Field active:Int
	Field time:Int
	Field lifes:Int
	Field gunImg:Image
	Field heartImg:Image
	Field shieldImg:Image
	Field specialImg:Image[]
	Field released:Int
	Field nstate:int
	
	Const STARTLEFT:Int = 1
	Const STARTRIGHT:Int = 2
	Const LEFT:Int = - 1
	Const RIGHT:Int = 1
	
	
	Method New(x:Float,y:Float)
		Self.image = media.ufoImg
		specialImg = New Image[3]
		Self.specialImg[Special.HEART] = media.heartImg
		Self.specialImg[Special.GUN] = media.gunImg
		Self.specialImg[Special.SHIELD] = media.shieldImg
		Local img:Image = image[0]
		SetHitBox(-img.Width/2,-img.Height/2+2,img.Width/2,img.Height/2-2)
		pos = New PVector2D(x,y)
		speed = 1.5
		dir = 1
		active = False
		delay = 5000+Rnd(10000)
		active = False
		time = Millisecs()
		lifes = 3
	End Method
	
	Method Update:Void() Override
		If lifes > 0
			If active = True
				frame = (frame + .2) Mod 4
				If nstate = STARTLEFT
					If pos.x > 680
						active = False
						time = currentTime
						lifes -= 1
					Else
						pos.x += dir * speed
					Endif
				Elseif pos.x  < -40
					dir = -dir
					active = False
					time = currentTime
					lifes -= 1
				Else
					pos.x += dir * speed
				Endif
			Else
				If time + delay < currentTime
					If Rnd(2) < 1
						nstate = STARTLEFT
						dir = 1
						pos.x = -40
					Else
						nstate = STARTRIGHT
						dir = -1
						pos.x = 680
					Endif
					active = True	
				Endif
			End If
			
		Endif 
	End Method
	
	Method DeActivate:Void()
		pos.x = -40
		active = False
		delay = 5000+Rnd(10000)
		time = currentTime
		lifes -= 1
	End Method
	
	Method Reset:Void()
		pos.x = -40
		active = False
		delay = 500+Rnd(10000)
		time = currentTime
		lifes = 3 		
	End Method
	
	Method ReleaseSpecial:Void(p:Player)
		Local type:Int
		Local n:Float = Rnd(3.0)
		If n < 1.0 
			If p.lifes < 5
				type = Special.HEART
			Else
				type = Special.SHIELD
			Endif
		Elseif n < 2.0 
			type = Special.SHIELD
		Else
			 type = Special.GUN
		Endif
		Local s:Special = New Special(pos.x,pos.y,2,type)
		specialList.AddLast(s)
	
	End Method
	
	Method UnRegister:Void() Override
		
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		If active = True
			canvas.DrawImage(image[frame],pos.x,pos.y)
			'hitBox.Render(canvas,pos.x,pos.y)
		Endif
	End Method
End Class

Class Special
	Field pos:PVector2D
	Field D:PVector2D
	Field speed:Float
	Field type:Int
	Field active:Int
	Field timer:Timer
	Field done:Int
	Field image:Image
	Field g:Float
	
	Const HEART:Int = 0
	Const GUN:Int = 1
	Const SHIELD:Int = 2
	
	Global hitBox:HitBox = New HitBox
	
	
	Method New(x:Float,y:Float,speed:Float,type:Float)
		Self.image = media.specialImg[type]
		pos = New PVector2D(x,y)
		D = New PVector2D(0,1)
		Self.speed = -speed
		active = True
		Self.type = type
		timer = New Timer(1000,0,0)
		g = .2
		done = False
		SetHitBox()
	End Method
		
	Method SetHitBox:Void()
		hitBox.Set(-image.Handle.X,-image.Handle.Y,image.Width - image.Handle.X,image.Height - image.Handle.Y)
	End Method
	
	Method Update:Int()
		If done = False
			If active = True
				pos.Add(D.x*speed,D.y*speed)
				speed += g
				If pos.y > 430
					pos.y = 430
					active = False
					timer.Reset()
				Endif
			Else
				If timer.Update() = False
					done = True
				Endif
			Endif
		Endif
		Return Not done
	End Method
	
	Method UnRegister:Void()
	
	End Method
	
	Method Render:Void(canvas:Canvas)
		canvas.DrawImage(image,pos.x,pos.y)
'		hitBox.Render(pos.x,pos.y)
	End Method
	
End Class

Class Level

	Method Update:Void() Abstract
	Method Render:Void(canvas:Canvas) Abstract	

End Class

Class Wave Extends Level
	
	Field grid:Entity[][]
	Field rows:Int
	Field columns:Int
	Field state:Int
	Field angle:Float
	Field direction:Float
	Field speed:Float
	Field cx:Float
	Field cy:Float
	Field explosionImg:Image[]
	Field trailImg:Image[]
	Field level:int
	
	Const EXPANDING:Int = 1
	Const MOVING:Int = 2
	
	
	Method New(level:Int = 0)
		rows = 9
		columns = 6
		Self.explosionImg = media.explosionImg
		trailImg = media.trailImg
		grid = New Entity[columns][]
		InitLevel(level)
		speed = 2.2
		Self.level = level
	End Method
	
	Method InitLevel:Void(lvl:Int)
		cx = 330 
		cy = 50
		state = MOVING
		Print lvl
		Select lvl 
			Case 0
				For Local i:Int =  0 Until columns
					grid[i] = New Entity[rows]
					For Local j:Int = 0 Until rows
						grid[i][j] = New Micron(2000,60000)
						grid[i][j].parent.Set(140 + j * 41, 130 + i * 24)
						grid[i][j].mainv.x = grid[i][j].parent.x-cx
						grid[i][j].mainv.y = grid[i][j].parent.y-cy
					Next
				Next
			Case 1
				For Local i:Int =  0 Until columns
					grid[i] = New Entity[rows]
					For Local j:Int = 0 Until rows
						If i < 2
							grid[i][j] = New Boxed(30000,1000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Else
							grid[i][j] = New Micron(1000,60000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Endif
						grid[i][j].mainv.x = grid[i][j].parent.x-cx
						grid[i][j].mainv.y = grid[i][j].parent.y-cy
					Next
				Next
			Case 2
				For Local i:Int =  0 Until columns
					grid[i] = New Entity[rows]
					For Local j:Int = 0 Until rows
						If (i Mod 2) = 0
							grid[i][j] = New Boxed(15000,1000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Else
							grid[i][j] = New Micron(1000,60000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Endif
						grid[i][j].mainv.x = grid[i][j].parent.x-cx
						grid[i][j].mainv.y = grid[i][j].parent.y-cy
					Next
				Next
			Case 3
				For Local i:Int =  0 Until columns
					grid[i] = New Entity[rows]
					For Local j:Int = 0 Until rows
						If i < 2
							grid[i][j] = New Tesla(45000,2000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Elseif i < 4
							grid[i][j] = New Boxed(30000,1000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Else
							grid[i][j] = New Micron(1000,60000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Endif
						grid[i][j].mainv.x = grid[i][j].parent.x-cx
						grid[i][j].mainv.y = grid[i][j].parent.y-cy
					Next
				Next
			Case 4
				For Local i:Int =  0 Until columns
					grid[i] = New Entity[rows]
					For Local j:Int = 0 Until rows
						If i = 0
							grid[i][j] = New Gripper()
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Elseif i = 1
							grid[i][j] = New Tesla(30000,2000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Elseif i = 2
							grid[i][j] = New Boxed(20000,1000)
							grid[i][j].parent.Set(140 + j * 41, 100 + i * 35)
						Else
							grid[i][j] = New Micron(1000,30000)
							grid[i][j].parent.Set(140 + j * 41, 130 + i * 30	)
						Endif
						grid[i][j].mainv.x = grid[i][j].parent.x-cx
						grid[i][j].mainv.y = grid[i][j].parent.y-cy
					Next
				Next
		End Select
	
	End Method
	
	Method SetNextLevel:Void()
		level +=  1
		angle = 0
		InitLevel(level)
	End method
	
	Method CollideBullet:Void(node:List<Bullet>.Node)
		
		For Local i:Int = 0 Until columns
			For Local j:Int = 0 Until rows
				If grid[i][j]
						Local o:Entity = grid[i][j]
						Local b := node.Value
						If o.Collided(b.pos.x,b.pos.y,b.hitBox)
							node.Remove()
							bulletStore.ReturnItem(b)
							Local e := explosionStore.GetItem()
							If o.state = Entity.IN_FORMATION Or o.state = Entity.ALIGNING_OUT Or o.state = Entity.ALIGNING_IN
								e.Init(o.parent.x,o.parent.y,40)
							Else
								e.Init(o.pos.x,o.pos.y,40)
							Endif
							explosionList.AddLast(e)
							o.UnRegister()
							If o.state = o.IN_FORMATION
								score += o.value
							Else
								score += o.value + 200
							Endif
							media.ExplodeSnd2()
							grid[i][j] = Null
							Return
						Endif
					Else
							
				Endif
			Next
		Next	
	End Method
	
	Method KilledAll:Int()
		For Local i:Int = 0 Until columns
			For Local j:Int = 0 Until rows
				If grid[i][j] Return False
			Next
		Next
		Return True
	End Method
	
	Method CollidedPlayer:Int(p:Player)
		For Local i:Int = 0 Until columns
			For Local j:Int = 0 Until rows
				If grid[i][j]
					Local o:Entity = grid[i][j]
					If Cast<Micron>(o) <> Null
						If o.Collided(p.pos.x,p.pos.y,p.hitBox)
							Local e := explosionStore.GetItem()
							If o.state = Entity.IN_FORMATION Or o.state = Entity.ALIGNING_OUT Or o.state = Entity.ALIGNING_IN
								e.Init(o.parent.x,o.parent.y)
							Else
								e.Init(o.pos.x,o.pos.y)
							Endif
							explosionList.AddLast(e)
							o.UnRegister()
							grid[i][j] = Null
							media.ExplodeSnd2()
							score += o.value
							Return True
						Endif
					Elseif o.state = o.SWEEPING
						Local b := Cast<Boxed>(o)
						If b 
							If p.Collided(b.pos.x,b.pos.y,b.lazer.hitBox)
								media.ExplodeSnd2()
								Return True
							Endif
						Endif
					Endif	
				Endif
			Next
		Next	
		Return False
	End Method
	
	Method Update:Void() Override
		Local len:Float = Sin(angle/2.0)*.3 + 1.0
		For Local i:Int = 0 Until columns
			For Local j:Int = 0 Until rows
				If grid[i][j]
					If state = MOVING
						grid[i][j].parent.x += Cos(angle)*speed
					Else
						grid[i][j].parent.Set(cx+grid[i][j].mainv.x * len,cy+grid[i][j].mainv.y * len)
					Endif
					grid[i][j].Update()	
				Endif
			Next
		Next
		angle += 1*ATR 'speed
		If angle > Float(TwoPi)
			If state = MOVING
				state = EXPANDING
			Else
				state = MOVING
			Endif
			angle = angle Mod TwoPi
		Endif
		
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		For Local i:Int = 0 Until columns
			For Local j:Int = 0 Until rows
				If grid[i][j]
					grid[i][j].Render(canvas)
				Endif
			Next
		Next
	End Method
	
End Class
	
Class Bullet Extends Entity
	Field vx:Float
	Field vy:Float
	Field speed:Float
	Field trailImg:Image[]
	Field time:Int
	Field delay:Int
	
	Method New()
		
	End Method 
	
	Method New(image:Image[],trail:Image[],x:Float,y:Float,dx:Float,dy:Float,speed:Float)
		Init(image,trail,x,y,dx,dy,speed)
	End Method
	
	Method Init:Void(image:Image[],trail:Image[],x:Float,y:Float,dx:Float,dy:Float,speed:Float)
		Self.image = image
		Self.pos.Set(x,y)
		Self.d.Set(dx, dy)
		Self.speed = speed
		Self.vx = dx * speed
		Self.vy = dy * speed
		Self.trailImg = trail
		Self.SetHitBox(3-image[0].Handle.X,3-image[0].Handle.Y,image[0].Width - image[0].Handle.X,image[0].Height - image[0].Handle.Y)
		Self.time = Millisecs()
		Self.delay = 60
	End Method
	
	Method Update:Void() Override
		pos.Add(vx,vy)
		If delay+time < Millisecs()
			Local ap:ParticleA = aparticleStore.GetItem()
			ap.Set(pos.x,pos.y,speed/5.0,ATan2(d.y,d.x),trailImg,2)
			aparticleList.AddLast(ap)
			time = Millisecs()
		Endif
		
	End Method
	
	Method UnRegister:Void() Override
	
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawImage(image[0],pos.x,pos.y,0,1.5,1.5)
		'hitBox.Render(canvas,pos.x,pos.y)
	End Method

End Class

Class BulletStore
	Field list:List<Bullet>
	
	Method New(count:Int)
		list = New List<Bullet>
		Fill(count)
	End Method
	
	Method Fill:Void(total:Int)
		For Local i:Int = 0 Until total
			list.AddLast(New Bullet())
		Next
	End Method
	
	Method GetItem:Bullet()
		If Not list.Empty
			Return list.RemoveLast()
		Endif
		Return New Bullet()
	End Method
	
	Method ReturnItem:Void(bullet:Bullet)
		list.AddLast(bullet)
	End Method
	
End Class


Class Explosion Extends Entity
	
	Field delay:Int
	Field node:List<Explosion>.Node
	Field frame:Int
	
	Method New()
		
	End method
	
	Method New(x:Float,y:Float,frameDelay:Int=50)
		Init(x,y,frameDelay)
	End Method
	
	Method Init:Void(x:Float,y:Float,frameDelay:Int=50)
		Self.pos.Set(x,y)
		Self.image = media.explosionImg
		Self.delay = frameDelay
		Self.frame = 0
		Self.totalFrames = image.Length - 1
		Self.startTime = currentTime
	End Method
	
		
	Method Update:Void() Override
		If startTime+delay < currentTime
			If frame < totalFrames
				frame += 1
				startTime = currentTime
			Endif
		Endif
	End Method
	
	Method Done:Int()
		If frame = totalFrames
			If startTime+delay < currentTime
				Return True
			Endif
		Endif
		Return False
	End Method
	
	Method UnRegister:Void() Override
	
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawImage(image[frame],pos.x,pos.y,0,2.0,2.0)
	End Method
	
End Class

Class ExplosionStore
	Field list:List<Explosion>
	
	Method New(count:Int)
		list = New List<Explosion>
		Fill(count)
	End Method
	
	Method Fill:Void(total:Int)
		For Local i:Int = 0 Until total
			list.AddLast(New Explosion())
		Next
	End Method
	
	Method GetItem:Explosion()
		If Not list.Empty
			Return list.RemoveLast()
		Endif
		Return New Explosion()
	End Method
	
	Method ReturnItem:Void(explosion:Explosion)
		list.AddLast(explosion)
	End Method
	
End Class

Class AParticleStore
	Field list:List<ParticleA>
	
	Method New(count:Int)
		list = New List<ParticleA>
		Fill(count)
	End Method
	
	Method Fill:Void(total:Int)
		For Local i:Int = 0 Until total
			list.AddLast(New ParticleA())
		Next
	End Method
	
	Method GetItem:ParticleA()
		If Not list.Empty
			Return list.RemoveLast()
		Endif
		Return New ParticleA()
	End Method
	
	Method ReturnItem:Void(p:ParticleA)
		list.AddLast(p)
	End Method
	
End Class


Class ParticleStore
	Field list:List<Particle>
	
	Method New(count:Int)
		list = New List<Particle>
		Fill(count)
	End Method
	
	Method Fill:Void(total:Int)
		For Local i:Int = 0 Until total
			list.AddLast(New Particle())
		Next
	End Method
	
	Method GetItem:Particle()
		If Not list.Empty
			Return list.RemoveLast()
		Endif
		Return New Particle()
	End Method
	
	Method ReturnItem:Void(p:Particle)
		list.AddLast(p)
	End Method
	
End Class
Class Particle Extends Entity
	
	Field speed:Float
	Field angleRot:Float
	Field alpha:Float
	Field alphaDec:Float
	Field frame:Int
	Field node:List<Particle>.Node
	
	Method Init:Void(image:Image[],x:Float,y:Float,rotate:Float,dx:Float,dy:Float,speed:Float,alphaDec:Float,frame:Int = 0)
		Self.image = image
		Self.pos.Set(x,y)
		Self.d.Set(dx, dy)
		Self.angleRot = rotate
		Self.angle = 0
		Self.speed = speed
		Self.alphaDec = alphaDec
		Self.alpha = 1.0
		Self.frame = frame
	End Method	
	
	Method Done:Int()
		Return alpha <= 0
	End Method
	
	
	Method Update:Void() Override
		angle += angleRot
		alpha -= alphaDec 
		pos.Add(d.x * speed,d.y * speed) 
	End Method

	Method Delet:Void()
		node.Remove()
	End Method
	
	Method UnRegister:Void() Override
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.Alpha = alpha
		canvas.DrawImage(image[frame],pos.x,pos.y,angle,1,1)
		canvas.Alpha = 1.0
	End Method

End Class

Function CreateShipExplosion:Void(x:Float,y:Float)
	For Local py:Float = 0 Until 6
		For Local px:Float = 0 Until 6
			Local p:Particle = particleStore.GetItem()
			Local ang:Float = Rnd(0,360)
			p.Init(media.shipExplosionImg,x-12 + px*4,y-12 + py*4,ang,Cos(ang),Sin(ang),Rnd(1,5),.01,py*6+px)
			shipParticleList.AddLast(p)
		Next
	Next
End Function

Class Media

	Field atlas:Image
	Field bulletImg:Image[]
	Field ExplosionImg:Image[]
	Field playerImg:Image[]
	Field gripperImg:Image[]
	Field lazerImg:Image
	Field teslaImg:Image[]
	Field boxedImg:Image[]
	Field micronImg:Image[]
	Field ufoImg:Image[]
	Field specialImg:Image[]
	Field starsImg:Image[]
	Field alienImg:Image
'	Field backGroundImg:Image
	Field trailImg:Image[]
	Field shipExplosionImg:Image[]
	Field explosionImg:Image[]
	Field meteorImg:Image[]
	Field gunbImg:Image
	Field heartImg:Image
	Field gunImg:Image
	Field shieldImg:Image
	Field woopSnd:Sound
	
	Field shoot1:Sound
	Field explode1:Sound
	Field shoot2:Sound
	Field explode2:Sound
	Field explode3:Sound
	Field shoot3:Sound
	Field laser:Sound
	Field music:Sound

	Field channel:Channel[]
	Field channelIndex:Int

	Method New()
		atlas = Image.Load("asset::aliens.png")
'		backGroundImg = Image.Load("asset::background.png")
		LoadImages()
		LoadSounds()
		channelIndex = 0	
	End Method
	
	Method LoadImages:Void()

		alienImg = New Image(atlas,0,202,367,310)

		starsImg = New Image[8]
		For Local i:int = 0 Until 8
			starsImg[i] = New Image(atlas,192+16*i,16,16,16)
			starsImg[i].Handle = New Vec2f(.5,.5)
		Next
		
		trailImg = New Image[8]
		For Local i:Int = 0 Until 8
			trailImg[i] = New Image(atlas,192+16*i,16,16,16)
			trailImg[i].Handle = New Vec2f(.5,.5)
		next
		
		shipExplosionImg = New Image[36]
		For Local i:Int = 0 Until 36
			shipExplosionImg[i] = New Image(atlas,0+4*i,64,4,4)
			shipExplosionImg[i].Handle = New Vec2f(.5,.5)
		next
		
		explosionImg = New Image[8]
		For Local i:Int = 0 Until 8
			explosionImg[i] = New Image(atlas,0+24*i,88,24,24)
			explosionImg[i].Handle = New Vec2f(.5,.5)
		Next
		
		meteorImg = New Image[16]
		For Local i:int = 0 Until 16
			meteorImg[i] = New Image(atlas,0+24*i,120,24,24)
			meteorImg[i].Handle = New Vec2f(.5,.5)
		next
		ufoImg = New Image[4]
		For Local i:Int = 0 Until 4
			ufoImg[i] = New Image(atlas,0+40*i,144,40,20)
			ufoImg[i].Handle = New Vec2f(.5,.5)
		Next
		gripperImg = New Image[2]
		gripperImg[0] = New Image(atlas,0,0,24,24)
		gripperImg[1] = New Image(atlas,24,0,24,24)
		
		teslaImg = New Image[2]
		For Local i:Int =  0 Until 2
			teslaImg[i] = New Image(atlas,48+24*i,0,24,24)
			teslaImg[i].Handle = New Vec2f(.5,.5)
		Next
		
		bulletImg = New Image[1]
		bulletImg[0] = New Image(atlas,152,56,8,8)
		bulletImg[0].Handle = New Vec2f(.5,.5)
		
		micronImg = New Image[4]
		For Local i:Int = 0 Until 4
			micronImg[i] = New Image(atlas,0+16*i,48,16,16)
			micronImg[i].Handle = New Vec2f(.5,.5)
		Next
		boxedImg = New Image[3]
		For Local i:Int = 0  Until 3
			boxedImg[i] = New Image(atlas,96+24*i,24,24,24)
			boxedImg[i].Handle = New Vec2f(.5,.5)
		Next
		
		lazerImg = New Image(atlas,152,48,16,1)
		lazerImg.Handle = New Vec2f(.5,0)
		
		gunbImg = New Image(atlas,152,53,16,3)
		gunbImg.Handle = New Vec2f(.5,1)
		
		playerImg = New Image[2]
		For Local i:Int = 0 Until 2
			playerImg[i] = New Image(atlas,144+24*i,0,24,24)
			playerImg[i].Handle = New Vec2f(.5,.5)
		Next
		
		specialImg = New Image[3]
		specialImg[0] = New Image(atlas,195,88,18,18)
		specialImg[1] = New Image(atlas,213,88,28,18)
		specialImg[2] = New Image(atlas,249,88,18,18)
		
	End Method
	
	Method LoadSounds:Void()
		shoot1 = Sound.Load("asset::shoota.ogg")
		shoot2 = Sound.Load("asset::hita.ogg")
		shoot3 = Sound.Load("asset::fireball.ogg")
		explode1 = Sound.Load("asset::hit.ogg")
		explode2 = Sound.Load("asset::explosion.ogg")
		explode3 = Sound.Load("asset::bomb0.ogg")
		laser = Sound.Load("asset::laser.ogg")
		woopSnd = Sound.Load("asset::woop.ogg")
		music = Sound.Load("asset::kickshock.ogg")
		
		channel = New Channel[9]
		For Local i:Int = 0 Until 9
			channel[i] = New Channel
		Next
		channel[0].Volume = 0	
		channel[0].Play(shoot2)	
		channel[0].Volume = 1
	End Method

	Method ShootSnd1:Void()
		channel[channelIndex].Play(shoot1)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method ShootSnd2:Void()
		channel[channelIndex].Play(shoot2)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method ShootSnd3:Void()
		channel[channelIndex].Play(shoot2)
		channelIndex = (channelIndex+1) Mod 8
	End Method

	Method ExplodeSnd1:Void()
		channel[channelIndex].Play(explode1)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method ExplodeSnd2:Void()
		channel[channelIndex].Play(explode2)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method ExplodeSnd3:Void()
		channel[channelIndex].Play(explode3)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method LaserSnd:Void()
		channel[channelIndex].Play(laser)
		channelIndex = (channelIndex+1) Mod 8
	End Method
	
	Method WoopSnd:Void()
		channel[channelIndex].Play(woopSnd)
		channelIndex = (channelIndex+1) Mod 8
	End Method
			
	Method PlayTune:Void()
		channel[8].Play(music,True)
	End Method
	
	Method StopMusic()
		channel[8].Stop()
	End Method
		
	
End Class

Class Meteor Extends Entity
	Field speed:Float
	Field index:Float
	Field frameCount:Int
	Field frameTime:Int
	
	Method New(x:Float,y:Float,angle:Float,speed:Float)
		Self.image = media.meteorImg
		Self.pos.Set(x,y)
		Self.d.Set(Cos(angle),Sin(angle))
		Self.speed = speed
		Self.frameDelay = 100
		Self.frameTime = currentTime
		Self.frameCount = image.Length
	End Method
	
	Method UnRegister:Void() Override
	End Method

	Method Update:Void() Override
		pos.Add(d.x * speed,d.y * speed)
		If pos.x > 656 And d.x > 0 pos.x = -16
		If pos.x < -16 And d.x < 0 pos.x = 656
		If pos.y > 496 And d.y > 0 pos.y = -16
		If pos.y < -16 And d.y < 0 pos.y = 496
		
		If frameTime + frameDelay < currentTime
			index = (index + 1) Mod frameCount
			frameTime = currentTime
		Endif
	End Method
	
	Method Render:Void(canvas:Canvas) Override
		canvas.DrawImage(image[index],pos.x,pos.y,0,1.5,1.5)
	End Method
	
End Class

Class ParticleA
	Field pos:PVector2D
	Field V:PVector2D
	Field D:PVector2D
	Field G:PVector2D
	Field Speed:Float
	Field image:Image[]
	Field frame:Int
	Field alpha:Float
	
	Method New()
		pos = New PVector2D
		D = New PVector2D
		V = New PVector2D
		G = New PVector2D
	End Method
		
	Method New(x:Int,y:Int,speed:Float,dir:Float,image:Image[],frame:Int = 0, gx:Float = 0, gy:Float = 0)
		Self.image = image
		If image = Null DebugStop()
		Self.frame = frame
		pos = New PVector2D(x,y)
		D = New PVector2D(Cos(dir),Sin(dir))
		V = New PVector2D(D).Multiply(speed)
		G = New PVector2D(gx,gy)
	End Method
	
	Method Set:ParticleA(x:Int,y:Int,speed:Float,dir:Float,image:Image[],frame:Int = 0, gx:Float = 0, gy:Float = 0,alpha:Float = 1)
		Self.image = image
		Self.frame = frame
		Self.alpha = alpha
		pos.Set(x,y)
		D.Set(Cos(dir),Sin(dir))
		V.Set(D).Multiply(speed)
		G.Set(gx,gy)
		Return Self
	End Method
	
		
	Method Update:Bool()
		Local done:Bool = False
		pos.Add(V.Add(G))
		alpha -= .02
		If alpha <= 0
			done = true
		Endif
		Return done
	End Method
	
	Method Render:Void(canvas:Canvas)
		canvas.Alpha = alpha
		canvas.DrawImage(image[frame], pos.x, pos.y,0,2,2)
	End Method
	
End Class


Class Stars
	Field stars:PVector2D[]
	Field starsImg:Image[]
	Field starsIdx:Int[]
	Field starsAlp:Float[]
	
	Const TOTALSTARS:Int = 150
	
	Method New()
		starsImg = media.starsImg
		stars = New PVector2D[TOTALSTARS]
		starsIdx = New Int[TOTALSTARS]
		starsAlp = New Float[TOTALSTARS]
		For Local i:int = 0 Until TOTALSTARS
			stars[i] = New PVector2D(Rnd(640),Rnd(480))
			starsIdx[i] = Rnd(7)
			starsAlp[i] = Rnd()
		Next
	
	End Method
	
	Method Update:Void()
		For Local i:Int = 0 Until TOTALSTARS
			starsAlp[i] -= .005
			If starsAlp[i] < 0
				starsAlp[i] = 1.0
			Endif 
		Next
	End Method
		
	
	Method Render:Void(canvas:Canvas)
		canvas.BlendMode = BlendMode.Additive
		For Local i:Int = 0 Until TOTALSTARS
			canvas.Alpha = starsAlp[i]
			canvas.DrawImage(starsImg[starsIdx[i]],stars[i].x,stars[i].y)
		Next
		canvas.BlendMode = BlendMode.Alpha
		canvas.Alpha = 1.0
	End Method
End Class

Class Timer
	Field x:Float
	Field y:Float
	Field startTime:Int
	Field duration:Int
	Field timeRemaining:Int
	Field lapsedTime:Int
	
	Const SECOND:Int = 1000
	
	Method New(duration:Int,x:Float,y:Float)
		startTime = currentTime
		Self.duration = duration
		lapsedTime = currentTime - startTime
		timeRemaining = ((duration - lapsedTime)/SECOND)
	End Method
	
	Method Reset:Void()
		startTime = currentTime
		lapsedTime = currentTime - startTime
		timeRemaining = ((duration - lapsedTime)/SECOND)	
	End Method
	
	Method Expire:Void()
		startTime = currentTime - (duration+duration)
		Update()
	End Method
	
	Method Update:Int()
		lapsedTime = currentTime - startTime
		timeRemaining = ((duration - lapsedTime)/SECOND)
		If timeRemaining < 0 
			timeRemaining = 0
			Return False
		Endif
		Return True
	End Method

	Method Render:Void(canvas:Canvas)
		canvas.Color = New Color(0,1,0) '0,255,0
		RenderText(canvas,"Seconds Left :"+timeRemaining,x,y) '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

	End Method
	
End Class
