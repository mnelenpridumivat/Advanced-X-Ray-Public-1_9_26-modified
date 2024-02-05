#pragma once
#include "control_combase.h"
#include "../../../Include/xrRender/KinematicsAnimated.h"

struct SControlMeleeJumpData : public ControlCom::IComData {
	MotionID		anim_ls;
	MotionID		anim_rs;
};

class CControlMeleeJump : public CControl_ComCustom<SControlMeleeJumpData> {
	typedef CControl_ComCustom<SControlMeleeJumpData> inherited;
	
	u32				m_time_next_melee_jump;

public:
	void	reinit					() override;

	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	void	activate				() override;
	void	on_release				() override;
	bool	check_start_conditions	() override;
};

