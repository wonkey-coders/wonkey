
#Import "<std>"
#Import "<mojo>"

Using std..
Using mojo..
 
Function Main()
	Local testStack := New TestStack
	
	For Local n := 1 To 20
		Local newItem := New TestItem
		testStack.Add( newItem, Rnd( 0, 100 ) )
	Next
		
	For Local n := Eachin testStack.items
		Print( n.depth )
	Next
End
 
 
Class TestStack
	Field items := New Stack< TestItem >
	Method Add( item:TestItem, depth:Float ) 
		item.depth = depth
		items.Push( item )
	End
End
 
 
Struct TestItem				'Change this to a Class and it will compile!
	Field depth:Int
	Field img: Image		'Comment out this line and it will compile!
	Field color: Color
End
