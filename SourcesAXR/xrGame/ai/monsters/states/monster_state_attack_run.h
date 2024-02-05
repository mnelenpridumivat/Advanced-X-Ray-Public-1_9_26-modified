#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterAttackRun : public CState<_Object> {
	typedef CState<_Object> inherited;

	TTime				m_time_path_rebuild;

public:
	IC					CStateMonsterAttackRun	(_Object *obj) : inherited(obj) {}

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;

};

#include "monster_state_attack_run_inline.h"
