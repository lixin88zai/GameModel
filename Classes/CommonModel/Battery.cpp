//
//  Battery.cpp
//  GouJi
//
//  Created by Joi Yao on 15/8/10.
//
//

#include "Battery.h"
#include "PlatformFunction.h"
#include "Util/Utils.h"
#include "Config/Config.h"


USING_NS_CC;
using namespace util;

bool Battery::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Sprite::init());
        
        m_batteryBack = Sprite::create(BG_BATTERY_BACK);
        m_batteryBack->retain();
        addChild(m_batteryBack);
        auto oSize = m_batteryBack->getContentSize();
        
        for(int i = 0; i < 4; i++)
        {
            auto batteryItem = Sprite::create(BG_BATTERY_ITEM);
            batteryItem->setAnchorPoint(Vec2(0, 0.5));
            batteryItem->setPosition(Vec2(9 + 8.5 * i, oSize.height / 2));
            batteryItem->setTag(i);
            batteryItem->retain();
            m_batteryBack->addChild(batteryItem);
            
        }
        
        setCascadeOpacityEnabled(true);
        onUpdateTime(0);
        bRet = true;
    } while (0);
    return bRet;
}

void Battery::onEnter()
{
    Sprite::onEnter();
    schedule(CC_SCHEDULE_SELECTOR(Battery::onUpdateTime), 60.0);
}

void Battery::onExit()
{
    unscheduleAllCallbacks();
    Sprite::onExit();
}

void Battery::onUpdateTime(float delta)
{
    float percent = PlatformFunction::getBatteryLevel();
    updateBatteryItem(int(percent * 100.0 / 25 + 1) % 4);
    return;
}

void Battery::updateBatteryItem(int num)
{
    if(m_IBatteryNumber == num - 1)
        return;
    
    for(int i = 0; i < 4; i++)
    {
        if(m_batteryBack->getChildByTag(i) != nullptr)
            m_batteryBack->getChildByTag(i)->setVisible(false);
    }

    for(int i = 0; i < num; i++)
    {
        if(m_batteryBack->getChildByTag(i) != nullptr)
        {
            m_batteryBack->getChildByTag(i)->setVisible(true);
            m_IBatteryNumber = i;
        }
    }
}

void Battery::enableAction(const bool &bEnabled)
{
    if (bEnabled)
    {
        if (!m_pAction)
        {
            stopAllActions();
            setOpacity(255);
            m_pAction = RepeatForever::create(Sequence::create(FadeOut::create(0.5), FadeIn::create(0.5), nullptr));
            m_pAction->retain();
            runAction(m_pAction);
        }
    }
    else
    {
        if (m_pAction)
        {
            stopAllActions();
            setOpacity(255);
            CC_SAFE_RELEASE_NULL(m_pAction);
        }
    }
}

Battery::Battery()
:
m_batteryBack(nullptr),
m_IBatteryNumber(-1),
m_pAction(nullptr)
{
}

Battery::~Battery()
{
    CC_SAFE_RELEASE_NULL(m_batteryBack);
    CC_SAFE_RELEASE_NULL(m_pAction);
}
