//
//  SceneMediator.cpp
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#include "SceneMediator.h"
#include "Config/Config.h"
#include "AppDelegate.h"
#include "SceneHall.h"
#include "Scene/SceneGame.h"
USING_NS_CC;
using namespace std;
using namespace profile;
string SceneMediator::NAME = "SceneMediator";

vector<string> SceneMediator::listEventNames()
{
    return
    {
        SCENE_NTF_SCENE_CHANGE
    };
}

void SceneMediator::handleEventData(const string &sEvent, void *pData)
{
    if (sEvent == SCENE_NTF_SCENE_CHANGE)
    {
        onChange();
    }
}

void SceneMediator::onClear()
{
    if (m_pScene)
    {
        m_pScene->onRemove();
        CC_SAFE_RELEASE_NULL(m_pScene);
    }
}

void SceneMediator::onChange()
{
    onClear();
    SCENE eCurr = SceneModel::getInstance()->getCurrentScene();
    if (eCurr == kSceneSplash)
    {
//        m_pScene = SceneSplash::create();
    }
    else if(eCurr == kSceneHall)
    {
        m_pScene = SceneHall::create();
    }
    else if(eCurr == kSceneGame)
    {
        m_pScene = SceneGame::create();
    }
    
    if (m_pScene)
    {
        m_pScene->retain();
        m_pScene->onRegister();
    }
}

SceneCommon* SceneMediator::getSceneGame(int nPlayType)
{
    SceneCommon* pScene = nullptr;
    return pScene;
}

SceneMediator::SceneMediator()
:
m_pScene(nullptr)
{

}

SceneMediator::~SceneMediator()
{
    CC_SAFE_RELEASE_NULL(m_pScene);
}
