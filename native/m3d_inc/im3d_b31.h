#ifndef __im3d_b31_H__
#define __im3d_b31_H__

#include "Micro3D.h"

//*************************************** defines copied from AEE.h (BREW) *******************************************************
#define VTBL(iname) iname##Vtbl

#define QINTERFACE(iname) struct _##iname {\
							 struct VTBL(iname)  *pvt; \
						   };\
						   typedef struct VTBL(iname) VTBL(iname); \
						   struct VTBL(iname)

#define DECLARE_IBASE(iname) \
  uint32_t  (*AddRef)         (iname*);\
  uint32_t  (*Release)        (iname*);\

#define GET_PVTBL(p,iname)       ((iname*)(void*)p)->pvt
//************************************* end defines copied from AEE.h ************************************************************

// IMicro3D Interface typedef
typedef struct _IMicro3D IMicro3D;

//********************************************************************************************************************************
//
// IMicro3D Interface Definition
//
//********************************************************************************************************************************
QINTERFACE(IMicro3D)
{
	DECLARE_IBASE(IMicro3D)

	void (*Atrans3i_set)(Atrans3i * This,
		hi_sint32 a00, hi_sint32 a01, hi_sint32 a02, hi_sint32 a03,
		hi_sint32 a10, hi_sint32 a11, hi_sint32 a12, hi_sint32 a13,
		hi_sint32 a20, hi_sint32 a21, hi_sint32 a22, hi_sint32 a23);
	void (*Atrans3i_setIdentity)(Atrans3i * This);
	void (*Atrans3i_transPoint)(const Atrans3i * This, const Vec3i * src, Vec3i * dst);
	void (*Atrans3i_multiply)(Atrans3i * This, const Atrans3i * t);
	void (*Atrans3i_multiply2)(Atrans3i * This, const Atrans3i * t1, const Atrans3i * t2);
	void (*Atrans3i_setRotateX)(Atrans3i * This, hi_sint32 angle);
	void (*Atrans3i_setRotateY)(Atrans3i * This, hi_sint32 angle);
	void (*Atrans3i_setRotateZ)(Atrans3i * This, hi_sint32 angle);
	void (*Atrans3i_setRotateV)(Atrans3i * This, const Vec3i * axis, hi_sint32 angle);
	void (*Atrans3i_setViewTrans)(Atrans3i * This, const Vec3i * position, const Vec3i * look, const Vec3i * up);
	void (*Atrans3i_normalize)(Atrans3i * This, const Atrans3i * src);
	void (*Atrans3iArray_initialize)(Atrans3iArray * This);
	void (*Atrans3iArray_finalize)(Atrans3iArray * This);
	hi_bool(*Atrans3iArray_set)(Atrans3iArray * This, Atrans3i * trans, hi_sint32 num);
	hi_bool(*Atrans3iArray_isLocked)(Atrans3iArray * This);

	hi_sint32(*Vec3i_dot)(const Vec3i * This, const Vec3i * v);
	void      (*Vec3i_cross)(Vec3i * This, const Vec3i * v);
	void      (*Vec3i_cross2)(Vec3i * This, const Vec3i * u, const Vec3i * v);
	void      (*Vec3i_normalize12)(Vec3i * This, const Vec3i * src);

	void      (*ActTable_initialize)(ActTable * This, IAllocator * allocator);
	void      (*ActTable_finalize)(ActTable * This);
	hi_bool(*ActTable_loadMtraData)(ActTable * This, IIstream * iis);
	hi_sint32(*ActTable_getNumActions)(const ActTable * This);
	hi_sint32(*ActTable_getNumFrames)(const ActTable * This, hi_sint32 act_idx);
	hi_bool(*ActTable_isLocked)(const ActTable * This);

	void      (*Figure_initialize)(Figure * This, IAllocator * allocator);
	void      (*Figure_finalize)(Figure * This);
	hi_bool(*Figure_loadMbacData)(Figure * This, IIstream * iis);
	void      (*Figure_setPosture)(Figure * This, struct tagActTable* act, hi_sint32 act_idx, hi_sint32 frame);
	void	  (*Figure_setPattern)(Figure * This, hi_sint32 pattern);
	hi_sint32(*Figure_getNumPatterns)(Figure * This);
	hi_bool(*Figure_isLocked)(const Figure * This);

	void    (*Render_initialize)(Render * This, IAllocator * allocator);
	void    (*Render_finalize)(Render * This);
	hi_bool(*Render_setTargetTexture)(Render * This, Texture * texture);
	void    (*Render_setVram)(Render * This, hi_uint32 width, hi_uint32 height, hi_sint32 pitch, hi_byte * buffer);
	void    (*Render_setClipRect)(Render * This, hi_sint32 left, hi_sint32 top, hi_sint32 right, hi_sint32 bottom);
	void    (*Render_setViewTrans)(Render * This, const Atrans3i * trans);
	void    (*Render_setScreenCenter)(Render * This, hi_sint32 cx, hi_sint32 cy);
	void	(*Render_setPerspectiveFov)(Render * This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 angle);
	void	(*Render_setPerspectiveWH)(Render * This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 vw, hi_sint32 vh);
	void    (*Render_setOrthographicScale)(Render * This, hi_sint32 sx, hi_sint32 sy);
	void    (*Render_setOrthographicWH)(Render * This, hi_sint32 vw, hi_sint32 vh);
	void	(*Render_setAttribute)(Render * This, hi_sint32 attribute);
	hi_sint32(*Render_getAttribute)(Render * This);
	void    (*Render_setAmbientLight)(Render * This, hi_sint32 intensity);
	void    (*Render_setDirectionLight)(Render * This, const Vec3i * dir, hi_sint32 intensity);
	hi_bool(*Render_setSphereTexture)(Render * This, Texture * texture);
	void    (*Render_setToonParam)(Render * This, hi_sint32 threshold, hi_sint32 high, hi_sint32 low);
	hi_bool(*Render_setTexture)(Render * This, Texture * texture);
	hi_bool(*Render_setTextureArray)(Render * This, TextureArray * array);
	hi_bool(*Render_flush)(Render * This);
	hi_bool(*Render_drawFigure)(Render * This, struct tagFigure* fig);
	void	(*Render_setTextureIndex)(Render * This, hi_sint32 index);
	void	(*Render_setViewTransArray)(Render * This, Atrans3iArray * array);
	void	(*Render_setViewTransIndex)(Render * This, hi_sint32 index);
	hi_bool(*Render_drawPrimitive)(Render * This, hi_sint32 primtype, IntArray * coord, IntArray * normal, IntArray * texcoord, IntArray * color);
	hi_sint32(*Render_drawCommandList)(Render * This, IntArray * array);
	void	(*Render_setPerspectiveW)(Render * This, hi_sint32 z_near, hi_sint32 z_far, hi_sint32 vw);
	void    (*Render_setOrthographicW)(Render * This, hi_sint32 vw);
	hi_bool(*Render_drawFigure_v2)(Render * This, struct tagFigure* fig);

	hi_sint32(*Util3D_iSqrt)(hi_uint32 x);
	hi_sint32(*Util3D_sin12)(hi_sint32 a);
	hi_sint32(*Util3D_cos12)(hi_sint32 a);
	hi_sint32(*Util3D_getVersion)(void);

	void    (*Texture_initialize)(Texture * This, IAllocator * allocator);
	void    (*Texture_finalize)(Texture * This);
	hi_bool(*Texture_loadBmpData)(Texture * This, IIstream * iis, hi_texture_type type);
	hi_bool(*Texture_isSphereTexture)(const Texture * This);
	hi_bool(*Texture_isLocked)(const Texture * This);

	hi_uint32(*ActTable_getNumAction)(const ActTable * This);
	hi_sint32(*ActTable_getMaxFrame)(const ActTable * This, hi_sint32 act_idx);
	void      (*ActTable_setFigure)(ActTable * This, Figure * fig);
	void      (*ActTable_figPosture)(ActTable * This, hi_sint32 act_idx, hi_sint32 frame);
	void	 (*Util3D_getUnitVector12)(const Vec3i * src, Vec3i * dst);
	void	  (*Util3D_getRotateX)(hi_sint32 a, Atrans3i * t);
	void	  (*Util3D_getRotateY)(hi_sint32 a, Atrans3i * t);
	void	  (*Util3D_getRotateZ)(hi_sint32 a, Atrans3i * t);
	void	  (*Util3D_getRotateV)(const Vec3i * axis, hi_sint32 angle, Atrans3i * This);
	void	 (*Util3D_getViewTrans)(const Vec3i * position, const Vec3i * look, const Vec3i * up, Atrans3i * This);
	void	  (*Util3D_getUnitTrans)(const Atrans3i * src, Atrans3i * dst);
	void	  (*Render_enableLight)(Render * This, hi_bool flag);
	void	  (*Render_enableSphereMap)(Render * This, hi_bool flag);
	void	  (*Render_enableSemiTransparent)(Render * This, hi_bool flag);
	void      (*Texture_setToonShader)(Texture * This, hi_sint32 threshold, hi_sint32 high, hi_sint32 low);
	void     (*Texture_setNormalShader)(Texture * This);

	void      (*Render_fillRect)(Render * This, hi_uint32 rgb, hi_sint32 x, hi_sint32 y, hi_sint32 w, hi_sint32 h);
	void     (*Render_fillRectRaw)(Render * This, hi_uint32 pixel, hi_sint32 x, hi_sint32 y, hi_sint32 w, hi_sint32 h);
};

#define IMICRO3D_AddRef(p)							GET_PVTBL(p,IMicro3D)->AddRef(p)
#define IMICRO3D_Release(p)							GET_PVTBL(p,IMicro3D)->Release(p)

#define IMICRO3D_Atrans3i_set(p, a, a00, a01, a02, a03,a10, a11, a12, a13,a20, a21, a22, a23)  GET_PVTBL(p,IMicro3D)->Atrans3i_set(a, a00, a01, a02, a03,a10, a11, a12, a13,a20, a21, a22, a23)
#define IMICRO3D_Atrans3i_setIdentity(p,a)		 GET_PVTBL(p,IMicro3D)->Atrans3i_setIdentity(a)
#define IMICRO3D_Atrans3i_transPoint(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Atrans3i_transPoint(a,b,c)
#define IMICRO3D_Atrans3i_multiply(p,a,b)		 GET_PVTBL(p,IMicro3D)->Atrans3i_multiply(a,b)
#define IMICRO3D_Atrans3i_multiply2(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Atrans3i_multiply2(a,b,c)
#define IMICRO3D_Atrans3i_setRotateX(p,a,b)		 GET_PVTBL(p,IMicro3D)->Atrans3i_setRotateX(a,b)
#define IMICRO3D_Atrans3i_setRotateY(p,a,b)		 GET_PVTBL(p,IMicro3D)->Atrans3i_setRotateY(a,b)
#define IMICRO3D_Atrans3i_setRotateZ(p,a,b)		 GET_PVTBL(p,IMicro3D)->Atrans3i_setRotateZ(a,b)
#define IMICRO3D_Atrans3i_setRotateV(p,a,b,c)		 GET_PVTBL(p,IMicro3D)->Atrans3i_setRotateV(a,b,c)
#define IMICRO3D_Atrans3i_setViewTrans(p,a,b,c,d)	 GET_PVTBL(p,IMicro3D)->Atrans3i_setViewTrans(a,b,c,d)
#define IMICRO3D_Atrans3i_normalize(p,a,b)		     GET_PVTBL(p,IMicro3D)->Atrans3i_normalize (a,b)
#define IMICRO3D_Atrans3iArray_initialize(p,a)	     GET_PVTBL(p,IMicro3D)->Atrans3iArray_initialize (a)
#define IMICRO3D_Atrans3iArray_finalize(p,a)	     GET_PVTBL(p,IMicro3D)->Atrans3iArray_finalize(a)
#define IMICRO3D_Atrans3iArray_set(p,a,b,c)	         GET_PVTBL(p,IMicro3D)->Atrans3iArray_set(a,b,c)
#define IMICRO3D_Atrans3iArray_isLocked(p,a)	     GET_PVTBL(p,IMicro3D)->Atrans3iArray_isLocked(a)

#define IMICRO3D_Vec3i_dot(p,a,b)			GET_PVTBL(p,IMicro3D)->Vec3i_dot(a,b)
#define IMICRO3D_Vec3i_cross(p,a,b)			GET_PVTBL(p,IMicro3D)->Vec3i_cross(a,b)
#define IMICRO3D_Vec3i_cross2(p,a,b,c)		GET_PVTBL(p,IMicro3D)->Vec3i_cross2(a,b,c)
#define IMICRO3D_Vec3i_normalize12(p,a,b)	 GET_PVTBL(p,IMicro3D)->Vec3i_normalize12(a,b)

#define IMICRO3D_ActTable_initialize(p,a,b)			 GET_PVTBL(p,IMicro3D)->ActTable_initialize(a,b)
#define IMICRO3D_ActTable_finalize(p,a)			GET_PVTBL(p,IMicro3D)->ActTable_finalize(a)
#define IMICRO3D_ActTable_loadMtraData(p,a,b)	 GET_PVTBL(p,IMicro3D)->ActTable_loadMtraData(a,b)
#define IMICRO3D_ActTable_getNumActions(p,a)	 GET_PVTBL(p,IMicro3D)->ActTable_getNumActions(a) 
#define IMICRO3D_ActTable_getNumFrames(p,a,b)	 GET_PVTBL(p,IMicro3D)->ActTable_getNumFrames(a,b)
#define IMICRO3D_ActTable_isLocked(p,a)			 GET_PVTBL(p,IMicro3D)->ActTable_isLocked(a)

#define IMICRO3D_Figure_initialize(p,a,b)	GET_PVTBL(p,IMicro3D)->Figure_initialize(a,b)
#define IMICRO3D_Figure_finalize(p,a)	GET_PVTBL(p,IMicro3D)->Figure_finalize(a)
#define IMICRO3D_Figure_loadMbacData(p,a,b)		 GET_PVTBL(p,IMicro3D)->Figure_loadMbacData(a,b)
#define IMICRO3D_Figure_setPosture(p,a,b,c,d)	 GET_PVTBL(p,IMicro3D)->Figure_setPosture(a,b,c,d)
#define IMICRO3D_Figure_setPattern(p,a,b)	 GET_PVTBL(p,IMicro3D)->Figure_setPattern(a,b)
#define IMICRO3D_Figure_getNumPatterns(p,a)	 GET_PVTBL(p,IMicro3D)->Figure_getNumPatterns(a)
#define IMICRO3D_Figure_isLocked(p,a)	 GET_PVTBL(p,IMicro3D)->Figure_isLocked(a)

#define IMICRO3D_Render_initialize(p,a,b)		GET_PVTBL(p,IMicro3D)->Render_initialize(a,b)
#define IMICRO3D_Render_finalize(p,a)			GET_PVTBL(p,IMicro3D)->Render_finalize(a)
#define IMICRO3D_Render_setTargetTexture(p,a,b)  GET_PVTBL(p,IMicro3D)->Render_setTargetTexture(a,b)
#define IMICRO3D_Render_setVram(p,a,b,c,d,e)	GET_PVTBL(p,IMicro3D)->Render_setVram(a,b,c,d,e)
#define IMICRO3D_Render_setClipRect(p,a,b,c,d,e)  GET_PVTBL(p,IMicro3D)->Render_setClipRect(a,b,c,d,e)
#define IMICRO3D_Render_setViewTrans(p,a,b)			GET_PVTBL(p,IMicro3D)->Render_setViewTrans(a,b)
#define IMICRO3D_Render_setScreenCenter(p,a,b,c)	GET_PVTBL(p,IMicro3D)->Render_setScreenCenter(a,b,c)
#define IMICRO3D_Render_setPerspectiveFov(p,a,b,c,d)  GET_PVTBL(p,IMicro3D)->Render_setPerspectiveFov(a,b,c,d)
#define IMICRO3D_Render_setPerspectiveWH(p,a,b,c,d,e)	 GET_PVTBL(p,IMicro3D)->Render_setPerspectiveWH(a,b,c,d,e)
#define IMICRO3D_Render_setOrthographicScale(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Render_setOrthographicScale(a,b,c)
#define IMICRO3D_Render_setOrthographicWH(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Render_setOrthographicWH(a,b,c)
#define IMICRO3D_Render_setAttribute(p,a,b)			GET_PVTBL(p,IMicro3D)->Render_setAttribute(a,b)
#define IMICRO3D_Render_getAttribute(p,a)			GET_PVTBL(p,IMicro3D)->Render_getAttribute(a)
#define IMICRO3D_Render_setAmbientLight(p,a,b)		GET_PVTBL(p,IMicro3D)->Render_setAmbientLight(a,b)
#define IMICRO3D_Render_setDirectionLight(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Render_setDirectionLight(a,b,c)
#define IMICRO3D_Render_setSphereTexture(p,a,b)		GET_PVTBL(p,IMicro3D)->Render_setSphereTexture(a,b)
#define IMICRO3D_Render_setToonParam(p,a,b,c,d)		 GET_PVTBL(p,IMicro3D)->Render_setToonParam(a,b,c,d)
#define IMICRO3D_Render_setTexture(p,a,b)		GET_PVTBL(p,IMicro3D)->Render_setTexture(a,b)
#define IMICRO3D_Render_setTextureArray(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_setTextureArray(a,b)
#define IMICRO3D_Render_flush(p,a)			GET_PVTBL(p,IMicro3D)->Render_flush(a)
#define IMICRO3D_Render_drawFigure(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_drawFigure(a,b)
#define IMICRO3D_Render_drawFigure_v2(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_drawFigure_v2(a,b)
#define IMICRO3D_Render_setTextureIndex(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_setTextureIndex(a,b)
#define IMICRO3D_Render_setViewTransArray(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_setViewTransArray(a,b)
#define IMICRO3D_Render_setViewTransIndex(p,a,b)	GET_PVTBL(p,IMicro3D)->Render_setViewTransIndex(a,b)
#define IMICRO3D_Render_drawPrimitive(p,a,b,c,d,e,f)	GET_PVTBL(p,IMicro3D)->Render_drawPrimitive(a,b,c,d,e,f)
#define IMICRO3D_Render_drawCommandList(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_drawCommandList(a,b)
#define IMICRO3D_Render_setPerspectiveW(p,a,b,c,d)	 GET_PVTBL(p,IMicro3D)->Render_setPerspectiveW(a,b,c,d)
#define IMICRO3D_Render_setOrthographicW(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_setOrthographicW(a,b)

#define IMICRO3D_Util3D_iSqrt(p,a)			GET_PVTBL(p,IMicro3D)->Util3D_iSqrt(a)
#define IMICRO3D_Util3D_sin12(p,a)			GET_PVTBL(p,IMicro3D)->Util3D_sin12(a)
#define IMICRO3D_Util3D_cos12(p,a)			GET_PVTBL(p,IMicro3D)->Util3D_cos12(a)
#define IMICRO3D_Util3D_getVersion(p)		GET_PVTBL(p,IMicro3D)->Util3D_getVersion()

#define IMICRO3D_Texture_initialize(p,a,b)		GET_PVTBL(p,IMicro3D)->Texture_initialize(a,b)
#define IMICRO3D_Texture_finalize(p,a)			 GET_PVTBL(p,IMicro3D)->Texture_finalize(a)
#define IMICRO3D_Texture_loadBmpData(p,a,b,c)	 GET_PVTBL(p,IMicro3D)->Texture_loadBmpData(a,b,c)
#define IMICRO3D_Texture_isSphereTexture(p,a)			GET_PVTBL(p,IMicro3D)->Texture_isSphereTexture(a)
#define IMICRO3D_Texture_isLocked(p,a)			 GET_PVTBL(p,IMicro3D)->Texture_isLocked(a)

#define IMICRO3D_ActTable_getNumAction(p,a)		 GET_PVTBL(p,IMicro3D)->ActTable_getNumAction(a)
#define IMICRO3D_ActTable_getMaxFrame(p,a,b)		GET_PVTBL(p,IMicro3D)->ActTable_getMaxFrame(a,b)
#define IMICRO3D_ActTable_setFigure(p,a,b)		GET_PVTBL(p,IMicro3D)->ActTable_setFigure(a,b)
#define IMICRO3D_ActTable_figPosture(p,a,b,c)		GET_PVTBL(p,IMicro3D)->ActTable_figPosture(a,b,c)
#define IMICRO3D_Util3D_getUnitVector12(p,a,b)		 GET_PVTBL(p,IMicro3D)->Util3D_getUnitVector12(a,b)	
#define IMICRO3D_Util3D_getRotateX(p,a,b)		 GET_PVTBL(p,IMicro3D)->Util3D_getRotateX(a,b)
#define IMICRO3D_Util3D_getRotateY(p,a,b)		 GET_PVTBL(p,IMicro3D)->Util3D_getRotateY(a,b)
#define IMICRO3D_Util3D_getRotateZ(p,a,b)		GET_PVTBL(p,IMicro3D)->Util3D_getRotateZ(a,b)
#define IMICRO3D_Util3D_getRotateV(p,a,b,c)		 GET_PVTBL(p,IMicro3D)->Util3D_getRotateV(a,b,c)
#define IMICRO3D_Util3D_getViewTrans(p,a,b,c,d)	 GET_PVTBL(p,IMicro3D)->Util3D_getViewTrans(a,b,c,d)	
#define IMICRO3D_Util3D_getUnitTrans(p,a,b)		 GET_PVTBL(p,IMicro3D)->Util3D_getUnitTrans(a,b)
#define IMICRO3D_Render_enableLight(p,a,b)		 GET_PVTBL(p,IMicro3D)->Render_enableLight(a,b)
#define IMICRO3D_Render_enableSphereMap(p,a,b)		GET_PVTBL(p,IMicro3D)->Render_enableSphereMap(a,b)
#define IMICRO3D_Render_enableSemiTransparent(p,a,b)	 GET_PVTBL(p,IMicro3D)->Render_enableSemiTransparent(a,b)
#define IMICRO3D_Texture_setToonShader(p,a,b,c,d)	 GET_PVTBL(p,IMicro3D)->Texture_setToonShader(a,b,c,d)
#define IMICRO3D_Texture_setNormalShader(p,a)		 GET_PVTBL(p,IMicro3D)->Texture_setNormalShader(a)	

#define IMICRO3D_Render_fillRect(p,a,b,c,d,f,g)		GET_PVTBL(p,IMicro3D)->Render_fillRect(a,b,c,d,f,g)
#define IMICRO3D_Render_fillRectRaw(p,a,b,c,d,f,g)	GET_PVTBL(p,IMicro3D)->Render_fillRectRaw(a,b,c,d,f,g)

/*=====================================================================
  INTERFACES   DOCUMENTATION
=======================================================================

Interface Name: IMicro3D

Description:
   IMicro3D is a interface made to show 3D graphics under BREW.
   IMicro3DUse applet is complementary to this class
   since it dynamically creates and instance of this class and uses
   its exported methods.

=======================================================================

Function:  IMICRO3D_AddRef()

Description:
		This function increases the reference count for the Micro3D object

Prototype:
	uint32 IMICRO3D_AddRef(IMicro3D * po)

Parameters:
   po: Pointer to IMicro3D interface whos reference count is to be incremented

Return Value:
	The updated reference count

Comments:  None

Side Effects: None

=======================================================================

Function:  IMICRO3D_Release()

Description:
		This function decreases the reference count for the Micro3D object. If
		the reference count reaches zero, it does the required cleanup

Prototype:
	uint32 IMICRO3D_Release(IMicro3D* po)

Parameters:
   po: Pointer to the IMicro3D interface whose reference count needs to be
	decremented.

Return Value:
   The updated reference count

Comments:  None

Side Effects: None

=======================================================================*/

#endif  //__im3d_b31_H__


