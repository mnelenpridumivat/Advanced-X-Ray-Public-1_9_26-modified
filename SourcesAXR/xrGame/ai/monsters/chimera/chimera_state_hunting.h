#pragma once
#include "../state.h"

template<typename _Object>
class	CStateChimeraHunting : public CState<_Object> {
protected:
	typedef CState<_Object> inherited;
	typedef CState<_Object>* state_ptr;

	enum {
		eStateMoveToCover,
		eStateComeOut
	};

public:
						CStateChimeraHunting	(_Object *obj);

	void		reselect_state			() override;
	bool 		check_start_conditions	() override;
	bool 		check_completion		() override;	

};

#include "chimera_state_hunting_inline.h"
