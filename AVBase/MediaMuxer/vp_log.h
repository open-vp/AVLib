
/**
 */
#ifndef _FFMPEG_LOG_H
#define _FFMPEG_LOG_H

#include <android/log.h>

//int JNI_DEBUG = 1;

#define LOGE(debug, format, ...) if(debug){__android_log_print(ANDROID_LOG_ERROR, "vp_ffmpeg", format, ##__VA_ARGS__);}
#define LOGI(debug, format, ...) if(debug){__android_log_print(ANDROID_LOG_INFO, "vp_ffmpeg", format, ##__VA_ARGS__);}

#endif //_FFMPEG_LOG_H
