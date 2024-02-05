#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterSquadRest : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	u32		time_next_state_reselect;

public:
						CStateMonsterSquadRest		(_Object *obj);
	~CStateMonsterSquadRest		() override;

	void		reselect_state				() override;
	void		setup_substates				() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_squad_rest_inline.h"