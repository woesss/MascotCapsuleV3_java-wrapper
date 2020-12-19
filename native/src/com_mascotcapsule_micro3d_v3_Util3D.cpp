#include "../inc/JMicro3DApi.h"

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Util3D_sqrt(JNIEnv*, jclass, jint x)
{
    return Util3D_iSqrt(x);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Util3D_sin(JNIEnv*, jclass, jint a)
{
    return Util3D_sin12(a);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Util3D_cos(JNIEnv*, jclass, jint a)
{
    return Util3D_cos12(a);
}
