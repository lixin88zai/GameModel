//
//  PrivyCommand.cpp
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/28.
//
//

#include "PrivyCommand.h"

// 解析配桌
PKMATCHINFO parseMatchInfo(const rapidjson::Document &obJson)
{
    PKMATCHINFO oRet = {};
    if (obJson.HasMember("matchinfo"))
    {
        const rapidjson::Value &obJsonMatchInfo = obJson["matchinfo"];
        oRet.nRoomId = readJsonValueInt32(obJsonMatchInfo, "roomid");
        oRet.nTableId = readJsonValueInt32(obJsonMatchInfo, "tableid");
    }
    return oRet;
}
// 解析房间信息
PKROOM parseRoomInfo(const rapidjson::Document &obJson, int nRoomId)
{
    PKROOM oRet = {};
    oRet.nRoomId = nRoomId;
    if (obJson.HasMember("roominfo"))
    {
        const rapidjson::Value &obJsonRoom = obJson["roominfo"];
        //oRet.nRoomId = readJsonValueInt32(obJsonRoom, "roomid");
        oRet.nRoomType = readJsonValueInt32(obJsonRoom, "roomtype");
        oRet.nPlayType = readJsonValueInt32(obJsonRoom, "playtype");
        oRet.sRoomName = readJsonValueString(obJsonRoom, "roomname");
        oRet.nTotalGames = readJsonValueInt32(obJsonRoom, "games");
        oRet.nTotalPlayers = readJsonValueInt32(obJsonRoom, "players");
        oRet.bSpade3First = readJsonValueInt32(obJsonRoom, "s3first") == 1;
        oRet.nDealTime = readJsonValueInt32(obJsonRoom, "deal_time");
        oRet.nFirstPlayTime = readJsonValueInt32(obJsonRoom, "first_play_time");
        oRet.nPlayTime = readJsonValueInt32(obJsonRoom, "playtime");
        oRet.nFollowTime = readJsonValueInt32(obJsonRoom, "followtime");
    }
    return oRet;
}
//________________________________________________
// 配置
WebResult* PrivyConfigCommand::parseResult(const rapidjson::Document &obJson)
{
    PrivyConfigResult* pRet = new PrivyConfigResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code");
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_oConfig = {};
    if (obJson.HasMember("playtypes"))
    {
        const rapidjson::Value &obJsonPlayTypes = obJson["playtypes"];
        if (obJsonPlayTypes.IsArray())
        {
            for (rapidjson::SizeType i = 0; i < obJsonPlayTypes.Size(); i ++)
            {
                pRet->m_oConfig.oPlayTypes.push_back(obJsonPlayTypes[i].GetInt());
            }
        }
    }
    if (obJson.HasMember("players"))
    {
        const rapidjson::Value &obJsonPlayers = obJson["players"];
        for (rapidjson::SizeType i = 0; i < obJsonPlayers.Size(); i ++)
        {
            pRet->m_oConfig.oCntPlayers.push_back(obJsonPlayers[i].GetInt());
        }
    }
    if (obJson.HasMember("games"))
    {
        const rapidjson::Value &obJsonGames = obJson["games"];
        for (rapidjson::SizeType i = 0; i < obJsonGames.Size(); i ++)
        {
            pRet->m_oConfig.oCntGames.push_back(obJsonGames[i].GetInt());
        }
    }
    if (obJson.HasMember("costs"))
    {
        const rapidjson::Value &obJsonCosts = obJson["costs"];
        for (rapidjson::SizeType i = 0; i < obJsonCosts.Size(); i ++)
        {
            pRet->m_oConfig.oCntCosts.push_back(obJsonCosts[i].GetInt());
        }
    }
    pRet->m_oConfig.bSpade3First = readJsonValueInt32(obJson, "bs3first") == 1;
    return pRet;
}
//________________________________________________
// 创建
WebResult* PrivyCreateCommand::parseResult(const rapidjson::Document &obJson)
{
    PrivyCreateResult* pRet = new PrivyCreateResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code");
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_nPrivyId = readJsonValueInt32(obJson, "privyid");
    pRet->m_obMatchInfo = parseMatchInfo(obJson);
    pRet->m_obRoomInfo = parseRoomInfo(obJson, pRet->m_nPrivyId);
    return pRet;
}
//________________________________________________
// 加入
WebResult* PrivyJoinCommand::parseResult(const rapidjson::Document &obJson)
{
    PrivyJoinResult* pRet = new PrivyJoinResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code");
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_nPrivyId = readJsonValueInt32(obJson, "privyid");
    pRet->m_obMatchInfo = parseMatchInfo(obJson);
    pRet->m_obRoomInfo = parseRoomInfo(obJson, pRet->m_nPrivyId);
    return pRet;
}
//________________________________________________
// 获取房间配置
WebResult* GetRoomInfoCommand::parseResult(const rapidjson::Document &obJson)
{
    GetRoomInfo* pRet = new GetRoomInfo();
    pRet->m_nCode = readJsonValueInt32(obJson, "code");
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_nPrivyId = readJsonValueInt32(obJson, "tableid");
    pRet->m_obMatchInfo = parseMatchInfo(obJson);
    pRet->m_obRoomInfo = parseRoomInfo(obJson, pRet->m_nPrivyId);
    return pRet;
}