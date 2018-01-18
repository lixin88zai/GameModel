//
//  ConnectingLayer.h
//  
//
//  Created by Joi Yao on 16/10/20.
//
//

#pragma once

#include "Util/ModalLayer.h"

class ConnectingLayer : public util::ModalLayer
{
public:
    static ConnectingLayer* getInstance();
    void show(const std::string& sText);
    void hide();
    
protected:
    CREATE_FUNC(ConnectingLayer);
    virtual bool init();
    
    ConnectingLayer();
    ~ConnectingLayer();
    
private:
    cocos2d::Label* m_pLabel;
};