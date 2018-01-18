#include "SvUDIDTools.h"
#include "Util/IOSUtil/CppCallObjectC.h"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

namespace iosutil
{
    std::string GetUDID()
    {
        NSString* ocudid = [SvUDIDTools UDID];
        const char* udid = [ocudid UTF8String];
        return (std::string)udid;
    }
}