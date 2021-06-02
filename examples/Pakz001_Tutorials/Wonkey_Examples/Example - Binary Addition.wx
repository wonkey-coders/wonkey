#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..

' How long should the binary be
Global binlen:Int=14
' This contains the binary data. bin[0] is the most left
Global bin:Int[]


Class MyWindow Extends Window

	' keep track of the number
	Field cnt:Int=0
	
	Method New()
		' create our binary array
		bin = New Int[binlen]
	
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		
        If Keyboard.KeyReleased(Key.Space) Or Mouse.ButtonReleased(MouseButton.Left)
        	' Add one to the binary
	    	incbin()
	    	' Add up one into our count
	    	cnt+=1
	    	' if all values are zero then reset cnt
	    	Local res:Bool=True
	    	For Local i:Int=0 Until binlen
		    	If bin[i] = 1 Then res=False
		    Next
		    If res Then cnt=0
	   	End If
		
        canvas.Scale(2,2)
        canvas.DrawText("Press Space or LMB(touch) to increase",0,0)
        ' Draw the binary on the screen
		For Local i:Int=0 Until binlen
			canvas.DrawText(bin[i],i*20,100)
		Next
		canvas.DrawText(cnt,0,120)
		
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

'We go from right to left turning each 1 into a zero until
'or if we find a 0 and then we then turn this into a 1 and then return
Function incbin()
	' Loop from right to left
	For Local i:Int=binlen-1 To 0 Step -1
		' if we encounter a 0 then turn it into a 1 and return
		If bin[i] = 0 Then 
			bin[i] = 1
			Return
		End If
		' turn the next bit into a 0
		bin[i] = 0
	Next
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
