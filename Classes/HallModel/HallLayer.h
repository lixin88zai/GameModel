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

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class HallLayer : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(HallLayer);
    HallLayer();
    ~HallLayer();
    virtual bool init();    
    
    void initView();
    
private:
    void buttonTouched(Ref* sender,TouchEventType touchType);
};
