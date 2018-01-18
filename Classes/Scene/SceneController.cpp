//
//  SceneController.cpp
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#include "SceneController.h"
#include "Config/Config.h"
#include "AppDelegate.h"
#include "SceneModel.h"

using namespace std;

SceneController::SceneController()
:
Controller("SceneController")
{
}

void SceneController::listEventNames()
{
    m_oEventNames = {SCENE_EVT_SCENE_CHANGE};
}

void SceneController::onEventData(const string &sName, void *pUserData)
{
    if (sName == SCENE_EVT_SCENE_CHANGE)
    {
        SCENE* pData = static_cast<SCENE*>(pUserData);
        if(*pData == SceneModel::getInstance()->getCurrentScene())
        {
            //跳转的场景与当前场景相同，则返回
            return;
        }
        
        if (nullptr != pData)
        {
            onChange(*pData);
        }
        dispatchEvent(SCENE_NTF_SCENE_CHANGE);
    }
}

void SceneController::onChange(SCENE eScene)
{
    SceneModel::getInstance()->setCurrentScene(eScene);
}

void SceneController::onEnter()
{
    
}
