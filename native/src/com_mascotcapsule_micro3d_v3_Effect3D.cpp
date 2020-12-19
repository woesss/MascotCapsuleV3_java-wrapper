#include "../inc/JMicro3DApi.h"

jfieldID JTexture_isBlendEnable = NULL;
jfieldID JTexture_mShading      = NULL;
jfieldID JTexture_mHigh         = NULL;
jfieldID JTexture_mLow          = NULL;
jfieldID JTexture_mThreshold    = NULL;
jfieldID JTexture_mLight        = NULL;
jfieldID JTexture_mTexture      = NULL;

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Effect3D_nInitClass(JNIEnv* env, jclass clazz)
{
    JTexture_isBlendEnable = env->GetFieldID(clazz, "isBlendEnable", "Z");
    JTexture_mShading      = env->GetFieldID(clazz, "mShading"     , "I");
    JTexture_mHigh         = env->GetFieldID(clazz, "mHigh"        , "I");
    JTexture_mLow          = env->GetFieldID(clazz, "mLow"         , "I");
    JTexture_mThreshold    = env->GetFieldID(clazz, "mThreshold"   , "I");
    JTexture_mLight        = env->GetFieldID(clazz, "mLight"       , "Lcom/mascotcapsule/micro3d/v3/Light;");
    JTexture_mTexture      = env->GetFieldID(clazz, "mTexture"     , "Lcom/mascotcapsule/micro3d/v3/Texture;");
}

jobject JEffect3D_getLight(JNIEnv* env, jobject obj) {
    return env->GetObjectField(obj, JTexture_mLight);
}

hi_sint32 JEffect3D_getShadingType(JNIEnv* env, jobject obj) {
    return env->GetIntField(obj, JTexture_mShading);
}

hi_bool JEffect3D_getEnableBlend(JNIEnv* env, jobject obj) {
    return env->GetBooleanField(obj, JTexture_isBlendEnable);
}

Texture* JEffect3D_getTexture(JNIEnv* env, jobject obj) {
    jobject jtexture = env->GetObjectField(obj, JTexture_mTexture);
    if (jtexture)
    {
        return JTexture_get(env, jtexture);
    }
    return NULL;
}

hi_sint32 JEffect3D_getToonThreshold(JNIEnv* env, jobject obj) {
    return env->GetIntField(obj, JTexture_mThreshold);
}

hi_sint32 JEffect3D_getToonHigh(JNIEnv* env, jobject obj) {
    return env->GetIntField(obj, JTexture_mHigh);
}

hi_sint32 JEffect3D_getToonLow(JNIEnv* env, jobject obj) {
    return env->GetIntField(obj, JTexture_mLow);
}
