//
//  WebProxy.h
//  GouJi
//
//  Created by 曾琪 on 14-9-23.
//
//

#ifndef GouJi_WebProxy_h
#define GouJi_WebProxy_h

#include <string>
#include "network/HttpClient.h"
#include "Net/Web/WebCommand.h"

class WebProxy
{
public:
    WebProxy();
    ~WebProxy();
    
    void init(cocos2d::network::HttpClient *pClient, const std::string &sRootURL);
    
public:
    bool get(WebCommand *pCommand);
    bool post(WebCommand *pCommand);
    
private:
    bool send(WebCommand *pCommand, cocos2d::network::HttpRequest::Type eMethod);
    bool resend(cocos2d::network::HttpRequest *pRequest);
    void configureRequest(cocos2d::network::HttpRequest *pRequest, WebCommand *pCommand, cocos2d::network::HttpRequest::Type eMethod);
    
    void onHttpResponse(cocos2d::network::HttpClient* pClient, cocos2d::network::HttpResponse* pResponse);
    
private:
    cocos2d::network::HttpClient    *m_pClient;
    std::string                     m_sRootURL;
};

#endif
