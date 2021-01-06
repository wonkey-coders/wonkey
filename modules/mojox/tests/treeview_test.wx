
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window

	Method New()
		Super.New( "TreeView Demo",640,480,WindowFlags.Resizable )

		Local treeView:=New TreeView
		
		treeView.NodeClicked+=Lambda( node:TreeView.Node )

			Alert( "Node clicked: node.Text=~q"+node.Text+"~q" )
		End
		
		treeView.NodeExpanded+=Lambda( node:TreeView.Node )
		
'			Alert( "Node expanded: node.Text=~q"+node.Text+"~q" )
		End
		
		treeView.NodeCollapsed+=Lambda( node:TreeView.Node )
		
'			Alert( "Node collapsed: node.Text=~q"+node.Text+"~q" )
		End
		
		treeView.RootNode.Text=CurrentDir()
		
		CreateTree( CurrentDir(),treeView.RootNode )
		
		ContentView=treeView
	End
	
	Method CreateTree( path:String,parent:TreeView.Node )
	
		For Local f:=Eachin LoadDir( path )
		
			Local p:=path+"/"+f
			
			Local node:=New TreeView.Node( f,parent )
			
			If GetFileType( p )=FileType.Directory CreateTree( p,node )
		Next
	End

End


Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
