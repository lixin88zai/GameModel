//
//  HallMediator.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "Mediator.h"
#include "HallLayer.h"
#include "BaseClass/TimeTick/TimeTick.h"
#include "Config/Config.h"

extern KKQQGROUPINFO* QQGROUPINFO;

class HallMediator : public Mediator, public TimeTick
{
public:
    CREATE_MEDIATOR(HallMediator);
    virtual std::vector<std::string> listEventNames();
    virtual void handleEventData(const std::string& sEvent, void* pData);
    virtual void onRegister();
    virtual void onRemove();
    virtual void onExitComplete();
    
    
    void onButtonClick(cocos2d::EventCustom* pEvent);
    
private:
    HallMediator();
    ~HallMediator();

public:
    static std::string NAME;
    
private:
    HallLayer*      m_pHall;
    cocos2d::Layer* m_pDialogLayer;
};
