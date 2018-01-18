//
//  AppProfile.cpp
//  GouJi
//
//  Created by ZengQi on 16/4/25.
//
//

#include "AppProfile.h"

enum ProfileLevel
{
    ENABLED,
    DISABLED,
    DISABLED_IN_REVIEW
};

// 是否定制版本
static const bool CUSTOMIZED_VERSION = false;

// 推荐功能开放等级
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static const ProfileLevel LEVEL_INVITE = DISABLED_IN_REVIEW;
#else
static const ProfileLevel LEVEL_INVITE = ENABLED;
#endif

// 分享功能开放等级
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static const ProfileLevel LEVEL_SHARE = DISABLED_IN_REVIEW;
#else
static const ProfileLevel LEVEL_SHARE = DISABLED_IN_REVIEW;
#endif


// 自动更新功能开放等级
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
static const ProfileLevel LEVEL_AUTOUPDATE = DISABLED_IN_REVIEW;
#else
static const ProfileLevel LEVEL_AUTOUPDATE = DISABLED_IN_REVIEW;
#endif

namespace profile
{
    bool isFunctionEnabled(ProfileLevel eLevel, int nThreshold = 0)
    {
        if (eLevel == DISABLED_IN_REVIEW)
        {
            return false;
        }
        return eLevel == ENABLED;
    }
    
    // 是否定制版本（定制版本禁用游客及账号安全相关功能）
    bool isCusomizedVersion()
    {
        return CUSTOMIZED_VERSION;
    }
    
    // 是否启用推荐功能
    bool isInviteEnbaled()
    {
        return isFunctionEnabled(LEVEL_INVITE);
    }
    
    // 是否启用分享功能
    bool isShareEnabled()
    {
        return isFunctionEnabled(LEVEL_SHARE);
    }
    
    // 是否启用自动更新功能
    bool isAutoUpdateEnabled()
    {
        return isFunctionEnabled(LEVEL_AUTOUPDATE);
    }
}
