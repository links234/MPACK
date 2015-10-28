package com.PukApp.MPACK;

import android.content.Intent;
import android.support.v7.widget.ShareActionProvider;
import android.util.Log;

class EasyShare
{
	MainActivity mContext;
	ShareActionProvider mShareActionProvider;
	Intent mIntent;
	
	public EasyShare(MainActivity mainActivity)
	{
		mContext = mainActivity;
		mShareActionProvider = new ShareActionProvider(mContext);
	}
	
	public native void nativeEasyShare();	
	
	public void sendEasyShareToCpp() 
	{
		nativeEasyShare();
	}
	
	public void Share(String shareSubject,String shareBody)
	{		
		Intent sharingIntent = new Intent(android.content.Intent.ACTION_SEND); 
	    sharingIntent.setType("text/plain");
	    sharingIntent.putExtra(android.content.Intent.EXTRA_SUBJECT, shareSubject);
	    sharingIntent.putExtra(android.content.Intent.EXTRA_TEXT, shareBody);
	    mContext.startActivity(Intent.createChooser(sharingIntent, "Share via"));
	}
	
}