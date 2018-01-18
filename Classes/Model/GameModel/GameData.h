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
    virtual void reset();                                       //退出游戏重置游戏数据
    virtual void continueReset();                               //继续游戏重置游戏数据
//玩家信息数据相关  begin
public:
    void addUserInfo(KKGAMEUSERINFGO oUserInfo);                //添加一个玩家信息
    void leaveUserInfo(unsigned long long userId);              //删除一个玩家信息
protected:
    vector<KKGAMEUSERINFGO>        m_pUserInfoVec;              //玩家信息vec
//玩家数信息据相关  end

//玩家牌相关 begin
public:
    
//玩家牌相关 end
};
