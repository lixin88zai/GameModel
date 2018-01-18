//
//  HornService.h
//  GouJi
//
//  Created by Joi Yao on 16/10/18.
//
//

#pragma once

#include "CommonService.h"
#include "Protocol/ProtocolEnumDef.h"

class HornServiceDelegate
{
public:
    // 使用喇叭通知
    DELEGATE_FUNC(OnNTFUseHorn);
};

class HornService : public CommonService
{
public:
    static HornService* getInstance();
    
    virtual void ConfigureMsgs();
    bool HasDelegate() { return m_pDelegate != nullptr; }
    void SetDelegate(HornServiceDelegate *pDelegate) { m_pDelegate = pDelegate; }
    HornServiceDelegate* GetDelegate() { return m_pDelegate; }

    HornService()
    :
    m_pDelegate(nullptr)
    {
    }
    
public:
    // 使用喇叭通知
    SERVICE_FUNC(OnNTFUseHorn);
    
private:
    HornServiceDelegate* m_pDelegate;
};
