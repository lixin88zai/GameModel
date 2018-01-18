//
//  WebManager.h
//  GouJi
//
//  Created by 曾琪 on 14-9-25.
//
//

#ifndef GouJi_WebManager_h
#define GouJi_WebManager_h

#include "Net/Web/WebProxy.h"
#include "Net/Web/Commands/MailCommand.h"
#include "Config/Config.h"

class WebManager
{
public:
    static WebManager* getInstance();
    
    WebManager();
    ~WebManager();
    
    void initialize(std::string sDeviceId);
    void reset();
    
public:
    // 登录
    void doCommonLogin(const std::string &sUserName, const std::string &sPassword, WebResultCallback pCallback);
    void doGuestLogin(WebResultCallback pCallback);
    void doWechatLogin(const std::string token,const int tokentype,WebResultCallback pCallback);
    
    void doCheckLogin(WebResultCallback pCallback);
    // 版本检查
    void doCheckVersion(WebResultCallback pCallback);
    // 私人场配置
    void doPrivyConfig(WebResultCallback pCallback);
    // 私人场创建
    void doPrivyCreate(const KKPRIVYRULE& oRule, WebResultCallback pCallback);
    // 私人场加入
    void doPrivyJoin(int nPrivyId, const std::string& sPassword, WebResultCallback pCallback);
    void doGetRoomInfo(int nPrivyId,const std::string& sPassword,WebResultCallback pCallback);
    // 道具信息
    void doPropDetail(WebResultCallback pCallback);
    
    // 邮件相关
    void doGetMailAbsract(WebResultCallback pCallback);
    void doGetMailList(const int& nVer, WebResultCallback pCallback);
    void doGetMailDetail(const std::string& sMailId, WebResultCallback pCallback);
    void doGetMailAttach(const std::string& sMailId, WebResultCallback pCallback);
    
    // 获取在线配置
    void doGetOnlineConfig(WebResultCallback pCallback);
    
private:
    std::string m_sDeviceId;
    WebProxy    *m_pWebProxy;
};

#endif
