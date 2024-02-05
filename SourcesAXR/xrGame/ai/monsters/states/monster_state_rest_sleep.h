#pragma once

#include "../state.h"
#include "../../../ai_debug.h"

template<typename _Object>
class CStateMonsterRestSleep : public CState<_Object> {
	typedef CState<_Object> inherited;
public:
						CStateMonsterRestSleep	(_Object *obj);
	~CStateMonsterRestSleep	() override;

	void		initialize				() override;
	void		execute					() override;
	void		finalize				() override;
	void		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_rest_sleep_inline.h"
