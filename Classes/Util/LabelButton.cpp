//
//  LabelButton.cpp
//  GouJiProject
//
//  Created by 张旭 on 14-9-19.
//
//

#include "LabelButton.h"
#include "Config/Config.h"
#include "Util/ColorUtil/ColorUtil.h"

USING_NS_CC;
using namespace std;

const LabelButtonScale9Definition SKIN_DEFS[] =
{
    {BTN_BORDER1, Rect(0, 0, 103, 75),  Rect(50, 0, 3, 75),   Point(0, 3)},
    {BTN_BORDER2, Rect(0, 0, 103, 75),  Rect(50, 0, 3, 75),   Point(0, 3)},
    {BTN_BORDER3, Rect(0, 0, 103, 75),  Rect(50, 0, 3, 75),   Point(0, 3)},
    {BTN_BORDER4, Rect(0, 0, 103, 75),  Rect(50, 0, 3, 75),   Point(0, 3)},
    {BTN_BACKB,   Rect(0, 0, 100, 100), Rect(35, 0, 30, 100), Point(6, 1)}
};

const LabelButtonTextDefinition TEXT_DEFS[] =
{
    {"黑体", 36, COLOR_WHITE},
    {"黑体", 36, COLOR_WHITE},
    {"黑体", 36, COLOR_WHITE},
    {"黑体", 36, COLOR_WHITE},
    {"黑体", 28, COLOR_WHITE}
    
};

LabelButton::LabelButton()
:
m_pNormalImage(nullptr),
m_pHighlightImage(nullptr),
m_pLabel(nullptr)
{
}

LabelButton::~LabelButton()
{
    CC_SAFE_RELEASE_NULL(m_pNormalImage);
    CC_SAFE_RELEASE_NULL(m_pHighlightImage);
    CC_SAFE_RELEASE_NULL(m_pLabel);
}

LabelButton* LabelButton::create(LabelButtonStyle eStyle,
                                 const char *pText,
                                 float fWidth,
                                 const ccMenuCallback &fnCallback)
{
    auto pRet = new LabelButton();
    pRet->init(SKIN_DEFS[eStyle], TEXT_DEFS[eStyle], pText, fWidth, fnCallback);
    pRet->autorelease();
    return pRet;
}

LabelButton* LabelButton::createButtonBack(const ccMenuCallback &fnCallback)
{
    return LabelButton::create(kLabelButtonBack, "返回", 100, fnCallback);
}

bool LabelButton::init(const LabelButtonScale9Definition &oSkinDef,
                       const LabelButtonTextDefinition &oTextDef,
                       const char *pText,
                       float fWidth,
                       const ccMenuCallback &fnCallback)
{
    MenuItem::initWithCallback(fnCallback);
    // 底板
    m_pNormalImage = LabelButton::createSkin(oSkinDef, fWidth);
    m_pNormalImage->retain();
    addChild(m_pNormalImage);
    // 文本
    m_pLabel = LabelButton::createLabel(pText, oTextDef);
    m_pLabel->retain();
    m_pLabel->setPosition(Point(m_pNormalImage->getContentSize().width / 2 + oSkinDef.oLabelOffset.x,
                            m_pNormalImage->getContentSize().height / 2 + oSkinDef.oLabelOffset.y));
    m_pNormalImage->addChild(m_pLabel, 5);
    // 高亮层
    m_pHighlightImage = LabelButton::createSkin(oSkinDef, fWidth);
    m_pHighlightImage->retain();
    m_pHighlightImage->setColor(COLOR_BLACK);
    m_pHighlightImage->setOpacity(128);
    m_pHighlightImage->setVisible(false);
    addChild(m_pHighlightImage);
    
    setContentSize(m_pNormalImage->getContentSize());
    
    setCascadeColorEnabled(true);
    setCascadeOpacityEnabled(true);
    
    return true;
}

//通过两个精灵创建一个可置灰的按钮
MenuItem* LabelButton::createClickedGrayButtonBySprite(cocos2d::Sprite* normalSprite,cocos2d::Sprite* selectSprite,const cocos2d::ccMenuCallback &fucCallBack)
{
    MenuItem* pButtonItem = nullptr;
    selectSprite->setColor(COLOR_GRAY);
    for (int i=0; i<selectSprite->getChildren().size(); i++) {
        selectSprite->getChildren().at(i)->setColor(COLOR_GRAY);
    }
    pButtonItem = MenuItemSprite::create(normalSprite,
                                         selectSprite,
                                         fucCallBack);
    return pButtonItem;
}

MenuItem* LabelButton::createClickedGrayButton(const char *pszName, const cocos2d::ccMenuCallback &fucCallBack, bool bExpandTouchSize, const int nExpand)
{
    
    auto pButtonItemUp   = Sprite::create(pszName);
    auto pButtonItemDown = Sprite::create(pszName);
    auto pButtonItemDisabel = Sprite::create(pszName);
    MenuItem* pButtonItem = nullptr;
    if (bExpandTouchSize)
    {
        auto pSpriteUpContainer = Sprite::create();
        pSpriteUpContainer->setContentSize(Size(pButtonItemUp->getContentSize().width + nExpand,
                                                pButtonItemDown->getContentSize().height + nExpand));
        pButtonItemUp->setPosition(Vec2(pSpriteUpContainer->getContentSize().width / 2,
                                        pSpriteUpContainer->getContentSize().height / 2));
        pSpriteUpContainer->addChild(pButtonItemUp);
        
        auto pSpriteDownContainer = Sprite::create();
        pSpriteDownContainer->setContentSize(Size(pButtonItemDown->getContentSize().width + nExpand,
                                                  pButtonItemDown->getContentSize().height + nExpand));
        pButtonItemDown->setPosition(Vec2(pSpriteDownContainer->getContentSize().width / 2,
                                          pSpriteDownContainer->getContentSize().height / 2));
        pSpriteDownContainer->addChild(pButtonItemDown);
        
        pSpriteDownContainer->setColor(COLOR_GRAY);
        pSpriteDownContainer->setCascadeColorEnabled(true);
        
        auto pSpriteDisabelContainer = Sprite::create();
        pSpriteDisabelContainer->setContentSize(Size(pButtonItemDisabel->getContentSize().width + nExpand,
                                                     pButtonItemDisabel->getContentSize().height + nExpand));
        pButtonItemDisabel->setPosition(Vec2(pSpriteDisabelContainer->getContentSize().width / 2,
                                             pSpriteDisabelContainer->getContentSize().height / 2));
        pSpriteDisabelContainer->addChild(pButtonItemDisabel);
        pSpriteDisabelContainer->setColor(COLOR_GRAY);
        pSpriteDisabelContainer->setCascadeColorEnabled(true);
        
        pButtonItem = MenuItemSprite::create(pSpriteUpContainer,
                                             pSpriteDownContainer,
                                             pSpriteDisabelContainer,
                                             fucCallBack);
        
    } else
    {
        pButtonItemDown->setColor(COLOR_GRAY);
        pButtonItemDisabel->setColor(COLOR_GRAY);
        pButtonItem = MenuItemSprite::create(pButtonItemUp,
                                             pButtonItemDown,
                                             pButtonItemDisabel,
                                             fucCallBack);
    }
    return pButtonItem;

    
}

ui::Scale9Sprite* LabelButton::createSkin(const LabelButtonScale9Definition &oDef, float fWidth)
{
    ui::Scale9Sprite *pRet = ui::Scale9Sprite::create(oDef.pSkinFile, oDef.oRect, oDef.oCapInsets);
    pRet->setContentSize(Size(fWidth, oDef.oRect.size.height));
    pRet->setAnchorPoint(Vec2::ZERO);
    return pRet;
}

Label* LabelButton::createLabel(const char* pText, const LabelButtonTextDefinition &oDef)
{
    auto pRet = Label::createWithSystemFont(pText, oDef.pFontName, oDef.fFontSize);
    pRet->setColor(oDef.oFontColor);
    return pRet;
}

Sprite* LabelButton::createResSprite(const string &sResBg, const string &sResTxt)
{
    if (sResBg.empty() || sResTxt.empty())
    {
        return nullptr;
    }
    Sprite* pRet = Sprite::create(sResBg);
    Size oSize = pRet->getContentSize();
    Sprite* pTxt = Sprite::create(sResTxt);
    pTxt->setPosition(oSize.width / 2, oSize.height / 2);
    pRet->addChild(pTxt);
    pRet->setCascadeColorEnabled(true);
    pRet->setCascadeOpacityEnabled(true);
    return pRet;
}

void LabelButton::selected()
{
    MenuItem::selected();
    
    m_pHighlightImage->setVisible(true);
}

void LabelButton::unselected()
{
    MenuItem::unselected();
    
    m_pHighlightImage->setVisible(false);
}

void LabelButton::setLabelString(const std::string &sName)
{
    m_pLabel->setString(sName);
}

MenuItem* LabelButton::createDisabledButton(LabelButtonStyle eStyle,
                                            std::string pText,
                                            float fWidth,
                                            const cocos2d::ccMenuCallback &fnCallback)
{
    auto pNormal = createButtonSprite(SKIN_DEFS[eStyle].pSkinFile, pText, fWidth, 36, COLOR_WHITE);
    auto pSelected = createButtonSprite(SKIN_DEFS[eStyle].pSkinFile, pText, fWidth, 36, COLOR_GRAY);
    auto pDisabled = createButtonSprite(BTN_BORDER4, pText, fWidth, 36, COLOR_WHITE);
    
    MenuItem* pButtonItem = MenuItemSprite::create(pNormal, pSelected, pDisabled, fnCallback);
    return pButtonItem;
}

Node* LabelButton::createButtonSprite(const std::string& sAssest,
                                            const std::string& sText,
                                            const float& fWidth,
                                            const int& nFontSize,
                                            const cocos2d::Color3B& oColor)
{
    auto pBg = ui::Scale9Sprite::create(sAssest);
    pBg->setContentSize(Size(fWidth, pBg->getContentSize().height));
    pBg->setColor(oColor);
    
    auto pLabel = Label::createWithSystemFont(sText.c_str(), "黑体", nFontSize);
    pLabel->setColor(oColor);
    pLabel->setPosition(Point(pBg->getContentSize().width / 2,
                              pBg->getContentSize().height / 2 + 3));
    
    pBg->addChild(pLabel, 5);
    return pBg;
}

MenuItem* LabelButton::createLabelButton(const char* pszName,
                                         const cocos2d::ccMenuCallback &fucCallBack,
                                         const cocos2d::Color3B& oColor,
                                         float fontSize,
                                         bool bSkew,
                                         bool bOutline)
{
    Label* pLabelUp = Label::createWithSystemFont(pszName, "黑体", fontSize);
    pLabelUp->setColor(oColor);
    pLabelUp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    
    ui::Scale9Sprite* pLineUp = ui::Scale9Sprite::create(BG_FEFEFF);
    pLineUp->setColor(oColor);
    pLineUp->setAnchorPoint(Vec2::ZERO);
    pLineUp->setContentSize(Size(pLabelUp->getContentSize().width, 2));
    
    Label* pLabelDown = Label::createWithSystemFont(pszName, "黑体", fontSize);
    pLabelDown->setColor(oColor);
    pLabelDown->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    
    ui::Scale9Sprite* pLineDown = ui::Scale9Sprite::create(BG_FEFEFF);
    pLineDown->setColor(oColor);
    pLineDown->setAnchorPoint(Vec2::ZERO);
    pLineDown->setContentSize(Size(pLabelDown->getContentSize().width, 2));
    
    if (bSkew)
    {
        pLabelUp->setSkewX(8.0f);
        pLabelDown->setSkewX(8.0f);
    }
    if (bOutline)
    {
        pLabelUp->enableOutline(Color4B(oColor), 1);
        pLabelDown->enableOutline(Color4B(oColor), 1);
    }
    
    auto pSpriteUpContainer = Sprite::create();
    pSpriteUpContainer->setContentSize(Size(pLabelUp->getContentSize().width,
                                            pLabelUp->getContentSize().height + 2));
    pLabelUp->setPosition(Vec2(0, pSpriteUpContainer->getContentSize().height / 2 + 1));
    pSpriteUpContainer->addChild(pLabelUp);

    pLineUp->setPosition(Vec2(0, 0));
    pSpriteUpContainer->addChild(pLineUp);
    
    auto pSpriteDownContainer = Sprite::create();
    pSpriteDownContainer->setContentSize(Size(pLabelDown->getContentSize().width,
                                              pLabelDown->getContentSize().height + 2));
    pLabelDown->setPosition(Vec2(0, pSpriteDownContainer->getContentSize().height / 2 + 1));
    pSpriteDownContainer->addChild(pLabelDown);
    
    pLineDown->setPosition(Vec2(0, 0));
    pSpriteDownContainer->addChild(pLineDown);
    
    pSpriteDownContainer->setColor(COLOR_GRAY);
    pSpriteDownContainer->setCascadeColorEnabled(true);
    
    MenuItem* pButtonItem = MenuItemSprite::create(pSpriteUpContainer,
                                                   pSpriteDownContainer,
                                                   fucCallBack);
    
    return pButtonItem;
}

cocos2d::MenuItem* LabelButton::createTxtSpriteButton(const char* pszName,
                                                const char* psInnerImg,
                                                const cocos2d::Rect& oRect,
                                                const cocos2d::Size& oBtnSize,
                                                const Vec2& offset,
                                                const float fInnerScale,
                                                const cocos2d::ccMenuCallback& fnCallback)
{
    auto pBaseUpSprite = ui::Scale9Sprite::create(pszName);
    pBaseUpSprite->setCapInsets(oRect);
    pBaseUpSprite->setContentSize(oBtnSize);
    auto pTxtSprite = Sprite::create(psInnerImg);
    pTxtSprite->setScale(fInnerScale);
    pTxtSprite->setPosition(Vec2(pBaseUpSprite->getContentSize().width / 2 + offset.x,
                                 pBaseUpSprite->getContentSize().height / 2 + offset.y));
    pBaseUpSprite->addChild(pTxtSprite);
    pBaseUpSprite->setCascadeColorEnabled(true);
    pBaseUpSprite->setCascadeOpacityEnabled(true);
    
    auto pBaseDownSprite = ui::Scale9Sprite::create(pszName);
    pBaseDownSprite->setCapInsets(oRect);
    pBaseDownSprite->setContentSize(oBtnSize);
    pTxtSprite = Sprite::create(psInnerImg);
    pTxtSprite->setScale(fInnerScale);
    pTxtSprite->setPosition(Vec2(pBaseDownSprite->getContentSize().width / 2 + offset.x,
                                 pBaseDownSprite->getContentSize().height / 2 + offset.y));
    pBaseDownSprite->addChild(pTxtSprite);
    pBaseDownSprite->setCascadeColorEnabled(true);
    pBaseDownSprite->setCascadeOpacityEnabled(true);
    pBaseDownSprite->setColor(COLOR_GRAY);
    
    MenuItem* pButtonItem = MenuItemSprite::create(pBaseUpSprite, pBaseDownSprite, fnCallback);
    
    return pButtonItem;
}

cocos2d::MenuItem* LabelButton::createNormalClickDiffButton(const char* psNorName,
                                                      const char* psCliName,
                                                      const cocos2d::ccMenuCallback& fnCallback)
{
    auto pNormalSprite = Sprite::create(psNorName);
    pNormalSprite->setCascadeColorEnabled(true);
    pNormalSprite->setCascadeOpacityEnabled(true);
    
    auto pClickSprite = Sprite::create(psCliName);
    pClickSprite->setCascadeColorEnabled(true);
    pClickSprite->setCascadeOpacityEnabled(true);
    
    MenuItem* pButtonItem = MenuItemSprite::create(pNormalSprite, pClickSprite, fnCallback);
    
    return pButtonItem;
}

MenuItem* LabelButton::createResButton(const string &sResBg,
                                       const string &sResTxt,
                                       const ccMenuCallback &fnCallback)
{
    Sprite* pNormal = createResSprite(sResBg, sResTxt);
    Sprite* pSelect = createResSprite(sResBg, sResTxt);
    pSelect->setColor(COLOR_GRAY);
    Sprite* pDisable = createResSprite(sResBg, sResTxt);
    ColorUtil::gray(pDisable);
    MenuItem* pRet = MenuItemSprite::create(pNormal, pSelect, pDisable, fnCallback);
    return pRet;
}

void LabelButton::addInnerResListOnSprite(Sprite* pButton,std::vector<std::string> innerResList,std::vector<Vec2> nPosList)
{
    if (innerResList.size() != nPosList.size())     //内嵌图片数量和对应位置不匹配
    {
        return;
    }
    for(int i=0;i<innerResList.size();i++)
    {
        Sprite* pSprite = Sprite::create(innerResList.at(i));
        pSprite->setPosition(nPosList.at(i));
        pSprite->setAnchorPoint(Vec2(0.5,0.5));
        pButton->addChild(pSprite);
    }
}
