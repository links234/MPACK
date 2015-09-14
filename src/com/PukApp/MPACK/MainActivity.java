package com.PukApp.MPACK;

import java.io.UnsupportedEncodingException;
import java.security.GeneralSecurityException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;

import javax.crypto.BadPaddingException;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

public class MainActivity extends NativeActivity

{

	MainActivity _activity;
	GoogleAds mGoogleAds;
	//EasyShare mEasyShare;
	//RateMe mRateMe;
	//InAppPurchases mInAppPurchases;
	
	
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		_activity = this;
		
		System.loadLibrary("MPACK");
	}
	
	public void sendInAppPurchasesJavaVmToCpp()
	{
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				//mInAppPurchases = new InAppPurchases(_activity);
				//mInAppPurchases.sendInAppPurchasesToCpp();
			}
		});
	}
	
	public void sendGoogleAdsJavaVmToCpp()
	{
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				mGoogleAds = new GoogleAds(_activity);
				mGoogleAds.sendGoogleAdsToCpp();
			}
		});
	}
	
	public void sendEasyShareJavaVmToCpp()
	{
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				//mEasyShare = new EasyShare(_activity);
				//mEasyShare.sendEasyShareToCpp();
			}
		});
		
	}
	
	public void sendRateMeJavaVmToCpp(final String p1,final String p2,final int p3,final int p4)
	{
		this.runOnUiThread(new Runnable()
		{
			public void run()
			{
				//mRateMe = new RateMe(_activity,p1,p2,p3,p4);
				//mRateMe.sendRateMeToCpp();
			}
		});
		
	}
	
	@Override
	
	public void onDestroy() 
	{
		super.onDestroy();
	}

}
