#include "../inc/JMicro3DApi.h"

jfieldID JAffineTrans_m00 = NULL;
jfieldID JAffineTrans_m01 = NULL;
jfieldID JAffineTrans_m02 = NULL;
jfieldID JAffineTrans_m03 = NULL;
jfieldID JAffineTrans_m10 = NULL;
jfieldID JAffineTrans_m11 = NULL;
jfieldID JAffineTrans_m12 = NULL;
jfieldID JAffineTrans_m13 = NULL;
jfieldID JAffineTrans_m20 = NULL;
jfieldID JAffineTrans_m21 = NULL;
jfieldID JAffineTrans_m22 = NULL;
jfieldID JAffineTrans_m23 = NULL;

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nTransform(JNIEnv* env, jobject obj, jobject srcVec, jobject dstVec)
{
    Atrans3i trans;
    Vec3i src;
    Vec3i dst;
    JAffineTrans_get(env, obj, &trans);
    JVec3D_get(env, srcVec, &src);
    Atrans3i_transPoint(&trans, &src, &dst);
    JVec3D_set(env, dstVec, &dst);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nMultiply(JNIEnv* env, jobject obj1, jobject obj2)
{
    Atrans3i a1;
    Atrans3i a2;
    JAffineTrans_get(env, obj1, &a1);
    JAffineTrans_get(env, obj2, &a2);
    Atrans3i_multiply(&a1, &a2);
    JAffineTrans_set(env, obj1, &a1);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nMultiply2(JNIEnv* env, jobject objRes, jobject obj1, jobject obj2)
{
    Atrans3i a1;
    Atrans3i a2;
    Atrans3i r;
    JAffineTrans_get(env, obj1, &a1);
    JAffineTrans_get(env, obj2, &a2);
    Atrans3i_multiply2(&r, &a1, &a2);
    JAffineTrans_set(env, objRes, &r);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetRotationX(JNIEnv* env, jobject obj, jint angle)
{
    Atrans3i a;
    JAffineTrans_get(env, obj, &a);
    Atrans3i_setRotateX(&a, angle);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetRotationY(JNIEnv* env, jobject obj, jint angle)
{
    Atrans3i a;
    JAffineTrans_get(env, obj, &a);
    Atrans3i_setRotateY(&a, angle);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetRotationZ(JNIEnv* env, jobject obj, jint angle)
{
    Atrans3i a;
    JAffineTrans_get(env, obj, &a);
    Atrans3i_setRotateZ(&a, angle);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetIdentity(JNIEnv* env, jobject obj)
{
    Atrans3i a;
    Atrans3i_setIdentity(&a);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetRotationV(JNIEnv* env, jobject obj, jobject jvec, jint angle)
{
    Atrans3i a;
    Vec3i v;
    JVec3D_get(env, jvec, &v);
    JAffineTrans_get(env, obj, &a);
    Atrans3i_setRotateV(&a, &v, angle);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nSetViewTtans(JNIEnv* env, jobject obj, jobject jpos, jobject jlook, jobject jup)
{
    Atrans3i a;
    Vec3i pos;
    Vec3i look;
    Vec3i up;
    JVec3D_get(env, jpos, &pos);
    JVec3D_get(env, jlook, &look);
    JVec3D_get(env, jup, &up);
    JAffineTrans_get(env, obj, &a);
    Atrans3i_setViewTrans(&a, &pos, &look, &up);
    JAffineTrans_set(env, obj, &a);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_AffineTrans_nInitClass(JNIEnv* env, jclass clazz)
{
    JAffineTrans_m00 = env->GetFieldID(clazz, "m00", "I");
    JAffineTrans_m01 = env->GetFieldID(clazz, "m01", "I");
    JAffineTrans_m02 = env->GetFieldID(clazz, "m02", "I");
    JAffineTrans_m03 = env->GetFieldID(clazz, "m03", "I");
    JAffineTrans_m10 = env->GetFieldID(clazz, "m10", "I");
    JAffineTrans_m11 = env->GetFieldID(clazz, "m11", "I");
    JAffineTrans_m12 = env->GetFieldID(clazz, "m12", "I");
    JAffineTrans_m13 = env->GetFieldID(clazz, "m13", "I");
    JAffineTrans_m20 = env->GetFieldID(clazz, "m20", "I");
    JAffineTrans_m21 = env->GetFieldID(clazz, "m21", "I");
    JAffineTrans_m22 = env->GetFieldID(clazz, "m22", "I");
    JAffineTrans_m23 = env->GetFieldID(clazz, "m23", "I");
}

void JAffineTrans_get(JNIEnv* env, jobject obj, Atrans3i* out)
{
    hi_sint32* dst = (hi_sint32*)out;
    *dst++ = env->GetIntField(obj, JAffineTrans_m00);
    *dst++ = env->GetIntField(obj, JAffineTrans_m01);
    *dst++ = env->GetIntField(obj, JAffineTrans_m02);
    *dst++ = env->GetIntField(obj, JAffineTrans_m03);
    *dst++ = env->GetIntField(obj, JAffineTrans_m10);
    *dst++ = env->GetIntField(obj, JAffineTrans_m11);
    *dst++ = env->GetIntField(obj, JAffineTrans_m12);
    *dst++ = env->GetIntField(obj, JAffineTrans_m13);
    *dst++ = env->GetIntField(obj, JAffineTrans_m20);
    *dst++ = env->GetIntField(obj, JAffineTrans_m21);
    *dst++ = env->GetIntField(obj, JAffineTrans_m22);
    *dst   = env->GetIntField(obj, JAffineTrans_m23);
}

void JAffineTrans_set(JNIEnv* env, jobject obj, Atrans3i* in)
{
    hi_sint32* dst = &in->m00;
    env->SetIntField(obj, JAffineTrans_m00, *dst++);
    env->SetIntField(obj, JAffineTrans_m01, *dst++);
    env->SetIntField(obj, JAffineTrans_m02, *dst++);
    env->SetIntField(obj, JAffineTrans_m03, *dst++);
    env->SetIntField(obj, JAffineTrans_m10, *dst++);
    env->SetIntField(obj, JAffineTrans_m11, *dst++);
    env->SetIntField(obj, JAffineTrans_m12, *dst++);
    env->SetIntField(obj, JAffineTrans_m13, *dst++);
    env->SetIntField(obj, JAffineTrans_m20, *dst++);
    env->SetIntField(obj, JAffineTrans_m21, *dst++);
    env->SetIntField(obj, JAffineTrans_m22, *dst++);
    env->SetIntField(obj, JAffineTrans_m23, *dst  );
}
