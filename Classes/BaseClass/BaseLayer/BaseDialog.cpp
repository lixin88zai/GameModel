//
//  BaseDialog.cpp
//  GouJi
//
//  Created by Joi Yao on 4/9/16.
//
//

#include "BaseDialog.h"
#include "Util/Utils.h"
#include "Config/Config.h"
#include "ui/UIScale9Sprite.h"
#include "CommonModel/PromptTextBar.h"

USING_NS_CC;
using namespace util;

bool BaseDialog::init()
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!ModalLayer::init());
        initView();
        bRet = true;
    } while (0);
    return bRet;
}

void BaseDialog::onEnter()
{
    ModalLayer::onEnter();
    enterSceneAnimation();
}

void BaseDialog::onExit()
{
    unscheduleAllCallbacks();
    ModalLayer::onExit();
}

bool BaseDialog::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Point oPos = m_pContainer->getParent()->convertTouchToNodeSpace(pTouch);
    m_bTouchIn = m_pContainer->getBoundingBox().containsPoint(oPos);
    return true;
}

void BaseDialog::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    Point oPos = m_pContainer->getParent()->convertTouchToNodeSpace(pTouch);
    if (!m_bTouchIn && !m_pContainer->getBoundingBox().containsPoint(oPos))
    {
        onTouchBlank();
    }
}

void BaseDialog::initView()
{
    initSize();
    initContainer();
    initBg();
    initTitle();
    initMenu();
    initKey();
    initContent();
}

void BaseDialog::initSize()
{
    m_oSize = Size(700, 520);
    m_fScale = SCALE_FIT;
}

void BaseDialog::initContainer()
{
    m_pContainer = Node::create();
    m_pContainer->retain();
    m_pContainer->setScale(m_fScale);
    m_pContainer->setContentSize(m_oSize);
    m_pContainer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    m_pContainer->setPosition(DEVICE_W / 2, DEVICE_H / 2);
    m_pContainer->setCascadeColorEnabled(true);
    m_pContainer->setCascadeOpacityEnabled(true);
    addChild(m_pContainer);
}

void BaseDialog::initBg()
{
    ui::Scale9Sprite* pBg = ui::Scale9Sprite::create(BG_DIALOG);
    Size oSizeBg = pBg->getContentSize();
    Rect oRect = Rect(0, 0, oSizeBg.width, oSizeBg.height);
    Rect oCapInsets = Rect(oSizeBg.width / 2 - 1, oSizeBg.height / 2 - 1, 3, 3);
    pBg = ui::Scale9Sprite::create(BG_DIALOG, oRect, oCapInsets);
    pBg->setContentSize(m_oSize);
    pBg->setAnchorPoint(Vec2::ZERO);
    pBg->setPosition(Vec2::ZERO);
    m_pContainer->addChild(pBg);
    
    Sprite* pGradient = Sprite::create(BG_DIALOG_GRADIENT);
    Size oSize = pGradient->getContentSize();
    oSizeBg = Size(m_oSize.width - 21 * 2, m_oSize.height - 35 * 2);
    if (oSize.width > 0 && oSize.height > 0)
    {
        pGradient->setScale(oSizeBg.width / oSize.width, oSizeBg.height / oSize.height);
        pGradient->setAnchorPoint(Vec2::ZERO);
        pGradient->setPosition(21, 35);
        m_pContainer->addChild(pGradient);
    }
    
    pBg = ui::Scale9Sprite::create(BG_DIALOG_WAVE);
    oSize = pBg->getContentSize();
    oRect = Rect(0, 0, oSize.width, oSize.height);
    oCapInsets = Rect(oSize.width / 2, 0, 1, oSize.height);
    pBg->setContentSize(Size(m_oSize.width - 18 * 2, oSize.height));
    pBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    pBg->setPosition(m_oSize.width / 2, m_oSize.height - 18);
    m_pContainer->addChild(pBg);
    
    Sprite* pSprite = Sprite::create(BG_DIALOG_UP);
    pSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    pSprite->setPosition(m_oSize.width / 2, m_oSize.height - 18);
    pSprite->setScaleX((m_oSize.width - 33 * 2) / pSprite->getContentSize().width);
    m_pContainer->addChild(pSprite);
    
    pSprite = Sprite::create(BG_DIALOG_DOWN);
    pSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
    pSprite->setPosition(m_oSize.width / 2, 16);
    pSprite->setScaleX((m_oSize.width - 23 * 2) / pSprite->getContentSize().width);
    m_pContainer->addChild(pSprite);
}

void BaseDialog::initTitle()
{
}

void BaseDialog::initMenu()
{
    m_pClose = LabelButton::createClickedGrayButton(BTN_X, CC_CALLBACK_1(BaseDialog::onClose, this), true);
    m_pClose->retain();
    m_pClose->setPosition(m_oSize.width - 25, m_oSize.height - 18);
    auto pMenu = Menu::create(m_pClose, nullptr);
    pMenu->setAnchorPoint(Vec2::ZERO);
    pMenu->setPosition(Vec2::ZERO);
    m_pContainer->addChild(pMenu);
}

void BaseDialog::initKey()
{
    auto obKeyBackListener = EventListenerKeyboard::create();
    obKeyBackListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
        {
            event->stopPropagation();
            onPressKeyBack();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(obKeyBackListener, this);
}

void BaseDialog::onTouchBlank()
{
    if (!m_bUnCanClose)
    {
        onClose();
    }
}

void BaseDialog::onPressKeyBack()
{
    if (!m_bUnCanClose)
    {
        onClose();
    }
}

void BaseDialog::setUnCanClose(bool var)
{
    m_bUnCanClose = var;
    if (m_pClose)
    {
        m_pClose->setVisible(!var);
    }
}

void BaseDialog::onClose(Ref* pSender)
{
    MusicUtil::PlayEffectMusic(SFX_CLICK);
    setUnCanClose(false);
    removeFromParent();
}

void BaseDialog::tip(const string &sText)
{
    if (sText.empty())
    {
        return;
    }
    promptText(Director::getInstance()->getRunningScene(), DEVICE_H / 2, sText.c_str());
}

void BaseDialog::enterSceneAnimation()
{
    EffectUtil::doFadeInAndMoveAction(this, 0.3f, 0xff * 0.58f, 0, nullptr);
    EffectUtil::setEnableRecursiveCascading(m_pContainer, true);
    m_pContainer->setScale(0);
    m_pContainer->setOpacity(0);
    Spawn* pSpawn = Spawn::create(EaseBackOut::create(ScaleTo::create(0.2, m_fScale)), FadeIn::create(0.2),nullptr);
    m_pContainer->runAction(pSpawn);
}

BaseDialog::BaseDialog()
:
m_pContainer(nullptr),
m_pClose(nullptr),
m_oSize(Size::ZERO),
m_fScale(1.0),
m_bTouchIn(false),
m_bUnCanClose(false)
{
}

BaseDialog::~BaseDialog()
{
    CC_SAFE_RELEASE_NULL(m_pContainer);
    CC_SAFE_RELEASE_NULL(m_pClose);
}
