#pragma once

#include "../state.h"
#include "../states/monster_state_attack.h"

template<typename _Object>
class	CStateBurerAttackMelee : public CStateMonsterAttack<_Object> {
	typedef CStateMonsterAttack<_Object>	inherited;

public:
						CStateBurerAttackMelee			(_Object *obj);
	bool		check_start_conditions			() override;
	bool		check_completion				() override;
};

#include "burer_state_attack_melee_inline.h"
