//
//  OnlineParams.cpp
//  GouJi
//
//  Created by ZengQi on 15-2-4.
//
//

#include "OnlineParams.h"
#include "network/HttpClient.h"
#include "Util/Utils.h"
#include "Net/Web/WebManager.h"
#include "AppDelegate.h"
#include "Net/Web/Commands/OnlineConfigCommand.h"
#include "Config/Config.h"
#include "CommonModel/WaitingLayer.h"

#include <netdb.h>

#define KEY_SERVERHOSTRESOLVE       "server_host_resolve"

using namespace umeng;
using namespace util;
using namespace cocos2d::network;

static OnlineParams* s_OnlineParams = nullptr;

OnlineParams* OnlineParams::getInstance()
{
    if(!s_OnlineParams)
    {
        s_OnlineParams = new OnlineParams();
        s_OnlineParams->initialize();
    }
    
    return s_OnlineParams;
}

OnlineParams::OnlineParams()
:m_bInReview(true)
{
}

OnlineParams::~OnlineParams()
{
    
}

void OnlineParams::initialize()
{
#if DEBUG_MODEL
    m_bInReview = false;
#else
    m_bInReview = util::ReaderWriter::LoadBooleanFromXML(KEY_INREVIEWCHANNEL, true);
#endif
    doGetOnlineConfig();
}

void OnlineParams::onUpdateFinished(bool succeed, void* pUserData)
{
#ifdef DEBUG_MODE
    return;
#endif
    if (!succeed)
    {
        return;
    }
    
    // 读取DNS解析绑定
    string sResolve = readUmengConfigParamString(KEY_SERVERHOSTRESOLVE);
    if (!sResolve.empty() && !isIPv6Enabled())
    {
        // 暂时不支持IPv6
        vector<string> obCustomHosts;
        obCustomHosts.push_back(sResolve);
        HttpClient::getInstance()->enableCustomHosts(obCustomHosts);
    }
}

string OnlineParams::readUmengConfigParamString(const char* pszKey)
{
    //return MobClickCpp::getConfigParam(pszKey);
    return "";
}

bool OnlineParams::readUmengConfigParamBool(const char* pszKey)
{
    //string sValue = MobClickCpp::getConfigParam(pszKey);
    //return (!sValue.empty() && atoi(sValue.c_str()) > 0);
    return false;
}

bool OnlineParams::readUmengConfigParamBool(const char* pszKey, const char* pszPattern)
{
    //string sValue = MobClickCpp::getConfigParam(pszKey);
    //return sValue.find(pszPattern) != string::npos;
    return false;
}

bool OnlineParams::isIPv6Enabled()
{
    struct addrinfo hints, *res, *res0;
    int error;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    error = getaddrinfo("127.0.0.1", nullptr, &hints, &res0);
    if (error != 0)
    {
        return false;
    }
    
    bool enabled = false;
    for (res = res0; res; res = res->ai_next)
    {
        if (res->ai_family == AF_INET6)
        {
            enabled = true;
            break;
        }
    }
    
    freeaddrinfo(res0);
    
    return enabled;
}

//检测是否在审核中
void OnlineParams::doGetOnlineConfig()
{
    WebManager::getInstance()->doGetOnlineConfig(CC_CALLBACK_1(OnlineParams::onGetOnlineConfigComplete, this));
}

void OnlineParams::onGetOnlineConfigComplete(WebResult* pResult)
{
    WaitingLayer::sharedInstance()->hide();


}
