
#rem

IMPORTANT!

This wont work 'as is'! You'll need to set up a bunch of stuff on GooglePlay/iTunes Connect developer portal such as app/products etc.

#end

Namespace myapp

#Import "<iap>"
#Import "<std>"
#Import "<mojo>"
#Import "<mojox>"

Using iap..
Using std..
Using mojo..
Using mojox..

Class MyWindow Extends Window
	
	Field _purchases:JsonObject
	
	Field _products:Product[]
	
	Field _info:String

	Field _listView:ListView

	Field _openStoreItem:ListView.Item
	
	Field _restorePurchasesItem:ListView.Item
	
	Field _iap:IAPStore
	
	Method New( title:String="Simple mojo app",width:Int=640,height:Int=480,flags:WindowFlags=Null )

		Super.New( title,width,height,flags )
		
		Layout="stretch"
		
		'Create our IAP products.
		'
		_products=New Product[](
			New Product( "speed_boost",ProductType.Consumable ),
			New Product( "bullet_boost",ProductType.Consumable ),
			New Product( "ship_upgrade",ProductType.NonConsumable ) )
		
		'Load purchases we've already bought.
		'
		LoadPurchases()

		'Create a ListView to fill in with products later...
		'	
		_listView=New ListView
		_listView.Layout="float"
		_listView.Gravity=New Vec2f( .5,.5 )
		
		_listView.ItemClicked=Lambda( item:ListView.Item )
		
			If Not _iap Or _iap.Busy Return
			
			If item=_restorePurchasesItem

				_iap.GetOwnedProducts()

				Return
			Endif
			
			If item=_openStoreItem
				
				OpenStore()
				
				Return
			Endif

			Local index:= _listView.IndexOfItem( item )
			
			Local product:=_products[ index ]
			
			'it's actually harmless to let someone purchase a non consumable again, they'll
			'only be charged for it once, but still...
			If product.Type=ProductType.NonConsumable And _purchases.GetNumber( product.Identifier )>0 Return
		
			_iap.BuyProduct( product )

			_info="Buying product "+product.Identifier
		End
		
		ContentView=_listView
		
		OpenStore()
	End
	
	Method MakePurchase( product:Product )
		
		Select product.Type
		Case ProductType.Consumable
			_purchases.SetNumber( product.Identifier,_purchases.GetNumber( product.Identifier )+1 )
		Case ProductType.NonConsumable
			_purchases.SetNumber( product.Identifier,1 )
		End
	End
	
	Method OpenStore()

		_iap?.CloseStore()
		_iap=Null
		
		'Create IAPStore and various handlers.
		'
		_iap=New IAPStore

		GCCollect()
		GCCollect()

		'This is called when OpenStore completes.
		'
		_iap.OpenStoreComplete=Lambda( result:Int,interrupted:Product[],owned:Product[] )
		
			Print "OpenStoreComplete result="+result
		
			Select result
			Case 0

				'Handle interrupted purchases - these are purchases that the user was charged for but your app never
				'got notified about coz it or the OS crashed or something...
				'
				'This array is always empty on ios which apparently handles this edge case better?
				'
				For Local product:=Eachin interrupted
					MakePurchase( product )
				Next
				
				'Handle owned products - these are non-consumables that have been bought by the user. Android tracks these for
				'you (as long as you're logged in anyway) so you don't strictly need to save them, but you do on ios so for the sake of 
				'uniformity we will on android too.
				'
				'On Android, you never really need to use GetOwnedProducts() because you are given this array of owned products when the store
				'opens. So in a sense, android automatically 'restores purchases' whenever you open the store.
				'
				'This array is always empty on ios. To restore non-consumables on ios you must call GetOwnedProducts in response to the push
				'of a 'Restore Purchases' button or similar. Apps with IAP but no 'restore purchases' mechanism will be rejected from the 
				'app store. GetOwnedProducts may cause dialogs to appear etc as the user may need to log into itunes, which is why it's not
				'just done by default when the store opens the way it is on android.
				'
				For Local product:=Eachin owned
					MakePurchase( product )
				Next
				
				SavePurchases()
				
				_info="OpenStore successful"
			Default
				_info="OpenStore error:"+result
			End

			UpdateListView()
		End
		
		'This is called when BuyProduct completes.
		'
		_iap.BuyProductComplete=Lambda( result:Int,product:Product )
		
			Select result
			Case 0	'success!
				MakePurchase( product )
				SavePurchases()
				UpdateListView()
				_info="BuyProduct successful:"+product.Identifier
			Case 1	'cancelled!
				_info="BuyProduct cancelled:"+product.Identifier
			Default
				_info="BuyProduct error:"+result
			End
				
		End
		
		'This is called when GetOwnProducts completes.
		'
		_iap.GetOwnedProductsComplete=Lambda( result:Int,owned:Product[] )

			Select result
			Case 0	'success!
				
				'Make sure we really own all owned products.
				'
				For Local product:=Eachin owned
					MakePurchase( product )
				Next
				
				SavePurchases()
				UpdateListView()
				_info="GetOwnProducts successful"
			Default
				_info="GetOwnedProducts error:"+result
			End
			
		End

		_iap.OpenStore( _products )
		
		_info="Opening store..."
		
	End
	
	Method LoadPurchases()
		
		'load purchases file from internal app storage.
		'
		_purchases=JsonObject.Load( "internal::purchases.json" )
		
		'if not found, create new purchases file.
		'
		If Not _purchases
			
			_purchases=New JsonObject
			
			For Local product:=Eachin _products
				_purchases.SetNumber( product.Identifier,0 )
			Next
			
			SavePurchases()
			
		Endif
		
	End
	
	Method SavePurchases()
		
		_purchases.Save( "internal::purchases.json" )
	
	end

	'populate listview with products
	'
	Method UpdateListView()

		_listView.RemoveAllItems()
		
		_restorePurchasesItem=Null
		
		_openStoreItem=Null
		
		If _iap?.Open
		
			For Local product:=Eachin _products
				
				'products become valid when store is opened.
				'
				'If Not product.Valid Continue
				
				_listView.AddItem( product.Title+" - "+product.Description+" for the low price of "+product.Price+" ("+_purchases.GetNumber( product.Identifier )+")" )
			Next
			
			_restorePurchasesItem=_listView.AddItem( "[RESTORE PURCHASES]" )
			
		Endif
		
		_openStoreItem=_listView.AddItem( "[REOPEN STORE]" )
	End
	
	Method OnRender( canvas:Canvas ) Override
		
		RequestRender()
		
		canvas.DrawText( "Hello World!",Width/2,Height/2,.5,.5 )
		
		canvas.DrawText( "IAP info:"+_info,0,0 )
	End
	
	Method OnMeasure:Vec2i() Override
		
		Return New Vec2i( 640,360 )
	End
	
End

Function Main()

	New AppInstance
	
	New MyWindow
	
	App.Run()
End
