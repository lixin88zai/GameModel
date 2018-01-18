//
//  PostionUtil.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/11/11.
//
//

#pragma once
#include "cocos2d.h"

namespace util
{
    class PostionUtil
    {
    public:
        static void initialize();
    public:
        static cocos2d::Vec2 posSeats[3];
    };
    // 统一宏定义
#define POS_SEAT    util::PostionUtil::posSeats
}
