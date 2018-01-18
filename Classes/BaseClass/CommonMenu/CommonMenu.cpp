//
//  CommonMenu.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/25.
//
//

#include "CommonMenu.h"
#include "Util/Utils.h"
#include "Config/Config.h"

USING_NS_CC;
using namespace std;
using namespace util;

bool CommonMenu::init(const vector<KKMENU> &oMenus)
{
    bool bRet = false;
    do
    {
        CC_BREAK_IF(!Node::init());
        
        m_oMenus = oMenus;
        initView();
        
        bRet = true;
    } while (0);
    return bRet;
}

void CommonMenu::onMenuClick(cocos2d::Ref *pEvent, MENU eMenu)
{
    MusicUtil::PlayEffectMusic(SFX_CLICK);
    Value oData = Value(eMenu);
    dispatchEvent(NTF_MENU_CLICK, &oData);
}
