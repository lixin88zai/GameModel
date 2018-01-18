//
//  GameChannel.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/27.
//
//

#pragma once
#include "Net/Socket/GameService.h"
#include "BaseClass/Event/EventWrapper.h"

#define FORMAT_ERROR            "出错了，请向客服反馈（问题代码：%s）"
#define MAX_REJOIN              3

class GameChannel : public cocos2d::Ref, public GameServiceDelegate, public EventWrapper
{
public:
    static GameChannel* create();
    virtual bool init();
    
    void DoPrivyJoinGame();
    void DoRejoinGame();
    void ConnectBroken();
    void CheckInGame();

public:
    virtual void OnPrivyJoinGameAck(Message* pMsg);
    virtual void OnRejoinGameAck(Message *pMsg);
    virtual void OnReadyAck(Message* pMsg);
    virtual void OnLeaveGameAck(Message* pMsg);
    virtual void OnNTFGameInit(Message* pMsg);
    virtual void OnNTFToken(Message* pMsg);
    virtual void OnNTFDealCards(Message* pMsg);
    virtual void OnNTFPlayCards(Message* pMsg);
    virtual void OnNTFPassCards(Message* pMsg);
    virtual void OnNTFResetCards(Message* pMsg);
    virtual void OnNTFResult(Message* pMsg);
    virtual void OnNTFTableEvent(Message* pMsg);
        
    // 断线重连
    virtual void OnNTFBoardInfo(Message* pMsg);
    
    // 普通聊天
    virtual void OnNTFChat(Message* pMsg);
    
    virtual void OnNTFPropInfo(Message* pMsg);

    void OnEventLogin(TableEventItem *pTableEvent);             // 玩家登陆
    void OnEventJoinTable(TableEventItem *pTableEvent);         // 玩家加入桌子
    void OnEventSitDown(TableEventItem *pTableEvent);           // 玩家坐下
    void OnEventReady(TableEventItem *pTableEvent);             // 玩家ready
    void OnEventCancelReady(TableEventItem *pTableEvent);       // 玩家取消ready
    void OnEventStandUp(TableEventItem *pTableEvent);           // 玩家站起
    void OnEventLeaveTable(TableEventItem *pTableEvent);        // 玩家离开桌子
    void OnEventViewJoinTable(TableEventItem *pTableEvent);     // 旁观者进入
    void OnEventViewLeaveTable(TableEventItem *pTableEvent);    // 旁观者退出
    void OnEventKickOff(TableEventItem *pTableEvent);           // 玩家被踢出
    void OnEventOffline(TableEventItem *pTableEvent);           // 玩家断线
    void OnEventReconnect(TableEventItem *pTableEvent);         // 断线重连
    void OnEventGameStart(TableEventItem *pTableEvent);         // 游戏开始
    void OnEventGameEnd(TableEventItem *pTableEvent);           // 游戏结束
    void OnEventGameInfoChange(TableEventItem *pTableEvent);    // 玩家gameinfo改变
    void OnEventUserInfoChange(TableEventItem *pTableEvent);    // 玩家userinfo改变
    void OnEventTableInfoChange(TableEventItem *pTableEvent);   // 桌子信息变化
    void OnEventTableInfoShow(TableEventItem *pTableEvent);     // 玩家showinfo显示
    void onLogUserId(const std::string& sEventName, unsigned long long nUserId);
    void onError(const std::string& sMessage);
    std::string generateErrorMessage(int nMsgId, int nResult, int nBaseMsgId = MSGID_BASE_GS_CLIENT);
    
private:
    GameChannel();
    ~GameChannel();
    
private:
    bool    m_bJoined;
    bool    m_bConnBroken;
    bool    m_bRejoin;
    int     m_nCntRejoin;
};
