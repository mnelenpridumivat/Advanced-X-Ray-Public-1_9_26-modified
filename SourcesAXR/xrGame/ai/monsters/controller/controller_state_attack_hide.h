#pragma once

template<typename _Object>
class CStateControlHide : public CState<_Object> {
	typedef	CState<_Object>		inherited;
	typedef	CState<_Object>*	state_ptr;

	bool			m_cover_reached;

	struct {
		Fvector position;
		u32		node;
	} target;

	u32				m_time_finished;

	bool			m_state_fast_run;

public:

					CStateControlHide		(_Object *obj) : inherited(obj) {}
	~CStateControlHide		() override {}

	void	initialize				() override;
	void	execute					() override;

	void	finalize				() override;
	void	critical_finalize		() override;
	void	remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 	check_completion		() override;
	bool 	check_start_conditions	() override;


private:
			void	select_target_point		();
};


#include "controller_state_attack_hide_inline.h"

