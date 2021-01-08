
// ***** appstore.h *****

#include "iap_ios.h"

@implementation WXIAPStoreDelegate

-(id)initWithPeer:(WXIAPStore*)peer{

	if( self=[super init] ){
	
		_peer=peer;
	}
	return self;
}

-(void)productsRequest:(SKProductsRequest*)request didReceiveResponse:(SKProductsResponse*)response{

	_peer->OnRequestProductDataResponse( request,response );
}

-(void)paymentQueue:(SKPaymentQueue*)queue updatedTransactions:(NSArray*)transactions{

	_peer->OnUpdatedTransactions( queue,transactions );
}

-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue*)queue{

	_peer->OnRestoreTransactionsFinished( queue,0 );
}

-(void)paymentQueue:(SKPaymentQueue*)queue restoreCompletedTransactionsFailedWithError:(NSError*)error{

	_peer->OnRestoreTransactionsFinished( queue,error );
}

-(void)request:(SKRequest*)request didFailWithError:(NSError*)error{

	_peer->OnRequestFailed( request,error );
}

@end

WXProduct::WXProduct():product(0),valid(false),type(0),owned(false),interrupted(false){
}

WXProduct::~WXProduct(){

//	[product release];
}

// ***** IAPStore *****

WXIAPStore::WXIAPStore():_running( false ),_products( 0 ),_result( -1 ){

	_priceFormatter=[[NSNumberFormatter alloc] init];
	
	[_priceFormatter setFormatterBehavior:NSNumberFormatterBehavior10_4];
	[_priceFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
}

bool WXIAPStore::OpenStoreAsync( wxArray<wxGCVar<WXProduct>> products ){

	if( _running || _products.length() ) return false;

	if( ![SKPaymentQueue canMakePayments] ) return false;
	
	if( !_delegate ){	
		_delegate=[[WXIAPStoreDelegate alloc] initWithPeer:this];
	
		[[SKPaymentQueue defaultQueue] addTransactionObserver:_delegate];
	}
	
	_products=products;
	
	id __strong *objs=new id[products.length()];

	for( int i=0;i<products.length();++i ){
		objs[i]=products[i]->identifier.ToNSString();
	}
	
	NSSet *set=[NSSet setWithObjects:objs count:products.length()];
	
	SKProductsRequest *request=[[SKProductsRequest alloc] initWithProductIdentifiers:set];
	
    request.delegate=_delegate;
    
    _running=true;

	_result=-1;

    [request start];
    
    return true;
}

bool WXIAPStore::BuyProductAsync( WXProduct *prod ){

	if( _running || !_products.length() || !prod || !prod->valid ) return false; 

	if( ![SKPaymentQueue canMakePayments] ) return false;
	
	SKMutablePayment *payment=[SKMutablePayment paymentWithProduct:prod->product];
	
	_running=true;

	_result=-1;
	
	[[SKPaymentQueue defaultQueue] addPayment:payment];
	
	return true;
}

bool WXIAPStore::GetOwnedProductsAsync(){

	if( _running || !_products.length() ) return false;

	if( ![SKPaymentQueue canMakePayments] ) return false;
	
	_running=true;
	
	_result=-1;
	
	[[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
	
	return true;
}

void WXIAPStore::CloseStore(){

	if( !_delegate ) return;
	
	[[SKPaymentQueue defaultQueue] removeTransactionObserver:_delegate];

	_delegate=0;
}

bool WXIAPStore::IsRunning(){

	return _running;
}

int WXIAPStore::GetResult(){

	return _result;
}

bool WXIAPStore::CanMakePayments(){

	return [SKPaymentQueue canMakePayments];
}

WXProduct *WXIAPStore::FindProduct( wxString id ){

	for( int i=0;i<_products.length();++i ){
	
		WXProduct *p=_products[i];
		
		if( p->identifier==id ) return p;
	}

	return 0;
}

void WXIAPStore::OnRequestProductDataResponse( SKProductsRequest *request,SKProductsResponse *response ){

	//Get product details
	for( SKProduct *p in response.products ){
	
//		printf( "product=%p\n",p );fflush( stdout );
	
		WXProduct *prod=FindProduct( p.productIdentifier );
		if( !prod ) continue;
		
		[_priceFormatter setLocale:p.priceLocale];
		
		prod->valid=true;
		prod->product=p;	//[p retain];
		prod->title=wxString( p.localizedTitle );
		prod->identifier=wxString( p.productIdentifier );
		prod->description=wxString( p.localizedDescription );
		prod->price=wxString( [_priceFormatter stringFromNumber:p.price] );
	}
	
	_result=-1;
	
	for( int i=0;i<_products.length();++i ){
	
		if( !_products[i]->product ) continue;
		
		_result=0;
		break;
	}

	if( _result==-1 ){	
		[[SKPaymentQueue defaultQueue] removeTransactionObserver:_delegate];

		_delegate=0;
	}

	_running=false;
}

void WXIAPStore::OnUpdatedTransactions( SKPaymentQueue *queue,NSArray *transactions ){

	_result=-1;

	for( SKPaymentTransaction *transaction in transactions ){
	
		if( transaction.transactionState==SKPaymentTransactionStatePurchased ){
		
//			printf( "IAP purchased\n" );fflush( stdout );
			
			_result=0;
			
			_running=false;
			
		}else if( transaction.transactionState==SKPaymentTransactionStateFailed ){
		
//			printf( "IAP failed %i\n",transaction.error.code );fflush( stdout );
			
			_result=(transaction.error.code==SKErrorPaymentCancelled) ? 1 : -1;
			
			_running=false;
			
		}else if( transaction.transactionState==SKPaymentTransactionStateRestored ){
		
//			printf( "IAP restored\n" );fflush( stdout );
			
			if( WXProduct *p=FindProduct( transaction.payment.productIdentifier ) ) p->owned=true;
		
		}else{
		
//			printf( "IAP ?????\n" );fflush( stdout );

			continue;
		}
		
		[queue finishTransaction:transaction];
	}
}

void WXIAPStore::OnRestoreTransactionsFinished( SKPaymentQueue *queue,NSError *error ){

	_result=error ? (error.code==SKErrorPaymentCancelled ? 1 : -1) : 0;
	
	_running=false;
}

void WXIAPStore::OnRequestFailed( SKRequest *request,NSError *error ){

	[[SKPaymentQueue defaultQueue] removeTransactionObserver:_delegate];

	_delegate=0;

	_running=false;
}

void WXIAPStore::gcMark(){

	wxGCMark( _products );
}
