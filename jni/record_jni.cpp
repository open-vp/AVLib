/**
 */
#include <jni.h>
#include <string>
#include "audio_encode_aac.h"
#include "video_encode_h264.h"
#include "media_muxer.h"

using namespace std;
using namespace OPENVP;

VideoEncodeH264 *h264_encoder;
AudioEncodeAAC *aac_encoder;


#define VIDEO_FORMAT ".h264"
#define MEDIA_FORMAT ".mp4"
#define AUDIO_FORMAT ".aac"

/**
 * 编码准备，写入配置信息
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_openvp_shortVideo_AVBaseJni_InitEncoder(JNIEnv *env,
									jclass type,
									jstring media_base_path_,
									jstring media_name_,
									jint v_custom_format,
									jint in_width,
									jint in_height,
									jint out_width,
									jint out_height,
									jint frame_rate,
									jlong video_bit_rate) {


    jclass global_class = (jclass) env->NewGlobalRef(type);
    UserArguments *arguments = (UserArguments *) malloc(sizeof(UserArguments));
    const char *media_base_path = env->GetStringUTFChars(media_base_path_, 0);
    const char *media_name = env->GetStringUTFChars(media_name_, 0);
    MediaMuxer *muxer_handler = new MediaMuxer();
    muxer_handler->setup_audio_state(START_STATE);
    muxer_handler->setup_video_state(START_STATE);
    arguments->media_base_path = media_base_path;
    arguments->media_name = media_name;

    size_t v_path_size = strlen(media_base_path) + strlen(media_name) + strlen(VIDEO_FORMAT) + 1;
    arguments->video_path = (char *) malloc(v_path_size + 1);

    size_t a_path_size = strlen(media_base_path) + strlen(media_name) + strlen(AUDIO_FORMAT) + 1;
    arguments->audio_path = (char *) malloc(a_path_size + 1);

    size_t m_path_size = strlen(media_base_path) + strlen(media_name) + strlen(MEDIA_FORMAT) + 1;
    arguments->media_path = (char *) malloc(m_path_size + 1);

    strcpy(arguments->video_path, media_base_path);
    strcat(arguments->video_path, "/");
    strcat(arguments->video_path, media_name);
    strcat(arguments->video_path, VIDEO_FORMAT);

    strcpy(arguments->audio_path, media_base_path);
    strcat(arguments->audio_path, "/");
    strcat(arguments->audio_path, media_name);
    strcat(arguments->audio_path, AUDIO_FORMAT);

    strcpy(arguments->media_path, media_base_path);
    strcat(arguments->media_path, "/");
    strcat(arguments->media_path, media_name);
    strcat(arguments->media_path, MEDIA_FORMAT);

    arguments->video_bit_rate = video_bit_rate;
    arguments->frame_rate = frame_rate;
    arguments->audio_bit_rate = 40000;
    arguments->audio_sample_rate = 44100;
    arguments->in_width = in_width;
    arguments->in_height = in_height;
    arguments->out_height = out_height;
    arguments->out_width = out_width;
    arguments->v_custom_format = v_custom_format;
    arguments->handler = muxer_handler;
    arguments->env = env;
    arguments->java_class = global_class;
    arguments->env->GetJavaVM(&arguments->javaVM);
    h264_encoder = new VideoEncodeH264(arguments);
    aac_encoder = new AudioEncodeAAC(arguments);
    int v_code = h264_encoder->initVideoEncoder();
    int a_code = aac_encoder->initAudioEncoder();

    if (v_code == 0 && a_code == 0) {
        return 0;
    } else {
        return -1;
    }

}
/**
 * 编码一帧视频
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_openvp_shortVideo_AVBaseJni_encodeFrame2H264(JNIEnv *env,
                                                                                  jclass type,
                                                                                  jbyteArray data_,
																				  jint length) {

    jbyte *elements = env->GetByteArrayElements(data_, 0);
    h264_encoder->sendVideoFrame((uint8_t *) elements,(int)length);
    env->ReleaseByteArrayElements(data_,elements,0);
    return 0;
}


/**
 * 编码一帧音频
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_openvp_shortVideo_AVBaseJni_encodeFrame2AAC(JNIEnv *env,
                                                                                 jclass type,
                                                                                 jbyteArray data_,
																				 jint length) {
    jbyte *elements = env->GetByteArrayElements(data_, 0);
    aac_encoder->sendAudioFrame((uint8_t *) elements,(int)length);
    env->ReleaseByteArrayElements(data_,elements,0);
    return 0;
}

/**
 *结束
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_openvp_shortVideo_AVBaseJni_recordEnd(JNIEnv *env,
                                                                           jclass type) {

    if (h264_encoder != NULL) {
        h264_encoder->user_end();
        h264_encoder = NULL;
    }

    if (aac_encoder != NULL) {
        aac_encoder->user_end();
        aac_encoder = NULL;
    }

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_openvp_shortVideo_AVBaseJni_nativeRelease(JNIEnv *env,
                                                                               jclass type) {

    if (aac_encoder != NULL) {
        aac_encoder->release();
        aac_encoder = NULL;
    }
    if (h264_encoder != NULL) {
        h264_encoder->release();
        h264_encoder = NULL;
    }
}
