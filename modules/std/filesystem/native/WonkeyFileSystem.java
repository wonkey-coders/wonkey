package com.wonkey.lib;

import android.util.Log;

public class WonkeyFileSystem{

    private static final String TAG = "WonkeyFileSystem";
    
    public static String getSpecialDir( String name ){
    
		//Log.v( TAG,"getSpecialDir, name="+name );
		
		java.io.File f=null;
		
		if( name.equals( "internal" ) ){
	    	f=WonkeyActivity.instance().getFilesDir();
	    }else if( name.equals( "external" ) ){
	    	f=WonkeyActivity.instance().getExternalFilesDir( null );
	    }

		if( f!=null ) return f.getAbsolutePath()+"/";
	    
	    return "";
    }
}
	