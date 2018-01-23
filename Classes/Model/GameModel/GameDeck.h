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
#include "Config/Config.h"

class GameDeck : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(GameDeck);
    GameDeck();
    ~GameDeck();
    virtual bool init();    
    
public:
    void reset();
//---------------------------------- 牌墙相关 ---------------------------------------//
public:
    void initWall();
    

protected:
    Player_Seat_Type m_oSeatType;

};
