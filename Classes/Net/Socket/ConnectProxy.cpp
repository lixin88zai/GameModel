//
//  ConnectProxy.cpp
//  game
//
//  Created by Joi Yao on 16/10/17.
//
//

#include "ConnectProxy.h"
#include "AppDelegate.h"
#include "CommonModel/ConnectingLayer.h"
#include "Util/Utils.h"
#include "Config/Config.h"

#define REGFUNC(_MSGID_, _TEMPLATECLASS_, _FUNC_)\
m_pSocket->RegisterMsg(_MSGID_, new _TEMPLATECLASS_(), this, onMsgHandler_selector(_FUNC_));

#define CONN_LIMIT  3

USING_NS_CC;
using namespace std;
using namespace util;

static ConnectProxy* s_ConnectProxy = nullptr;

ConnectProxy* ConnectProxy::getInstance()
{
    if(!s_ConnectProxy)
    {
        s_ConnectProxy = new ConnectProxy();
    }
    return s_ConnectProxy;
}

void ConnectProxy::Register(CommonService *pService)
{
    m_oServices.pushBack(pService);
}

void ConnectProxy::Configure()
{
    MsgService::Configure();
    // 心跳包应答，用来判断客户端是否超时
    REGFUNC(MSGID_HOLD | MSGID_ACK,     ACKIsTimeout,   ConnectProxy::OnIdleAck);
    // 登陆
    REGFUNC(MSGID_LOGIN | MSGID_ACK,    ACKUserLogin,   ConnectProxy::OnACKUserLogin);
    // 其他模块消息注册
    for (size_t i = 0; i < m_oServices.size(); i ++)
    {
        m_oServices.at(i)->Configure(m_pSocket, this);
    }
}

void ConnectProxy::OnServiceConnected(bool bConnected)
{
    log("ConnectProxy::OnServiceConnected = %s", bConnected? "true": "false");
    MsgService::OnServiceConnected(bConnected);
    unTickAll();
    if (bConnected)
    {
        m_nCntConn = 0;
        // 启动IDLE时钟，发送心跳包
        tick(CC_SCHEDULE_SELECTOR(ConnectProxy::DoSendIdle), this, IDLEINTERVAL);
        DoUserLogin();
    }
    else
    {
        CheckConnect();
    }
}

void ConnectProxy::OnServiceClosed()
{
    log("ConnectProxy::OnServiceClosed");
    CheckConnect();
}

//___________________________________________________________________________________________
// 开始等待
void ConnectProxy::BeginConnectWait()
{
    EndConnectWait();
    if (m_bReconnect)
    {
        string sText = str_format("当前网络有点坑，系统第%d次尝试重连中...", m_nCntConn);
        ConnectingLayer::getInstance()->show(sText);
    }
    tickOnce(CC_SCHEDULE_SELECTOR(ConnectProxy::OnConnectTimeout), this, TCPTIMEOUT);
}
//___________________________________________________________________________________________
// 结束等待
void ConnectProxy::EndConnectWait()
{
    unTick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnConnectTimeout), this);
    ConnectingLayer::getInstance()->hide();
}
//___________________________________________________________________________________________
// 连接超时
void ConnectProxy::OnConnectTimeout(float dt)
{
    Close();
    OnServiceConnected(false);
}
//___________________________________________________________________________________________
// 发送心跳同步
void ConnectProxy::DoSendIdle(float dt)
{
    //log("ConnectProxy::DoSendIdle");
    tick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnIdleTimeout), this, IDLETIMEOUT);
    tick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnIdleLost), this, TCPTIMEOUT);
    SendIdle();
}
//___________________________________________________________________________________________
// 心跳同步超时
void ConnectProxy::OnIdleTimeout(float dt)
{
    log("ConnectProxy::OnIdleTimeout");
    bool bLastLogin = m_bLogined;
    m_bLogined = false;
    if (bLastLogin)
    {
        Reconnect();
    }
    else
    {
        DoConnect();
    }
}
//___________________________________________________________________________________________
// 心跳同步丢失
void ConnectProxy::OnIdleLost(float dt)
{
    log("ConnectProxy::OnIdleLost");
    unTick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnIdleLost), this);
    dispatchEvent(NTF_CONNECT_BAD);
}
//___________________________________________________________________________________________
// 关闭心跳
void ConnectProxy::StopIdle()
{
    log("ConnectProxy::StopIdle");
    unTick(CC_SCHEDULE_SELECTOR(ConnectProxy::DoSendIdle), this);
}
//___________________________________________________________________________________________
// 连接
void ConnectProxy::DoConnect()
{
    m_bReconnect = false;
    m_bLastLogined = false;
    log("ConnectProxy::DoConnect");
    ConnectServer();
}

void ConnectProxy::Reconnect()
{
    m_bReconnect = true;
    log("ConnectProxy::Reconnect");
    ConnectServer();
}

void ConnectProxy::CheckConnect()
{
    if (m_nCntConn >= CONN_LIMIT)
    {
        ConnectFail();
        return;
    }
    m_bLogined = false;
    if (m_bLastLogined)
    {
        Reconnect();
    }
    else
    {
        DoConnect();
    }
}

void ConnectProxy::CloseConnect()
{
    log("ConnectProxy::CloseConnect");
    EndConnectWait();
    dispatchEvent(NTF_CONNECT_BROKEN);
    unTickAll();
    Close();
}

void ConnectProxy::ConnectServer()
{
    m_nCntConn ++;
    log("ConnectProxy::ConnectServer >>> count=%d", m_nCntConn);
    CloseConnect();
    BeginConnectWait();

}

void ConnectProxy::ConnectFail()
{
    log("ConnectProxy::ConnectFail");
    ClearStandbyMsg();
    CloseConnect();
    m_nCntConn = 0;
    Value oData = Value(E_NETWORK_CLOSE);
    dispatchEvent(EVT_COMMON_ERROR, &oData);
    dispatchEvent(NTF_CLOSE_GAME);
}
//___________________________________________________________________________________________
// 登录
void ConnectProxy::DoUserLogin()
{
    
}
//
void ConnectProxy::SendUserLogin(unsigned long long nUserId, const std::string &sSession)
{
    REQUserLogin req;
    req.set_user_id(nUserId);
    req.set_session_key(sSession);
    req.set_client_version(0);
    
    SendMsg(&req, MSGID_LOGIN | MSGID_REQ);
}
//
void ConnectProxy::OnACKUserLogin(Message *pMsg)
{
    
}
//___________________________________________________________________________________________
// 心跳
void ConnectProxy::SendIdle()
{
    SendMsg(0, MSGID_HOLD | MSGID_REQ);
}
//
void ConnectProxy::OnIdleAck(Message *pMsg)
{
    //log("ConnectProxy::OnIdleAck");
    unTick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnIdleTimeout), this);
    unTick(CC_SCHEDULE_SELECTOR(ConnectProxy::OnIdleLost), this);
}
//___________________________________________________________________________________________
// 注册消息
void ConnectProxy::registerMsg(unsigned int nMsgId, google::protobuf::Message *pTemplate, cocos2d::Ref *pTarget, SEL_OnMsgHandler pFunc)
{
    m_pSocket->RegisterMsg(nMsgId, pTemplate, pTarget, pFunc);
}
