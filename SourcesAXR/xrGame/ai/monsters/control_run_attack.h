#pragma once
#include "control_combase.h"

class CControlRunAttack : public CControl_ComCustom<> {
	float			m_min_dist;
	float			m_max_dist;

	u32				m_min_delay;
	u32				m_max_delay;

	u32				m_time_next_attack;

public:
	void	load					(LPCSTR section) override;
	void	reinit					() override;

	void	on_event				(ControlCom::EEventType, ControlCom::IEventData*) override;
	void	activate				() override;
	void	on_release				() override;
	bool	check_start_conditions	() override;
};

