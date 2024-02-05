#pragma once
#include "control_combase.h"

struct SControlCriticalWoundData : public ControlCom::IComData {
	LPCSTR	animation;
};

class CControlCriticalWound : public CControl_ComCustom<SControlCriticalWoundData> {
	typedef CControl_ComCustom<SControlCriticalWoundData> inherited;

public:
	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	void	activate				() override;
	void	on_release				() override;
	bool	check_start_conditions	() override;
};

