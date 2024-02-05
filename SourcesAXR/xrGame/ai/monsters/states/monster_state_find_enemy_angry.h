#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterFindEnemyAngry : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterFindEnemyAngry	(_Object *obj);
	~CStateMonsterFindEnemyAngry() override;

	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_find_enemy_angry_inline.h"
