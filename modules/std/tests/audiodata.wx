
#Import "<std>"

Using std..

Function Main()
	
	Local data:=New AudioData[4]
	
	data[0]=New AudioData( 1,AudioFormat.Mono8,11025 )
	data[1]=New AudioData( 1,AudioFormat.Stereo8,11025 )
	data[2]=New AudioData( 1,AudioFormat.Mono16,11025 )
	data[3]=New AudioData( 1,AudioFormat.Stereo16,11025 )
	
	For Local i:=0 Until 4
		Print "i="+i
		For Local f:=-1.0 To 1.0 Step .125
			Print "SetSample="+f
			data[i].SetSample( 0,f )
			Print "GetSample="+data[i].GetSample( 0 )
		Next
	Next

End
