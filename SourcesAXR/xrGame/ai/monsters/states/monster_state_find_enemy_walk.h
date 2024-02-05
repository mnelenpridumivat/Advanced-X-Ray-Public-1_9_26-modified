#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterFindEnemyWalkAround : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterFindEnemyWalkAround	(_Object *obj) : inherited(obj) {}
	void		execute						() override;
	bool		check_completion			() override {return false;}
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_find_enemy_walk_inline.h"
