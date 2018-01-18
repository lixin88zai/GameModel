//
//  CommonMenu.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/25.
//
//

#pragma once

#include "cocos2d.h"
#include "Config/AppDef.h"
#include "BaseClass/Event/EventWrapper.h"

class CommonMenu : public cocos2d::Node, public EventWrapper
{
public:
    virtual bool init(const std::vector<KKMENU>& oMenus);
    
protected:
    virtual void initView() = 0;
    virtual void onMenuClick(cocos2d::Ref* pEvent, MENU eMenu);
    CommonMenu()
    :
    m_oMenus({})
    {
    }
    
    ~CommonMenu()
    {
    }
    
protected:
    std::vector<KKMENU> m_oMenus;
};
