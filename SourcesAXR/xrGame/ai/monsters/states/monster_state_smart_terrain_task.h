#pragma once
#include "../state.h"

#include "../../../alife_smart_terrain_task.h"

template<typename _Object>
class CStateMonsterSmartTerrainTask : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	CALifeSmartTerrainTask *m_current_task;
public:
						CStateMonsterSmartTerrainTask	(_Object *obj);
	~CStateMonsterSmartTerrainTask	() override;

	void		initialize				() override;
	void		reselect_state			() override;
	bool		check_start_conditions	() override;
	bool		check_completion		() override;
	void		setup_substates			() override;
	void		check_force_state		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_smart_terrain_task_inline.h"
