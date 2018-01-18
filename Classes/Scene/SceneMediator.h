//
//  SceneMediator.h
//  Gouji
//
//  Created by Joi Yao on 16/10/12.
//
//

#pragma once

#include "cocos2d.h"
#include "Mediator.h"
#include "BaseClass/TimeTick/TimeTick.h"
#include "SceneCommon.h"
#include "SceneModel.h"

class SceneMediator : public Mediator, public TimeTick
{
public:
    CREATE_MEDIATOR(SceneMediator);
    virtual std::vector<std::string> listEventNames();
    virtual void handleEventData(const std::string& sEvent, void* pData);
    virtual void onRegister() {}
    virtual void onRemove() {}
    
private:
    void onChange();
    void onClear();
    SceneCommon* getSceneGame(int nPlayType);
    
    SceneMediator();
    ~SceneMediator();
    
private:
    static std::string NAME;
    SceneCommon*    m_pScene;
};
