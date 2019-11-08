#include <com_example_nativeapp_MainActivity.h>

JNIEXPORT jstring JNICALL java_com_example_nativeapp_MainActivity_getJNIString(JNIEnv *env, jobject obj)
{
 return env->NewStringUTF("Message from jniMain");
}
