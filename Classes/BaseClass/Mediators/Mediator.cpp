//
//  Mediator.cpp
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#include "Mediator.h"

USING_NS_CC;
using namespace std;

bool Mediator::initialize(const string &sName, cocos2d::Ref* pView)
{
    m_sName = sName;
    m_pView = pView;
    CC_SAFE_RETAIN(m_pView);
    return true;
}

vector<string> Mediator::listEventNames()
{
    return {};
}

void Mediator::handleEvent(cocos2d::EventCustom *pEvent)
{
    string sEventName = pEvent->getEventName();
    log("--%s >>> %s", getName().c_str(), sEventName.c_str());
    handleEventData(sEventName, pEvent->getUserData());
}

void Mediator::addObserver()
{
    m_oEventNames = listEventNames();
    for (long i = 0; i < m_oEventNames.size(); i ++)
    {
        ADD_OBSERVER(Mediator::handleEvent, m_oEventNames.at(i));
    }
}

void Mediator::removeObservser()
{
    removeAllEventListeners();
}

Mediator::Mediator()
:
m_sName("Mediator"),
m_pView(nullptr),
m_oEventNames({})
{
    
}

Mediator::~Mediator()
{
    removeObservser();
    CC_SAFE_RELEASE_NULL(m_pView);
}