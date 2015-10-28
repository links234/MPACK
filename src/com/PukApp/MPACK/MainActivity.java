package com.PukApp.MPACK;

import java.util.concurrent.CountDownLatch;

import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.api.GoogleApiClient.ConnectionCallbacks;
import com.google.android.gms.common.api.GoogleApiClient.OnConnectionFailedListener;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.WindowManager;

public class MainActivity extends NativeActivity implements ConnectionCallbacks, OnConnectionFailedListener

{
	private static final int REQUEST_RESOLVE_ERROR = 1001;
	
	
	MainActivity _activity;
	GoogleAds mGoogleAds;
	EasyShare mEasyShare;
	RateMe mRateMe;
	InAppPurchases mInAppPurchases;
	String TAG = "MainActivity";
	
	
	static 
	{
		System.loadLibrary("MPACK");
	}
	
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		_activity = this;
		
	
		nativeOnActivityCreated(this, savedInstanceState);
	}
	
	
	public void sendInAppPurchasesJavaVmToCpp()
	{
		final CountDownLatch latch = new CountDownLatch(1);
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				mInAppPurchases = new InAppPurchases(_activity);
				mInAppPurchases.sendInAppPurchasesToCpp();
				latch.countDown();
			}
		});
		try {
		    latch.await();
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
		
	}
	
	public void sendGoogleAdsJavaVmToCpp()
	{
		final CountDownLatch latch = new CountDownLatch(1);
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				mGoogleAds = new GoogleAds(_activity);
				mGoogleAds.sendGoogleAdsToCpp();
				latch.countDown();
			}
		});
		try {
		    latch.await();
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
	}
	
	public void sendEasyShareJavaVmToCpp()
	{
		final CountDownLatch latch = new CountDownLatch(1);
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				mEasyShare = new EasyShare(_activity);
				mEasyShare.sendEasyShareToCpp();
				latch.countDown();
			}
		});
		try {
		    latch.await();
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
		
	}
	
	public void sendRateMeJavaVmToCpp(final String p1,final int p2,final int p3)
	{
		final CountDownLatch latch = new CountDownLatch(1);
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				mRateMe = new RateMe(_activity,p1,p2,p3);
				mRateMe.sendRateMeToCpp();
				latch.countDown();
			}
		});
		try {
		    latch.await();
		} catch (InterruptedException e) {
		    e.printStackTrace();
		}
		
	}
	
	 @Override
	 protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		 Log.d(TAG, "onActivityResult");
		 
	     // Pass on the activity result to the helper for handling
		 if (InAppPurchases.mHelper == null || !InAppPurchases.mHelper.handleActivityResult(requestCode, resultCode, data))
		 {
	         super.onActivityResult(requestCode, resultCode, data);
	     }
	     else {
	         Log.d(TAG, "onActivityResult handled by IABUtil." + String.valueOf(resultCode)	);
	     }
		 
		 nativeOnActivityResult(this, requestCode, resultCode, data);
	 }
	 
	 protected void onResume()
	 {
		 super.onResume();
		 nativeOnActivityResumed(this);
	 }
	 
	 protected void onPause() 
	 {
		 super.onPause();

		nativeOnActivityPaused(this);
	}
	 
	

    protected void onStart() 
    {
        super.onStart();
        nativeOnActivityStarted(this);
    }

    protected void onStop() 
    {
        super.onStop();
        nativeOnActivityStopped(this);
    }
    
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        nativeOnActivitySaveInstanceState(this, outState);
    }
	
	@Override
	public void onDestroy() 
	{
		super.onDestroy();
		nativeOnActivityDestroyed(this);
	}

	@Override
	public void onConnected(Bundle arg0) {
		// TODO Auto-generated method stub
		Log.w(TAG,"onConnected");
	}

	@Override
	public void onConnectionSuspended(int arg0) {
		// TODO Auto-generated method stub
		Log.w(TAG,"onConnectionSuspended");
	}

	@Override
	public void onConnectionFailed(ConnectionResult arg0) {
		// TODO Auto-generated method stub
		Log.w(TAG,"onConnectionFailed "+arg0.toString());
	}

	public static native void nativeOnActivityResult(Activity activity,
            int requestCode, int resultCode, Intent data);

    public static native void nativeOnActivityCreated(Activity activity,
            Bundle savedInstanceState);

    private static native void nativeOnActivityDestroyed(Activity activity);

    private static native void nativeOnActivityPaused(Activity activity);

    private static native void nativeOnActivityResumed(Activity activity);

    private static native void nativeOnActivitySaveInstanceState(
            Activity activity, Bundle outState);

    private static native void nativeOnActivityStarted(Activity activity);

    private static native void nativeOnActivityStopped(Activity activity);
	
}
