//
//  MatchService.h
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#pragma once

#include "CommonService.h"
#include "Protocol/ProtocolEnumDef.h"

class MatchServiceDelegate
{
public:
    DELEGATE_FUNC(OnACKMatchTable);
};

class MatchService : public CommonService
{
public:
    static MatchService* getInstance();
    
    virtual void ConfigureMsgs();
    bool HasDelegate() { return m_pDelegate != nullptr; }
    void SetDelegate(MatchServiceDelegate *pDelegate) { m_pDelegate = pDelegate; }
    MatchServiceDelegate* GetDelegate() { return m_pDelegate; }
    
    MatchService()
    :
    m_pDelegate(nullptr)
    {
    }
    
    void SendMatchTable(int nRoomId);
    
public:
    SERVICE_FUNC(OnACKMatchTable);
    
private:
    MatchServiceDelegate* m_pDelegate;
};
