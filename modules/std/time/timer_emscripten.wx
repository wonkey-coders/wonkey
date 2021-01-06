
#If __TARGET__="emscripten"

#Import "<emscripten>"

Namespace std.timer

Private

Using std.time
Using std.collections
Using emscripten

'GC protection!
Global _timers:=New Map<Timer,Bool>

Public

'Have to poll with emscripten...
'
Class Timer

	Method New( hertz:Double,fired:Void() )
	
		_period=1/hertz
		_timeout=Now()+_period
		_fired=fired
		
		_context.timer=self
		
		emscripten_async_call( Callback,Cast<Byte Ptr>( Varptr _context ),_period * 1000 )

		_timers[Self]=True
	End
	
	Property Suspended:Bool()
	
		Return _suspended
	
	Setter( suspended:Bool )
	
		_suspended=suspended
	End
	
	Method Cancel()
	
		_cancelled=True
	End
	
	Private
	
	Struct Context
		Field timer:Timer
	End
	
	Field _period:Double
	Field _timeout:Double
	Field _fired:Void()
	Field _suspended:Bool
	Field _cancelled:Bool
	Field _context:Context
	
	Function Callback( arg:Void Ptr )
	
		Local context:=Cast<Context Ptr>( arg )
		
		context->timer.Update()
	End
	
	Method Update()
	
		While Not _cancelled
			
			Local now:=Now()
			
			Local sleep:=Int((_timeout-now)*1000)
			If sleep>0
				emscripten_async_call( Callback,Cast<Byte Ptr>( Varptr _context ),sleep )
				Return
			Endif
				
			If Not _suspended _fired()

			_timeout+=_period
		Wend
		
		_timers.Remove( Self )
	End
	
End

#Endif
