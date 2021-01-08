
#import "adview_ios.h"
#import <AdSupport/ASIdentifierManager.h>
#import <CommonCrypto/CommonDigest.h>

#import <SDL.h>

//Ugly stuff, but need these 'coz admob interstitial/rewardedvideo don't suspend/resume app?
//
static void suspendApp(){

	//send a 'fake' SDL_APP_WILLENTERBACKGROUND to app.
	
	SDL_Event event={0};
	event.type=SDL_APP_WILLENTERBACKGROUND;
	
	if( SDL_PeepEvents( (SDL_Event*)&event,1,SDL_ADDEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT )!=1 ){
		printf( "SDL_PeepEvents error: %s\n",SDL_GetError() );fflush( stdout );
	}
}

static void resumeApp(){

	//send a 'fake' SDL_APP_DIDENTERFOREGROUND to app.
	
	SDL_Event event={0};
	event.type=SDL_APP_DIDENTERFOREGROUND;
	
	if( SDL_PeepEvents( (SDL_Event*)&event,1,SDL_ADDEVENT,SDL_FIRSTEVENT,SDL_LASTEVENT )!=1 ){
		printf( "SDL_PeepEvents error: %s\n",SDL_GetError() );fflush( stdout );
	}
}

@implementation WXAdmobDelegate{

	WXAdView *_view;
}

-(id)initWithView:(WXAdView*)view{

	self=[super init];
 
    if( self ){
    	_view=view;
    }
 
    return self;
}

-(void)adViewDidReceiveAd:(GADBannerView*)bannerView{

	printf( "Wonkey AdViewDelegate: adViewDidReceiveAd\n" );fflush( stdout );
	
	_view->setState( 2 );	//Ready
}

-(void)adView:(GADBannerView*)bannerView didFailToReceiveAdWithError:(GADRequestError*)error{

	NSString *err=error.localizedDescription;
	
	printf( "Wonkey AdViewDelegate: bannerView didFailToReceiveAdWithError '%s' code=%ld\n",[err UTF8String],(long)error.code );fflush( stdout );
	
	_view->_error=error.code==9 ? 1 : -1;
	
	_view->setState( 3 );	//Error
}

-(void)interstitialDidReceiveAd:(GADInterstitial*)interstitial{

	printf( "Wonkey AdViewDelegate: interstitialDidReceivedAd\n" );fflush( stdout );

	_view->setState( 2 );	//Ready
}

-(void)interstitial:(GADInterstitial*)ad didFailToReceiveAdWithError:(GADRequestError*)error{

	NSString *err=error.localizedDescription;
	
	printf( "Wonkey AdViewDelegate: interstitial didFailToReceiveAdWithError '%s' code=%ld\n",[err UTF8String],(long)error.code );fflush( stdout );
	
	_view->_error=error.code==9 ? 1 : -1;

	_view->setState( 3 );	//Error
}

-(void)interstitialWillPresentScreen:(GADInterstitial*)interstitial{

	printf( "Wonkey AdViewDelegate: interstitialWillPresentScreen\n" );fflush( stdout );
	
	suspendApp();
}

-(void)interstitialDidDismissScreen:(GADInterstitial*)interstitial{

	printf( "Wonkey AdViewDelegate: interstitialDidDismissScreen\n" );fflush( stdout );
	
	_view->setState( 0 );	//Initial
	
	resumeApp();
}

-(void)rewardBasedVideoAd:(GADRewardBasedVideoAd*)rewardBasedVideoAd didRewardUserWithReward:(GADAdReward*)reward{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAd didRewardUserWithReward, type='%s', amount=%l\n",[reward.type UTF8String],[reward.amount doubleValue] );fflush( stdout );
	
	_view->_rewardType=wxString( reward.type );	//careful! threading...
	
	_view->_rewardAmount=(int)[reward.amount doubleValue];
}

-(void)rewardBasedVideoAdDidReceiveAd:(GADRewardBasedVideoAd*)rewardBasedVideoAd{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAdDidReceiveAd\n" );fflush( stdout );

	_view->setState( 2 );	//Ready
}

-(void)rewardBasedVideoAd:(GADRewardBasedVideoAd*)rewardBasedVideoAd didFailToLoadWithError:(NSError*)error{

	NSString *err=error.localizedDescription;
	
	printf( "Wonkey AdViewDelegate: rewardBasedVideoAd didFailToLoadWithError '%s' code=%ld\n",[err UTF8String],(long)error.code );fflush( stdout );
	
	_view->_error=error.code==9 ? 1 : -1;

	_view->setState( 3 );	//Error
}

-(void)rewardBasedVideoAdDidOpen:(GADRewardBasedVideoAd*)rewardBasedVideoAd{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAdDidOpen\n" );fflush( stdout );

//	_view->setState( 4 );	//Playing
	
	suspendApp();
}

-(void)rewardBasedVideoAdDidClose:(GADRewardBasedVideoAd*)rewardBasedVideoAd{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAdDidClose\n" );fflush( stdout );
	
	_view->setState( 0 );	//Initial

	resumeApp();
}

-(void)rewardBasedVideoAdDidStartPlaying:(GADRewardBasedVideoAd*)rewardBasedVideoAd{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAdDidStartPlaying\n" );fflush( stdout );
}

-(void)rewardBasedVideoAdWillLeaveApplication:(GADRewardBasedVideoAd*)rewardBasedVideoAd{

	printf( "Wonkey AdViewDelegate: rewardBasedVideoAdWillLeaveApplication\n" );fflush( stdout );
}

@end

static NSString *admobDeviceID(){

    NSUUID* adid = [[ASIdentifierManager sharedManager] advertisingIdentifier];
    const char *cStr = [adid.UUIDString UTF8String];
    unsigned char digest[16];
    CC_MD5( cStr, strlen(cStr), digest );

    NSMutableString *output = [NSMutableString stringWithCapacity:CC_MD5_DIGEST_LENGTH * 2];

    for(int i = 0; i < CC_MD5_DIGEST_LENGTH; i++)
        [output appendFormat:@"%02x", digest[i]];

    return output;
}

WXAdView::WXAdView( wxString size,wxString layout,wxString adUnitId,wxBool visible ):_size( size ),_layout( layout ),_adUnitId( adUnitId ),_visible( visible ){
}

void WXAdView::start( int callback ){

	_callback=callback;

	_adDelegate=[[WXAdmobDelegate alloc] initWithView:this];
		
	_adRequest=[GADRequest request];
	
	if( _size=="rewardedvideo" ){
		
        if( _adUnitId=="" ) _adUnitId="ca-app-pub-3940256099942544/1712485313";
        
		createRewardBasedVideoAd();
	
	}else if( _size=="interstitial" ){
		
        if( _adUnitId=="" ) _adUnitId="ca-app-pub-3940256099942544/1033173712";
        
		createInterstitialAd();
	
	}else{
		
        if( _adUnitId=="" ) _adUnitId="ca-app-pub-3940256099942544/6300978111";

		createBannerAd();
	}
}

void WXAdView::setState( int state ){

	if( state==_state ) return;
	
	_state=state;
	
	wxAsync::invokeAsyncCallback( _callback );
}

void WXAdView::createRewardBasedVideoAd(){

	_rewardBasedVideoAd=[GADRewardBasedVideoAd sharedInstance];
	
	_rewardBasedVideoAd.delegate=_adDelegate;
	
	[_rewardBasedVideoAd loadRequest:[GADRequest request] withAdUnitID:[NSString stringWithUTF8String:_adUnitId.c_str()]];
	
	setState( 1 );
}

void WXAdView::createInterstitialAd(){
	
	_interstitialAd=[[GADInterstitial alloc] initWithAdUnitID:[NSString stringWithUTF8String:_adUnitId.c_str()]];
		
	_interstitialAd.delegate=_adDelegate;
		
	[_interstitialAd loadRequest:[GADRequest request]];
		
	setState( 1 );
}

void WXAdView::createBannerAd(){
	
	UIWindow *keyWindow=[UIApplication sharedApplication].keyWindow;
	if( !keyWindow ) return;
		
	UIViewController *rootViewController=keyWindow.rootViewController;
	if( !rootViewController ) return;
	
	GADAdSize adSize=kGADAdSizeBanner;
    if( _size=="banner" ){
        adSize=kGADAdSizeBanner;
    }else if( _size=="large-banner" ){
        adSize=kGADAdSizeLargeBanner;
    }else if( _size=="medium-rectangle" ){
        adSize=kGADAdSizeMediumRectangle;
    }else if( _size=="full-banner" ){
        adSize=kGADAdSizeFullBanner;
    }else if( _size=="leaderboard" ){
        adSize=kGADAdSizeLeaderboard;
    }
		
	_adView=[[GADBannerView alloc] initWithAdSize:adSize];
	_adView.delegate=_adDelegate;
	_adView.adUnitID=[NSString stringWithUTF8String:_adUnitId.c_str()];
	_adView.rootViewController=rootViewController;
	_adView.hidden=_visible ? NO : YES;
		
	CGRect b1=keyWindow.bounds;
	CGRect b2=_adView.frame;
	
	if( _layout=="top-left" ){		
		_adView.autoresizingMask=UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleBottomMargin;
	}else if( _layout=="top" ){
		b2.origin.x=(b1.size.width-b2.size.width)/2;
		_adView.autoresizingMask=UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleBottomMargin;
	}else if( _layout=="top-right" ){
		b2.origin.x=(b1.size.width-b2.size.width);
		_adView.autoresizingMask=UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleBottomMargin;
	}else if( _layout=="bottom-left" ){
		b2.origin.y=(b1.size.height-b2.size.height);
		_adView.autoresizingMask=UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleTopMargin;
	}else if( _layout=="bottom" ){
		b2.origin.x=(b1.size.width-b2.size.width)/2;
		b2.origin.y=(b1.size.height-b2.size.height);
		_adView.autoresizingMask=UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleTopMargin;
	}else if( _layout=="bottom-right" ){
		b2.origin.x=(b1.size.width-b2.size.width);
		b2.origin.y=(b1.size.height-b2.size.height);
		_adView.autoresizingMask=UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleTopMargin;
	}else{
		b2.origin.x=(b1.size.width-b2.size.width)/2;
		b2.origin.y=(b1.size.height-b2.size.height)/2;
		_adView.autoresizingMask=UIViewAutoresizingFlexibleLeftMargin|UIViewAutoresizingFlexibleRightMargin|UIViewAutoresizingFlexibleTopMargin|UIViewAutoresizingFlexibleBottomMargin;
	}		
	
	_adView.frame=b2;
		
	[_adView.rootViewController.view addSubview:_adView];
	
	[_adView loadRequest:_adRequest];
		
	setState( 1 );
}
	
void WXAdView::setVisible( bool visible ){

	if( _adView ){
		_adView.hidden=!visible;
		return;
	}
	
	if( !visible ) return;

	if( _state!=2 ){
		printf( "Wonkey AdView setVisible error, expecting _state==2, but _state==%i\n",_state );fflush( stdout );
		return;
	}

	if( _rewardBasedVideoAd ){
		
		if( _rewardBasedVideoAd.isReady ){
			
			UIWindow *keyWindow=[UIApplication sharedApplication].keyWindow;
			if( !keyWindow ) return;
			
			UIViewController *rootViewController=keyWindow.rootViewController;
			if( !rootViewController ) return;
			
			[_rewardBasedVideoAd presentFromRootViewController:rootViewController];
				
		}
			
	}else if( _interstitialAd ){
		
		if( _interstitialAd.isReady ){
		
			UIWindow *keyWindow=[UIApplication sharedApplication].keyWindow;
			if( !keyWindow ) return;
			
			UIViewController *rootViewController=keyWindow.rootViewController;
			if( !rootViewController ) return;
			
			[_interstitialAd presentFromRootViewController:rootViewController];
		}
	}
}

bool WXAdView::getVisible(){

	return _adView && _adView.hidden==NO;
}

int WXAdView::getState(){

	return _state;
}

int WXAdView::getError(){

	return _error;
}

wxString WXAdView::getRewardType(){

	return _rewardType;
}

int WXAdView::getRewardAmount(){

	return _rewardAmount;
}

void WXAdView::consumeReward(){

	_rewardType="";
	
	_rewardAmount=0;
}

void WXAdView::reload(){

	_state=0;

	if( _size=="rewardedvideo" ){
		
		createRewardBasedVideoAd();
	
	}else if( _size=="interstitial" ){
		
		createInterstitialAd();
	
	}else{
		
		createBannerAd();
	}
}

