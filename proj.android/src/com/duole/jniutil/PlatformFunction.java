package com.duole.jniutil;

import java.util.Collections;
import java.util.List;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import android.content.BroadcastReceiver;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.net.Uri;

public class PlatformFunction {
	 
	private static Cocos2dxActivity thisActivity = null;
	
	// ��垫��������
	private static BroadcastReceiver batteryChangedReceiver = null;
	private static float batteryLevel = 0;
	
	public static void init(Cocos2dxActivity activity) {
		thisActivity = activity;
		
		// ��垫��������
		batteryChangedReceiver = new BroadcastReceiver() {
			
			@Override
			public void onReceive(Context context, Intent intent) {
				int level = intent.getIntExtra("level", -1);
				int scale = intent.getIntExtra("scale", -1);
				if (level >= 0 && scale > 0) {
					batteryLevel = (float)level / scale;
				}
			}
		};
		thisActivity.registerReceiver(batteryChangedReceiver, new IntentFilter(Intent.ACTION_BATTERY_CHANGED));
	}
	
	public static void destroy() {
		// ��垫��������
		thisActivity.unregisterReceiver(batteryChangedReceiver);
		batteryChangedReceiver = null;
		
		thisActivity = null;
	}
	
	public static void openURL(final String url) {
		thisActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(url));
				thisActivity.startActivity(intent);
			}
		});
	}
	
	public static void openApplication(final String packageName, final String sDownLoadLink) {
        thisActivity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                boolean bSuccess = false;
                PackageManager manager = thisActivity.getPackageManager();
                Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
                mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);
                List<ResolveInfo> resolveInfos = manager.queryIntentActivities(mainIntent, 0);
                Collections.sort(resolveInfos, new ResolveInfo.DisplayNameComparator(manager));
                if (resolveInfos == null)
                {
                    bSuccess = false;
                }
                for (ResolveInfo reInfo : resolveInfos) {
                    if (reInfo.activityInfo.packageName.contentEquals(packageName)) {
                        String activityName = reInfo.activityInfo.name;
                        Intent launchIntent = new Intent();
                        launchIntent.setComponent(new ComponentName(packageName, activityName));
                        thisActivity.startActivity(launchIntent);
                        thisActivity.finish();
                        Cocos2dxHelper.terminateProcess();
                        bSuccess = true;
                        break;
                    }
                }
                if (!bSuccess)
                {
                    openURL(sDownLoadLink);
                }
            }
        });
    }
	
	public static boolean canOpenApplication(final String packageName) {
		boolean bRet = false;
		PackageManager manager = thisActivity.getPackageManager();
		Intent mainIntent = new Intent(Intent.ACTION_MAIN, null);
		mainIntent.addCategory(Intent.CATEGORY_LAUNCHER);
		List<ResolveInfo> resolveInfos = manager.queryIntentActivities(mainIntent, 0);
		Collections.sort(resolveInfos, new ResolveInfo.DisplayNameComparator(manager));
		if (resolveInfos == null) {
			bRet = false;
		}
		for (ResolveInfo reInfo : resolveInfos) {
			if (reInfo.activityInfo.packageName.contentEquals(packageName)) {
				bRet = true;
				break;
			}
		}
		return bRet;
    }
	
	public static float getBatteryLevel() {
		return batteryLevel;
	}
	
	public static void onActivityResult(int requestCode, int resultCode, Intent data) {
	}
	
	public static void copyText(final String sText) {
		thisActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				ClipboardManager manager = (ClipboardManager)thisActivity.getSystemService(Context.CLIPBOARD_SERVICE);  
				manager.setPrimaryClip(ClipData.newPlainText(null, sText));
			}
		}); 
    }
	
	//������qq缇�
	public static boolean joinQQGroup(final String sUrl){
		try{
			Intent intent = new Intent(Intent.ACTION_VIEW, Uri.parse(sUrl));
			thisActivity.startActivity(intent);
			return true;
		}catch(Exception e){
			
		}
		return false;
	}
	
	public static native String getUmengAppKey();
	public static native String getUmengChannelId();
	public static native String getWXAppId();
	public static native String getWXAppSecret();
	public static native String getUmengShareLink();
	public static native String getTencentShareLink();
}
