
package com.wonkey.lib;

import android.util.Log;
import android.support.v4.content.ContextCompat;
import android.support.v4.app.ActivityCompat;
import android.Manifest;
import android.content.pm.PackageManager;

public class WonkeyPermissions extends WonkeyActivity.Delegate{

    private static final String TAG = "WonkeyPermissions";
    
	String result="";
	int callback;
	
	WonkeyPermissions(){
	
		WonkeyActivity.instance().addDelegate( this );
	}

 	public int checkPermission( String permission ){
 	
		if( ContextCompat.checkSelfPermission( WonkeyActivity.instance(),permission )==PackageManager.PERMISSION_GRANTED ) return 1;

 		return 0;
    }
    
    public void requestPermissions( String permissions,int callback ){
    
    	this.callback=callback;
    	
    	ActivityCompat.requestPermissions( WonkeyActivity.instance(),permissions.split( ";" ),101 );
    }
    
    public String requestPermissionsResult(){
    
	    return result;
    }
    
	public void onRequestPermissionsResult( int requestCode,String[] permissions,int[] results ){
	
		switch( requestCode ){
		case 101:
			result="";
			for( int i=0;i<results.length;++i ){
				if( i>0 ) result+=";";
				this.result+=(results[i]==PackageManager.PERMISSION_GRANTED ? "1" : "0" );
			}
			WonkeyAsync.invokeAsyncCallback( callback );
		}
	}
}
