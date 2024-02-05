#pragma once
#include "mosquitobald.h"

class CObjectAnimator;

class CTorridZone :public CMosquitoBald
{
private:
	typedef	CCustomZone	inherited;
	CObjectAnimator		*m_animator;
public:
						CTorridZone			();
	~CTorridZone		() override;
	void		UpdateWorkload		(u32 dt) override;
	void		shedule_Update		(u32 dt) override;
	BOOL				net_Spawn			(CSE_Abstract* DC) override;

	bool		IsVisibleForZones	() override { return true;		}
	bool		Enable				() override;
	bool		Disable				() override;

	// Lain: added
	bool        light_in_slow_mode  () override;
	BOOL        AlwaysTheCrow       () override;
};