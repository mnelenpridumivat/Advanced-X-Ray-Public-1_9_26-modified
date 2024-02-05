////////////////////////////////////////////////////////////////////////////
//	Module 		: danger_cover_location.h
//	Created 	: 24.05.2004
//  Modified 	: 14.01.2005
//	Author		: Dmitriy Iassenev
//	Description : Danger cover location
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "danger_location.h"

class CCoverPoint;

class CDangerCoverLocation : public CDangerLocation {
private:
	const CCoverPoint		*m_cover;
	
public:
	IC						CDangerCoverLocation	(const CCoverPoint *cover, u32 level_time, u32 interval, float radius, const squad_mask_type &mask = static_cast<squad_mask_type>(-1));
	const Fvector	&position				() const override;
};

#include "danger_cover_location_inline.h"