#Import "<std>"
#Import "<mojo>"
#Import "<sdl2>"
#import "<sdl2-mixer>"

#Import "audiopipe.monkey2"

Using std..
Using mojo..
Using sdl2..

Global AppTitle:String="VSynth 0.01 Big Ben Release"	
Global Contact:="Latest Source=github.com/nitrologic/m2"

Global About:="VSynth Control"
Global Octave1:= "Sharps=    W   E       T   Y   U      "
Global Octave0:= "Notes=A   S   D  F   G   H    J  K"
Global Controls:="Reset Keys=Space,Quit=Escape"

Global OscillatorNames:=New String[]("Square","Sine","Sawtooth","Triangle","Noise")
Global EnvelopeNames:=New String[]("Plain","Punchy","SlowOut","SlowIn")
Global ArpNames:=New String[]("None","Natural","Ascending","Descending","UpDown","Random")

Alias V:Double ' Voltage(volts)
Alias F:Double ' Frequency(hz)
Alias T:Double ' Time(seconds)

Alias Note:Int
Alias K:Key

Public

Global instance:AppInstance
Global vsynth:VSynth

Global Duration:=0
Global FragmentSize:=1024
Global WriteAhead:=8192
Global AudioFrequency:=44100

Const MaxPolyphony:=16

Class Envelope
	Field p:V
	Method On:V() Virtual
		Return 1.0
	End
	Method Off:V() Virtual
		Return 0.0
	End
End

Class ADSR Extends Envelope
	Field attack:T
	Field decay:T
	Field sustain:V
	Field release:T
	
	Method New(a:T,d:T,s:V,r:T)
		attack=a
		decay=d
		sustain=s
		release=r
	End
	
	Field t:T
	Field noteOn:Bool

	Method On:V() Override
		If Not noteOn
			t=0
			noteOn=True
		Endif
		t+=1.0/AudioFrequency
		If t<attack Return t/attack
		If t-attack<decay Return 1.0-((1-sustain)*(t-attack)/decay)
		Return sustain
	End

	Method Off:V() Override
		noteOn=False
		t+=1.0/AudioFrequency
		If t<release 
			Return 1.0-t/release
		Endif
		Return 0.0
	End
End


Class Oscillator
	Field delta:T
	Method Sample:V(hz:F) Virtual
		Return 0
	End
End

Class Sine Extends Oscillator	
	Method Sample:V(hz:F) Override
		Local t:T=hz/AudioFrequency
		delta+=t
		Return Sin(Pi*delta)
	End
End

Class Sawtooth Extends Oscillator
	Method Sample:V(hz:F) Override
		Local t:T=hz/AudioFrequency
		delta+=t		
		Return ((delta+1) Mod 2)-1
	End
End

Class Triangle Extends Oscillator
	Method Sample:V(hz:F) Override
		Local t:T=2*hz/AudioFrequency
		delta+=t
		Return (Abs(delta Mod 4)-2)-1
	End
End

Class Square Extends Oscillator
	Method Sample:V(hz:F) Override
		Local t:T=hz/AudioFrequency
		delta+=t
		Return -1+2*(Int(delta)&1)
	End
End

Class Noise Extends Oscillator
	Field a:V
	Method Sample:V(hz:F) Override
		Local t:T=hz/AudioFrequency
		Local delta0:=delta
		delta+=t		
		Local f:=delta Mod 1				
		If Int(delta0)<>Int(delta)
			a=Rnd()
		Endif	
		Return 1-2*a	'(a+f*(b-a)		
	End
End

Class Voice
	Field oscillator:Oscillator
	Field envelope:Envelope
	Field noteOn:Bool
	Field hz:F
	Field pan:V
	Field gain:V=0.12
	
	Method SetOscillator(osc:Int)
		Select osc
			Case 0 oscillator=New Square
			Case 1 oscillator=New Sine
			Case 2 oscillator=New Sawtooth
			Case 3 oscillator=New Triangle
			Case 4 oscillator=New Noise
		End
	End
	
	Method SetEnvelope(env:Int)
		Select env
			Case 0 
				envelope=New ADSR(0.05,1.5,0.2,0.3)
			Case 1
				envelope=New ADSR(0.06,0.01,0.92,0.2)
			Case 2 
				envelope=New ADSR(0.06,2.0,0.2,1.2)
			Case 3
				envelope=New ADSR(0.2,0.2,0.92,0.4)
		End
	End

	Method SetPan(value:V)
		pan=value
	End
	
	Method SetGain(value:V)
		gain=value
	End

	Method Stop()
		NoteOff()
		envelope.Off()
	End	
	
	Method NoteOn(note:Int)
		hz=440.0*Pow(2.0,(note-67.0)/12)
		noteOn=True
	End
	
	Method NoteOff()
		noteOn=False
	End
	
	Method Mix(buffer:Double[],samples:Int,detune:V)
		Local left:=1.0
		Local right:=1.0
		If pan<0 right+=pan
		If pan>0 left-=pan		
		For Local i:=0 Until samples
			Local v:=oscillator.Sample(hz*detune)			
			Local e:V
			If noteOn e=envelope.On() Else e=envelope.Off()
			e*=gain
			buffer[i*2+0]+=e*left*v
			buffer[i*2+1]+=e*right*v
		Next
	End
End

Class VSynth

	Field audioSpec:SDL_AudioSpec
	Field buffer:=New Double[FragmentSize*2]
	Field audioPipe:=AudioPipe.Create()
	Field voices:=New Stack<Voice>
	Field polyList:=New List<Voice>
	Field polyMap:=New Map<Int,Voice>

	Field detune:V

	Method New()
		OpenAudio()
	End
	
	Method Detune(bend:V)
		detune=bend
	End
	
	Method ClearKeys()
		voices.Clear()
	End

	Method UpdateAudio()
		While True
			Local buffered:=audioPipe.writePointer-audioPipe.readPointer
			If buffered>=WriteAhead Exit
			Local samples:=FragmentSize
			Local buffer:=vsynth.FillAudioBuffer(samples)			
			Local pointer:=Varptr buffer[0]
			audioPipe.WriteSamples(pointer,samples*2)
		Wend
	End
		
	Method FillAudioBuffer:Double[](samples:Int)	
		For Local i:=0 Until samples
			buffer[i*2+0]=0
			buffer[i*2+1]=0
		Next			
		For Local voice:=Eachin voices
			voice.Mix(buffer,samples,detune)
		Next
		
		Duration+=samples
		Return buffer
	End
	
	Method OpenAudio()
		Local spec:SDL_AudioSpec
		spec.freq=AudioFrequency	
		spec.format = AUDIO_S16
		spec.channels = 2
		spec.samples = FragmentSize
		spec.callback = AudioPipe.Callback
		spec.userdata = audioPipe.Handle()
		
		Mix_CloseAudio()		
		Local error:Int = SDL_OpenAudio(Varptr spec,Varptr audioSpec)		
		If error
			Print "error="+error+" "+String.FromCString(SDL_GetError())
		Else
			Print "Audio Open freq="+audioSpec.freq
			AudioFrequency=audioSpec.freq
		Endif
				
		For Local i:=0 Until MaxPolyphony
			Local tone:=New Voice
			tone.SetOscillator(0)
			tone.SetEnvelope(0)
			polyList.AddLast(tone)
		Next
		
		SDL_PauseAudio(0)
	End

	Method NoteOn(note:Int,oscillator:Int,envelope:Int)
		NoteOff(note)
		If polyList.Empty Return
		Local voice:=polyList.RemoveFirst()
		voice.SetEnvelope(envelope)
		voice.SetOscillator(oscillator)
		voice.NoteOn(note)
		polyMap[note]=voice
		polyList.Remove(voice)
		If Not voices.Contains(voice)
			voices.Add(voice)
		Endif	
	End

	Method NoteOff(note:Int)	
		Local voice:=polyMap[note]
		If voice
			voice.Stop()
			polyMap.Remove(note)
			polyList.AddLast(voice)
		Endif
	End

End	

Class VSynthWindow Extends Window

	Const MusicKeys:=New Key[]( Key.Q,Key.A,Key.W,Key.S,Key.E,Key.D,  Key.F,Key.T,Key.G,Key.Y,Key.H,Key.U,Key.J,  Key.K,Key.O,Key.L,Key.P,Key.Semicolon)',Key.Apostrophe )

	Field frame:Int
	Field tick:Int
	Field mousex:Int
	Field mousey:Int
	
	Field oscillator:Int
	Field envelope:Int
	Field octave:Int=5
	
	Field pitchbend:V
	
	Field keyNoteMap:=New Map<Key,Int>

	Method New(title:String)
		Super.New(title,720,560,WindowFlags.Resizable)				
		For Local i:=0 Until MusicKeys.Length
			keyNoteMap.Set(MusicKeys[i],i-1)
		Next
		vsynth=New VSynth
	End
	
	Method OnRender( display:Canvas ) Override	
		App.RequestRender()	

		vsynth.Detune(Pow(2,pitchbend))
		vsynth.UpdateAudio()

		Local text:String = About+",,"+Octave1+","+Octave0+","
		text+="Octave=< >="+octave
		text+=",Oscillator=1-5="+OscillatorNames[oscillator]
		text+=",Envelope=[]="+EnvelopeNames[envelope]
		text+=",PitchBend=Mouse Wheel="+FloatString(pitchbend)
		text+=",,"+Controls+",,"+Contact

		Local cy:=40
		For Local line:=Eachin text.Split(",")
			Local cx:=50
			For Local tab:=Eachin line.Split("=")
				display.DrawText(tab,cx,cy)
				cx+=100
			Next
			cy+=20
		Next

	End				
	
	Method KeyDown(key:Key)
		Local note:=keyNoteMap[key]+octave*12
		vsynth.NoteOn(note,oscillator,envelope)
	End

	Method KeyUp(key:Key)
		Local note:=keyNoteMap[key]+octave*12
		vsynth.NoteOff(note)
	End

	Method UpdateSequence()
		frame+=1
		Local t:Int=(frame/20)	
		If t<>tick
			Local note:=((t Shr 1)&15)*3+40
			If t&1
				vsynth.NoteOn(note,oscillator,envelope)
			Else
				vsynth.NoteOff(note)			
			Endif
			tick=t
		Endif				
'		Print "tick d="+d
	End
			
	Function Limit:Int(value:Int, lo:Int, hi:Int)
		If value<lo Return lo
		If value>hi Return hi
		Return value
	End
				
	Method OnKeyEvent( event:KeyEvent ) Override	
		Select event.Type
		Case EventType.KeyDown
			Select event.Key
			Case Key.Key1
				oscillator=0
			Case Key.Key2
				oscillator=1
			Case Key.Key3
				oscillator=2
			Case Key.Key4
				oscillator=3
			Case Key.Key5
				oscillator=4
			Case Key.Escape
				instance.Terminate()
			Case Key.LeftBracket
				envelope=Wrap(envelope-1,0,EnvelopeNames.Length)
			Case Key.RightBracket
				envelope=Wrap(envelope+1,0,EnvelopeNames.Length)				
			Case Key.Comma
				octave=Clamp(octave-1,0,12)
			Case Key.Period
				octave=Clamp(octave+1,0,12)
			Case Key.Space
				vsynth.ClearKeys()
			Default
				KeyDown(event.Key)
			End
		Case EventType.KeyUp
			Select event.Key
			Case Key.Escape
			Default
				KeyUp(event.Key)
			End
		End
	End

	Method OnMouseEvent( event:MouseEvent ) Override	
		mousex=event.Location.X
		mousey=event.Location.Y
		pitchbend+=event.Wheel.Y/24.0
	End
	
End

Function FloatString:String(value:Float,dp:Int=2)
	Local sign:String
	If value<0 
		sign="-"
		value=-value
	Endif
	Local a:String=Int(value*(Pow(10,dp)))
	Local l:=dp+1-a.Length
	If l>0 a="000000".Slice(0,l)+a
	Local r:=a.Length
	Return sign+a.Slice(0,r-dp)+"."+a.Slice(r-dp)
End

Function Wrap:Int(value:Int,lower:Int,upper:Int)
	If value<lower value=upper-1
	If value>=upper value=lower
	Return value
End

Function Main()
	instance = New AppInstance	
	New VSynthWindow(AppTitle)	
	App.Run()	
End
