//
//  WebManager.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-25.
//
//

#include "WebManager.h"
#include "AppDelegate.h"
#include "Config/AppVersion.h"
#include "Config/AppDeveloper.h"
#include "Net/Web/Commands/LoginCommand.h"
#include "Net/Web/Commands/PrivyCommand.h"
#include "Net/Web/Commands/OnlineConfigCommand.h"
#include "Net/Web/Commands/PropCommand.h"

using namespace std;
using namespace cocos2d::network;

static WebManager* s_WebManager = nullptr;
WebManager* WebManager::getInstance()
{
    if(!s_WebManager)
    {
        s_WebManager = new WebManager();
    }
    return s_WebManager;
}

WebManager::WebManager()
:
m_sDeviceId(""),
m_pWebProxy(nullptr)
{
}

WebManager::~WebManager()
{
    if (m_pWebProxy != nullptr)
    {
        delete m_pWebProxy;
        m_pWebProxy = nullptr;
    }
}

void WebManager::initialize(string sDeviceId)
{
    m_sDeviceId = sDeviceId;
    
    HttpClient *pClient = HttpClient::getInstance();
    pClient->setTimeoutForConnect(5);
    pClient->setTimeoutForRead(20);
    pClient->setTimeoutForDnsCache(86400);
    pClient->enableCookies(nullptr);
    
    reset();
}

void WebManager::reset()
{
    if (m_pWebProxy == nullptr)
    {
        m_pWebProxy = new WebProxy();
    }
    m_pWebProxy->init(HttpClient::getInstance(), developer::getServerHost());
}

void WebManager::doCommonLogin(const string &sUserName, const string &sPassword, WebResultCallback pCallback)
{
    WebCommand *pCommand = new CommonLoginCommand(pCallback);
    pCommand->getVariables()->input("user", sUserName);
    pCommand->getVariables()->input("passwd", sPassword);
    pCommand->getVariables()->input("idtype", IDTYPE_SEVENK);
    pCommand->getVariables()->input("passtype", PASSTYPE_NAKE);
    pCommand->getVariables()->input("deviceid", m_sDeviceId);
    pCommand->getVariables()->input("ver", LOGIC_VERSION);
    pCommand->getVariables()->input("channelid", CHANNEL_TYPE);
    pCommand->getVariables()->input("platform", PLATFORM_TYPE);
    
    m_pWebProxy->post(pCommand);
}

void WebManager::doGuestLogin(WebResultCallback pCallback)
{
    WebCommand *pCommand = new GuestLoginCommand(pCallback);
    pCommand->getVariables()->input("deviceid", m_sDeviceId);
    pCommand->getVariables()->input("ver", LOGIC_VERSION);
    pCommand->getVariables()->input("channelid", CHANNEL_TYPE);
    pCommand->getVariables()->input("platform", PLATFORM_TYPE);
    
    m_pWebProxy->post(pCommand);
}

//微信登录
void WebManager::doWechatLogin(std::string token,const int tokentype,WebResultCallback pCallback)
{
    WebCommand *pCommand = new WechatLoginCommand(pCallback);
    pCommand->getVariables()->input("deviceid", m_sDeviceId);
    pCommand->getVariables()->input("ver", LOGIC_VERSION);
    pCommand->getVariables()->input("channelid", CHANNEL_TYPE);
    pCommand->getVariables()->input("platform", PLATFORM_TYPE);
    pCommand->getVariables()->input("token", token);
    pCommand->getVariables()->input("tokentype", tokentype);
    
    m_pWebProxy->post(pCommand);
}

void WebManager::doCheckLogin(WebResultCallback pCallback)
{
    WebCommand *pCommand = new CheckLoginCommand(pCallback);
    m_pWebProxy->get(pCommand);
}

void WebManager::doCheckVersion(WebResultCallback pCallback)
{
    WebCommand *pCommand = new CheckVersionCommand(pCallback);
    m_pWebProxy->get(pCommand);
}

void WebManager::doPrivyConfig(WebResultCallback pCallback)
{
    WebCommand *pCommand = new PrivyConfigCommand(pCallback);
    m_pWebProxy->get(pCommand);
}

void WebManager::doPrivyCreate(const KKPRIVYRULE &oRule, WebResultCallback pCallback)
{
    WebCommand *pCommand = new PrivyCreateCommand(pCallback);
    pCommand->getVariables()->input("playtype", oRule.nPlayType);
    pCommand->getVariables()->input("players", oRule.nTotalPlayers);
    pCommand->getVariables()->input("games", oRule.nTotalGames);
    pCommand->getVariables()->input("s3first", oRule.bSpade3First);
    m_pWebProxy->post(pCommand);
}

void WebManager::doGetRoomInfo(int nPrivyId,const string &sPassword,WebResultCallback pCallback)
{
    WebCommand *pCommand = new GetRoomInfoCommand(pCallback);
    pCommand->getVariables()->input("privytableid", nPrivyId);
    m_pWebProxy->get(pCommand);
}

void WebManager::doPrivyJoin(int nPrivyId, const string &sPassword, WebResultCallback pCallback)
{
    WebCommand *pCommand = new PrivyJoinCommand(pCallback);
    pCommand->getVariables()->input("privytableid", nPrivyId);
    m_pWebProxy->post(pCommand);
}

// 道具信息
void WebManager::doPropDetail(WebResultCallback pCallback)
{
    WebCommand *pCommand = new PropDetailCommand(pCallback);
    m_pWebProxy->get(pCommand);
}


void WebManager::doGetMailAbsract(WebResultCallback pCallback)
{
    WebCommand* pCommand = new MailAbstractCommand(pCallback);
    m_pWebProxy->get(pCommand);
}

void WebManager::doGetMailList(const int& nVer, WebResultCallback pCallback)
{
    WebCommand* pCommand = new MailListCommand(pCallback);
    pCommand->getVariables()->input("ver", nVer);
    m_pWebProxy->get(pCommand);
}

void WebManager::doGetMailDetail(const std::string& sMailId, WebResultCallback pCallback)
{
    WebCommand* pCommand = new MailDetailCommand(pCallback);
    pCommand->getVariables()->input("mailid", sMailId);
    m_pWebProxy->get(pCommand);
}

void WebManager::doGetMailAttach(const std::string& sMailId, WebResultCallback pCallback)
{
    WebCommand* pCommand = new MailAttachCommand(sMailId, pCallback);
    pCommand->getVariables()->input("mailid", sMailId);
    m_pWebProxy->post(pCommand);
}

void WebManager::doGetOnlineConfig(WebResultCallback pCallback)
{
    WebCommand* pCommand = new OnlineConfigCommand(pCallback);
    pCommand->getVariables()->input("channelid", CHANNEL_TYPE);
    pCommand->getVariables()->input("ver", LOGIC_VERSION);
    m_pWebProxy->get(pCommand);
}
