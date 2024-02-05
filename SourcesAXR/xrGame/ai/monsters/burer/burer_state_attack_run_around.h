#pragma once
#include "../state.h"

template<typename _Object>
class	CStateBurerAttackRunAround : public CState<_Object> {
	typedef CState<_Object>	inherited;

	Fvector				selected_point;
	u32					time_started;

	Fvector				dest_direction;

public:
						CStateBurerAttackRunAround	(_Object *obj);
	void		initialize					() override;
	void		execute						() override;

	bool		check_start_conditions		() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "burer_state_attack_run_around_inline.h"