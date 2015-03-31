package com.mpack.Framework;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.WindowManager;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.widget.LinearLayout;
import android.widget.PopupWindow;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;


class GoogleAds
{
	MainActivity mContext;
	
	LinearLayout layout;
	LinearLayout mainLayout;
	
	AdView mBanner,mLargeBanner, mSmartBanner;
	InterstitialAd mTIInterstitial , mTIVInterstitial , mVInterstitial ;
	AdRequest mAdRequest;
	PopupWindow mPopUpBanner , mPopUpLargeBanner, mPopUpSmartBanner;
	boolean mShowBanner = false, mShowLargeBanner = false, mShowSmartBanner = false;
	boolean mIsLoadedBanner = false, mIsLoadedLargeBanner = false, mIsLoadedSmartBanner = false;
	boolean mIsShowedBanner = false, mIsShowedLargeBanner = false, mIsShowedSmartBanner = false;
	
	AdListener mBannerListener;
	

	public GoogleAds(MainActivity mainActivity) 
	{
		System.loadLibrary("Framework");
		mContext = mainActivity;
		GoogleAdsInit();
	}


	
	 public native void nativeGoogleAds();
	 
	 public void sendGoogleAdsToCpp() 
	 {
	    nativeGoogleAds();
	 }
	
	 public void GoogleAdsInit()
	 {
		 mShowBanner = mShowLargeBanner = mShowSmartBanner = false;
		 mIsLoadedBanner = mIsLoadedLargeBanner = mIsLoadedSmartBanner = false;
		 
		 mBanner = new AdView(mContext);
		 mBanner.setAdUnitId(mContext.getResources().getString(R.string.StandardBanner));
		 mBanner.setAdSize(com.google.android.gms.ads.AdSize.BANNER);
		 
		 mLargeBanner = new AdView(mContext);
		 mLargeBanner.setAdUnitId(mContext.getResources().getString(R.string.StandardBanner));
		 mLargeBanner.setAdSize(com.google.android.gms.ads.AdSize.LARGE_BANNER);
		
		 mSmartBanner = new AdView(mContext);
		 mSmartBanner.setAdUnitId(mContext.getResources().getString(R.string.StandardBanner));
		 mSmartBanner.setAdSize(com.google.android.gms.ads.AdSize.SMART_BANNER);
			
		 mTIInterstitial = new InterstitialAd(mContext);
		 mTIInterstitial.setAdUnitId(mContext.getResources().getString(R.string.TIInterstitial));
		
		 mTIVInterstitial = new InterstitialAd(mContext);
		 mTIVInterstitial.setAdUnitId(mContext.getResources().getString(R.string.TIVInterstitial));
	
		 mVInterstitial = new InterstitialAd(mContext);
		 mVInterstitial.setAdUnitId(mContext.getResources().getString(R.string.VInterstitial));
	 
		 mAdRequest = new AdRequest.Builder().build();
		 
		 mBanner.loadAd(mAdRequest);
		 mLargeBanner.loadAd(mAdRequest);
		 mSmartBanner.loadAd(mAdRequest);
		 
		 mTIInterstitial.loadAd(mAdRequest);
		 mTIVInterstitial.loadAd(mAdRequest);
		 mVInterstitial.loadAd(mAdRequest);
		 
		 mPopUpBanner = new PopupWindow(mContext);
		 mPopUpBanner.setWidth(320);
		 mPopUpBanner.setHeight(50);
		 mPopUpBanner.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		 mPopUpBanner.setClippingEnabled(false);
		 
		 mPopUpLargeBanner = new PopupWindow(mContext);
		 mPopUpLargeBanner.setWidth(320);
		 mPopUpLargeBanner.setHeight(50);
		 mPopUpLargeBanner.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		 mPopUpLargeBanner.setClippingEnabled(false);
		 
		 mPopUpSmartBanner = new PopupWindow(mContext);
		 mPopUpSmartBanner.setWidth(320);
		 mPopUpSmartBanner.setHeight(50);
		 mPopUpSmartBanner.setWindowLayoutMode(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		 mPopUpSmartBanner.setClippingEnabled(false);
		 
		 mTIVInterstitial.setAdListener(new AdListener()
		 {
			 public void onAdClosed()
			 {
				 mTIVInterstitial.loadAd(mAdRequest);
			 }
		 } );
		 
		 mTIInterstitial.setAdListener(new AdListener()
		 {
			 public void onAdClosed()
			 {
				 mTIInterstitial.loadAd(mAdRequest);
			 }
		 } );
		 
		 mVInterstitial.setAdListener(new AdListener()
		 {
			 public void onAdClosed()
			 {
				 mVInterstitial.loadAd(mAdRequest);
			 }
		 } );
		 
		 mBanner.setAdListener(new AdListener()
		 {
			 public void onAdLoaded()
			 {
				mIsLoadedBanner = true;
				if (mShowBanner)
					showBanner();
			 }
			 public void onAdClosed()
			 {
				 mIsLoadedBanner = false;
				 if (mIsShowedBanner == true)
				 {
					 hideBanner();
				 }
				 mBanner.loadAd(mAdRequest);
			 }
		 });
		 
		 mLargeBanner.setAdListener(new AdListener()
		 {
			 public void onAdLoaded()
			 {
				mIsLoadedLargeBanner = true;
				if (mShowLargeBanner)
					showLargeBanner();
			 }
			 public void onAdClosed()
			 {
				 mIsLoadedLargeBanner = false;
				 if (mIsShowedLargeBanner)
				 {
					 hideLargeBanner();
				 }
				 mLargeBanner.loadAd(mAdRequest);
			 }
		 });
		 
		 mSmartBanner.setAdListener(new AdListener()
		 {
			 public void onAdLoaded()
			 {
				mIsLoadedSmartBanner = true;
				if (mShowSmartBanner)
					showSmartBanner();
			 }
			 public void onAdClosed()
			 {
				 mIsLoadedSmartBanner = false;
				 if (mIsShowedSmartBanner)
				 {
					 hideSmartBanner();
				 }
				 mSmartBanner.loadAd(mAdRequest);
			 }
		 });
	 }
	
	 public void showTextImageInterstitial()
	 {
		 mContext.runOnUiThread(new Runnable()
		 {
			 public void run()
			 {
				 if (mTIInterstitial.isLoaded())
					 mTIInterstitial.show(); 
				 else
					 Log.w("ads","TIInterstitial not loaded");
			 }
		 });
	}
	 
	 public void showTextImageVideoInterstitial()
	 {
		 mContext.runOnUiThread(new Runnable()
		 {
			 public void run()
			 {
				 if (mTIVInterstitial.isLoaded())
					 mTIVInterstitial.show(); 
				 else
					 Log.w("ads","TIVInterstitial not loaded");
			 }
		 });
	}
	 
	 public void showVideoInterstitial()
	 {
		 mContext.runOnUiThread(new Runnable()
		 {
			 public void run()
			 {
				 if (mVInterstitial.isLoaded())
					 mVInterstitial.show(); 
				 else
					 Log.w("ads","VInterstitial not loaded");
			 }
		 });
	}
	 
	 
	 
	 public void showBanner()
	 {
		mShowBanner = true;
		if (mIsShowedBanner == true) return;
		
		if (mIsLoadedBanner == true)
		{
			mIsShowedBanner = true;		
			showAdPopup(mPopUpBanner,mBanner);
		}
	 }
	 
	 public void showLargeBanner()
	 {
		mShowLargeBanner = true;
		if (mIsShowedLargeBanner == true) return;
		
		if (mIsLoadedLargeBanner == true)
		{
			mIsShowedLargeBanner = true;
			showAdPopup(mPopUpLargeBanner,mLargeBanner);
		}
	 }
	 
	 public void showSmartBanner()
	 {
		 Log.w("ads","ShowSmartBanner!!!!!!!!!!1");
		 
		mShowSmartBanner = true;
		if (mIsShowedSmartBanner == true) return;
		
		if (mIsLoadedSmartBanner == true)
		{
			mIsShowedSmartBanner = true;
			showAdPopup(mPopUpSmartBanner,mSmartBanner);
		}
	 }
	 
	 public void hideBanner()
	 {
		 mShowBanner = false;
		 if (mIsShowedBanner == false) return;
		 
		 mIsShowedBanner = false;
		 mContext.runOnUiThread(new Runnable()  
		 {
			 public void run()
			 {
				 mPopUpBanner.dismiss();
				((LinearLayout) mBanner.getParent()).removeView(mBanner);
			 }
		 });	
	}
	 
	 public void hideLargeBanner()
	 {
		 mShowLargeBanner = false;
		 if (mIsShowedLargeBanner == false) return;
		 
		 mIsShowedLargeBanner = false;
		 mContext.runOnUiThread(new Runnable()  
		 {
			 public void run()
			 {
				 mPopUpLargeBanner.dismiss();
				((LinearLayout) mLargeBanner.getParent()).removeView(mLargeBanner);
			 }
		 });	
	}
	 
	 public void hideSmartBanner()
	 {
		 Log.w("ads","hideSmartBanner !!!!!!!!!!!!");
		 
		 mShowSmartBanner = false;
		 if (mIsShowedSmartBanner == false) return;
		 
		 mIsShowedSmartBanner = false;
		 mContext.runOnUiThread(new Runnable()  
		 {
			 public void run()
			 {
				 mPopUpSmartBanner.dismiss();
				((LinearLayout) mSmartBanner.getParent()).removeView(mSmartBanner);
			 }
		 });	
	}
	 
	 public void showAdPopup(final PopupWindow popUp, final AdView adView)
	 {
		 mContext.runOnUiThread(new Runnable()  
			{
			
				public void run()  
				{	
					layout = new LinearLayout(mContext);
					mainLayout = new LinearLayout(mContext);
					layout.setPadding(-10, 0, -10, 0);
					//layout.setPadding(0, 0, 0, 0);
					MarginLayoutParams params = new MarginLayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					params.setMargins(0, 0, 0, 0);
					layout.setOrientation(LinearLayout.VERTICAL);
					layout.addView(adView, params);
					popUp.setContentView(layout);
					mContext.setContentView(mainLayout, params);
					popUp.showAtLocation(mainLayout, Gravity.BOTTOM, 0, 0);
					popUp.update();
				}
			});	
	 }
	
}