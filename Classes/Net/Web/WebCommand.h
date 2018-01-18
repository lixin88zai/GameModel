//
//  WebCommand.h
//  GouJi
//
//  Created by 曾琪 on 14-9-24.
//
//

#ifndef GouJi_WebCommand_h
#define GouJi_WebCommand_h

#include <string>
#include <functional>
#include "json/document.h"
#include "Net/Web/WebVariables.h"
#include "Net/Web/WebResult.h"

typedef std::function<void(WebResult*)> WebResultCallback;

// WebCommand子类通用声明的宏
#define WEBCOMMAND_SUBCLASS_DECLARATION(_CLASS_NAME_, _ACTION_URI_) \
class _CLASS_NAME_ : public WebCommand\
{\
public:\
_CLASS_NAME_(WebResultCallback pCallback)\
:\
WebCommand(_ACTION_URI_, pCallback) {}\
protected:\
WebResult* parseResult(const rapidjson::Document &obJson);\
}

class WebCommand
{
public:
    // 初始化
    WebCommand(std::string sActionURI, WebResultCallback pCallback);
    virtual ~WebCommand();
    
public:
    // 由WebProxy调用
    std::string getActionURI();
    // 由业务和WebProxy调用
    WebVariables* getVariables();
    // 由WebProxy调用
    void onRespond(const std::string &sResponseData);
    
protected:
    // 由WebCommond::onRespond调用，必须由子类重写
    virtual WebResult* parseResult(const rapidjson::Document &obJson) = 0;
    
protected:
    // 请求URI
    std::string         m_sActionURI;
    // 请求参数
    WebVariables        m_obVariables;
    // 响应回调
    WebResultCallback   m_pCallback;
};

// --------------------
// 快捷读取Json数据
// --------------------
#define RAPIDJSON_READ_FUNC(_FUNC_NAME_, _NODE_TYPE_, _VALUE_TYPE_, _VALUE_METHOD_, _VALUE_DEFAULT_)\
inline _VALUE_TYPE_ _FUNC_NAME_(const _NODE_TYPE_ &node, const char* name, _VALUE_TYPE_ defaultValue = _VALUE_DEFAULT_)\
{\
    return node.HasMember(name) ? node[name]._VALUE_METHOD_() : defaultValue;\
}

// 读取Json数据类型int
RAPIDJSON_READ_FUNC(readJsonValueInt32, rapidjson::Document, int32_t, GetInt, 0);
RAPIDJSON_READ_FUNC(readJsonValueInt32, rapidjson::Value, int32_t, GetInt, 0);

// 读取Json数据类型unsigned int
RAPIDJSON_READ_FUNC(readJsonValueUint32, rapidjson::Document, uint32_t, GetUint, 0);
RAPIDJSON_READ_FUNC(readJsonValueUint32, rapidjson::Value, uint32_t, GetUint, 0);

// 读取Json数据类型long long
RAPIDJSON_READ_FUNC(readJsonValueInt64, rapidjson::Document, int64_t, GetInt64, 0);
RAPIDJSON_READ_FUNC(readJsonValueInt64, rapidjson::Value, int64_t, GetInt64, 0);

// 读取Json数据类型unsigned long long
RAPIDJSON_READ_FUNC(readJsonValueUint64, rapidjson::Document, uint64_t, GetUint64, 0);
RAPIDJSON_READ_FUNC(readJsonValueUint64, rapidjson::Value, uint64_t, GetUint64, 0);

// 读取Json数据类型double
RAPIDJSON_READ_FUNC(readJsonValueDouble, rapidjson::Document, double, GetDouble, 0.0);
RAPIDJSON_READ_FUNC(readJsonValueDouble, rapidjson::Value, double, GetDouble, 0.0);

// 读取Json数据类型bool
RAPIDJSON_READ_FUNC(readJsonValueBool, rapidjson::Document, bool, GetBool, false);
RAPIDJSON_READ_FUNC(readJsonValueBool, rapidjson::Value, bool, GetBool, false);

// 读取Json数据类型string
RAPIDJSON_READ_FUNC(readJsonValueString, rapidjson::Document, std::string, GetString, "");
RAPIDJSON_READ_FUNC(readJsonValueString, rapidjson::Value, std::string, GetString, "");

#endif
