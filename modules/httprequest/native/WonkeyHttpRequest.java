
package com.wonkey.lib;

import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class WonkeyHttpRequest{

	private static final String TAG = "WonkeyHttpRequest";

	HttpURLConnection connection;
	
	int readyState;
	
	boolean sending;

    native void onNativeReadyStateChanged( int state );
    
    native void onNativeResponseReceived( String response,int status,int state );
    
    void setReadyState( int state ){
    
    	if( state==readyState ) return;
    	
    	onNativeReadyStateChanged( state );
    	
    	readyState=state;
    }
	
	void open( String req,String url ){
	
		if( readyState!=0 ) return;
		
		try{
		
			URL turl=new URL( url );
			connection=(HttpURLConnection)turl.openConnection();
			connection.setRequestMethod( req );
			
			setReadyState( 1 );
			
		}catch( IOException ex ){
		
			Log.v( TAG,ex.toString() );
				
			setReadyState( 5 );
		}		
	}
	
	void setHeader( String name,String value ){
	
		if( readyState!=1 || sending ) return;
	
		connection.setRequestProperty( name,value );
	}
	
	void send( final String text,final int timeout ){
	
		if( readyState!=1 || sending ) return;
				
		sending=true;
		
		new Thread( new Runnable(){
		
			public void run(){
			
				connection.setConnectTimeout( timeout );
		
				connection.setReadTimeout( timeout );
				
				try{
				
					if( text!=null && text.length()!=0 ){
			
						byte[] bytes=text.getBytes( "UTF-8" );

						connection.setDoOutput( true );
						connection.setFixedLengthStreamingMode( bytes.length );
				
						OutputStream out=connection.getOutputStream();
						out.write( bytes,0,bytes.length );
						out.close();
					}
					
					InputStream in=connection.getInputStream();
					
					setReadyState( 3 );

					byte[] buf=new byte[4096];
					ByteArrayOutputStream out=new ByteArrayOutputStream(1024);
					for( ;; ){
						int n=in.read( buf );
						if( n<0 ) break;
						out.write( buf,0,n );
					}
					in.close();

					String response=new String( out.toByteArray(),"UTF-8" );

					int status=connection.getResponseCode();
					
					onNativeResponseReceived( response,status,4 );
					
					readyState=4;
					
				}catch( IOException ex ){
				
					Log.v( TAG,ex.toString() );
				
					setReadyState( 5 );
				}

				connection.disconnect();

				sending=false;
			}
		} ).start();
	}
	
	void cancel(){
	
		connection.disconnect();
	}
}
