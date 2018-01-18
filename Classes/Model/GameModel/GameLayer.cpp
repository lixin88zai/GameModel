//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "GameLayer.h"
#include "Util/Utils.h"
#include "Config/Config.h"


USING_NS_CC;


bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    initView();
    return true;
}

void GameLayer::initView()
{
    Sprite* pSprite = Sprite::create(BG_HALL);
    pSprite->setScale(SCALE_X, SCALE_Y);
    pSprite->setAnchorPoint(Vec2::ZERO);
    pSprite->setPosition(Vec2::ZERO);
    addChild(pSprite);
}

GameLayer::GameLayer()
{
    
}

GameLayer::~GameLayer()
{
    
}
