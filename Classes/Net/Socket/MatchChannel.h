//
//  MatchChannel.h
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#pragma once

#include "MatchService.h"
#include "BaseClass/Event/EventWrapper.h"

class MatchChannel :  public cocos2d::Ref, public MatchServiceDelegate, public EventWrapper
{
public:
    static MatchChannel* create();
    virtual bool init();
    
    virtual void OnACKMatchTable(Message* pMsg);
    
private:
    MatchChannel();
    ~MatchChannel();
};
