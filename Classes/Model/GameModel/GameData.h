//
//  HallLayer.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "Config/Config.h"

using namespace std;

class GameData
{
public:
    static GameData* getInstance();
    GameData();
    ~GameData();
    virtual bool init();
    virtual void reset();               //退出游戏重置游戏数据
    virtual void continueReset();       //继续游戏重置游戏数据
//-------------------------玩家信息数据相关  begin----------------------------//
public:
    void addPlayerInfo(KKPLAYERINFGO oUserInfo);                        //添加一个玩家信息
    void leavePlayerInfo(unsigned long long playerId);                  //删除一个玩家信息
    const KKPLAYERINFGO getPlayerInfo(unsigned long long playerId);     //通过玩家id获取信息
protected:
    vector<KKPLAYERINFGO>        m_pUserInfoVec;            //玩家信息vec
//-------------------------玩家信息数据相关  end------------------------------//
    
//-------------------------玩家牌相关 begin----------------------------------//
public:
    void setPlayerHandCards(unsigned long long playerId, vector<int> handsCards);               //设置玩家手牌
    void setPlayerCardsData(KKPLAYERCARDSDATA cardsData);                                       //设置玩家牌数据
    void getPlayerCardsData(unsigned long long playerId, KKPLAYERCARDSDATA& cardsData);         //通过id获取玩家牌数据
    const KKPLAYERCARDSDATA getPlayerCardsData(unsigned long long playerId);                    //获取玩家牌数据
protected:
    vector<KKPLAYERCARDSDATA>          m_pPlayersCardsVec;                                      //玩家牌信息
//-------------------------玩家牌相关 end------------------------------------//
//-------------------------玩家操作相关 begin--------------------------------//
public:
    void doOption(KKPLAYEROPTIONDATA option);
//-------------------------玩家操作相关 end----------------------------------//
};
