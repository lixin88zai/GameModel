//
//  Model.cpp
//  GouJi
//
//  Created by ZengQi on 14-11-24.
//
//

#include "NoFullLayer.h"
#include "Util/Utils.h"

using namespace std;
bool NoFullLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    initContainer();
    initContent();
    return true;
}


void NoFullLayer::initContainer()
{
    m_pContainer  = Node::create();
    m_pContainer->setScale(SCALE_FIT);
    addChild(m_pContainer);
}

NoFullLayer::NoFullLayer()
{
    
}
NoFullLayer::~NoFullLayer()
{
    
}
