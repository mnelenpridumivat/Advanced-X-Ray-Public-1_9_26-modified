#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterAttackRunAttack : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterAttackRunAttack	(_Object *obj) : inherited(obj) {};

	void		initialize						() override;
	void		execute							() override;
	void		finalize						() override;
	void		critical_finalize				() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}

	bool 		check_completion				() override;
	bool 		check_start_conditions			() override;
};

#include "monster_state_attack_run_attack_inline.h"
