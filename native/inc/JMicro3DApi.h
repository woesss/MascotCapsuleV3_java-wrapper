#pragma once

#if !defined(JMicro3D_API)
#define JMicro3D_API
#endif

#include <jni.h>
#include <Micro3D.h>
#include "Allocator.h"
#include "ByteIstream.h"
#include "com_mascotcapsule_micro3d_v3_ActionTable.h"
#include "com_mascotcapsule_micro3d_v3_AffineTrans.h"
#include "com_mascotcapsule_micro3d_v3_Effect3D.h"
#include "com_mascotcapsule_micro3d_v3_Figure.h"
#include "com_mascotcapsule_micro3d_v3_FigureLayout.h"
#include "com_mascotcapsule_micro3d_v3_Graphics3D.h"
#include "com_mascotcapsule_micro3d_v3_Light.h"
#include "com_mascotcapsule_micro3d_v3_Texture.h"
#include "com_mascotcapsule_micro3d_v3_Util3D.h"
#include "com_mascotcapsule_micro3d_v3_Vector3D.h"

ActTable*    JActionTable_get             (JNIEnv*, jobject               );
									      
void         JAffineTrans_get             (JNIEnv*, jobject, Atrans3i*    );
void         JAffineTrans_set             (JNIEnv*, jobject, Atrans3i*    );

jobject		 JEffect3D_getLight           (JNIEnv*, jobject               );
hi_sint32	 JEffect3D_getShadingType     (JNIEnv*, jobject               );
hi_bool		 JEffect3D_getEnableBlend     (JNIEnv*, jobject               );
Texture*     JEffect3D_getTexture         (JNIEnv*, jobject               );
hi_sint32	 JEffect3D_getToonThreshold   (JNIEnv*, jobject               );
hi_sint32	 JEffect3D_getToonHigh        (JNIEnv*, jobject               );
hi_sint32	 JEffect3D_getToonLow         (JNIEnv*, jobject               );
									      
Figure*      JFigure_get                  (JNIEnv*, jobject               );
Texture*     JFigure_getTexture           (JNIEnv*, jobject               );
void	     JFigure_getTextureArray      (JNIEnv*, jobject, TextureArray*);

hi_sint32	 JFigureLayout_getCenterX     (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getCenterY     (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getScaleX      (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getScaleY      (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getParallelW   (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getParallelH   (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getNear        (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getFar         (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getAngle       (JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getPerspectiveW(JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getPerspectiveH(JNIEnv*, jobject               );
hi_sint32	 JFigureLayout_getProjectType (JNIEnv*, jobject               );
jobjectArray JFigureLayout_getAffineArray (JNIEnv*, jobject               );
void		 JFigureLayout_getAffine      (JNIEnv*, jobject, Atrans3i*    );

void		 JLight_getDirVector          (JNIEnv*, jobject, Vec3i*       );
hi_sint32	 JLight_getDirIntensity       (JNIEnv*, jobject               );
hi_sint32	 JLight_getAmbIntensity       (JNIEnv*, jobject               );

Texture*     JTexture_get                 (JNIEnv*, jobject               );
									      
void         JVec3D_get                   (JNIEnv*, jobject, Vec3i*       );
void         JVec3D_set                   (JNIEnv*, jobject, Vec3i*       );
