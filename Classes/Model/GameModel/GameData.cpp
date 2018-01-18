//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "GameData.h"
#include "Util/Utils.h"
#include "Config/Config.h"


USING_NS_CC;


static GameData* m_pGameDataInstance = nullptr;
GameData* GameData::getInstance()
{
    if(m_pGameDataInstance == nullptr)
    {
        m_pGameDataInstance = new GameData();
        if(m_pGameDataInstance->init())
        {
            return m_pGameDataInstance;
        }
        else
        {
            CC_SAFE_DELETE(m_pGameDataInstance);
            m_pGameDataInstance = nullptr;
            return nullptr;
        }
    }
    return m_pGameDataInstance;
}

void GameData::addPlayerInfo(KKPLAYERINFGO oUserInfo)
{
    for(int i = 0; i < m_pUserInfoVec.size(); i++)
    {
        if(m_pUserInfoVec.at(i).nUserId == oUserInfo.nUserId)
        {
            m_pUserInfoVec.at(i) = oUserInfo;
            return;
        }
    }
    m_pUserInfoVec.push_back(oUserInfo);
}

void GameData::leavePlayerInfo(unsigned long long playerId)
{
    for(int i = 0; i < m_pUserInfoVec.size(); i++)
    {
        if(m_pUserInfoVec.at(i).nUserId == playerId)
        {
            m_pUserInfoVec.erase(m_pUserInfoVec.begin() + i);
            return;
        }
    }
}

void GameData::setPlayerHandCards(unsigned long long playerId, vector<int> handsCards)       //设置玩家手牌
{
    for(int i = 0; i < m_pPlayersCardsVec.size(); i++)
    {
        if(m_pPlayersCardsVec.at(i).nUserId == playerId)
        {
            m_pPlayersCardsVec.at(i).oHandsCardVec = handsCards;
            return; //存在赋值后返回
        }
    }
    
    //不存在，生成玩家牌信息，放在列表中
    KKPLAYERCARDSDATA gameCardData;
    gameCardData.nUserId = playerId;
    gameCardData.oHandsCardVec = handsCards;
    m_pPlayersCardsVec.push_back(gameCardData);
}
void GameData::setPlayerCardsData(KKPLAYERCARDSDATA cardsData)                                  //设置玩家牌数据
{
    for(int i = 0; i < m_pPlayersCardsVec.size(); i++)
    {
        if(m_pPlayersCardsVec.at(i).nUserId == cardsData.nUserId)
        {
            m_pPlayersCardsVec.at(i) = cardsData;
            return; //存在赋值后返回
        }
    }
    
    //不存在，生成玩家牌信息，放在列表中
    m_pPlayersCardsVec.push_back(cardsData);
}
const KKPLAYERCARDSDATA GameData::getPlayerCardsData(unsigned long long userId)                //获取玩家牌数据
{
    for(int i = 0; i < m_pPlayersCardsVec.size(); i++)
    {
        if(m_pPlayersCardsVec.at(i).nUserId == userId)
        {
            //存在返回
            return m_pPlayersCardsVec.at(i);
        }
    }
    //不存在打印信息，返回空值
    CCLOG("玩家（userId=%lld）不存在,(1function=getUserCardData)返回空值", userId);
    return {};
}

/*
 描述：通过id获取玩家牌数据
 参数:
    playerId：玩家id
    cardData：保存玩家牌信息，此时可以进行修改玩家牌信息
 */
void GameData::getPlayerCardsData(unsigned long long playerId, KKPLAYERCARDSDATA& cardsData)
{
    for(int i = 0; i < m_pPlayersCardsVec.size(); i++)
    {
        if(m_pPlayersCardsVec.at(i).nUserId == playerId)
        {
            //存在 赋值参数cardData
            cardsData = m_pPlayersCardsVec.at(i);
        }
    }
    //不存在打印信息
    CCLOG("玩家（playerId=%lld）不存在,(2function=getGameCardData)返回空值", playerId);
}

void GameData::doOption(KKPLAYEROPTIONDATA option)
{
    KKPLAYERCARDSDATA cardsData = {};
    getPlayerCardsData(option.userId, cardsData);
    
}

void GameData::reset()
{
    continueReset();
    m_pUserInfoVec.clear();
}

void GameData::continueReset()
{
    m_pPlayersCardsVec.clear();
}

bool GameData::init()
{
    continueReset();
    m_pUserInfoVec.clear();
    return true;
}

GameData::GameData()
{
    
}

GameData::~GameData()
{
    
}
