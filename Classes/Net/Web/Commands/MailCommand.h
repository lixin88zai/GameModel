//
//  MailCommand.h
//  PaoDeKuaiPQ
//
//  Created by 曹涛 on 16/11/30.
//
//

#ifndef __PaoDeKuaiPQ__MailCommand__
#define __PaoDeKuaiPQ__MailCommand__

#include <stdio.h>
#include "Config/AppDef.h"
#include "Net/Web/WebResult.h"
#include "Net/Web/WebCommand.h"

// 获取邮件概要，登录轮询使用
WEBCOMMAND_SUBCLASS_DECLARATION(MailAbstractCommand, "/mail/abstract");

class GetMailAbstractResult : public WebResult
{
public:
    GetMailAbstractResult()
    :
    m_nUnreadNum(0),
    m_nTotalNum(0),
    m_sCurDate("")
    {}
    
public:
    int            m_nTotalNum;
    int            m_nUnreadNum;
    std::string    m_sCurDate;
};

// 获取邮件列表
WEBCOMMAND_SUBCLASS_DECLARATION(MailListCommand, "/mail/list");

class GetMailListResult : public WebResult
{
public:
    GetMailListResult()
    :
    m_nTotalNum(0),
    m_nUnreadNum(0),
    m_nVer(0),
    m_sCurDate(""),
    m_oMailList({})
    {}
    
public:
    int             m_nTotalNum;
    int             m_nUnreadNum;
    int             m_nVer;
    std::string     m_sCurDate;
    std::vector<KKMAIL> m_oMailList;
};

// 获取邮件具体信息
WEBCOMMAND_SUBCLASS_DECLARATION(MailDetailCommand, "/mail/detail");

class GetMailDetailResult : public WebResult
{
public:
    GetMailDetailResult()
    :
    m_oMail({})
    {}
    
public:
    KKMAIL m_oMail;
};

// 获取邮件附件
class MailAttachCommand : public WebCommand
{
public:
    MailAttachCommand(const std::string& sMailId, WebResultCallback pCallback)
    :
    WebCommand("/mail/attach", pCallback),
    m_sMailId(sMailId)
    {}
    
protected:
    WebResult* parseResult(const rapidjson::Document &obJson);
    
private:
    std::string m_sMailId;
};

class GetMailAttachResult : public WebResult
{
public:
    GetMailAttachResult()
    :
    m_oAttach({}),
    m_sMailId("")
    {}
    
public:
    std::vector<KAWARDPROPINFO> m_oAttach;
    std::string                 m_sMailId;
};

#endif /* defined(__PaoDeKuaiPQ__MailCommand__) */
