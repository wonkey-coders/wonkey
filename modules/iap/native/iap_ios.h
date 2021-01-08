
#ifndef WX_IAP_IOS_H
#define WX_IAP_IOS_H

#import <wxwonkey.h>

#ifdef __OBJC__

#import <StoreKit/StoreKit.h>

class WXIAPStore;
	
@interface WXIAPStoreDelegate : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>{
@private
WXIAPStore *_peer;
}
-(id)initWithPeer:(WXIAPStore*)peer;
-(void)productsRequest:(SKProductsRequest*)request didReceiveResponse:(SKProductsResponse*)response;
-(void)paymentQueue:(SKPaymentQueue*)queue updatedTransactions:(NSArray*)transactions;
-(void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue*)queue;
-(void)paymentQueue:(SKPaymentQueue*)queue restoreCompletedTransactionsFailedWithError:(NSError*)error;
-(void)request:(SKRequest*)request didFailWithError:(NSError*)error;

@end

#else

#include <objc/objc.h>

typedef struct objc_object SKProduct;
typedef struct objc_object SKProductsRequest;
typedef struct objc_object SKProductsResponse;
typedef struct objc_object SKPaymentQueue;
typedef struct objc_object NSArray;
typedef struct objc_object NSError;
typedef struct objc_object SKRequest;
typedef struct objc_object WXIAPStoreDelegate;
typedef struct objc_object NSNumberFormatter;

#endif

struct WXProduct : public wxObject{
	
	WXProduct();
	~WXProduct();
	
	SKProduct *product;

	bool valid;
	wxString title;
	wxString identifier;
	wxString description;
	wxString price;
	int type;
	bool owned;
	bool interrupted;
};

struct WXIAPStore : public wxObject{
	
	WXIAPStore();
	
	bool OpenStoreAsync( wxArray<wxGCVar<WXProduct>> products );
	bool BuyProductAsync( WXProduct* product );
	bool GetOwnedProductsAsync();
	void CloseStore();
	
	bool IsRunning();
	int GetResult();
	
	static bool CanMakePayments();
	
	WXProduct *FindProduct( wxString id );
	void OnRequestProductDataResponse( SKProductsRequest *request,SKProductsResponse *response );
	void OnUpdatedTransactions( SKPaymentQueue *queue,NSArray *transactions );
	void OnRestoreTransactionsFinished( SKPaymentQueue *queue,NSError *error );
	void OnRequestFailed( SKRequest *request,NSError *error );
	
	virtual void gcMark();
	
	WXIAPStoreDelegate *_delegate;

	NSNumberFormatter *_priceFormatter;

	wxArray<wxGCVar<WXProduct>> _products;

	bool _running;
	
	int _result;
};

#endif
