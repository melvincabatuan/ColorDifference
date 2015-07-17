#include "com_cabatuan_colordifference_MainActivity.h"
#include <android/log.h>
#include <android/bitmap.h>
#include <stdlib.h>

#include "opencv2/imgproc/imgproc.hpp"
#include "ColorDifference.h"

using namespace cv;

#define  LOG_TAG    "ColorDifference"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)



/*       Global Variables        */

ColorDifference cdiff;
Mat bgr;

/*
 * Class:     com_cabatuan_colordifference_MainActivity
 * Method:    filter
 * Signature: (Landroid/graphics/Bitmap;[B)V
 */
JNIEXPORT void JNICALL Java_com_cabatuan_colordifference_MainActivity_filter
  (JNIEnv *pEnv, jobject clazz, jobject pTarget, jbyteArray pSource){

   AndroidBitmapInfo bitmapInfo;
   uint32_t* bitmapContent; // Links to Bitmap content

   if(AndroidBitmap_getInfo(pEnv, pTarget, &bitmapInfo) < 0) abort();
   if(bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) abort();
   if(AndroidBitmap_lockPixels(pEnv, pTarget, (void**)&bitmapContent) < 0) abort();

   /// Access source array data... OK
   jbyte* source = (jbyte*)pEnv->GetPrimitiveArrayCritical(pSource, 0);
   if (source == NULL) abort();

   Mat srcNV21(bitmapInfo.height + (bitmapInfo.height/2), bitmapInfo.width, CV_8UC1, (unsigned char *)source);
   Mat mbgra(bitmapInfo.height, bitmapInfo.width, CV_8UC4, (unsigned char *)bitmapContent);

/***********************************************************************************************/

   if (bgr.empty())
       bgr.create(bitmapInfo.height, bitmapInfo.width,CV_8UC3);
  
   cvtColor( srcNV21, bgr, CV_YUV420sp2RGB);
   cvtColor( cdiff.process(bgr), mbgra, CV_BGR2BGRA);
 
    //cvtColor(srcNV21(cv::Range(0, bitmapInfo.height), cv::Range(0, bitmapInfo.width)), mbgra, CV_GRAY2BGRA);
    
    //cvtColor(cdiff.process(srcNV21(cv::Range(0, bitmapInfo.height), cv::Range(0, bitmapInfo.width))), mbgra, CV_GRAY2BGRA);

/************************************************************************************************/ 
   
   /// Release Java byte buffer and unlock backing bitmap
   pEnv-> ReleasePrimitiveArrayCritical(pSource,source,0);
   if (AndroidBitmap_unlockPixels(pEnv, pTarget) < 0) abort();

}
