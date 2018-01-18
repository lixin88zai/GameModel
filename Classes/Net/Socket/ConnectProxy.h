//
//  ConnectProxy.h
//  game
//
//  Created by Joi Yao on 16/10/17.
//
//

#pragma once

#include "BaseClass/TimeTick/TimeTick.h"
#include "BaseClass/Event/EventWrapper.h"
#include "CommonService.h"

class ConnectProxy : public MsgService, public TimeTick, public EventWrapper
{
public:
    static ConnectProxy* getInstance();
    
    void Register(CommonService* pService);
    void Configure();
    
protected:
    virtual void OnServiceConnected(bool bConnected);
    virtual void OnServiceClosed();
    
public:
    // 连接
    void DoConnect();
    void Reconnect();
    void CheckConnect();
    void CloseConnect();
    void ConnectServer();
    void ConnectFail();
    
    ConnectProxy()
    :
    m_oServices({}),
    m_bReconnect(false),
    m_bLogined(false),
    m_bLastLogined(false)
    {
    }
    
    ~ConnectProxy()
    {
        m_oServices.clear();
    }
    
private:
    void BeginConnectWait();
    void EndConnectWait();
    void OnConnectTimeout(float dt);

    void DoSendIdle(float dt);
    void OnIdleTimeout(float dt);
    void OnIdleLost(float dt);
    void StopIdle();
    // 登陆
    void DoUserLogin();
    void SendUserLogin(unsigned long long nUserId, const std::string& sSession);
    void OnACKUserLogin(Message *pMsg);
    // 心跳
    void SendIdle();
    void OnIdleAck(Message *pMsg);
    
    void registerMsg(unsigned int nMsgId, Message *pTemplate, cocos2d::Ref *pTarget, SEL_OnMsgHandler pFunc);
    
private:
    cocos2d::Vector<CommonService*> m_oServices;
    bool                            m_bReconnect;
    bool                            m_bLogined;
    bool                            m_bLastLogined;
    int                             m_nCntConn;
};
