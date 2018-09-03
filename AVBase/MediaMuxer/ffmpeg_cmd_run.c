/**
 */

#include "ffmpeg.h"
#include <jni.h>

JNIEXPORT jint JNICALL
Java_com_openvp_shortVideo_AVBaseJni_ffmpegRun(JNIEnv *env, jobject type,
        jobjectArray commands){
    int argc = (*env)->GetArrayLength(env,commands);
    char *argv[argc];
    int i;
    for (i = 0; i < argc; i++) {
        jstring js = (jstring) (*env)->GetObjectArrayElement(env,commands, i);
        argv[i] = (char *) (*env)->GetStringUTFChars(env,js, 0);
    }
    return vp_ff_run(argc,argv);
}

JNIEXPORT jstring JNICALL
Java_com_openvp_shortVideo_AVBaseJni_getFFmpegConfig(JNIEnv *env, jobject instance) {

    char info[10000] = {0};
    sprintf(info, "%s\n", avcodec_configuration());
    return (*env)->NewStringUTF(env,info);

}
