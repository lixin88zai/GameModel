//
//  LoginCommand.h
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#ifndef GouJi_LoginCommand_h
#define GouJi_LoginCommand_h

#include "Net/Web/WebCommand.h"
#include "Config/AppDef.h"

class CommonLoginCommand : public WebCommand
{
public:
    CommonLoginCommand(WebResultCallback pCallback):WebCommand("/login", pCallback) {}
    
protected:
    // 由WebCommond::onRespond调用，必须由子类重写
    WebResult* parseResult(const rapidjson::Document &obJson);
};

class GuestLoginCommand : public WebCommand
{
public:
    GuestLoginCommand(WebResultCallback pCallback):WebCommand("/guestlogin", pCallback) {}
    
protected:
    // 由WebCommond::onRespond调用，必须由子类重写
    WebResult* parseResult(const rapidjson::Document &obJson);
};

class WechatLoginCommand : public WebCommand
{
public:
    WechatLoginCommand(WebResultCallback pCallback) :
    WebCommand("/wechatlogin",pCallback),
    refreshToken(""),
    expireIn(0)
    {}
    
protected:
    WebResult* parseResult(const rapidjson::Document &obJson);
    
public:
    std::string refreshToken;
    int expireIn;
};

class CheckLoginCommand : public WebCommand
{
public:
    CheckLoginCommand(WebResultCallback pCallback):WebCommand("/checklogin", pCallback) {}
    
protected:
    // 由WebCommond::onRespond调用，必须由子类重写
    WebResult* parseResult(const rapidjson::Document &obJson);

};

class LoginResult : public WebResult
{
public:
    LoginResult()
    :
    m_sSessionKey(""),
    m_bPlaying(false),
    m_obUserInfo({}),
    m_oConnInfo({}),
    m_oQQGroupInfo({}){}
    
    
public:
    std::string     m_sSessionKey;          // 游戏Session
    bool            m_bPlaying;             // 是否在游戏中
    KKUSERINFO      m_obUserInfo;           // 登录用户信息
    PKCONNINFO      m_oConnInfo;            // 连接信息
    KKQQGROUPINFO   m_oQQGroupInfo;         // QQ群信息
};

class WechatLoginResult : public LoginResult
{
public:
    WechatLoginResult() :
    wxCode(""),
    refreshToken("")
    {};

public:
    std::string wxCode ;
    std::string refreshToken;
};

class CheckVersionCommand : public WebCommand
{
public:
    CheckVersionCommand(WebResultCallback pCallback):WebCommand("/version/check", pCallback) {}
    
protected:
    // 由WebCommond::onRespond调用，必须由子类重写
    WebResult* parseResult(const rapidjson::Document &obJson);
    
};

class CheckVersionResult : public WebResult
{
public:
    CheckVersionResult() {}
};

#endif
