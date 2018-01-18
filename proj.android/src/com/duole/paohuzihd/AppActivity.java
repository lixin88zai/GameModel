/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.duole.paohuzihd;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.telephony.PhoneStateListener;
import android.telephony.SignalStrength;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.WindowManager;

import com.duole.jniutil.PlatformFunction;
import com.duole.jniutil.SysUtil;
import com.umeng.analytics.mobclick.game.MobClickCppHelper;
import com.umeng.message.PushAgent;
import com.umeng.message.UmengRegistrar;

public class AppActivity extends Cocos2dxActivity {
	//信号强度
	public static int gsm_signalStrength = 0;
	private TelephonyManager telManager;
	private SignalStateListener signalListener;
		
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// 屏幕常亮
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		
		// 友盟统计
		MobClickCppHelper.init(this, PlatformFunction.getUmengAppKey(), PlatformFunction.getUmengChannelId());
		// 友盟推送
		PushAgent.getInstance(this).enable();
		PushAgent.getInstance(this).onAppStart();
		Log.d("", "DEVICE_TOKEN=" + UmengRegistrar.getRegistrationId(this));
		
		SysUtil.getInstance().init(this);
		PlatformFunction.init(this);
		signalListener  = new SignalStateListener();
		telManager  = (TelephonyManager)getSystemService(Context.TELEPHONY_SERVICE);
		telManager.listen(signalListener, PhoneStateListener.LISTEN_SIGNAL_STRENGTHS);
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		
		SysUtil.getInstance().destroy();
		PlatformFunction.destroy();
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		
		MobClickCppHelper.onPause(this);
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		
		MobClickCppHelper.onResume(this);
	}
	
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		PlatformFunction.onActivityResult(requestCode, resultCode, data);
	}
			
	private class SignalStateListener extends PhoneStateListener{
		public void onSignalStrengthsChanged(SignalStrength signalStrength) {
			super.onSignalStrengthsChanged(signalStrength);
			final int strength = signalStrength.getGsmSignalStrength();
			int level = (int)Math.pow(strength, 1.0 / 3) * 30;
			SysUtil.getInstance().setSignalStrengthGsm(level);
		}
	}
}
