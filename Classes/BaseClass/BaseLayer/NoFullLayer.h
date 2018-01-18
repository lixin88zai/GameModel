//
//  Model.h
//  GouJi
//
//  Created by ZengQi on 14-11-24.
//  该基础类是基于非全屏节点页面，此类页面没有关闭按钮
//

#ifndef __GouJi__Model__
#define __GouJi__Model__

#include "BaseClass/Event/EventWrapper.h"
#include "BaseClass/TimeTick/TimeTick.h"
#include "extensions/cocos-ext.h"
#include <string>
#include "cocos2d.h"


USING_NS_CC;

//该基础类是基于非全屏节点页面，此类页面没有关闭按钮,内容位置是从（0,0)开始
//该基础类是基于非全屏节点页面，此类页面没有关闭按钮,内容位置是从（0,0)开始
//该基础类是基于非全屏节点页面，此类页面没有关闭按钮,内容位置是从（0,0)开始
class NoFullLayer : public cocos2d::Layer, public EventWrapper, public TimeTick
{
public:
    virtual bool init();
    virtual void initContainer();
    virtual void initContent() = 0;
    virtual void showAction(){}
    virtual void hideAction(){}
    virtual void onMenuClick(cocos2d::Ref* pEvent, int eTag){}
    NoFullLayer();
    ~NoFullLayer();
protected:
    cocos2d::Node*  m_pContainer;   // 容器
    
};

#endif /* defined(__GouJi__Model__) */
