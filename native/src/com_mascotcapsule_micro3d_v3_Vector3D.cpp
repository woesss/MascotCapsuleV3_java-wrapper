#include "../inc/JMicro3DApi.h"

jfieldID JVec3D_x = NULL;
jfieldID JVec3D_y = NULL;
jfieldID JVec3D_z = NULL;

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_unit(JNIEnv* env, jobject obj)
{
    Vec3i v;
    JVec3D_get(env, obj, &v);
    Vec3i_normalize12(&v, &v);
    JVec3D_set(env, obj, &v);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_nDot(JNIEnv* env, jobject obj1, jobject obj2)
{
    Vec3i v1;
    Vec3i v2;
    JVec3D_get(env, obj1, &v1);
    JVec3D_get(env, obj2, &v2);
    return Vec3i_dot(&v1, &v2);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_nCross(JNIEnv* env, jobject obj1, jobject obj2)
{
    Vec3i v1;
    Vec3i v2;
    JVec3D_get(env, obj1, &v1);
    JVec3D_get(env, obj2, &v2);
    Vec3i_cross(&v1, &v2);
    JVec3D_set(env, obj1, &v1);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_nDot2(JNIEnv* env, jclass, jobject obj1, jobject obj2)
{
    Vec3i v1;
    Vec3i v2;
    JVec3D_get(env, obj1, &v1);
    JVec3D_get(env, obj2, &v2);
    return Vec3i_dot(&v1, &v2);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_nCross2(JNIEnv* env, jclass, jobject obj1, jobject obj2, jobject objRes)
{
    Vec3i v1;
    Vec3i v2;
    Vec3i res;
    JVec3D_get(env, obj1, &v1);
    JVec3D_get(env, obj2, &v2);
    Vec3i_cross2(&res, &v1, &v2);
    JVec3D_set(env, objRes, &res);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Vector3D_nInitClass(JNIEnv* env, jclass clazz)
{
    JVec3D_x = env->GetFieldID(clazz, "x", "I");
    JVec3D_y = env->GetFieldID(clazz, "y", "I");
    JVec3D_z = env->GetFieldID(clazz, "z", "I");
}

void JVec3D_get(JNIEnv* env, jobject obj, Vec3i* out)
{
    out->x = env->GetIntField(obj, JVec3D_x);
    out->y = env->GetIntField(obj, JVec3D_y);
    out->z = env->GetIntField(obj, JVec3D_z);
}

void JVec3D_set(JNIEnv* env, jobject obj, Vec3i* in)
{
    env->SetIntField(obj, JVec3D_x, in->x);
    env->SetIntField(obj, JVec3D_y, in->y);
    env->SetIntField(obj, JVec3D_z, in->z);
}
