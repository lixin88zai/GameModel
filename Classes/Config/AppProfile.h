//
//  AppProfile.h
//  GouJi
//
//  Created by ZengQi on 16/4/25.
//
//

#ifndef AppProfile_h
#define AppProfile_h

#include "cocos2d.h"

namespace profile
{
    // 是否定制版本（定制版本禁用游客及账号安全相关功能）
    bool isCusomizedVersion();
    
    // 是否启用推荐功能
    bool isInviteEnbaled();
    
    // 是否启用分享功能
    bool isShareEnabled();
  
    // 是否启用自动更新功能
    bool isAutoUpdateEnabled();
}

#endif /* AppProfile_h */
