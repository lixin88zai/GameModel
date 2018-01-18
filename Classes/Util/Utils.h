/*******************************************************************************
包含所有工具的类。
*******************************************************************************/
#pragma  once

#include "Util/WindowUtil.h"
#include "Util/SpriteUtil.h"
#include "Util/MacroUtil.h"
#include "Util/MusicUtil.h"
#include "Util/ReaderWriter.h"
#include "Util/RandomUtil.h"
#include "Util/EffectUtil.h"
#include "Util/TimeUtil.h"
#include "Util/CharsetUtil.h"
#include "Util/PostionUtil.h"
#include "Util/LabelButton.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "Util/IOSUtil/CppCallObjectC.h"
#endif
