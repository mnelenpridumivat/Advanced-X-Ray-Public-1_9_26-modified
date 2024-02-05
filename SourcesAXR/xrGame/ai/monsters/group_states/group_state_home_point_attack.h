#pragma once
#include "../state.h"

template<typename _Object>
class CStateGroupAttackMoveToHomePoint : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32					m_target_node;
	bool				m_skip_camp;

	TTime				m_first_tick_enemy_inaccessible;
	TTime				m_last_tick_enemy_inaccessible;
	TTime				m_state_started;

public:
						CStateGroupAttackMoveToHomePoint(_Object *obj);
	void		initialize				() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool		check_start_conditions	() override;
	bool		check_completion		() override;

	void		reselect_state			() override;
	void		setup_substates			() override;

			bool		enemy_inaccessible		();
};

#include "group_state_home_point_attack_inline.h"
