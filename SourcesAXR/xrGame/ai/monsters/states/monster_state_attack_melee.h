#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterAttackMelee : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterAttackMelee	(_Object *obj);
	~CStateMonsterAttackMelee	() override;

	void		execute						() override;

	bool 		check_completion			() override;
	bool 		check_start_conditions		() override;
	void		remove_links				(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_attack_melee_inline.h"
