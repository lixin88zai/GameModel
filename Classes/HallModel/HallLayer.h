//
//  HallLayer.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "BaseClass/Event/EventWrapper.h"
#include "BaseClass/TimeTick/TimeTick.h"
#include "extensions/cocos-ext.h"
#include "cocos2d.h"

class HallLayer : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(HallLayer);
    HallLayer();
    ~HallLayer();
    virtual bool init();    
    
    void initView();
};
