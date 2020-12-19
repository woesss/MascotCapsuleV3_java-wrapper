#include "../inc/JMicro3DApi.h"

jfieldID JActionTable_pointer = NULL;

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_ActionTable_nInit(JNIEnv* env, jobject jAtable, jbyteArray jBytes)
{
    jsize len = env->GetArrayLength(jBytes);
    if (len > 0)
    {
        IAllocator* allocator = Allocator_getInstance();
        ActTable* ptr = (ActTable*)IAllocator_alloc(allocator, sizeof(ActTable));
        if (ptr)
        {
            ActTable_initialize(ptr, allocator);
            ByteIstream* stream = (ByteIstream*)IAllocator_alloc(allocator, sizeof(ByteIstream));
            if (stream)
            {
                jbyte* data = env->GetByteArrayElements(jBytes, NULL);
                if (ByteIstream_initialize(stream, (hi_byte*)data, len))
                {
                    hi_bool succes = ActTable_loadMtraData(ptr, ByteIstream_getIIstream(stream));
                    ByteIstream_finalize(stream);
                    IAllocator_free(allocator, stream);
                    env->ReleaseByteArrayElements(jBytes, data, 0);
                    if (succes)
                    {
                        return (jint)ptr;
                    }
                }
                env->ReleaseByteArrayElements(jBytes, data, 0);
                IAllocator_free(allocator, stream);
            }
        }
        ActTable_finalize(ptr);
        IAllocator_free(allocator, ptr);
    }
    return 0;
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_ActionTable_nGetNumActions(JNIEnv* env, jobject obj)
{
    ActTable* table = JActionTable_get(env, obj);
    return ActTable_getNumActions(table);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_ActionTable_nGetNumFrames(JNIEnv* env, jobject obj, jint act_index)
{
    ActTable* table = JActionTable_get(env, obj);
    return ActTable_getNumFrames(table, act_index);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_ActionTable_nInitClass(JNIEnv* env, jclass clazz)
{
    JActionTable_pointer = env->GetFieldID(clazz, "nPointer", "I");
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_ActionTable_nFinalize(JNIEnv* env, jobject obj)
{
    ActTable* table = JActionTable_get(env, obj);
    ActTable_finalize(table);
    IAllocator_free(Allocator_getInstance(), table);
}

ActTable* JActionTable_get(JNIEnv* env, jobject obj)
{
    return (ActTable*)env->GetIntField(obj, JActionTable_pointer);
}
