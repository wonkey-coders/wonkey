
'TO DO: different loop behaviors ( loop, stop, bounce, random )
Class Sprite Extends GameGraphics

	Field timeScale := 1.0			'Adjusts playback speed. Can be used to create slow motion effects without setting the framerate.
	Field frameRate := 10			'in frames per second
	
	Field animations := New StringMap< AnimationClip >		'List of available animation clips
	
	Private
	
	Field _time:Int					'main time. Can be overriden in the Draw() method.
	Field _period:Int				'how many millisecs for each frame
	Field _listFrame:Int			'looped animation clip frame number
	Field _clampedListFrame:Int		'ensures not out-of-bounds value
	Field _duration:Int				'how long the current animation clip is
	Field _frame:Int				'current frame being played
	Field _startTime:Int			'keeps track of when the last Reset() ocurred
	Field _anim := ""				'The animation clip last played

	Public
	
	'************************************* Instance Properties *************************************
	
	'Current frame
	Property Frame:Int()
		Return _frame
	End


	'************************************* Instance Methods *************************************

	'Loads images[] and initializes itself
	Method New( ImagePath:String, Totalframes:Int=1, cellWidth:Int, cellHeight:Int, filter:Bool = True )
		images = LoadFrames( ImagePath, Totalframes, cellWidth, cellHeight, filter )
		Handle = New Vec2f( 0.5, 0.5 )
		Reset()
	End

	'Use this to restart the playback from frame 0
	Method Reset()
		_startTime = Millisecs()
	End

	'main drawing. You can override the time to offset instances of the same sprite.
	Method Draw( canvas:Canvas, anim:String, x:Float, y:Float, rotation:Float = 0.0, scaleX:Float = 1.0, scaleY:Float = 1.0, time:Int = -1 )

		Local _anim := animations.Get( anim )
	
		If debug Or Not _anim
			Local w := images[ _frame ].Width
			Local h := images[ _frame ].Height
			DrawOutline( canvas, x, y, w, h , rotation, scaleX, scaleY )
		End
		If Not _anim
			canvas.DrawText( "Sprite: AnimationClip '" + anim + "' is undefined", x, y )
			Return
		End
		
		'Override _time with any time value above -1
		If time < 0
			_time = Millisecs() - _startTime
		Else
			_time = time 
		End
		_period = ( 1000 / frameRate ) / timeScale	

		If _anim.loop
			_listFrame = _time Mod ( _anim.frame.Length * _period )
			_clampedListFrame = Clamp( _listFrame/_period, 0, _anim.frame.Length - 1 )			
		Else
			_clampedListFrame = Clamp( _time/_period, 0, _anim.frame.Length - 1 )
		End
		
		_frame = _anim.frame[ _clampedListFrame ]

		If images
			canvas.DrawImage( images[ _frame ], x, y, rotation, scaleX, scaleY )
		Else
			canvas.DrawText( "Sprite: No image loaded", x, y )
		End		
	End

	'How long this animation clip is in milliseconds
	Property Duration:Int( anim:String )
		Local a := animations.Get( anim )
		If Not a Then Return 0
		_period = ( 1000 / frameRate ) / timeScale
		Return _period * a.Count()				
	End	
	
	'Adds new animation clips. Won't draw anything until you create at least one animation clip
	Method AddAnimationClip( _id:String, _frames:Int[], _loop:Bool = True )
		local animClip := New AnimationClip()
		animClip.id = _id
		animClip.loop = _loop
		animClip.frame = _frames
		animations.Add( _id, animClip )
	End

End

'*******************************************************************'

'AnimationClips contain a sequence of frames to be played
Class AnimationClip

	field id			:String			'Animation name
	field frame 		:Int[]			'Frame list array, contains the sequence in which the frames play
	field loop			:= True			'looping can be controlled per animation

	Method Count:Int()
		Return frame.Length
	End

End
