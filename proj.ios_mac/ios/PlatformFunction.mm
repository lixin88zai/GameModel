//
//  PlatformFunction.cpp
//  GouJi
//
//  Created by mtt on 14-9-29.
//
//
#import <UIKit/UIKit.h>

#include "PlatformFunction.h"
#include "cocos2d.h"
#include "AppController.h"
#include "Util/IOSUtil/CommentAlert.h"
#include "Util/IOSUtil/CheckUpdateIos.h"
#include "Util/IOSUtil/Reachability.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace std;

// 打开链接
void PlatformFunction::openURL(const string &sUrl)
{
    NSString *url = [NSString stringWithUTF8String:sUrl.c_str()];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

void PlatformFunction::openApplication(const string &sLinkUrl, const string &sDownloadUrl)
{
    //链接到对应的appURL上
    NSURL *linkUrl = [NSURL URLWithString:[NSString stringWithUTF8String:sLinkUrl.c_str()]];
    //如果链接不到对应app的url上 就直接链接到对应的app下载的URL上
    NSURL *downloadUrl = [NSURL URLWithString:[NSString stringWithUTF8String:sDownloadUrl.c_str()]];
    if ([[UIApplication sharedApplication] canOpenURL:linkUrl])
    {
        [[UIApplication sharedApplication] openURL:linkUrl];
    }
    else
    {
        [[UIApplication sharedApplication] openURL:downloadUrl];
    }
}

bool PlatformFunction::canOpenApplication(const std::string &sLinkUrl)
{
    //链接到对应的appURL上
    NSURL *linkUrl = [NSURL URLWithString:[NSString stringWithUTF8String:sLinkUrl.c_str()]];
    return [[UIApplication sharedApplication] canOpenURL:linkUrl];
}


void PlatformFunction::installFile()
{
    
}

// 获取电量
float PlatformFunction::getBatteryLevel()
{
    UIDevice *currentDevice = [UIDevice currentDevice];
    currentDevice.batteryMonitoringEnabled = YES;
    float fRet = currentDevice.batteryLevel;
    return fRet >= 0 ? fRet : 1;
}

//0无 1数据 2wifi
int PlatformFunction::getNetType()
{
    Reachability *r = [Reachability reachabilityWithHostname:@"www.baidu.com"];
    return [r currentReachabilityStatus];
}

//获取当前的网络信号强度
int PlatformFunction::getSignalStrength()
{
    UIApplication *app = [UIApplication sharedApplication];
    NSArray *subviews = [[[app valueForKey:@"statusBar"] valueForKey:@"foregroundView"] subviews];
    NSString *dataNetworkItemView = nil;
    
    for (id subview in subviews) {
        if([subview isKindOfClass:[NSClassFromString(@"UIStatusBarDataNetworkItemView") class]]) {
            dataNetworkItemView = subview;
            break;
        }
    }
    
    int signalStrength = [[dataNetworkItemView valueForKey:@"_wifiStrengthBars"] intValue];

    return signalStrength;
}

// 评论
void PlatformFunction::showComment()
{
    [[CommentAlert getInstance] showCommentAlert];
}

void PlatformFunction::share(SocialPlatform ePlatform,
                             const string &sText,
                             const string &sTitle,
                             const string &sEventOnFinish)
{
}

void PlatformFunction::shareImage(SocialPlatform ePlatform,
                                  const string &sAbsoluteImagePath,
                                  const string &sEventOnFinish)
{
}

void PlatformFunction::copyText(const std::string &sText)
{
    NSString *text = [NSString stringWithUTF8String:sText.c_str()];
    [UIPasteboard generalPasteboard].string = text;
}

bool PlatformFunction::joinQQGroup(const std::string &sURL){
    NSString *urlStr = [NSString stringWithFormat:@"%s",sURL.c_str()];
    NSURL *url = [NSURL URLWithString:urlStr];
    if([[UIApplication sharedApplication] canOpenURL:url]){
        [[UIApplication sharedApplication] openURL:url];
        return YES;
    }
    else return NO;
}
