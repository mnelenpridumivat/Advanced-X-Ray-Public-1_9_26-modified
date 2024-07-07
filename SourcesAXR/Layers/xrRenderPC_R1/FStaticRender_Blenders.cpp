#include "stdafx.h"

#include "blenderdefault.h"
#include "blender_default_aref.h"
#include "blender_vertex.h"
#include "blender_vertex_aref.h"
#include "../xrRender/blender_screen_set.h"
#include "blender_screen_gray.h"
#include "../xrRender/blender_editor_wire.h"
#include "../xrRender/blender_editor_selection.h"
#include "blender_LaEmB.h"
#include "../xrRender/blender_Lm(EbB).h"
#include "../xrRender/blender_BmmD.h"
#include "blender_shadow_world.h"
#include "blender_blur.h"
#include "blender_model.h"
#include "../xrRender/blender_model_ebb.h"
#include "../xrRender/blender_detail_still.h"
#include "../xrRender/blender_tree.h"
#include "../xrRender/blender_particle.h"

IBlender*	CRender::blender_create	(CLASS_ID cls)
{
/*#ifdef DEBUG
	if(cls == B_DEFAULT)			return xr_new<CBlender_default>();
	if(cls == B_DEFAULT_AREF)	return xr_new<CBlender_default_aref>();
	if(cls == B_VERT)			return xr_new<CBlender_Vertex>();
	if(cls == B_VERT_AREF)		return xr_new<CBlender_Vertex_aref>();
	if(cls == B_SCREEN_SET)		return xr_new<CBlender_Screen_SET>();
	if(cls == B_SCREEN_GRAY)		return xr_new<CBlender_Screen_GRAY>();
	if(cls == B_EDITOR_WIRE)		return xr_new<CBlender_Editor_Wire>();
	if(cls == B_EDITOR_SEL)		return xr_new<CBlender_Editor_Selection>();
	if(cls == B_LaEmB)			return xr_new<CBlender_LaEmB>();
	if(cls == B_LmEbB)			return xr_new<CBlender_LmEbB>();
	if(cls == B_BmmD)			return xr_new<CBlender_BmmD>();
	if(cls == B_SHADOW_WORLD)	return xr_new<CBlender_ShWorld>();
	if(cls == B_BLUR)			return xr_new<CBlender_Blur>();
	if(cls == B_MODEL)			return xr_new<CBlender_Model>();
	if(cls == B_MODEL_EbB)		return xr_new<CBlender_Model_EbB>();
	if(cls == B_DETAIL)			return xr_new<CBlender_Detail_Still>();
	if(cls == B_TREE)			return xr_new<CBlender_Tree>();
	if(cls == B_PARTICLE)		return xr_new<CBlender_Particle>();
#else*/
	switch (cls)
	{
	case B_DEFAULT:			return xr_new<CBlender_default>			();		
	case B_DEFAULT_AREF:	return xr_new<CBlender_default_aref>	();	
	case B_VERT:			return xr_new<CBlender_Vertex>			();		
	case B_VERT_AREF:		return xr_new<CBlender_Vertex_aref>		();	
	case B_SCREEN_SET:		return xr_new<CBlender_Screen_SET>		();	
	case B_SCREEN_GRAY:		return xr_new<CBlender_Screen_GRAY>		();	
	case B_EDITOR_WIRE:		return xr_new<CBlender_Editor_Wire>		();	
	case B_EDITOR_SEL:		return xr_new<CBlender_Editor_Selection>();
	case B_LaEmB:			return xr_new<CBlender_LaEmB>			();		
	case B_LmEbB:			return xr_new<CBlender_LmEbB>			();		
	case B_BmmD:			return xr_new<CBlender_BmmD>			();			
	case B_SHADOW_WORLD:	return xr_new<CBlender_ShWorld>			();		
	case B_BLUR:			return xr_new<CBlender_Blur>			();			
	case B_MODEL:			return xr_new<CBlender_Model>			();		
	case B_MODEL_EbB:		return xr_new<CBlender_Model_EbB>		();	
	case B_DETAIL:			return xr_new<CBlender_Detail_Still>	();	
	case B_TREE:			return xr_new<CBlender_Tree>			();	
	case B_PARTICLE:		return xr_new<CBlender_Particle>		();
	}
//#endif
	return 0;
}

void		CRender::blender_destroy(IBlender* &B)
{
	xr_delete(B);
}
