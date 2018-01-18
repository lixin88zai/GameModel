//
//  HallLayer.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#pragma once

#include "BaseClass/BaseLayer/NoFullLayer.h"

class HallFooter : public NoFullLayer
{
public:
    CREATE_FUNC(HallFooter);
    HallFooter();
    ~HallFooter();
    virtual void initContent();
};
