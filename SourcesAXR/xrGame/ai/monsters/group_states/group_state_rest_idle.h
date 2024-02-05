#pragma once

#include "../state.h"

template<typename _Object>
class CStateGroupRestIdle : public CState<_Object> {
	typedef CState<_Object> inherited;
	typedef CState<_Object> *state_ptr;

	u32					m_target_node;
	int					m_move_type;

public:
						CStateGroupRestIdle	(_Object *obj);
	void 		initialize				() override;
	void 		finalize				() override;
	void 		critical_finalize		() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}

	void		reselect_state			() override;
	void		setup_substates			() override;
};

#include "group_state_rest_idle_inline.h"
