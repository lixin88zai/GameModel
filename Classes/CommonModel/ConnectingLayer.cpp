//
//  ConnectingLayer.cpp
//  
//
//  Created by Joi Yao on 16/10/20.
//
//

#include "ConnectingLayer.h"

#include "Util/Utils.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace util;
using namespace std;

static ConnectingLayer *s_pInstance = nullptr;

ConnectingLayer* ConnectingLayer::getInstance()
{
    if (!s_pInstance)
    {
        s_pInstance = ConnectingLayer::create();
        s_pInstance->retain();
    }
    return s_pInstance;
}

void ConnectingLayer::show(const string &sText)
{
    if (!s_pInstance)
    {
        return;
    }
    s_pInstance->removeFromParent();
    m_pLabel->setString(sText);
    Director::getInstance()->getRunningScene()->addChild(s_pInstance);
}

void ConnectingLayer::hide()
{
    if (!s_pInstance)
    {
        return;
    }
    s_pInstance->removeFromParent();
}

bool ConnectingLayer::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ModalLayer::init());
        m_pLabel = GetLabel(26, "");
        m_pLabel->retain();
        m_pLabel->setScale(SCALE_FIT);
        m_pLabel->setPosition(DEVICE_W / 2, 300 * SCALE_Y);
        addChild(m_pLabel);
        bRet = true;
    } while (0);
    return bRet;
}

ConnectingLayer::ConnectingLayer()
:
m_pLabel(nullptr)
{
}

ConnectingLayer::~ConnectingLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLabel);
}
