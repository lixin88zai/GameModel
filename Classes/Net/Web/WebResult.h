//
//  WebResult.h
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#ifndef GouJi_WebResult_h
#define GouJi_WebResult_h

#include <string>

class WebResult
{
public:
    WebResult();
    virtual ~WebResult();
    
public:
    int         m_nCode;    // 错误码
    std::string m_sMessage; // 信息
};

#endif
