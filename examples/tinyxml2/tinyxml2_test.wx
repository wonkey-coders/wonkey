
#Import "dream.xml"

#Import "<std>"
#Import "<mojo>"
#import "<mojox>"
#Import "<tinyxml2>"
 
Using std..
Using mojo..
Using mojox..
Using tinyxml2..
 
Function Main()
 
	New AppInstance
	
	New MyWindow()
	
	App.Run()
End
 
Class MyWindow Extends Window
 
	Field _tree:TreeView
 
	Method New()
	
		Super.New("XML TreeView Test", 640, 480, WindowFlags.Resizable)
 
		Local xml := LoadString( "asset::dream.xml" )
		
		Local doc := New XMLDocument()
		
		If doc.Parse(xml) <> XMLError.XML_SUCCESS
			Print "Failed to parse embedded XML!"
			Return
		Endif
				
		Local _tree := New TreeView
 
		_tree.RootNode.Text = "XML document"
 
		AddXMLNodeToTree(doc, _tree.RootNode)
		
		ContentView = _tree
		
		doc.Destroy()
	End
 
	Method AddXMLNodeToTree(xmlNode:XMLNode, parent:TreeView.Node)
	
		Local str := ""
	
		Local xmlElement := xmlNode.ToElement()
		
		If xmlElement
		
			str += "<" + xmlNode.Value()
			
			Local attrib := xmlElement.FirstAttribute()
			While attrib 
				str += " " + attrib.Name() + "=~q" + attrib.Value() + "~q "
				attrib=attrib.NextAttribute()
			wend
			
			str += ">"
		Else
			str += xmlNode.Value()
		Endif
 
		Local treeNode:TreeView.Node
	
		If str
			treeNode = New TreeView.Node(str, parent)
		Endif
		
		Local xmlChild := xmlNode.FirstChild()
	
		While xmlChild
		
			If Not xmlChild.NoChildren()
				If treeNode Then parent = treeNode
			Endif
		
			AddXMLNodeToTree(xmlChild, parent)
			
			xmlChild = xmlChild.NextSibling()
	
		Wend
	
	End
 
End
