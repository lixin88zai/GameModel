//
//  ControllerManager.h
//  GouJi
//
//  Created by 曾琪 on 14-9-26.
//
//

#ifndef GouJi_ControllerManager_h
#define GouJi_ControllerManager_h

#include "cocos2d.h"
#include "Controller.h"
#include "BaseClass/Event/EventWrapper.h"

class ControllerManager : public EventWrapper
{
public:
    static ControllerManager* getInstance();
    
    ControllerManager();
    ~ControllerManager();
    
    void initialize();
    
private:
    void registerController(Controller* pController);
    void mapController(const std::string &sEventName, Controller *pController);
    
private:
    void onEventReceived(cocos2d::EventCustom *pEvent);
    
private:
    cocos2d::Map<std::string, Controller*> m_obControllerMap;
    
};

#endif
