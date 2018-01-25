//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "GameDeck.h"
#include "Util/Utils.h"
#include "Config/Config.h"
#include "GameData.h"


USING_NS_CC;

//牌墙开始的位置
static const Vec2 wall_position_start[4] = {
    Vec2(DEVICE_W / 2 + 252 * SCALE_FIT, 160 * SCALE_Y),
    Vec2(DEVICE_W - 310 * SCALE_X, 338.5 * SCALE_Y + 15.5 * (13 - 1) * SCALE_FIT),
    Vec2(DEVICE_W / 2 - 252 * SCALE_FIT, 517 * SCALE_Y),
    Vec2(300 * SCALE_X, 338.5 * SCALE_Y - 15.5 * (13 - 1) * SCALE_FIT)
};
static const Vec2 wall_poistion_offset[] = {
    Vec2(0, 0),
    Vec2(0, 0),
    Vec2(0, 0),
    Vec2(0, 0)
};

bool GameDeck::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    return true;
}

void GameDeck::initWall()        //加载牌墙
{
    int cardTotalNum = GameData::getInstance()->getCardTotalNum();
    int playersNum = GameData::getInstance()->getPlayerTotalNum();
    int wallCardTotalNum = cardTotalNum / playersNum;
    if(wallCardTotalNum % 2 != 0)
    {
        if(m_oSeatType == Player_Seat_Type::Player_Seat_Type_0 || m_oSeatType == Player_Seat_Type::Player_Seat_Type_2)
        {
            wallCardTotalNum += 1;
        }
        else
        {
            wallCardTotalNum -= 1;
        }
    }
    for(int i = 0; i < wallCardTotalNum; i++)
    {
        Card* wallCard = Card::create(Card_Seat_Type::Card_Seat_Type_wall, m_oSeatType);
        wallCard->setPosition(wall_position_start[m_oSeatType] + Vec2(i / 2 * wall_poistion_offset[m_oSeatType].x, i % 2 * wall_poistion_offset[m_oSeatType].y));
        wallCard->setLocalZOrder(i % 2 * (-1));
        addChild(wallCard);
        
        m_oWallCardVec.push_back(wallCard);
    }
}

void GameDeck::getWallCardVec(vector<Card*> &cardVec)    //获取牌墙，运用引用返回牌墙，对牌墙进行操作
{
    cardVec = m_oWallCardVec;
}

void GameDeck::showWall()
{
    for(int i = 0; i < m_oWallCardVec.size(); i++)
    {
        m_oWallCardVec.at(i)->setVisible(true);
    }
}

void GameDeck::hideWall()
{
    for(int i = 0; i < m_oWallCardVec.size(); i++)
    {
        m_oWallCardVec.at(i)->setVisible(false);
    }
}

void GameDeck::addOutCard(int cardId)
{
    Card* outCard = Card::create(Card_Seat_Type::Card_Seat_Type_out, m_oSeatType, cardId);
    outCard->setPosition(0, 0);
    addChild(outCard);
    
    m_oOutCardVec.push_back(outCard);
}
void GameDeck::addOutCard(vector<int> cardIdVec)
{
    for(int i = 0; i < cardIdVec.size(); i++)
    {
        addOutCard(cardIdVec.at(i));
    }
}

void GameDeck::addHandCard(int cardId)
{
    Card* handCard = Card::create(Card_Seat_Type::Card_Seat_Type_hand, m_oSeatType);
    handCard->setPosition(Vec2(0, 0));
    addChild(handCard);
    
    m_oHandCardVec.push_back(handCard);
}

void GameDeck::addHandCard(vector<int> cardIdVec, bool isShow)
{
    for(int i = 0; i < cardIdVec.size(); i++)
    {
        addHandCard(cardIdVec.at(i));
    }
}

void GameDeck::addDrawCard(int cardId)   //添加摸牌
{
    m_oDrawCard = Card::create(Card_Seat_Type::Card_Seat_Type_hand, m_oSeatType);
    m_oDrawCard->setPosition(Vec2(0, 0));
    addChild(m_oDrawCard);
    
    m_oHandCardVec.push_back(m_oDrawCard);
}

void GameDeck::addPGCCard(PlayerOptionData optionData)
{
    if(optionData.oOptionType == Game_Option_Type::Game_Option_Type_gang
       && optionData.oGangType == Gang_Type::Gang_Type_bu)
    {
        for(int i = 0; i < m_oPGCCardVec.size(); i++)
        {
            if(m_oPGCCardVec.at(i)->getCardId() == optionData.nCardId)
            {
                m_oPGCCardVec.at(i)->pengUpGang();
            }
        }
    }
    else
    {
        CardsNode* cardsNode = CardsNode::create(m_oSeatType, optionData.oCardsVec.at(0), optionData.oOptionType, optionData.oGangType);
        cardsNode->setPosition(Vec2(0, 0));
        addChild(cardsNode);
        
        m_oPGCCardVec.push_back(cardsNode);
    }
}


GameDeck::GameDeck():
m_oSeatType(Player_Seat_Type_null)
{
    
}

GameDeck::~GameDeck()
{
    
}



//----------------------------------------------------------------------------------//
//-----------------------------------牌组--------------------------------------------//
//----------------------------------------------------------------------------------//

CardsNode* CardsNode::create(Player_Seat_Type seatType, vector<int> cardIdVec, Game_Option_Type optionType, Gang_Type gangType)
{
    CardsNode* cardNode = new CardsNode();
    if(cardNode->init(seatType, cardIdVec, optionType, gangType))
    {
        return cardNode;
    }
    delete cardNode;
    cardNode = NULL;
    return NULL;
}

bool CardsNode::init(Player_Seat_Type seatType, vector<int> cardIdVec, Game_Option_Type optionType, Gang_Type gangType)
{
    if(!Node::init())
    {
        return false;
    }
    
    m_oPlayerSeatType = seatType;
    m_oOptionType = optionType;
    m_oGangType = gangType;
    m_oCardIdVec = cardIdVec;
    
    if(optionType == Game_Option_Type::Game_Option_Type_peng
       || optionType == Game_Option_Type::Game_Option_Type_gang)
    {
        m_nCardId = cardIdVec.at(0);
    }
    
    if(optionType == Game_Option_Type::Game_Option_Type_chi || optionType == Game_Option_Type::Game_Option_Type_peng)
    {
        for(int i = 0; i < cardIdVec.size(); i++)
        {
            Card* card = Card::create(Card_Seat_Type::Card_Seat_Type_peng, m_oPlayerSeatType, cardIdVec.at(i));
            card->setPosition(Vec2(card->getContentSize().width * i, card->getContentSize().height / 2));
            addChild(card);
        }
    }
    else if(optionType == Game_Option_Type::Game_Option_Type_gang)
    {
        for(int i = 0; i < 3; i++)
        {
            Card* card = Card::create(Card_Seat_Type::Card_Seat_Type_peng, m_oPlayerSeatType, cardIdVec.at(i));
            card->setPosition(Vec2(card->getContentSize().width * i, card->getContentSize().height / 2));
            addChild(card);
        }
        
        Card* card = Card::create(Card_Seat_Type::Card_Seat_Type_peng, m_oPlayerSeatType, cardIdVec.at(0));
        card->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height / 2 + 10));
        addChild(card);
    }
    return true;
}

void CardsNode::pengUpGang()
{
    if(m_oOptionType != Game_Option_Type::Game_Option_Type_peng)
    {
        CCLOG("碰牌升级为杠牌失败，本牌组不是碰牌");
        return;
    }
    m_oOptionType = Game_Option_Type::Game_Option_Type_gang;
    
    Card* card = Card::create(Card_Seat_Type::Card_Seat_Type_peng, m_oPlayerSeatType, m_oCardIdVec.at(0));
    card->setPosition(Vec2(card->getContentSize().width, card->getContentSize().height / 2 + 10));
    addChild(card);
}

const vector<int> CardsNode::getCardIdVec()
{
    return m_oCardIdVec;
}

CardsNode::CardsNode():
m_oOptionType(Game_Option_Type_null),
m_oGangType(Gang_Type_null),
m_nCardId(-1),
m_oPlayerSeatType(Player_Seat_Type_null),
m_oCardIdVec({})
{
    
}
CardsNode::~CardsNode()
{
    
}
