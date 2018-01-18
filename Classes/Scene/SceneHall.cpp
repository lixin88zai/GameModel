//
//  SceneHall.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "SceneHall.h"
#include "Core/AppView.h"
#include "HallModel/HallMediator.h"

USING_NS_CC;

void SceneHall::onRegister()
{
    onRemove();
    AppView::getInstance()->registerMediator(HallMediator::create());
}

void SceneHall::onRemove()
{
    AppView::getInstance()->removeMediator(HallMediator::NAME);
}
