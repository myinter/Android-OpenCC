//
// Created by HiungMacMini on 15/8/13.
//

#ifdef __cplusplus
extern "C" {
#endif

/* Standard C prototypes */

#include "main.h"
#include <malloc.h>
#include <stdio.h>
#include <android/log.h>
#include "NDKConverter.h"
#include "src/opencc.h"

//#define  LOG_TAG    "native-dev"
////#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
//#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
//#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)


char  *openCC_ResoucePath = NULL;
char  *OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD = NULL;
char *OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP = NULL;
opencc_t *openccTradToSimpConvertr = NULL;
opencc_t *openccSimpToTradConvertr = NULL;



void JNICALL Java_androidopencc_AndroidOpenCC_setOpenCCResPath(JNIEnv * env, jobject jObj,jstring resourcePath)
{
    if (openCC_ResoucePath)
    {
    free(openCC_ResoucePath);
    }
    if (OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD)
    {
    free(OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD);
    }
    if(OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP)
    {
    free(OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP);
    }
    openCC_ResoucePath = NULL;
    openCC_ResoucePath = (*env)->GetStringUTFChars(env,resourcePath, 0);
    OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP = malloc(sizeof(char) * (strlen(openCC_ResoucePath) + strlen("t2s.json") + 1));
    OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD = malloc(sizeof(char) * (strlen(openCC_ResoucePath) + strlen("s2t.json") + 1));
    strcpy(OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP, openCC_ResoucePath);
    strcpy(OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP + sizeof(char) * strlen(openCC_ResoucePath), "t2s.json");
    strcpy(OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD, openCC_ResoucePath);
    strcpy(OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD + sizeof(char) * strlen(openCC_ResoucePath), "s2t.json");
}


JNIEXPORT jstring JNICALL Java_androidopencc_AndroidOpenCC_ConvertSimpleToTraditional
        (JNIEnv * env, jobject jObj,jstring inputJstring)
{
    char *input = (*env)->GetStringUTFChars(env,inputJstring, 0);
    char *outPut = ConvertSimpleTraditional(input);
    jstring outputJstring = (*env)->NewStringUTF(env,outPut);
    free(input);
    free(outPut);
    return outputJstring;
}

JNIEXPORT jstring JNICALL Java_androidopencc_AndroidOpenCC_ConvertTradTextToSimplized
        (JNIEnv * env, jobject jObj,jstring inputJstring)
{
    char *input = (*env)->GetStringUTFChars(env,inputJstring,0);
        if (openccTradToSimpConvertr == NULL) {
        openccTradToSimpConvertr = opencc_open(OPENCC_DEFAULT_CONFIG_TRAD_TO_SIMP);
        }
        char *output = opencc_convert_utf8(openccTradToSimpConvertr, input, strlen(input));
    jstring outputJstring = (*env)->NewStringUTF(env,output);
    free(input);
    free(output);
    return outputJstring;
}

JNIEXPORT jstring JNICALL Java_androidopencc_AndroidOpenCC_ConvertSimpleTextToTraditional
        (JNIEnv * env, jobject jObj,jstring inputJstring)
{
    char *input = (*env)->GetStringUTFChars(env,inputJstring,0);
     if (openccSimpToTradConvertr == NULL) {
            openccSimpToTradConvertr = opencc_open(OPENCC_DEFAULT_CONFIG_SIMP_TO_TRAD);
        }
            char *output = opencc_convert_utf8(openccSimpToTradConvertr, input, strlen(input));
            jstring outputJstring = (*env)->NewStringUTF(env,output);
            free(input);
            free(output);
     return outputJstring;
}



#ifdef __cplusplus
}
#endif

























