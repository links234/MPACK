LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(info $(LOCAL_PATH))

LOCAL_MODULE     := MPACK
LOCAL_SRC_FILES  := $(subst $(LOCAL_PATH)/,,$(shell /usr/bin/find $(LOCAL_PATH) -type f -name '*.cpp'))
LOCAL_SRC_FILES  += $(subst $(LOCAL_PATH)/,,$(shell /usr/bin/find $(LOCAL_PATH) -type f -name '*.c')) 
LOCAL_C_INCLUDES := $(shell /usr/bin/find $(LOCAL_PATH) -type d)
LOCAL_CFLAGS     := -std=gnu++11 -DANDROID_PLATFORM
LOCAL_LDLIBS     := -landroid -llog -lEGL -lGLESv2 -lOpenSLES
LOCAL_LDFLAGS    := "-L/libs/armeabi"

LOCAL_STATIC_LIBRARIES := android_native_app_glue png ndk_helper gpg-1

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,libpng)
$(call import-module,gpg-cpp-sdk/android)
$(call import-module,android/ndk_helper)
