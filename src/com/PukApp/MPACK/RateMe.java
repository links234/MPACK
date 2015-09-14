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
	final static int Default = 0;
	final static int DialogOn = 1;
	final static int AnswerYes = 2;
	final static int AnswerRemindMeLater = 3;
	final static int AnswerNeverRate = 4;
	
	
	private static int mState = 0;
	
    private static String mAppTitle = "App Name";// App Name
    private static String mAppPName = "com.example.name";// Package Name

    private static int mDaysUntilPrompt = 2;//Min number of days
    private static int mLaunchesUntilPrompt = 5;//Min number of launches
    private static MainActivity mContext;
    private static long mInfinity = 1000000000;
    
    private static float mScaledDensityFactor ;
    
    
    
    
	public RateMe(MainActivity Context,String appTitle, String appPname, int daysUntilPrompt, int launchesUntilPrompt)
    {
    	mContext = Context;
    	
    	mAppTitle = appTitle;
    	mAppPName = appPname;
    	
    	mDaysUntilPrompt = daysUntilPrompt;
    	mLaunchesUntilPrompt = launchesUntilPrompt;
    	
    	mScaledDensityFactor = mContext.getResources().getDisplayMetrics().scaledDensity;
    	mState = 0;
    	
    	AutoFitText.initiliazeClass(mContext,mScaledDensityFactor);
    }
   
	
	
	private static void Rate(final String text ,final boolean never, final boolean verticalOrientation)
    {
		
		mContext.runOnUiThread(new Runnable()  
		{
        	
			public void run()  
			{	
				WindowManager wm = (WindowManager) mContext.getSystemService(Context.WINDOW_SERVICE);
				Display display = wm.getDefaultDisplay();
				@SuppressWarnings("deprecation")
				int width = display.getWidth();
				Log.w("RateMe","Width = "+String.valueOf(width));
				@SuppressWarnings("deprecation")
				int height = display.getHeight();
				Log.w("RateMe","height = "+String.valueOf(height));
				
				Log.w("RateMe","ScaledDensityFactor = "+String.valueOf(mScaledDensityFactor));
				
			
				int buttonWidth = 0,buttonHeight = 0;
				int textViewWidth = 0,textViewHeight = 0;
				int space = 0;
				int padding =(int) ( (float)mScaledDensityFactor/(float)0.75 * 2);
				float error = 0;
				Log.w("RateMe","Error = "+String.valueOf(error));
				float minSize = 500;
				LinearLayout.LayoutParams params = null,params1 = null,params2 = null,params3 = null,paramsTv = null;
				
				if (verticalOrientation == false)
				{
					if (never == true)
					{
						
						buttonWidth =  11*width/80;
						buttonHeight = 9*height/100;
						
						textViewWidth = width/2;
						textViewHeight = 18*height/ 100;
						
						space = (textViewWidth - 3*buttonWidth)/8;
						//error = (float)3 * (float)width/800 *  ((float)1.5 - mScaledDensityFactor)!=0?(6*( Math.abs((float)1.5 - mScaledDensityFactor))):(float)0;
					}	
					else
					{
						
						buttonWidth =  16*width/80  ;
						buttonHeight = 11*height/100;
						
						textViewWidth = width/2;
						textViewHeight = 18*height/ 100;
						
						space = (textViewWidth - 2*buttonWidth)/4;
						//error = (float)3 * (float)width/800 *  ((float)1.5 - mScaledDensityFactor)!=0?(6*(Math.abs( (float)1.5 - mScaledDensityFactor))):(float)0;
					}
					paramsTv = new LinearLayout.LayoutParams(textViewWidth, textViewHeight);
					
					params = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					params.setMargins(0, 0, 0, 0);
					
					params1 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params1.gravity = Gravity.CENTER;
					params1.setMargins(space, space/2, space, space/2);
					
					
					
					params2 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params2.gravity = Gravity.CENTER;
					if (never)
						params2.setMargins(2*space, space/2 ,2*space, space/2);
					else
						params2.setMargins(space, space/2 ,space, space/2);
					
					params3 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params3.gravity = Gravity.CENTER;
					params3.setMargins(space, space/2, space, space/2);
				}
				else
				{
					
					buttonWidth =  width/3;
					buttonHeight = 5*height/100;
					
					textViewWidth = width/2;
					textViewHeight = 20*height/ 100;
					
					space =width/100;
					//error = 3 * (float)width/480 *  ((float)1.5 - mScaledDensityFactor)!=0?(6*( Math.abs((float)1.5 - mScaledDensityFactor))):(float)1.2;
					
					params = new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);
					params.setMargins(0, 0, 0, 0);
					
					paramsTv = new LinearLayout.LayoutParams(textViewWidth, textViewHeight);
					
					params1 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params1.gravity = Gravity.CENTER;
					params1.setMargins(0, 0, 0, space);
					
					
					params2 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params2.gravity = Gravity.CENTER;
					params2.setMargins(0, space ,0, space);
					
					params3 = new LinearLayout.LayoutParams(buttonWidth,buttonHeight);
					params3.gravity = Gravity.CENTER;
					params3.setMargins(0, space, 0, space);
				}

				
				
				
				LinearLayout layout = new LinearLayout(mContext);
				
				layout.setOrientation(LinearLayout.VERTICAL);
				layout.setPadding(0, 0, 0, 0);
				
				LinearLayout layout2 = new LinearLayout(mContext);
				layout2.setOrientation(LinearLayout.HORIZONTAL);
				layout2.setPadding(0, 0, 0, 0);
				layout2.setLayoutParams(params);
				
				
				final Dialog dialog = new Dialog(mContext);
				dialog.setCanceledOnTouchOutside(false);
		        dialog.setTitle("Rate " + mAppTitle);

		        TextView tv = new TextView(mContext);
		        tv.setText(text);
		        tv.setLayoutParams(paramsTv);
		        tv.setWidth(textViewWidth);
		        tv.setHeight(textViewHeight);
		        tv.setPadding(10, 0, 0, 10);
		        
		      
		        AutoFitText.setAutoFitText(tv.getText().toString());
		        AutoFitText.setSizeLimit(textViewWidth, textViewHeight,10,0,0,10);
		        tv.setTextSize(TypedValue.COMPLEX_UNIT_SP, (float)AutoFitText.getResultSize() / mScaledDensityFactor);
		        
		      
		        
		        Button b1 = new Button(mContext,null,android.R.attr.buttonStyleSmall);
		        b1.setGravity(Gravity.CENTER);
		        b1.setLayoutParams(params1);
		        b1.setPadding(padding,padding,padding,padding);
		        b1.setText("Rate it");
		        
		        AutoFitText.setSizeLimit(buttonWidth, buttonHeight, padding,padding,padding,padding);
		        AutoFitText.setAutoFitText(b1.getText().toString());
		        minSize = Math.min((float)AutoFitText.getResultSize(), minSize);
		      
		        
		        b1.setOnClickListener(new OnClickListener() {
		            public void onClick(View v) {
		                mContext.startActivity(new Intent(Intent.ACTION_VIEW, Uri.parse("http://33.media.tumblr.com/290a6aeb012fb450600d2fed890c07e5/tumblr_ni7qf8lxIC1u3d5tbo1_500.gif")));
		                //Uri.parse("market://details?id=" + mAppTitle)
		                mState = AnswerYes;
		                dialog.dismiss();
		            }
		        });        
		     
		        
		        Button b2 = new Button(mContext,null,android.R.attr.buttonStyleSmall);
	        	b2.setGravity(Gravity.CENTER);
	        	b2.setLayoutParams(params2);
	        	b2.setText("Remind me later");
	        	b2.setPadding(padding,padding,padding,padding);
	        
	        	
	        	AutoFitText.setSizeLimit(buttonWidth, buttonHeight,padding,padding,padding,padding);
	        	AutoFitText.setAutoFitText(b2.getText().toString());
	        	minSize = Math.min((float)AutoFitText.getResultSize(), minSize);
		        
		        
		        b2.setOnClickListener(new OnClickListener() {
		            public void onClick(View v) {
		            	reteMeLater();
		                dialog.dismiss();
		            }
		        });
		       
		        
		        
		       
		        Button b3 = new Button(mContext,null,android.R.attr.buttonStyleSmall);
		        if (never)
		        {
			        b3.setGravity(Gravity.CENTER);
			        b3.setLayoutParams(params3);
			        b3.setText("Don't ask again");
			        b3.setPadding(padding,padding,padding,padding);
			        
			      
			        AutoFitText.setSizeLimit(buttonWidth, buttonHeight, padding,padding,padding,padding);
			        AutoFitText.setAutoFitText(b3.getText().toString());
			        minSize = Math.min((float)AutoFitText.getResultSize(), minSize);
			        
			        b3.setOnClickListener(new OnClickListener() {
			            public void onClick(View v) {
			            	neverRateMe();
			                dialog.dismiss();
			            }
			        });
		        }
		   
		        b1.setTextSize(TypedValue.COMPLEX_UNIT_SP, (minSize - error) / mScaledDensityFactor);
		        b2.setTextSize(TypedValue.COMPLEX_UNIT_SP, (minSize - error) / mScaledDensityFactor);
		        if (never) b3.setTextSize(TypedValue.COMPLEX_UNIT_SP, (minSize - error) / mScaledDensityFactor);
		        
		        
		        layout.addView(tv);
		        if (verticalOrientation)
		        {
		        	layout.addView(b1);
		        	layout.addView(b2);
		        	if (never) layout.addView(b3);
		        }
		        else
		        {
		        	layout2.addView(b1);
		        	layout2.addView(b2);
		        	if (never) layout2.addView(b3);
		        	layout.addView(layout2);
		        }
		        
		        dialog.setContentView(layout);  
				dialog.show();
			}
		});	
    }
	

    public void automaticRateMe(String text, boolean never, boolean verticalOrientation)
    {
        mState = Default;
    	
		SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
		
		long launch_count = prefs.getLong("launch_count", 0) + 1;
		Long date_firstLaunch = prefs.getLong("date_firstlaunch", 0);
	    boolean never_rate = prefs.getBoolean("never_rate",false); 
	    
	    if (!never_rate)
	    {
		   	if (launch_count >= mLaunchesUntilPrompt) 
		   	{
		        if (System.currentTimeMillis() >= date_firstLaunch + (mDaysUntilPrompt * 24 * 60 * 60 * 1000)) 
		        {
		        	mState = DialogOn;
	           	 	SharedPreferences.Editor editor = prefs.edit();
	           	 	editor.putLong("date_firstlaunch",System.currentTimeMillis());
	           	 	editor.commit(); 
	           	 	
	           	 	Rate(text,never,verticalOrientation);
		        }
		    }
	    }
    	        
    }
   
    public void rateMeNow(String text, boolean never,boolean verticalOrientation)
    {	
    	 mState = Default;
    	
    	 SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
    	 boolean never_rate = prefs.getBoolean("never_rate", false);
    	 
    	 if (!never_rate) 
    	 {
    		 mState = DialogOn;
    		 SharedPreferences.Editor editor = prefs.edit();
    		 editor.putLong("date_firstlaunch",System.currentTimeMillis());
    		 editor.commit(); 
    		 Rate(text,never,verticalOrientation);
    	 }
    }
    
    public static void reteMeLater()
    {
    	mState = AnswerRemindMeLater;
    }
    
    public static void neverRateMe()
    {
    	mState = AnswerNeverRate;
    	SharedPreferences prefs = mContext.getSharedPreferences("RateMe", 0);
    	SharedPreferences.Editor  editor = prefs.edit();
    	editor.putBoolean("never_rate", true);
    	editor.commit();
    }
    
    public static int getRateMeState()
    {
    	return mState;
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