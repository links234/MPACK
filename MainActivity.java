package com.mpack.Framework;

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
	
	
	public void onCreate(Bundle savedInstanceState) 
	{
	
		super.onCreate(savedInstanceState);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		_activity = this;
			
	    GoogleAdsInit();
	
	}
	
	 public void GoogleAdsInit()
	 {
		 mShowBanner = mShowLargeBanner = mShowSmartBanner = false;
		 mIsLoadedBanner = mIsLoadedLargeBanner = mIsLoadedSmartBanner = false;
		 
		 mBanner = new AdView(this);
		 mBanner.setAdUnitId(getResources().getString(R.string.StandardBanner));
		 mBanner.setAdSize(com.google.android.gms.ads.AdSize.BANNER);
		 
		 mLargeBanner = new AdView(this);
		 mLargeBanner.setAdUnitId(getResources().getString(R.string.StandardBanner));
		 mLargeBanner.setAdSize(com.google.android.gms.ads.AdSize.LARGE_BANNER);
		
		 mSmartBanner = new AdView(this);
		 mSmartBanner.setAdUnitId(getResources().getString(R.string.StandardBanner));
		 mSmartBanner.setAdSize(com.google.android.gms.ads.AdSize.SMART_BANNER);
			
		 mTIInterstitial = new InterstitialAd(this);
		 mTIInterstitial.setAdUnitId(getResources().getString(R.string.TIInterstitial));
		
		 mTIVInterstitial = new InterstitialAd(this);
		 mTIVInterstitial.setAdUnitId(getResources().getString(R.string.TIVInterstitial));
	
		 mVInterstitial = new InterstitialAd(this);
		 mVInterstitial.setAdUnitId(getResources().getString(R.string.VInterstitial));
	 
		 mAdRequest = new AdRequest.Builder().build();
		 
		 mBanner.loadAd(mAdRequest);
		 mLargeBanner.loadAd(mAdRequest);
		 mSmartBanner.loadAd(mAdRequest);
		 
		 mTIInterstitial.loadAd(mAdRequest);
		 mTIVInterstitial.loadAd(mAdRequest);
		 mVInterstitial.loadAd(mAdRequest);
		 
		 mPopUpBanner = new PopupWindow(_activity);
		 mPopUpBanner.setWidth(320);
		 mPopUpBanner.setHeight(50);
		 mPopUpBanner.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		 mPopUpBanner.setClippingEnabled(false);
		 
		 mPopUpLargeBanner = new PopupWindow(_activity);
		 mPopUpLargeBanner.setWidth(320);
		 mPopUpLargeBanner.setHeight(50);
		 mPopUpLargeBanner.setWindowLayoutMode(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
		 mPopUpLargeBanner.setClippingEnabled(false);
		 
		 mPopUpSmartBanner = new PopupWindow(_activity);
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
		 _activity.runOnUiThread(new Runnable()
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
		 _activity.runOnUiThread(new Runnable()
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
		 _activity.runOnUiThread(new Runnable()
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
		 _activity.runOnUiThread(new Runnable()  
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
		 _activity.runOnUiThread(new Runnable()  
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
		 mShowSmartBanner = false;
		 if (mIsShowedSmartBanner == false) return;
		 
		 mIsShowedSmartBanner = false;
		 _activity.runOnUiThread(new Runnable()  
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
		 _activity.runOnUiThread(new Runnable()  
			{
			
				public void run()  
				{	
					layout = new LinearLayout(_activity);
					mainLayout = new LinearLayout(_activity);
					layout.setPadding(-10, -10, -10, -10);
					//layout.setPadding(0, 0, 0, 0);
					MarginLayoutParams params = new MarginLayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					params.setMargins(0, 0, 0, 0);
					layout.setOrientation(LinearLayout.VERTICAL);
					layout.addView(adView, params);
					popUp.setContentView(layout);
					_activity.setContentView(mainLayout, params);
					popUp.showAtLocation(mainLayout, Gravity.BOTTOM, 0, 0);
					popUp.update();
				}
			});	
	 }
	
	
	 
	// Do some cleanup
	
	  @Override
	
	  public void onDestroy() {
	
	    super.onDestroy();
	
	  }

}
