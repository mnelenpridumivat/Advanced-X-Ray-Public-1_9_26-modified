#pragma once
#include "../state.h"

template<typename _Object>
class	CStateControllerPanic : public CState<_Object> {
protected:
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

	enum {
		eStateRun			= static_cast<u32>(0),
		eStateSteal,
		eStateLookAround,
	};

public:
						CStateControllerPanic	(_Object *obj);
	~CStateControllerPanic	() override;

	void		reselect_state			() override;
};

#include "controller_state_panic_inline.h"
