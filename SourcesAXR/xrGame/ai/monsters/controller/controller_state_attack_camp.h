#pragma once

template<typename _Object>
class CStateControlCamp : public CState<_Object> {
	typedef	CState<_Object>		inherited;

	float			m_angle_from;
	float			m_angle_to;
	
	float			m_target_angle;
	u32				m_time_next_updated;

public:

					CStateControlCamp	(_Object *obj) : inherited(obj) {}
	~CStateControlCamp	() override {}

	void	initialize				() override;
	void	execute					() override;
	bool	check_completion		() override;
	bool	check_start_conditions	() override;

	void	remove_links			(CObject* object) override {}

private:

	virtual void	update_target_angle		();

};

#include "controller_state_attack_camp_inline.h"
