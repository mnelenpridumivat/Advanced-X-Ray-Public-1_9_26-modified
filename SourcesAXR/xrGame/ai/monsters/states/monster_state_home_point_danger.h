#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterDangerMoveToHomePoint : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32					m_target_node;
	bool				m_skip_camp;
	Fvector				m_danger_pos;

public:
						CStateMonsterDangerMoveToHomePoint(_Object *obj);
	void		initialize				() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;

	bool		check_start_conditions	() override;
	bool		check_completion		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	void		reselect_state			() override;
	void		setup_substates			() override;
private:
			Fvector		&get_most_danger_pos	();
};

#include "monster_state_home_point_danger_inline.h"
