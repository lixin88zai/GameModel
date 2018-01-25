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

class CardsNode;

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
//---------------------------------- 打出牌相关 BEGIN -------------------------------------//
public:
    void addOutCard(int cardId);
    void addOutCard(vector<int> cardIdVec);
protected:
    vector<Card*> m_oOutCardVec;
//---------------------------------- 打出牌相关 END ---------------------------------------//
//---------------------------------- 手牌相关 BEGIN ---------------------------------------//
public:
    void addHandCard(int cardId);
    void addHandCard(vector<int> cardIdVec, bool isShow = true);
    void addDrawCard(int cardId);   //添加摸牌
protected:
    vector<Card*> m_oHandCardVec;
    Card* m_oDrawCard;              //摸的牌
//---------------------------------- 手牌相关 END -----------------------------------------//
//---------------------------------- 碰牌相关 BEGIN ---------------------------------------//
public:
    void addPGCCard(PlayerOptionData optionData);
protected:
    vector<CardsNode*> m_oPGCCardVec;
//---------------------------------- 碰牌相关 END -----------------------------------------//
    
protected:
    Player_Seat_Type m_oSeatType;
    
//---------------------------------- 牌墙相关 BEGIN ---------------------------------------//
//---------------------------------- 牌墙相关 END -----------------------------------------//

};

class CardsNode : public Node
{
public:
    static CardsNode* create(Player_Seat_Type seatType, vector<int> cardIdVec, Game_Option_Type optionType, Gang_Type gangType);
    virtual bool init(Player_Seat_Type seatType, vector<int> cardIdVec, Game_Option_Type optionType, Gang_Type gangType);
    CardsNode();
    ~CardsNode();
    
    void pengUpGang();      //碰牌升级为杠牌
    const vector<int> getCardIdVec();
private:
    CC_SYNTHESIZE(Game_Option_Type, m_oOptionType, OptionType);
    CC_SYNTHESIZE(Gang_Type, m_oGangType, GangType);
    CC_SYNTHESIZE(int, m_nCardId, CardId);
    CC_SYNTHESIZE(Player_Seat_Type, m_oPlayerSeatType, PlayerSeatType);
    vector<int> m_oCardIdVec;
};
