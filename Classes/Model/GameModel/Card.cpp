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
#include "Util/Utils.h"


USING_NS_CC;

//记录,不同玩家、不同区域对应牌的背景图片名称
static const string static_card_back_name[4][4] = {
    {GAME_CARD_BACK_WALL_Up, GAME_CARD_FACE_WHITE_UP, GAME_CARD_STAND_OWN, GAME_CARD_FACE_WHITE_OWN},   //本家玩家区域
    {GAME_CARD_BACK_WALL_SIDE, GAME_CARD_FACE_WHITE_SIDE, GAME_CARD_STAND_SIDE, GAME_CARD_FACE_WHITE_SIDE},   //下家玩家区域
    {GAME_CARD_BACK_WALL_Up, GAME_CARD_FACE_WHITE_UP, GAME_CARD_STAND_UP, GAME_CARD_FACE_WHITE_UP},   //对家玩家区域
    {GAME_CARD_BACK_WALL_SIDE, GAME_CARD_FACE_WHITE_SIDE, GAME_CARD_STAND_SIDE, GAME_CARD_FACE_WHITE_SIDE}};  //上家玩家区域

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
    initBcak();
    initCardId();
    
    return true;
}


void Card::initBcak()        //加载牌背景
{
    if(m_oPlayerSeatType == Player_Seat_Type_null || m_oCardSeatType == Card_Seat_Type_null)
    {
        CCLOG("加载牌背景失败，资源越界!");
        return;
    }
    
    string spriteStr = static_card_back_name[m_oPlayerSeatType][m_oCardSeatType];
    auto backSprite = Sprite::create(spriteStr);
    auto oSize = backSprite->getContentSize();
    backSprite->setPosition(oSize.width / 2, oSize.height / 2);
    this->setContentSize(oSize);
    addChild(backSprite);
}
void Card::initCardId()      //加载牌正面id
{
    if(!GameConfig::cardIdIsValue(m_nCardId))
    {
        CCLOG("牌的id无效！");
        return;
    }
    
    string strName = "";
    if(m_oPlayerSeatType == Player_Seat_Type::Player_Seat_Type_0 || m_oPlayerSeatType == Player_Seat_Type::Player_Seat_Type_2)
    {
        strName = GAME_CARD_ID_NAME_STR_SHU;
    }
    else if(m_oPlayerSeatType == Player_Seat_Type::Player_Seat_Type_1 || m_oPlayerSeatType == Player_Seat_Type::Player_Seat_Type_3)
    {
        strName = GAME_CARD_ID_NAME_STR_HENG;
    }
    strName = util::str_format(strName.c_str(), m_nCardId);
    auto spriteName = util::GetSpriteFromFile(strName.c_str());
    addChild(spriteName);
    Size oSize = getContentSize();
    
    //设置缩放
    if(m_oCardSeatType == Card_Seat_Type::Card_Seat_Type_out
       || (m_oCardSeatType == Card_Seat_Type::Card_Seat_Type_peng && m_oPlayerSeatType != Player_Seat_Type_0))
    {
        if(m_oPlayerSeatType == Player_Seat_Type_0 || m_oPlayerSeatType == Player_Seat_Type_2)
        {
            spriteName->setScale(0.45);
            spriteName->setPosition(oSize.width / 2, (oSize.height - 12) / 2 + 12);
        }
        else if(m_oPlayerSeatType == Player_Seat_Type_1)
        {
            spriteName->setRotation(180);
            spriteName->setPosition(oSize.width / 2, (oSize.height - 15) / 2 + 13);
        }
        else if(m_oPlayerSeatType == Player_Seat_Type_3)
        {
            setPosition(oSize.width / 2, (oSize.height - 15) / 2 + 13);
        }
    }
    else if(m_oPlayerSeatType == Player_Seat_Type_0)
    {
        if(m_oCardSeatType == Card_Seat_Type::Card_Seat_Type_peng)
        {
            spriteName->setPosition(oSize.width / 2, (oSize.height - 20) / 2 + 20);
        }
        else if(m_oCardSeatType == Card_Seat_Type::Card_Seat_Type_hand)
        {
            spriteName->setPosition(oSize.width / 2, (oSize.height - 20) / 2);
        }
    }
}

int Card::getCardId()        //获取牌的id
{
    return m_nCardId;
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
