#pragma once

#include "../state.h"

template<typename _Object>
class	CStatePsyDogPsyAttack : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
						CStatePsyDogPsyAttack	(_Object *obj);
	~CStatePsyDogPsyAttack	() override {}

	void		reselect_state			() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "psy_dog_state_psy_attack_inline.h"
