
package com.wonkey.lib;

import android.os.*;
import android.app.*;
import android.content.*;

import java.util.*;

import com.android.vending.billing.*;

import org.json.*;

public class WonkeyIAP extends WonkeyActivity.Delegate implements ServiceConnection{

    private static final String TAG = "WonkeyIAP";

	private static final int ACTIVITY_RESULT_REQUEST_CODE=101;

	public static class Product{
	
		public boolean valid;
		public String title;
		public String identifier;
		public String description;
		public String price;
		public int type;
		public boolean owned;
		public boolean interrupted;
		
		Product( String identifier,int type ){
			this.identifier=identifier;
			this.type=type;
		}
	}
	
	public WonkeyIAP(){

		//Log.v( TAG,"WonkeyIAP()" );

		_activity=WonkeyActivity.instance();
		
		Intent intent=new Intent( "com.android.vending.billing.InAppBillingService.BIND" );

		intent.setPackage( "com.android.vending" );
	
		_activity.bindService( intent,this,Context.BIND_AUTO_CREATE );
	}

	public boolean OpenStoreAsync( Product[] products ){
	
		if( _running ) return false;
	
		_products=products;
		
		OpenStoreThread thread=new OpenStoreThread();
		
		_running=true;
		
		_result=-1;

		thread.start();
		
		return true;
	}

	public boolean BuyProductAsync( Product p ){
	
		if( _running ) return false;
	
		_result=-1;
	
		try{
			Bundle buy=_service.getBuyIntent( 3,_activity.getPackageName(),p.identifier,"inapp","NOP" );
			int response=buy.getInt( "RESPONSE_CODE" );
			
			if( response==0 ){
				
				PendingIntent intent=buy.getParcelable( "BUY_INTENT" );
				if( intent!=null ){
				
					Integer zero=Integer.valueOf( 0 );
					_activity.startIntentSenderForResult( intent.getIntentSender(),ACTIVITY_RESULT_REQUEST_CODE,new Intent(),zero,zero,zero );
					
					_running=true;
					return true;
				}
			}
			switch( response ){
			case 1:
				_result=1;	//cancelled
				break;
			case 7:
				_result=0;	//already purchased
				break;
			}
		}catch( IntentSender.SendIntentException ex ){
		
		}catch( RemoteException ex ){
		}
		
		return true;
	}
	
	public boolean GetOwnedProductsAsync(){
	
		if( _running ) return false;
	
		_result=0;
		
		return true;
	}
	
	public boolean IsRunning(){

		return _running;
	}
	
	public int GetResult(){

		return _result;
	}
	
	// ***** PRIVATE *****

	Activity _activity;
	IInAppBillingService _service;
	Object _mutex=new Object();
	boolean _running;
	int _result=-1;
	Product[] _products;
	ArrayList unconsumed=new ArrayList();
	
	Product FindProduct( String id ){
		for( int i=0;i<_products.length;++i ){
			if( id.equals( _products[i].identifier ) ) return _products[i];
		}
		return null;
	}
	
	class OpenStoreThread extends Thread{
	
		public void run(){
		
			//wait for service to start
			synchronized( _mutex ){
				while( _service==null ){
					try{
						_mutex.wait();
					}catch( InterruptedException ex ){
					
					}catch( IllegalMonitorStateException ex ){
					
					}
				}
			}
			
			int i0=0;
			while( i0<_products.length ){
			
				ArrayList list=new ArrayList();
				for( int i1=Math.min( i0+20,_products.length );i0<i1;++i0 ){
					list.add( _products[i0].identifier );
				}

				Bundle query=new Bundle();
				query.putStringArrayList( "ITEM_ID_LIST",list );
				
				_result=0;
	
				try{
	
					//Get product details
					Bundle details=_service.getSkuDetails( 3,_activity.getPackageName(),"inapp",query );
					ArrayList detailsList=details.getStringArrayList( "DETAILS_LIST" );
					
					if( detailsList==null ){
						_result=-1;
						_running=false;
						return;
					}
					
					for( int i=0;i<detailsList.size();++i ){
					
						JSONObject jobj=new JSONObject( (String)detailsList.get( i ) );
	
						Product p=FindProduct( jobj.getString( "productId" ) );
						if( p==null ) continue;
	
						//strip (APP_NAME) from end of title					
						String title=jobj.getString( "title" );
						if( title.endsWith( ")" ) ){
							int j=title.lastIndexOf( " (" );
							if( j!=-1 ) title=title.substring( 0,j );
						}
						
						p.valid=true;
						p.title=title;
						p.description=jobj.getString( "description" );
						p.price=jobj.getString( "price" );
					}
					
					//Get owned products and consume consumables
					Bundle owned=_service.getPurchases( 3,_activity.getPackageName(),"inapp",null );
					ArrayList itemList=owned.getStringArrayList( "INAPP_PURCHASE_ITEM_LIST" );
					ArrayList dataList=owned.getStringArrayList( "INAPP_PURCHASE_DATA_LIST" );
	
					if( itemList==null || dataList==null ){
						_result=-1;
						_running=false;
						return;
					}
					
					//consume consumables
					for( int i=0;i<itemList.size();++i ){
					
						Product p=FindProduct( (String)itemList.get( i ) );
						if( p==null ) continue;
						
						if( p.type==1 ){
	
							JSONObject jobj=new JSONObject( (String)dataList.get( i ) );
							int response=_service.consumePurchase( 3,_activity.getPackageName(),jobj.getString( "purchaseToken" ) );
							if( response!=0 ){
								p.valid=false;
								_result=-1;
								break;
							}
							p.interrupted=true;

						}else if( p.type==2 ){
	
							p.owned=true;
						}
					}
					
				}catch( RemoteException ex ){
					_result=-1;
				}catch( JSONException ex ){
					_result=-1;
				}
			}
			_running=false;
		}
	}
	
	class ConsumeProductThread extends Thread{
	
		String _token;
		
		ConsumeProductThread( String token ){
			_token=token;
		}
		
		public void run(){
		
			try{
				int response=_service.consumePurchase( 3,_activity.getPackageName(),_token );
				if( response==0 ) _result=0;
			}catch( RemoteException ex ){
			}
			
			_running=false;
		}
	}

	@Override
	public void onServiceDisconnected( ComponentName name ){
		_service=null;
	}

	@Override
	public void onServiceConnected( ComponentName name,IBinder service ){
		_service=IInAppBillingService.Stub.asInterface( service );

		WonkeyActivity.addDelegate( this );

		synchronized( _mutex ){
			try{
				_mutex.notify();
			}catch( IllegalMonitorStateException ex ){
			}
		}
	}

	@Override	
	public void onActivityResult( int requestCode,int resultCode,Intent data ){
	
		if( requestCode!=ACTIVITY_RESULT_REQUEST_CODE ) return;

		int response=data.getIntExtra( "RESPONSE_CODE",0 );
		
		switch( response ){
		case 0:
			try{
				JSONObject pdata=new JSONObject( data.getStringExtra( "INAPP_PURCHASE_DATA" ) );
				Product p=FindProduct( pdata.getString( "productId" ) );
				if( p!=null ){
					if( p.type==1 ){
						ConsumeProductThread thread=new ConsumeProductThread( pdata.getString( "purchaseToken" ) );
						thread.start();
						return;
					}else if( p.type==2 ){
						p.owned=true;
						_result=0;
					}
				}
			}catch( JSONException ex ){
			}
			break;
		case 1:
			_result=1;	//cancelled
			break;
		case 7:
			_result=0;	//already purchased
			break;
		}

		_running=false;
	}
}
