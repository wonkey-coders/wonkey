
#Import "<std>"

Using std..

Class Parser
	
	Method New( text:String )
		
		_text=text
		
		Bump()
	End
	
	Property Text:String()
		
		Return _text
	End
	
	Property Toke:String()
		
		Return _toke
	End
	
	Property TokePos:Int()
		
		Return _tokePos
	End
	
	Method Bump:String()
		
		While PeekChr() And PeekChr()<=32
			ParseChr()
		End
		
		_tokePos=_pos
		Local chr:=ParseChr()
		
		If IsAlpha( chr ) Or chr=95
			
			While IsIdent( PeekChr() )
				ParseChr()
			Wend
			
		Else If chr=35 And (IsAlpha( PeekChr() ) Or PeekChr()=95 )		'#ident

			ParseChr()
			While IsIdent( PeekChr() )
				ParseChr()
			Wend
			
		Else If chr=48 And PeekChr()=120			'0x
			
			ParseChr()
			While IsHexDigit( PeekChr() )
				ParseChr()
			Wend
			
		Else If IsDigit( chr )

			While IsDigit( PeekChr() )
				ParseChr()
			Wend
			
		Endif
		
		_toke=_text.Slice( _tokePos,_pos )
		
		Return _toke
	End
	
	Method Error( err:String )
		
		Print "ERROR: "+err
		
		Print "Text: "+_text
		
		Print "Toke: "+Toke
	End
	
	Method Parse:String()
		
		Local toke:=Toke
		
		If Not toke Error( "Unexpected EOI" )
		
		Bump()
		
		Return toke
	End
	
	Method Parse( toke:String )
		
		If toke<>Toke Error( "Expecting:"+toke )
			
		Bump()
	End
	
	Method CParse:Bool( toke:String )
		
		If toke=Toke Bump() ; Return True
		
		Return False
	End

	Method ParseIdent:String()
		
		If Toke And IsIdent( Toke[0] ) 
			Local ident:=Toke
			Bump()
			Return ident
		End
		
		Error( "Expecting identifier" )
		
		Return ""
	End
	
	Method CParseIdent:String()

		If Toke And IsIdent( Toke[0] ) 
			Local ident:=Toke
			Bump()
			Return ident
		End
		
		Return ""
	End
	
	Method ParseType:String()
		
		Local isconst:=CParse( "const" )
		
		Local type:=Parse()
		If type="void" Or type="GLvoid" type="Void"
		
		If CParse( "*" )
			If isconst And type="GLchar" type="CString" Else type+=" Ptr"
		Endif
		
		isconst=CParse( "const" )
		
		If CParse( "*" ) type+=" Ptr"
		
		Return type
	End
	
	Private

	Field _text:String
	Field _toke:String
	Field _pos:Int
	Field _tokePos:Int
	
	Method PeekChr:Int()
		
		Return _pos<_text.Length ? _text[_pos] Else 0
	End
	
	Method ParseChr:Int()
		
		Local chr:=PeekChr()

		If _pos<_text.Length _pos+=1
			
		Return chr
	End
	
End

Function FixIdent:String( ident:String )
	Select ident
	Case "ptr" Return "p"
	Case "string" Return "s"
	End
	Return ident
End

Function Main()
	
'	ChangeDir( "../../../" )

	ChangeDir( "modules/opengl/glew-2.1.0/src" )
	
	Print CurrentDir()
	
	Local src:=LoadString( "gles20.h" )
	
	Local lines:=New StringStack
	
	For Local line:=Eachin src.Split( "~n" )
		
		line=line.Trim()
		If Not line Continue
		
		Local p:=New Parser( line )
		Select p.Toke
		Case "typedef"
			
			Continue
			
		Case "#define"
			
			p.Bump()
			
			Local ident:=p.CParseIdent()
			
			If Not ident.StartsWith( "GL_" ) Continue
			
			Local value:=p.Toke
			
			If value.StartsWith( "0x" ) value="$"+value.Slice( 2 )
				
'			Print "#define "+ident+" "+value
		
		Case "GL_APICALL"
			
			p.Bump()

			Local pos:=p.TokePos			
			Local rtype:=p.ParseType()
			Local ctype:=p.Text.Slice( pos,p.TokePos )
			
			p.Parse( "GL_APIENTRY" )

			Local ident:=p.ParseIdent()
			
			Local argtys:="",cargs:=""

			p.Parse( "(" )
			
			If p.Toke<>")"
				
				Repeat
				
					pos=p.TokePos
					Local argty:=p.ParseType()
					If argty="Void" Exit
					
					Local argid:=FixIdent( p.ParseIdent() )
					
					If argtys argtys+=","
					argtys+=argid+":"+argty
					
					If cargs cargs+=","
					cargs+=p.Text.Slice( pos,p.TokePos )
					
					If Not p.CParse( "," ) Exit
					
				Forever
			
			Endif
			
			p.Parse( ")" )
				
			p.Parse( ";" )
			
			Print "Function "+ident+":"+rtype+"("+argtys+")"
			
'			Print ctype+"(*"+ident+")("+cargs+");"
		
		End
	
	Next

End

	