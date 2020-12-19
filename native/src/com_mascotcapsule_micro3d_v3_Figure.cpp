#include "../inc/JMicro3DApi.h"

jfieldID JFigure_nPointer = NULL;
jfieldID JFigure_mTexArray = NULL;
jfieldID JFigure_mTexture = NULL;

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nInit(JNIEnv* env, jobject, jbyteArray jBytes)
{
    jsize len = env->GetArrayLength(jBytes);
    if (len > 0)
    {
        IAllocator* allocator = Allocator_getInstance();
        Figure* ptr = (Figure*)IAllocator_alloc(allocator, sizeof(Figure));
        if (ptr)
        {
            Figure_initialize(ptr, allocator);
            ByteIstream* stream = (ByteIstream*)IAllocator_alloc(allocator, sizeof(ByteIstream));
            if (stream)
            {
                jbyte* data = env->GetByteArrayElements(jBytes, NULL);
                if (ByteIstream_initialize(stream, (hi_byte*)data, len))
                {
                    hi_bool succes = Figure_loadMbacData(ptr, ByteIstream_getIIstream(stream));
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
            Figure_finalize(ptr);
            IAllocator_free(allocator, ptr);
        }
    }
    return 0;
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nSetPosture(JNIEnv* env, jobject obj, jobject jActionTable, jint action, jint frame)
{
    Figure* figure = JFigure_get(env, obj);
    ActTable* table = JActionTable_get(env, jActionTable);
    Figure_setPosture(figure, table, action, frame);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nSetPattern(JNIEnv* env, jobject obj, jint pattern)
{
    Figure* figure = JFigure_get(env, obj);
    Figure_setPattern(figure, pattern);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nGetNumPatterns(JNIEnv* env, jobject obj)
{
    Figure* figure = JFigure_get(env, obj);
    return Figure_getNumPatterns(figure);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nInitClass(JNIEnv* env, jclass clazz)
{
    JFigure_nPointer = env->GetFieldID(clazz, "nPointer", "I");
    JFigure_mTexture = env->GetFieldID(clazz, "mTexture", "Lcom/mascotcapsule/micro3d/v3/Texture;");
    JFigure_mTexArray = env->GetFieldID(clazz, "mTexArray", "[Lcom/mascotcapsule/micro3d/v3/Texture;");
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Figure_nFinalize(JNIEnv* env, jobject obj)
{
    Figure* figure = JFigure_get(env, obj);
    Figure_finalize(figure);
    IAllocator_free(Allocator_getInstance(), figure);
}

Figure* JFigure_get(JNIEnv* env, jobject obj)
{
    return (Figure*)env->GetIntField(obj, JFigure_nPointer);
}

Texture* JFigure_getTexture(JNIEnv* env, jobject obj)
{
    jobject jtex = env->GetObjectField(obj, JFigure_mTexture);
    if (jtex)
        return JTexture_get(env, jtex);
    return NULL;
}

void JFigure_getTextureArray(JNIEnv* env, jobject obj, TextureArray* out)
{
    jobjectArray texArray = (jobjectArray)env->GetObjectField(obj, JFigure_mTexArray);
    if (texArray == NULL)
    {
        out->num = 0;
        return;
    }
    jsize len = env->GetArrayLength(texArray);
    if (len > 16)
    {
        len = 16;
    }
    for (jsize i = 0; i < len; i++)
    {
        jobject jtex = env->GetObjectArrayElement(texArray, i);
        Texture* tex = JTexture_get(env, jtex);
        out->texture[i] = tex;
    }
    out->num = len;
}
