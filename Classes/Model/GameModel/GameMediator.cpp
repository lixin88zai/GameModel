//
//  HallMediator.cpp
//
//  Created by 赵靖 on 17/01/07.
//
//

#include "GameMediator.h"
#include "Util/Utils.h"
#include "Config/Config.h"
#include "Core/AppView.h"

USING_NS_CC;
using namespace std;
using namespace util;

string GameMediator::NAME = "HallMediator";

vector<string> GameMediator::listEventNames()
{
    return
    {
        HALL_MENU_CLICK,
    };
}

void GameMediator::handleEventData(const string &sEvent, void *pData)
{
    if (sEvent == HALL_MENU_CLICK)
    {
        MENU *pMenu = static_cast<MENU*>(pData);
    }
}

void GameMediator::onRegister()
{
    onRemove();
    //添加gameLayer
    m_oGameLayer = GameLayer::create();
    AppView::getInstance()->addTo(AppView::kLayerAds, m_oGameLayer);
    //添加玩家桌面
    for(int i = 0; i < 4; i++)
    {
        GameDeck* gameDeck = GameDeck::create();
        gameDeck->setSeatType(Player_Seat_Type(i));
        
        AppView::getInstance()->addTo(AppView::kLayerAds, gameDeck);
        m_oPlayerDeckVec.push_back(gameDeck);
    }
}

void GameMediator::onRemove()
{
    
}

void GameMediator::onExitComplete()
{

}


void GameMediator::onButtonClick(cocos2d::EventCustom* pEvent)
{
    
    
}

GameMediator::GameMediator()
{}

GameMediator::~GameMediator()
{
    onRemove();
}
