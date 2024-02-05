#pragma once
#include "control_combase.h"

struct SControlThreatenData : public ControlCom::IComData {
	LPCSTR	animation;
	float	time;
};

class CControlThreaten : public CControl_ComCustom<SControlThreatenData> {
	typedef CControl_ComCustom<SControlThreatenData> inherited;

public:
	void	reinit					() override;
	void	update_schedule			() override;
	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	void	activate				() override;
	void	on_release				() override;
	bool	check_start_conditions	() override;
};

