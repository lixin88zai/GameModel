//
//  SceneHall.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "SceneGame.h"
#include "Core/AppView.h"
#include "Model/GameModel/GameMediator.h"

USING_NS_CC;

void SceneGame::onRegister()
{
    onRemove();
    AppView::getInstance()->registerMediator(GameMediator::create());
}

void SceneGame::onRemove()
{
    AppView::getInstance()->removeMediator(GameMediator::NAME);
}
