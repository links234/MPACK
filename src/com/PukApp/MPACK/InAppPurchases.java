package com.PukApp.MPACK;
import java.io.UnsupportedEncodingException;
import java.nio.charset.Charset;
import java.security.GeneralSecurityException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.util.ArrayList;
import java.util.List;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.SecretKeySpec;

import com.android.vending.billing.IInAppBillingService;
import com.google.android.gms.plus.Plus;

import android.content.Intent;
import android.content.res.Resources;
import android.util.Base64;
import android.util.Log;

public class InAppPurchases {
	static MainActivity mContext;
	static IabHelper mHelper;
	static IInAppBillingService mService;

	final static String TAG = "InAppPurchases";

	final static int Binding = 0;
	final static int BindingError = -1;
	final static int BindingDone = 1;

	final static int NoProcess = 0;
	final static int Processing = 1;
	final static int Success = 2;
	final static int PurchaseCanceled = 3;
	final static int PurchaseError = -1;
	final static int ConsumeError = -2;
	
	final static int NoType = 0;
	final static int PurchaseType = 1;
	final static int SubscriptionType = 2;
	
	final static int Querying = 1;
	final static int QueryFinished = 2;
	final static int QueryConsuming = 3;
	final static int QueryError = -1;
	final static int QueryPriceFinished = 4;
	final static int QueryingPrice = 5;
	
	final static String Separator = "###";
	
	static int mCurrentProcessType = NoType;
	static int mCurrentProcessState = NoProcess;
	static int mCurrentQueryProcessState = NoProcess;
	static Inventory mCurrentQueryInventory;
	static List<Purchase> mCurrentQueryAllPurchases = new ArrayList<Purchase>();
	static List<String> mConsumedItemsId = new ArrayList<String>();
	static ArrayList<String> mCurrentQueryPrices = new ArrayList<String>();
	static ArrayList<String> mCurrentPriceQueryIds = new ArrayList<String> ();
			
	static int mConsumedItemsIndex = 0;
	
	final static int RC_REQUEST = 5435;
	
	static int mServiceBindingState;
	static String mCurrentDeveloperPayload = "";
	
	public InAppPurchases(MainActivity context)
	{
		mContext = context;

		Resources res = mContext.getResources();
		String password = res.getString(R.string.password);
		String salt = res.getString(R.string.salt);
		String license_code = res.getString(R.string.license);
		AesCbcWithIntegrity.CipherTextIvMac cipherTextIvMac = new AesCbcWithIntegrity.CipherTextIvMac(license_code);
		AesCbcWithIntegrity.SecretKeys keys;
		try {
			keys = AesCbcWithIntegrity.generateKeyFromPassword(password, salt);
			mHelper = new IabHelper(mContext, AesCbcWithIntegrity.decryptString(cipherTextIvMac, keys));
		} catch (GeneralSecurityException e) {
			Log.d(TAG, "GeneralSecurityException");
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			Log.d(TAG, "UnsupportedEncodingException");
			e.printStackTrace();
		}

	}
	
	public void purchase(String purchaseId, String developerPayload)
	{
		mCurrentDeveloperPayload = developerPayload;
		Log.w(TAG, "purchaseAndConsume");
		if (mCurrentProcessState != Processing)
		{
			mCurrentProcessState = Processing;
			mCurrentProcessType = PurchaseType;
			initPurchase(purchaseId, true);
		}
	}

	
	public void subscribe(String purchaseId, String developerPayload) 
	{
		mCurrentDeveloperPayload = developerPayload;
		if (mCurrentProcessState != Processing)
		{
			mCurrentProcessState = Processing;
			mCurrentProcessType = SubscriptionType; 
			initPurchase(purchaseId, false);
		}
	}
	
	public ArrayList<String> getAllPrices()
	{
		return mCurrentQueryPrices;
	}

	public void sendInAppPurchasesToCpp()
	{
		nativeInAppPurchases();
	}

	public native void nativeInAppPurchases();

	public void bindServices()
	{
		if (mHelper != null)
		{
			mServiceBindingState = Binding;
			mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener()
			{
				public void onIabSetupFinished(IabResult result)
				{
					if (!result.isSuccess())
					{
						Log.d(TAG , "Problem setting up In-app Billing: " + result);
						mServiceBindingState = BindingError;
					}
					else
					{
						Log.w(TAG, "Binding ok" );
						mServiceBindingState = BindingDone;
					}
				}
			});
		}
		else
		{
			Log.w(TAG ,"mHelper has null value ! Please initialiaze it!");
			mServiceBindingState = BindingError;
		}
	}
	
	public void startQuery()
	{
		mContext.runOnUiThread(new Runnable()
    	{
    		public void run()
    		{
				if (mCurrentQueryProcessState == NoProcess || mCurrentQueryProcessState == QueryError)
				{
					mCurrentQueryProcessState = Querying;
					mHelper.queryInventoryAsync(mGotInventoryListener);
				}
    		}
    	});
	}
	
	IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
        public void onQueryInventoryFinished(IabResult result, Inventory inventory) {
            Log.d(TAG, "Query inventory finished.");

            // Have we been disposed of in the meantime? If so, quit.
            if (mHelper == null) 
            {
            	mCurrentQueryProcessState = QueryError;
            	return;
            }

            // Is it a failure?
            if (result.isFailure()) {
                Log.w(TAG,"Failed to query inventory: " + result);
                mCurrentQueryProcessState = QueryError;
                return;
            }
            
            if (mCurrentQueryProcessState == Querying)
            {
            	Log.d(TAG, "Query inventory was successful.");
            	mCurrentQueryProcessState = QueryFinished;
            	mCurrentQueryInventory = inventory;
            	mCurrentQueryAllPurchases = inventory.getAllPurchases();
            
            	if (mCurrentQueryAllPurchases.size() == 0)
            		mCurrentQueryProcessState = NoProcess;
            }
            else
            {
            	Log.d(TAG, "Querying inventory for price was succesful.");
            	
            	mCurrentQueryPrices.clear();
            	
            	
            	for (int i = 0;i < mCurrentPriceQueryIds.size();i++)
            	{
            		String current_id = mCurrentPriceQueryIds.get(i);
            		String current_price = "";
            		if (inventory.getSkuDetails(current_id) != null)
            			current_price = inventory.getSkuDetails(current_id).getPrice();
            		Log.w(TAG,"id = "+current_id);
            		Log.w(TAG,"price = "+current_price);
            		if (current_price != null && current_price.length() > 0)
            			mCurrentQueryPrices.add(current_id + Separator + current_price);
            	}
            	
	    		mCurrentQueryProcessState = QueryPriceFinished;
            }
        }
    };
	
    public int getItemPrice(String id)
    {
    	
    	return 1;
    }
    
    public int getServiceBindingState()
    {
    	return mServiceBindingState;
    }
    
    public int getCurrentQueryProcessState()
    {
    	return mCurrentQueryProcessState;
    }
    
    
    public void consumeAllPurchases(String developerPayload)
    {
    	
    	mCurrentDeveloperPayload = developerPayload;
    	
    	mContext.runOnUiThread(new Runnable()
    	{
    		public void run()
    		{
		    	if (mCurrentQueryAllPurchases.size() > 0)
		    	{
		    		List <Purchase> currentUserPurchases = new ArrayList<Purchase>();
		    		
		    		for (int i = 0;i < mCurrentQueryAllPurchases.size(); i++)
		    			if (verifyDeveloperPayload(mCurrentQueryAllPurchases.get(i)))
		    				currentUserPurchases.add(mCurrentQueryAllPurchases.get(i));
		    	
		    		mCurrentQueryProcessState = QueryConsuming;
		    		mHelper.consumeAsync(currentUserPurchases, mOnConsumeMultiFinishedListener);
		    		
		    		mCurrentQueryAllPurchases.clear();
		    	}
    		}
    	});
    }
    
    public void consumePurchase(String purchase_id, String developerPayload)
    {
    	mCurrentDeveloperPayload = developerPayload;
    	if (verifyDeveloperPayload(mCurrentQueryInventory.getPurchase(purchase_id)))
    	{
    		mCurrentProcessState = Processing;
	    	mHelper.consumeAsync(mCurrentQueryInventory.getPurchase(purchase_id),mConsumeFinishedListener);
    	}
    	else
    	{
    		mCurrentProcessState = ConsumeError;
    	}
	}
    
    
    
    public int getCurrentProcessState()
    {
    	Log.w(TAG, "getmCurrentProcessState = "+ String.valueOf(mCurrentProcessState));
    	return mCurrentProcessState;
    }
    
    public int getCurrentProcessType()
    {
    	return mCurrentProcessType;
    }
    
    public boolean verifyDeveloperPayload(Purchase p) {
        String payload = p.getDeveloperPayload();
        Log.d(TAG, "current developer payload = " + mCurrentDeveloperPayload);
        Log.d(TAG, "purchase developer payload = " + payload);
        
        if (payload.equals(mCurrentDeveloperPayload))
        	return true;
        else
        	return false;
    }
    
    
    public void initPurchase(final String purchaseName, final boolean consumable)
    {
    	Log.w(TAG,"here");
    	final String payload = mCurrentDeveloperPayload;
    	mContext.runOnUiThread(new Runnable()
    	{
    		public void run()
    		{
		    	if (consumable == true)
		    	{
		    		Log.w(TAG,"got here");
		    		mHelper.launchPurchaseFlow(mContext,
		                    purchaseName, IabHelper.ITEM_TYPE_INAPP,
		                    RC_REQUEST, mPurchaseFinishedListener, payload);
		    	}
		    	else
			    	mHelper.launchPurchaseFlow(mContext,
			                purchaseName, IabHelper.ITEM_TYPE_SUBS,
			                RC_REQUEST, mPurchaseFinishedListener, payload);
    		}
    	});
    }
    
    IabHelper.OnConsumeMultiFinishedListener mOnConsumeMultiFinishedListener = new IabHelper.OnConsumeMultiFinishedListener() 
    {
		public void onConsumeMultiFinished(List<Purchase> purchases, List<IabResult> results) 
		{
			Log.w(TAG, "OnConsumeMultiFinishedListener");
			
			if (mHelper == null) 
			{
				mCurrentProcessState = ConsumeError;
				return;
			}
			
			
			mConsumedItemsId.clear();
		
			
			for (int i = 0; i < results.size() ; i++)
				if (results.get(i).isSuccess())
				{
					mConsumedItemsId.add(purchases.get(i).getSku());
				}
			mConsumedItemsIndex  = 0;
			mCurrentProcessState = Success;
		}
	};

	ArrayList<String> getConsumedItems()
	{
		ArrayList<String> res = new ArrayList(mConsumedItemsId);
		mCurrentQueryProcessState = QueryFinished;
		return res;
	}
	
	void startPriceQuery(final ArrayList<String> ids)
	{
		Log.w(TAG, "startPriceQuery " + String.valueOf(mCurrentQueryProcessState));
		if (mCurrentQueryProcessState != Querying && mCurrentQueryProcessState != QueryingPrice)
		{
			mCurrentPriceQueryIds = ids;
			mCurrentQueryProcessState = QueryingPrice;
			mContext.runOnUiThread(new Runnable()
			{
				public void run()
				{
					mHelper.queryInventoryAsync(true, mCurrentPriceQueryIds, mGotInventoryListener);
				}
			});
		}
	}	
	
	
	String getConsumedItem()
	{
		if (mConsumedItemsIndex >= mConsumedItemsId.size())
		{
			mConsumedItemsId.clear();
			mConsumedItemsIndex = 0;
			return "*";
		}
		else
			return mConsumedItemsId.get(mConsumedItemsIndex);
	}
	
    IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() 
    {
        public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
            Log.d(TAG, "Purchase finished: " + result + ", purchase: " + purchase);

            // if we were disposed of in the meantime, quit.
            if (mHelper == null) return;	

            if (result.isFailure()) {
            	if (result.getMessage().contains("User canceled"))
            	{
            		mCurrentProcessState = PurchaseCanceled;
            		Log.w(TAG, "Purchase canceled");
            	}
            	else
            	{
            		
            		mCurrentProcessState = PurchaseError;
            		Log.w(TAG ,"Purchases erorr : " + result);
            	}
            	return;
            }
            
            
            if (!verifyDeveloperPayload(purchase)) {
            	mCurrentProcessState = ConsumeError;
                Log.d(TAG, "Error consuming. Authenticity verification failed.");
                return;
            }

            Log.d(TAG, "Purchase successful.");
            
            if (mCurrentProcessType == PurchaseType)
            {
            	Log.d(TAG, "Starting consume.");
            	mHelper.consumeAsync(purchase, mConsumeFinishedListener);
            }
            else
            {
            	mCurrentProcessState = Success;
            }  
        }
    };
    
    
    
    
    IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
        public void onConsumeFinished(Purchase purchase, IabResult result) {
            Log.d(TAG, "Consumption finished. Purchase: " + purchase + ", result: " + result);

            // if we were disposed of in the meantime, quit.
            if (mHelper == null)
            {
            	mCurrentProcessState = ConsumeError;
            	return;
            }

            if (result.isSuccess())
            {
            	mCurrentProcessState = Success;
                Log.d(TAG, "Consumption successful.");
            }
            else 
            {
            	mCurrentProcessState = ConsumeError;
                Log.d(TAG, "Error while consuming: " + result);
            }
            Log.d(TAG, "End consumption flow.");
        }
    };


    
	public void destroy()
	{
		if (mHelper != null) mHelper.dispose();
		mHelper = null;
	}


}
