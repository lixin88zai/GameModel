//
//  CommonService.cpp
//  game
//
//  Created by Joi Yao on 16/10/17.
//
//

#include "CommonService.h"

void CommonService::Configure(GameSocketProxy *pProxy, MsgService *pMsgService)
{
    m_pSocket = pProxy;
    m_pMsgService = pMsgService;
    ConfigureMsgs();
}

void CommonService::ClearStandbyMsg()
{
    if (m_pMsgService)
    {
        m_pMsgService->ClearStandbyMsg();
    }
}

void CommonService::SendMsg(google::protobuf::Message *pMsg, unsigned int dwType, unsigned int dwSeqID)
{
    if (m_pMsgService)
    {
        m_pMsgService->SendMsg(pMsg, dwType, dwSeqID);
    }
}

void CommonService::RegisterMsg(unsigned int nMsgId, Message *pTemplate, cocos2d::Ref *pTarget, SEL_OnMsgHandler pFunc)
{
    if (m_pSocket)
    {
        m_pSocket->RegisterMsg(nMsgId, pTemplate, pTarget, pFunc);
    }
}

void CommonService::RegisterSeqUpdate(Ref *pTarget, SEL_OnSeqUpdateHandler pFunc)
{
    if (m_pSocket)
    {
        m_pSocket->RegisterSeqUpdate(pTarget, pFunc);
    }
}

unsigned int CommonService::GetLastReceivedMsgSeqId()
{
    if (m_pSocket)
    {
        return m_pSocket->GetLastReceivedMsgSeqId();
    }
    return 0;
}