//
//  SceneModel.cpp
//  GouJi
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "SceneModel.h"

USING_NS_CC;

static SceneModel* s_pSceneModel = nullptr;
SceneModel* SceneModel::getInstance()
{
    if(!s_pSceneModel)
    {
        s_pSceneModel = new SceneModel();
        s_pSceneModel->init();
    }
    return s_pSceneModel;
}

SceneModel::SceneModel()
:
Model("SceneModel"),
m_eSceneCurr(kSceneUnknown),
m_eSceneLast(kSceneUnknown)
{
}

void SceneModel::init()
{
    m_eSceneLast = kSceneUnknown;
    m_eSceneCurr = kSceneSplash;
}

void SceneModel::reset()
{
    m_eSceneLast = kSceneUnknown;
    m_eSceneCurr = kSceneUnknown;
}

void SceneModel::setCurrentScene(SCENE eScene)
{
//    log("SceneModel::setCurrentScene >>> last=%d, curr=%d", m_eSceneLast, m_eSceneCurr);
    m_eSceneLast = m_eSceneCurr;
    m_eSceneCurr = eScene;
    log("SceneModel::setCurrentScene >>> last=%d, curr=%d", m_eSceneLast, m_eSceneCurr);
}
