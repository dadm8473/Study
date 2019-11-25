LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := HelloGst
LOCAL_SRC_FILES := HelloGst.c

include $(BUILD_SHARED_LIBRARY)