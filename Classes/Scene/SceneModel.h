//
//  SceneModel.h
//  GouJi
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "Model.h"

#include "Config/AppDef.h"

class SceneModel : public Model
{
public:
    static SceneModel* getInstance();
    SceneModel();
    ~SceneModel() {}
    
    virtual void init() override;
    virtual void reset() override;
    
    CC_SYNTHESIZE_READONLY(SCENE, m_eSceneLast, LastScene)
    CC_SYNTHESIZE_READONLY(SCENE, m_eSceneCurr, CurrentScene);
    
    void setCurrentScene(SCENE eScene);
};
