//
//  MatchService.cpp
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#include "MatchService.h"

USING_NS_CC;
using namespace std;

static MatchService* s_MatchService = nullptr;

MatchService* MatchService::getInstance()
{
    if(!s_MatchService)
    {
        s_MatchService = new MatchService();
    }
    return s_MatchService;
}

void MatchService::ConfigureMsgs()
{
    RECEIVE_MSG(MSGID_MATCH_TABLE | MSGID_ACK,    ACKMatchTable,     MatchService::OnACKMatchTable);
}

void MatchService::SendMatchTable(int nRoomId)
{
    log("MatchService::SendMatchTable >>> roomid=%d", nRoomId);
    REQMatchTable req;
    req.set_roomid(nRoomId);
    SendMsg(&req, MSGID_MATCH_TABLE | MSGID_REQ);
}
