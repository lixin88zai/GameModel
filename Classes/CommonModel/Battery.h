//
//  Battery.h
//  GouJi
//
//  Created by Joi Yao on 15/8/10.
//
//

#pragma once

#include "cocos2d.h"

class Battery : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Battery);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    void onUpdateTime(float delta);
    void enableAction(const bool& bEnabled);
    void updateBatteryItem(int num);
    Battery();
    ~Battery();
    
private:
    cocos2d::Sprite*            m_pBatteryFull;
    cocos2d::Label*             m_pLabel;
    cocos2d::Action*            m_pAction;
    cocos2d::Sprite*            m_batteryBack;
    int                         m_IBatteryNumber;
};
