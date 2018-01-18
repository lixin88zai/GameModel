//
//  WaitingLayer.cpp
//  GouJiProject
//
//  Created by 张旭 on 14-9-19.
//
//

#include "WaitingLayer.h"
#include "Util/Utils.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace util;

static WaitingLayer *s_pSharedInstance = nullptr;

WaitingLayer::WaitingLayer()
:
m_bWaiting(false),
m_pLoading(nullptr),
m_pTarget(nullptr),
m_pCallback(nullptr)
{
}

WaitingLayer::~WaitingLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLoading);
    CC_SAFE_RELEASE_NULL(m_pTarget);
    m_pCallback = nullptr;
}

WaitingLayer* WaitingLayer::sharedInstance()
{
    if (s_pSharedInstance == nullptr)
    {
        s_pSharedInstance = new WaitingLayer();
        s_pSharedInstance->init();
    }
    return s_pSharedInstance;
}

bool WaitingLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        m_pLoading = Sprite::create(BG_LOADING);
        m_pLoading->retain();
        m_pLoading->setScale(SCALE_FIT);
        m_pLoading->setPosition(Vec2(DEVICE_W / 2, DEVICE_H / 2));
        addChild(m_pLoading);
        
        auto pEventToucher = EventListenerTouchOneByOne::create();
        pEventToucher->setSwallowTouches(true);
        pEventToucher->onTouchBegan = CC_CALLBACK_2(WaitingLayer::onTouchBegan, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(pEventToucher, this);
        
        // 物理键屏蔽
        auto obKeyBackListener = EventListenerKeyboard::create();
        obKeyBackListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
        {
            if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
            {
                event->stopPropagation();
            }
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(obKeyBackListener, this);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void WaitingLayer::onEnter()
{
	Layer::onEnter();
    
    scheduleUpdate();
}

void WaitingLayer::onExit()
{
    hide();
    unscheduleUpdate();
    
	Layer::onExit();
}

void WaitingLayer::update(float delta)
{
    float fRotation = m_pLoading->getRotation() + 6;
    if (fRotation >= 360)
    {
        fRotation -= 360;
    }
    m_pLoading->setRotation(fRotation);
}

bool WaitingLayer::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    return true;
}

void WaitingLayer::show(int nTimeout, Ref *pTarget, SEL_CallFunc pCallback)
{
	if (m_bWaiting)
    {
        hide();
    }
    m_bWaiting = true;
    Director::getInstance()->getRunningScene()->addChild(this, INT_MAX);
    if (nTimeout > 0 && pTarget != nullptr && pCallback != nullptr)
    {
        m_pTarget = pTarget;
        m_pTarget->retain();
        m_pCallback = pCallback;
        scheduleOnce(schedule_selector(WaitingLayer::onTimeout), nTimeout);
    }
}

void WaitingLayer::hide()
{
	if (!m_bWaiting)
    {
        return;
    }
    m_bWaiting = false;
    removeFromParent();
    if (m_pTarget != nullptr)
    {
        unschedule(schedule_selector(WaitingLayer::onTimeout));
        CC_SAFE_RELEASE_NULL(m_pTarget);
        m_pCallback = nullptr;
    }
}

void WaitingLayer::onTimeout(float delta)
{
	if (m_pTarget != nullptr)
    {
        (m_pTarget->*m_pCallback)();
        CC_SAFE_RELEASE_NULL(m_pTarget);
        m_pCallback = nullptr;
    }
}
