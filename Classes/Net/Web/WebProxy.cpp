//
//  WebProxy.cpp
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#include "WebProxy.h"
#include "Util/Utils.h"

// JSON串错误定义
#define JSON_ERRCODE_STRING             "{\"code\":-10}"
#define JSON_ERRCODE_GZIP               "{\"code\":-20}"

USING_NS_CC;
using namespace std;
using namespace util;
using namespace cocos2d::network;

#define MAX_RETRY_COUNT 2

class WebRequestCounter
{
public:
    WebRequestCounter(WebCommand *pCommand, int nRetryCount);
    ~WebRequestCounter();
    
    WebCommand* getWebCommand();
    int getRetryCount();
    bool retry();
    
private:
    WebCommand* m_pCommand;
    int         m_nRetryCount;
};

WebRequestCounter::WebRequestCounter(WebCommand *pCommand, int nRetryCount)
:
m_pCommand(pCommand),
m_nRetryCount(nRetryCount)
{
}

WebRequestCounter::~WebRequestCounter()
{
    delete m_pCommand;
    m_pCommand = nullptr;
}

WebCommand* WebRequestCounter::getWebCommand()
{
    return m_pCommand;
}

int WebRequestCounter::getRetryCount()
{
    return m_nRetryCount;
}

bool WebRequestCounter::retry()
{
    if (m_nRetryCount <= 0)
    {
        return false;
    }
    m_nRetryCount--;
    return true;
}

WebProxy::WebProxy()
:
m_pClient(nullptr),
m_sRootURL("localhost")
{
}

WebProxy::~WebProxy()
{
    m_pClient = nullptr;
}

void WebProxy::init(HttpClient *pClient, const string &sRootURL)
{
    m_pClient = pClient;
    m_sRootURL = sRootURL;
}

bool WebProxy::get(WebCommand *pCommand)
{
    return send(pCommand, HttpRequest::Type::GET);
}

bool WebProxy::post(WebCommand *pCommand)
{
    return send(pCommand, HttpRequest::Type::POST);
}

bool WebProxy::send(WebCommand *pCommand, HttpRequest::Type eMethod)
{
    if (m_pClient == nullptr)
    {
        return false;
    }
	
	HttpRequest* pRequest = new HttpRequest();
    configureRequest(pRequest, pCommand, eMethod);
    
    pRequest->setUserData(new WebRequestCounter(pCommand, MAX_RETRY_COUNT));
    
    log("WebProxy::send >>> URL=%s", pRequest->getUrl());
    log("WebProxy::send >>> Method=%s", eMethod == HttpRequest::Type::GET ? "GET" : "POST");
    log("WebProxy::send >>> Data=%s", string(pRequest->getRequestData(), pRequest->getRequestDataSize()).c_str());
    
    m_pClient->send(pRequest);
    pRequest->release();
    
    return true;
}

bool WebProxy::resend(HttpRequest *pRequest)
{
    if (m_pClient == nullptr)
    {
        return false;
    }
    
    WebRequestCounter *pCounter = static_cast<WebRequestCounter *>(pRequest->getUserData());
    WebCommand *pCommand = pCounter->getWebCommand();
    HttpRequest::Type eMethod = pRequest->getRequestType();
    configureRequest(pRequest, pCommand, eMethod);
    
    log("WebProxy::resend >>> URL=%s", pRequest->getUrl());
    log("WebProxy::resend >>> Method=%s", eMethod == HttpRequest::Type::GET ? "GET" : "POST");
    log("WebProxy::resend >>> Data=%s", string(pRequest->getRequestData(), pRequest->getRequestDataSize()).c_str());
    
    m_pClient->send(pRequest);
    
    return true;
}

void WebProxy::configureRequest(HttpRequest *pRequest, WebCommand *pCommand, HttpRequest::Type eMethod)
{
    string sURL = m_sRootURL + pCommand->getActionURI();
    string sData = pCommand->getVariables()->toURLEncodedString();
    pRequest->setRequestType(eMethod);
    if (eMethod == HttpRequest::Type::GET)
    {
        if (!sData.empty())
        {
            sURL.append("?").append(sData);
        }
    }
    else
    {
        pRequest->setRequestData(sData.c_str(), sData.size());
    }
    pRequest->setUrl(sURL.c_str());
    pRequest->setResponseCallback(CC_CALLBACK_2(WebProxy::onHttpResponse, this));
}

void WebProxy::onHttpResponse(HttpClient *pClient, HttpResponse *pResponse)
{
    if (pResponse == nullptr)
	{
        log("WebProxy::onHttpResponse >>> 响应为空");
	    return;
	}
    
    WebRequestCounter *pCounter = static_cast<WebRequestCounter *>(pResponse->getHttpRequest()->getUserData());
    
    log("WebProxy::onHttpResponse >>> ActionURI=%s", pCounter->getWebCommand()->getActionURI().c_str());
    log("WebProxy::onHttpResponse >>> StatusCode=%ld", pResponse->getResponseCode());
    log("WebProxy::onHttpResponse >>> Succeed=%s", pResponse->isSucceed() ? "TRUE" : "FALSE");
    
    string sResponseData;
    
    if (pResponse->isSucceed())
    {
        vector<char> *pBuffer = pResponse->getResponseData();
        sResponseData.assign(pBuffer->begin(), pBuffer->end());
    }
    else
    {
        log("WebProxy::onHttpResponse >>> Reason=%s", pResponse->getErrorBuffer());
        if (pCounter->retry())
        {
            log("WebProxy::onHttpResponse >>> Retry=%d", pCounter->getRetryCount());
            resend(pResponse->getHttpRequest());
            return;
        }
        sResponseData.assign(JSON_ERRCODE_STRING);
    }
    
    log("WebProxy::onHttpResponse >>> Data=%s", sResponseData.c_str());
    
    pCounter->getWebCommand()->onRespond(sResponseData);
    
    delete pCounter;
}