//
//  PostionUtil.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/11/11.
//
//

#include "PostionUtil.h"
#include "Util/Utils.h"
#include "Config/AppDef.h"

USING_NS_CC;

namespace util
{
    Vec2 PostionUtil::posSeats[3];
    
    void PostionUtil::initialize()
    {
        posSeats[kSeatBottom] = Vec2(33 * SCALE_X + 50 * SCALE_FIT, 138 * SCALE_FIT);
        posSeats[kSeatRight] =  Vec2(DEVICE_W - 38 * SCALE_X - 50 * SCALE_FIT, DEVICE_H - 164 * SCALE_Y);
        posSeats[kSeatLeft] =  Vec2(38 * SCALE_X + 50 * SCALE_FIT, DEVICE_H - 164 * SCALE_Y);
    }
}
