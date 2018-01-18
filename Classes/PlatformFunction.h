//
//  PlatformFunction.h
//  GouJi
//
//  Created by mtt on 14-9-29.
//
//

#ifndef __GouJi__PlatformFunction__
#define __GouJi__PlatformFunction__

#include <string>

class PlatformFunction
{
public:
    // 打开链接
    static void openURL(const std::string &sUrl);
    // 打开应用
    static void openApplication(const std::string &sLinkUrl, const std::string &sDownloadUrl);
    // 判断是否可以打开应用
    static bool canOpenApplication(const std::string &sLinkUrl);
    
    // 安装应用
    static void installFile();
    
    // 获取电量
    static float getBatteryLevel();
    
    //获取当前网络的信号
    static int getNetType();
    //获取当前的网络强度
    static int getSignalStrength();
    
    // 评论
    static void showComment();
    
    // 分享
    enum SocialPlatform
    {
        UNKNOWN,        // 未知
        WECHATSESSION,  // 微信好友
        WECHATTIMELINE, // 微信朋友圈
        QQ,             // QQ好友
        QZONE,          // QQ空间
        SINA            // 新浪微博
    };
    static void share(SocialPlatform ePlatform,
                      const std::string &sText,
                      const std::string &sTitle = "",
                      const std::string &sEventOnFinish = "");
    static void shareImage(SocialPlatform ePlatform,
                           const std::string &sAbsoluteImagePath,
                           const std::string &sNotificationOnFinish = "");
    
    static void copyText(const std::string &sText);
    
    //加入qq群
    static bool joinQQGroup(const std::string &url);
};

#endif /* defined(__GouJi__PlatformFunction__) */
