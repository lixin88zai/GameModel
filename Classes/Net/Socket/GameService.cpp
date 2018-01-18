//
//  GameService.cpp
//  Gouji
//
//  Created by 曾琪 on 14-7-21.
//
//

#include "GameService.h"

using namespace std;


static GameService* s_GameService = nullptr;
GameService* GameService::getInstance()
{
    if(!s_GameService)
    {
        s_GameService = new GameService();
    }
    return s_GameService;
}

void GameService::ConfigureMsgs()
{
    RECEIVE_MSG(MSGID_PRIVY_JOIN_GAME | MSGID_ACK,      ACKPrivyJoinGame,       GameService::OnPrivyJoinGameAck);
    RECEIVE_MSG(MSGID_REJOIN_GAME | MSGID_ACK,          ACKRejoinGame,          GameService::OnRejoinGameAck);
    RECEIVE_MSG(MSGID_LEAVE_GAME | MSGID_ACK,           ACKLeaveGame,           GameService::OnLeaveGameAck);
    RECEIVE_MSG(MSGID_READY | MSGID_ACK,                ACKReady,               GameService::OnReadyAck);
    RECEIVE_MSG(MSGID_GAME_INIT | MSGID_NTF,            NTFGameInit,            GameService::OnNTFGameInit);
    RECEIVE_MSG(MSGID_DEAL_CARDS | MSGID_NTF,           NTFDealCards,           GameService::OnNTFDealCards);
    RECEIVE_MSG(MSGID_TOKEN | MSGID_NTF,                NTFToken,               GameService::OnNTFToken);
    RECEIVE_MSG(MSGID_PLAY | MSGID_NTF,                 NTFPlayCards,           GameService::OnNTFPlayCards);
    RECEIVE_MSG(MSGID_PASS | MSGID_NTF,                 NTFPassCards,           GameService::OnNTFPassCards);
    RECEIVE_MSG(MSGID_RESET_CARDIDS | MSGID_NTF,        NTFResetCards,          GameService::OnNTFResetCards);
    RECEIVE_MSG(MSGID_RESULT | MSGID_NTF,               NTFResult,              GameService::OnNTFResult);
    RECEIVE_MSG(MSGID_BOMB_RESULT | MSGID_NTF,          NTFBombResult,          GameService::OnNTFBombResult);
    // 桌子事件消息
    RECEIVE_MSG(MSGID_TABLE_EVENT | MSGID_NTF,          NTFTableEvent,          GameService::OnNTFTableEvent);
    // 断线重连
    RECEIVE_MSG(MSGID_BOARD_INFO | MSGID_NTF,           NTFBoardInfo,           GameService::OnNTFBoardInfo);
    RECEIVE_MSG(MSGID_PROP_INFO | MSGID_NTF,            NTFPropInfo,            GameService::OnNTFPropInfo);
    // 聊天
    RECEIVE_MSG(MSGID_CHAT | MSGID_NTF,                 NTFChat,                GameService::OnNTFChat);
    RegisterSeqUpdate(this, onSeqUpdateHandler_selector(GameService::onSeqUpdate));
}

void GameService::SendJoinPrivyGame(unsigned long long nUserId, const string &sSession, int nTableId)
{
    REQPrivyJoinGame req;
    req.set_user_id(nUserId);
    req.set_session_key(sSession);
    req.set_client_version(0);
    req.set_table_id(nTableId);
    SendMsg(&req, MSGID_PRIVY_JOIN_GAME | MSGID_REQ);
}

void GameService::SendRejoinGame(unsigned long long nUserID, const string& sSession, int nTableID, int nSeatID)
{
    REQRejoinGame req;
    req.set_user_id(nUserID);
    req.set_session_key(sSession);
    req.set_client_version(0);
    req.set_table_id(nTableID);
    req.set_seat_id(nSeatID);
    req.set_seq_id(GetLastReceivedMsgSeqId());
    SendMsg(&req, MSGID_REJOIN_GAME | MSGID_REQ);
}

void GameService::SendSitDown()
{
    REQPrivySitDown req;
    req.set_seat_id(0);
    SendMsg(&req, MSGID_PRIVY_SITDOWN | MSGID_REQ);
}

void GameService::SendReady()
{
    REQReady req;
    SendMsg(&req, MSGID_READY | MSGID_REQ);
}

void GameService::SendLeaveGame()
{
    REQLeaveGame req;
    SendMsg(&req, MSGID_LEAVE_GAME | MSGID_REQ);
}

void GameService::SendDealEnd()
{
    REQDealEnd req;
    SendMsg(&req, MSGID_DEAL_END | MSGID_REQ);
}

void GameService::SendPlayCards(const vector<int>& oCardIds)
{
    REQPlayCards req;
    for (size_t i = 0; i < oCardIds.size(); i ++)
    {
        req.add_card_id(oCardIds.at(i));
    }
    SendMsg(&req, MSGID_PLAY | MSGID_REQ);
}

void GameService::SendNormalChat(unsigned long long nUserId, int nChatId, const std::string& sChatContent)
{
    REQChat req;
    req.set_to_user_id(nUserId);
    req.set_chat_msg_id(nChatId);
    req.set_chat_msg(sChatContent);
    SendMsg(&req, MSGID_CHAT | MSGID_REQ);
}

unsigned int GameService::GetLastReceivedMsgSeqId()
{
    cocos2d::log("GameService::GetLastReceivedMsgSeqId >>> seq=%u", m_nLastSeqId);
    return m_nLastSeqId;
}

void GameService::ClearSeq()
{
    m_nLastSeqId = 0;
}

void GameService::onSeqUpdate(unsigned int nSeq)
{
    if (nSeq != 0)
    {
        m_nLastSeqId = nSeq;
    }
}
