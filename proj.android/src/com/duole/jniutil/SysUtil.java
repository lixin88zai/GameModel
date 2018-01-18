package com.duole.jniutil;

import java.io.File;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.net.wifi.WifiManager;
import android.os.Environment;
import android.provider.Settings;
import android.telephony.TelephonyManager;

public class SysUtil {
	// 常量定义
	public static final String TAG = "SysUtil";

	private static SysUtil instance = null;

	private static Activity context = null;


	//信号强度
	public static int wifi_signalStrength = 0;
	public static int gsm_signalStrength = 0;
		
	/**
	 * A signal handler in native code has been triggered. As our last gasp,
	 * launch the crash handler (in its own process), because when we return
	 * from this function the process will soon exit.
	 */
	public static void nativeCrashed() {
		new RuntimeException("crashed here (native trace should follow after the Java trace)").printStackTrace();
	}

	public static Object rtnObject() {
		return SysUtil.getInstance();
	}

	public static SysUtil getInstance() {
		if (instance == null) {
			instance = new SysUtil();
		}
		return instance;
	}

	public void init(Activity activity) {
		context = activity;
	}

	public void destroy() {
		context = null;
	}

	// 取设备信息
	public String getMobileID() {
		String sRet = "";
		TelephonyManager tm = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
		sRet = tm.getDeviceId();
		if (sRet == null || sRet.length() < 2) {// ESN
			sRet = tm.getSubscriberId();
			if (sRet == null || sRet.length() < 2) {
				int iSDK = android.os.Build.VERSION.SDK_INT;
				if (iSDK > 8) {
					sRet = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.ANDROID_ID);
				} else {
					sRet = android.os.Build.ID + android.os.Build.CPU_ABI;
				}
			}
		}
		return sRet;
	}
	
	// 取得手机号码
	public String getPhoneNumber() {
		TelephonyManager tm = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
		return tm.getLine1Number();
	}

	// 取得IMSI
	public String getIMSI() {
		TelephonyManager tm = (TelephonyManager)context.getSystemService(Context.TELEPHONY_SERVICE);
		return tm.getSubscriberId();
	}
	
	public String getCacheDir() {
		File cacheDir = context.getCacheDir();
		return cacheDir.getParent()
				+ File.separator
				+ cacheDir.getName()
				+ File.separator;
	}
	
	public String getExternalCacheDir() {
		File cacheDir = context.getExternalCacheDir();
		return cacheDir.getParent()
				+ File.separator
				+ cacheDir.getName()
				+ File.separator;
	}
	
	public String getFilesDir() {
		File fileDir = context.getFilesDir();
		return fileDir.getParent()
				+ File.separator
				+ fileDir.getName()
				+ File.separator;
	}
	
	public String getExternalStorageDirectory() {
		return Environment.getExternalStorageDirectory().getAbsolutePath()
				+ File.separator;
	}
	
	public String getPackageName() {
		return context.getPackageName();
	}

	// 取得包版本号
	public String getVersionName() {
		String version = "";
		try {
			// getPackageName()是你当前类的包名，0代表是获取版本信息
			PackageInfo packInfo = context.getPackageManager().getPackageInfo(getPackageName(), 0);
			version = packInfo.versionName;
		} catch (PackageManager.NameNotFoundException e) {
		}
		return version;
	}

	// 取Application中meta-data
	public String getApplicationMetaData(String strName) {
		String strVal = "";
		try {
			ApplicationInfo appInfo = context.getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
			strVal = appInfo.metaData.getString(strName);
		} catch (PackageManager.NameNotFoundException e) {
		}
		return strVal;
	}

	// 获取手机型号
	public String getBuildModel() {
		return android.os.Build.MODEL;
	}

	// 获取手机厂商
	public String getBuildManufacturer() {
		return android.os.Build.MANUFACTURER;
	}

	public String ShowUrl(String strURL) {
		String strVal = "";
		Intent intent = new Intent();
		intent.setAction("android.intent.action.VIEW");
		intent.setData(Uri.parse(strURL));
		context.startActivity(intent);
		return strVal;
	}
	
	// 判断网络是否有效
	public boolean isNetworkConnected() {
		ConnectivityManager mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mNetworkInfo = mConnectivityManager.getActiveNetworkInfo();
		if (mNetworkInfo != null) {
			return mNetworkInfo.isAvailable();
		}
		return false;
	}

	// 判断WIFI网络是否可用
	public static boolean isWifiConnected() {
		ConnectivityManager mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mWiFiNetworkInfo = mConnectivityManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
		if (mWiFiNetworkInfo != null) {
			return mWiFiNetworkInfo.isAvailable();
		}
		return false;
	}
	
	// 判断MOBILE网络是否可用
	public static boolean isMobileConnected() {
		ConnectivityManager mConnectivityManager = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo mMobileNetworkInfo = mConnectivityManager.getNetworkInfo(ConnectivityManager.TYPE_MOBILE);
		if (mMobileNetworkInfo != null) {
			return mMobileNetworkInfo.isAvailable();
		}
		return false;
	}
	
	// 获取当前网络连接的类型信息
	public static int getConnectedType() {
		if (isWifiConnected()) {
			return 2; // wifi
		}
		if (isMobileConnected()) {
			return 1; // gprs
		}
		return -1;
	}

	public static int getSignalStrength(){
		if (getConnectedType() == 1){
			return getSignalStrengthGsm();
		}
		else{
			return getSignalStrengthWifi();
		}
	}

	//_gsm_signalStrength: gsm信号强度
	public void setSignalStrengthGsm(int _gsm_signalStrength){
		gsm_signalStrength = _gsm_signalStrength;
	}

	public static int getSignalStrengthGsm(){
		if (isMobileConnected()){
			gsm_signalStrength = 4;
		}
		else{
			gsm_signalStrength = 0;
		}
		return gsm_signalStrength;
	}
	//_wifi_signalStrength: wifi信号强度
	public static void setSignalStrengthWifi(int _wifi_signalStrength){
		wifi_signalStrength = _wifi_signalStrength;
	}

	public static int getSignalStrengthWifi(){
		int level = 0;
		level = 100 + ((WifiManager)context.getSystemService(Context.WIFI_SERVICE)).getConnectionInfo().getRssi();
		level = (int)Math.max(level, 0);
		return level;
	}	
}