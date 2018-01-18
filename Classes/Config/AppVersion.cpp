//
//  AppVersion.cpp
//  GouJi
//
//  Created by ZengQi on 15-1-29.
//
//

#include "AppVersion.h"

// 客户端版本
const char* const CLIENT_VERSION = "1.0.0";
// 逻辑版本
const char* const LOGIC_VERSION = "1.0.0";
// 渠道类型
#ifdef DEBUG_MODE
const char* const CHANNEL_TYPE = "debugger";
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const char* const CHANNEL_TYPE = "App Store";
#else
const char* const CHANNEL_TYPE = "{ANDROID_CHANNEL}";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const char* const PLATFORM_TYPE = "ios";
#else
const char* const PLATFORM_TYPE = "android";
#endif

// 友盟APPKEY
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
const char* const UMENG_APP_KEY = "58c36fa6e88bad2d7b000e33";
#else
const char* const UMENG_APP_KEY = "58c36f449f06fd5b13000f75";
#endif

// 友盟渠道ID
const char* const UMENG_CHANNEL_ID = CHANNEL_TYPE;

// 游戏服务器
#ifdef DEBUG_MODE
const char* const SERVER_HOST = "115.182.55.206:8888";
#else
const char* const SERVER_HOST = "paodekuai.duolepdk.com";
#endif

const char* const IOS_APP_ID = "1186036778";
const char* const IOS_URL_SCHEMES = "duole.paohuzihd";
// iOS检查更新地址
const char* const IOS_LOOKUP_LINK = "https://itunes.apple.com/cn/lookup?id=820847844";
// iOS下载地址
const char* const IOS_DOWNLOAD_LINK = "https://itunes.apple.com/cn/app/id820847844?mt=8";

KKQQGROUPINFO* QQGROUPINFO = new KKQQGROUPINFO();


