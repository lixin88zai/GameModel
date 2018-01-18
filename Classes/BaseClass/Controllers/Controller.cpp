//
//  Controller.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-28.
//
//

#include "Controller.h"

USING_NS_CC;
using namespace std;

Controller::Controller(const string &sName)
:
m_sName(sName)
{
}

Controller::~Controller()
{
}

void Controller::execute(const std::string &sName, void *pUserData)
{
    log("%s::execute >>> %s", m_sName.c_str(), sName.c_str());
    onEventData(sName, pUserData);
}