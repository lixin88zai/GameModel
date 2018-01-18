//
//  PlatformFunction.cpp
//  GouJi
//
//  Created by mtt on 14-9-29.
//
//

#include "PlatformFunction.h"
#include "Core/AppVersion.h"
#include "Core/AppEvent.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "AppDelegate.h"

USING_NS_CC;
using namespace std;

#define CLASS_NAME "com/duole/jniutil/PlatformFunction"
#define SYS_UTIL "com/duole/jniutil/SysUtil"

static string s_sEventOnFinish = "";

void PlatformFunction::openURL(const string &sUrl)
{
    JniMethodInfo obMethodInfo;
    if (JniHelper::getStaticMethodInfo(obMethodInfo,
                                       CLASS_NAME,
                                       "openURL",
                                       "(Ljava/lang/String;)V"))
    {
        jstring url = obMethodInfo.env->NewStringUTF(sUrl.c_str());

        obMethodInfo.env->CallStaticVoidMethod(obMethodInfo.classID,
                                               obMethodInfo.methodID,
                                               url);

        obMethodInfo.env->DeleteLocalRef(url);
        obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
    }
}

void PlatformFunction::openApplication(const string &sLinkUrl, const string &sDownloadUrl)
{
    JniMethodInfo obMethodInfo;
    if (JniHelper::getStaticMethodInfo(obMethodInfo,
                                       CLASS_NAME,
                                       "openApplication",
                                       "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring linkUrl = obMethodInfo.env->NewStringUTF(sLinkUrl.c_str());
        jstring downloadUrl = obMethodInfo.env->NewStringUTF(sDownloadUrl.c_str());
        obMethodInfo.env->CallStaticVoidMethod(obMethodInfo.classID,
                                               obMethodInfo.methodID,
                                               linkUrl,
                                               downloadUrl);
        obMethodInfo.env->DeleteLocalRef(linkUrl);
        obMethodInfo.env->DeleteLocalRef(downloadUrl);
        obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
    }
}

bool PlatformFunction::canOpenApplication(const std::string &sLinkUrl)
{
	JniMethodInfo obMethodInfo;
	jboolean bRet = false;
	if (JniHelper::getStaticMethodInfo(obMethodInfo,
	                                   CLASS_NAME,
	                                   "canOpenApplication",
	                                   "(Ljava/lang/String;)Z"))
	{
		jstring url = obMethodInfo.env->NewStringUTF(sLinkUrl.c_str());

		bRet = obMethodInfo.env->CallStaticBooleanMethod(obMethodInfo.classID,
		                                               	 obMethodInfo.methodID,
		                                                 url);

		obMethodInfo.env->DeleteLocalRef(url);
		obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
	}
	return bRet == JNI_TRUE ? true : false;
}

void PlatformFunction::installFile()
{
}

float PlatformFunction::getBatteryLevel()
{
    JniMethodInfo obMethodInfo;
    jfloat fRet = 0;
    if (JniHelper::getStaticMethodInfo(obMethodInfo,
                                       CLASS_NAME,
                                       "getBatteryLevel",
                                       "()F"))
    {
        fRet = obMethodInfo.env->CallStaticFloatMethod(obMethodInfo.classID,
                                                       obMethodInfo.methodID);

        obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
    }
    return fRet;
}

void PlatformFunction::share(SocialPlatform ePlatform,
                             const string &sText,
                             const string &sTitle,
                             const string &sEventOnFinish)
{
    s_sEventOnFinish = sEventOnFinish;

    JniMethodInfo obMethodInfo;
    if (JniHelper::getStaticMethodInfo(obMethodInfo,
                                       CLASS_NAME,
                                       "share",
                                       "(ILjava/lang/String;Ljava/lang/String;)V"))
    {
    	jint platform = (jint)ePlatform;
    	jstring text = obMethodInfo.env->NewStringUTF(sText.c_str());
    	jstring title = obMethodInfo.env->NewStringUTF(sTitle.c_str());

        obMethodInfo.env->CallStaticVoidMethod(obMethodInfo.classID,
                                               obMethodInfo.methodID,
                                               platform,
                                               text,
                                               title);

        obMethodInfo.env->DeleteLocalRef(text);
        obMethodInfo.env->DeleteLocalRef(title);
        obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
    }
}

void PlatformFunction::shareImage(SocialPlatform ePlatform,
                                  const string &sAbsoluteImagePath,
                                  const string &sEventOnFinish)
{
    s_sEventOnFinish = sEventOnFinish;

    JniMethodInfo obMethodInfo;
    if (JniHelper::getStaticMethodInfo(obMethodInfo,
                                       CLASS_NAME,
                                       "shareImage",
                                       "(ILjava/lang/String;)V"))
    {
    	jint platform = (jint)ePlatform;
    	jstring absoluteImagePath = obMethodInfo.env->NewStringUTF(sAbsoluteImagePath.c_str());

        obMethodInfo.env->CallStaticVoidMethod(obMethodInfo.classID,
                                               obMethodInfo.methodID,
                                               platform,
                                               absoluteImagePath);

        obMethodInfo.env->DeleteLocalRef(absoluteImagePath);
        obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
    }
}

void PlatformFunction::copyText(const std::string &sText)
{
	JniMethodInfo obMethodInfo;
	if (JniHelper::getStaticMethodInfo(obMethodInfo,
	                                   CLASS_NAME,
	                                   "copyText",
	                                   "(Ljava/lang/String;)V"))
	{
	    jstring url = obMethodInfo.env->NewStringUTF(sText.c_str());

	    obMethodInfo.env->CallStaticVoidMethod(obMethodInfo.classID,
	                                           obMethodInfo.methodID,
	                                           url);

	    obMethodInfo.env->DeleteLocalRef(url);
	    obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
	}
}

bool PlatformFunction::joinQQGroup(const std::string &sUrl)
{
	JniMethodInfo obMethodInfo;
	jboolean bRet = false;
	if (JniHelper::getStaticMethodInfo(obMethodInfo,
									   CLASS_NAME,
									   "joinQQGroup",
									   "(Ljava/lang/String;)Z"))
	{
		jstring url = obMethodInfo.env->NewStringUTF(sUrl.c_str());

		bRet = obMethodInfo.env->CallStaticBooleanMethod(obMethodInfo.classID,
														 obMethodInfo.methodID,
														 url);

		obMethodInfo.env->DeleteLocalRef(url);
		obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
	}
	return bRet == JNI_TRUE ? true : false;
}

int PlatformFunction::getNetType()
{
  JniMethodInfo obMethodInfo;
  jint bRet = 0;
  if (JniHelper::getStaticMethodInfo(obMethodInfo,
                     SYS_UTIL,
                     "getConnectedType",
                     "()I"))
  {

    bRet = obMethodInfo.env->CallStaticIntMethod(obMethodInfo.classID,
                         obMethodInfo.methodID);

    obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
  }
  return bRet;
}

int PlatformFunction::getSignalStrength()
{
  JniMethodInfo obMethodInfo;
  jint bRet = 0;
  if (JniHelper::getStaticMethodInfo(obMethodInfo,
                     SYS_UTIL,
                     "getSignalStrength",
                     "()I"))
  {

    bRet = obMethodInfo.env->CallStaticIntMethod(obMethodInfo.classID,
                         obMethodInfo.methodID);

    obMethodInfo.env->DeleteLocalRef(obMethodInfo.classID);
  }
  return bRet;
}


extern "C"
{
	JNIEXPORT jstring JNICALL Java_com_duole_jniutil_PlatformFunction_getUmengAppKey(JNIEnv* env, jobject thiz)
	{
		return env->NewStringUTF(UMENG_APP_KEY);
    }

	JNIEXPORT jstring JNICALL Java_com_duole_jniutil_PlatformFunction_getUmengChannelId(JNIEnv* env, jobject thiz)
	{
		return env->NewStringUTF(UMENG_CHANNEL_ID);
    }
}
