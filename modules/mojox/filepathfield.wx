
#if __DESKTOP_TARGET__

Namespace mojox

Class FilePathField Extends DockingView

	Field FilePathChanged:Void()

	Method New( path:String="",fileType:FileType=std.filesystem.FileType.File )
	
		_fileType=fileType

		_textField=New TextField( path )
		
		_textField.TextChanged+=Lambda()
		
			FilePathChanged()
		End

		_pathButton=New PushButton( "..." )
		
		_pathButton.Clicked=Lambda()
		
			New Fiber( Lambda()
		
				Local future:=New Future<String>
			
				App.Idle+=Lambda()
					If _fileType=FileType.Directory
						future.Set( requesters.RequestDir( "Select Directory",_textField.Text ) )
					Else
						future.Set( requesters.RequestFile( "Select File",_filter,False,_textField.Text ) )
					Endif
				End
				
				Local path:=future.Get()
				If Not path Return
				
				_textField.Text=path
				
				FilePathChanged()
			End )
		End
		
		AddView( _pathButton,"right" )

		ContentView=_textField

		MaxSize=New Vec2i( 320,0 )
	End
	
	Property FileFilter:String()
	
		Return _filter
	
	Setter( filter:String )
	
		_filter=filter
	End
	
	Property FilePath:String()
	
		Return _textField.Text
	
	Setter( path:String )
	
		_textField.Text=path
	End
	
	Property FileType:FileType()
	
		Return _fileType
	
	Setter( fileType:FileType )
	
		_fileType=fileType
	End
	
	Private

	Field _filter:String	
	Field _textField:TextField
	Field _pathButton:PushButton
	Field _fileType:FileType

End

#endif
