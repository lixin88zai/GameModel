//
//  GameChannelTable.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/11/8.
//
//

#include "GameChannel.h"
#include "AppDelegate.h"
#include "Util/Utils.h"
#include "Config/Config.h"
#include "Net/Socket/Protocol/ProtocolEnumDef.h"

USING_NS_CC;
using namespace util;
using namespace std;

void GameChannel::OnNTFTableEvent(Message *pMsg)
{
    NTFTableEvent *pNtf = (NTFTableEvent*)pMsg;
    int nLen = pNtf->event_list_size();
    log("GameChannel::OnNTFTableEvent >>> len=%d", nLen);
    for (int i = 0; i < nLen; i ++)
    {
        TableEventItem oEvent = pNtf->event_list(i);
        switch (oEvent.event_type())
        {
            case table_event_login:
                OnEventLogin(&oEvent);
                break;
            case table_event_join_table:
                OnEventJoinTable(&oEvent);
                break;
            case table_event_sit_down:
                OnEventSitDown(&oEvent);
                break;
            case table_event_ready:
                OnEventReady(&oEvent);
                break;
            case table_event_cancel_ready:
                OnEventCancelReady(&oEvent);
                break;
            case table_event_stand_up:
                OnEventStandUp(&oEvent);
                break;
            case table_event_leave_table:
                OnEventLeaveTable(&oEvent);
                break;
            case table_event_viewer_join_table:
                OnEventViewJoinTable(&oEvent);
                break;
            case table_event_viewer_leave_table:
                OnEventViewLeaveTable(&oEvent);
                break;
            case table_event_kick_off:
                OnEventKickOff(&oEvent);
                break;
            case table_event_offline:
                OnEventOffline(&oEvent);
                break;
            case table_event_reconnect:
                OnEventReconnect(&oEvent);
                break;
            case table_event_game_start:
                OnEventGameStart(&oEvent);
                break;
            case table_event_game_end:
                OnEventGameEnd(&oEvent);
                break;
            case table_event_gameinfo_change:
                OnEventGameInfoChange(&oEvent);
                break;
            case table_event_userinfo_change:
                OnEventUserInfoChange(&oEvent);
                break;
            case table_event_tableinfo_change:
                OnEventTableInfoChange(&oEvent);
                break;
            case table_event_showinfo_change:
                OnEventTableInfoShow(&oEvent);
                break;
            default:
                break;
        }
    }
}

void GameChannel::OnEventLogin(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventLogin", pTableEvent->user_id());
    
}

void GameChannel::OnEventJoinTable(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventJoinTable", pTableEvent->user_id());
    unsigned long long nUserId = pTableEvent->user_id();
}

void GameChannel::OnEventSitDown(TableEventItem *pTableEvent)
{
    unsigned long long nUserId = pTableEvent->user_id();
    onLogUserId("OnEventSitDown", nUserId);
}

void GameChannel::OnEventReady(TableEventItem *pTableEvent)
{
    unsigned long long nUserId = pTableEvent->user_id();
    onLogUserId("OnEventReady", nUserId);
}

void GameChannel::OnEventCancelReady(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventCancelReady", pTableEvent->user_id());
}

void GameChannel::OnEventStandUp(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventStandUp", pTableEvent->user_id());
}

void GameChannel::OnEventLeaveTable(TableEventItem *pTableEvent)
{
    // 机器人被踢走这个TCP消息
    unsigned long long nUserId = pTableEvent->user_id();
    onLogUserId("OnEventLeaveTable", nUserId);

}

void GameChannel::OnEventViewJoinTable(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventViewJoinTable", pTableEvent->user_id());
}

void GameChannel::OnEventViewLeaveTable(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventViewLeaveTable", pTableEvent->user_id());
}

void GameChannel::OnEventKickOff(TableEventItem *pTableEvent)
{
    unsigned long long nUserId = pTableEvent->kicked_user_id();
    onLogUserId("OnEventKickOff", nUserId);

}

void GameChannel::OnEventOffline(TableEventItem *pTableEvent)
{
    unsigned long long nUserId = pTableEvent->user_id();
    onLogUserId("OnEventOffline", nUserId);
   
}

void GameChannel::OnEventReconnect(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventReconnect", pTableEvent->user_id());
    unsigned long long nUserId = pTableEvent->user_id();
   }

void GameChannel::OnEventGameStart(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventGameStart", pTableEvent->user_id());
}

void GameChannel::OnEventGameEnd(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventGameEnd", pTableEvent->user_id());
}

void GameChannel::OnEventGameInfoChange(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventGameInfoChange", pTableEvent->user_id());
    PlayerGameInfo oPlayerInfo;
    oPlayerInfo.ParseFromString(pTableEvent->pb_buffer());
    unsigned long long nUserId = oPlayerInfo.user_id();
    int nScore = oPlayerInfo.score();
}

void GameChannel::OnEventUserInfoChange(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventUserInfoChange", pTableEvent->user_id());
    UserInfo oUserInfo;
    oUserInfo.ParseFromString(pTableEvent->pb_buffer());
    KKUSERINFO oData;
    oData.nUserId = pTableEvent->user_id();
    oData.sFaceURL = oUserInfo.face();
    oData.sFaceId = "";
    oData.nGender = oUserInfo.gender();
    //oData.sNick = str_format("玩家%llu", oData.nUserId);
    oData.sNick = oUserInfo.nick();
    oData.sIP = oUserInfo.loginip();


    KKFACE oFaceData;
    oFaceData.faceName = "";
    oFaceData.faceUrl = oData.sFaceURL;
    oFaceData.userId = oData.nUserId;
//    dispatchEvent(EVT_GET_FACE, &oFaceData);
//    dispatchEvent(NTF_USERINFO_UPDATE, &oData);

}

void GameChannel::OnEventTableInfoChange(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventTableInfoChange", pTableEvent->user_id());
    TableInfo oTableInfo;
    oTableInfo.ParseFromString(pTableEvent->pb_buffer());

}

void GameChannel::OnEventTableInfoShow(TableEventItem *pTableEvent)
{
    onLogUserId("OnEventTableInfoShow", pTableEvent->user_id());
}

void GameChannel::onLogUserId(const string &sEventName, unsigned long long nUserId)
{
    log("GameChannel::%s >>> u=%llu", sEventName.c_str(), nUserId);
}
