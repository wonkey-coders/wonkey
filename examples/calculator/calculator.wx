
Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

Using std..
Using mojo..
Using mojox..

'Simple gridview layout, since mojox doesn't have one yet!
'
Class GridView Extends View

	Method New( columns:Int=2 )
		_cols=columns

		Layout="fill"
	End

	Property Columns:Int()
	
		Return _cols
		
	Setter( cols:Int )
	
		_cols=cols
	End
	
	Method AddView( view:View )

		AddChildView( view )
		
		_views.Push( view )
	End
	
	Protected
	
	Method OnMeasure:Vec2i() Override
		
		Local rows:=(_views.Length-1)/_cols+1
		
		Local w:=0,h:=0
		
		For Local view:=Eachin _views
			w=Max( w,view.LayoutSize.x )
			h=Max( h,view.LayoutSize.y )
		Next
		
		Return New Vec2i( w * _cols,h * rows )
	End
	
	Method OnLayout() Override
	
		Local rows:=(_views.Length-1)/_cols+1

		Local i:=0,j:=0
		
		For Local view:=Eachin _views
		
			Local x0:=(i * Width)/_cols
			Local y0:=(j * Height)/rows
			Local x1:=((i+1) * Width)/_cols
			Local y1:=((j+1) * Height)/rows
			
			view.Frame=New Recti( x0,y0,x1,y1 )
			
			i=(i+1) Mod _cols
			If Not i j+=1
		Next
	
	End
	
	Private
	
	Field _cols:Int=2
	
	Field _views:=New Stack<View>
	
End

Class CalcButton Extends PushButton

	Method New( text:String )
		Super.New( text )
		
		TextGravity=New Vec2f( .5,.5 )
		
		MinSize=New Vec2i( 32,0 )
	End
End

Class CalcView Extends DockingView

	Field _result:Label
	
	Field _buttons:GridView
	
	Field _acc:Long
	
	Field _lastOp:Long( lhs:Long,rhs:Long )

	Field _nullOp:Long( lhs:Long,rhs:Long )

	Field _clr:Bool
	
	Method AddButton( text:String,clicked:Void() )
	
		Local button:=New CalcButton( text )

		button.Clicked=clicked
		
		_buttons.AddView( button )
	End
	
	Method AddButton( text:String,op:Long( x:Long,y:Long ) )
	
		Local button:=New CalcButton( text )
		
		button.Clicked=Lambda()
			_acc=_lastOp( _acc,Long( _result.Text ) )
			_result.Text=String( _acc )
			_clr=True
			_lastOp=op
		End
		
		_buttons.AddView( button )
	End
	
	Method New()
	
		_result=New Label( "0" )
		_result.Style=App.Theme.GetStyle( "PushButton" )
		_result.TextGravity=New Vec2f( 1,.5 )
		AddView( _result,"top" )
		
		_buttons=New GridView( 3 )
		AddView( _buttons,"top" )
		
		For Local i:=0 Until 10
		
			AddButton( String( i ),Lambda()
			
				If _clr
				
					_clr=False
					_result.Text=""
					
				Else if _result.Text="0" 
				
					_result.Text=""
					
				Endif
	
				_result.Text+=String( i )
			
			End )
			
		Next
		
		AddButton( "+",Lambda:Long( lhs:Long,rhs:Long )
			Return lhs + rhs
		End )
		
		AddButton( "-",Lambda:Long( lhs:Long,rhs:Long )
			Return lhs - rhs
		End )
		
		AddButton( "*",Lambda:Long( lhs:Long,rhs:Long )
			Return lhs * rhs
		End )
		
		AddButton( "/",Lambda:Long( lhs:Long,rhs:Long )
			Return lhs - rhs
		End )
		
		AddButton( "=",Lambda()
		
			_acc=_lastOp( _acc,Long( _result.Text ) )
			_result.Text=String( _acc )
			_lastOp=_nullOp
			_clr=True
			
		End )
		
		AddButton( "+/-",Lambda()
		
			If Not Long( _result.Text ) Return
		
			If _result.Text.StartsWith( "-" )
				_result.Text=_result.Text.Slice( 1 )
			Else
				_result.Text="-"+_result.Text
			Endif
			
		End )
		
		AddButton( "CE",Lambda()
		
			_result.Text="0"
			
		End )
		
		AddButton( "C",Lambda()
		
			_result.Text="0"
			_lastOp=_nullOp
			_acc=0

		End )

		_nullOp=Lambda:Long( lhs:Long,rhs:Long )
			Return rhs
		End
		
		_result.Text="0"
		_lastOp=_nullOp
		_acc=0
		
	End
End

Class MyWindow Extends Window

	Field _calc:CalcView
	
	Field _dialog:Dialog

	Method New()
	
		_calc=New CalcView
		
		_dialog=New Dialog( "Calculator" )
		
		_dialog.ContentView=_calc
		
		App.Idle+=_dialog.Open
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
