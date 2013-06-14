LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Framework
LOCAL_SRC_FILES := $(subst $(LOCAL_PATH),,$(shell find $(LOCAL_PATH) -type f -name '*.cpp')) 
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv2 -lOpenSLES

LOCAL_STATIC_LIBRARIES := android_native_app_glue png

$(info **********************************************************************)
$(info $(LOCAL_SRC_FILES))
$(info **********************************************************************)

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,libpng)
