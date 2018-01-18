//
//  SceneCommon.cpp
//  Gouji
//
//  Created by Joi Yao on 16/10/13.
//
//

#include "SceneCommon.h"

USING_NS_CC;

SceneCommon* SceneCommon::create()
{
    SceneCommon* pRet = new SceneCommon();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    pRet = nullptr;
    return nullptr;
}

bool SceneCommon::init()
{
    return true;
}