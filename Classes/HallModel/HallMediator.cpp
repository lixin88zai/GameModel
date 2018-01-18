//
//  HallMediator.cpp
//
//  Created by 赵靖 on 17/01/07.
//
//

#include "HallMediator.h"
#include "Util/Utils.h"
#include "Config/Config.h"
#include "HallLayer.h"
#include "Core/AppView.h"
#include "HallFooter.h"
#include "GameMenu.h"

USING_NS_CC;
using namespace std;
using namespace util;

string HallMediator::NAME = "HallMediator";

vector<string> HallMediator::listEventNames()
{
    return
    {
        HALL_MENU_CLICK,
    };
}

void HallMediator::handleEventData(const string &sEvent, void *pData)
{
    if (sEvent == HALL_MENU_CLICK)
    {
        MENU *pMenu = static_cast<MENU*>(pData);
    }
}

void HallMediator::onRegister()
{
    onRemove();
    HallLayer* oHallLayer = HallLayer::create();
    AppView::getInstance()->addTo(AppView::kLayerBackground, oHallLayer);
    
    HallFooter* oHallFooter = HallFooter::create();
    AppView::getInstance()->addTo(AppView::kLayerCanvas, oHallFooter);
    oHallFooter->setPosition(DEVICE_W / 2, 0);
    
    GameMenu* oGameMenu = GameMenu::create();
    oGameMenu->setPosition(DEVICE_W, DEVICE_H / 2);
    AppView::getInstance()->addTo(AppView::kLayerCanvas, oGameMenu);
}

void HallMediator::onRemove()
{
    
}

void HallMediator::onExitComplete()
{

}


void HallMediator::onButtonClick(cocos2d::EventCustom* pEvent)
{
    
    
}

HallMediator::HallMediator()
:
m_pHall(nullptr),
m_pDialogLayer(nullptr)
{}

HallMediator::~HallMediator()
{
    onRemove();
}
