//
//  Mediator.h
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#pragma once

#include "BaseClass/Event/EventWrapper.h"

#define CREATE_MEDIATOR(__TYPE__) \
static __TYPE__* create() \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->initialize(__TYPE__::NAME)) \
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

class Mediator : public cocos2d::Ref, public EventWrapper
{
public:
    virtual bool initialize(const std::string& sName, cocos2d::Ref* pView = nullptr);
    virtual std::vector<std::string> listEventNames() = 0;
    virtual void handleEvent(cocos2d::EventCustom* pEvent);
    virtual void handleEventData(const std::string& sEvent, void* pData) = 0;
    virtual void onRegister() = 0;
    virtual void onRemove() = 0;
    
    virtual void addObserver();
    virtual void removeObservser();
    
    Mediator();
    ~Mediator();
    
    CC_SYNTHESIZE_READONLY(std::string,                 m_sName,        Name);
    CC_SYNTHESIZE_READONLY(cocos2d::Ref*,               m_pView,        View);
    
protected:
    std::vector<std::string> m_oEventNames;
};
