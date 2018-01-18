//
//  ScrollViewMenu.h
//  GouJi
//
//  Created by 张旭 on 15/6/17.
//
//

//在ScrollView 里面直接加入Menu 时，会出现问题:
//(1)滑动ScrollView时，Menu也会被触发。
//(2)不在ScrollView ViewSize 之内时，也可以点击Menu

#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class ScrollViewMenu : public cocos2d::Menu
{
public:
    ScrollViewMenu(const cocos2d::Rect &VisibleRect,cocos2d::Node* pNode);
    
    ~ScrollViewMenu();
    
    static ScrollViewMenu * create(const cocos2d::Rect &VisibleRect,cocos2d::Node* pNode);
    
    bool init();
    
    bool initWithArray(const cocos2d::Vector<cocos2d::MenuItem*>& arrayOfItems);
    
    virtual bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    virtual void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    
private:
    cocos2d::Rect m_VisibleRect;
    cocos2d::Point m_StartPoint;
    bool m_bMoved;
    cocos2d::Node* m_pVisibleNode;
};