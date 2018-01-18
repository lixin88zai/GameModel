//
//  CheckInReviewCommand.cpp
//  PaoDeKuaiPQ
//
//  Created by 曹涛 on 16/12/1.
//
//

#include "OnlineConfigCommand.h"

// 获取在线参数信息
WebResult* OnlineConfigCommand::parseResult(const rapidjson::Document &obJson)
{
    auto pRet = new OnlineConfigResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    if (obJson.HasMember("inreview")) {
        pRet->m_bInReview = readJsonValueBool(obJson, "inreview");
    }
    if (obJson.HasMember("broadcastinfo")) {
        const rapidjson::Value &obJsonBroadCastInfo = obJson["broadcastinfo"];
        for (int i=0; i<obJsonBroadCastInfo.Size(); i++)
        {
            std::string str = (obJsonBroadCastInfo.onBegin()+i)->GetString();
            pRet->oMessageList.push_back(str);
        }
    }
    return pRet;
}