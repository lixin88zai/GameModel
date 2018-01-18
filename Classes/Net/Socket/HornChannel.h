//
//  HornChannel.h
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#pragma once

#include "HornService.h"
#include "BaseClass/Event/EventWrapper.h"

class HornChannel : public cocos2d::Ref, public HornServiceDelegate, public EventWrapper
{
public:
    static HornChannel* create();
    virtual bool init();
    
private:
    void OnNTFUseHorn(Message *pMsg);
    
    HornChannel();
    ~HornChannel();
};
