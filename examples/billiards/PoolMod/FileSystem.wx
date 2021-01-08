#Import "<mojo>"

Class DataConversion

	Method StringToInt:Int(val:String)
		Return Int(val)
	End

	Method IntToString:String(val:Int)
		Return String(val)
	End
End

Class FileSystem Extends DataConversion
	
	Field fileData:String=""
	
	Field index:StringMap<FileStream>
	
	Field _header:String="MKYDATA"
	
	Method LoadAll:Void()
	
		Local numFiles:Int=0
		
		Local stream:FileStream
		
		Local len:Int=0
		
		Local ptri:Int=0
		
'		Self.fileData=LoadState() '********************************************************* fix this ****************
		
		Self.index=New StringMap<FileStream>
		
		If(Self.fileData.Length>0)
			
			If(Self.fileData.StartsWith(Self._header))
				
				Self.index.Clear()
				
				ptri+=Self._header.Length
				
				numFiles=Self.StringToInt(Self.fileData.Mid(ptri,3)) '.[ptr..ptr+3])
				
				ptri+=3
				
				If(numFiles>0)
					
					For Local n:Int=1 To numFiles
						
						stream=New FileStream()
						
						len=Int(Self.fileData.Mid(ptri,3)) ',[ptr..ptr+3])
						
						ptri+=3
						
						If(len>0)
						
							stream.filename=Self.fileData.Mid(ptri,len) '[ptr..ptr+len]
						
							ptri+=len
						
						End
						
						len=Int(Self.fileData.Mid(ptri,3)) '[ptr..ptr+3])
						
						ptri+=3
						
						If(len>0)
						
							stream.data=Self.fileData.Mid(ptri,len) '[ptr..ptr+len]
						
							ptri+=len
						
						End
						
						Self.index.Add(stream.filename,stream)
					
					End
				End
			End
		Else
'			SaveState("") '********************************** fix this *********************************************8
		End
	End
	
	Method New()
		Self.LoadAll()
	End
	
	Method FileExists:Bool(filename:String)
		
		filename=filename.ToLower()
		
		If(Self.index.Contains(filename))
		
			Return True
		
		Else
		
			Return False
		
		End
	
	End
	
	Method ReadFile:FileStream(filename:String)
	
		filename=filename.ToLower()
	
		Local f:FileStream
	
		f=Self.index.Get(filename)
		f.fileptr=0
	
		Return f
	
	End
	
	Method WriteFile:FileStream(filename:String)
	
		Local f:FileStream= New FileStream()
	
		f.filename=filename.ToLower()
	
		f.fileptr=0
	
		Self.index.Add(f.filename.ToLower(),f)
	
		Return f
	
	End
	
	Method SaveAll:Void()
	
		Local f:FileStream
	
		Self.fileData=Self._header
	
		Self.fileData=Self.fileData+Self.IntToString(Self.index.Count())
	
		If(Self.index.Count()>0)
	
			For f = Eachin Self.index.Values 
	
				Self.fileData=Self.fileData+Self.IntToString(f.filename.Length)
	
				If(f.filename.Length>0)
	
					Self.fileData=Self.fileData+f.filename
	
				End
	
				Self.fileData=Self.fileData+Self.IntToString(f.data.Length)
	
				If(f.data.Length>0)
	
					Self.fileData=Self.fileData+f.data
	
				End
	
			End
	
		End
	
		' SaveState(Self.fileData) '************************* fix ***************************
	End
End

Class FileStream Extends DataConversion
	
	Field filename:String=""
	
	Field data:String=""
	
	Field fileptr:Int=0
	
	Method ReadString:String()
		
		Local result:String=""
		
		Local strLen:Int=Int(Self.data.Mid(Self.fileptr,3)) '[Self.fileptr..Self.fileptr+3])
		
		Self.fileptr+=3
		
		If(strLen>0)
		
			result=Self.data.Mid(Self.fileptr,strLen) '[Self.fileptr..Self.fileptr+strLen]
		
			Self.fileptr+=strLen
		
		End
		
		Return result
	
	End
	
	Method ReadInt:Int()
	
		Local result:String=""
	
		result=Self.data.Mid(Self.fileptr,3) '[Self.fileptr..Self.fileptr+3]
	
		Self.fileptr+=3
	
		Return Int(result)
	
	End
	
	Method WriteString:Void(val:String)
	
		Self.data=Self.data+Self.IntToString(val.Length)
	
		If(val.Length>0)
	
			Self.data=Self.data+val
	
		End
	
	End
	
	Method WriteInt:Void(val:Int)
	
		Self.data=Self.data+Self.IntToString(val)
	
	End
	
End
