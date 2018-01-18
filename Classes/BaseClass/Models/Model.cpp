//
//  Model.cpp
//  GouJi
//
//  Created by ZengQi on 14-11-24.
//
//

#include "Model.h"

using namespace std;

Model* Model::create()
{
    Model* pRet = new Model("Model");
    if (pRet)
    {
        pRet->init();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    pRet = nullptr;
    return nullptr;
}

Model::Model(const string &sName)
:
m_sName(sName)
{
}

Model::~Model()
{
}