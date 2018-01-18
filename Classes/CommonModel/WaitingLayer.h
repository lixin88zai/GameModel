//
//  WaitingLayer.h
//  GouJiProject
//
//  Created by 张旭 on 14-9-19.
//
//

#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class WaitingLayer : public cocos2d::Layer
{
public:
    static WaitingLayer* sharedInstance();
    
    virtual bool init();
	virtual void onEnter();
	virtual void onExit();
    virtual void update(float delta);
    
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
    void show(int nTimeout = 0, cocos2d::Ref *pTarget = nullptr, cocos2d::SEL_CallFunc pCallback = nullptr);
    void hide();
private:
    WaitingLayer();
	~WaitingLayer();
    
    void onTimeout(float delta);
private:
	bool                            m_bWaiting;
    cocos2d::Sprite*                m_pLoading;
    cocos2d::Ref*                   m_pTarget;
    cocos2d::SEL_CallFunc           m_pCallback;
};