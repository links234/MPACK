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
	GoogleAds mGoogleAds;
	
	
	
	public void onCreate(Bundle savedInstanceState) 
	{
	
		super.onCreate(savedInstanceState);
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		_activity = this;
		
		
	    mGoogleAds = new GoogleAds(this);
	
	}
	
	
	public void sendGoogleAdsJavaVmToCpp()
	{
		mGoogleAds.sendGoogleAdsToCpp();
	}
	
	 
	// Do some cleanup
	
	  @Override
	
	  public void onDestroy() {
	
	    super.onDestroy();
	
	  }

}
