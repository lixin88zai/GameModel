//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "GameMenu.h"
#include "Util/Utils.h"
#include "Config/Config.h"

void GameMenu::initContent()
{
    MenuItem* oMenuItem = LabelButton::createClickedGrayButton(HALL_BTN_JOIN_ROOM, CC_CALLBACK_1(GameMenu::onMenuClick, this, ClickTag_JoinGame));
    oMenuItem->setPosition(-oMenuItem->getContentSize().width / 2, 0);
    Menu* oMenu = Menu::create(oMenuItem, nullptr);
    oMenu->setPosition(0, 0);
    m_pContainer->addChild(oMenu);
}

void GameMenu::onMenuClick(cocos2d::Ref* pEvent, int eTag)
{
    util::MusicUtil::PlayEffectMusic(SFX_CLICK);
    switch(eTag)
    {
        case ClickTag_JoinGame:
        {
            CCLOG("点击了进入游戏");
        }break;
        case ClickTag_CreateGame:
        {
            
        }break;
        default:
            break;
    }
}

GameMenu::GameMenu()
{
    
}

GameMenu::~GameMenu()
{
    
}
