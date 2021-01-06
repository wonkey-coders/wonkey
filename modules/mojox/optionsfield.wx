
Namespace mojox

Class OptionsField Extends DockingView

	Field CurrentChanged:Void()

	Method New( options:String[],current:Int=0 )
	
		_options=options
		
		_current=current
		
		_group=New CheckGroup
		
		_group.CheckedChanged+=Lambda()
		
			For Local i:=0 Until _checks.Length
				If _group.Checked=_checks[i]
					_current=i
					CurrentChanged()
					Return
				Endif
			Next
			
		End

		_checks=New CheckButton[options.Length]
		
		For Local i:=0 Until options.Length
		
			_checks[i]=New CheckButton( _options[i],,_group )
			
			AddView( _checks[i],"left" )
		
		Next
		
		_checks[_current].Checked=True
	End
	
	Property Current:Int()
	
		Return _current
	
	Setter( current:Int )
	
		_current=current
		
		_checks[_current].Checked=True
	End
	
	Private

	Field _options:String[]
	
	Field _current:Int
	
	Field _group:CheckGroup
	
	Field _checks:CheckButton[]
	
End
