package com.PukApp.MPACK;

import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Point;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.util.Log;
import android.util.TypedValue;
import android.view.Display;
import android.view.Gravity;
import android.view.View;
import android.view.View.MeasureSpec;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewGroup.MarginLayoutParams;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

public class RateMe {
	final static int Ok = 1;
	final static int NeverOptionTriggered = 2;
	final static int AlreadyRated = 3;
	final static int TimeOrLaunchesProblem = 4;
	
	
    private static String mAppTitle = "App Name";// App Name
    private static String mAppPName = "com.example.name";// Package Name
    private static String mUrl = "";

    private static int mDaysUntilPrompt = 2;//Min number of days
    private static int mLaunchesUntilPrompt = 5;//Min number of launches
    private static MainActivity mContext;
    private static long mInfinity = 1000000000;
    
    private static float mScaledDensityFactor ;
    
    
	public RateMe(MainActivity Context,String url, int daysUntilPrompt, int launchesUntilPrompt)
    {
    	mContext = Context;
    	
    	mUrl = url;
    	
    	mDaysUntilPrompt = daysUntilPrompt;
    	mLaunchesUntilPrompt = launchesUntilPrompt;
    	
    	mScaledDensityFactor = mContext.getResources().getDisplayMetrics().scaledDensity;
    }
   

    public int check()
    {
		SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
		
		long launch_count = prefs.getLong("launch_count", 0) + 1;
		Long date_firstLaunch = prefs.getLong("date_firstlaunch", 0);
	    boolean never_rate = prefs.getBoolean("never_rate",false); 
	    boolean already_rated = prefs.getBoolean("already_rated",false);
	    
	    if (!never_rate)
	    {
	    	if (!already_rated)
	    	{
			   	if (launch_count >= mLaunchesUntilPrompt) 
			   	{
			        if (System.currentTimeMillis() >= date_firstLaunch + (mDaysUntilPrompt * 24 * 60 * 60 * 1000)) 
			        {
		           	 	SharedPreferences.Editor editor = prefs.edit();
		           	 	editor.putLong("date_firstlaunch",System.currentTimeMillis());
		           	 	editor.commit(); 
		           	 	
		           	 	return Ok;
			        }
			        else
			        	return TimeOrLaunchesProblem;
			    }
			   	else 
			   		return TimeOrLaunchesProblem;
	    	}
	    	else
	    		return AlreadyRated;
	    }
	    else
	    	return NeverOptionTriggered;
    }
    
    public void update()
    {		
		SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
		SharedPreferences.Editor editor = prefs.edit();
   	 	editor.putLong("date_firstlaunch",System.currentTimeMillis());
   	 	editor.commit(); 
    }
   
    public void rate()
    {
    	SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
		SharedPreferences.Editor editor = prefs.edit();
   	 	editor.putBoolean("already_rated",true);
   	 	editor.commit(); 
    	mContext.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse(mUrl)));
    }
    
    public void rateLater()
    {
    	
    }
    
    public void rateNever()
    {
    	SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
    	SharedPreferences.Editor  editor = prefs.edit();
    	editor.putBoolean("never_rate", true);
    	editor.commit();
    }
    
    public void reset()
    {
    	SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
    	SharedPreferences.Editor  editor = prefs.edit();
    	editor.putBoolean("never_rate", false);
    	editor.putBoolean("already_rated", false);
    	editor.putLong("launch_count", 0);
    	editor.commit();
    }
    
    public native void nativeRateMe();
   
    public void sendRateMeToCpp()
    {
    	
    	SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
        SharedPreferences.Editor editor = prefs.edit();
        
        // Increment launch counter
        long launch_count = prefs.getLong("launch_count", 0) + 1;
        Log.w("RateMe2","launch_count "+ String.valueOf(launch_count));
        if (launch_count > mInfinity) launch_count = mInfinity;
        editor.putLong("launch_count", launch_count);

        // Get date of first launch
        Long date_firstLaunch = prefs.getLong("date_firstlaunch", 0);
        Log.w("RateMe2","date_firstlaunch "+String.valueOf(date_firstLaunch));
        if (date_firstLaunch == 0) {
            date_firstLaunch = System.currentTimeMillis();
            editor.putLong("date_firstlaunch", date_firstLaunch);
        }
        
        editor.commit();
    	
    	nativeRateMe(); 
    }
    
    
}