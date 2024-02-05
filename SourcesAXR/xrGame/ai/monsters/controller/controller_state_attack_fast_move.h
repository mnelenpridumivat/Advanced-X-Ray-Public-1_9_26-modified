#pragma once

#include "../state.h"

template<typename _Object>
class	CStateControllerFastMove : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
public:
						CStateControllerFastMove	(_Object *obj) : inherited(obj) {}
	void		initialize					() override;
	void		finalize					() override;
	void		critical_finalize			() override;

	void		execute						() override;
};

#include "controller_state_attack_fast_move_inline.h"
