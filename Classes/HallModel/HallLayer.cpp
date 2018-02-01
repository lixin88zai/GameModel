//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "HallLayer.h"
#include "Util/Utils.h"
#include "Config/Config.h"





bool HallLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    initView();
    return true;
}

void HallLayer::initView()
{
    Sprite* pSprite = Sprite::create(BG_HALL);
    pSprite->setScale(SCALE_X, SCALE_Y);
    pSprite->setAnchorPoint(Vec2::ZERO);
    pSprite->setPosition(Vec2::ZERO);
    addChild(pSprite);
    
    Button* button = Button::create(HALL_BTN_STARTGAME, HALL_BTN_STARTGAME);
    button->addTouchEventListener(this, toucheventselector(HallLayer::buttonTouched));
    button->setPosition(Vec2(DEVICE_W /2, DEVICE_H / 2));
    button->setTag(0);
    addChild(button);
}

void HallLayer::buttonTouched(Ref* sender,TouchEventType touchType)
{
    Node* node = static_cast<Node*>(sender);
    int tag = node->getTag();
    switch(tag)
    {
        case 0:
        {
            Value oData = Value(kSceneGame);
            dispatchEvent(SCENE_EVT_SCENE_CHANGE, &oData);
        }break;
        default:
            break;
    }
}

HallLayer::HallLayer()
{
    
}

HallLayer::~HallLayer()
{
    
}
