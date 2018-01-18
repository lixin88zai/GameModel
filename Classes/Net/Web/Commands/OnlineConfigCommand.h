//
//  CheckInReviewCommand.h
//  PaoDeKuaiPQ
//
//  Created by 曹涛 on 16/12/1.
//
//

#ifndef __PaoDeKuaiPQ__CheckInReviewCommand__
#define __PaoDeKuaiPQ__CheckInReviewCommand__

#include <stdio.h>
#include "Config/AppDef.h"
#include "Net/Web/WebResult.h"
#include "Net/Web/WebCommand.h"

WEBCOMMAND_SUBCLASS_DECLARATION(OnlineConfigCommand, "/check");

class OnlineConfigResult : public WebResult
{
public:
    OnlineConfigResult()
    :
    m_bInReview(true),
    oMessageList({})
    {}
    
public:
    bool m_bInReview;
    std::vector<std::string> oMessageList;
};

#endif /* defined(__PaoDeKuaiPQ__CheckInReviewCommand__) */
