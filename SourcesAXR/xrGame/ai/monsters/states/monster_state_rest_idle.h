#pragma once

#include "../state.h"

template<typename _Object>
class CStateMonsterRestIdle : public CState<_Object> {
	typedef CState<_Object> inherited;
	typedef CState<_Object> *state_ptr;

	u32					m_target_node;

public:
						CStateMonsterRestIdle	(_Object *obj);
	void 		initialize				() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	void		reselect_state			() override;
	void		setup_substates			() override;
};

#include "monster_state_rest_idle_inline.h"
