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

class Card : public cocos2d::Node, public EventWrapper, public TimeTick
{
public:
    static Card* create(Card_Seat_Type cardSeatType, Player_Seat_Type playerSeatType, int cardId = -1);
    virtual bool init(Card_Seat_Type cardSeatType, Player_Seat_Type playerSeatType, int cardId = -1);
    Card();
    ~Card();
public:
    void initBcak();        //加载牌背景
    void initCardId();      //加载牌正面id
    int getCardId();        //获取牌的id
private:
    Card_Seat_Type  m_oCardSeatType;   //牌区域状态
    Player_Seat_Type    m_oPlayerSeatType;  //玩家座位状态
    int m_nCardId;  //牌id
};
