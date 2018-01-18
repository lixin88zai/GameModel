//
//  MailCommand.cpp
//  PaoDeKuaiPQ
//
//  Created by 曹涛 on 16/11/30.
//
//

#include "MailCommand.h"

// 获取邮件概要，登录轮询使用
WebResult* MailAbstractCommand::parseResult(const rapidjson::Document &obJson)
{
    auto pRet = new GetMailAbstractResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_nTotalNum = readJsonValueInt32(obJson, "total");
    pRet->m_nUnreadNum = readJsonValueInt32(obJson, "unread");
    return pRet;
}

// 获取邮件列表
WebResult* MailListCommand::parseResult(const rapidjson::Document &obJson)
{
    auto pRet = new GetMailListResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_nTotalNum = readJsonValueInt32(obJson, "total");
    pRet->m_nUnreadNum = readJsonValueInt32(obJson, "unread");
    pRet->m_nVer = readJsonValueInt32(obJson, "ver");
    pRet->m_sCurDate = readJsonValueString(obJson, "curdate");
    pRet->m_oMailList.clear();
    const rapidjson::Value& obJsonList = obJson["list"];
    if (obJsonList.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < obJsonList.Size(); i++)
        {
            const rapidjson::Value& obMail = obJsonList[i];
            KKMAIL oData = {};
            oData.sMailId       = readJsonValueString(obMail, "id");
            oData.nStatus       = readJsonValueInt32(obMail, "status");
            oData.sTitle        = readJsonValueString(obMail, "title");
            oData.bHasAttach    = readJsonValueInt32(obMail, "hasattach") != 0;
            oData.bGotAttach    = readJsonValueInt32(obMail, "gotattach") != 0;
            oData.nFromId       = readJsonValueInt64(obMail, "fromid");
            oData.nToId         = readJsonValueInt64(obMail, "toid");
            oData.sSendDate     = readJsonValueString(obMail, "senddate");
            oData.sOutDate      = readJsonValueString(obMail, "outdate");
            oData.bDetailed     = false;
            pRet->m_oMailList.push_back(oData);
        }
    }
    return pRet;
}

// 获取邮件具体信息
WebResult* MailDetailCommand::parseResult(const rapidjson::Document &obJson)
{
    auto pRet = new GetMailDetailResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_oMail = {};
    pRet->m_oMail.sMailId       = readJsonValueString(obJson, "id");
    pRet->m_oMail.nType         = readJsonValueInt32(obJson, "type");
    pRet->m_oMail.nStatus       = readJsonValueInt32(obJson, "status");
    pRet->m_oMail.sTitle        = readJsonValueString(obJson, "title");
    pRet->m_oMail.bHasAttach    = readJsonValueInt32(obJson, "hasattach") != 0;
    pRet->m_oMail.bGotAttach    = readJsonValueInt32(obJson, "gotattach") != 0;
    pRet->m_oMail.nFromId       = readJsonValueInt64(obJson, "fromid");
    pRet->m_oMail.nToId         = readJsonValueInt64(obJson, "toid");
    pRet->m_oMail.sSendDate     = readJsonValueString(obJson, "senddate");
    pRet->m_oMail.sOutDate      = readJsonValueString(obJson, "outdate");
    pRet->m_oMail.sContent      = readJsonValueString(obJson, "content");
    pRet->m_oMail.sExtra        = readJsonValueString(obJson, "extra");
    pRet->m_oMail.sBtnText      = readJsonValueString(obJson, "btntxt");
    pRet->m_oMail.bDetailed     = true;
    const rapidjson::Value& obAttachList = obJson["attach"];
    if (obAttachList.IsArray())
    {
        pRet->m_oMail.oAttaches.clear();
        for (rapidjson::SizeType i = 0; i < obAttachList.Size(); i ++)
        {
            const rapidjson::Value& obAttach = obAttachList[i];
            KAWARDPROPINFO oAttach = {};
            oAttach.nPropId = readJsonValueInt32(obAttach, "propid");
            oAttach.nPropNum = readJsonValueInt32(obAttach, "num");
            pRet->m_oMail.oAttaches.push_back(oAttach);
        }
    }
    return pRet;
}

// 获取邮件附件
WebResult* MailAttachCommand::parseResult(const rapidjson::Document &obJson)
{
    auto pRet = new GetMailAttachResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    pRet->m_sMessage = readJsonValueString(obJson, "reason");
    pRet->m_sMailId = m_sMailId;
    const rapidjson::Value& obAttachList = obJson["attach"];
    if (obAttachList.IsArray())
    {
        pRet->m_oAttach.clear();
        for (rapidjson::SizeType i = 0; i < obAttachList.Size(); i ++)
        {
            const rapidjson::Value& obAttach = obAttachList[i];
            KAWARDPROPINFO oAttach = {};
            oAttach.nPropId = readJsonValueInt32(obAttach, "propid");
            oAttach.nPropNum = readJsonValueInt32(obAttach, "num");
            pRet->m_oAttach.push_back(oAttach);
        }
    }
    return pRet;
}