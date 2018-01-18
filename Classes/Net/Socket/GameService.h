//
//  GameService.h
//  BaoHuang
//
//  Created by 曾琪 on 14-7-21.
//
//

#pragma once

#include "CommonService.h"
#include "Protocol/ProtocolDef.h"

class GameServiceDelegate
{
public:
    DELEGATE_FUNC(OnPrivyJoinGameAck);
    DELEGATE_FUNC(OnRejoinGameAck);
    DELEGATE_FUNC(OnReadyAck);
    DELEGATE_FUNC(OnLeaveGameAck);
    DELEGATE_FUNC(OnNTFGameInit);
    DELEGATE_FUNC(OnNTFDealCards);
    DELEGATE_FUNC(OnNTFToken);
    DELEGATE_FUNC(OnNTFPlayCards);
    DELEGATE_FUNC(OnNTFPassCards);
    DELEGATE_FUNC(OnNTFResetCards);
    DELEGATE_FUNC(OnNTFResult);
    DELEGATE_FUNC(OnNTFBombResult);
    // 桌子事件
    DELEGATE_FUNC(OnNTFTableEvent);
    // 断线重连
    DELEGATE_FUNC(OnNTFBoardInfo);
    DELEGATE_FUNC(OnNTFPropInfo);
    // 普通聊天
    DELEGATE_FUNC(OnNTFChat);
};

class GameService : public CommonService
{
public:
    static GameService* getInstance();
    
    virtual void ConfigureMsgs();
    bool HasDelegate() { return m_pDelegate != nullptr; }
    void SetDelegate(GameServiceDelegate *pDelegate) { m_pDelegate = pDelegate; }
    GameServiceDelegate* GetDelegate() { return m_pDelegate; }
    
    virtual void ClearSeq();
    void onSeqUpdate(unsigned int nSeq);
    
    GameService()
    :
    m_pDelegate(nullptr),
    m_nLastSeqId(0)
    {
    }
    
public:
    // 加入游戏
    void SendJoinPrivyGame(unsigned long long nUserId, const std::string& sSession, int nTableId);
    // 发送重新加入游戏
    void SendRejoinGame(unsigned long long nUserID, const std::string& sSession, int nTableID, int nSeatID);
    // 坐下
    void SendSitDown();
    // 准备
    void SendReady();
    // 离开游戏
    void SendLeaveGame();
    // 发牌结束
    void SendDealEnd();
    // 出牌
    void SendPlayCards(const std::vector<int>& oCardIds);
    // 发送普通聊天消息
    void SendNormalChat(unsigned long long nUserId, int nChatId, const std::string& sChatContent);
    
public:
    SERVICE_FUNC(OnPrivyJoinGameAck);
    SERVICE_FUNC(OnRejoinGameAck);
    SERVICE_FUNC(OnReadyAck);
    SERVICE_FUNC(OnLeaveGameAck);
    SERVICE_FUNC(OnNTFGameInit);
    SERVICE_FUNC(OnNTFDealCards);
    SERVICE_FUNC(OnNTFToken);
    SERVICE_FUNC(OnNTFPlayCards);
    SERVICE_FUNC(OnNTFPassCards);
    SERVICE_FUNC(OnNTFResetCards);
    SERVICE_FUNC(OnNTFResult);
    SERVICE_FUNC(OnNTFTableEvent);
    SERVICE_FUNC(OnNTFBombResult);
    SERVICE_FUNC(OnNTFBoardInfo);
    SERVICE_FUNC(OnNTFPropInfo);
    SERVICE_FUNC(OnNTFChat);
    
protected:
    unsigned int GetLastReceivedMsgSeqId();
    
private:
    GameServiceDelegate *m_pDelegate;
    unsigned int m_nLastSeqId;
    
public:
};
