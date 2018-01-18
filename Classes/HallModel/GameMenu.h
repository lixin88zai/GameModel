//
//  HallLayer.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "BaseClass/BaseLayer/NoFullLayer.h"

class GameMenu : public NoFullLayer
{
    enum ClickTag
    {
        ClickTag_JoinGame = 0,
        ClickTag_CreateGame,
    };
public:
    CREATE_FUNC(GameMenu);
    GameMenu();
    ~GameMenu();
    virtual void initContent();
    virtual void onMenuClick(cocos2d::Ref* pEvent, int eTag);
};
