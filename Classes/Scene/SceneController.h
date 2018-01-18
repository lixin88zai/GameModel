//
//  SceneController.h
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#pragma once

#include "Controller.h"
#include "Config/AppDef.h"

class SceneController : public Controller
{
public:
    SceneController();
    virtual void listEventNames();
    virtual void onEventData(const std::string& sName, void *pUserData);
    
    void onChange(SCENE eScene);
    void onEnter();
};
