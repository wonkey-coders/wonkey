
Namespace mojox

Class GridView Extends View
	
	Method New( width:Int,height:Int )
		_gridw=width
		_gridh=height
		Style=GetStyle( "GridView" )
	End
	
	Property GridWidth:Int()
		
		Return _gridw
		
	Setter( gridw:Int )
		If gridw=_gridw Return
		
		_gridw=gridw
		
		RequestRender()
	End
	
	Property GridHeight:Int()
		
		Return _gridh
		
	Setter( gridh:Int )
		If gridh=_gridh Return
		
		_gridh=gridh

		RequestRender()
	End
	
	Method Clear()
		
		For Local cell:=Eachin _cells
			RemoveChildView( cell.view )
		Next
		_cells.Clear()
		RequestRender()
	End
	
	Method AddView( view:View,x:Int,y:Int,width:Int=1,height:Int=1 )
		
		_cells.Add( New Cell( view,x,y,width,height ) )
		AddChildView( view )
		RequestRender()
	End
	
	Method ReplaceView( view:View,with:View )
		
		For Local cell:=Eachin _cells
			If cell.view<>view Continue
			RemoveChildView( view )
			AddChildView( with )
			cell.view=with
			RequestRender()
			Return
		Next
		
	End
	
	Method RemoveView( view:View )
		
		For Local cell:=Eachin _cells
			If cell.view<>view Continue
			RemoveChildView( view )
			_cells.Remove( cell )
			RequestRender()
			Return
		Next
		
	End
	
	Protected
	
	Method OnMeasure:Vec2i() Override

		Local maxw:=0,maxh:=0
		
		For Local cell:=Eachin _cells
			
			Local size:=cell.view.LayoutSize
			
			maxw=Max( maxw,size.x/cell.w )
			maxh=Max( maxh,size.y/cell.h )
		Next
		
		Return New Vec2i( maxw * _gridw,maxh * _gridh )
	End
	
	Method OnLayout() Override
		
		For Local cell:=Eachin _cells
			
			Local x0:=cell.x * Width / _gridw
			Local x1:=(cell.x+cell.w) * Width / _gridw

			Local y0:=cell.y * Height / _gridh
			Local y1:=(cell.y+cell.h) * Height / _gridh
			
			cell.view.Frame=New Recti( x0,y0,x1,y1 )
		Next
			
	End
	
	Private
	
	Struct Cell
		Field view:View
		Field x:Int
		Field y:Int
		Field w:Int
		Field h:Int
		
		Method New( view:View,x:Int,y:Int,w:Int,h:Int )
			Self.view=view
			Self.x=x
			Self.y=y
			Self.w=w
			Self.h=h
		End
	End
	
	Field _gridw:Int
	Field _gridh:Int
	Field _cells:=New Stack<Cell>
End

