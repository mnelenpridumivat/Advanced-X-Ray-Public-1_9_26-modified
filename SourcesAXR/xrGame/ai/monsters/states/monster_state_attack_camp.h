#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterAttackCamp : public CState<_Object> {
	typedef CState<_Object> inherited;
	typedef CState<_Object> *state_ptr;

	u32					m_target_node;
public:
						CStateMonsterAttackCamp	(_Object *obj);

	void 		initialize				() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;

	void		check_force_state		() override;
	void		reselect_state			() override;
	void		setup_substates			() override;

};

#include "monster_state_attack_camp_inline.h"
