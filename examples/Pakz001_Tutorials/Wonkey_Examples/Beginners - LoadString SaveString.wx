#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..


Class MyWindow Extends Window
	' This is the string which we save
	Field mystring:String="This could be a string filled with tile data...."
	Method New()
		' Set The title of the window...
		Title="LoadString and SaveString"
		' Save/create the field 'mystring'
		savefile(mystring)		
		' Put the data from the file into mystring.
		mystring = readfile()
	End Method
	
	Method OnRender( canvas:Canvas ) Override
		App.RequestRender() ' Activate this method 
		' Clear with black color
		canvas.Clear(Color.Black)
		' Draw the text at 100,100
		canvas.DrawText(mystring,100,100)
		' if key escape then quit
		If Keyboard.KeyReleased(Key.Escape) Then App.Terminate()		
	End Method	
	
End	Class

Function savefile(savedata:String)
		' Save text into mydata.txt
		SaveString(savedata,AssetsDir()+"mydata.txt" )
End Function

Function readfile:String()
	' Load text from mydata.txt
	Return LoadString( AssetsDir()+"mydata.txt" )
End Function

Function Main()
	New AppInstance		
	New MyWindow
	App.Run()
End Function
