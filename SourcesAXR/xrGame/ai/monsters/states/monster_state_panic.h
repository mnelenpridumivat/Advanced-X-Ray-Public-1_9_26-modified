#pragma once

#include "../state.h"

template<typename _Object>
class	CStateMonsterPanic : public CState<_Object> {
	typedef CState<_Object>		inherited;
	typedef CState<_Object>*	state_ptr;
	
public:
						CStateMonsterPanic		(_Object *obj);
	~CStateMonsterPanic		() override;

	void		initialize				() override;
	void		reselect_state			() override;
	void		check_force_state		() override;
	void		setup_substates			() override;
	void		remove_links			(CObject* object) override { inherited::remove_links(object);}
};

#include "monster_state_panic_inline.h"
