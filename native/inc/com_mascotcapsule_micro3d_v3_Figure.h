/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_mascotcapsule_micro3d_v3_Figure */

#ifndef _Included_com_mascotcapsule_micro3d_v3_Figure
#define _Included_com_mascotcapsule_micro3d_v3_Figure
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nInit
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nInit
  (JNIEnv *, jobject, jbyteArray);

/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nSetPosture
 * Signature: (Lcom/mascotcapsule/micro3d/v3/ActionTable;II)V
 */
JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nSetPosture
  (JNIEnv *, jobject, jobject, jint, jint);

/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nSetPattern
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nSetPattern
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nGetNumPatterns
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nGetNumPatterns
  (JNIEnv *, jobject);

/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nFinalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nFinalize
  (JNIEnv *, jobject);

/*
 * Class:     com_mascotcapsule_micro3d_v3_Figure
 * Method:    nInitClass
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nInitClass
  (JNIEnv *, jclass);

#ifdef __cplusplus
}
#endif
#endif
