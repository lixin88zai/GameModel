//
//  ScrollViewMenu.cpp
//  GouJi
//
//  Created by 张旭 on 15/6/17.
//
//

#include "ScrollViewMenu.h"
USING_NS_CC;

ScrollViewMenu::ScrollViewMenu(const Rect &VisibleRect, Node* pNode)
{
    m_VisibleRect = VisibleRect;
    m_StartPoint = Vec2::ZERO;
    m_bMoved = false;
    m_pVisibleNode = pNode;
    m_pVisibleNode->retain();
}

ScrollViewMenu::~ScrollViewMenu()
{
    m_pVisibleNode->release();
}

ScrollViewMenu* ScrollViewMenu::create(const  Rect &VisibleRect, Node* pNode)
{
    ScrollViewMenu* pRet=new ScrollViewMenu(VisibleRect, pNode);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return pRet;
}

bool ScrollViewMenu::init()
{
    return initWithArray(Vector<MenuItem*>());
}

bool ScrollViewMenu::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
    if (Layer::init())
    {
        _enabled = true;
        // menu in the center of the screen
        Size s = Director::getInstance()->getWinSize();
        
        this->ignoreAnchorPointForPosition(true);
        setAnchorPoint(Vec2(0.5f, 0.5f));
        this->setContentSize(s);
        
        setPosition(s.width/2, s.height/2);
        
        int z=0;
        
        for (auto& item : arrayOfItems)
        {
            this->addChild(item, z);
            z++;
        }
        
        _selectedItem = nullptr;
        _state = Menu::State::WAITING;
        
        // enable cascade color and opacity on menus
        setCascadeColorEnabled(true);
        setCascadeOpacityEnabled(true);
        
        
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(false);
        
        touchListener->onTouchBegan = CC_CALLBACK_2(Menu::onTouchBegan, this);
        touchListener->onTouchMoved = CC_CALLBACK_2(Menu::onTouchMoved, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(Menu::onTouchEnded, this);
        touchListener->onTouchCancelled = CC_CALLBACK_2(Menu::onTouchCancelled, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
    }
    return false;
}

bool ScrollViewMenu::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    m_VisibleRect.origin = Vec2::ZERO;
    Point cp = m_pVisibleNode->convertToNodeSpace(pTouch->getLocation());
    if(m_VisibleRect.containsPoint(cp))
    {}
    else
    {
        return false;
    }
    m_StartPoint = pTouch->getLocation();
    m_bMoved=false;
    return Menu::onTouchBegan(pTouch, pEvent);
}

void ScrollViewMenu::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    Point obMovePoint = pTouch->getLocation();
    float fPointX = obMovePoint.x - m_StartPoint.x;
    float fPointY = obMovePoint.y - m_StartPoint.y;
    if((fPointX * fPointX > 100) || (fPointY * fPointY > 100))
    {
        m_bMoved=true;
    }
    if (m_bMoved)
    {
        if(_selectedItem)
        {
            _selectedItem->unselected();
        }
    }
    else
    {
        return Menu::onTouchMoved(pTouch, pEvent);
    }
}

void ScrollViewMenu::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    if(!m_bMoved)
    {
        Menu::onTouchEnded(pTouch, pEvent);
    }
    else
    {
        _state = Menu::State::WAITING;
        if(_selectedItem)
        {
            _selectedItem->unselected();
        }
    }
}