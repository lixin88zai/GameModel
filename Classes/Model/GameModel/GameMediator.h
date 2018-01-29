//
//  HallMediator.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "Mediator.h"
#include "BaseClass/TimeTick/TimeTick.h"
#include "Config/Config.h"
#include "GameLayer.h"
#include "GameDeck.h"

class GameMediator : public Mediator, public TimeTick
{
public:
    CREATE_MEDIATOR(GameMediator);
    virtual std::vector<std::string> listEventNames();
    virtual void handleEventData(const std::string& sEvent, void* pData);
    virtual void onRegister();
    virtual void onRemove();
    virtual void onExitComplete();
    
    
    void onButtonClick(cocos2d::EventCustom* pEvent);
    
private:
    GameMediator();
    ~GameMediator();

public:
    static std::string NAME;
    
private:
    cocos2d::Layer* m_pDialogLayer;
    vector<GameDeck*> m_oPlayerDeckVec;
    GameLayer* m_oGameLayer;
};
