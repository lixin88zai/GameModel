//
//  PropConfig.h
//  PaoDeKuaiPQ
//
//  Created by ChuKun on 16/12/1.
//
//

#pragma once
#include <stdio.h>
#include <string>

#define PROP_ID_ROOMCARD                    1019   // 房卡

using namespace std;

struct PropInfoConfig
{
    int                     nPropId;
    std::string             sName;
    std::string             sIcon;
    std::string             sDes;
    std::string             sUnit; // 单位
};

namespace config
{
    std::string getPropName(const int& nPropId);
    std::string getPropIcon(const int& nPropId);
    std::string getPropDes(const int& nPropId);
    std::string getPropUnit(const int& nPropId);
}
