#include "../inc/JMicro3DApi.h"

jfieldID JLight_mDirVector = NULL;
jfieldID JLight_mDirIntensity = NULL;
jfieldID JLight_mAmbIntensity = NULL;

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Light_nInitClass(JNIEnv* env, jclass clazz)
{
    JLight_mDirVector    = env->GetFieldID(clazz, "mDirVector"   , "Lcom/mascotcapsule/micro3d/v3/Vector3D;");
    JLight_mDirIntensity = env->GetFieldID(clazz, "mDirIntensity", "I"                                      );
    JLight_mAmbIntensity = env->GetFieldID(clazz, "mAmbIntensity", "I"                                      );
}

 void JLight_getDirVector(JNIEnv* env, jobject obj, Vec3i* out)
{
    jobject jvec = env->GetObjectField(obj, JLight_mDirVector);
    JVec3D_get(env, jvec, out);
}

 hi_sint32 JLight_getDirIntensity(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JLight_mDirIntensity);
}

 hi_sint32 JLight_getAmbIntensity(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JLight_mAmbIntensity);
}
