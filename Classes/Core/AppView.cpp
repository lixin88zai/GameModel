//
//  AppView.cpp
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#include "AppView.h"
#include "Scene/SceneMediator.h"

USING_NS_CC;
using namespace std;

static AppView* s_pInstance = nullptr;

AppView* AppView::getInstance()
{
    if (nullptr == s_pInstance)
    {
        s_pInstance = new AppView();
    }
    return s_pInstance;
}

void AppView::initialize()
{
    // 初始化单场景
    m_pSingleScene = Scene::create();
    CC_SAFE_RETAIN(m_pSingleScene);
    
    // 初始化图层
    for (int i = LAYER::kLayerBackground; i <= LAYER::kLayerErr; i ++)
    {
        Layer *pLayer = Layer::create();
        pLayer->setTag(i);
        m_pSingleScene->addChild(pLayer);
        m_obLayerVector.pushBack(pLayer);
    }
    //初始化场景mediator
    registerMediator(SceneMediator::create());
    // 启动
    Director::getInstance()->runWithScene(m_pSingleScene);
}

Layer* AppView::getLayer(LAYER eType)
{
    Layer* pResult = nullptr;
    for (ssize_t i = 0; i < m_obLayerVector.size(); i++)
    {
        Layer* pItem = m_obLayerVector.at(i);
        if (eType == pItem->getTag())
        {
            pResult = pItem;
            break;
        }
    }
    return pResult;
}

void AppView::addTo(LAYER eType, Node *pComponent)
{
    if (pComponent == nullptr)
    {
        return;
    }
    Layer *pLayer = getLayer(eType);
    if (pLayer == nullptr)
    {
        return;
    }
    pLayer->addChild(pComponent);
}

void AppView::clear()
{
    for (ssize_t i = 0; i < m_obLayerVector.size(); i++)
    {
        m_obLayerVector.at(i)->removeAllChildren();
    }
}

Mediator* AppView::getMediator(const string& sMediatorName)
{
    return m_obMediatorMap.at(sMediatorName);
}

void AppView::registerMediator(Mediator *pMediator)
{
    if (pMediator == nullptr)
    {
        return;
    }
    string sMediatorName = pMediator->getName();
    if (m_obMediatorMap.at(sMediatorName) != nullptr)
    {
        return;
    }
    pMediator->addObserver();
    pMediator->onRegister();
    m_obMediatorMap.insert(sMediatorName, pMediator);
}

void AppView::removeMediator(const string &sMediatorName)
{
    Mediator* pMediator = m_obMediatorMap.at(sMediatorName);
    if (pMediator == nullptr)
    {
        return;
    }
    pMediator->removeObservser();
    pMediator->onRemove();
    m_obMediatorMap.erase(sMediatorName);
}

AppView::AppView()
:
m_pSingleScene(nullptr),
m_obMediatorMap()
{
}

AppView::~AppView()
{
    m_obLayerVector.clear();
    m_obMediatorMap.clear();
}
