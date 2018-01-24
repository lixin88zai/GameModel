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
#include "Card.h"

class GameDeck : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    CREATE_FUNC(GameDeck);
    GameDeck();
    ~GameDeck();
    virtual bool init();    
    
public:
    void reset();
//---------------------------------- 牌墙相关 BEGIN ---------------------------------------//
public:
    void initWall();        //加载牌墙
    void getWallCardVec(vector<Card*> &cardVec);    //获取牌墙，运用引用返回牌墙，对牌墙进行操作
    void showWall();
    void hideWall();
protected:
    vector<Card*>   m_oWallCardVec;     //牌墙队列
//---------------------------------- 牌墙相关 END -----------------------------------------//

    
    
protected:
    Player_Seat_Type m_oSeatType;
    
//---------------------------------- 牌墙相关 BEGIN ---------------------------------------//
//---------------------------------- 牌墙相关 END -----------------------------------------//

};
