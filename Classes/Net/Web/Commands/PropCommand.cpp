//
//  PropCommand.cpp
//  PaoDeKuaiPQ
//
//  Created by lzq on 2016/12/1.
//
//

/*
 Data={"code": 0, "props": [{"time_left": 0, "num": 10, "type": 1, "id": 1019}]}
 */
#include "PropCommand.h"
#include "Util/macroUtil.h"

using namespace util;

WebResult* PropDetailCommand::parseResult(const rapidjson::Document &obJson)
{
    PropDetailResult* pRet = new PropDetailResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code");
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    
    const rapidjson::Value &oJsonList = obJson["props"];
    if (oJsonList.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < oJsonList.Size(); i++)
        {
            KAWARDPROPINFO oDetail = {};
            oDetail.nPropId = readJsonValueInt32(oJsonList[i], "id");
            oDetail.nPropNum = readJsonValueInt32(oJsonList[i], "num");
            pRet->m_oPropDetailList.push_back(oDetail);
        }
    }
    return pRet;
}
