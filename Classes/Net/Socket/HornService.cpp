//
//  HornService.cpp
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#include "HornService.h"

static HornService* s_HornService = nullptr;

HornService* HornService::getInstance()
{
    if(!s_HornService)
    {
        s_HornService = new HornService();
    }
    return s_HornService;
}

void HornService::ConfigureMsgs()
{
    RECEIVE_MSG(MSGID_USE_HORN | MSGID_NTF,    NTFUseHorn,     HornService::OnNTFUseHorn);
}
