//
//  WebCommand.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#include "WebCommand.h"
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

WebCommand::WebCommand(string sActionURI, WebResultCallback pCallback)
:
m_sActionURI(sActionURI),
m_pCallback(pCallback)
{
}

WebCommand::~WebCommand()
{
}

string WebCommand::getActionURI()
{
    return m_sActionURI;
}

WebVariables* WebCommand::getVariables()
{
    return &m_obVariables;
}

void WebCommand::onRespond(const string &sResponseData)
{
    if (sResponseData.empty())
    {
        // 响应数据为空
        log("WebCommand::onRespond >>> 响应数据为空");
        return;
    }
    
    rapidjson::Document obJson;
    obJson.Parse<rapidjson::kParseDefaultFlags>(sResponseData.c_str());
    
    if (obJson.HasParseError())
    {
        // 响应数据为空
        log("WebCommand::onRespond >>> JSON解析错误");
        return;
    }
    
    if (m_pCallback != nullptr)
    {
        WebResult *pResult = parseResult(obJson);
        m_pCallback(pResult);
        delete pResult;
    }
}
