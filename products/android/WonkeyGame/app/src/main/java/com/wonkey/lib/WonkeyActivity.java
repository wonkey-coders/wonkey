package com.wonkey.lib;

import android.os.Bundle;
import android.os.Looper;
import android.util.Log;
import android.content.Intent;
import android.view.ViewGroup;
import android.support.v4.app.ActivityCompat;

import org.libsdl.app.SDLActivity;

import java.util.List;
import java.util.LinkedList;

public class WonkeyActivity extends SDLActivity implements ActivityCompat.OnRequestPermissionsResultCallback{

    private static final String TAG = "WonkeyActivity";

    public static WonkeyActivity mSingleton;

    public static List<Delegate> mDelegates=new LinkedList<Delegate>();

    public static class Delegate{

        public void onActivityResult( int requestCode,int resultCode,Intent data ){}
        
		public void onRequestPermissionsResult( int requestCode,String[] permissions,int[] results ){}
    }

    public static WonkeyActivity instance(){

        return mSingleton;
    }

    public static ViewGroup layout(){

        return mSingleton.mLayout;
    }

    public static void addDelegate( Delegate delegate ){

        if( mDelegates.contains( delegate ) ) return;

        mDelegates.add( delegate );
    }

    // ***** overrides *****

    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        mSingleton = this;
    }

    protected void onDestroy() {

        super.onDestroy();
    }

    protected void onActivityResult( int requestCode,int resultCode,Intent data ){

        for( Delegate delegate : mDelegates ){

            delegate.onActivityResult( requestCode,resultCode,data );
        }
    }

	public void onRequestPermissionsResult( int requestCode,String[] permissions,int[] results ){

        for( Delegate delegate : mDelegates ){

            delegate.onRequestPermissionsResult( requestCode,permissions,results );
        }
	}
    
}
