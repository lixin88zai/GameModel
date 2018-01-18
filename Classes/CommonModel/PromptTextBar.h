//
//  PromptTextBar.h
//  PaoDeKuaiPQ
//
//  Created by Zongyang on 16/11/19.
//
//

#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class PromptTextBar : public cocos2d::Sprite
{
public:
    PromptTextBar();
    ~PromptTextBar();
    static PromptTextBar* create();
    
    void prompt(const char* szText, int nSecond);
    void hide();
private:
    Sprite*         m_pLeftBG;
    Sprite*         m_pRightBG;
    Label*          m_pLabel;
    float           m_fMinWidth;
    float           m_fMinHeight;
};

//显示提示信息
void promptText(cocos2d::Node *pNode, float fy, const char* szText, int nSecond = 3, float fx = Director::getInstance()->getWinSize().width / 2);
