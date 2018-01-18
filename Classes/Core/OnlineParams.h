//
//  OnlineParams.h
//  GouJi
//
//  Created by ZengQi on 15-2-4.
//
//

#ifndef __GouJi__OnlineParams__
#define __GouJi__OnlineParams__

#define KEY_INREVIEWCHANNEL         "in_review_channel"

#include "MobClickCpp.h"
#include "Util/ReaderWriter.h"
#include "Net/Web/Commands/OnlineConfigCommand.h"
#include "BaseClass/Event/EventWrapper.h"

class OnlineParams : public EventWrapper
{
public:
    static OnlineParams* getInstance();
    OnlineParams();
    ~OnlineParams();
    
public:
    void initialize();
    virtual void onUpdateFinished(bool succeed, void* pUserData);
    
    void doGetOnlineConfig();
    void onGetOnlineConfigComplete(WebResult* pResult);
    
    bool inReview()
    {
        return m_bInReview;
    }
    
private:
    bool m_bInReview;
    
private:
    std::string readUmengConfigParamString(const char* pszKey);
    bool readUmengConfigParamBool(const char* pszKey);
    bool readUmengConfigParamBool(const char* pszKey, const char* pszPattern);
    bool isIPv6Enabled();
};

#endif /* defined(__GouJi__OnlineParams__) */
