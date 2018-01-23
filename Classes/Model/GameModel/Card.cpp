//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "Card.h"
#include "Util/Utils.h"
#include "Config/Config.h"


USING_NS_CC;

//记录,不同玩家、不同区域对应牌的背景图片名称
static const string static_card_back_name[4][4] = {
    {"", "", "", ""},   //本家玩家区域
    {"", "", "", ""},   //下家玩家区域
    {"", "", "", ""},   //对家玩家区域
    {"", "", "", ""}};  //上家玩家区域

Card* Card::create(Card_Seat_Type cardSeatType, Player_Seat_Type playerSeatType, int cardId)
{
    Card* pCard = new Card();
    if(pCard->init(cardSeatType, playerSeatType, cardId))
    {
        pCard->autorelease();
        return pCard;
    }
    else
    {
        delete pCard;
        pCard = NULL;
        return NULL;
    }
}

bool Card::init(Card_Seat_Type cardSeatType, Player_Seat_Type playerSeatType, int cardId)
{
    if(!Node::init())
    {
        return false;
    }
    
    m_oCardSeatType = cardSeatType;
    m_oPlayerSeatType = playerSeatType;
    m_nCardId = cardId;
    
    
    
    
    return true;
}


void Card::initBcak()        //加载牌背景
{
    string spriteStr = "";
    
}
void Card::initCardId()      //加载牌正面id
{
    
}


Card::Card()
:m_oCardSeatType(Card_Seat_Type_null),
m_oPlayerSeatType(Player_Seat_Type_null),
m_nCardId(-1)
{
    
}
Card::~Card()
{
    
}
