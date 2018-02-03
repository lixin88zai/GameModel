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
/*------------------------------牌墙相关参数----------------------------------------*/
//牌墙开始的位置
static const Size wall_card_size02 = Size(39, 60);
static const Size wall_card_size13 = Size(54, 46);

/*------------------------------出牌相关参数----------------------------------------*/
//打出的牌两行的z轴高度的起始高度
static const int out_line_z_start[4][2] = {{10, 20}, {10, 10}, {20, 10}, {10, 10}};
static const int out_line_z_ratio[4] = {0, 1, 0, -1};

/*------------------------------手牌相关参数----------------------------------------*/
static const int hand_z_ratio[4] = {0, -1, 0, 1};

/*------------------------------碰牌相关参数----------------------------------------*/
static const Vec2 pgnode_position_xy_ratio[4] = {
    Vec2(1, 0),
    Vec2(0, 1),
    Vec2(-1, 0),
    Vec2(0, -1),
};


bool GameDeck::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    this->setAnchorPoint(Vec2(0, 0));
    this->initStartPosition();
    return true;
}

void GameDeck::initStartPosition()
{
    //----------------------牌墙------------------------//
    wall_position_start[0] = Vec2(DEVICE_W / 2, 160 * SCALE_Y);
    wall_position_start[1] = Vec2(DEVICE_W - 310 * SCALE_X, DEVICE_H / 2);
    wall_position_start[2] = Vec2(DEVICE_W / 2, 517 * SCALE_Y);
    wall_position_start[3] = Vec2(300 * SCALE_X, DEVICE_H / 2);
    
    //牌墙两堆之间的偏移量
    wall_cardheap_offset[0] = Vec2(-39 * SCALE_X, 0);
    wall_cardheap_offset[1] = Vec2(0, 32 * SCALE_Y);
    wall_cardheap_offset[2] = Vec2(39 * SCALE_X, 0);
    wall_cardheap_offset[3] = Vec2(0, -32 * SCALE_Y);
    
    //牌墙上下两张牌的偏移量
    wall_updown_offset[0] = Vec2(0, -12);
    wall_updown_offset[1] = Vec2(0, -12);
    wall_updown_offset[2] = Vec2(0, -10);
    wall_updown_offset[3] = Vec2(0, -10);
    
    //牌墙每张牌的z轴系数
    wall_z_ratio[0] = 0;
    wall_z_ratio[1] = -1;
    wall_z_ratio[2] = 0;
    wall_z_ratio[3] = 1;
    
    //----------------------出牌------------------------//
    //出牌开始位置
    out_position_start[0] = Vec2(DEVICE_W / 2 - 39 * SCALE_X * 3.5, 300 * SCALE_Y);
    out_position_start[1] = Vec2(DEVICE_W - 435 * SCALE_X, DEVICE_H / 2 - 32 * SCALE_X * 2.5);
    out_position_start[2] = Vec2(DEVICE_W / 2 + 39 * SCALE_X * 3.5, DEVICE_H - 226 * SCALE_Y);
    out_position_start[3] = Vec2(DEVICE_W - 435 * SCALE_X, DEVICE_H / 2 + 32 * SCALE_X * 2.5);
    
    //两张牌之间的偏移量
    out_card_offset[0] = Vec2(39, 0);
    out_card_offset[1] = Vec2(0, 35 * SCALE_Y);
    out_card_offset[2] = Vec2(-39, 0);
    out_card_offset[3] = Vec2(0, -35 * SCALE_Y);
    //两行之间的偏移量
    out_line_offset[0] = Vec2(0, -48 * SCALE_Y);
    out_line_offset[1] = Vec2(51 * SCALE_X, 0);
    out_line_offset[2] = Vec2(0, 48 * SCALE_Y);
    out_line_offset[3] = Vec2(-51 * SCALE_X, 0);
    
    //----------------------手牌------------------------//
    hand_position_start[0] = Vec2(DEVICE_W - 320 * SCALE_X, 70 * SCALE_Y);
    hand_position_start[1] = Vec2(DEVICE_W - 200 * SCALE_X, DEVICE_H - 112 * SCALE_Y);
    hand_position_start[2] = Vec2(522 * SCALE_X, DEVICE_H - 92 * SCALE_Y);
    hand_position_start[3] = Vec2(200 * SCALE_X, 280 * SCALE_Y);
    
    hand_draw_position[0] = Vec2(DEVICE_W - 216 * SCALE_X, 70 * SCALE_Y);
    hand_draw_position[1] = Vec2(DEVICE_W - 200 * SCALE_X, DEVICE_H - 70 * SCALE_Y);
    hand_draw_position[2] = Vec2(452 * SCALE_X, DEVICE_H - 92 * SCALE_Y);
    hand_draw_position[3] = Vec2(200 * SCALE_X, 227 * SCALE_Y);
    
    hand_card_offset[0] = Vec2(86 * SCALE_X, 0);
    hand_card_offset[1] = Vec2(0, -30 * SCALE_Y);
    hand_card_offset[2] = Vec2(32 * SCALE_X, 0);
    hand_card_offset[3] = Vec2(0, 30 * SCALE_Y);
    
    //----------------------碰牌------------------------//
    pgnode_position_start[0] = Vec2(55 * SCALE_X, 61 * SCALE_Y);
    pgnode_position_start[1] = Vec2(DEVICE_W - 200 * SCALE_X, 197 * SCALE_Y);
    pgnode_position_start[2] = Vec2(DEVICE_W - 318 * SCALE_X, DEVICE_H - 89 * SCALE_Y);
    pgnode_position_start[3] = Vec2(190 * SCALE_X, DEVICE_H - 50 * SCALE_Y);
    
    pgnode_position_offset[0] = Vec2(20 * SCALE_X, 0);
    pgnode_position_offset[1] = Vec2(0, -13 * SCALE_Y);
    pgnode_position_offset[2] = Vec2(-8 * SCALE_X, 0);
    pgnode_position_offset[3] = Vec2(0, 13 * SCALE_Y);
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
    
    Vec2 startPosition = wall_position_start[m_oSeatType] + wall_cardheap_offset[m_oSeatType] * (wallCardTotalNum / 2 / 2) * (-1);
    for(int i = 0; i < wallCardTotalNum; i++)
    {
        Card* wallCard = Card::create(Card_Seat_Type::Card_Seat_Type_wall, m_oSeatType);
        wallCard->setPosition(startPosition + wall_cardheap_offset[m_oSeatType] * (i / 2) + wall_updown_offset[m_oSeatType] * (i % 2));
        if(i % 2 == 0)
        {
            wallCard->setLocalZOrder(100 + wall_z_ratio[m_oSeatType] * i + 1);
        }
        else
        {
            wallCard->setLocalZOrder(100 + wall_z_ratio[m_oSeatType] * i - 1);
        }
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
    addChild(outCard);
    
    //设置位置
    int outCardSize = (int)m_oOutCardVec.size();
    Vec2 startPosition = out_position_start[m_oSeatType];
    if(outCardSize + 1 > 8)
    {
        startPosition = out_position_start[m_oSeatType] - out_card_offset[m_oSeatType] + out_line_offset[m_oSeatType];
    }
    Vec2 position = startPosition +  out_card_offset[m_oSeatType] * (outCardSize % 8);
    outCard->setPosition(position);
    
    //设置z轴
    if(outCardSize / 8 < 2)
    {
        int z = out_line_z_start[m_oSeatType][outCardSize / 8] + out_line_z_ratio[m_oSeatType];
        outCard->setLocalZOrder(z);
    }
    
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
    addChild(handCard);
    handCard->setPosition(hand_position_start[m_oSeatType] + hand_card_offset[m_oSeatType] * m_oHandCardVec.size());
    //设置z轴
    handCard->setLocalZOrder(20 + hand_z_ratio[m_oSeatType]);
    
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
    m_oDrawCard->setPosition(hand_draw_position[m_oSeatType]);
    addChild(m_oDrawCard);
    m_oDrawCard->setLocalZOrder(20 + hand_z_ratio[m_oSeatType] * 20);
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
        cardsNode->setPosition(pgnode_position_start[m_oSeatType] + pgnode_position_offset[m_oSeatType] * m_oPGCCardVec.size() + Vec2(pgnode_position_xy_ratio[m_oSeatType].x *  cardsNode->getContentSize().width * m_oPGCCardVec.size(), pgnode_position_xy_ratio[m_oSeatType].y * cardsNode->getContentSize().height * m_oPGCCardVec.size()));
        addChild(cardsNode);
        cardsNode->setLocalZOrder(-100);
        
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
