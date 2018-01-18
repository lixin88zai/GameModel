//
//  CommonService.h
//  game
//
//  Created by Joi Yao on 16/10/17.
//
//

#pragma once

#include "MsgService.h"
#include "Protocol/ProtocolDef.h"

#define RECEIVE_MSG(_MSGID_, _TEMPLATECLASS_, _FUNC_)\
m_pSocket->RegisterMsg(_MSGID_, new _TEMPLATECLASS_(), this, onMsgHandler_selector(_FUNC_));

class CommonService : public cocos2d::Ref
{
public:
    virtual void Configure(GameSocketProxy* pProxy, MsgService* pMsgService);
    virtual void ConfigureMsgs() = 0;
    virtual void ClearStandbyMsg();
    
protected:
    void SendMsg(Message *pMsg, unsigned int dwType, unsigned int dwSeqID = 0);
    void RegisterMsg(unsigned int nMsgId, Message *pTemplate, cocos2d::Ref *pTarget, SEL_OnMsgHandler pFunc);
    void RegisterSeqUpdate(cocos2d::Ref* pTarget, SEL_OnSeqUpdateHandler pFunc);
    unsigned int GetLastReceivedMsgSeqId();
    
    
    CommonService()
    :
    m_pSocket(nullptr),
    m_pMsgService(nullptr)
    {
    }
    
    ~CommonService()
    {
        m_pSocket = nullptr;
        m_pMsgService = nullptr;
    }
    
protected:
    GameSocketProxy*    m_pSocket;
    MsgService*         m_pMsgService;
};
