//
//  SceneHall.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "SceneCommon.h"

class SceneHall : public SceneCommon
{
public:
    CREATE_SCENE(SceneHall);
    
    virtual void onRegister();
    virtual void onRemove();
    
private:
    SceneHall() {}
    ~SceneHall() {}
};
