#include "../inc/JMicro3DApi.h"

jfieldID JFigureLayout_mAffineArray    = NULL;
jfieldID JFigureLayout_mAffine         = NULL;
jfieldID JFigureLayout_mScaleX         = NULL;
jfieldID JFigureLayout_mScaleY         = NULL;
jfieldID JFigureLayout_mCenterX        = NULL;
jfieldID JFigureLayout_mCenterY        = NULL;
jfieldID JFigureLayout_mParallelW      = NULL;
jfieldID JFigureLayout_mParallelH      = NULL;
jfieldID JFigureLayout_mNear           = NULL;
jfieldID JFigureLayout_mFar            = NULL;
jfieldID JFigureLayout_mAngle          = NULL;
jfieldID JFigureLayout_mPerspectiveW   = NULL;
jfieldID JFigureLayout_mPerspectiveH   = NULL;
jfieldID JFigureLayout_mProjectionType = NULL;

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_FigureLayout_nInitClass(JNIEnv* env, jclass clazz)
{
    JFigureLayout_mAffineArray    = env->GetFieldID(clazz, "mAffineArray"   , "[Lcom/mascotcapsule/micro3d/v3/AffineTrans;");
    JFigureLayout_mAffine         = env->GetFieldID(clazz, "mAffine"        , "Lcom/mascotcapsule/micro3d/v3/AffineTrans;" );
    JFigureLayout_mScaleX         = env->GetFieldID(clazz, "mScaleX"        , "I"                                          );
    JFigureLayout_mScaleY         = env->GetFieldID(clazz, "mScaleY"        , "I"                                          );
    JFigureLayout_mCenterX        = env->GetFieldID(clazz, "mCenterX"       , "I"                                          );
    JFigureLayout_mCenterY        = env->GetFieldID(clazz, "mCenterY"       , "I"                                          );
    JFigureLayout_mParallelW      = env->GetFieldID(clazz, "mParallelW"     , "I"                                          );
    JFigureLayout_mParallelH      = env->GetFieldID(clazz, "mParallelH"     , "I"                                          );
    JFigureLayout_mNear           = env->GetFieldID(clazz, "mNear"          , "I"                                          );
    JFigureLayout_mFar            = env->GetFieldID(clazz, "mFar"           , "I"                                          );
    JFigureLayout_mAngle          = env->GetFieldID(clazz, "mAngle"         , "I"                                          );
    JFigureLayout_mPerspectiveW   = env->GetFieldID(clazz, "mPerspectiveW"  , "I"                                          );
    JFigureLayout_mPerspectiveH   = env->GetFieldID(clazz, "mPerspectiveH"  , "I"                                          );
    JFigureLayout_mProjectionType = env->GetFieldID(clazz, "mProjectionType", "I"                                          );
}

hi_sint32 JFigureLayout_getCenterX(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mCenterX);
}

hi_sint32 JFigureLayout_getCenterY(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mCenterY);
}

hi_sint32 JFigureLayout_getScaleX(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mScaleX);
}

hi_sint32 JFigureLayout_getScaleY(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mScaleY);
}

hi_sint32 JFigureLayout_getParallelW(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mParallelW);
}

hi_sint32 JFigureLayout_getParallelH(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mParallelH);
}

hi_sint32 JFigureLayout_getNear(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mNear);
}

hi_sint32 JFigureLayout_getFar(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mFar);
}

hi_sint32 JFigureLayout_getAngle(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mAngle);
}

hi_sint32 JFigureLayout_getPerspectiveW(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mPerspectiveW);
}

hi_sint32 JFigureLayout_getPerspectiveH(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mPerspectiveH);
}

hi_sint32 JFigureLayout_getProjectType(JNIEnv* env, jobject obj)
{
    return env->GetIntField(obj, JFigureLayout_mProjectionType);
}

jobjectArray JFigureLayout_getAffineArray(JNIEnv* env, jobject obj)
{
    return (jobjectArray)env->GetObjectField(obj, JFigureLayout_mAffineArray);
}

void JFigureLayout_getAffine(JNIEnv* env, jobject obj, Atrans3i* out)
{
    jobject jActTrans = env->GetObjectField(obj, JFigureLayout_mAffine);
    JAffineTrans_get(env, jActTrans, out);
}
