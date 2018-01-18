//
//  HallLayer.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/24.
//
//

#include "HallFooter.h"
#include "Util/Utils.h"
#include "Config/Config.h"

void HallFooter::initContent()
{
    auto pFooterBg = ui::Scale9Sprite::create(HALL_BG_BACK);
    pFooterBg->setCapInsets(Rect(85, 10, 60, 70));
    pFooterBg->setContentSize(Size(DEVICE_W / SCALE_FIT - 92, 86));
    pFooterBg->setPosition(0, pFooterBg->getContentSize().height / 2);
    m_pContainer->addChild(pFooterBg);
    
    
}

HallFooter::HallFooter()
{
    
}

HallFooter::~HallFooter()
{
    
}
