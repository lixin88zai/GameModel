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


GameDeck::GameDeck():
m_oSeatType(Player_Seat_Type_null)
{
    
}

GameDeck::~GameDeck()
{
    
}
