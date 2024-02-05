#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterSquadRestFollow : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	Fvector		last_point;

public:
						CStateMonsterSquadRestFollow	(_Object *obj);
	~CStateMonsterSquadRestFollow	() override;

	void		initialize						() override;
	void		reselect_state					() override;
	void		setup_substates					() override;
	void		check_force_state				() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_squad_rest_follow_inline.h"
