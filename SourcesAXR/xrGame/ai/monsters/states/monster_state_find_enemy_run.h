#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterFindEnemyRun : public CState<_Object> {
	typedef CState<_Object> inherited;

	Fvector				target_point;
	u32					target_vertex;

public:
						CStateMonsterFindEnemyRun	(_Object *obj);
	~CStateMonsterFindEnemyRun	() override;

	void		initialize					() override;
	void		execute						() override;
	bool		check_completion			() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_find_enemy_run_inline.h"
