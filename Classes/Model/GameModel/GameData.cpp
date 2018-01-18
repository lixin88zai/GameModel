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

void GameData::addUserInfo(KKGAMEUSERINFGO oUserInfo)
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

void GameData::leaveUserInfo(unsigned long long userId)
{
    for(int i = 0; i < m_pUserInfoVec.size(); i++)
    {
        if(m_pUserInfoVec.at(i).nUserId == userId)
        {
            m_pUserInfoVec.erase(m_pUserInfoVec.begin() + i);
            return;
        }
    }
}

void GameData::reset()
{
    
}

void GameData::continueReset()
{
    
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
