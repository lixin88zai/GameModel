//
//  AppView.h
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#pragma once

#include "cocos2d.h"
#include "BaseClass/Mediators/Mediator.h"
#include "BaseClass/Event/EventWrapper.h"

class AppView : public cocos2d::Ref, public EventWrapper
{
public:
    enum LAYER
    {
        kLayerBackground = 1,   // 背景层
        kLayerCanvas,           // 游戏画布层
        kLayerForeground,       // 前景层
        kLayerAvatar,           // Avatar层
        kLayerResult,           // 结算层
        kLayerFrame,            // 主界面层
        kLayerFloating,         // 浮层
        kLayerAnimation,        // 动画层
        kLayerDialog,           // 对话层
        kLayerPanel,            // 面板层
        kLayerGuide,            // 引导层
        kLayerAds,              // 广告层
        kLayerSys,              // 系统公告层
        kLayerErr,              // 网络连接错误层
    };
    
public:
    static AppView* getInstance();
    
    void initialize();
    
    cocos2d::Layer* getLayer(LAYER eType);
    void addTo(LAYER eType, cocos2d::Node* pComponent);
    void clear();
    
    Mediator* getMediator(const std::string& sMediatorName);
    void registerMediator(Mediator* pMediator);
    void removeMediator(const std::string& sMediatorName);
    
private:
    AppView();
    ~AppView();
    
private:
    cocos2d::Scene*                         m_pSingleScene;
    cocos2d::Vector<cocos2d::Layer*>        m_obLayerVector;
    cocos2d::Map<std::string, Mediator*>    m_obMediatorMap;
};
