//
//  BaseDialogNoBackground.h
//  paohuzi
//
//  Created by zhaojing on 3/10/17.
//
//

#pragma once

#include "Util/BaseLayerUtil.h"
#include "Config/Config.h"
#include "BaseClass/Event/EventWrapper.h"

class BaseDialogNoBackground : public util::BaseLayerUtil, public EventWrapper
{
public:
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    
protected:
    virtual void initView();
    virtual void initSize();
    // 容器
    virtual void initContainer();
    // 背景
    virtual void initBg();
    // 标题
    virtual void initTitle();
    // 菜单
    virtual void initMenu();
    // 按键
    virtual void initKey();
    // 内容
    virtual void initContent() = 0;
    // 点击空白区
    virtual void onTouchBlank();
    // 按返回键
    virtual void onPressKeyBack();
    // 关闭对话框
    virtual void onClose(cocos2d::Ref* pSender = nullptr);
    
    void tip(const std::string& sText);
    void enterSceneAnimation();
    void setUnCanClose(bool var);
    
    BaseDialogNoBackground();
    ~BaseDialogNoBackground();
    
protected:
    cocos2d::Node*  m_pContainer;   // 容器
    cocos2d::MenuItem*  m_pClose;   // 关闭按钮
    cocos2d::Size   m_oSize;        // 9宫格背景大小
    float           m_fScale;       // 整体缩放值
    bool            m_bTouchIn;
    bool            m_bUnCanClose;  // 是否可以关闭
};
