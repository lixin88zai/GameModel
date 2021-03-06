//
//  TimeTick.cpp
//  ShengJi
//
//  Created by Joi Yao on 15/10/30.
//
//

#include "TimeTick.h"

USING_NS_CC;

TimeTick::TimeTick()
:
m_pScheduler(nullptr)
{
    m_oTargets.clear();
    m_pScheduler = Director::getInstance()->getScheduler();
    CC_SAFE_RETAIN(m_pScheduler);
}

TimeTick::~TimeTick()
{
    CC_SAFE_RELEASE_NULL(m_pScheduler);
    unTickAll();
}

void TimeTick::tick(cocos2d::SEL_SCHEDULE selector, Ref *target, float interval)
{
    if (m_oTargets.find(target) == m_oTargets.end())
    {
        m_oTargets.pushBack(target);
    }
    m_pScheduler->schedule(selector, target, interval, false);
}

void TimeTick::tickOnce(SEL_SCHEDULE selector, Ref *target, float delay)
{
    if (m_oTargets.find(target) == m_oTargets.end())
    {
        m_oTargets.pushBack(target);
    }
    m_pScheduler->schedule(selector, target, delay, 0, 0, false);
}

void TimeTick::unTick(SEL_SCHEDULE selector, Ref *target)
{
    m_pScheduler->unschedule(selector, target);
}

void TimeTick::unTickAll()
{
    for (size_t i = 0; i < m_oTargets.size(); i ++)
    {
        m_pScheduler->unscheduleAllForTarget(m_oTargets.at(i));
    }
    m_oTargets.clear();
}