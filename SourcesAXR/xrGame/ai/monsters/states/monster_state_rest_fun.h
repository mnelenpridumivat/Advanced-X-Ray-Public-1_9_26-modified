#pragma once

#include "../state.h"
#include "../../../ai_debug.h"

template<typename _Object>
class CStateMonsterRestFun : public CState<_Object> {
	typedef CState<_Object> inherited;

	u32					time_last_hit;

public:
						CStateMonsterRestFun	(_Object *obj);
	void		initialize				() override;
	void		execute					() override;
	bool		check_completion		() override;
	bool		check_start_conditions	() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_rest_fun_inline.h"
