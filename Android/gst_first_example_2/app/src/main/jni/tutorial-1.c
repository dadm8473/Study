#include <string.h>
#include <jni.h>
#include <android/log.h>
#include <gstreamer-1.0/gst/gst.h>
#include <glib-2.0/gio/gio.h>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib/gmem.h>
#include <com_example_gst_first_example_2_MainActivity.h>

#define G_N_ELEMENTS(arr)		(sizeof (arr) / sizeof ((arr)[0]))

/*
 * Java Bindings
 */

static jstring gst_native_get_gstreamer_info (JNIEnv* env, jobject thiz) {
  char *version_utf8 = gst_version_string();
  jstring *version_jstring = (*env)->NewStringUTF(env, version_utf8);
  g_free ((gpointer)(version_utf8));
  return version_jstring;
}

static JNINativeMethod native_methods[] = {
  { "nativeGetGStreamerInfo", "()Ljava/lang/String;", (void *) gst_native_get_gstreamer_info}
};

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
  JNIEnv *env = NULL;

  if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    __android_log_print (ANDROID_LOG_ERROR, "tutorial-1", "Could not retrieve JNIEnv");
    return 0;
  }
  jclass klass = (*env)->FindClass (env, "com/example/gst_first_example_2/MainActivity");
  (*env)->RegisterNatives (env, klass, native_methods, G_N_ELEMENTS(native_methods));

  return JNI_VERSION_1_4;
}
