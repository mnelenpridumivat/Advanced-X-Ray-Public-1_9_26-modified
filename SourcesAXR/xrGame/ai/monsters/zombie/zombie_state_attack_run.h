#pragma once

#include "../state.h"

template<typename _Object>
class CStateZombieAttackRun : public CState<_Object> {
	typedef CState<_Object> inherited;

	TTime				m_time_action_change;
	EAction				action;

public:
						CStateZombieAttackRun	(_Object *obj);
	~CStateZombieAttackRun	() override;

	void		initialize				() override;
	void		execute					() override;

	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

private:
			void		choose_action			();

};

#include "zombie_state_attack_run_inline.h"
