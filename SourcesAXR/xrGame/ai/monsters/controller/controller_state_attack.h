#pragma once

#include "../state.h"
#include "../../../ai_debug.h"

template<typename _Object>
class	CStateControllerAttack : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
						CStateControllerAttack	(_Object *obj);
	~CStateControllerAttack	() override {}

	void		initialize				() override;
	void		finalize				() override;
	void		critical_finalize		() override;

	void		execute					() override;
	void		setup_substates			() override;
	void		check_force_state		() override;
	void		remove_links			(CObject * ) override {}
			bool		check_home_point		();
};

#include "controller_state_attack_inline.h"
