//
//  PromptTextBar.cpp
//  PaoDeKuaiPQ
//
//  Created by Zongyang on 16/11/19.
//
//

#include "PromptTextBar.h"
#include "Util/Utils.h"
#include "Config/Config.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define TAG_GLOBAL_PROMPTTXT 3003

PromptTextBar::PromptTextBar()
:
m_pLeftBG(nullptr),
m_pRightBG(nullptr),
m_pLabel(nullptr),
m_fMinWidth(0),
m_fMinHeight(0)
{
}

PromptTextBar::~PromptTextBar()
{
}

PromptTextBar* PromptTextBar::create()
{
    PromptTextBar *pobBar = new PromptTextBar();
    if(pobBar && pobBar->initWithFile(BG_NULL))
    {
       	pobBar->autorelease();
        
        pobBar->m_pLeftBG = Sprite::create(BG_TIP_BLACK);
        pobBar->m_pRightBG = Sprite::create(BG_TIP_BLACK);

        pobBar->setContentSize( Size(pobBar->m_pLeftBG->getContentSize().width * 2, pobBar->m_pLeftBG->getContentSize().height) );
        pobBar->setAnchorPoint(Point(0.5f, 0.5f));
        pobBar->m_fMinWidth =pobBar->m_pLeftBG->getContentSize().width * 2;
        pobBar->m_fMinHeight = pobBar->m_pLeftBG->getContentSize().height;
        
        //pobBar->m_pBG->setScale(SCALE_FIT);
        pobBar->m_pLeftBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
        pobBar->m_pRightBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        pobBar->m_pLeftBG->setPosition( Vec2(0 , 0) );
        pobBar->m_pRightBG->setPosition( Vec2(0 , 0) );
        pobBar->m_pRightBG->setFlippedX(true);
        pobBar->addChild(pobBar->m_pLeftBG);
        pobBar->addChild(pobBar->m_pRightBG);
        
        //文字
        auto pLabel = Label::createWithSystemFont("", "黑体", 30);
        if(pLabel)
        {
            pobBar->m_pLabel = pLabel;
            pLabel->setAnchorPoint(Point(0.5f, 0.5f));
            pLabel->setColor(Color3B(255,255,0));
            pLabel->setPosition(0, 0);
            pobBar->addChild(pLabel, 4);
        }
        return pobBar;
    }

    CC_SAFE_DELETE(pobBar);
    return 0;
}

void PromptTextBar::prompt(const char* szText, int nSecond)
{
    if( !m_pLeftBG || !m_pRightBG || !m_pLabel) return;
    
    hide();
    
    m_pLabel->setString(szText);
    Size csLabel = m_pLabel->getContentSize();
    float fw = csLabel.width + 32;
    if(fw < m_fMinWidth) fw = m_fMinWidth;
    float fh = csLabel.height + 32;
    m_pLabel->setAnchorPoint(Point(0.5, 0.5));
    m_pLabel->setPosition(Point(fw / 2, fh / 2));
    m_pLeftBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
    m_pRightBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    m_pLeftBG->setPosition(Point(fw / 2, fh / 2));
    m_pRightBG->setPosition(Point(fw / 2, fh / 2));
    
    m_pLeftBG->setOpacity(200);
    m_pRightBG->setOpacity(200);
    m_pLabel->setOpacity(255);
    setVisible(true);
    
    float ffade = 0.5;
    FiniteTimeAction* pa1 = Sequence::create(TargetedAction::create(m_pLeftBG, Show::create()),
                                             TargetedAction::create(m_pLeftBG, DelayTime::create(nSecond)),
                                             TargetedAction::create(m_pLeftBG, FadeOut::create(ffade)),
                                             TargetedAction::create(m_pLeftBG, Hide::create()),
                                             nullptr);
    FiniteTimeAction* pa12 = Sequence::create(TargetedAction::create(m_pRightBG, Show::create()),
                                             TargetedAction::create(m_pRightBG, DelayTime::create(nSecond)),
                                             TargetedAction::create(m_pRightBG, FadeOut::create(ffade)),
                                             TargetedAction::create(m_pRightBG, Hide::create()),
                                             nullptr);
    FiniteTimeAction* pa2 = Sequence::create(TargetedAction::create(m_pLabel, Show::create()),
                                             TargetedAction::create(m_pLabel, DelayTime::create(nSecond)),
                                             TargetedAction::create(m_pLabel, FadeOut::create(ffade)),
                                             TargetedAction::create(m_pLabel, Hide::create()),
                                             nullptr);
    runAction(Spawn::create(pa1, pa12, pa2, nullptr));
}

void PromptTextBar::hide()
{
    stopAllActions();
    m_pLeftBG->stopAllActions();
    m_pRightBG->stopAllActions();
    m_pLabel->stopAllActions();
    setVisible(false);
}

//显示提示信息
void promptText(Node *pNode, float fy, const char* szText, int nSecond, float fx)
{
    do
    {
        CC_BREAK_IF(!pNode);
        PromptTextBar* pPrompt = (PromptTextBar*)pNode->getChildByTag(TAG_GLOBAL_PROMPTTXT);
        if(!pPrompt)
        {
            pPrompt = PromptTextBar::create();
            pPrompt->setScale(SCALE_FIT);
            CC_BREAK_IF(!pPrompt);
            pPrompt->setTag(TAG_GLOBAL_PROMPTTXT);
            pPrompt->setAnchorPoint(Point(0.5f, 0.5f));
            pPrompt->setPosition(Point(fx, fy));
            pNode->addChild(pPrompt, INT_MAX);
        }
        if(szText)
        {
            pPrompt->setPositionY(fy);
            pPrompt->prompt(szText, nSecond);
        }
        else
        {
            pPrompt->hide();
        }
    }
    while (0);
}
