//
//  MatchChannel.cpp
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#include "MatchChannel.h"
#include "Config/AppDef.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace std;

MatchChannel* MatchChannel::create()
{
    MatchChannel* pRet = new MatchChannel();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    pRet = nullptr;
    return nullptr;
}

bool MatchChannel::init()
{
    return true;
}

void MatchChannel::OnACKMatchTable(Message *pMsg)
{
    ACKMatchTable* pAck = static_cast<ACKMatchTable*>(pMsg);
    log("MatchChannel::OnACKMatchTable >>> code=%d, roomid=%d, tableid=%d, seatid=%d", pAck->code(), pAck->roomid(), pAck->tableid(), pAck->seatid());
    ACKMatchTable oData = *pAck;
}

MatchChannel::MatchChannel()
{
}

MatchChannel::~MatchChannel()
{
}
