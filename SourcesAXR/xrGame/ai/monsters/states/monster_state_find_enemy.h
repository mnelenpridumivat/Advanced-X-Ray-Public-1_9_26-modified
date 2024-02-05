#pragma once

#include "../state.h"


template<typename _Object>
class	CStateMonsterFindEnemy : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
						CStateMonsterFindEnemy	(_Object *obj);
	~CStateMonsterFindEnemy	() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	void		reselect_state			() override;
};

#include "monster_state_find_enemy_inline.h"

