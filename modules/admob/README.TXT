
***** Installation *****

This README.TXT file should be located inside an 'admob' folder. You will need to copy this folder to your wonkey 'modules' folder, after which you will need to 'update modules' for the particular target you are planning to use admob with (ios or android). To update modules, select 'Update Modules' from the 'Build' menu of Wide, the Wonkey IDE.

You can then try out one of the samples in the admob/bananas directory: 'banner', 'interstitial' or 'rewardedvideo'. See notes below for help with building admob apps for ios or android.


***** Class AdView API *****


* Method New( size:String,layout:String="",adUnitId:String="",visible:Bool=True )

Creates an AdView and starts it loading.

'size' should be one of the following: "banner", "large-banner", "medium-rectangle", "full-banner" or "leaderboard" for a banner ad, "interstitial" for an interstitial ad or "rewardedvideo" for a rewarded video ad.

'layout' is ignored for interstitial and rewarded video ads, which are always 'full screen'. For banner ads, it should be one of: "top", "bottom", "left", "right" "top-left", "top-right", "bottom-left", "bottom-right" or "center".

'adUnitId' is the admob ad unit id of the ad you want to display. Ad unit ids are created from you admob account. Set ad unit id to an empty string to create a 'test' ad.

For banner ads, if 'visible' is true then the ad is initially visible and will automatically appear once it has successfully loaded. Otherwise the ad will be initially hidden.


* Property Visible:Bool	(read/write)

Set to true to show an ad. In the case of interstitial ads, setting `Visible` to true will also show the ad. In the case of rewarded video ads, setting `Visible` to true will also play the video.

	
* Property State:AdState (read only)
	
Returns the current ad state, one of: AdState.Loading, AdState.Ready or AdState.Error.


* Method Reload()

Reloads the AdView, should only be used in the case of an ad load error.


* Field Loading:Void()

Invoked when AdView state changes to AdState.Loading.


* Field Ready:Void()

Invoked when the AdView state changes to AdState.Ready.


* Field Error:Void( error:Int )

Invoked when an AdView error occurs, usually while loading. In this case, you can wait a while and call Reload() if you want.


* Field Rewarded:Void( type:String,amount:Int )

Invoke when the user has sat through a rewarded video and therefore claimed their reward. The 'type' and 'amount' parameters will default to "coins" and 10 if you are using test ads. Otherwise, they will reflect the values associated with the ad unit you are using as entered on the admob web page.


***** Using the admob module with android studio *****

To prepare an android studio project for use with admob, add the following line to your project's 'build.gradle (Module:app)' file inside the 'dependancies' block...

    implement 'com.google.android.gms:play-services-ads:17.1.1'
        
You may need to change the version number depending on when you're reading this.

If you are using a version >= 17.0.0 you will also need to add something like this to your app manifest...

        <meta-data android:name="com.google.android.gms.ads.APPLICATION_ID"
            android:value="ca-app-pub-3940256099942544~3347511713"/>

...inside the <application> block. The publisher id shown here allows you to test admob offline, you'll have to change it with your actual admob publisher id when you go 'live'.

After this, you'll need to do a 'gradle sync'.

If you get stuck, try looking at the 'import sdk' section here:

https://developers.google.com/admob/android/quick-start


***** Using the admob module with ios/xcode *****

To prepare an xcode project for use with admob you will need to add the google mobile ads framework to the project. The framework can be downloaded here: https://developers.google.com/admob/ios/download

You will also need to add the following system frameworks to the project:

AdSupport.framework
CFNetwork.framework
CoreMedia.framework
CoreTelephony.framework
CoreVideo.framework
GLKit.framework
MediaPlayer.framework
MessageUI.framework
MobileCoreServices.framework
Security.framework
StoreKit.framework
SystemConfiguration.framework

If you get stuck, try looking at the 'import sdk' section here:

https://developers.google.com/admob/ios/quick-start

