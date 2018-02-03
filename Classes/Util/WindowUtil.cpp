#include "WindowUtil.h"

USING_NS_CC;

namespace util
{
    Size WindowUtil::sizeDesign(1280, 720);
    Size WindowUtil::sizeDevice(0, 0);
    float WindowUtil::scaleX    = 1.0;
    float WindowUtil::scaleY    = 1.0;
    float WindowUtil::scaleFit  = 1.0;
    float WindowUtil::scaleExtra = 1.0;
    
    void WindowUtil::initialize()
    {
        sizeDevice = Director::getInstance()->getWinSizeInPixels();        
        scaleX = sizeDevice.width / sizeDesign.width;
        scaleY = sizeDevice.height / sizeDesign.height;
        // 适配缩放值
        scaleFit = MIN(scaleX, scaleY);
        // 额外的适配系数
        scaleExtra = sizeDevice.height / sizeDevice.width < 0.625 ? 1.2 : 1.0;
    }
    // 统一宏定义
#define DESIGN_S    util::WindowUtil::sizeDesign
#define DESIGN_W    util::WindowUtil::sizeDesign.width
#define DESIGN_H    util::WindowUtil::sizeDesign.height
#define DEVICE_S    util::WindowUtil::sizeDevice
#define DEVICE_W    util::WindowUtil::sizeDevice.width
#define DEVICE_H    util::WindowUtil::sizeDevice.height
#define SCALE_X     util::WindowUtil::scaleX
#define SCALE_Y     util::WindowUtil::scaleY
#define SCALE_FIT   util::WindowUtil::scaleFit
#define SCALE_EXTRA util::WindowUtil::scaleExtra
}
