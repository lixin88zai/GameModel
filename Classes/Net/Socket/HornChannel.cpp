//
//  HornChannel.cpp
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#include "HornChannel.h"
#include "AppDelegate.h"
#include "Util/Utils.h"
#include "Net/Socket/Protocol/ProtocolEnumDef.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace std;
using namespace util;

HornChannel* HornChannel::create()
{
    HornChannel* pRet = new HornChannel();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    pRet = nullptr;
    return nullptr;
}


bool HornChannel::init()
{
    return true;
}

//___________________________________________________________________________________________
// 使用喇叭通知
void HornChannel::OnNTFUseHorn(Message *pMsg)
{
    NTFUseHorn* pNtf = static_cast<NTFUseHorn*>(pMsg);
    log("HornChannel::OnNTFUseHorn>>>type=%d", pNtf->horn_type());
    KKHORNINFO oHornInfo = {};
    oHornInfo.nType = pNtf->horn_type();
    
    switch (oHornInfo.nType) {
        case horn_type_normal_announce:     // 普通系统公告
        case horn_type_serious_announce:    // 紧急系统公告
        {
            SystemHorn systemHorn;
            systemHorn.ParseFromString(pNtf->horn_content());
            oHornInfo.sText = systemHorn.content();
        }
            break;
        default:
            break;
    }
}

HornChannel::HornChannel()
{
}

HornChannel::~HornChannel()
{
}
