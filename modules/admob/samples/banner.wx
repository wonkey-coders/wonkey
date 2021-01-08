
Namespace myapp

#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"
#Import "<admob>"

Using std..
Using mojo..
Using mojox..
Using admob..

'Replace this with your AdMobID for banner ads, eg: "ca-app-pub-XXXXXXXXXXXXXXXX/YYYYYYYYYY"
'
Const AdUnitId:=""

Class MyWindow Extends Window
	
	Field _adView:AdView

	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )

		'Scale up GUI a bit on mobile!
		'
		App.Theme.Scale=New Vec2f( 3,3 )
		
		'Create AdView instance
		'		
		_adView=New AdView( "banner","bottom",AdUnitId )
		
		_adView.Loading+=Lambda()
		
			Print "AdView Loading"
		End
		
		_adView.Ready+=Lambda()
		
			Print "AdView Ready"
		End

		'Add some buttons to hide/show the ad.
		'
		Local tools:=New ToolBar
					
		tools.AddAction( "Show Ad" ).Triggered=Lambda()
			
			_adView.Visible=True
		End
					
		tools.AddAction( "Hide Ad" ).Triggered=Lambda()
			
			_adView.Visible=False
		End
		
		tools.AddAction( "Reload Ad" ).Triggered=Lambda()
		
			If _adView.State=AdState.Error
				
				_adView.Reload()	'Tries to load another ad. If State<>AdState.Error, this has no effect.
			
			Endif
		
		End

					
		ContentView=tools

	End
	
	Method OnRender( canvas:Canvas ) Override
	
		RequestRender()
		
		Local state:="?????"
		
		Select _adView.State
		Case AdState.Initial	'ad is starting up
			state="Initial"
		Case AdState.Loading	'ad is loading
			state="Loading"
		Case AdState.Ready		'ad is ready to be made visible
			state="Ready"
		Case AdState.Error		'ad error.
			state="Error"
		End

		canvas.DrawText( state+"...",Width/2,Height/2,.5,.5 )
		
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
