
Namespace linqtest
 
#Import "<std>"
#Import "<linq>"
 
Using std..
Using linq
 
Function Main:Void()
 
	Local list := New List<String>()
 
	If not list.Any()
		
		list.Add("ABC")
		list.Add("DEF")
		list.Add("GHI")
		
		Local x := list.First2(Lambda:Bool(item:String)
			return item = "DEF"
		End)
		
		Print(x)
		
	End
	
End
