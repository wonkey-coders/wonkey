
Namespace ted2

#Import "assets/about.html@/ted2"
#Import "assets/scripts.json@/ted2"

#Import "assets/newfiles/Simple_Console_App.monkey2@/ted2/newfiles"
#Import "assets/newfiles/Simple_Mojo_App.monkey2@/ted2/newfiles"
#Import "assets/newfiles/Letterboxed_Mojo_App.monkey2@/ted2/newfiles"

Global MainWindow:MainWindowInstance

Class MainWindowInstance Extends Window

	Field _debugging:String
	
	'paths
	Field _tmp:String
	Field _mx2cc:String

	'actions
	Field _fileNew:Action
	Field _fileOpen:Action
	Field _fileClose:Action
	Field _fileCloseOthers:Action
	Field _fileCloseAll:Action
	Field _fileSave:Action
	Field _fileSaveAs:Action
	Field _fileSaveAll:Action
	Field _fileNextFile:Action
	Field _filePrevFile:Action
	Field _fileOpenProject:Action
	Field _fileQuit:Action
	
	Field _editUndo:Action
	Field _editRedo:Action
	Field _editCut:Action
	Field _editCopy:Action
	Field _editPaste:Action
	Field _editSelectAll:Action
	Field _editFind:Action
	
	Field _buildDebug:Action
	Field _buildRelease:Action
	Field _buildForceStop:Action
	Field _buildLockFile:Action
	Field _buildNextError:Action
	
	Field _helpOnlineHelp:Action
	Field _helpOfflineHelp:Action
	Field _helpAbout:Action
	
	Field _findNext:Action
	Field _findPrevious:Action
	Field _findReplace:Action
	Field _findReplaceAll:Action
	
	Field _escape:Action
	
	'menus
	Field _menuBar:MenuBar
	
	Field _newFiles:Menu
	Field _recentFiles:Menu
	Field _closeProject:Menu
	Field _scripts:Menu
	
	Field _fileMenu:Menu
	Field _tabMenu:Menu
	Field _editMenu:Menu
	Field _viewMenu:Menu
	Field _buildMenu:Menu
	Field _helpMenu:Menu
	
	Field _recent:=New Stack<String>
	Field _projects:=New Stack<String>

	'dialogs	
	Field _findDialog:FindDialog
	
	'browsers
	Field _browser:TabView
	Field _projectView:ProjectView
	Field _debugView:DebugView
	Field _helpView:HelpView
	
	Field _console:Console

	'documents
	Field _docTabber:TabView
	Field _currentDoc:Ted2Document
	Field _currentTextView:TextView
	Field _openDocs:=New Stack<Ted2Document>
	Field _lockedDoc:Ted2Document
	
	'main docking view
	Field _docker:DockingView
	
	Field _errors:=New List<Mx2Error>
	
	Method OnFileNew()
	
		OpenDocument( "" )
	End
	
	Method OnFileOpen()

		Local path:=RequestFile( "Open file...","",False )
		If Not path Return
	
		OpenDocument( path,True )
		SaveState()
	End
	
	Method OnFileClose()
	
		If Not _currentDoc Return
		
		If _currentDoc.Dirty
		
			Local buttons:=New String[]( "Save","Discard Changes","Cancel" )
		
			Select TextDialog.Run( "Close","File '"+_currentDoc.Path+"' has been modified.",buttons )
			Case 0
				If Not SaveDocument( _currentDoc ) Return
			Case 2
				Return
			End

		Endif
		
		CloseDocument( _currentDoc )
		
		SaveState()
	End
	
	Method OnFileCloseOthers()
	
		Local docs:=_openDocs.Slice( 0 )
		
		For Local doc:=Eachin docs
			If doc<>_currentDoc CloseDocument( doc )
		Next
	
	End
	
	Method OnFileCloseAll()

		Local close:=New Stack<Ted2Document>
	
		For Local doc:=Eachin _openDocs
		
			If doc.Dirty
			
				MakeCurrent( doc )

				Local buttons:=New String[]( "Save","Discard Changes","Cancel" )
			
				Select TextDialog.Run( "Close All","File '"+doc.Path+"' has been modified.",buttons )
				Case 0
					If Not SaveDocument( doc ) Return
				Case 2
					Return
				End
			
			Endif
			
			close.Add( doc )

		Next
		
		For Local doc:=Eachin close
			CloseDocument( doc )
		Next
		
		SaveState()
	End
	
	Method OnFileSave()
	
		If Not _currentDoc Return
			
		SaveDocument( _currentDoc )
	End
	
	Method OnFileSaveAs()

		If Not _currentDoc Return
			
		Local path:=RequestFile( "Save As","",True )
		If Not path Return
		
		RenameDocument( _currentDoc,path )
		SaveDocument( _currentDoc )
	End
	
	Method OnFileSaveAll()
		For Local doc:=Eachin _openDocs
			SaveDocument( doc )
		Next
	End
	
	Method OnFileNextFile()
		If _docTabber.Count<2 Return
		
		Local i:=_docTabber.CurrentIndex+1
		If i=_docTabber.Count i=0
		
		Local doc:=FindDocument( _docTabber.TabView( i ) )
		If Not doc Return
		
		MakeCurrent( doc )
	End
	
	Method OnFilePrevFile()
		If _docTabber.Count<2 Return
		
		Local i:=_docTabber.CurrentIndex-1
		If i=-1 i=_docTabber.Count-1
		
		Local doc:=FindDocument( _docTabber.TabView( i ) )
		If Not doc Return
		
		MakeCurrent( doc )
	End
	
	Method OnFileOpenProject()
	
		Local dir:=RequestDir( "Select Project Directory...","" )
		If Not dir Return
		
		If Not _projectView.OpenProject( dir ) Return
		
		_projects.Push( dir )
		UpdateCloseProjectMenu()
		
	End
	
	Method OnFileQuit()
	
		For Local doc:=Eachin _openDocs
		
			If doc.Dirty
			
				MakeCurrent( doc )

				Local buttons:=New String[]( "Save","Discard Changes","Cancel" )
			
				Select TextDialog.Run( "Quit","File '"+doc.Path+"' has been modified.",buttons )
				Case 0
					If Not SaveDocument( doc ) Return
				Case 2
					Return
				End
			
			Endif
		
		Next
		
		SaveState()
		
		_console.Terminate()
		
		App.Terminate()
	End
	
	Method OnEditUndo()

		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.Undo()
	End
	
	Method OnEditRedo()
	
		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.Redo()
	End
	
	Method OnEditCut()
	
		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.Cut()
	End

	Method OnEditCopy()

		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.Copy()
	End

	Method OnEditPaste()		
		
		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.Paste()
	End
	
	Method OnEditSelectAll()
		
		Local textView:=Cast<TextView>( App.KeyView )
		
		If textView textView.SelectAll()
	End
	
	Method OnEditFind()
	
		_findDialog.Open()
	End
	
	Method OnBuildDebug()
	
		Build( "debug" )
	End
	
	Method OnBuildRelease()
	
		Build( "release" )
	End
	
	Method OnBuildForceStop()
	
		_console.Terminate()
	End
	
	Method OnBuildLockFile()
	
		LockDoc( _currentDoc )
	End
	
	Method OnBuildNextError()

		While Not _errors.Empty And _errors.First.removed
			_errors.RemoveFirst()
		Wend
		
		If _errors.Empty Return
		
		_errors.AddLast( _errors.RemoveFirst() )
			
		GotoError( _errors.First )
	End
	
	Method OnHelpOnlineHelp()
	
		App.Idle+=Lambda()
			mojo.requesters.OpenUrl( "http://monkeycoder.co.nz/modules-reference/" )
		End
		
	End
	
	Method OnHelpOfflineHelp()
	
		App.Idle+=Lambda()
			mojo.requesters.OpenUrl( "file://"+CurrentDir()+"docs/index.html" )
		End

	End
	
	Method OnHelpAbout()
	
		Local htmlView:=New HtmlView
		htmlView.Go( "asset::ted2/about.html" )

		Local dialog:=New Dialog( "About Monkey2" )
		dialog.ContentView=htmlView
		
		dialog.MinSize=New Vec2i( 640,600 )
		
		dialog.MaxSize=Rect.Size
		
		dialog.AddAction( "Okay!" ).Triggered=Lambda()
		
			dialog.Close()
		End
		
		dialog.Open()
	
	End
	
	Method OnFindNext()
	
		If Not _currentTextView Return
		
		Local text:=_findDialog.FindText
		If Not text Return
		
		Local tvtext:=_currentTextView.Text
		Local cursor:=Max( _currentTextView.Anchor,_currentTextView.Cursor )
		
		If Not _findDialog.CaseSensitive
			tvtext=tvtext.ToLower()
			text=text.ToLower()
		Endif
		
		Local i:=tvtext.Find( text,cursor )
		If i=-1
			i=tvtext.Find( text )
			If i=-1 Return
		Endif
		
		_currentTextView.SelectText( i,i+text.Length )
	End
	
	Method OnFindPrevious()
		
		If Not _currentTextView Return
		
		Local text:=_findDialog.FindText
		If Not text Return

		Local tvtext:=_currentTextView.Text
		Local cursor:=Min( _currentTextView.Anchor,_currentTextView.Cursor )
		
		If Not _findDialog.CaseSensitive
			tvtext=tvtext.ToLower()
			text=text.ToLower()
		Endif
		
		Local i:=tvtext.Find( text )
		If i=-1 Return
		
		If i>=cursor
			i=tvtext.FindLast( text )
		Else
			Repeat
				Local n:=tvtext.Find( text,i+text.Length )
				If n>=cursor Exit
				i=n
			Forever
		End
		
		_currentTextView.SelectText( i,i+text.Length )
	End
	
	Method OnFindReplace()

		If Not _currentTextView Return
		
		Local text:=_findDialog.FindText
		If Not text Return
		
		Local min:=Min( _currentTextView.Anchor,_currentTextView.Cursor )
		Local max:=Max( _currentTextView.Anchor,_currentTextView.Cursor )
		
		Local tvtext:=_currentTextView.Text.Slice( min,max )

		If Not _findDialog.CaseSensitive
			tvtext=tvtext.ToLower()
			text=text.ToLower()
		Endif
		
		If tvtext<>text Return
		
		_currentTextView.ReplaceText( _findDialog.ReplaceText )
		
		OnFindNext()

	End
	
	Method OnFindReplaceAll()
	
		If Not _currentTextView Return
		
		Local text:=_findDialog.FindText
		If Not text Return
		
		Local rtext:=_findDialog.ReplaceText
		
		Local tvtext:=_currentTextView.Text

		If Not _findDialog.CaseSensitive
			tvtext=tvtext.ToLower()
			text=text.ToLower()
		Endif
		
		Local anchor:=_currentTextView.Anchor
		Local cursor:=_currentTextView.Cursor
		
		Local i:=0,t:=0
		Repeat
		
			Local i:=tvtext.Find( text,i )
			If i=-1 Exit
			
			_currentTextView.SelectText( i+t,i+text.Length+t )
			_currentTextView.ReplaceText( rtext )
			
			t+=rtext.Length-text.Length
			i+=text.Length
			
		Forever
		
		_currentTextView.SelectText( anchor,cursor )
		
	End
	
	Method OnEscape()
		
		If _findDialog.Visible
			_findDialog.Close()
			UpdateKeyView()
			Return
		Endif
		
		_console.Visible=Not _console.Visible
		
	End
	
	Method InitPaths()
	
		_tmp=RealPath( "tmp/" )
		
#If __HOSTOS__="macos"
		_mx2cc="bin/mx2cc_macos"
#Else If __HOSTOS__="windows"
		_mx2cc="bin/mx2cc_windows.exe"
#Else
		_mx2cc="bin/mx2cc_linux"
#Endif
		
		CreateDir( _tmp )
	End
	
	Method InitActions()
	
		_fileNew=New Action( "New" )
		_fileNew.HotKey=Key.N
		_fileNew.HotKeyModifiers=Modifier.Control
		_fileNew.Triggered=OnFileNew
		
		_fileOpen=New Action( "Open" )
		_fileOpen.HotKey=Key.O
		_fileOpen.HotKeyModifiers=Modifier.Control
		_fileOpen.Triggered=OnFileOpen

		_fileClose=New Action( "Close" )
		_fileClose.HotKey=Key.F4
		_fileClose.HotKeyModifiers=Modifier.Control
		_fileClose.Triggered=OnFileClose
		
		_fileCloseOthers=New Action( "Close Others" )
		_fileCloseOthers.Triggered=OnFileCloseOthers

		_fileCloseAll=New Action( "Close All" )
		_fileCloseAll.Triggered=OnFileCloseAll
		
		_fileSave=New Action( "Save" )
		_fileSave.HotKey=Key.S
		_fileSave.HotKeyModifiers=Modifier.Control
		_fileSave.Triggered=OnFileSave
		
		_fileSaveAs=New Action( "Save As" )
		_fileSaveAs.Triggered=OnFileSaveAs
		
		_fileSaveAll=New Action( "Save All" )
		_fileSaveAll.Triggered=OnFileSaveAll
		
		_fileNextFile=New Action( "Next File" )
		_fileNextFile.Triggered=OnFileNextFile
		_fileNextFile.HotKey=Key.Tab
		_fileNextFile.HotKeyModifiers=Modifier.Control
		
		_filePrevFile=New Action( "Previous File" )
		_filePrevFile.Triggered=OnFilePrevFile
		_filePrevFile.HotKey=Key.Tab
		_filePrevFile.HotKeyModifiers=Modifier.Control|Modifier.Shift
		
		_fileOpenProject=New Action( "Open project" )
		_fileOpenProject.Triggered=OnFileOpenProject
		
		_fileQuit=New Action( "Quit" )
		_fileQuit.Triggered=OnFileQuit
		
		_editUndo=New Action( "Undo" )
		_editUndo.HotKey=Key.Z
		_editUndo.HotKeyModifiers=Modifier.Control
		_editUndo.Triggered=OnEditUndo
		
		_editRedo=New Action( "Redo" )
		_editRedo.HotKey=Key.Y
		_editRedo.HotKeyModifiers=Modifier.Control
		_editRedo.Triggered=OnEditRedo
		
		_editCut=New Action( "Cut" )
'		_editCut.HotKey=Key.X
'		_editCut.HotKeyModifiers=Modifier.Control
		_editCut.Triggered=OnEditCut
		
		_editCopy=New Action( "Copy" )
'		_editCopy.HotKey=Key.C
'		_editCopy.HotKeyModifiers=Modifier.Control
		_editCopy.Triggered=OnEditCopy
		
		_editPaste=New Action( "Paste" )
'		_editPaste.HotKey=Key.V
'		_editPaste.HotKeyModifiers=Modifier.Control
		_editPaste.Triggered=OnEditPaste
		
		_editSelectAll=New Action( "Select All" )
'		_editSelectAll.HotKey=Key.A
'		_editSelectAll.HotKeyModifiers=Modifier.Control
		_editSelectAll.Triggered=OnEditSelectAll
		
		_editFind=New Action( "Find" )
		_editFind.HotKey=Key.F
		_editFind.HotKeyModifiers=Modifier.Control
		_editFind.Triggered=OnEditFind
		
		_findNext=New Action( "Find Next" )
		_findNext.HotKey=Key.F3
		_findNext.Triggered=OnFindNext
		
		_findPrevious=New Action( "Find Previous" )
		_findPrevious.HotKey=Key.F3
		_findPrevious.HotKeyModifiers=Modifier.Shift
		_findPrevious.Triggered=OnFindPrevious
		
		_findReplace=New Action( "Replace" )
		_findReplace.Triggered=OnFindReplace
		
		_findReplaceAll=New Action( "Replace All" )
		_findReplaceAll.Triggered=OnFindReplaceAll
		
		_buildDebug=New Action( "Debug" )
		_buildDebug.HotKey=Key.F5
		_buildDebug.Triggered=OnBuildDebug
		
		_buildRelease=New Action( "Release" )
		_buildRelease.HotKey=Key.F6
		_buildRelease.Triggered=OnBuildRelease
		
		_buildForceStop=New Action( "Force Stop" )
		_buildForceStop.HotKey=Key.F5
		_buildForceStop.HotKeyModifiers=Modifier.Shift
		_buildForceStop.Triggered=OnBuildForceStop

		_buildLockFile=New Action( "Lock Build File" )
		_buildLockFile.HotKey=Key.L
		_buildLockFile.HotKeyModifiers=Modifier.Control
		_buildLockFile.Triggered=OnBuildLockFile
		
		_buildNextError=New Action( "Next Error" )
		_buildNextError.HotKey=Key.F4
		_buildNextError.Triggered=OnBuildNextError
		
		_helpOnlineHelp=New Action( "Online Help" )
		_helpOnlineHelp.Triggered=OnHelpOnlineHelp

		_helpOfflineHelp=New Action( "Offline Help" )
		_helpOfflineHelp.Triggered=OnHelpOfflineHelp
		
		_helpAbout=New Action( "About Monkey2" )
		_helpAbout.Triggered=OnHelpAbout
		
		_escape=New Action( "" )
		_escape.HotKey=Key.Escape
		_escape.Triggered=OnEscape
	End
	
	Method InitMenus()
	
		_newFiles=New Menu( "New..." )
		Local p:=AssetsDir()+"ted2/newfiles/"
		For Local f:=Eachin LoadDir( p )
			Local src:=stringio.LoadString( p+f )
			_newFiles.AddAction( StripExt( f.Replace( "_"," " ) ) ).Triggered=Lambda()
				Local doc:=Cast<Mx2Document>( OpenDocument( "" ) )
				If doc
					doc.TextDocument.Text=src
					doc.Save()
				Endif
			End
		Next
		
		_scripts=New Menu( "Scripts..." )
		Local obj:=JsonObject.Load( "asset::ted2/scripts.json" )
		If obj
			For Local obj2:=Eachin obj["scripts"].ToArray()
				Local name:=obj2.ToObject()["name"].ToString()
				Local script:=obj2.ToObject()["script"].ToString()
				Local action:=_scripts.AddAction( name )
				action.Triggered=Lambda()
					RunScript( script )
				End
			Next
		Endif
		
		_recentFiles=New Menu( "Recent Files..." )
		
		_closeProject=New Menu( "Close Project..." )
		
		_fileMenu=New Menu( "File" )
		_fileMenu.AddAction( _fileNew )
		_fileMenu.AddSubMenu( _newFiles )
		_fileMenu.AddAction( _fileOpen )
		_fileMenu.AddSubMenu( _recentFiles )
		_fileMenu.AddSeparator()
		_fileMenu.AddAction( _fileClose )
		_fileMenu.AddAction( _fileCloseOthers )
		_fileMenu.AddAction( _fileCloseAll )
		_fileMenu.AddSeparator()
		_fileMenu.AddAction( _fileSave )
		_fileMenu.AddAction( _fileSaveAs )
		_fileMenu.AddAction( _fileSaveAll )
		_fileMenu.AddSeparator()
		_fileMenu.AddAction( _fileNextFile )
		_fileMenu.AddAction( _filePrevFile )
		_fileMenu.AddSeparator()
		_fileMenu.AddAction( _fileOpenProject )
		_fileMenu.AddSubMenu( _closeProject )
		_fileMenu.AddSeparator()
		_fileMenu.AddAction( _fileQuit )
		
		_tabMenu=New Menu
		_tabMenu.AddAction( _fileClose )
		_tabMenu.AddAction( _fileCloseOthers )
		_tabMenu.AddSeparator()
		_tabMenu.AddAction( _fileSave )
		_tabMenu.AddAction( _fileSaveAs )
		_tabMenu.AddSeparator()
		_tabMenu.AddAction( _buildLockFile )
		
		_editMenu=New Menu( "Edit" )
		_editMenu.AddAction( _editUndo )
		_editMenu.AddAction( _editRedo )
		_editMenu.AddSeparator()
		_editMenu.AddAction( _editCut )
		_editMenu.AddAction( _editCopy )
		_editMenu.AddAction( _editPaste )
		_editMenu.AddSeparator()
		_editMenu.AddAction( _editSelectAll )
		_editMenu.AddSeparator()
		_editMenu.AddAction( _editFind )
		_editMenu.AddAction( _findNext )
		_editMenu.AddAction( _findPrevious )
		_editMenu.AddAction( _findReplace )
		_editMenu.AddAction( _findReplaceAll )
		
		_buildMenu=New Menu( "Build" )
		_buildMenu.AddAction( _buildDebug )
		_buildMenu.AddAction( _buildRelease )
		_buildMenu.AddSeparator()
		_buildMenu.AddAction( _buildNextError )
		_buildMenu.AddSeparator()
		_buildMenu.AddAction( _buildLockFile )
		_buildMenu.AddSeparator()
		_buildMenu.AddSubMenu( _scripts )
		_buildMenu.AddSeparator()
		_buildMenu.AddAction( _buildForceStop )
		
		_helpMenu=New Menu( "Help" )
		_helpMenu.AddAction( _helpOnlineHelp )
		_helpMenu.AddAction( _helpOfflineHelp )
		_helpMenu.AddAction( _helpAbout )
		
		_menuBar=New MenuBar
		_menuBar.AddMenu( _fileMenu )
		_menuBar.AddMenu( _editMenu )
		_menuBar.AddMenu( _buildMenu )
		_menuBar.AddMenu( _helpMenu )
	End
	
	Method InitViews()
	
		_findDialog=New FindDialog
		
		_projectView=New ProjectView		
		_debugView=New DebugView
		_helpView=New HelpView

		_browser=New TabView( TabViewFlags.DraggableTabs )'|TabViewFlags.ClosableTabs )
		_browser.AddTab( "Project",_projectView )
		_browser.AddTab( "Debug",_debugView )
'		_browser.AddTab( "Help",_helpView )
		_browser.CurrentView=_projectView
		
		_console=New Console
		_console.ReadOnly=True
		
		_docTabber=New TabView( TabViewFlags.DraggableTabs|TabViewFlags.ClosableTabs )
		
		_docTabber.CurrentChanged=Lambda()
			MakeCurrent( FindDocument( _docTabber.CurrentView ) )
		End
		
		_docTabber.RightClicked=Lambda()
			_tabMenu.Open()
		End
		
		_docTabber.CloseClicked=Lambda( index:Int )
			CloseDocument( FindDocument( _docTabber.TabView( index ) ) )
		End
		
		_docker=New DockingView
		_docker.ContentView=_docTabber
		_docker.AddView( _menuBar,"top",0 )
		_docker.AddView( _browser,"right",250 )
		_docker.AddView( _console,"bottom",200 )
		
	End
	
	Method New( title:String,rect:Recti,flags:WindowFlags )
		Super.New( title,rect,flags )
		
		MainWindow=Self
		
		ClearColor=App.Theme.GetColor( "windowClearColor" )
		
		SwapInterval=1
		
		InitPaths()
		InitActions()
		InitMenus()
		InitViews()

		LoadState()
		
		DeleteTmps()
		
		UpdateRecentFilesMenu()
		
		UpdateCloseProjectMenu()
		
		If Not _projects.Length
			Local dir:=CurrentDir()
			If _projectView.OpenProject( dir ) _projects.Push( dir )
		Endif

		App.Idle+=AppIdle
		
		ContentView=_docker
		
		Update( False )
		
		Print "Here!"
		
'		If Not _docTabber.Count OnHelpAbout()
		
	End
	
	Method OnWindowEvent( event:WindowEvent ) Override
	
		Select event.Type
		Case EventType.WindowClose
			_fileQuit.Trigger()
		Default
			Super.OnWindowEvent( event )
		End
		
	End
		
	Method ToRecti:Recti( value:JsonValue )
		Local json:=value.ToArray()
		Return New Recti( json[0].ToNumber(),json[1].ToNumber(),json[2].ToNumber(),json[3].ToNumber() )
	End
	
	Method UpdateCloseProjectMenu()
		_closeProject.Clear()
		For Local dir:=Eachin _projects
			_closeProject.AddAction( dir ).Triggered=Lambda()
				_projectView.CloseProject( dir )
				_projects.Remove( dir )
				UpdateCloseProjectMenu()
			End
		Next
	End
	
	Method UpdateRecentFilesMenu()
		_recentFiles.Clear()
		For Local path:=Eachin _recent
			_recentFiles.AddAction( path ).Triggered=Lambda()
				OpenDocument( path )
			End
		Next
	End
	
	Method LoadState()
	
		Local obj:=JsonObject.Load( "bin/ted2.state.json" )
		If Not obj Return
		
		If obj.Contains( "openDocuments" )
			For Local doc:=Eachin obj["openDocuments"].ToArray()
				Local path:=doc.ToString()
				If GetFileType( path )<>FileType.File Continue
				OpenDocument( doc.ToString() )
			Next
		Endif
		
		If obj.Contains( "recentFiles" )
			_recent.Clear()
			For Local file:=Eachin obj["recentFiles"].ToArray()
				Local path:=file.ToString()
				If GetFileType( path )<>FileType.File Continue
				_recent.Push( path )
			Next
		End
		
		If obj.Contains( "openProjects" )
			_projects.Clear()
			For Local proj:=Eachin obj["openProjects"].ToArray()
				Local dir:=proj.ToString()
				If Not _projectView.OpenProject( dir ) Continue
				_projects.Push( dir )
			Next
		Endif
		
		If obj.Contains( "windowRect" )
			Frame=ToRecti( obj["windowRect"] )
		Endif
		
		If obj.Contains( "consoleSize" )
			_docker.SetViewSize( _console,obj["consoleSize"].ToNumber() )
		Endif
		
		If obj.Contains( "browserSize" )
			_docker.SetViewSize( _browser,obj["browserSize"].ToNumber() )
		Endif
		
		If obj.Contains( "helpTreeSize" )
			_helpView.SetViewSize( _helpView.HelpTree,obj["helpTreeSize"].ToNumber() )
		Endif
		
		If obj.Contains( "lockedDocument" )
			Local doc:=OpenDocument( obj["lockedDocument"].ToString() )
			If doc LockDoc( doc )
		Endif
		
	End
	
	Method ToJson:JsonValue( rect:Recti )
		Return New JsonArray( New JsonValue[]( New JsonNumber( rect.min.x ),New JsonNumber( rect.min.y ),New JsonNumber( rect.max.x ),New JsonNumber( rect.max.y ) ) )
	End
	
	Method SaveState()
	
		Local obj:=New JsonObject
		
		Local docs:=New JsonArray
		For Local doc:=Eachin _openDocs
			docs.Add( New JsonString( doc.Path ) )
		Next
		obj["openDocuments"]=docs
		
		Local recent:=New JsonArray
		For Local path:=Eachin _recent
			recent.Add( New JsonString( path ) )
		End
		obj["recentFiles"]=recent
		
		Local projects:=New JsonArray
		For Local dir:=Eachin _projects
			projects.Add( New JsonString( dir ) )
		Next
		obj["openProjects"]=projects
		
		obj["windowRect"]=ToJson( Frame )
		
		obj["consoleSize"]=New JsonNumber( _docker.GetViewSize( _console ) )
		
		obj["browserSize"]=New JsonNumber( _docker.GetViewSize( _browser ) )
		
		obj["helpTreeSize"]=New JsonNumber( _helpView.GetViewSize( _helpView.HelpTree ) )
		
		If _lockedDoc obj["lockedDocument"]=New JsonString( _lockedDoc.Path )
		
		SaveString( obj.ToJson(),"bin/ted2.state.json" )
	
	End
	
	Method Notify( text:String,title:String="Ted2" )
		Local buttons:=New String[]( "Okay" )
		TextDialog.Run( title,text,buttons )
	End
	
	Method Confirm:Bool( text:String,title:String="Ted2" )
		Local buttons:=New String[]( "Okay","Cancel" )
		Return TextDialog.Run( title,text,buttons )=0
	End
	
	Method DeleteTmps()
		For Local i:=1 Until 10
			Local path:=RealPath( _tmp+"untitled"+i+".monkey2" )
			If GetFileType( path )=FileType.File 
				If Not FindDocument( path ) DeleteFile( path )
			Endif
		Next
	End
	
	Method AllocTmpPath:String()
		For Local i:=1 Until 10
			Local path:=_tmp+"untitled"+i+".monkey2"
			If GetFileType( path )=FileType.None Return path
		Next
		Return ""
	End
	
	Method IsTmpPath:Bool( path:String )
		Return path.StartsWith( _tmp )
	End
	
	Method BuildDoc:Ted2Document()
		If _lockedDoc Return _lockedDoc
		Return _currentDoc
	End
	
	Method LockDoc( doc:Ted2Document )

		If _lockedDoc And _lockedDoc=doc
			_lockedDoc=Null
			UpdateTabLabel( doc )
			Return
		Endif

		If doc And Not Cast<TextView>( doc.View ) doc=Null
	
		Local old:=_lockedDoc
		_lockedDoc=doc
		
		If _lockedDoc=old Return
		
		UpdateTabLabel( old )
		UpdateTabLabel( _lockedDoc )
	
	End
	
	Method UpdateKeyView()
	
		If Not _currentDoc Return
		
		_currentDoc.View.MakeKeyView()
	End
	
	Method MakeCurrent( doc:Ted2Document )
	
		If doc=_currentDoc Return
		
		If doc And _docTabber.CurrentView<>doc.View
			_docTabber.CurrentView=doc.View
		Endif
		
		_currentDoc=doc
		_currentTextView=Null
		If doc _currentTextView=Cast<TextView>( doc.View )
		
		
		App.Idle+=Lambda()
			If _currentDoc
				Title="Ted2 - "+_currentDoc.Path
			Else
				Title="Ted2"
			Endif
		End

		UpdateKeyView()
		
		Update( False )
	End
	
	Method FindDocument:Ted2Document( path:String )
		For Local doc:=Eachin _openDocs
			If doc.Path=path Return doc
		Next
		Return Null
	End	
	
	Method FindDocument:Ted2Document( view:View )
		For Local doc:=Eachin _openDocs
			If doc.View=view Return doc
		Next
		Return Null
	End	

	Method ReadError( path:String )
		Notify( "I/O Error reading file '"+path+"'" )
	End
	
	Method WriteError( path:String )
		Notify( "I/O Error writing file '"+path+"'" )
	End
	
	Method DocumentTabLabel:String( doc:Ted2Document )
		Local label:=StripDir( doc.Path )
		If ExtractExt( doc.Path ).ToLower()=".monkey2"  label=StripExt( label )
		If IsTmpPath( doc.Path ) label="<"+label+">"
		If doc=_lockedDoc label="+"+label
		If doc.Dirty label+="*"
		Return label
	End
	
	Method UpdateTabLabel( doc:Ted2Document )
		If doc _docTabber.SetTabLabel( doc.View,DocumentTabLabel( doc ) )
	End
	
	Method OpenDocument:Ted2Document( path:String,addRecent:Bool=False,makeCurrent:Bool=True )
	
		Local doc:Ted2Document

		If path

			path=RealPath( path )
			
			Local ext:=ExtractExt( path ).ToLower()
			
			Select ext
			Case ".monkey2"
			Case ".png",".jpg",".bmp"
			Case ".h",".hpp",".hxx",".c",".cpp",".cxx",".m",".mm",".s",".asm"
			Case ".html",".md",".json",".xml"
			Case ".sh",".bat"
			Case ".glsl"
			Case ".txt"
			Default
				Notify( "Unrecognized file type extension for file '"+path+"'" )
				Return Null
			End
		
			doc=FindDocument( path )
			If doc
				If makeCurrent MakeCurrent( doc )
				Return doc
			Endif
			
			Select ext
			Case ".monkey2"
				doc=New Mx2Document( path )
			Case ".png",".jpg"
				doc=New ImgDocument( path )
			Default
				doc=New TxtDocument( path )
			End
			
		Else
		
			path=AllocTmpPath()
			If Not path
				Notify( "Can't create temporary file" )
				Return Null
			Endif
			SaveString( "",path )
			
			doc=New Mx2Document( path )
		
		Endif
		
		If GetFileType( path )<>FileType.File Or Not doc.Load()
			ReadError( path )
			Return Null
		End
		
		doc.DirtyChanged=Lambda()
			UpdateTabLabel( doc )
		End
		
		_docTabber.AddTab( DocumentTabLabel( doc ),doc.View )
		_openDocs.Add( doc )
		
		If addRecent
			_recent.Remove( path )
			_recent.Insert( 0,path )
			If _recent.Length>20 _recent.Resize( 20 )
			UpdateRecentFilesMenu()
		Endif
		
		If makeCurrent MakeCurrent( doc )

		Return doc
	End
	
	Method RenameDocument( doc:Ted2Document,path:String )

		doc.Rename( path )

		UpdateTabLabel( doc )

	End
	
	Method SaveDocument:Bool( doc:Ted2Document )
	
		If IsTmpPath( doc.Path )

			Local path:=RequestFile( "Save As","",True )

			If Not path Return False
			
			RenameDocument( doc,path )
		Endif
		
		If doc.Save() Return True
		
		WriteError( doc.Path )
		
		Return False
	End
	
	Method CloseDocument( doc:Ted2Document )
	
		Local index:=_docTabber.TabIndex( doc.View )
		
		_docTabber.RemoveTab( doc.View )

		_openDocs.Remove( doc )
		
		doc.Close()
			
		If IsTmpPath( doc.Path ) DeleteFile( doc.Path )
		
		If doc=_lockedDoc _lockedDoc=Null
		
		If doc<>_currentDoc Return
		
		If Not _docTabber.Count 
			MakeCurrent( Null )
			Return
		Endif
		
		If index=_docTabber.Count index-=1
		
		MakeCurrent( FindDocument( _docTabber.TabView( index ) ) )
	End
	
	Method GotoError( err:Mx2Error )
	
		Local doc:=Cast<Mx2Document>( OpenDocument( err.path ) )
		If Not doc Return
		
		Local tv:=Cast<TextView>( doc.View )
		If Not tv Return
		
		Local sol:=tv.Document.StartOfLine( err.line )
		tv.SelectText( sol,sol )
		
		Return
	End
	
	Method Build( config:String )

		If _console.Running Return
		
		Local buildDoc:=Cast<Mx2Document>( BuildDoc() )
		If Not buildDoc Return
		
		For Local doc:=Eachin _openDocs
			Local mx2Doc:=Cast<Mx2Document>( doc )
			If mx2Doc mx2Doc.Errors.Clear()
		Next
		
		For Local doc:=Eachin _openDocs
			If doc.Save() Continue
			WriteError( doc.Path )
			Return
		Next

		_console.Clear()
		
		Local cmd:=_mx2cc+" makeapp -apptype=gui -build -config="+config+" ~q"+buildDoc.Path+"~q"
		
		If Not _console.Start( cmd )
			Notify( "Failed to start process: '"+cmd+"'" )
			Return
		Endif
		
		Local appFile:String
		
		Local dialog:=New TextDialog( "Ted2","Building "+buildDoc.Path+"..." )
		
		dialog.AddAction( "Cancel" ).Triggered=_console.Terminate
		
		dialog.Open()

		_errors.Clear()
		
		Repeat
		
			Local stdout:=_console.ReadStdout()
			If Not stdout Exit
			
			If stdout.StartsWith( "Application built:" )
				appFile=stdout.Slice( stdout.Find( ":" )+1 ).Trim()
			Else
				Local i:=stdout.Find( "] : Error : " )
				If i<>-1
					Local j:=stdout.Find( " [" )
					If j<>-1
						Local path:=stdout.Slice( 0,j )
						Local line:=Int( stdout.Slice( j+2,i ) )-1
						Local msg:=stdout.Slice( i+12 )
						
						Local err:=New Mx2Error( path,line,msg )
						Local doc:=Cast<Mx2Document>( OpenDocument( path,False,False ) )
						
						If doc
							doc.Errors.Add( err )
							If _errors.Empty GotoError( err )
							_errors.Add( err )
						Endif
						
					Endif
				Endif
			Endif
			
			_console.Write( stdout )
		
		Forever
		
		dialog.Close()
		
		If Not appFile Return
		
		cmd=appFile
		
		If Not _console.Start( cmd )
			Notify( "Failed to start process: '"+cmd+"'" )
			Return
		Endif
		
		_console.Clear()
		
		Local tab:=_browser.CurrentView
			
		If config="debug"
			_console.Write( "Debugging app:"+appFile+"~n" )
			_browser.CurrentView=_debugView
			_debugView.DebugBegin()
		Else
			_console.Write( "Running app:"+appFile+"~n" )
		Endif
		
		Repeat
			
			Local stdout:=_console.ReadStdout()
			If Not stdout Exit
			
			If config="debug" And stdout="{{!DEBUG!}}~n"
				_debugView.DebugStop()
				Continue
			End
			
			_console.Write( stdout )
		
		Forever
		
		If config="debug"
			_debugView.DebugEnd()
		Endif
		
		For Local doc:=Eachin _openDocs
			Local mx2Doc:=Cast<Mx2Document>( doc )
			If mx2Doc mx2Doc.DebugLine=-1
		Next
		
		_browser.CurrentView=tab
		
		_console.Write( "Done.~n" )

	End
	
	Method RunScript( script:String )
	
		If _console.Running Return
		
		For Local doc:=Eachin _openDocs
			If doc.Save() Continue
			WriteError( doc.Path )
			Return
		Next
		
		_console.Clear()
	
		Local cmd:=script

#If __HOSTOS__="windows"
        cmd=script+".bat"
#Else If __HOSTOS__="macos"
        cmd="/bin/bash -l "+script+".sh"
#Else
        cmd="/bin/bash -l -c "+script+".sh"
#Endif		
		
		Local cd:=CurrentDir()
		ChangeDir( "scripts" )
		Local r:=_console.Start( cmd )
		ChangeDir( cd )
		
		If Not r
			Notify( "Failed to start process: '"+cmd+"'" )
			Return
		Endif
		
		Repeat

			Local stdout:=_console.ReadStdout()
			If Not stdout Exit

			_console.Write( stdout )
		Forever
			
		_console.Write( "Done.~n" )
	End
	
	Method RequestDir:String( title:String,dir:String )

		Local future:=New Future<String>
		
		App.Idle+=Lambda()
			future.Set( mojo.requesters.RequestDir( title,dir ) )
		End
		
		Return future.Get()
	End

	Method RequestFile:String( title:String,filters:String,save:Bool,path:String="" )

		Local future:=New Future<String>
		
		App.Idle+=Lambda()
			future.Set( mojo.requesters.RequestFile( title,filters,save,path ) )
		End
		
		Return future.Get()
	End

	Method UpdateActions()
	
		Local keyView:=Cast<TextView>( App.KeyView )
	
		Local dirtyDocs:Bool
		For Local doc:=Eachin _openDocs
			If doc.Dirty dirtyDocs=True
		Next
		
		While Not _errors.Empty And _errors.First.removed
			_errors.RemoveFirst()
		Wend
	
		_fileClose.Enabled=_currentDoc<>Null
		_fileCloseOthers.Enabled=_openDocs.Length>1
		_fileCloseAll.Enabled=_openDocs.Length<>0
		_fileSave.Enabled=_currentDoc<>Null And _currentDoc.Dirty
		_fileSaveAs.Enabled=_currentDoc<>Null
		_fileSaveAll.Enabled=dirtyDocs
		_fileNextFile.Enabled=_docTabber.Count>1
		_filePrevFile.Enabled=_docTabber.Count>1
		
		_editUndo.Enabled=keyView And keyView.CanUndo
		_editRedo.Enabled=keyView And keyView.CanRedo
		_editCut.Enabled=keyView And keyView.CanCut
		_editCopy.Enabled=keyView And keyView.CanCopy
		_editPaste.Enabled=keyView And keyView.CanPaste
		_editSelectAll.Enabled=keyView<>Null
		
		_buildDebug.Enabled=BuildDoc()<>Null And Not _console.Running
		_buildRelease.Enabled=BuildDoc()<>Null And Not _console.Running
		_buildLockFile.Enabled=_currentDoc<>Null
		_buildForceStop.Enabled=_console.Running
		_buildNextError.Enabled=Not _errors.Empty
		
		_scripts.Enabled=Not _console.Running
	End
	
	Method AppIdle()
	
		UpdateActions()
		
'		App.RequestRender()
	
		App.Idle+=AppIdle
		
		GCCollect()	'thrash that GC!
	End
	
End
