
#include <wxwonkey.h>

#include "../../std/async/native/async_cb.h"

#ifdef __OBJC__

#import "GoogleMobileAds/GADBannerView.h"
#import "GoogleMobileAds/GADInterstitial.h"
#import "GoogleMobileAds/GADRewardBasedVideoAd.h"
#import "GoogleMobileAds/GADRewardBasedVideoAdDelegate.h"
#import "GoogleMobileAds/GADAdReward.h"

@interface WXAdmobDelegate : NSObject<GADBannerViewDelegate,GADInterstitialDelegate,GADRewardBasedVideoAdDelegate>

@end

#else

#include <objc/objc.h>

typedef struct objc_object WXAdmobDelegate;
typedef struct objc_object GADRequest;
typedef struct objc_object GADInterstitial;
typedef struct objc_object GADBannerView;
typedef struct objc_object GADRewardBasedVideoAd;

#endif

class WXAdView : public wxObject{

	public:
	
	WXAdView(){}
	
	WXAdView( wxString size,wxString layout,wxString adUnitId,wxBool visible );
	
	void start( int callback );
	
	void setState( int state );
	
	void setVisible( bool visible );
	
	bool getVisible();
	
	int getState();
	
	wxString getRewardType();
	
	int getRewardAmount();
	
	void consumeReward();
	
	int getError();

	void reload();

	void createRewardBasedVideoAd();
	
	void createInterstitialAd();
	
	void createBannerAd();
	
//	private:

	wxString _size;
	
	wxString _layout;
	
	wxString _adUnitId;
	
	wxBool _visible;
	
	int _callback=0;
			
	int _state=0;
	
	WXAdmobDelegate *_adDelegate=0;

	GADRewardBasedVideoAd *_rewardBasedVideoAd=0;
	
	GADInterstitial *_interstitialAd=0;
	
	GADBannerView *_adView=0;

	GADRequest *_adRequest=0;
	
	wxString _rewardType="";
	
	int _rewardAmount=0;
	
	int _error=0;
};
