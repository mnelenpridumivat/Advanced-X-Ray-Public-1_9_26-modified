#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterControlledFollow : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
						CStateMonsterControlledFollow	(_Object *obj);
	void		reselect_state					() override;
	void		setup_substates					() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_controlled_follow_inline.h"
