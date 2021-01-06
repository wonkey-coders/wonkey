package com.wonkey.lib;

import android.util.Log;
import android.content.Intent;
import android.net.Uri;

public class WonkeyRequesters {

    private static final String TAG = "WonkeyRequesters";
    
    static public void openUrl( String url ) {
    
		  //Log.v( TAG,"openUrl, url="+url );
    
      Intent browserIntent=new Intent( Intent.ACTION_VIEW,Uri.parse( url ) );
      
      WonkeyActivity.instance().startActivity( browserIntent );
    }
    
}
