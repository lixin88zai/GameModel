//
//  AppDeveloper.cpp
//  GouJi
//
//  Created by ZengQi on 16/8/11.
//
//

#include "AppDeveloper.h"
#include "AppVersion.h"
#include "Util/Utils.h"
#include "Net/Web/WebManager.h"

#define KEY_SERVERHOSTDEVELOPER "server_host_developer"

using namespace std;
using namespace util;

namespace developer
{
    string getServerHost()
    {
        string sRet = ReaderWriter::LoadStringFromXML(KEY_SERVERHOSTDEVELOPER, "");
        return sRet.empty() ? SERVER_HOST : sRet;
    }
    
    void setServerHost(const string &sNewHost)
    {
        ReaderWriter::SaveStringToXML(KEY_SERVERHOSTDEVELOPER, sNewHost);
        WebManager::getInstance()->reset();
        
    }
}
