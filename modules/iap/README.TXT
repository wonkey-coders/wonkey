
***** The IAP (In App Purchases) module *****

***** THE IAP API *****

Enum ProductType
	Consumable=1
	NonConsumable=2
End

Class Product

	Method New( identifier:String,type:ProductType )	'Creates a new product

	Property Identifier:String 		'Product identifier, used to identify product to store.
	Property Type:ProductType 		'Product type: ProductType.Consumable or ProductType.NonConsumable
	Property Valid:Bool				'True if product was found in store by OpenStore. 
    Property Title:String			'Product title, only valid once store is open and if Valid property is also true.
	Property Description:String		'Product description, only valid once store is open and if Valid property is also true.
	Property Price:String 			'Product price, only valid once store is open and if Valid property is also true.
End

Class IAPStore

	Field OpenStoreComplete:Void( result:Int,interrupted:Product[] )		'Called when OpenStore completes.
	
	'If result is 0, the store was opened successfully. Otherwise, an error occured. You can try and open the store again a bit later if you want.
	'If the store opened successfully, interrupted contains an array of interrupted product purchases. That is, purchases made by the user that the app was never informed of. This can happen if an app crashes halfway through a purchase.
	
	Field BuyProductComplete:Void( result:Int,product:Product )				'Called when BuyProduct completes.
	
	'If result is 0, the product was successfully purchased.
	'If result is 1, the purchase process was cancelled by the user.
	'If result is >1, a non fatal error occured and the product was not purchased.
	'If result is <0, a fatal error occured and the store will need to be reopened before it can be used again.
	
	Field GetOwnedProductsComplete:Void( result:Int,products:Product[] )	'Called when GetOwnedProducts completes.

	'If result is 0, owned is an array of all non-consumable products owned by the user.
	'If result is >0, a non fatal error occured.
	'If result is <0, a fatal error occured and the store will need to be reopened before it can be used again.

	Method New()
	
	Property Open:Bool()	'True if store is open, ie: OpenStore has successfully completed.
	Property Busy:Bool()	'True if store is busy, ie: OpenStore, BuyProduct or GetOwnedProducts is currently in progress.
	
	Method OpenStore( products:Product[] )	'Attempt to open the store.
	Method BuyProduct( product:Product )	'Attempt to buy a product.
	Method GetOwnedProducts()				'Attempt to get owned products.
	Method CloseStore()						'Closes store.
End


***** Android *****

* Building IAP apps.

To be able to build android apps that can use iap, You will need to modify your android studio project as per steps 1 and 2 here:

https://developer.android.com/google/play/billing/billing_integrate.html

For step 1, I've included an 'aidl' directory in the iap module's 'native' folder, just copy this into your android studio project's app/src/main folder.


* Testing IAP apps.

1) Create a new app via the GooglePlay console. This involves filling in a bunch of forms, uploading some artwork etc.

2) Upload a *signed* APK of your app via the GooglePlay console. You can sign an app using the Build->Generate Signed APK... menu in android studio. More information on app signing can be found here: https://developer.android.com/studio/publish/app-signing.html#sign-apk

3) Publish your app as an alpha. Note that this can take several hours, during which time your app's status will be 'pending publication'. You can still add in app purchases etc at this point, but you wont be able to test IAP from your device until the app is successfully published. Note that the app is still only alpha, so only you and your testers will be able to see it.

4) Add in app purchase products to the app via the GooglePlay console. Make sure they are enabled!

5) Add yourself as a 'tester' for your GooglePlay account. This is done via Settings->License Testing on the GooglePlay comsole. You may need a gmail account for this.

5) Upload the *signed* APK of your app to your device. This can be done via the ADB command line tool in the android SDK.

6) You can also get andriod studio to automatically sign your app each time it builds it -  see: https://developer.android.com/studio/publish/app-signing.html#sign-auto

6) Note that it is important that the key you use to sign the apk you upload to google play is the same as the one you use to sign the app for testing on your device - do not lose this key!


***** iOS *****

* Building IAP apps

You will need to add the StoreKit framework to your app project in xcode.


* Testing IAP apps *

Publishing on iOS is hard! All I can really offer is some tips:

1) If you're having problems with 'provisioning profiles', it may help to delete them from your keychain and to let XCode automatically restore them when necessary.

2) Along the same lines, delete any expired or invalid certificates and provisioning profiles from your developer account online.

3) It's not actually necessary to upload an app to itunes connect to test out iap. Just create the app, create the iap products, add the items to the app, and add a test user. See: https://developer.apple.com/library/content/documentation/LanguagesUtilities/Conceptual/iTunesConnectInAppPurchase_Guide/Chapters/TestingInAppPurchases.html

4) You do need to make sure all the itunes paperwork is up to date though. This held me up for several hours!

5) If you're having trouble uploading a screenshot for iap products (ie: 'invalid screenshot' errors), try leaving the page and creating the item from scratch again using the same screenshot. Worked for me several times!
