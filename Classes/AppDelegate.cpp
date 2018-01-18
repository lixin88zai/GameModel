#include "AppDelegate.h"
#include "System/SysUtil.h"
#include "Util/Utils.h"
#include "Net/Web/WebManager.h"
#include "Config/Config.h"
#include "Core/OnlineParams.h"
#include "Core/ControllerManager.h"
#include "Net/Web/WebManager.h"
#include "Net/Socket/ConnectProxy.h"
#include "Net/Socket/GameService.h"
#include "Net/Socket/MatchService.h"
#include "Net/Socket/HornChannel.h"
#include "Core/AppView.h"


USING_NS_CC;
using namespace util;
using namespace std;

#define KEY_DEVICEID      "DeviceID"

AppDelegate*    app         = nullptr;

AppDelegate::AppDelegate()
:
m_pWorkQueue(nullptr)
{
    app = this;
}

AppDelegate::~AppDelegate()
{
    app = nullptr;
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLViewImpl::create("多乐跑胡子");
        director->setOpenGLView(glview);
    }

    // turn off display FPS
#ifdef DEBUG_MODE
    //director->setDisplayStats(true);
#endif
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // 初始化
    initialize();
    
    // 友盟统计
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL(UMENG_APP_KEY, UMENG_CHANNEL_ID);
#endif
    
    log("UMENG_APP_KEY = %s", UMENG_APP_KEY);
    log("UMENG_CHANNEL_ID = %s", UMENG_CHANNEL_ID);
    
//     当前版本不显示启动页
    Value oData = Value(kSceneHall);
    dispatchEvent(SCENE_EVT_SCENE_CHANGE, &oData);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseAllEffects();
    
    // 友盟统计
    //umeng::MobClickCpp::applicationDidEnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // 静音模式
    MusicUtil::ResumeBackgroundMusic();
    MusicUtil::ResumeEffect();
    
    
    // 检查登录状态
//    dispatchEvent(EVT_CHECK_LOGIN);
}

void AppDelegate::initialize()
{
    // 初始化View
    AppView::getInstance()->initialize();
    
    // 获取设备ID
    string sDeviceId = ReaderWriter::LoadStringFromXML(KEY_DEVICEID, "");
    if (sDeviceId.empty())
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        sDeviceId = iosutil::GetUDID();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        CSysUtil::GetMobileID(sDeviceId);
#endif
        ReaderWriter::SaveStringToXML(KEY_DEVICEID, sDeviceId);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    // 初始化崩溃跟踪
    CSysUtil::CrashHandlerSetup();
#endif
    // 初始化屏幕参数
    WindowUtil::initialize();
    // 初始化声音参数
    MusicUtil::initialize();
    // 初始化位置参数
    PostionUtil::initialize();
    // 初始化工作队列
    m_pWorkQueue = new CWorkQueue();
    // 初始化WEB服务
    WebManager::getInstance()->initialize(sDeviceId);
    // 初始化Connet
    initConnect();
    // 初始化Controller模块
    ControllerManager::getInstance()->initialize();
    // 初始化在线参数配置
    OnlineParams::getInstance()->initialize();
}

void AppDelegate::initConnect()
{
    // 喇叭服务
    ConnectProxy::getInstance()->Register(HornService::getInstance());
    // 游戏服务
    ConnectProxy::getInstance()->Register(GameService::getInstance());
    // 配桌服务
    ConnectProxy::getInstance()->Register(MatchService::getInstance());
    
    ConnectProxy::getInstance()->Configure();
}
