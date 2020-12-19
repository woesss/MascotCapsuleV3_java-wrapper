#include "../inc/JMicro3DApi.h"

jfieldID JTexture_nPointer = NULL;

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Texture_nInit(JNIEnv* env, jobject, jbyteArray jBytes, jboolean isModel)
{
    jsize len = env->GetArrayLength(jBytes);
    if (len > 0)
    {
        IAllocator* allocator = Allocator_getInstance();
        Texture* ptr = (Texture*)IAllocator_alloc(allocator, sizeof(Texture));
        if (ptr)
        {
            Texture_initialize(ptr, allocator);
            ByteIstream* stream = (ByteIstream*)IAllocator_alloc(allocator, sizeof(ByteIstream));
            if (stream)
            {
                jbyte* data = env->GetByteArrayElements(jBytes, NULL);
                if (ByteIstream_initialize(stream, (hi_byte*)data, len))
                {
                    hi_bool succes = Texture_loadBmpData(ptr, ByteIstream_getIIstream(stream), isModel ? TEXTURE_TYPE_NORMAL : TEXTURE_TYPE_SPHEREMAP);
                    ByteIstream_finalize(stream);
                    IAllocator_free(allocator, stream);
                    env->ReleaseByteArrayElements(jBytes, data, 0);
                    if (succes)
                    {
                        return (jint)ptr;
                    }
                }
                IAllocator_free(allocator, stream);
                env->ReleaseByteArrayElements(jBytes, data, 0);
            }
            Texture_finalize(ptr);
            IAllocator_free(allocator, ptr);
        }
    }
    return 0;
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Texture_nInitClass(JNIEnv* env, jclass clazz)
{
    JTexture_nPointer = env->GetFieldID(clazz, "nPointer", "I");
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Texture_nFinalize(JNIEnv* env, jobject obj)
{
    Texture* texture = JTexture_get(env, obj);
    Texture_finalize(texture);
    IAllocator_free(Allocator_getInstance(), texture);
}

Texture* JTexture_get(JNIEnv* env, jobject obj)
{
    return obj ? (Texture*)env->GetIntField(obj, JTexture_nPointer) : NULL;
}
