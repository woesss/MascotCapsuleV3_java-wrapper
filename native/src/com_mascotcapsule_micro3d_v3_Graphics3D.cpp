#include <memory.h>
#include "../inc/JMicro3DApi.h"

jfieldID JGraphics3D_nPointer    = NULL;
jfieldID JGraphics3D_nBufPointer = NULL;

#define getRender() (Render*)env->GetIntField(obj, JGraphics3D_nPointer)

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nFinalize(JNIEnv* env, jobject obj)
{
	Render* render = getRender();
	Render_finalize(render);
	IAllocator_free(Allocator_getInstance(), render);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nRenderPrimitive
(JNIEnv* env, jobject obj, jobject jtex, jint x, jint y, jobject jlayout, jobject jeffect, jint cmd,
	jintArray jvertexCoords, jintArray jnormals, jintArray jtexCoords, jintArray jcolors)
{
	Render* render = getRender();
	hi_sint32 attrs = Render_getAttribute(render);

	Atrans3i affine;
	JFigureLayout_getAffine(env, jlayout, &affine);
	Render_setViewTrans(render, &affine);

	hi_sint32 projection = JFigureLayout_getProjectType(env, jlayout);
	switch (projection)
	{
	case 0:
	{
		hi_sint32 scaleX = JFigureLayout_getScaleX(env, jlayout);
		hi_sint32 scaleY = JFigureLayout_getScaleY(env, jlayout);
		Render_setOrthographicScale(render, scaleX, scaleY);
		break;
	}
	case 1:
	{
		hi_sint32 w = JFigureLayout_getParallelW(env, jlayout);
		hi_sint32 h = JFigureLayout_getParallelH(env, jlayout);
		Render_setOrthographicWH(render, w, h);
		break;
	}
	case 2:
	{
		hi_sint32 near = JFigureLayout_getNear(env, jlayout);
		hi_sint32 far = JFigureLayout_getFar(env, jlayout);
		hi_sint32 angle = JFigureLayout_getAngle(env, jlayout);
		Render_setPerspectiveFov(render, near, far, angle);
		break;
	}
	case 3:
	{
		hi_sint32 w = JFigureLayout_getPerspectiveW(env, jlayout);
		hi_sint32 h = JFigureLayout_getPerspectiveH(env, jlayout);
		hi_sint32 near = JFigureLayout_getNear(env, jlayout);
		hi_sint32 far = JFigureLayout_getFar(env, jlayout);
		Render_setPerspectiveWH(render, near, far, w, h);
		break;
	}
	}


	jobject jlight = JEffect3D_getLight(env, jeffect);
	if (jlight)
	{
		hi_sint32 ambIntencity = JLight_getAmbIntensity(env, jlight);
		hi_sint32 dirIntensity = JLight_getDirIntensity(env, jlight);
		Vec3i dir;
		JLight_getDirVector(env, jlight, &dir);
		Render_setDirectionLight(render, &dir, dirIntensity);
		Render_setAmbientLight(render, ambIntencity);
		attrs |= M3D_LIGHTING;
	}
	else
	{
		attrs &= ~M3D_LIGHTING;
	}

	hi_sint32 shading = JEffect3D_getShadingType(env, jeffect);
	if (shading)
	{
		attrs |= M3D_TOON_SHADING;
		hi_sint32 tress = JEffect3D_getToonThreshold(env, jeffect);
		hi_sint32 high = JEffect3D_getToonHigh(env, jeffect);
		hi_sint32 low = JEffect3D_getToonLow(env, jeffect);
		Render_setToonParam(render, tress, high, low);
	}
	else
	{
		attrs &= ~M3D_TOON_SHADING;
	}


	hi_bool isBlend = JEffect3D_getEnableBlend(env, jeffect);
	if (isBlend)
	{
		attrs |= M3D_BLEND;
	}
	else
	{
		attrs &= ~M3D_BLEND;
	}

	Texture* specular = JEffect3D_getTexture(env, jeffect);
	if (specular)
	{
		attrs |= M3D_SPECULAR;
		Render_setSphereTexture(render, specular);
	}
	else
	{
		attrs &= ~M3D_SPECULAR;
	}

	hi_sint32 cx = JFigureLayout_getCenterX(env, jlayout);
	hi_sint32 cy = JFigureLayout_getCenterY(env, jlayout);
	Render_setScreenCenter(render, cx + x, cy + y);

	Texture* tex = JTexture_get(env, jtex);
	Render_setTexture(render, tex);

	Render_setAttribute(render, attrs);

	IntArray coord;
	coord.num = env->GetArrayLength(jvertexCoords);
	coord.array = (hi_sint32*)env->GetIntArrayElements(jvertexCoords, NULL);
	IntArray normal;
	normal.num = env->GetArrayLength(jnormals);
	normal.array = (hi_sint32*)env->GetIntArrayElements(jnormals, NULL);
	IntArray texcoord;
	texcoord.num = env->GetArrayLength(jtexCoords);
	texcoord.array = (hi_sint32*)env->GetIntArrayElements(jtexCoords, NULL);
	IntArray color;
	color.num = env->GetArrayLength(jcolors);
	color.array = (hi_sint32*)env->GetIntArrayElements(jcolors, NULL);
	hi_bool success = Render_drawPrimitive(render, cmd, &coord, &normal, &texcoord, &color);
	env->ReleaseIntArrayElements(jvertexCoords, (jint*)coord.array, 0);
	env->ReleaseIntArrayElements(jnormals, (jint*)normal.array, 0);
	env->ReleaseIntArrayElements(jtexCoords, (jint*)texcoord.array, 0);
	env->ReleaseIntArrayElements(jcolors, (jint*)color.array, 0);
	return !success;
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nDrawCmd
(JNIEnv* env, jobject obj, jobjectArray jtextures, jint x, jint y, jobject jlayout, jobject jeffect, jintArray jcommands)
{
	Render* render = getRender();

	Atrans3i affine;
	JFigureLayout_getAffine(env, jlayout, &affine);
	Render_setViewTrans(render, &affine);

	if (jtextures)
	{
		jsize len = env->GetArrayLength(jtextures);
		if (len > 0)
		{
			if (len > 16) len = 16;
			TextureArray texArray;
			for (jsize i = 0; i < len; i++)
			{
				jobject jtex = env->GetObjectArrayElement(jtextures, i);
				Texture* tex = JTexture_get(env, jtex);
				texArray.texture[i] = tex;
			}
			texArray.num = len;
			Render_setTextureArray(render, &texArray);
		}
	}

	jobjectArray jAffines = JFigureLayout_getAffineArray(env, jlayout);
	jsize len = env->GetArrayLength(jAffines);
	Atrans3iArray transArray;
	Atrans3iArray_initialize(&transArray);
	if (len > 0)
	{
		Atrans3i* transPtr = (Atrans3i*)IAllocator_alloc(Allocator_getInstance(), sizeof(Atrans3i) * len);
		if (transPtr == NULL)
			return -1;
		for (jsize i = 0; i < len; i++)
		{
			JAffineTrans_get(env, env->GetObjectArrayElement(jAffines, i), &transPtr[i]);
		}
		Atrans3iArray_set(&transArray, transPtr, len);
	}
	Render_setViewTransArray(render, &transArray);

	hi_sint32 projection = JFigureLayout_getProjectType(env, jlayout);
	switch (projection)
	{
	case 0:
	{
		hi_sint32 scaleX = JFigureLayout_getScaleX(env, jlayout);
		hi_sint32 scaleY = JFigureLayout_getScaleY(env, jlayout);
		Render_setOrthographicScale(render, scaleX, scaleY);
		break;
	}
	case 1:
	{
		hi_sint32 w = JFigureLayout_getParallelW(env, jlayout);
		hi_sint32 h = JFigureLayout_getParallelH(env, jlayout);
		Render_setOrthographicWH(render, w, h);
		break;
	}
	case 2:
	{
		hi_sint32 near = JFigureLayout_getNear(env, jlayout);
		hi_sint32 far = JFigureLayout_getFar(env, jlayout);
		hi_sint32 angle = JFigureLayout_getAngle(env, jlayout);
		Render_setPerspectiveFov(render, near, far, angle);
		break;
	}
	case 3:
	{
		hi_sint32 w = JFigureLayout_getPerspectiveW(env, jlayout);
		hi_sint32 h = JFigureLayout_getPerspectiveH(env, jlayout);
		hi_sint32 near = JFigureLayout_getNear(env, jlayout);
		hi_sint32 far = JFigureLayout_getFar(env, jlayout);
		Render_setPerspectiveWH(render, near, far, w, h);
		break;
	}
	}

	hi_sint32 attrs = Render_getAttribute(render);

	jobject jlight = JEffect3D_getLight(env, jeffect);
	if (jlight)
	{
		attrs |= M3D_LIGHTING;
		hi_sint32 ambIntencity = JLight_getAmbIntensity(env, jlight);
		hi_sint32 dirIntencity = JLight_getDirIntensity(env, jlight);
		Vec3i dir;
		JLight_getDirVector(env, jlight, &dir);
		Render_setDirectionLight(render, &dir, dirIntencity);
		Render_setAmbientLight(render, ambIntencity);
	}
	else
	{
		attrs &= ~M3D_LIGHTING;
	}

	hi_sint32 shading = JEffect3D_getShadingType(env, jeffect);
	switch (shading)
	{
	case 1:
	{
		attrs |= M3D_TOON_SHADING;
		hi_sint32 tress = JEffect3D_getToonThreshold(env, jeffect);
		hi_sint32 high = JEffect3D_getToonHigh(env, jeffect);
		hi_sint32 low = JEffect3D_getToonLow(env, jeffect);
		Render_setToonParam(render, tress, high, low);
		break;
	}
	default:
		attrs &= ~M3D_TOON_SHADING;
		break;
	}

	hi_bool blend = JEffect3D_getEnableBlend(env, jeffect);
	if (blend) attrs |= M3D_BLEND;
	else attrs &= ~M3D_BLEND;

	hi_sint32 cx = JFigureLayout_getCenterX(env, jlayout);
	hi_sint32 cy = JFigureLayout_getCenterY(env, jlayout);
	Render_setScreenCenter(render, cx + x, cy + y);

	Texture* specular = JEffect3D_getTexture(env, jeffect);
	if (specular)
	{
		attrs |= M3D_SPECULAR;
		Render_setSphereTexture(render, specular);
	}
	else
	{
		attrs &= ~M3D_SPECULAR;
	}

	Render_setAttribute(render, attrs);

	IntArray list;
	list.num = env->GetArrayLength(jcommands);
	jint* listPtr = env->GetIntArrayElements(jcommands, NULL);
	list.array = (hi_sint32*)listPtr;
	hi_sint32 result = Render_drawCommandList(render, &list);
	env->ReleaseIntArrayElements(jcommands, listPtr, 0);
	return result;
}


JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nInit(JNIEnv* env, jobject)
{
	IAllocator* allocator = Allocator_getInstance();
	Render* ptr = (Render*)IAllocator_alloc(allocator, sizeof(Render));
	Render_initialize(ptr, allocator);
	return (jint)ptr;
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nRenderFigure
(JNIEnv* env, jobject obj, jobject jFigure, jint x, jint y, jobject jLayout, jobject jEffect)
{
	Render* render = getRender();
	Figure* figure = JFigure_get(env, jFigure);

	Atrans3i affine;
	JFigureLayout_getAffine(env, jLayout, &affine);
	Render_setViewTrans(render, &affine);

	TextureArray texArray;
	JFigure_getTextureArray(env, jFigure, &texArray);
	if (texArray.num > 0)
		Render_setTextureArray(render, &texArray);

	hi_sint32 projection = JFigureLayout_getProjectType(env, jLayout);
	switch (projection)
	{
	case 0:
	{
		hi_sint32 scaleX = JFigureLayout_getScaleX(env, jLayout);
		hi_sint32 scaleY = JFigureLayout_getScaleY(env, jLayout);
		Render_setOrthographicScale(render, scaleX, scaleY);
		break;
	}
	case 1:
	{
		hi_sint32 w = JFigureLayout_getParallelW(env, jLayout);
		hi_sint32 h = JFigureLayout_getParallelH(env, jLayout);
		Render_setOrthographicWH(render, w, h);
		break;
	}
	case 2:
	{
		hi_sint32 near = JFigureLayout_getNear(env, jLayout);
		hi_sint32 far = JFigureLayout_getFar(env, jLayout);
		hi_sint32 angle = JFigureLayout_getAngle(env, jLayout);
		Render_setPerspectiveFov(render, near, far, angle);
		break;
	}
	case 3:
	{
		hi_sint32 w = JFigureLayout_getPerspectiveW(env, jLayout);
		hi_sint32 h = JFigureLayout_getPerspectiveH(env, jLayout);
		hi_sint32 near = JFigureLayout_getNear(env, jLayout);
		hi_sint32 far = JFigureLayout_getFar(env, jLayout);
		Render_setPerspectiveWH(render, near, far, w, h);
		break;
	}
	}

	hi_sint32 attrs = Render_getAttribute(render);

	jobject jlight = JEffect3D_getLight(env, jEffect);
	if (jlight)
	{
		attrs |= M3D_LIGHTING;
		hi_sint32 ambIntencity = JLight_getAmbIntensity(env, jlight);
		hi_sint32 dirIntansity = JLight_getDirIntensity(env, jlight);
		Vec3i dir;
		JLight_getDirVector(env, jlight, &dir);
		Render_setDirectionLight(render, &dir, dirIntansity);
		Render_setAmbientLight(render, ambIntencity);
	}
	else
	{
		attrs &= ~M3D_LIGHTING;
	}

	hi_sint32 shading = JEffect3D_getShadingType(env, jEffect);
	switch (shading)
	{
	case 1:
	{
		attrs |= M3D_TOON_SHADING;
		hi_sint32 tress = JEffect3D_getToonThreshold(env, jEffect);
		hi_sint32 high = JEffect3D_getToonHigh(env, jEffect);
		hi_sint32 low = JEffect3D_getToonLow(env, jEffect);
		Render_setToonParam(render, tress, high, low);
		break;
	}
	default:
		attrs &= ~M3D_TOON_SHADING;
		break;
	}

	hi_bool isBlend = JEffect3D_getEnableBlend(env, jEffect);
	if (isBlend) attrs |= M3D_BLEND;
	else attrs &= ~M3D_BLEND;

	hi_sint32 cx = JFigureLayout_getCenterX(env, jLayout);
	hi_sint32 cy = JFigureLayout_getCenterY(env, jLayout);
	Render_setScreenCenter(render, cx + x, cy + y);

	Texture* specular = JEffect3D_getTexture(env, jEffect);
	if (specular)
	{
		attrs |= M3D_SPECULAR;
		Render_setSphereTexture(render, specular);
	}
	else
	{
		attrs &= ~M3D_SPECULAR;
	}

	Render_setAttribute(render, attrs);
	Texture* texNow = JFigure_getTexture(env, jFigure);
	if (texNow)
		Render_setTexture(render, texNow);

	return !Render_drawFigure(render, figure);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nBind(JNIEnv* env, jobject obj, jintArray jdata, jint w, jint h, jint cx, jint cy, jint cw, jint ch)
{
	Render* render = getRender();
	jint* buffer = env->GetIntArrayElements(jdata, NULL);
	jint len = env->GetArrayLength(jdata);
	env->SetIntField(obj, JGraphics3D_nBufPointer, (jint)buffer);
	Render_setVram(render, w, h, w, (hi_byte*)buffer);
	Render_setClipRect(render, cx, cy, cx + cw, cy + ch);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nCapture(JNIEnv* env, jobject obj, jintArray jdata)
{
	jint* buffer = (jint*)env->GetIntField(obj, JGraphics3D_nBufPointer);
	jint* src = env->GetIntArrayElements(jdata, NULL);
	jint len = env->GetArrayLength(jdata);
	memcpy(buffer, src, len * sizeof(jint));
	env->ReleaseIntArrayElements(jdata, src, JNI_ABORT);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nRender(JNIEnv* env, jobject obj, jintArray jdata)
{
	jint* buffer = (jint*)env->GetIntField(obj, JGraphics3D_nBufPointer);
	jint* dst = env->GetIntArrayElements(jdata, NULL);
	jint len = env->GetArrayLength(jdata);
	memcpy(dst, buffer, len * sizeof(jint));
	env->ReleaseIntArrayElements(jdata, dst, 0);
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nRelease(JNIEnv* env, jobject obj, jintArray jdata)
{
	jint* buffer = (jint*)env->GetIntField(obj, JGraphics3D_nBufPointer);
	env->ReleaseIntArrayElements(jdata, buffer, 0);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nFlush(JNIEnv* env, jobject obj)
{
	Render* render = getRender();
	return !Render_flush(render);
}

JNIEXPORT jint JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nDrawFigure(JNIEnv* env, jobject obj, jobject jFigure, jint x, jint y, jobject jLayout, jobject jEffect)
{
	hi_bool success = !Java_com_mascotcapsule_micro3d_v3_Graphics3D_nRenderFigure(env, obj, jFigure, x, y, jLayout, jEffect);
	if (success)
	{
		Render* render = getRender();
		success = Render_flush(render);
	}
	return !success;
}

JNIEXPORT void JNICALL Java_com_mascotcapsule_micro3d_v3_Graphics3D_nInitClass(JNIEnv* env, jclass clazz)
{
	JGraphics3D_nPointer    = env->GetFieldID(clazz, "nPointer"   , "I");
	JGraphics3D_nBufPointer = env->GetFieldID(clazz, "nBufPointer", "I");
}
