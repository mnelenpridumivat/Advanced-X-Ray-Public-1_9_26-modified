#pragma once

template<typename _Object>
class CStateMonsterHittedHide : public CState<_Object> {
	typedef	CState<_Object>		inherited;
	typedef	CState<_Object>*	state_ptr;

public:

					CStateMonsterHittedHide	(_Object *obj) : inherited(obj) {}
	~CStateMonsterHittedHide() override {}

	void	initialize				() override;
	void	execute					() override;
	void	remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 	check_completion		() override;
	bool 	check_start_conditions	() override;
};

#include "monster_state_hitted_hide_inline.h"

