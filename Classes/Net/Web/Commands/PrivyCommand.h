//
//  PrivyCommand.h
//  PaoDeKuaiPQ
//
//  Created by Joi Yao on 16/10/28.
//
//

#pragma once

#include "Net/Web/WebCommand.h"
#include "Net/Web/WebResult.h"
#include "Config/AppDef.h"

//________________________________________________
// 配置
WEBCOMMAND_SUBCLASS_DECLARATION(PrivyConfigCommand,          "/privy/cfg");
class PrivyConfigResult : public WebResult
{
public:
    PrivyConfigResult()
    :
    m_oConfig({}) {}
public:
    KKPRIVYCONFIG   m_oConfig;
};
//________________________________________________
// 创建
WEBCOMMAND_SUBCLASS_DECLARATION(PrivyCreateCommand,          "/privy/createtable");
class PrivyCreateResult : public WebResult
{
public:
    PrivyCreateResult()
    :
    m_obMatchInfo({}),
    m_obRoomInfo({}),
    m_nPrivyId(0)
    {}
    
public:
    PKMATCHINFO     m_obMatchInfo;      // 配桌信息
    PKROOM          m_obRoomInfo;       // 私人房间信息
    int             m_nPrivyId;         // 私人房号
};
//________________________________________________
// 加入
WEBCOMMAND_SUBCLASS_DECLARATION(PrivyJoinCommand,          "/privy/jointable");
class PrivyJoinResult : public WebResult
{
public:
    PrivyJoinResult()
    :
    m_obMatchInfo({}),
    m_obRoomInfo({}),
    m_nPrivyId(0)
    {}
    
public:
    PKMATCHINFO         m_obMatchInfo;      // 配桌信息
    PKROOM              m_obRoomInfo;       // 私人房间信息
    int                 m_nPrivyId;         // 私人房号
};
//________________________________________________
// 获取房间配置
WEBCOMMAND_SUBCLASS_DECLARATION(GetRoomInfoCommand,          "/privy/roominfo");
class GetRoomInfo : public WebResult
{
public:
    GetRoomInfo()
    :
    m_obMatchInfo({}),
    m_obRoomInfo({}),
    m_nPrivyId(0)
    {}
    
public:
    PKMATCHINFO         m_obMatchInfo;      // 配桌信息
    PKROOM              m_obRoomInfo;       // 私人房间信息
    int                 m_nPrivyId;         // 私人房号
};
