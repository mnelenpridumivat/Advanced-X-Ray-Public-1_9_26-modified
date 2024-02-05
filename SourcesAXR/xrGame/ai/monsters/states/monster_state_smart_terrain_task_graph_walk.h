#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterSmartTerrainTaskGraphWalk : public CStateMove<_Object> {
	typedef CStateMove<_Object> inherited;

	CALifeSmartTerrainTask	*m_task;

public:
						CStateMonsterSmartTerrainTaskGraphWalk	(_Object *obj) : inherited(obj) {}
	void		initialize				() override;
	void		execute					() override;
	bool		check_start_conditions	() override;
	bool		check_completion		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_smart_terrain_task_graph_walk_inline.h"