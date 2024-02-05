#pragma once

#include "CustomZone.h"
//#include "../Include/xrRender/KinematicsAnimated.h"
#include "../Include/xrRender/KinematicsAnimated.h"
#include "ZoneVisual.h"

#include "script_export_space.h"

class CHairsZone : public CVisualZone {
typedef				CVisualZone		inherited;		
public:
void		Affect				(SZoneObjectInfo* O) override;
void		Load				(LPCSTR section) override;

protected:
					float		m_min_speed_to_react;
bool		BlowoutState		() override;
void		CheckForAwaking		() override;

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CHairsZone)
#undef script_type_list
#define script_type_list save_type_list(CHairsZone)