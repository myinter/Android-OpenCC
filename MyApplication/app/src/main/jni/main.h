//
// Created by HiungMacMini on 15/8/13.
//

#ifndef APPLICATION_MAIN_C_H
#define APPLICATION_MAIN_C_H

#endif //APPLICATION_MAIN_C_H

#include "jni.h"


#ifdef __cplusplus
extern "C" {
#endif

/* Standard C prototypes */



JNIEXPORT void JNICALL Java_com_example_hiungmacmini_application_AndroidOpenCC_setOpenCCResPath
(JNIEnv * env, jobject jObj,jstring resourcePath);
JNIEXPORT jstring JNICALL Java_com_example_hiungmacmini_application_AndroidOpenCC_ConvertSimpleToTraditional
        (JNIEnv * env, jobject jObj,jstring inputJstring);
JNIEXPORT jstring JNICALL Java_androidopencc_AndroidOpenCC_ConvertTradTextToSimplized
        (JNIEnv * env, jobject jObj,jstring inputJstring);
JNIEXPORT jstring JNICALL Java_androidopencc_AndroidOpenCC_ConvertSimpleTextToTraditional
                (JNIEnv * env, jobject jObj,jstring inputJstring);
#ifdef __cplusplus
}
#endif







//#include "OpenCCConverter.hpp"







//JNIEXPORT jstring JNICALL Java_com_example_hiungmacmini_application_MainActivity_ConvertSimpleToTraditional
//        (JNIEnv * env, jobject jObj,jstring resourcePath);
