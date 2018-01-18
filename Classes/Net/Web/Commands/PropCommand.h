//
//  PropCommand.hpp
//  PaoDeKuaiPQ
//
//  Created by lzq on 2016/12/1.
//
//

#pragma once

#include "Net/Web/WebCommand.h"
#include "Net/Web/WebResult.h"
#include "Config/AppDef.h"

//道具详情
WEBCOMMAND_SUBCLASS_DECLARATION(PropDetailCommand,          "/package");
class PropDetailResult : public WebResult
{
public:
    PropDetailResult()
    :
    m_oPropDetailList({})
    {}
public:
    std::vector<KAWARDPROPINFO>  m_oPropDetailList;
};

