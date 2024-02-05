#pragma once
#include "../state.h"

template<typename _Object>
class CStateBloodsuckerVampireHide : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;

public:
						CStateBloodsuckerVampireHide	(_Object *obj);

	void		reselect_state					() override;
	void		setup_substates					() override;
	bool		check_completion				() override;
	void		remove_links					(CObject* object) override { inherited::remove_links(object);}
};

#include "bloodsucker_vampire_hide_inline.h"
