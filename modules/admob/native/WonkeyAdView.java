
package com.wonkey.lib;

import android.provider.Settings;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.reward.RewardItem;
import com.google.android.gms.ads.reward.RewardedVideoAd;
import com.google.android.gms.ads.reward.RewardedVideoAdListener;

import org.libsdl.app.SDLActivity;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class WonkeyAdView{

    private static final String TAG = "WonkeyAdView";

    String _size;
    String _layout;
    String _adUnitId;
    boolean _visible;
    int _callback;

    RewardedVideoAd _rewardedVideoAd;
    InterstitialAd _interstitialAd;
    AdView _adView;
    int _adState;
    int _error;
    String _rewardType="";
    int _rewardAmount;

    public WonkeyAdView( final String size,final String layout,final String adUnitId,final boolean visible ){

        _size=size;
        _layout=layout;
        _adUnitId=adUnitId;
        _visible=visible;
    }

    void start( int callback ){

        this._callback=callback;

        WonkeyActivity.instance().runOnUiThread( new Runnable() {

            public void run() {

                if( _size.equals( "rewardedvideo" ) ){

                    createRewardedVideoAd();

                }else if( _size.equals( "interstitial" ) ){

                    createInterstitialAd();

                }else{

                    createBannerAd();
                }

                requestAd();
            }
        } );
    }

    void setState( int state ){

        if( state==_adState ) return;

        _adState=state;

        WonkeyAsync.invokeAsyncCallback( _callback );
    }

    void createRewardedVideoAd(){

        if( _adUnitId.equals( "" ) ) _adUnitId="ca-app-pub-3940256099942544/5224354917";

        _rewardedVideoAd=MobileAds.getRewardedVideoAdInstance( WonkeyActivity.instance() );

        _rewardedVideoAd.setRewardedVideoAdListener( new RewardedVideoAdListener(){

            public void onRewardedVideoAdLoaded(){

                Log.i( TAG,"onRewardedVideoAdLoaded" );

                setState( 2 );
            }

            public void onRewardedVideoAdFailedToLoad( int _errorCode ){

                Log.i( TAG,"onRewardedVideoAdFailedToLoad, _errorCode="+_errorCode );

                _error=_errorCode;

                setState( 3 );
            }

            public void onRewardedVideoAdOpened(){

                Log.i( TAG,"onRewardedVideoAdOpened" );
            }

            public void onRewardedVideoStarted(){

                Log.i( TAG,"onRewardedVideoStarted" );
            }

            public void onRewardedVideoCompleted(){

                Log.i( TAG,"onRewardedVideoCompleted" );
            }

            public void onRewardedVideoAdLeftApplication(){

                Log.i( TAG,"onRewardedVideoAdLeftApplication" );
            }

            public void onRewarded( RewardItem reward ){

                Log.i( TAG,"onRewarded type='"+reward.getType()+"', amount="+reward.getAmount() );

                _rewardType=reward.getType();

                _rewardAmount=reward.getAmount();
            }

            public void onRewardedVideoAdClosed(){

                Log.i( TAG, "onRewardedVideoAdClosed" );

                setState( 0 );
            }

        } );
    }

    void createInterstitialAd(){

        if( _adUnitId.equals( "" ) ) _adUnitId="ca-app-pub-3940256099942544/1033173712";

        _interstitialAd=new InterstitialAd( WonkeyActivity.instance() );
        _interstitialAd.setAdUnitId( _adUnitId );

        _interstitialAd.setAdListener( new AdListener() {

            public void onAdLoaded() {

                Log.i( TAG,"onAdLoaded" );

                setState( 2 );
            }

            public void onAdFailedToLoad( int _errorCode ){

                Log.i( TAG,"onAdFailedToLoad, _errorCode="+_errorCode );

                _error=_errorCode;

                setState( 3 );
            }

            public void onAdClosed() {

                Log.i( TAG,"onAdClosed" );

                setState( 0 );
            }
        });
    }

    void createBannerAd(){

        if(  _adUnitId.equals( "" ) ) _adUnitId="ca-app-pub-3940256099942544/6300978111";

        AdSize adSize=AdSize.SMART_BANNER;

        if( _size.equals( "banner" ) ){
            adSize=AdSize.BANNER;
        }else if( _size.equals( "large-banner" ) ) {
            adSize=AdSize.LARGE_BANNER;
        }else if( _size.equals( "medium-rectangle" ) ) {
            adSize=AdSize.MEDIUM_RECTANGLE;
        }else if( _size.equals( "full-banner" ) ){
            adSize=AdSize.FULL_BANNER;
        }else if( _size.equals( "leaderboard" ) ){
            adSize=AdSize.LEADERBOARD;
        }

        RelativeLayout.LayoutParams params=
                new RelativeLayout.LayoutParams( RelativeLayout.LayoutParams.WRAP_CONTENT,RelativeLayout.LayoutParams.WRAP_CONTENT );

        if( _layout.equals( "top" ) ){
            params.addRule( RelativeLayout.ALIGN_PARENT_TOP );
            params.addRule( RelativeLayout.CENTER_HORIZONTAL );
        }else if( _layout.equals( "top-left" ) ){
            params.addRule( RelativeLayout.ALIGN_PARENT_TOP );
            params.addRule( RelativeLayout.ALIGN_PARENT_LEFT );
        }else if( _layout.equals( "top-right" ) ){
            params.addRule( RelativeLayout.ALIGN_PARENT_TOP );
            params.addRule( RelativeLayout.ALIGN_PARENT_RIGHT );
        }else if( _layout.equals( "left" ) ){
            params.addRule( RelativeLayout.ALIGN_PARENT_LEFT );
            params.addRule( RelativeLayout.CENTER_VERTICAL );
        }else if( _layout.equals( "right") ){
            params.addRule( RelativeLayout.ALIGN_PARENT_RIGHT );
            params.addRule( RelativeLayout.CENTER_VERTICAL );
        }else if( _layout.equals( "bottom" ) ){
            params.addRule( RelativeLayout.ALIGN_PARENT_BOTTOM );
            params.addRule( RelativeLayout.CENTER_HORIZONTAL );
        }else if( _layout.equals( "bottom-left") ){
            params.addRule( RelativeLayout.ALIGN_PARENT_BOTTOM );
            params.addRule( RelativeLayout.ALIGN_PARENT_LEFT );
        }else if( _layout.equals( "bottom-right") ){
            params.addRule( RelativeLayout.ALIGN_PARENT_BOTTOM );
            params.addRule( RelativeLayout.ALIGN_PARENT_RIGHT );
        }else{
            params.addRule( RelativeLayout.CENTER_VERTICAL );
            params.addRule( RelativeLayout.CENTER_HORIZONTAL );
        }

        _adView=new AdView( WonkeyActivity.instance() );

        _adView.setAdSize( adSize );

        _adView.setAdUnitId( _adUnitId );

        if( !_visible ) _adView.setVisibility( View.GONE );

        _adView.setAdListener( new AdListener(){

            public void onAdLoaded() {

                Log.i( TAG,"onAdLoaded" );

                _adView.bringToFront();

                setState( 2 );
            }

            public void onAdFailedToLoad( int _errorCode ){

                Log.i( TAG,"onAdFailedToLoad, _errorCode="+_errorCode );

                _error=_errorCode;

                setState( 3 );
            }
        });

        WonkeyActivity.layout().addView( _adView,params );
    }

    //must be called on main thread...!
    //
    void requestAd(){

        AdRequest.Builder builder=new AdRequest.Builder();

        AdRequest adRequest=builder.build();

        setState( 1 );

        if( _rewardedVideoAd!=null ){

            _rewardedVideoAd.loadAd( _adUnitId,adRequest );

        }else if( _interstitialAd!=null ){

            if( _interstitialAd.isLoaded() ){	//interstitials cant be 'reloaded'?

                setState( 2 );

            }else{

                _interstitialAd.loadAd( adRequest );
            }

        }else if( _adView!=null ) {

            _adView.loadAd( adRequest );

        }
    }

    public void setVisible( boolean visible ){

        if( visible ){

            WonkeyActivity.instance().runOnUiThread( new Runnable(){

                public void run() {

                    if( _adState!=2 ) return;

                    if( _rewardedVideoAd!=null ){

                        _rewardedVideoAd.show();

                    }else if( _interstitialAd!=null ){

                        _interstitialAd.show();

                    }else if( _adView!=null ){

                        _adView.setVisibility( View.VISIBLE );

                        _adView.bringToFront();
                    }

                }

            } );

        }else{

            WonkeyActivity.instance().runOnUiThread( new Runnable(){

                public void run() {

                    if( _adState!=2 ) return;

                    if( _adView!=null ){

                        _adView.setVisibility( View.GONE );
                    }
                }

            } );
        }
    }

    public boolean getVisible(){

        return (_adView!=null) ? _adView.getVisibility()==View.VISIBLE : false;
    }

    public int getState(){

        return _adState;
    }

    public String getRewardType(){

        return _rewardType;
    }

    public int getRewardAmount(){

        return _rewardAmount;
    }

    public void consumeReward(){

        _rewardType="";

        _rewardAmount=0;
    }

    public int getError(){

        return _error;
    }

    public void reload(){

        _adState=0;

        WonkeyActivity.instance().runOnUiThread( new Runnable(){

            public void run() {

                requestAd();
            }
        } );
    }

}
