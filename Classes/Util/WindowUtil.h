/*窗体尺寸与缩放*/
#pragma once

#include "cocos2d.h"

namespace util
{
    class WindowUtil
    {
    public:
        static void initialize();
    public:
        static cocos2d::Size sizeDesign;  // 设计尺寸
        static cocos2d::Size sizeDevice;  // 设备尺寸
        static float scaleX;              // 相对于设计尺寸的X轴缩放
        static float scaleY;              // 相对于设计尺寸的Y轴缩放
        static float scaleFit;            // 设备适应尺寸
        static float scaleExtra;          // 额外的适配系数
    };
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
