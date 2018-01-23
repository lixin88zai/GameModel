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

class GameLayer : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(GameLayer);
    GameLayer();
    ~GameLayer();
    virtual bool init();    
    
    void initView();
};
