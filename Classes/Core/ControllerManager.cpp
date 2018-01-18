//
//  ControllerManager.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-26.
//
//

#include "ControllerManager.h"
#include "Config/Config.h"
#include "Scene/SceneController.h"


USING_NS_CC;
using namespace std;

static ControllerManager* s_ControllerManager = nullptr;

ControllerManager* ControllerManager::getInstance()
{
    if(!s_ControllerManager)
    {
        s_ControllerManager = new ControllerManager();
    }
    return s_ControllerManager;
}

ControllerManager::ControllerManager()
{
}

ControllerManager::~ControllerManager()
{
    m_obControllerMap.clear();
}

void ControllerManager::initialize()
{
    // 场景业务
    registerController(new SceneController());
}

void ControllerManager::registerController(Controller *pController)
{
    if (nullptr == pController)
    {
        return;
    }
    pController->listEventNames();
    vector<string> oEventNames = pController->getEventNames();
    for (size_t i = 0; i < oEventNames.size(); i ++)
    {
        mapController(oEventNames[i], pController);
    }
}

void ControllerManager::mapController(const string &sEventName, Controller *pController)
{
    m_obControllerMap.insert(sEventName, pController);
    addEventListener(sEventName, CC_CALLBACK_1(ControllerManager::onEventReceived, this));
}

void ControllerManager::onEventReceived(EventCustom *pEvent)
{
    auto sEventName = pEvent->getEventName();
    auto pController = m_obControllerMap.at(sEventName);
    if (pController != nullptr)
    {
        pController->execute(sEventName, static_cast<ValueMap *>(pEvent->getUserData()));
    }
}
