#pragma once


template<typename _Object>
class CStateMonsterAttackCampStealOut : public CStateMove<_Object> {
	typedef CStateMove<_Object> inherited;

public:
						CStateMonsterAttackCampStealOut	(_Object *obj);

	void		execute					() override;
	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_attack_camp_stealout_inline.h"
