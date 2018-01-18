//
//  SceneCommon.h
//  Gouji
//
//  Created by Joi Yao on 16/10/13.
//
//

#include "../cocos2d/cocos/base/CCRef.h"

#pragma once

#define CREATE_SCENE(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init()) \
{ \
pRet->autorelease(); \
return pRet; \
} \
else \
{ \
delete pRet; \
pRet = nullptr; \
return nullptr; \
} \
}

class SceneCommon : public cocos2d::Ref
{
public:
    static SceneCommon* create();
    virtual bool init();
    virtual void onRegister() {}
    virtual void onRemove() {}
    
    SceneCommon() {}
    ~SceneCommon() {}
};
