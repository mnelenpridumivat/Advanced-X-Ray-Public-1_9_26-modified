#pragma once

template<typename _Object>
class CStateControlFire : public CState<_Object> {
	typedef	CState<_Object>		inherited;

	u32				m_time_started;
	u32				m_time_state_last_execute;

public:

					CStateControlFire	(_Object *obj) : inherited(obj) {}
	~CStateControlFire	() override {}

	void	reinit					() override;
	void	initialize				() override;
	void	execute					() override;
	void	finalize				() override;
	void	critical_finalize		() override;
	bool	check_completion		() override;
	bool	check_start_conditions	() override;

};

#include "controller_state_attack_fire_inline.h"
