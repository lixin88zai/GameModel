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

class GamePlayerDeck : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(GamePlayerDeck);
    GamePlayerDeck();
    ~GamePlayerDeck();
    virtual bool init();    
    
    void initView();
};
