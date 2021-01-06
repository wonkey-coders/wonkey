
package com.wonkey.lib;

import android.util.Log;

public class WonkeyAsync{

    private static final String TAG = "WonkeyAsync";
    
    public static native void invokeAsyncCallback( int callback );
}
