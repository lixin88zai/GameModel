LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../Libraries)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp



define classes-cpp-files
$(patsubst jni/%,%,$(shell find $(LOCAL_PATH)/../../Classes -name "*.cpp")) \
$(patsubst jni/%,%,$(shell find $(LOCAL_PATH)/../../Classes -name "*.cc"))
endef

define libs-effcommon-cpp-files
$(patsubst jni/%,%,$(shell find $(LOCAL_PATH)/../../Libraries/eff_comm -name "*.cpp"))
endef

define libs-rapidxml-cpp-files
$(patsubst jni/%,%,$(shell find $(LOCAL_PATH)/../../Libraries/rapidxml -name "*.cpp"))
endef

define libs-socketx-cpp-files
$(patsubst jni/%,%,$(shell find $(LOCAL_PATH)/../../Libraries/socketx -name "*.cpp"))
endef



LOCAL_SRC_FILES := cocos2dcpp/main.cpp \
                   cocos2dcpp/PlatformFunction.cpp \
                   $(call classes-cpp-files) \
                   $(call libs-effcommon-cpp-files) \
                   $(call libs-rapidxml-cpp-files) \
                   $(call libs-socketx-cpp-files)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
                    $(LOCAL_PATH)/../../Libraries \
                    $(LOCAL_PATH)/../../Libraries/google

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += protobuf_static
LOCAL_WHOLE_STATIC_LIBRARIES += libmobclickcpp
include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,google)
$(call import-module,libmobclickcpp)
