//
//  LoginCommand.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#include "LoginCommand.h"
#include "Util/ReaderWriter.h"

LoginResult* parseLoginResult(const rapidjson::Document &obJson)
{
    LoginResult *pRet = new LoginResult();
    
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    pRet->m_bPlaying = (bool)readJsonValueInt32(obJson, "isplay");
    pRet->m_sSessionKey = readJsonValueString(obJson, "session_key");
    if (obJson.HasMember("userinfo"))
    {
        const rapidjson::Value &obJsonUserInfo = obJson["userinfo"];
        pRet->m_obUserInfo.nUserId = readJsonValueUint64(obJsonUserInfo, "userid");
        pRet->m_obUserInfo.nGender = readJsonValueInt32(obJsonUserInfo, "gender");
        pRet->m_obUserInfo.sNick = readJsonValueString(obJsonUserInfo, "nick");
        pRet->m_obUserInfo.sIP = readJsonValueString(obJsonUserInfo, "ip");
        pRet->m_obUserInfo.sFaceURL = readJsonValueString(obJsonUserInfo, "face");
        printf("sFaceURL = %s",pRet->m_obUserInfo.sFaceURL.c_str());
    }
    if (obJson.HasMember("connsvrd"))
    {
        const rapidjson::Value &obJsonBroad= obJson["connsvrd"];
        pRet->m_oConnInfo.sHost = readJsonValueString(obJsonBroad, "host");
        pRet->m_oConnInfo.nPort = readJsonValueInt32(obJsonBroad, "port");
    }
    if(obJson.HasMember("qqmsg")){
        const rapidjson::Value &obJsonQQMsg = obJson["qqmsg"];
        pRet->m_oQQGroupInfo.qqNumber = readJsonValueString(obJsonQQMsg, "number");
        pRet->m_oQQGroupInfo.qqGroupUrl = readJsonValueString(obJsonQQMsg, "url");
    }
    return pRet;
}

WebResult* CommonLoginCommand::parseResult(const rapidjson::Document &obJson)
{
    return parseLoginResult(obJson);
}

WebResult* GuestLoginCommand::parseResult(const rapidjson::Document &obJson)
{
    return parseLoginResult(obJson);
}

WebResult* WechatLoginCommand::parseResult(const rapidjson::Document &obJson)
{
    WebResult* pRet = parseLoginResult(obJson);
    //微信登录时返回token到期时间（剩余时间，单位秒）
    if (obJson.HasMember("token") && obJson.HasMember("expirein")) {
        int expirein = (int)time(nullptr) + readJsonValueInt32(obJson, "expirein");
        std::string refreshtoken = readJsonValueString(obJson, "token");
        util::ReaderWriter::SaveStringToXML("token", refreshtoken);
        util::ReaderWriter::SaveIntegerToXML("expirein", expirein);
    }
    return pRet;
}

WebResult* CheckLoginCommand::parseResult(const rapidjson::Document &obJson)
{
    WebResult *pRet = new WebResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    return pRet;
}

WebResult* CheckVersionCommand::parseResult(const rapidjson::Document &obJson)
{
    CheckVersionResult *pRet = new CheckVersionResult();
    pRet->m_nCode = readJsonValueInt32(obJson, "code", -1);
    return pRet;
}