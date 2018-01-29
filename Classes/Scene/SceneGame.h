//
//  SceneHall.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "SceneCommon.h"

class SceneGame : public SceneCommon
{
public:
    CREATE_SCENE(SceneGame);
    
    virtual void onRegister();
    virtual void onRemove();
    
private:
    SceneGame() {}
    ~SceneGame() {}
};
