#pragma once
#include "../state.h"

template<typename _Object>
class CStateMonsterSteal : public CState<_Object> {
	typedef CState<_Object> inherited;

public:
						CStateMonsterSteal		(_Object *obj);

	void		initialize				() override;
	void		execute					() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 		check_completion		() override;
	bool 		check_start_conditions	() override;

private:
			bool		check_conditions		();
};

#include "monster_state_steal_inline.h"
