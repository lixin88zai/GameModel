//
//  PropConfig.cpp
//  PaoDeKuaiPQ
//
//  Created by ChuKun on 16/12/1.
//
//

#include "PropConfig.h"
#include <string.h>

static const int PROP_TOTAL = 1;

static const PropInfoConfig PROP_INFOS[PROP_TOTAL] =
{
    {PROP_ID_ROOMCARD,              "房卡",               "",              "用于创建房间",           "张"}
};

namespace config
{
    std::string getPropName(const int& nPropId)
    {
        std::string sName = "";
        for (int i = 0; i < PROP_TOTAL; i++)
        {
            if (PROP_INFOS[i].nPropId == nPropId)
            {
                sName = PROP_INFOS[i].sName;
            }
        }
        return sName;
    }
    
    std::string getPropIcon(const int& nPropId)
    {
        std::string sIcon = "";
        for (int i = 0; i < PROP_TOTAL; i++)
        {
            if (PROP_INFOS[i].nPropId == nPropId)
            {
                sIcon = PROP_INFOS[i].sIcon;
                break;
            }
        }
        return sIcon;
    }
    
    std::string getPropDes(const int& nPropId)
    {
        std::string sDes = "";
        for (int i = 0; i < PROP_TOTAL; i++)
        {
            if (PROP_INFOS[i].nPropId == nPropId)
            {
                sDes = PROP_INFOS[i].sDes;
                break;
            }
        }
        return sDes;
    }
    
    std::string getPropUnit(const int& nPropId)
    {
        std::string sUnit = "";
        for (int i = 0; i < PROP_TOTAL; i++)
        {
            if (PROP_INFOS[i].nPropId == nPropId)
            {
                sUnit = PROP_INFOS[i].sUnit;
                break;
            }
        }
        return sUnit;
    }
}
