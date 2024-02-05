#pragma once

template<typename _Object>
class CStatePsyDogHide : public CState<_Object> {
	typedef	CState<_Object>		inherited;
	typedef	CState<_Object>*	state_ptr;

	struct {
		Fvector position;
		u32		node;
	} target;


public:
					CStatePsyDogHide		(_Object *obj) : inherited(obj) {}
	~CStatePsyDogHide		() override {}

	void	initialize				() override;
	void	execute					() override;
	void	remove_links			(CObject* object) override { inherited::remove_links(object);}

	bool 	check_completion		() override;
	bool 	check_start_conditions	() override;

private:
			void	select_target_point		();
};

#include "psy_dog_state_psy_attack_hide_inline.h"

