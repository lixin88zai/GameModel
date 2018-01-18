//
//  GameChannel.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/27.
//
//

#include "GameChannel.h"
#include "Config/Config.h""
#include "CommonModel/PromptTextBar.h"
#include "Util/Utils.h"
#include "Net/Socket/Protocol/ProtocolEnumDef.h"

USING_NS_CC;
using namespace std;
using namespace util;

GameChannel* GameChannel::create()
{
    GameChannel* pRet = new GameChannel();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    pRet = nullptr;
    return nullptr;
}

bool GameChannel::init()
{
    return true;
}

void GameChannel::DoPrivyJoinGame()
{
    
}

void GameChannel::DoRejoinGame()
{
    
}

void GameChannel::ConnectBroken()
{
    m_bConnBroken = true;
}

void GameChannel::CheckInGame()
{
    log("GameChannel::CheckInGame");
    if (m_bJoined && m_bConnBroken)
    {
        DoRejoinGame();
    }
}

void GameChannel::OnPrivyJoinGameAck(Message *pMsg)
{
    ACKPrivyJoinGame *pAck = static_cast<ACKPrivyJoinGame*>(pMsg);
    int nResult = pAck->result_id();
    log("GameChannel::OnPrivyJoinGameAck >>> result=%d", nResult);
    if (nResult == joingame_result_success || nResult == joingame_result_reconnect)
    {
        m_bJoined = true;
        if (nResult == joingame_result_reconnect) // 处于游戏中断线重连后记录该值
        {
    
        }
        else
        {
            // 准备阶段断线重连需要在此处移除转圈等待
            dispatchEvent(NTF_WAITINGLAYER_HIDE);
            // 若是断线重连需要移除上局桌子上显示的内容
            dispatchEvent(NTF_CLEAR_TABLE);
        }
        return;
    }
    string sMsg = "";
    switch (nResult)
    {
        case joingame_reuslt_failed_low_version:
            sMsg = GAME_LOGIN_FAILED_LOW_VERSION;
            break;
        case joingame_reuslt_failed_limit_userid:
            sMsg = GAME_LOGIN_FAILED_LIMIT;
            break;
        case joingame_result_failed_multi_login:
            sMsg = GAME_LOGIN_FAILED_MULTI;
            break;
        case joingame_result_failed_matchinfo_non:
            sMsg = GAME_JOIN_IN_FAILD;
            break;
        default:
            sMsg = str_format(FORMAT_ERROR, generateErrorMessage(MSGID_PRIVY_JOIN_GAME, nResult).c_str());
            sMsg += "，退出后请重新登录。";
            break;
    }
    onError(sMsg);
}

void GameChannel::OnRejoinGameAck(Message *pMsg)
{
    ACKRejoinGame* pAck = static_cast<ACKRejoinGame*>(pMsg);
    int nRet = pAck->result_id();
    log("GameChannel::OnRejoinGameAck >>> result=%d", nRet);
    if (!m_bRejoin)
    {
        return;
    }
    m_bRejoin = false;
    m_bConnBroken = false;
    switch (nRet)
    {
        case rejoin_game_result_succ:
            m_nCntRejoin = 0;
            break;
        case rejoin_game_result_failed_unknown:
        case rejoin_game_result_failed_login:
        case rejoin_game_result_failed_online:
            DoRejoinGame();
            break;
        default:
        {

        }
            break;
    }
}

void GameChannel::OnReadyAck(Message *pMsg)
{
    ACKReady* pAck = static_cast<ACKReady*>(pMsg);
    log("GameChannel::OnReadyAck >>> result=%d", pAck->result_id());
    if (pAck->result_id() == 0)
    {
        return;
    }
    string sMsg = generateErrorMessage(MSGID_READY, pAck->result_id());
    onError(sMsg);
}

void GameChannel::OnLeaveGameAck(Message *pMsg)
{
    ACKLeaveGame* pAck = static_cast<ACKLeaveGame*>(pMsg);
    log("GameChannel::OnLeaveGameAck %d", pAck->result_id());
    int nResultId = pAck->result_id();
    if (nResultId == leave_game_result_success) // 成功
    {

    }
    else if (nResultId == leave_game_result_failed_game_already_start) // 游戏已经开始
    {
        // 设置房主返回大厅的值为false
        promptText(Director::getInstance()->getRunningScene(), DEVICE_H / 2, TIP_OWNER_BACK_HALL_GAME_START);
    }
}

void GameChannel::OnNTFGameInit(Message *pMsg)
{

}

void GameChannel::OnNTFToken(Message *pMsg)
{

}

void GameChannel::OnNTFDealCards(Message *pMsg)
{

}

void GameChannel::OnNTFPlayCards(Message *pMsg)
{

}

void GameChannel::OnNTFPassCards(Message *pMsg)
{
    NTFPassCards* pNtf = static_cast<NTFPassCards*>(pMsg);
    unsigned long long nUserId = pNtf->user_id();
    onLogUserId("OnNTFPassCards", nUserId);
    dispatchEvent(EVT_CARD_PASS, &nUserId);
}

void GameChannel::OnNTFResetCards(Message *pMsg)
{

}

void GameChannel::OnNTFResult(Message *pMsg)
{
}

void GameChannel::OnNTFBoardInfo(Message* pMsg)
{

}

void GameChannel::OnNTFPropInfo(Message* pMsg)
{
    
}

void GameChannel::OnNTFChat(Message* pMsg)
{
   
}

void GameChannel::onError(const string &sMessage)
{
    if (sMessage.empty())
    {
        return;
    }
    Value oData(sMessage);
    dispatchEvent(EVT_GAME_ERROR, &oData);
}

string GameChannel::generateErrorMessage(int nMsgId, int nResult, int nBaseMsgId)
{
    nMsgId -= nBaseMsgId;
    string sRet = (string)str_format("%03d-%03d", nMsgId, nResult + 50);
    return sRet;
}

GameChannel::GameChannel()
:
m_bJoined(false),
m_bConnBroken(false),
m_bRejoin(false),
m_nCntRejoin(0)
{
}

GameChannel::~GameChannel()
{
    m_bRejoin = false;
    m_bConnBroken = false;
}
